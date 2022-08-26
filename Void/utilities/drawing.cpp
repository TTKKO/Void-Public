#include "drawing.hpp"

#pragma region imgui_extended

static constexpr std::array arr_key_names =
{
	"",
	"mouse 1", "mouse 2", "cancel", "mouse 3", "mouse 4", "mouse 5", "",
	"backspace", "tab", "", "", "clear", "enter", "", "",
	"shift", "control", "alt", "pause", "caps", "", "", "", "", "", "",
	"escape", "", "", "", "", "space", "page up", "page down",
	"end", "home", "left", "up", "right", "down", "", "", "",
	"print", "insert", "delete", "",
	"0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
	"", "", "", "", "", "", "",
	"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k",
	"l", "m", "n", "o", "p", "q", "r", "s", "t", "u",
	"v", "w", "x", "y", "z", "lwin", "rwin", "", "", "",
	"num0", "num1", "num2", "num3", "num4", "num5",
	"num6", "num7", "num8", "num9",
	"*", "+", "", "-", ".", "/",
	"f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8",
	"f9", "f10", "f11", "f12", "f13", "f14", "f15", "f16",
	"f17", "f18", "f19", "f20", "f21", "f22", "f23", "f24",
	"", "", "", "", "", "", "", "",
	"num lock", "scroll lock",
	"", "", "", "", "", "", "",
	"", "", "", "", "", "", "",
	"lshift", "rshift", "lctrl",
	"rctrl", "lmenu", "rmenu"
};

void ImGui::HelpMarker(const char* sz_description)
{
	TextDisabled(xorstr_("(?)"));
	if (IsItemHovered())
	{
		BeginTooltip();
		PushTextWrapPos(450.f);
		TextUnformatted(sz_description);
		PopTextWrapPos();
		EndTooltip();
	}
}

bool ImGui::ListBox(const char* sz_label, int* i_current_item, std::function<const char*(int)> p_lambda, const int n_items_count, const int i_height_in_items)
{
	return ListBox(sz_label, i_current_item, [](void* p_data, const int n_index, const char** sz_out_text)
	{
		*sz_out_text = (*static_cast<std::function<const char*(int)>*>(p_data))(n_index);
		return true;
	}, &p_lambda, n_items_count, i_height_in_items);
}

