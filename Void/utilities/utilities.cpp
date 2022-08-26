#include "utilities.hpp"
#include <random>
#include <mutex>
#include <Psapi.h>

std::string utility::get_date()
{
	const auto tp = std::chrono::system_clock::now();
	const auto tpm = date::floor<std::chrono::minutes>(tp); // truncate to minutes precision
	const auto dp = floor<date::days>(tpm);
	const auto ymd = date::year_month_day(dp);

	std::stringstream ss;
	ss << ymd.month() << xorstr_(" ") << ymd.day() << xorstr_(" ") << ymd.year();
	return ss.str();
}

std::string utility::get_time()
{
	const std::time_t now = std::time(nullptr);

	const std::tm tstruct = *std::localtime(&now);
	char buf[80];

	std::strftime(buf, sizeof buf, xorstr_("%X"), &tstruct);
	return buf;
}

std::size_t utility::write_data_callback(const void* ptr, const std::size_t size, const std::size_t nmemb, FILE* stream)
{
	const size_t written = fwrite(ptr, size, nmemb, stream);
	return written;
}

#pragma region string_manipulation
std::string utility::unicode_ascii(const std::wstring_view wsz_unicode)
{
	const int n_length = WideCharToMultiByte(CP_UTF8, 0ul, wsz_unicode.data(), static_cast<int>(wsz_unicode.length()), nullptr, 0, nullptr, nullptr);
	std::string sz_output = {};

	if (n_length > 0)
	{
		sz_output.resize(n_length);
		if (!WideCharToMultiByte(CP_UTF8, 0ul, wsz_unicode.data(), static_cast<int>(wsz_unicode.length()), &sz_output[0], n_length, nullptr, nullptr))
			throw std::range_error(format(xorstr_("bad conversion [utf16->utf8] [{:d}]"), GetLastError()));
	}

	return sz_output;
}

std::wstring utility::ascii_encode(const std::string_view sz_ascii)
{
	const int n_length = MultiByteToWideChar(CP_UTF8, 0ul, sz_ascii.data(), static_cast<int>(sz_ascii.length()), nullptr, 0);
	std::wstring wsz_output = {};

	if (n_length > 0)
	{
		wsz_output.resize(n_length);
		if (!MultiByteToWideChar(CP_UTF8, 0ul, sz_ascii.data(), static_cast<int>(sz_ascii.length()), &wsz_output[0], n_length))
			throw std::range_error(format(xorstr_("bad conversion [utf8->utf16] [{:d}]"), GetLastError()));
	}

	return wsz_output;
}

void utility::unicode_tolower(std::wstring& wsz_text)
{
	std::ranges::transform(wsz_text, wsz_text.begin(), tolower);
}

void utility::unicode_toupper(std::wstring& wsz_text)
{
	std::ranges::transform(wsz_text, wsz_text.begin(), toupper);
}

void utility::ascii_tolower(std::string& sz_text)
{
	std::ranges::transform(sz_text, sz_text.begin(), [](const std::uint8_t c) { return std::tolower(c); });
}

void utility::ascii_toupper(std::string& sz_text)
{
	std::ranges::transform(sz_text, sz_text.begin(), [](const std::uint8_t c) { return std::toupper(c); });
}
#pragma endregion

std::string utility::get_clipboard()
{
	// VMProtectBeginMutation("GetClipboard");

	if (!OpenClipboard(nullptr))
		return xorstr_("failed to get clipboard.");

	const HANDLE h_data = GetClipboardData(CF_TEXT);

	if (!h_data)
		return xorstr_("failed to get clipboard.");

	const char* psz_text = static_cast<char*>(GlobalLock(h_data));

	if (!psz_text)
		return xorstr_("failed to get clipboard.");

	std::string text(psz_text);

	GlobalUnlock(h_data);
	CloseClipboard();

	// VMProtectEnd();
	return text;
}

void utility::set_clipboard(const std::string_view sz_text)
{
	// VMProtectBeginMutation("SetClipboard");

	const HGLOBAL h_mem = GlobalAlloc(GMEM_MOVEABLE, sz_text.size() + 1);

	if (!h_mem)
		return;

	const LPVOID lock = GlobalLock(h_mem);

	if (!lock)
		return;

	memcpy(lock, sz_text.data(), sz_text.size() + 1);

	GlobalUnlock(h_mem);

	if (!OpenClipboard(nullptr))
		return;

	if (!EmptyClipboard())
		return;

	SetClipboardData(CF_TEXT, h_mem);
	CloseClipboard();

	// VMProtectEnd();
}

std::wstring utility::get_parent_path()
{
	std::vector<wchar_t> path_buf;

	DWORD copied = 0;
	do
	{
		path_buf.resize(path_buf.size() + MAX_PATH);
		copied = GetModuleFileNameW(nullptr, &path_buf.at(0), path_buf.size());
	}
	while (copied >= path_buf.size());

	// VMProtectBeginVirtualization("GetParentPath");

	path_buf.resize(copied);

	// VMProtectEnd();
	return { path_buf.begin(), path_buf.end() };
}

std::vector<std::string> utility::split(const std::string& str, const std::string& regex_str)
{
	const std::regex regexz(regex_str);
	std::vector<std::string> list(std::sregex_token_iterator(str.begin(), str.end(), regexz, -1), std::sregex_token_iterator());
	return list;
}

