#include "hooks/events.hpp"
#include "hooks/patches.hpp"
#include "hooks/dx11.hpp"

DWORD entrypoint(LPVOID lp_parameter)
{
	/* - Check what process we're attached to - */

	// VMProtectBeginUltra("Core Entry");

	// @note: auth ommitted

	//auto& cl_instance = connection_listener::get();

	//if (!VMProtectIsProtected())
	//	cl_instance.induce_crash(SECSTR("failed integrity check"));
	//if (VMProtectIsDebuggerPresent(true))
	//	cl_instance.induce_crash(SECSTR("failed integrity check"));

	const std::filesystem::path parent_path = utility::get_parent_path();
	const auto parent_directory = parent_path.parent_path();

	//if (parent_path.filename() == SECSTRW(L"VRChat.exe") && exists(parent_directory / SECSTRW(L"VRChat.exe")))
	//{
	//	//const std::wstring dir = parent_path.erase(parent_path.length() - 10);
	//	if (!exists(parent_directory / SECSTRW(L"UnityPlayer.dll")))
	//		cl_instance.induce_crash(SECSTR("failed file check"));
	//}
	//else cl_instance.induce_crash(SECSTR("failed file check"));

	// VMProtectEnd();

	const auto start = std::chrono::high_resolution_clock::now();

	while (!memory::get_module_base_handle(CLIENT_DLL))
		std::this_thread::sleep_for(std::chrono::milliseconds(10));

	while (!memory::get_module_base_handle(DX11_DLL))
		std::this_thread::sleep_for(std::chrono::milliseconds(10));

	while (!memory::get_module_base_handle(ENGINE_DLL))
		std::this_thread::sleep_for(std::chrono::milliseconds(10));

	// VMProtectBeginUltra("Core Checks");

	//if (!VMProtectIsProtected())
	//	cl_instance.induce_crash(SECSTR("failed integrity check"));
	//if (VMProtectIsDebuggerPresent(true))
	//	cl_instance.induce_crash(SECSTR("failed integrity check"));

	const std::string text = SECSTR("void - ") + std::string(stage) + SECSTR(" build ") + std::string(build);

	// VMProtectEnd();

	try
	{
		// VMProtectBeginUltra("Core Console Hook (try)");

		if (!logging::attach(utility::ascii_encode(text).c_str()))
			throw std::runtime_error(SECSTR("failed to hook console"));

		// VMProtectEnd();
	}
	catch (const std::exception& e)
	{
		logging::push(FOREGROUND_INTENSE_RED);
		logging::print(SECSTR("[critical] {}\n"), e.what());
		logging::pop();

#ifdef _DEBUG
        _RPT0(_CRT_ERROR, e.what());
#else
		memory::relink_module_to_peb(memory::void_handle);
		FreeLibraryAndExitThread(static_cast<HMODULE>(lp_parameter), EXIT_FAILURE);
#endif
	}

	// VMProtectBeginUltra("Core Authentication");

	logging::ofs_file.open(config::get_working_path().append(SECSTR("void.log")), std::ios::out | std::ios::trunc);

	logging::push(FOREGROUND_INTENSE_CYAN);
	logging::add_log(SECSTR("[log] Initializing graphical client...\n"));
	logging::pop();

	//cl_instance.initialize_socket();
	//cl_instance.authenticate();

	//std::int32_t i_passes = 0;
	//while (cl_instance.authenticated == connection_listener::auth_status::running)
	//{
	//	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	//	i_passes++;

	//	if (i_passes >= 1000)
	//		cl_instance.induce_crash(SECSTR("timed out"));
	//}

	//if (cl_instance.authenticated != connection_listener::auth_status::success)
	//	cl_instance.induce_crash(SECSTR("failed authentication."));

	//cl_instance.authenticated = connection_listener::auth_status::awaiting;
	//cl_instance.start_worker();

	//if (!VMProtectIsProtected())
	//	cl_instance.induce_crash(SECSTR("failed integrity check"));
	//if (VMProtectIsDebuggerPresent(true))
	//	cl_instance.induce_crash(SECSTR("failed integrity check"));

	//if (cl_instance.should_close)
	//{
	//	memory::relink_module_to_peb(memory::void_handle);
	//	FreeLibraryAndExitThread(static_cast<HMODULE>(lp_parameter), EXIT_FAILURE);
	//}

	// VMProtectEnd();

	try
	{
		logging::push(FOREGROUND_INTENSE_CYAN);
		logging::print(SECSTR("[log] getting required handles...\n"));
		logging::pop();

		memory::game_assembly_handle = memory::get_module_base_handle(CLIENT_DLL);
		if (memory::game_assembly_handle == nullptr)
			throw std::runtime_error(SECSTR("failed to get gameassembly handle."));

		memory::unity_player_handle = memory::get_module_base_handle(ENGINE_DLL);
		if (memory::unity_player_handle == nullptr)
			throw std::runtime_error(SECSTR("failed to get unityplayer handle."));

		memory::mono_handle = memory::get_module_base_handle(MONO_DLL);

		logging::push(FOREGROUND_INTENSE_CYAN);
		logging::print(SECSTR("[log] loading user config...\n"));
		logging::pop();

		config::setup(SECSTR("config.void"));
		misc::load_config();

		if (const auto res = dx11_hook::init(); res != kiero::status::Enum::success)
			throw std::runtime_error(utility::format(SECSTR("failed to initialize kiero hooks [status: {:d}]"), static_cast<std::int32_t>(res)));

		auto& detours_instance = detours::get();
		detours_instance.setup_ratelimter();
		detours_instance.setup();
		if (!detours_instance.init())
			throw std::runtime_error(SECSTR("failed to initialize hooks"));

		auto& patches_instance = patches::get();
		patches_instance.setup();
		if (!patches_instance.init())
			throw std::runtime_error(SECSTR("failed to initialize patches"));

#if LVM_TESTING == 1
		vlvm::initialize();
#endif

		// @todo: set working directory cus munchen is retarded
		// std::filesystem::current_path(utility::get_parent_path());

		// VMProtectBeginUltra("Core Finializing");

		/*cl_instance.handler.socket()->on(SECSTR("update_motd"), [&](const sio::event& ev)
		{
			try
			{
				const auto& map = ev.get_message()->get_map();

				if (const auto code = map.at(SECSTR("code"))->get_int(); code == 200)
					msg = map.at(SECSTR("message"))->get_string();
				else
					throw std::runtime_error(utility::format(SECSTR("failed to update motd [code {:d}]"), code));
			}
			catch (const std::exception& e)
			{
				logging::push(FOREGROUND_INTENSE_RED);
				logging::print(SECSTR("[critical] {}\n"), e.what());
				logging::pop();
			}
		});*/

		/*cl_instance.handler.socket()->emit(SECSTR("get_motd"), nullptr, [&](const sio::message::list& response)
		{
			try
			{
				const auto& map = response[0]->get_map();

				if (const auto code = map.at(SECSTR("code"))->get_int(); code == 200)
					msg = map.at(SECSTR("message"))->get_string();
				else
					throw std::runtime_error(utility::format(SECSTR("failed to update motd [code {:d}]"), code));
			}
			catch (const std::exception& e)
			{
				logging::push(FOREGROUND_INTENSE_RED);
				logging::print(SECSTR("[critical] {}\n"), e.what());
				logging::pop();
				msg = SECSTR("failed to update motd.");
			}
		});*/

		const auto end = std::chrono::high_resolution_clock::now();

		logging::push(FOREGROUND_INTENSE_CYAN);
#ifdef _DEBUG
		logging::print(xorstr_("[debug] gameassemblybase {:#08x}\n"), reinterpret_cast<std::uintptr_t>(memory::game_assembly_handle));
		logging::print(xorstr_("[debug] unityplayerbase {:#08x}\n"), reinterpret_cast<std::uintptr_t>(memory::unity_player_handle));
#endif
		logging::add_log(SECSTR("[log] graphical client initialized!\n"));
		logging::add_log(SECSTR("[log] initialization took {:.2f}s\n"), std::chrono::duration<double, std::milli>(end - start).count() / 1000);
		logging::add_log(SECSTR("[log] void's default keybind is 'L'\n"));
		logging::pop();

		// VMProtectEnd();
	}
	catch (const std::exception& e)
	{
		logging::push(FOREGROUND_INTENSE_RED);
		logging::print(SECSTR("[critical] {}\n"), e.what());
		logging::pop();

#ifdef _DEBUG
        _RPT0(_CRT_ERROR, e.what());
#else
		memory::relink_module_to_peb(memory::void_handle);
		FreeLibraryAndExitThread(static_cast<HMODULE>(lp_parameter), EXIT_FAILURE);
#endif
	}

	return 1ul;
}