bool ImGui::HotKey(const char* sz_label, int* p_value)
{
	ImGuiContext& g = *GImGui;
	ImGuiWindow* p_window = g.CurrentWindow;

	if (p_window->SkipItems)
		return false;

	ImGuiIO& io = g.IO;
	const ImGuiStyle& style = g.Style;
	const ImGuiID n_index = p_window->GetID(sz_label);

	const float fl_width = CalcItemWidth();
	const ImVec2 vec_label_size = CalcTextSize(sz_label, nullptr, true);

	const ImRect rect_frame(p_window->DC.CursorPos + ImVec2(vec_label_size.x > 0.0f ? style.ItemInnerSpacing.x + GetFrameHeight() : 0.0f, 0.0f), p_window->DC.CursorPos + ImVec2(fl_width, vec_label_size.x > 0.0f ? vec_label_size.y + style.FramePadding.y : 0.f));
	const ImRect rect_total(rect_frame.Min, rect_frame.Max);

	ItemSize(rect_total, style.FramePadding.y);
	if (!ItemAdd(rect_total, n_index, &rect_frame, ImGuiItemFlags_Inputable))
		return false;

	const bool b_hovered = ItemHoverable(rect_frame, n_index);
	if (b_hovered)
	{
		SetHoveredID(n_index);
		g.MouseCursor = ImGuiMouseCursor_TextInput;
	}

	const bool b_clicked = b_hovered && io.MouseClicked[0];
	if (const bool b_double_clicked = b_hovered && g.IO.MouseDoubleClicked[0]; b_clicked || b_double_clicked)
	{
		if (g.ActiveId != n_index)
		{
			std::memset(io.MouseDown, 0, sizeof io.MouseDown);
			std::memset(io.KeysDown, 0, sizeof io.KeysDown);
			*p_value = 0;
		}

		SetActiveID(n_index, p_window);
		FocusWindow(p_window);
	}

	bool b_value_changed = false;
	if (int n_key = *p_value; g.ActiveId == n_index)
	{
		for (int n = 0; n < IM_ARRAYSIZE(io.MouseDown); n++)
		{
			if (IsMouseDown(n))
			{
				switch (n)
				{
				case 0:
					n_key = VK_LBUTTON;
					break;
				case 1:
					n_key = VK_RBUTTON;
					break;
				case 2:
					n_key = VK_MBUTTON;
					break;
				case 3:
					n_key = VK_XBUTTON1;
					break;
				case 4:
					n_key = VK_XBUTTON2;
					break;
				}

				b_value_changed = true;
				ClearActiveID();
			}
		}

		if (!b_value_changed)
		{
			for (int n = VK_BACK; n <= VK_RMENU; n++)
			{
				if (IsKeyDown(n))
				{
					n_key = n;
					b_value_changed = true;
					ClearActiveID();
				}
			}
		}

		if (IsKeyDown(io.KeyMap[ImGuiKey_Escape]))
		{
			*p_value = 0;
			ClearActiveID();
		}
		else
			*p_value = n_key;
	}

	char ch_buffer[64] = {};
	sprintf_s(ch_buffer, sizeof ch_buffer, xorstr_("[ %s ]"), *p_value != 0 && g.ActiveId != n_index ? arr_key_names.at(*p_value) : g.ActiveId == n_index ? xorstr_("press") : xorstr_("none"));

	// modified by qo0
	PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));
	p_window->DrawList->AddText(ImVec2(rect_frame.Max.x - CalcTextSize(ch_buffer).x, rect_total.Min.y + style.FramePadding.y), GetColorU32(g.ActiveId == n_index ? ImGuiCol_Text : ImGuiCol_TextDisabled), ch_buffer);

	if (vec_label_size.x > 0.f)
		RenderText(ImVec2(rect_total.Min.x, rect_total.Min.y + style.FramePadding.y), sz_label);

	PopStyleVar();
	return b_value_changed;
}

bool ImGui::MultiCombo(const char* sz_label, std::vector<bool>& vec_values, const std::string_view* arr_items, const int n_items_count)
{
	const ImGuiContext& g = *GImGui;

	if (const ImGuiWindow* p_window = g.CurrentWindow; p_window->SkipItems)
		return false;

	const ImGuiStyle& style = g.Style;
	const float fl_active_width = CalcItemWidth() - (style.ItemInnerSpacing.x + GetFrameHeight()) - 40.f;

	std::vector<std::string_view> vec_active_items = {};

	// collect active items
	for (int i = 0; i < n_items_count; i++)
	{
		if (vec_values[i])
			vec_active_items.push_back(arr_items[i]);
	}

	std::string sz_buffer = {};
	for (std::size_t i = 0U; i < vec_active_items.size(); i++)
	{
		sz_buffer.append(vec_active_items[i]);

		if (i < vec_active_items.size() - 1U)
			sz_buffer.append(xorstr_(", "));
	}

	if (sz_buffer.empty())
		sz_buffer.assign(xorstr_("none"));
	else
	{
		const char* sz_wrap_position = g.Font->CalcWordWrapPositionA(GetCurrentWindow()->FontWindowScale, &sz_buffer[0], sz_buffer.data() + sz_buffer.length(), fl_active_width - style.FramePadding.x * 2.0f);

		if (const std::size_t n_wrap_length = sz_wrap_position - &sz_buffer[0]; n_wrap_length > 0U && n_wrap_length <
			sz_buffer.length())
		{
			sz_buffer.resize(n_wrap_length);
			sz_buffer.append(xorstr_("..."));
		}
	}


	bool b_value_changed = false;
	if (BeginCombo(sz_label, sz_buffer.c_str()))
	{
		for (int i = 0; i < n_items_count; i++)
		{
			if (Selectable(arr_items[i].data(), vec_values[i], ImGuiSelectableFlags_DontClosePopups))
			{
				vec_values[i] = !vec_values[i];
				b_value_changed = true;
			}
		}

		EndCombo();
	}

	return b_value_changed;
}