#pragma region logging_util
bool logging::attach(const wchar_t* sz_console_title)
{
	// VMProtectBeginUltra("Logging Attach");

	if (!GetConsoleWindow())
		if (!AllocConsole())
			return false;

	AttachConsole(ATTACH_PARENT_PROCESS);

	if (freopen_s(&p_istream, SECSTR("CONIN$"), SECSTR("r"), stdin) != 0)
		return false;
	if (freopen_s(&p_estream, SECSTR("CONOUT$"), SECSTR("w"), stderr) != 0)
		return false;
	if (freopen_s(&p_ostream, SECSTR("CONOUT$"), SECSTR("w"), stdout) != 0)
		return false;

	// @note: vrtool <3
	const auto h_stdout = CreateFileW(SECSTRW(L"CONOUT$"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	const auto h_stdin = CreateFileW(SECSTRW(L"CONIN$"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	SetStdHandle(STD_OUTPUT_HANDLE, h_stdout);
	SetStdHandle(STD_ERROR_HANDLE, h_stdout);
	SetStdHandle(STD_INPUT_HANDLE, h_stdin);

	if (!SetConsoleTitleW(sz_console_title))
		return false;

	const std::string_view text = SECSTR(
			"               ,---.            ,--,         ,---,            \n"
			"              /__./|   ,---.  ,--.'|       ,---.'|            \n"
			"         ,---.;  ; |  '   ,'\\ |  |,        |   | :            \n"
			"        /___/ \\  | | /   /   |`--'_        |   | |            \n"
			"        \\   ;  \\ ' |.   ; ,. :,' ,'|     ,--.__| |            \n"
			"         \\   \\  \\: |'   | |: :'  | |    /   ,'   |            \n"
			"          ;   \\  ' .'   | .; :|  | :   .   '  /  |            \n"
			"           \\   \\   '|   :    |'  : |__ '   ; |:  |            \n"
			"            \\   `  ; \\   \\  / |  | '.'||   | '/  '            \n"
			"             :   \\ |  `----'  ;  :    ;|   :    :|            \n"
			"              '---\"           |  ,   /  \\   \\  /              \n"
			"  ,----..    ,--,              ---`-'    `----'       ___     \n"
			" /   /   \\ ,--.'|     ,--,                          ,--.'|_   \n"
			"|   :     :|  | :   ,--.'|                  ,---,   |  | :,'  \n"
			".   |  ;. /:  : '   |  |,               ,-+-. /  |  :  : ' :  \n"
			".   ; /--` |  ' |   `--'_       ,---.  ,--.'|'   |.;__,'  /   \n"
			";   | ;    '  | |   ,' ,'|     /     \\|   |  ,\"' ||  |   |    \n"
			"|   : |    |  | :   '  | |    /    /  |   | /  | |:__,'| :    \n"
			".   | '___ '  : |__ |  | :   .    ' / |   | |  | |  '  : |__  \n"
			"'   ; : .'||  | '.'|'  : |__ '   ;   /|   | |  |/   |  | '.'| \n"
			"'   | '/  :;  :    ;|  | '.'|'   |  / |   | |--'    ;  :    ; \n"
			"|   :    / |  ,   / ;  :    ;|   :    |   |/        |  ,   /  \n"
			" \\   \\ .'   ---`-'  |  ,   /  \\   \\  /'---'          ---`-'   \n"
			"  `---`              ---`-'    `----'                         ");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSE_MAGENTA);
	std::cout << text << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSE_BLUE);
	std::cout << SECSTR("                   made with <3 by azurilex.                   ") << std::endl;
	std::cout << SECSTR("       knock knock, bitch, i'm kicking in the front door       ") << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), w_console_color);

	// VMProtectEnd();
	return true;
}

void logging::detach()
{
	fclose(p_istream);
	fclose(p_estream);
	fclose(p_ostream);
	FreeConsole();

	if (const auto h_console_wnd = GetConsoleWindow(); h_console_wnd != nullptr)
		PostMessageW(h_console_wnd, WM_CLOSE, 0U, 0L);
}

void logging::clear()
{
	buf.clear();
	line_offsets.clear();
	line_offsets.push_back(0);
}

void logging::draw(const ImColor& rainbow, const bool draw_rainbow)
{
	ImGui::BeginChild(xorstr_("scrolling"), ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar);
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 2));
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 4.f);

		const char* buf_start = buf.begin();
		const char* buf_end = buf.end();

		const char* time_buf_start = buf_times.begin();
		const char* time_buf_end = buf_times.end();

		ImGuiListClipper clipper;

		if (line_offsets.Size >= 1)
			clipper.Begin(line_offsets.Size - 1);
		else
			clipper.Begin(line_offsets.Size);

		while (clipper.Step())
		{
			for (std::int32_t line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
			{
				ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 4.f);

				ImGui::TextUnformatted(xorstr_("["));
				ImGui::SameLine();
				draw_rainbow ? ImGui::PushStyleColor(ImGuiCol_Text, rainbow.Value) : ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(170, 107, 241, 255));
				const char* time_line_start = time_buf_start + buf_times_offsets[line_no];
				const char* time_line_end = line_no + 1 < buf_times_offsets.Size ? time_buf_start + buf_times_offsets[line_no + 1] : time_buf_end;
				ImGui::TextUnformatted(time_line_start, time_line_end);
				ImGui::PopStyleColor();
				ImGui::SameLine();
				ImGui::TextUnformatted(xorstr_("] "));
				ImGui::SameLine();

				const char* log_line_start = buf_start + line_offsets[line_no];
				const char* log_line_end = line_no + 1 < line_offsets.Size ? buf_start + line_offsets[line_no + 1] - 1 : buf_end;
				ImGui::TextUnformatted(log_line_start, log_line_end);
			}
		}
		clipper.End();

		if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY() - 2.f)
			ImGui::SetScrollHereY(1.f);

		ImGui::PopStyleVar();
		ImGui::EndChild();
	}
}
#pragma endregion