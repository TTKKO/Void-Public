#include "dx11.hpp"

void dx11_hook::render_player()
{
	const auto draw = ImGui::GetBackgroundDrawList();
	const ImGuiIO& io = ImGui::GetIO();

	for (auto it = tabs::v_players.begin(); it != tabs::v_players.end(); ++it)
	{
		const auto apiuser = (*it)->get_api_user();

		if (!apiuser)
			continue;

		if (wsv_chars(apiuser->fields.id) == wsv_chars(assembler::vrc::core::api_user::get_current()->fields.id)) 
			continue;

		const auto player = (*it)->get_vrc_player_api();

		if (!player) 
			continue;

		if (config::get<bool>(g_context.dx11_esp))
		{
			std::uint32_t box;

			if (assembler::vrc::core::api_user::is_friends_with(apiuser->get_id()))
				box = IM_COL32(255, 255, 0.0f, 255);
			else
				box = IM_COL32(178, 66, 245, 255);

			const auto foot = player->get_bone_position(assembler::unity_engine::human_body_bones::left_foot);
			const auto head = player->get_bone_position(assembler::unity_engine::human_body_bones::head);

			if (!head.is_valid() || head.is_zero())
				continue;

			const auto w2_s_footpos = assembler::unity_engine::camera::get_main()->world_to_screen_point(foot);
			const auto w2_s_headpos = assembler::unity_engine::camera::get_main()->world_to_screen_point(head);

			const float h = w2_s_headpos.y - w2_s_footpos.y;
			const float w = h / 4.f;
			const float l = w2_s_footpos.x - w;
			const float r = w2_s_footpos.x + w;

			if (w2_s_footpos.z > 1.f)
			{
				const auto local_foot = assembler::vrc::sdk_base::vrc_player_api::get_current()->get_bone_position(assembler::unity_engine::human_body_bones::left_foot);

				ImGui::PushFont(byte_resources::verdana_small);
				draw->AddRect(ImVec2(l, io.DisplaySize.y - w2_s_headpos.y + h), ImVec2(r, io.DisplaySize.y - w2_s_footpos.y - h), box, 0.f, 0);
				draw->AddText(ImVec2(l, io.DisplaySize.y - w2_s_footpos.y - h - 20.f), IM_COL32(255, 255, 255, 255), apiuser->display_name().c_str(), nullptr);
				draw->AddText(ImVec2(l, io.DisplaySize.y - w2_s_headpos.y + h + 13.f), IM_COL32(255, 0, 0, 255), utility::format(xorstr_("dst: {:.1f}"), local_foot.dist_to(foot)).c_str(), nullptr);
				ImGui::PopFont();
			}
		}

		if (config::get<bool>(g_context.dx11_tracers)) 
		{
			const auto w2_s_chestpos = assembler::unity_engine::camera::get_main()->world_to_screen_point(player->get_bone_position(assembler::unity_engine::human_body_bones::chest));
			if (w2_s_chestpos.z > 1.f) 
			{
				const float h = w2_s_chestpos.y / 32.f;
				const float w = h / 4.f;
				const float l = w2_s_chestpos.x - w;

				draw->AddLine(ImVec2(io.DisplaySize.x / 2.f, io.DisplaySize.y / 2.f), ImVec2(l, io.DisplaySize.y - w2_s_chestpos.y), IM_COL32(178, 66, 245, 153), 2);
			}
		}
	}
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT dx11_hook::wnd_proc(const HWND h_wnd, const UINT u_msg, const WPARAM w_param, const LPARAM l_param)
{
	input_sys::process(u_msg, w_param, l_param);

#pragma region process_keybinds
	if (input_sys::is_key_released(config::get<int>(g_context.esp_key)))
		config::get<bool>(g_context.esp) = !config::get<bool>(g_context.esp);

	if (input_sys::is_key_released(config::get<int>(g_context.thirdperson_key)))
		helpers::camera::get().toggle();

	if (input_sys::is_key_released(config::get<int>(g_context.menu_key)) && !menu_window::is_typing)
		menu_window::mainmenu_opened = !menu_window::mainmenu_opened;

	if (input_sys::is_key_released(config::get<int>(g_context.flight_key)))
	{
		config::get<bool>(g_context.flight) = !config::get<bool>(g_context.flight);
		misc::toggle_flight(config::get<bool>(g_context.flight));
	}

	if (input_sys::is_key_released(config::get<int>(g_context.deserialize_key)))
	{
		const auto ptr = &config::get<bool>(g_context.serialize);
		*ptr = !*ptr;
		misc::handle_avatar_clone(*ptr);
	}

	if (input_sys::is_key_down(config::get<int>(g_context.playerlist_key)))
	{
		if (!tabs::playerlist_active && !menu_window::mainmenu_opened)
			tabs::playerlist_active = true;
		if (menu_window::mainmenu_opened && tabs::playerlist_active)
			tabs::playerlist_active = false;
	}
	else if (tabs::playerlist_active)
		tabs::playerlist_active = false;
#pragma endregion
		
	if (drawing::initialized && menu_window::mainmenu_opened)
	{
		ImGui_ImplWin32_WndProcHandler(h_wnd, u_msg, w_param, l_param);
		return 1L;
	}

	if (drawing::initialized && tabs::playerlist_active)
	{
		ImGui_ImplWin32_WndProcHandler(h_wnd, u_msg, w_param, l_param);
		return CallWindowProcW(input_sys::p_old_wnd_proc, h_wnd, u_msg, w_param, l_param);
	}

	return CallWindowProcW(input_sys::p_old_wnd_proc, h_wnd, u_msg, w_param, l_param);
}

HRESULT dx11_hook::hk_present(IDXGISwapChain* p_swap_chain, const UINT sync_interval, const UINT flags)
{
	if (!initialize_present)
	{
		if (SUCCEEDED(p_swap_chain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<void**>(&p_device))))
		{
			try
			{
				p_device->GetImmediateContext(&p_context);

				if (!input_sys::setup(p_swap_chain))
					throw std::runtime_error(xorstr_("failed to initialize input system"));

				ID3D11Texture2D* p_back_buffer = nullptr;

				if (FAILED(p_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&p_back_buffer))))
					throw std::runtime_error(xorstr_("directx11 -> failed to get backbuffer"));

				if (FAILED(p_device->CreateRenderTargetView(p_back_buffer, nullptr, &main_render_target_view)))
					throw std::runtime_error(xorstr_("directx11 -> failed to create targetview"));

				p_back_buffer->Release();

				if (!drawing::setup(p_device, p_context, input_sys::h_window))
					throw std::runtime_error(xorstr_("directx11 -> failed to setup void drawing sdk"));

				initialize_present = true;
			}
			catch (const std::exception& e)
			{
				logging::push(FOREGROUND_INTENSE_RED);
				logging::print(xorstr_("[critical] {}\n"), e.what());
				logging::pop();
				return o_present(p_swap_chain, sync_interval, flags);
			}
		}
		else
			return o_present(p_swap_chain, sync_interval, flags);
	}

	SEH_START
		if (!current_thread)
			current_thread = thread_attach(assembler::il2cpp::current_domain());

		ImGui::GetIO().MouseDrawCursor = menu_window::mainmenu_opened;

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		if (g_context.instantiated) 
		{
			tabs::v_players = array_to_vector<assembler::vrc::player*>(assembler::vrc::player_manager::get_players());

			if (config::get<bool>(g_context.dx11_esp) || config::get<bool>(g_context.dx11_tracers))
				render_player();
		}
		else if (tabs::v_players.size() > 0)
			tabs::v_players.clear();

		//ImGui::GetIO().MouseDrawCursor = ShowMenu;
		hue += 0.0008f;

		menu_window::main_window(ImColor::HSV(hue, 0.6f, 1.f));

		if (hue >= 1.f) 
			hue = 0.f;

		ImGui::EndFrame();
		ImGui::Render();
		p_context->OMSetRenderTargets(1, &main_render_target_view, nullptr);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	SEH_END
	return o_present(p_swap_chain, sync_interval, flags);
}