bool ImGui::Combo(const char* sz_label, std::vector<int>& vec_values, const int n_index, const char* sz_items_separated_by_zeros, const int n_height_in_items)
{
	int iValue = vec_values[n_index];
	const bool bValueChanged = Combo(sz_label, &iValue, sz_items_separated_by_zeros, n_height_in_items);

	if (bValueChanged)
		vec_values[n_index] = iValue;

	return bValueChanged;
}

bool ImGui::Checkbox(const char* sz_label, std::vector<bool>& vec_values, const std::size_t n_index)
{
	bool b_value = vec_values[n_index];
	const bool b_value_changed = Checkbox(sz_label, &b_value);

	if (b_value_changed)
		vec_values[n_index] = b_value;

	return b_value_changed;
}

bool ImGui::SliderFloat(const char* sz_label, std::vector<float>& vec_values, const int n_index, const float fl_min, const float fl_max, const char* sz_format, const float fl_power)
{
	float fl_value = vec_values[n_index];
	const bool b_value_changed = SliderFloat(sz_label, &fl_value, fl_min, fl_max, sz_format, fl_power);

	if (b_value_changed)
		vec_values[n_index] = fl_value;

	return b_value_changed;
}

bool ImGui::SliderInt(const char* sz_label, std::vector<int>& vec_values, const int n_index, const int i_min, const int i_max, const char* sz_format)
{
	int i_value = vec_values[n_index];
	const bool b_value_changed = SliderInt(sz_label, &i_value, i_min, i_max, sz_format);

	if (b_value_changed)
		vec_values[n_index] = i_value;

	return b_value_changed;
}

bool ImGui::ColorEdit3(const char* sz_label, sdk::color* p_color, const ImGuiColorEditFlags flags)
{
	return ColorEdit4(sz_label, p_color, flags);
}

auto ImGui::ColorEdit4(const char* sz_label, sdk::color* p_color, const ImGuiColorEditFlags flags) -> bool
{
	ImVec4 vec_color = p_color->get_vec4();

	if (ColorEdit4(sz_label, &vec_color.x, flags))
	{
		*p_color = sdk::color(vec_color.x, vec_color.y, vec_color.z, vec_color.w);
		return true;
	}

	return false;
}
#pragma endregion

#pragma region drawing_library
bool drawing::setup(ID3D11Device* p_device, ID3D11DeviceContext* p_context, HWND wnd)
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.WantCaptureMouse = true;

	// VMProtectBeginMutation("Drawing Setup");

	// load fonts
	static const std::string_view verdana_location = SECSTR(R"(C:\Windows\Fonts\Verdana.ttf)");

	ImFontConfig im_autohint_cfg;
	im_autohint_cfg.FontBuilderFlags = ImGuiFreeTypeBuilderFlags_ForceAutoHint;
	byte_resources::whitney = io.Fonts->AddFontFromMemoryCompressedTTF(whitney_compressed_data, whitney_compressed_size, 16.f, &im_autohint_cfg, io.Fonts->GetGlyphRangesCyrillic());
	byte_resources::verdana_small = io.Fonts->AddFontFromFileTTF(verdana_location.data(), 15.f, &im_autohint_cfg, io.Fonts->GetGlyphRangesCyrillic());
	byte_resources::verdana_medium = io.Fonts->AddFontFromFileTTF(verdana_location.data(), 16.f, &im_autohint_cfg, io.Fonts->GetGlyphRangesCyrillic());
	byte_resources::verdana_big = io.Fonts->AddFontFromFileTTF(verdana_location.data(), 20.f, &im_autohint_cfg, io.Fonts->GetGlyphRangesCyrillic());

	ImFontConfig im_verdana_bold_cfg;
	im_verdana_bold_cfg.FontBuilderFlags = ImGuiFreeTypeBuilderFlags_Bold;
	byte_resources::verdana_small_bold = io.Fonts->AddFontFromFileTTF(verdana_location.data(), 14.f, &im_verdana_bold_cfg, io.Fonts->GetGlyphRangesCyrillic());
	byte_resources::verdana_medium_bold = io.Fonts->AddFontFromFileTTF(verdana_location.data(), 16.f, &im_verdana_bold_cfg, io.Fonts->GetGlyphRangesCyrillic());

	io.FontDefault = byte_resources::whitney;

	// load textures
	if (!load_image(p_device, &byte_resources::void_logo, void_logo_bitmap, 240, 204))
		return false;

	if (!load_image(p_device, &byte_resources::checkmark, checkmark_bitmap, 64, 64))
		return false;

	// setup platform and renderer bindings
	if (!ImGui_ImplWin32_Init(wnd))
		return false;

	if (!ImGui_ImplDX11_Init(p_device, p_context))
		return false;

	if (!ImGui_ImplDX11_CreateDeviceObjects())
		return false;

	// VMProtectEnd();

	initialized = true;
	io.ImeWindowHandle = wnd;