// @note: unused
DWORD send_release(LPVOID lp_parameter)
{
	while (!input_sys::is_key_released(config::get<int>(g_context.panic_key)))
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

	assembler::vrc_player_menu::restore();
	assembler::vrc_social_menu::restore();

	auto& detours_instance = detours::get();
	detours_instance.restore();
	auto& patches_instance = patches::get();
	patches_instance.restore();
	//helpers::restore_ab_patches();
	
	dx11_hook::restore();

	input_sys::restore();

	drawing::destroy();

	MH_Uninitialize();

	if (logging::ofs_file.is_open())
		logging::ofs_file.close();

	logging::detach();

	memory::relink_module_to_peb(memory::void_handle);
	FreeLibraryAndExitThread(static_cast<HMODULE>(lp_parameter), EXIT_SUCCESS);

	return 1ul;
}

BOOL APIENTRY DllMain(const HMODULE h_module, const DWORD fwd_reason, LPVOID lp_reserved)
{
	switch (fwd_reason)
	{
	case DLL_PROCESS_ATTACH:
		memory::void_handle = h_module;

#ifdef NDEBUG
		if (!memory::erase_headers(h_module))
			return FALSE;

		memory::unlink_module_from_peb(h_module);
#endif

		if (memory::get_module_base_handle(SECSTR("VRChat.exe")) == nullptr)
			return FALSE;

		if (const auto h_thread = CreateThread(nullptr, 0ull, entrypoint, h_module, 0ul, nullptr); h_thread != nullptr)
			CloseHandle(h_thread);

		return TRUE;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
	default: break;
	}
	return FALSE;
}