//@credits: https://docs.microsoft.com/en-gb/windows/win32/direct3ddxgi/d3d10-graphics-programming-guide-dxgi?redirectedfrom=MSDN#handling-window-resizing
HRESULT dx11_hook::hk_resizebuffers(IDXGISwapChain* p_swap_chain, const UINT buffer_count, const UINT width, const UINT height, const DXGI_FORMAT new_format, const UINT swap_chain_flags)
{
	if (main_render_target_view)
	{
		p_context->OMSetRenderTargets(0, nullptr, nullptr);
		main_render_target_view->Release();
	}

	const HRESULT hr = o_resizebuffers(p_swap_chain, buffer_count, width, height, new_format, swap_chain_flags);

	try
	{
		if (!initialize_present)
			throw std::runtime_error(xorstr_("directx11 -> attempted to resize buffers without hooks being initialized"));

		ID3D11Texture2D* p_buffer = nullptr;

		if (FAILED(p_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&p_buffer))))
			throw std::runtime_error(xorstr_("directx11 -> failed to get backbuffer"));

		if (FAILED(p_device->CreateRenderTargetView(p_buffer, nullptr, &main_render_target_view)))
			throw std::runtime_error(xorstr_("directx11 -> failed to create new targetview"));

		p_buffer->Release();

		p_context->OMSetRenderTargets(1, &main_render_target_view, nullptr);

		const D3D11_VIEWPORT vp{ 0.f, 0.f, static_cast<float>(width), static_cast<float>(height), 0.f, 1.f };
		p_context->RSSetViewports(1, &vp);
		return hr;
	}
	catch (const std::exception& e)
	{
		logging::push(FOREGROUND_INTENSE_RED);
		logging::print(xorstr_("[critical] {}\n"), e.what());
		logging::pop();
		return hr;
	}
}

kiero::status::Enum dx11_hook::init()
{
	try
	{
		// VMProtectBeginMutation("DX11Hook Init");

		if (const auto res = kiero::init(kiero::render_type::Enum::d3d11); res != kiero::status::Enum::success)
			return res;

		if (const auto res = kiero::bind(static_cast<std::int32_t>(vtable::present), reinterpret_cast<void**>(&o_present), hk_present); res != kiero::status::Enum::success)
			return res;

		if (const auto res = kiero::bind(static_cast<std::int32_t>(vtable::resize_buffers), reinterpret_cast<void**>(&o_resizebuffers), hk_resizebuffers); res != kiero::status::Enum::success)
			return res;

		// VMProtectEnd();

		return kiero::status::Enum::success;
	}
	catch (const std::exception& e)
	{
		logging::push(FOREGROUND_INTENSE_RED);
		logging::print(xorstr_("[critical] {}\n"), e.what());
		logging::pop();
		return kiero::status::unknown_error;
	}
}

void dx11_hook::restore()
{
	kiero::unbind(8);
	kiero::unbind(13);
	kiero::shutdown();
}