#pragma region draw_style
	// @credits: styles curtosey of https://github.com/rollraw/qo0-base
	// setup styles
	ImGuiStyle& style = ImGui::GetStyle();
	style.Alpha = 1.0f;
	style.WindowPadding = ImVec2(8, 8);
	style.WindowRounding = 4.0f;
	style.WindowBorderSize = 1.0f;
	style.WindowMinSize = ImVec2(32, 32);
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style.ChildRounding = 4.0f;
	style.ChildBorderSize = 1.0f;
	style.PopupRounding = 4.0f;
	style.PopupBorderSize = 1.0f;
	style.FramePadding = ImVec2(4, 2);
	style.FrameRounding = 2.0f;
	style.FrameBorderSize = 1.0f;
	style.ItemSpacing = ImVec2(8, 4);
	style.ItemInnerSpacing = ImVec2(4, 4);
	style.IndentSpacing = 6.0f;
	style.ColumnsMinSpacing = 6.0f;
	style.ScrollbarSize = 6.0f;
	style.ScrollbarRounding = 9.0f;
	style.GrabMinSize = 0.0f;
	style.GrabRounding = 4.0f;
	style.TabRounding = 4.0f;
	style.TabBorderSize = 1.0f;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.SelectableTextAlign = ImVec2(0.0f, 0.5f);
	style.MouseCursorScale = 0.75f;
#pragma endregion

	set_colors();

	return true;
}

void drawing::destroy()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void drawing::set_colors()
{
	auto& style = ImGui::GetStyle();

#pragma region draw_style_color
	/*
	 * color navigation:
	 * [definition N][purpose]	[color] [rgb]
	 1 primitive:
	 -	primtv 0 (text) - white: 255,255,255
	 -	primtv 1 (background) - darkslategrey: 20,20,30
	 -	primtv 2 (disabled) - silver: 192,192,192
	 -	primtv 3 (control bg) - cadetblue: 30,35,50
	 -	primtv 4 (border) - black: 0,0,0
	 -	primtv 5 (hover) - matterhorn: 75,75,75
	 *
	 2 accents:
	 -	accent 0 (main) - blueviolet: 140,40,225
	 *	accent 1 (dark) - indigo: 55,0,100
	 *	accent 3 (darker) - darkviolet: 75,50,105
	 */

	constexpr auto p3 = sdk::color(0.101f, 0.121f, 0.156f).base();
	constexpr auto p5 = sdk::color(0.302f, 0.255f, 0.318f).base();

	const auto p6 = config::get<sdk::color>(g_context.color_primtv6).base();
	const auto a0 = config::get<sdk::color>(g_context.color_accent0).base();
	const auto a1 = config::get<sdk::color>(g_context.color_accent1).base();
	const auto a2 = config::get<sdk::color>(g_context.color_accent2).base();

	style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f); // primtv 0
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.75f, 0.75f, 0.75f, 0.85f); // primtv 2
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(a1[color_r], a1[color_g], a1[color_b], 0.85f); // accent 1
	style.Colors[ImGuiCol_WindowBg] = ImVec4(p3[color_r], p3[color_g], p3[color_b], 1.00f); // primtv 3
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.08f, 0.08f, 0.12f, 0.60f); // primtv 1
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.12f, 0.85f); // primtv 1
	style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.10f); // primtv 4
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f); // clear
	style.Colors[ImGuiCol_FrameBg] = ImVec4(p3[color_r], p3[color_g], p3[color_b], 1.00f); // primtv 3
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(a1[color_r], a1[color_g], a1[color_b], 1.00f); // accent 1
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(a0[color_r], a0[color_g], a0[color_b], 1.00f); // accent 0
	style.Colors[ImGuiCol_TitleBg] = ImVec4(a0[color_r], a0[color_g], a0[color_b], 0.70f); // accent 0
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(a0[color_r], a0[color_g], a0[color_b], 0.85f); // accent 1
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(a0[color_r], a0[color_g], a0[color_b], 0.70f); // accent 1
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.08f, 0.08f, 0.12f, 0.70f); // primtv 1
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(p3[color_r], p3[color_g], p3[color_b], 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(a2[color_r], a2[color_g], a2[color_b], 1.00f); // accent 3
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(p5[color_r], p5[color_g], p5[color_b], 0.90f); // primtv 5
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.75f, 0.75f, 0.75f, 0.10f); // primtv 2
	style.Colors[ImGuiCol_CheckMark] = ImVec4(p6[color_r], p6[color_g], p6[color_b], 0.70f); // accent 1
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(a0[color_r], a0[color_g], a0[color_b], 1.00f); // accent 0
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(a1[color_r], a1[color_g], a1[color_b], 1.00f); // accent 1
	style.Colors[ImGuiCol_Button] = ImVec4(p6[color_r], p6[color_g], p6[color_b], 0.70f); // primtv 3
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(p5[color_r], p5[color_g], p5[color_b], 1.00f); // primtv 5
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(a0[color_r], a0[color_g], a0[color_b], 1.00f); // accent 0
	style.Colors[ImGuiCol_Header] = ImVec4(a0[color_r], a0[color_g], a0[color_b], 1.00f); // accent 0
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(p5[color_r], p5[color_g], p5[color_b], 1.00f); // primtv 5
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(p3[color_r], p3[color_g], p3[color_b], 1.00f); // primtv 3
	style.Colors[ImGuiCol_Separator] = ImVec4(p3[color_r], p3[color_g], p3[color_b], 1.00f); // primtv 3
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(p5[color_r], p5[color_g], p5[color_b], 1.00f); // primtv 5
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(a0[color_r], a0[color_g], a0[color_b], 1.00f); // accent 0
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(a0[color_r], a0[color_g], a0[color_b], 1.00f); // accent 0
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(p5[color_r], p5[color_g], p5[color_b], 0.70f); // primtv 5
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(a1[color_r], a1[color_g], a1[color_b], 1.00f); // accent 1
	style.Colors[ImGuiCol_Tab] = ImVec4(0.1f, 0.07f, 0.18f, 0.80f); // primtv 1
	style.Colors[ImGuiCol_TabHovered] = ImVec4(p5[color_r], p5[color_g], p5[color_b], 0.80f); // primtv 5
	style.Colors[ImGuiCol_TabActive] = ImVec4(p6[color_r], p6[color_g], p6[color_b], 0.700f); // accent 0
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(p5[color_r], p5[color_g], p5[color_b], 0.70f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(a0[color_r], a0[color_g], a0[color_b] / 255, 0.60f); // accent 0
	style.Colors[ImGuiCol_PlotLines] = ImVec4(a0[color_r], a0[color_g], a0[color_b], 1.00f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(a0[color_r], a0[color_g], a0[color_b], 0.50f); // accent 0
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(a0[color_r], a0[color_g], a0[color_b], 1.00f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(a0[color_r], a0[color_g], a0[color_b], 0.50f); // accent 0
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(a2[color_r], a2[color_g], a2[color_b], 0.80f); // accent 3
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.25f); // primtv 4
}

void drawing::set_rgb_colors(const float hue)
{
	auto& style = ImGui::GetStyle();

	const auto accent0 = ImColor::HSV(hue, 0.3f, 0.6f).Value;
	const auto accent1 = ImColor::HSV(hue, 0.5f, 0.8f).Value;
	const auto accent2 = ImColor::HSV(hue, 0.6f, 0.6f).Value;

	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(accent1.x, accent1.y, accent1.z, 0.85f); // accent 1
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(accent1.x, accent1.y, accent1.z, 1.00f); // accent 1
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(accent0.x, accent0.y, accent0.z, 1.00f); // accent 0
	style.Colors[ImGuiCol_TitleBg] = ImVec4(accent0.x, accent0.y, accent0.z, 0.70f); // accent 0
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(accent0.x, accent0.y, accent0.z, 0.85f); // accent 1
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(accent0.x, accent0.y, accent0.z, 0.70f); // accent 1
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(accent2.x, accent2.y, accent2.z, 1.00f); // accent 3
	style.Colors[ImGuiCol_CheckMark] = ImVec4(accent1.x, accent1.y, accent1.z, 1.00f); // accent 1
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(accent0.x, accent0.y, accent0.z, 1.00f); // accent 0
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(accent1.x, accent1.y, accent1.z, 1.00f); // accent 1
	style.Colors[ImGuiCol_Button] = ImVec4(accent1.x, accent1.y, accent1.z, 0.70f); // primtv 3
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(accent0.x, accent0.y, accent0.z, 1.00f); // accent 0
	style.Colors[ImGuiCol_Header] = ImVec4(accent0.x, accent0.y, accent0.z, 1.00f); // accent 0
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(accent0.x, accent0.y, accent0.z, 1.00f); // accent 0
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(accent0.x, accent0.y, accent0.z, 1.00f); // accent 0
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(accent1.x, accent1.y, accent1.z, 1.00f); // accent 1
	style.Colors[ImGuiCol_TabActive] = ImVec4(accent1.x, accent1.y, accent1.z, 0.70f); // accent 0
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(accent0.x, accent0.y, accent0.z, 0.60f); // accent 0
	style.Colors[ImGuiCol_PlotLines] = ImVec4(accent0.x, accent0.y, accent0.z, 1.00f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(accent0.x, accent0.y, accent0.z, 0.50f); // accent 0
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(accent0.x, accent0.y, accent0.z, 1.00f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(accent0.x, accent0.y, accent0.z, 0.50f); // accent 0
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(accent2.x, accent2.y, accent2.z, 0.80f); // accent 3
}
#pragma endregion

bool drawing::load_image(ID3D11Device* p_device, ID3D11ShaderResourceView** shader_view, const std::uint8_t* data, const UINT width, const UINT height)
{
	// @note: width * (sizeof byte * 4 for r,g,b,a)
	// @note: another way of calculating bytes per row of pixels would be sizeof(data) / height
	const D3D11_SUBRESOURCE_DATA init_data = {
		data,
		static_cast<DWORD>(width * (sizeof(std::uint8_t) * 4)),
		0
	};

	const D3D11_TEXTURE2D_DESC desc = {
		width,
		height,
		1,
		1,
		DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_SAMPLE_DESC{1, 0},
		D3D11_USAGE_DEFAULT,
		D3D11_BIND_SHADER_RESOURCE,
		0
	};

	ID3D11Texture2D* tex = nullptr;
	if (SUCCEEDED(p_device->CreateTexture2D(&desc, &init_data, &tex)))
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc = {
			DXGI_FORMAT_R8G8B8A8_UNORM,
			D3D11_SRV_DIMENSION_TEXTURE2D
		};
		srv_desc.Texture2D.MipLevels = 1;

		if (FAILED(p_device->CreateShaderResourceView(tex, &srv_desc, shader_view)))
			return false;

		return true;
	}

	return false;
}