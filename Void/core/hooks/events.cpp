#include "events.hpp"
#include "../assembler/unityengine/ray.hpp"

#pragma region detour_system
void detours::setup()
{
	//m.name = xorstr_("TriggerEvent");
	//m.enabled = true;
	//m.genuine_f = memory::get_method(ANTIEVENT);
	//m.detour_f = &triggerevent;
	//detours_.push_back(m);

	detours_.emplace_back(
		SECSTR("Anti-Portal"),
		true,
		memory::get_method<void*>(ANTI_PORTAL),
		&hk_ontriggerenter
	);

	detours_.emplace_back(
		SECSTR("Fake Ping"),
		true,
		memory::get_method<void*>(FAKE_PING),
		&hk_getroundtriptime
	);

	detours_.emplace_back(
		SECSTR("Update"),
		true,
		memory::get_method<void*>(VRCHANDGRASPER),
		&hk_onupdate
	);

	detours_.emplace_back(
		SECSTR("OnEventPatch"),
		true,
		memory::get_method<void*>(ONEVENTPATCH),
		&hk_onevent
	);

	detours_.emplace_back(
		SECSTR("SetFixedDeltaTimeDetour"),
		true,
		assembler::il2cpp::resolve_icall(SECSTR("UnityEngine.Time::set_fixedDeltaTime(System.Single)")),
		&hk_setfixeddeltatime
	);

	detours_.emplace_back(
		SECSTR("OnAvatarDownload"),
		true,
		memory::get_method<void*>(ONAVATARDOWNLOAD),
		&hk_onavatardownload
	);

	detours_.emplace_back(
		SECSTR("HWIDSpoof"),
		true,
		assembler::il2cpp::resolve_icall(SECSTR("UnityEngine.SystemInfo::GetDeviceUniqueIdentifier()")),
		&hk_getdeviceuniqueidentifier
	);

	detours_.emplace_back(
		SECSTR("FPS Spoof"),
		true,
		assembler::il2cpp::resolve_icall(SECSTR("UnityEngine.Time::get_smoothDeltaTime()")),
		&hk_getsmoothdeltatime
	);

	detours_.emplace_back(
		SECSTR("SwitchAvatarRPC"),
		true,
		memory::get_method<void*>(SWITCHAVATARRPC),
		&hk_switchavatarrpc
	);

	detours_.emplace_back(
		SECSTR("OnPlayerJoined"),
		true,
		memory::get_method<void*>(PLAYERJOINED),
		&hk_onplayerjoin
	);

	detours_.emplace_back(
		SECSTR("OnPlayerLeft"),
		true,
		memory::get_method<void*>(PLAYERLEFT),
		&hk_onplayerleft
	);

	detours_.emplace_back(
		SECSTR("OnLeftRoom"),
		true,
		memory::get_method<void*>(ONLEFTROOM),
		&hk_onleftroom
	);

	detours_.emplace_back(
		SECSTR("SendPutRequest"),
		true,
		memory::get_method<void*>(OFFLINE_MODE),
		&hk_sendputrequest
	);

	detours_.emplace_back(
		SECSTR("VideoAddURLDetour"),
		true,
		memory::get_method<void*>(VIDEOPLAYERURL),
		&hk_videoaddurl
	);

	detours_.emplace_back(
		SECSTR("SDK3LoadURL2"),
		true,
		assembler::il2cpp::resolve_icall(SECSTR("UnityEngine.Video.VideoPlayer::set_url(System.String)")),
		&hk_loadurl
	);

	detours_.emplace_back(
		SECSTR("ReceiveAudio"),
		true,
		memory::get_method<void*>(RECEIVEAUDIO),
		&hk_processaudio
	);

	detours_.emplace_back(
		SECSTR("CustomPlates"),
		true,
		memory::get_method<void*>(VRCPLAYERCUSTOMPLATES),
		&hk_playerupdate
	);

	detours_.emplace_back(
		SECSTR("RaiseEvent"),
		true,
		memory::get_method<void*>(ONOPRAISEEVENT),
		&hk_opraiseevent
	);

	detours_.emplace_back(
		SECSTR("OnPhotonPlayerJoined"),
		true,
		memory::get_method<void*>(PHOTONPLAYERJOIN),
		&hk_onphotonplayerjoined
	);

	detours_.emplace_back(
		SECSTR("OnPhotonPlayerLeft"),
		true,
		memory::get_method<void*>(PHOTONPLAYERLEFT),
		&hk_onphotonplayerleft
	);

	//detours_.emplace_back(
	//	xorstr_("PageAvatarAwake"),
	//	true,
	//	memory::get_method<void*>(PAGEAVATARAWAKE),
	//	&hk_pageavatar_awake
	//);

	detours_.emplace_back(
		SECSTR("OnPageChange"),
		true,
		memory::get_method<void*>(VRCUIPAGEONCHANGE),
		&hk_vrcuipage_awake
	);

	detours_.emplace_back(
		SECSTR("UdonBehaviour::RunProgram(string)"),
		true,
		memory::get_method<void*>(UDONRUNPROGRAMSTR),
		&hk_udonbehaviour_runprogramstr
	);

	detours_.emplace_back(
		SECSTR("Udon::UdonSyncRunProgramAsRPC"),
		true,
		memory::get_method<void*>(UDONSYNCRUNPROGRAMASRPC),
		&hk_udonsync_runprogramasrpc
	);

	// -> customscenes::ctor
	// -> assetbundle::load::world

	detours_.emplace_back(
		SECSTR("CustomScenes::ctor"),
		true,
		memory::get_method<void*>(CUSTOMSCENESCTOR),
		&hk_customscenes_ctor
	);

	detours_.emplace_back(
		SECSTR("AssetBundle::LoadWorld"),
		true,
		memory::get_method<void*>(ASSETBUNDLELOADWORLD),
		&hk_assetbundle_loadworld
	);

	detours_.emplace_back(
		SECSTR("UIManagerImpl::OnMenuClose"),
		true,
		memory::get_method<void*>(UIMANAGERIMPL_ONMENUCLOSE),
		&hk_onmenuclose
	);

	detours_.emplace_back(
		SECSTR("UIManagerImpl::OnMenuOpen"),
		true,
		memory::get_method<void*>(UIMANAGERIMPL_ONMENUOPEN),
		&hk_onmenuopen
	);

	detours_.emplace_back(
		SECSTR("VRCUiPage::OnFlowPage"),
		true,
		memory::get_method<void*>(VRCUIPAGE_ONFLOWPAGE),
		&hk_onflowpage
	);

	detours_.emplace_back(
		SECSTR("VRCUIManager::Place"),
		true,
		memory::get_method<void*>(VRCUIMANAGER_PLACE),
		&hk_onvrcuimanager_place
	);
}

bool detours::init()
{
	for (auto& mode : detours_)
	{
		if (!mode.enabled)
		{
			logging::push(FOREGROUND_INTENSE_YELLOW);
			logging::print(xorstr_("[warn] {} is disabled.\n"), mode.name);
			logging::pop();

			continue;
		}

		try
		{
			if (!mode.apply_hook())
				return false;
		}
		catch (const std::runtime_error& e)
		{
			logging::push(FOREGROUND_INTENSE_RED);
			logging::print(xorstr_("[critical] {}\n"), e.what());
			logging::print(xorstr_("[critical] this is likely caused by running an incompatible version of vrchat.\n"));
			logging::pop();

			return false;
		}
	}

	logging::push(FOREGROUND_INTENSE_CYAN);
	logging::print(xorstr_("[log] finished loading {:d} detours.\n"), detours_.size());
	logging::pop();

	return true;
}

void detours::restore()
{
	for (auto& [name, enabled, genuine_f, detour_f, detour] : detours_)
	{
		if (!enabled)
			continue;

		detour.restore();
	}
}

void detours::setup_ratelimter()
{
	event_map_.set_current_time();

	for (const auto& [rpc, pair] : event_map::rate_limit_values)
	{
		event_map_.only_allow_per_seccond(xorstr_("G_") + rpc, pair.first);
		event_map_.only_allow_per_seccond(rpc, pair.second);
	}
}

bool detours::mode::operator()(const mode& m) const
{
	return m.name == name;
}

bool detours::mode::apply_hook()
{
	if (!detour.create(genuine_f, detour_f))
		return false;

	return true;
}

detours::mode& detours::fetch_hook(const std::string& setting_name)
{
	if (const auto it = std::ranges::find_if(detours_, mode(setting_name)); it != detours_.end()) return *it;
	throw std::runtime_error(utility::format(SECSTR("failed to find detour [{}]"), setting_name));
}

void detours::clean()
{
	SEH_START
		helpers::portable_mirror::get().cleanup();

		event_map_.cleanup();

		nameplate_manager::cleanup(false);

		{
			std::lock_guard guard(sniffer_window::sniffer_mutex);
			if (sniffer_window::logging_players.contains(0))
			{
				sniffer_window::logging_players.clear();
				sniffer_window::logging_players.reserve(2);
				sniffer_window::logging_players.insert(-1);
				sniffer_window::logging_players.insert(0);
			}
			else
				sniffer_window::logging_players.clear();
		}

		{
			std::lock_guard guard(g_mutex_);
			invisible_users_.clear();
		}

		{
			std::lock_guard guard(blocked_users_mutex_);
			blocked_users_.clear();
		}
	SEH_END
}

#pragma endregion

#pragma region events
#pragma region on_updates
void detours::hk_playerupdate(assembler::vrc_player* _this, const float f, const float f_2)
{
	static auto& instance = get();
	static auto genuine_f = instance.fetch_hook(SECSTR("CustomPlates")).detour.get_original<decltype(&hk_playerupdate)>();
	genuine_f(_this, f, f_2);

	try
	{
		if (const auto nameplate_mngr = nameplate_manager(_this); nameplate_mngr.is_ready())
		{
			if (config::get<bool>(g_context.custom_plates))
			{
				nameplate_mngr.render_colors();
				if (!nameplate_mngr.render_tags())
					throw std::runtime_error(utility::format(xorstr_("failed to render void tags on \"{}\""), _this->get_player()->get_api_user()->display_name()));
			}

			if (config::get<bool>(g_context.nameplate_info))
				if (!nameplate_mngr.render_info())
					throw std::runtime_error(utility::format(xorstr_("failed to render nameplate info on \"{}\""), _this->get_player()->get_api_user()->display_name()));

			nameplate_mngr.overrender();

			if (config::get<bool>(g_context.anti_block))
			{
				std::lock_guard guard(instance.blocked_users_mutex_);
				nameplate_mngr.render_blocked(instance.blocked_users_.contains(_this->get_player()->get_photon_id()));
			}
		}
	}
	catch (const std::exception& e)
	{
		logging::push(FOREGROUND_INTENSE_RED);
		logging::print(xorstr_("[critical] {}\n"), e.what());
		logging::pop();
	}

	const auto select_region = _this->get_transform()->find(xorstr_("SelectRegion"));

	if (!select_region)
		return;

	const auto selectcomp = reinterpret_cast<assembler::unity_engine::renderer*>(select_region->get_game_object()->get_component(xorstr_("MeshRenderer")));
	const auto hfx = assembler::highlights_fx::instance();

	if (!hfx || !selectcomp)
		return;

	hfx->enable_outline(selectcomp, config::get<bool>(g_context.esp));
	hfx->get_material()->set_color(xorstr_("_HighlightColor"), sdk::color(0.701f, 0.258f, 0.96f, 1.f));
}

void detours::hk_onupdate(assembler::il2cpp::il2cpp_object* _this)
{
	static auto& instance = get();
	//static auto& cl_instance = connection_listener::get();
	static auto genuine_f = instance.fetch_hook(SECSTR("Update")).detour.get_original<decltype(&hk_onupdate)>();

	// @note: vrchandgrasper has two instances, all this could would run 2x/frame if not for this block
	instance.should_skip_update_ = !instance.should_skip_update_;
	if (instance.should_skip_update_)
		return genuine_f(_this);

	if (!instance.initialized_menu_)
	{
		// @note: fetch all void users
		// VMProtectBeginUltra("OnUpdate Userdata");

		//instance.cached_hwid_ = connection_listener::get_hwid();
		//cl_instance.refresh_activity(instance.cached_hwid_, assembler::vrc::core::api_user::get_current()->get_id(), config::get<bool>(g_context.display_online));
		//cl_instance.fetch_plates(instance.cached_hwid_, nameplate_manager::get_userplates(), nameplate_manager::get_mutexes());

		// VMProtectEnd();

		// @note: initialize menu stuff
		try
		{
			// VMProtectBeginUltra("OnUpdate Initialization");

			if (!assembler::vrc_quick_menu::setup_buttons())
				throw std::runtime_error(SECSTR("failed to initialize vr menu. couldn't find components required."));

			if (!assembler::vrc_social_menu::setup_buttons())
				throw std::runtime_error(SECSTR("failed to initialize social menu. couldn't find components required."));

			if (!assembler::vrc_player_menu::setup_buttons())
				throw std::runtime_error(SECSTR("failed to initilize vr action menu. couldn't find components required."));

			if (config::get<bool>(g_context.qm_debug_log))
				if (!assembler::vrc_quick_menu::init_vr_debug())
					throw std::runtime_error(SECSTR("failed to initialize vr debug menu. couldn't find components required"));

			if (!helpers::camera::get().initialize())
				throw std::runtime_error(SECSTR("failed to initialize camera modules. couldn't find components required"));

			// VMProtectEnd();

			instance.initialized_menu_ = true;
		}
		catch (const std::exception& e)
		{
			logging::push(FOREGROUND_INTENSE_RED);
			logging::print(SECSTR("[critical] {}\n"), e.what());
			logging::pop();
			instance.initialized_menu_ = true;
		}
	}

	SEH_START
		// @note: check if avatar needs to be changed
		if (!g_context.changing_avatar.empty())
		{
			misc::change_avatar(g_context.changing_avatar);
			g_context.changing_avatar = {};
		}

		// @note: check if room neds to be changed
		if (!g_context.room_id.empty())
		{
			assembler::vrc::sdk_base::networking::go_to_room(g_context.room_id);
			g_context.room_id = {};
		}

		helpers::camera::get().handle();

		// @note: listen for lovense controller binds
		if (config::get<bool>(g_context.lovense_binds) && assembler::unity_engine::xrdevice::get_is_present())
		{
			if (assembler::unity_engine::input::get_key(assembler::unity_engine::key_code::JoystickButton15))
			{
				const auto progression = assembler::unity_engine::input::get_axis(xorstr_("Oculus_CrossPlatform_SecondaryThumbstickVertical"));

				if (instance.right_trigger_ready_)
				{
					if (progression > 0.93f)
					{
						instance.right_trigger_ready_ = false;
						lovense_modules::get().increase_vibration();
					}

					else if (progression < -0.93f)
					{
						instance.right_trigger_ready_ = false;
						lovense_modules::get().decrease_vibration();
					}
				}

				else if (progression <= 0.1f && progression >= -0.1f)
					instance.right_trigger_ready_ = true;
			}

			else if (!instance.right_trigger_ready_)
				instance.right_trigger_ready_ = true;
		}

		// @note: listen for deserialize binds
		if (config::get<bool>(g_context.deserialize_bind) && assembler::unity_engine::xrdevice::get_is_present())
		{
			if (!instance.deserialize_safety_check_)
			{
				if (assembler::unity_engine::input::get_axis(xorstr_("Oculus_CrossPlatform_SecondaryIndexTrigger")) > 0.5f && assembler::unity_engine::input::get_axis(xorstr_("Oculus_CrossPlatform_PrimaryIndexTrigger")) > 0.5f)
				{
					instance.deserialize_safety_check_ = true;
					config::get<bool>(g_context.serialize) = !config::get<bool>(g_context.serialize);
					misc::handle_avatar_clone(config::get<bool>(g_context.serialize));
				}
			}
			else if (assembler::unity_engine::input::get_axis(xorstr_("Oculus_CrossPlatform_SecondaryIndexTrigger")) <= 0.1f && assembler::unity_engine::input::get_axis(xorstr_("Oculus_CrossPlatform_PrimaryIndexTrigger")) <= 0.1f)
			{
				instance.deserialize_safety_check_ = false;
			}
		}

		// @note: fuck you
		if (instance.is_quickmenu_open_)
		{
			const auto is_vr = assembler::unity_engine::xrdevice::get_is_present();

			if (instance.quickmenu_safety_check_)
			{
				if (!is_vr && !input_sys::is_key_down(VK_ESCAPE))
					instance.quickmenu_safety_check_ = false;

				else if (is_vr && !assembler::unity_engine::input::get_key_down(assembler::unity_engine::key_code::Joystick1Button0) && !assembler::unity_engine::input::get_key_down(assembler::unity_engine::key_code::Joystick2Button0) && !assembler::unity_engine::input::get_key_down(assembler::unity_engine::key_code::JoystickButton0) && !assembler::unity_engine::input::get_key_down(assembler::unity_engine::key_code::JoystickButton2) && !assembler::unity_engine::input::get_key_down(assembler::unity_engine::key_code::Joystick2Button2))
					instance.quickmenu_safety_check_ = false;
			}

			else if (!is_vr && input_sys::is_key_down(VK_ESCAPE))
			{
				instance.is_quickmenu_open_ = false;
				hk_onmenuclose(assembler::ui_manager_impl::instance(), false);
			}

			else if (is_vr && (assembler::unity_engine::input::get_key_down(assembler::unity_engine::key_code::Joystick1Button0) || assembler::unity_engine::input::get_key_down(assembler::unity_engine::key_code::Joystick2Button0) || assembler::unity_engine::input::get_key_down(assembler::unity_engine::key_code::JoystickButton0) || (assembler::unity_engine::input::get_key_down(assembler::unity_engine::key_code::JoystickButton2) || assembler::unity_engine::input::get_key_down(assembler::unity_engine::key_code::Joystick2Button2))))
			{
				instance.is_quickmenu_open_ = false;
			}
		}

		// @note: listen for rotate avatar binds
		if (config::get<bool>(g_context.rotate_avatar))
		{
			if (input_sys::is_key_down(0x31)) // @note: 1
			{
				if (instance.avatar_rotation_z_ >= 360.f)
					instance.avatar_rotation_z_ = 0.f;

				const auto vrcplayer = assembler::vrc_player::get_current()->get_transform();
				vrcplayer->find(xorstr_("ForwardDirection/Avatar"))->set_rotation(sdk::quaternion::from_eulerangles(sdk::vector(instance.avatar_rotation_z_, 0, instance.avatar_rotation_z_)));
				instance.avatar_rotation_z_ = instance.avatar_rotation_z_ + 2.f;
			}

			if (input_sys::is_key_down(0x33)) // @note: 3
			{
				if (instance.avatar_rotation_z_ <= 0.f)
					instance.avatar_rotation_z_ = 360.f;

				const auto vrcplayer = assembler::vrc_player::get_current()->get_transform();
				vrcplayer->find(xorstr_("ForwardDirection/Avatar"))->set_rotation(sdk::quaternion::from_eulerangles(sdk::vector(instance.avatar_rotation_z_, 0, instance.avatar_rotation_z_)));
				instance.avatar_rotation_z_ = instance.avatar_rotation_z_ - 2.f;
			}
		}

		// @note: listen for flight binds
		if (config::get<bool>(g_context.flight))
		{
			const auto flight_speed = config::get<float>(g_context.flight_speed);
			const auto vrcplayer = assembler::vrc_player::get_current()->get_transform();
			auto vrcplayer_pos = vrcplayer->get_position();

			vrcplayer_pos += vrcplayer->get_forward() * (assembler::unity_engine::time::get_delta_time() * assembler::unity_engine::input::get_axis(xorstr_("Vertical")) * (flight_speed * 2));
			vrcplayer_pos += vrcplayer->get_right() * (assembler::unity_engine::time::get_delta_time() * assembler::unity_engine::input::get_axis(xorstr_("Horizontal")) * (flight_speed * 2));

			if (assembler::unity_engine::xrdevice::get_is_present())
				vrcplayer_pos.y += assembler::unity_engine::time::get_delta_time() * assembler::unity_engine::input::get_axis(xorstr_("Oculus_CrossPlatform_SecondaryThumbstickVertical")) * (flight_speed * 2);
			else
			{
				if (input_sys::is_key_down(0x51)) // @note: Q
					vrcplayer_pos.y -= assembler::unity_engine::time::get_delta_time() * (flight_speed * 2);
				if (input_sys::is_key_down(0x45)) // @note: E
					vrcplayer_pos.y += assembler::unity_engine::time::get_delta_time() * (flight_speed * 2);
			}
			vrcplayer->set_position(vrcplayer_pos);
		}

		if (config::get<bool>(g_context.click_teleport) && input_sys::is_key_released(VK_LBUTTON) && input_sys::is_key_down(VK_CONTROL))
		{
			const auto t_camera = assembler::unity_engine::camera::get_main()->get_transform();
			const auto ray = assembler::unity_engine::ray::ctor(t_camera->get_position(), t_camera->get_forward());
			
			assembler::unity_engine::raycast_hit hit_info{};
			if (assembler::unity_engine::ray::raycast(ray, &hit_info))
				assembler::vrc_player::get_current()->get_transform()->set_position(sdk::vector(hit_info.point));
		}

		// @note: update udon stuff
		if (config::get<bool>(g_context.anti_stream) && !config::get<bool>(g_context.udon_namespoof))
		{
			if (const auto user = assembler::vrc::core::api_user::get_current(); wsv_chars(user->fields.display_name) != xorstr_(L"a good streamer!"))
				user->fields.display_name = assembler::il2cpp::string_new(xorstr_(L"a good streamer!"));
		}

		else if (config::get<bool>(g_context.udon_namespoof))
		{
			if (config::get<bool>(g_context.udon_namespoof_patreon))
			{
				if (const auto apiworld = assembler::room_manager::get_class()->static_fields->world)
				{
					const auto name = wsv_chars(apiworld->fields.author_name);
					if (const auto user = assembler::vrc::core::api_user::get_current(); wsv_chars(user->fields.display_name) != name)
						user->fields.display_name = assembler::il2cpp::string_new(name);
				}
			}
			else if (const auto user = assembler::vrc::core::api_user::get_current(); s_chars(user->fields.display_name) != config::get<std::string>(g_context.udon_namespoof_name))
				user->fields.display_name = assembler::il2cpp::string_new(config::get<std::string>(g_context.udon_namespoof_name));
		}

		// @note: player attach
		if (g_context.player_attach)
		{
			if (!g_context.player_attach_id)
			{
				config::get<bool>(g_context.flight) = false;
				misc::toggle_flight(false);
				g_context.player_attach = false;
			}
			else
			{
				const auto current_player = assembler::vrc_player::get_current();

				if (!config::get<bool>(g_context.flight))
				{
					config::get<bool>(g_context.flight) = true;
					misc::toggle_flight(true);
				}

				const auto bone_pos = assembler::vrc::player_manager::get_player(g_context.player_attach_id)->get_vrc_player_api()->get_bone_position(assembler::unity_engine::human_body_bones::head);
				current_player->get_transform()->set_position(sdk::vector(bone_pos.x, bone_pos.y + 0.2f, bone_pos.z));

				if (const auto is_vr = assembler::unity_engine::xrdevice::get_is_present(); !is_vr && (input_sys::is_key_down(0x57) || input_sys::is_key_down(0x41) || input_sys::is_key_down(0x53) || input_sys::is_key_down(0x44)))
				{
					config::get<bool>(g_context.flight) = false;
					misc::toggle_flight(false);
					g_context.player_attach_id = NULL;
					g_context.player_attach = false;
				}

				else if (is_vr && (assembler::unity_engine::input::get_axis(xorstr_("Vertical")) != 0.f || assembler::unity_engine::input::get_axis(xorstr_("Horizontal")) != 0.f))
				{
					config::get<bool>(g_context.flight) = false;
					misc::toggle_flight(false);
					g_context.player_attach_id = NULL;
					g_context.player_attach = false;
				}
			}
		}

		instance.update_delay_ -= assembler::unity_engine::time::get_delta_time();

		// @note: send event 1 ear rape
		if (config::get<bool>(g_context.exploit_event_1) && instance.pn_.photon_network_ptr != nullptr)
		{
			const auto src = assembler::buffer::from_base64_string(xorstr_("BQAAAP51Dcw7CEgAeL1iJ2Bkj3KRCONbQGclHWF0qJ8JbM6WARDYeJ25oH2Gb+gA7mZ4aEbkznWVce9LjcNa5uMef1QpNRjwkbVYM3VVE3mFHbpLPAhDAHi//50nTm569Waiu/yxAamDw0GX8pimEBAILbZJthSkvj3qaSXeJcSOQKdcJe57KBn1tBx8CUJz1s09JOJzP+nHsmM9CDsAeL1w7SDWm09Uc/WynowuxSIh5GhyIxo4rvjOpPT9KDQIlGz2DBcPQVJByj+Hhh120NFh4Mn7OgcKsUo="));
			assembler::buffer::block_copy(assembler::buffer::get_bytes(assembler::vrc::player::get_current()->get_photon_id()), 0, src, 0, 4);
			assembler::buffer::block_copy(assembler::buffer::get_bytes(assembler::vrc::sdk_base::networking::get_server_time_in_milliseconds()), 0, src, 4, 4);
			hk_opraiseevent(instance.pn_.photon_network_ptr, 1u, src, nullptr, instance.pn_.send_options);
		}

		// @note: delay that fires every ~3 seconds
		if (instance.update_delay_ < 0.f)
		{
			instance.update_delay_ = 1.5f;

			try
			{
				// @note: update playerlist
				if (config::get<bool>(g_context.player_list_toggle))
					if (!assembler::vrc_quick_menu::player_list())
						throw std::runtime_error(xorstr_("failed to initilize vr player list. couldn't find components required."));

				// @note: check for portals
				if (config::get<bool>(g_context.prevent_portals))
					if (!misc::destroy_portals())
						throw std::runtime_error(xorstr_("failed to locate portal internal."));

				// @note: update discordrpc
				if (config::get<bool>(g_context.discord_rpc_toggle))
					if (!g_context.g_discord->update()) 
						throw std::runtime_error(xorstr_("failed to update discordrpc."));

				// @note: send an emoji
				if (config::get<bool>(g_context.emoji_spam) && config::get<int>(g_context.emoji_to_spam) - 1 != -1)
					assembler::vrc_player::get_current()->spawn_emoji(static_cast<assembler::emojis>(config::get<int>(g_context.emoji_to_spam) - 1));

				//if (cl_instance.should_close)
				//	cl_instance.induce_crash(xorstr_("failed validity check sadge"));
			}
			catch (const std::exception& e)
			{
				logging::push(FOREGROUND_INTENSE_RED);
				logging::print(xorstr_("[critical] {}\n"), e.what());
				logging::pop();
			}
		}

	SEH_END

	genuine_f(_this);
}
#pragma endregion

#pragma region external_source_processing
void* detours::hk_processaudio(void* _this, assembler::il2cpp::il2cpp_object* a1, assembler::il2cpp::il2cpp_array_wrapper<std::uint8_t>* buffer, const int length)
{
	static auto genuine_f = get().fetch_hook(SECSTR("ReceiveAudio")).detour.get_original<decltype(&hk_processaudio)>();
	if (!config::get<bool>(g_context.anti_audio_crash))
		return genuine_f(_this, a1, buffer, length);

	// @note: leave some room
	constexpr auto high = std::numeric_limits<std::int32_t>::max() - 4096;
	constexpr auto low = std::numeric_limits<std::int32_t>::min() + 4096;

	if (const std::int32_t convert_bytes = assembler::vrc::udon::serialization::odin_serializer::proper_bit_converter::to_int32(buffer, 6); convert_bytes > high || convert_bytes == NULL || convert_bytes < low)
		return nullptr;

	return genuine_f(_this, a1, buffer, length);
}

void detours::hk_videoaddurl(void* _this, assembler::il2cpp::il2cpp_string* url)
{
	static auto genuine_f = get().fetch_hook(SECSTR("VideoAddURLDetour")).detour.get_original<decltype(&hk_videoaddurl)>();

	if (!config::get<bool>(g_context.anti_video_exploit))
		return genuine_f(_this, url);

	if (const auto c_url = wsv_chars(url); c_url.contains(xorstr_(L"youtube.com")) || c_url.contains(xorstr_(L"googlevideo.com")) || c_url.contains(xorstr_(L"youtu.be")) || c_url.contains(xorstr_(L"twitch.tv")))
		return genuine_f(_this, url);
}

void detours::hk_loadurl(void* _this, assembler::il2cpp::il2cpp_string* vrcurl)
{
	static auto genuine_f = get().fetch_hook(SECSTR("SDK3LoadURL2")).detour.get_original<decltype(&hk_loadurl)>();

	if (!config::get<bool>(g_context.anti_video_exploit))
		return genuine_f(_this, vrcurl);

	if (const auto c_url = wsv_chars(vrcurl); c_url.contains(xorstr_(L"youtube.com")) || c_url.contains(xorstr_(L"googlevideo.com")) || c_url.contains(xorstr_(L"youtu.be")) || c_url.contains(xorstr_(L"twitch.tv")))
		return genuine_f(_this, vrcurl);
}

void detours::hk_ontriggerenter(assembler::il2cpp::il2cpp_object* _this, assembler::unity_engine::collider* collider)
{
	static auto genuine_f = get().fetch_hook(SECSTR("Anti-Portal")).detour.get_original<decltype(&hk_ontriggerenter)>();

	if (config::get<bool>(g_context.anti_portal))
	{
		collider = nullptr;

		ingame_logging::get().log(xorstr_("[<color=#a75cf6>notice</color>]: portal detected, removing collider"));
		logging::push(FOREGROUND_INTENSE_WHITE);
		logging::add_log(xorstr_("[notice] portal detected, removing collider\n"));
		logging::pop();
	}

	return genuine_f(_this, collider);
}
#pragma endregion

#pragma region spoofing
void detours::hk_setfixeddeltatime(const float value)
{
	static auto genuine_f = get().fetch_hook(SECSTR("SetFixedDeltaTimeDetour")).detour.get_original<decltype(&hk_setfixeddeltatime)>();

	if (!config::get<bool>(g_context.fps_target))
		return genuine_f(value);

	return genuine_f(static_cast<float>(1.0 / config::get<int>(g_context.fps_target_i)));
}

float detours::hk_getsmoothdeltatime()
{
	static auto genuine_f = get().fetch_hook(SECSTR("FPS Spoof")).detour.get_original<decltype(&hk_getsmoothdeltatime)>();

	if (!config::get<bool>(g_context.fake_fps))
		return genuine_f();

	const auto& range = config::get<int>(g_context.fake_fps_range);
	const auto& value = config::get<int>(g_context.fake_fps_i);

	if (range == 0)
		return 1 / static_cast<float>(value);

	std::random_device rd;
	std::mt19937_64 gen(rd());
	const std::uniform_int_distribution distr(value - range / 2, value + range / 2);

	return 1 / static_cast<float>(round(distr(gen)));
}

std::int32_t detours::hk_getroundtriptime(void* _this)
{
	static auto genuine_f = get().fetch_hook(SECSTR("Fake Ping")).detour.get_original<decltype(&hk_getroundtriptime)>();

	if (!config::get<bool>(g_context.fake_ping))
		return genuine_f(_this);

	const auto& range = config::get<int>(g_context.fake_ping_range);
	const auto& value = config::get<int>(g_context.fake_ping_i);

	if (!range)
		return value;

	std::random_device rd;
	std::mt19937_64 gen(rd());
	const std::uniform_int_distribution distr(value - range / 2, value + range / 2);

	return static_cast<std::int32_t>(std::round(distr(gen)));
}

assembler::il2cpp::il2cpp_string* detours::hk_getdeviceuniqueidentifier()
{
	static auto genuine_f = get().fetch_hook(SECSTR("HWIDSpoof")).detour.get_original<decltype(&hk_getdeviceuniqueidentifier)>();

	if (!config::get<bool>(g_context.fake_hwid))
		return genuine_f();

	if (config::get<std::string>(g_context.set_hwid).empty())
		config::get<std::string>(g_context.set_hwid) = misc::get_device_id();

	return assembler::il2cpp::string_new(config::get<std::string>(g_context.set_hwid));
}

void detours::hk_sendputrequest(assembler::il2cpp::il2cpp_string* target, assembler::il2cpp::il2cpp_object* res, assembler::il2cpp::il2cpp_object* req, assembler::il2cpp::il2cpp_object* cr)
{
	/* Seems to send "visits" to display online activity. No idea what "joins" is but that is sometimes passed through as well.
	 * Most notiablly passed whenever joining a new world or something. idk man. */
	static auto genuine_f = get().fetch_hook(SECSTR("SendPutRequest")).detour.get_original<decltype(&hk_sendputrequest)>();


	const auto target_casted = wsv_chars(target);
	if (config::get<bool>(g_context.fake_offline))
		if (target_casted.contains(xorstr_(L"visits")))
			return;


	genuine_f(target, res, req, cr);
}
#pragma endregion

#pragma region avatar_loading
std::uintptr_t* detours::hk_onavatardownload(std::uintptr_t* callback, assembler::vrc::core::api_avatar* avatar, assembler::il2cpp::il2cpp_object* a3, const bool a4)
{
	static auto genuine_f = get().fetch_hook(SECSTR("OnAvatarDownload")).detour.get_original<decltype(&hk_onavatardownload)>();

	if (std::ranges::find(g_context.g_avatars, avatar->get_id()) == g_context.g_avatars.end())
	{
		if (const auto bl_vec = &config::get<std::vector<std::string>>(g_context.avatar_blacklist); config::get<bool>(g_context.anti_blacklisted_avatars) && std::ranges::find(*bl_vec, avatar->get_id()) != bl_vec->end())
		{
			logging::push(FOREGROUND_INTENSE_RED);
			logging::print(xorstr_("[log] \"{}\" by \"{}\" is blacklisted [{}]\n"), avatar->get_name(), avatar->get_author_name(), avatar->get_asset_url());
			logging::pop();
			avatar->set_id("");
		}

		else
		{
			logging::push(FOREGROUND_CYAN);
			logging::print(xorstr_("[log] downloading \"{}\" by \"{}\" [{}]\n"), avatar->get_name(), avatar->get_author_name(), avatar->get_asset_url());
			logging::pop();
		}
	}

	return genuine_f(callback, avatar, a3, a4);
}

assembler::il2cpp::il2cpp_object* detours::hk_switchavatarrpc(assembler::il2cpp::il2cpp_object* callback, assembler::vrc::avatarmanager* _this, assembler::vrc::core::api_avatar* apiavatar, const float fl)
{
	static auto genuine_f = get().fetch_hook(xorstr_("SwitchAvatarRPC")).detour.get_original<decltype(&hk_switchavatarrpc)>();

	const auto vrcplayer = _this->get_vrc_player();
	const std::string avatar_id = apiavatar->get_id();

	if (const auto player = vrcplayer->get_player(); wsv_chars(player->get_api_user()->fields.id) == wsv_chars(assembler::vrc::core::api_user::get_current()->fields.id))
	{
		if (config::get<bool>(g_context.collision_crash) || config::get<bool>(g_context.quest_crash) || config::get<bool>(g_context.corrupt_asset_crash) || config::get<bool>(g_context.audio_crash))
			apiavatar = nullptr;

		return genuine_f(callback, _this, apiavatar, fl);
	}

	return genuine_f(callback, _this, apiavatar, fl);
}
#pragma endregion

#pragma region photon
bool detours::hk_opraiseevent(std::uintptr_t* _this, const std::uint8_t code, assembler::il2cpp::il2cpp_object* custom_content, assembler::il2cpp::il2cpp_object* raise_options, std::uintptr_t* send_options)
{
	//0x181CB29A0
	static auto& instance = get();
	static auto genuine_f = instance.fetch_hook(SECSTR("RaiseEvent")).detour.get_original<decltype(&hk_opraiseevent)>();

	//if (static_cast<int>(code) == 7 && selected_photon_id != NULL) return genuine_f(_this, code, content, raise_options, send_options);

	if (sniffer_window::enabled && code != event_map::executive_moderation)
	{
		const auto index = event_map::convert_packet_to_config_type(code);
		if (index <= global_variables::join && sniffer_window::log_self && config::get<std::vector<bool>>(g_context.vec_packet_log).at(index))
		{
			const auto customdata = static_cast<assembler::il2cpp::il2cpp_array*>(custom_content);
			const auto data = customdata && customdata->max_length > 0 ? assembler::buffer::to_base64_string(customdata) : xorstr_("none");
			const auto fmt = utility::format(xorstr_("[outgoing] [code: {:d}] data: {}\n"), code, data);
			logging::push(FOREGROUND_INTENSE_WHITE);
			logging::print(fmt);
			sniffer_window::print_log(fmt);
			logging::pop();
		}
	}
	if (sniffer_window::block_outgoing)
		if (const auto index = event_map::convert_packet_to_config_type(code); index <= global_variables::join && config::get<std::vector<bool>>(g_context.vec_packet_log).at(index))
			return false;

	SEH_START
		switch (static_cast<int>(code))
		{
		case event_map::object_instantiation:
			{
				if (config::get<bool>(g_context.anti_instance_lock))
				{
					if (const auto vrc_el = assembler::vrc_eventlog::instance())
					{
						vrc_el->should_process_events(true);
						vrc_el->get_eventreplicator()->process_events(true);
					}
				}

				//@note: set broadcast type to master-only, no other players see instantiation
				if (config::get<bool>(g_context.invisible_join))
					*(reinterpret_cast<std::uint8_t*>(raise_options) + 0x20) = 2U;

				const auto ret = genuine_f(_this, code, custom_content, raise_options, send_options);

				if (config::get<bool>(g_context.invisible_join))
					*(reinterpret_cast<std::uint8_t*>(raise_options) + 0x20) = 0U;

				return ret;
			}
		case event_map::serialized_data_unreliable:
			{
				instance.pn_.photon_network_ptr = _this;
				instance.pn_.send_options = send_options;

				if (g_context.anti_aim)
				{
					static const auto far_vec = sdk::vector(1000000.f, 1000000.f, 1000000.f);

					const auto customdata = static_cast<assembler::il2cpp::il2cpp_array_wrapper<std::uint8_t>*>(custom_content);
					std::memcpy(&customdata->at(39), far_vec.data(), sizeof(float) * 3);

					return genuine_f(_this, code, custom_content, raise_options, send_options);
				}
#if TEST == 1
				if (config::get<bool>(g_context.event_7_test))
				{
					if (!instance.e7_exploit_servertime_)
						instance.e7_exploit_servertime_ = assembler::vrc::sdk_base::networking::get_server_time_in_milliseconds();

					assembler::buffer::block_copy(assembler::buffer::get_bytes(instance.e7_exploit_servertime_), 0, static_cast<assembler::il2cpp::il2cpp_array*>(custom_content), 4, 4);

					break;
				}

				if (instance.e7_exploit_servertime_)
					instance.e7_exploit_servertime_ = 0;
#endif

				//@note: block event 7 to stop movement broadcasting entirely
				if (config::get<bool>(g_context.serialize))
					return false;

				break;
			}
		case event_map::serialized_data_reliable:
			{
				if (config::get<bool>(g_context.serialize))
					return false;

				break;
			}
		default: break;
		}
	SEH_END
	return genuine_f(_this, code, custom_content, raise_options, send_options);
}

void detours::hk_onevent(assembler::il2cpp::il2cpp_object* _this, assembler::event_data* event_data)
{
	static auto& instance = get();
	static auto genuine_f = instance.fetch_hook(SECSTR("OnEventPatch")).detour.get_original<decltype(&hk_onevent)>();

	const auto code = event_data->fields.code;
	const auto player_id = event_data->fields.sender;
	const auto customdata = reinterpret_cast<assembler::il2cpp::il2cpp_array_wrapper<std::uint8_t>*>(event_data->get_custom_data());

#pragma region log_packets
	if (sniffer_window::enabled && code != event_map::executive_moderation)
	{
		const auto index = event_map::convert_packet_to_config_type(code);
		bool is_mapped = false;

		{
			std::lock_guard sniffer_guard(sniffer_window::sniffer_mutex);
			is_mapped = sniffer_window::logging_players.contains(player_id);
		}

		if (index <= global_variables::join && is_mapped && config::get<std::vector<bool>>(g_context.vec_packet_log).at(index))
		{
			const auto data = customdata && customdata->max_length > 0 ? assembler::buffer::to_base64_string(customdata) : xorstr_("none");
			std::string name = xorstr_("server");

			if (player_id > 0)
				name = assembler::vrc::player_manager::get_player(player_id)->get_api_user()->display_name();

			const auto fmt = utility::format(xorstr_("[incoming from actor {:d} ({})] [code: {:d}] data: {}\n"), player_id, name, code, data);
			logging::push(FOREGROUND_INTENSE_WHITE);
			logging::print(fmt);
			sniffer_window::print_log(fmt);
			logging::pop();
		}
	}
	if (sniffer_window::block_incoming)
		if (const auto index = event_map::convert_packet_to_config_type(code); index <= global_variables::join && config::get<std::vector<bool>>(g_context.vec_packet_log).at(index))
			return;

#pragma endregion

	if (player_id > 0)
	{
		const auto apiuser = assembler::vrc::player_manager::get_player(player_id)->get_api_user();

		if (apiuser && apiuser->get_id() == assembler::vrc::core::api_user::get_current()->get_id())
		{
			if (config::get<bool>(g_context.reduce_bad_activity))
			{
				try
				{
					return genuine_f(_this, event_data);
				}
				catch (const Il2CppExceptionWrapper& e)
				{
					logging::push(FOREGROUND_INTENSE_RED);
					logging::print(xorstr_("[critical] failed to process event [{}]\n"), s_chars(e.ex->message));
					logging::pop();
					return;
				}
			}

			return genuine_f(_this, event_data);
		}

		if (instance.event_map_.is_blacklisted(player_id, code))
			return;

		if (apiuser && instance.event_map_.is_user_blocked(apiuser->get_id()))
			return;

		if (instance.invisible_users_.contains(player_id) && config::get<bool>(g_context.reduce_bad_activity))
			return;

		if (config::get<bool>(g_context.allow_friends) && apiuser && assembler::vrc::core::api_user::is_friends_with(apiuser->get_id()))
		{
			if (config::get<bool>(g_context.reduce_bad_activity))
			{
				try
				{
					return genuine_f(_this, event_data);
				}
				catch (const Il2CppExceptionWrapper& e)
				{
					logging::push(FOREGROUND_INTENSE_RED);
					logging::print(xorstr_("[critical] failed to process event from \"{}\" [{}]\n"), apiuser->display_name(), s_chars(e.ex->message));
					logging::pop();

					instance.event_map_.blacklist_user(player_id, code);
					return;
				}
			}

			return genuine_f(_this, event_data);
		}
	}

	switch (code)
	{
	case event_map::serialized_data_unreliable:
		{
			if (config::get<bool>(g_context.nameplate_info))
				nameplate_manager::update_user(player_id);

			if (!customdata)
				break;

			if (config::get<bool>(g_context.reduce_bad_activity))
				assembler::buffer::block_copy(assembler::buffer::get_bytes(assembler::vrc::sdk_base::networking::get_server_time_in_milliseconds()), 0, customdata, 4, 4);

			auto bytes = assembler::il2cpp::array_to_vector<std::uint8_t>(customdata);
			if (const auto sender_id = std::to_string(assembler::vrc::udon::serialization::odin_serializer::proper_bit_converter::to_int32(bytes, 0)); config::get<bool>(g_context.anti_object_spam) && sender_id != std::to_string(player_id) + xorstr_("00001"))
				return;

			if (!config::get<bool>(g_context.reduce_bad_activity))
				break;

			if (bytes.size() < 20)
				return;
			
			if (instance.event_map_.is_event_mapped(code, player_id, bytes))
			{
				instance.event_map_.blacklist_user(player_id, code);
				return;
			}

			if (!instance.bot_users_.contains(player_id))
			{
				std::lock_guard guard(instance.bot_mutex_);
				instance.bot_users_[player_id] = false;
			}
			break;
		}
	case event_map::serialized_data_reliable:
		{
			if (config::get<bool>(g_context.nameplate_info))
				nameplate_manager::update_user(player_id);

			if (!customdata)
				break;

			auto bytes = assembler::il2cpp::array_to_vector<std::uint8_t>(customdata);
			const auto sender_id = assembler::vrc::udon::serialization::odin_serializer::proper_bit_converter::to_int32(bytes, 0);

			if (config::get<bool>(g_context.anti_object_spam) && !std::to_string(sender_id).starts_with(std::to_string(player_id) + xorstr_("0000")))
				return;

			if (!config::get<bool>(g_context.reduce_bad_activity))
				break;

			if (!sender_id)
				return;

			if (bytes.size() <= 10)
			{
				ingame_logging::get().log(xorstr_("[<color=#a75cf6>event 9</color>] {} sent malicious bytes [{:d}<]"), assembler::vrc::player_manager::get_player(player_id)->to_string(), bytes.size());
				logging::push(FOREGROUND_INTENSE_BLUE);
				logging::add_log(xorstr_("[event 9] {} sent malicious bytes [{:d}<]\n"), assembler::vrc::player_manager::get_player(player_id)->to_string(), bytes.size());
				logging::pop();

				instance.event_map_.blacklist_user(player_id, code);
				return;
			}

			if (!assembler::vrc::udon::serialization::odin_serializer::proper_bit_converter::to_int32(bytes, 4))
			{
				ingame_logging::get().log(xorstr_("[<color=#a75cf6>event 9</color>] {} sent invalid bytes."), assembler::vrc::player_manager::get_player(player_id)->to_string());
				logging::push(FOREGROUND_INTENSE_BLUE);
				logging::add_log(xorstr_("[event 9] {} sent invalid bytes.\n"), assembler::vrc::player_manager::get_player(player_id)->to_string());
				logging::pop();

				instance.event_map_.blacklist_user(player_id, code);
				return;
			}

			if (instance.event_map_.is_event_mapped(code, player_id, bytes))
			{
				instance.event_map_.blacklist_user(player_id, code);
				return;
			}
			break;
		}
	case event_map::vrchat_rpc:
		{
			if (!config::get<bool>(g_context.reduce_bad_activity) || !customdata)
				break;

			if (!instance.event_map_.is_event_safe(xorstr_("Generic"), code, 0))
				return;

			assembler::il2cpp::il2cpp_object* obj;
			try
			{
				assembler::buffer::deserialize(customdata, &obj);

				if (!obj)
					break;
			}
			catch (const Il2CppExceptionWrapper& e)
			{
				ingame_logging::get().log(xorstr_("[<color=#a75cf6>event 6</color>] {} sent invalid bytes."), assembler::vrc::player_manager::get_player(player_id)->to_string());
				logging::push(FOREGROUND_INTENSE_BLUE);
				logging::add_log(xorstr_("[event 6] {} sent invalid bytes. [{}]\n"), assembler::vrc::player_manager::get_player(player_id)->to_string(), s_chars(e.ex->message));
				logging::pop();

				instance.event_map_.blacklist_user(player_id, code);
				return;
			}

			const auto event_log = reinterpret_cast<assembler::vrc_eventlog::event_log_entry*>(obj);
			if (event_log->get_sender_id() != player_id)
			{
				ingame_logging::get().log(xorstr_("[<color=#a75cf6>event 6</color>] {} sent invalid bytes."), assembler::vrc::player_manager::get_player(player_id)->to_string());
				logging::push(FOREGROUND_INTENSE_BLUE);
				logging::add_log(xorstr_("[event 6] {} sent invalid bytes.\n"), assembler::vrc::player_manager::get_player(player_id)->to_string());
				logging::pop();

				instance.event_map_.blacklist_user(player_id, code);
				return;
			}

			const auto vrc_event = event_log->get_vrc_event();
			if (!vrc_event)
				break;

			assembler::il2cpp::il2cpp_array_wrapper<assembler::il2cpp::il2cpp_object*>* params;
			try
			{
				if (params = assembler::buffer::serialize_parameters(vrc_event->fields.parameter_bytes); params == nullptr)
				{
					ingame_logging::get().log(xorstr_("[<color=#a75cf6>event 6</color>] {} sent invalid bytes."), assembler::vrc::player_manager::get_player(player_id)->to_string());
					logging::push(FOREGROUND_INTENSE_BLUE);
					logging::add_log(xorstr_("[event 6] {} sent invalid bytes.\n"), assembler::vrc::player_manager::get_player(player_id)->to_string());
					logging::pop();

					instance.event_map_.blacklist_user(player_id, code);
					return;
				}
			}
			catch (const Il2CppExceptionWrapper& e)
			{
				ingame_logging::get().log(xorstr_("[<color=#a75cf6>event 6</color>] {} sent invalid bytes."), assembler::vrc::player_manager::get_player(player_id)->to_string());
				logging::push(FOREGROUND_INTENSE_BLUE);
				logging::add_log(xorstr_("[event 6] {} sent invalid bytes [{}]\n"), assembler::vrc::player_manager::get_player(player_id)->to_string(), s_chars(e.ex->message));
				logging::pop();

				instance.event_map_.blacklist_user(player_id, code);
				return;
			}

			const auto param_string = s_chars(vrc_event->fields.parameter_string);
			switch (sdk::hash::fnv1a::hash(param_string.c_str()))
			{
			case sdk::hash::fnv1a::hash_const("ConfigurePortal"):
				{
					if (!params->at(0) || !params->at(1) || !params->at(2))
					{
						ingame_logging::get().log(xorstr_("[<color=#a75cf6>event 6</color>] {} sent invalid bytes."), assembler::vrc::player_manager::get_player(player_id)->to_string());
						logging::push(FOREGROUND_INTENSE_BLUE);
						logging::add_log(xorstr_("[event 6] {} sent invalid bytes.\n"), assembler::vrc::player_manager::get_player(player_id)->to_string());
						logging::pop();

						instance.event_map_.blacklist_user(player_id, code);
						return;
					}

					if (const auto player_count = *static_cast<std::int32_t*>(object_unbox(params->at(2))); player_count < 0 || player_count > 80)
					{
						ingame_logging::get().log(xorstr_("[<color=#a75cf6>event 6</color>] {} sent invalid bytes."), assembler::vrc::player_manager::get_player(player_id)->to_string());
						logging::push(FOREGROUND_INTENSE_BLUE);
						logging::add_log(xorstr_("[event 6] {} sent invalid bytes.\n"), assembler::vrc::player_manager::get_player(player_id)->to_string());
						logging::pop();

						instance.event_map_.blacklist_user(player_id, code);
						return;
					}

					const auto apiuser = assembler::vrc::player_manager::get_player(player_id)->get_api_user();
					ingame_logging::get().log(xorstr_("[<color=#a75cf6>log</color>] {} spawned a portal"), apiuser->display_name());
					logging::push(FOREGROUND_CYAN);
					logging::add_log(xorstr_("[log] {} spawned a portal\n"), apiuser->display_name());
					logging::pop();
					break;
				}
			case sdk::hash::fnv1a::hash_const("SpawnEmojiRPC"):
				{
					if (!params->at(0))
					{
						ingame_logging::get().log(xorstr_("[<color=#a75cf6>event 6</color>] {} sent invalid bytes."), assembler::vrc::player_manager::get_player(player_id)->to_string());
						logging::push(FOREGROUND_INTENSE_BLUE);
						logging::add_log(xorstr_("[event 6] {} sent invalid bytes.\n"), assembler::vrc::player_manager::get_player(player_id)->to_string());
						logging::pop();

						instance.event_map_.blacklist_user(player_id, code);
						return;
					}

					if (const auto emoji_index = *static_cast<std::int32_t*>(object_unbox(params->at(0))); emoji_index < 0 || emoji_index > 56)
					{
						ingame_logging::get().log(xorstr_("[<color=#a75cf6>event 6</color>] {} sent invalid bytes."), assembler::vrc::player_manager::get_player(player_id)->to_string());
						logging::push(FOREGROUND_INTENSE_BLUE);
						logging::add_log(xorstr_("[event 6] {} sent invalid bytes.\n"), assembler::vrc::player_manager::get_player(player_id)->to_string());
						logging::pop();

						instance.event_map_.blacklist_user(player_id, code);
						return;
					}

					const auto apiuser = assembler::vrc::player_manager::get_player(player_id)->get_api_user();
					ingame_logging::get().log(xorstr_("[<color=#a75cf6>log</color>] {} spawned an emoji"), apiuser->display_name());
					logging::push(FOREGROUND_CYAN);
					logging::add_log(xorstr_("[log] {} spawned an emoji\n"), apiuser->display_name());
					logging::pop();
					break;
				}
			case sdk::hash::fnv1a::hash_const("UdonSyncRunProgramAsRPC"):
				{
					if (config::get<bool>(g_context.anti_udon_events))
						return;

					break;
				}
			default: break;
			}

			const auto event_type = vrc_event->fields.event_type;

			if (event_type > assembler::vrc_event_type::call_udon_method)
			{
				ingame_logging::get().log(xorstr_("[<color=#a75cf6>event 6</color>] {} sent invalid bytes."), assembler::vrc::player_manager::get_player(player_id)->to_string());
				logging::push(FOREGROUND_INTENSE_BLUE);
				logging::add_log(xorstr_("[event 6] {} sent invalid bytes.\n"), assembler::vrc::player_manager::get_player(player_id)->to_string());
				logging::pop();

				instance.event_map_.blacklist_user(player_id, code);
				return;
			}

			switch (event_type)
			{
			case assembler::vrc_event_type::call_udon_method:
				{
					if (config::get<bool>(g_context.anti_udon_events))
						return;

					break;
				}
			case assembler::vrc_event_type::animation_bool:
			case assembler::vrc_event_type::set_game_object_active:
				{
					if (config::get<bool>(g_context.anti_worldtriggers))
						return;

					break;
				}
			case assembler::vrc_event_type::send_rpc:
			case assembler::vrc_event_type::add_health:
				{
					if (!config::get<bool>(g_context.anti_master_dc))
						break;

					if (param_string.length() > 75 || param_string.contains(xorstr_("color")))
						return;

					break;
				}

			default: break;
			}

			if (event_type > assembler::vrc_event_type::send_rpc)
				break;

			for (const auto& sc : event_log->get_name())
			{
				if (const auto& uc = static_cast<std::uint8_t>(sc); !(std::isalpha(uc) || std::isdigit(uc) || sc == ':' || sc == '/' || std::isspace(uc) || sc == ' ' || sc == '(' || sc == ')' || sc == '-' || sc == '_'))
				{
					ingame_logging::get().log(xorstr_("[<color=#a75cf6>event 6</color>] {} sent invalid bytes."), assembler::vrc::player_manager::get_player(player_id)->to_string());
					logging::push(FOREGROUND_INTENSE_BLUE);
					logging::add_log(xorstr_("[event 6] {} sent invalid bytes.\n"), assembler::vrc::player_manager::get_player(player_id)->to_string());
					logging::pop();

					instance.event_map_.blacklist_user(player_id, code);
					return;
				}
			}

			if (!instance.event_map_.is_event_safe(xorstr_("G_") + param_string, code, 0))
				return;

			if (!instance.event_map_.is_event_safe(param_string, code, player_id))
				return;

			break;
		}
	case event_map::uspeak_audio:
		{
			if (!customdata)
				break;

			if (config::get<int>(g_context.copy_event1) == player_id)
			{
				const auto src = assembler::buffer::from_base64_string(assembler::buffer::to_base64_string(customdata));
				assembler::buffer::block_copy(assembler::buffer::get_bytes(0), 0, src, 0, 4);
				assembler::buffer::block_copy(assembler::buffer::get_bytes(assembler::vrc::sdk_base::networking::get_server_time_in_milliseconds()), 0, src, 4, 4);
				hk_opraiseevent(instance.pn_.photon_network_ptr, 1u, src, nullptr, instance.pn_.send_options);
			}

			if (!config::get<bool>(g_context.anti_uspeak_exploit))
				break;

			auto bytes = assembler::il2cpp::array_to_vector<std::uint8_t>(customdata);

			if (bytes.size() <= 8)
			{
				instance.event_map_.blacklist_user(player_id, code);
				return;
			}

			if (const auto sender_bytes = assembler::vrc::udon::serialization::odin_serializer::proper_bit_converter::to_int32(bytes, 0); sender_bytes != player_id)
			{
				instance.event_map_.blacklist_user(player_id, code);
				return;
			}

			if (instance.event_map_.is_event_mapped(code, player_id, bytes))
			{
				instance.event_map_.blacklist_user(player_id, code);
				return;
			}
			break;
		}
	case event_map::mc_sync_start:
		{
			if (const auto vrcplayerapi_current = assembler::vrc::sdk_base::vrc_player_api::get_current())
				if (vrcplayerapi_current->get_is_master() && config::get<bool>(g_context.instance_lock))
					return;

			break;
		}
	case event_map::ownership_request:
		{
			if (config::get<bool>(g_context.anti_master_dc) || config::get<bool>(g_context.anti_object_spam))
				return;

			break;
		}
	case event_map::ownership_transfer:
		{
			if (config::get<bool>(g_context.anti_object_spam))
				return;

			break;
		}
	case event_map::auth_event:
		{
			ingame_logging::get().log(xorstr_("[<color=#a75cf6>event 223</color>] photon authenticated serverside"));
			logging::push(FOREGROUND_INTENSE_BLUE);
			logging::add_log(xorstr_("[event 223] photon authenticated serverside\n"));
			logging::pop();
			break;
		}
	case event_map::executive_moderation:
		{
			const auto hashtable = static_cast<assembler::system_replication::collections::dictionary*>(event_data->get_item(245u));

			std::uint8_t lookup = 1;
			const auto player_index = hashtable->dictionary_get<std::int32_t>(&lookup, xorstr_("System.Byte"));

			if (!player_index)
				break;

			lookup = 10;
			const auto block_index = hashtable->contains_key(assembler::il2cpp::value_box(xorstr_("System.Byte"), &lookup));
			lookup = 11;
			const auto mute_index = hashtable->dictionary_get<bool>(&lookup, xorstr_("System.Byte"));

			const auto apiuser = assembler::vrc::player_manager::get_player(player_index)->get_api_user();

			if (block_index)
			{
				lookup = 10;
				const auto is_blocked = hashtable->dictionary_get<bool>(&lookup, xorstr_("System.Byte"));

				std::unique_lock blocked_user_guard(instance.blocked_users_mutex_);
				if (instance.blocked_users_.contains(player_index) && !is_blocked)
				{
					instance.blocked_users_.erase(player_index);
					blocked_user_guard.unlock();

					ingame_logging::get().log(xorstr_("[<color=#a75cf6>notice</color>] {} unblocked you"), apiuser ? apiuser->display_name() : xorstr_("an unknown user"));
					logging::push(FOREGROUND_INTENSE_RED);
					logging::add_log(xorstr_("[notice] {} unblocked you\n"), apiuser ? apiuser->display_name() : xorstr_("an unknown user"));
					logging::pop();

					if (config::get<bool>(g_context.xs_overlay_toggle))
						xs_overlay::get().send(xorstr_("Void Client"), utility::format(xorstr_("{} unblocked you\n"), apiuser ? apiuser->display_name() : xorstr_("an unknown user")), xorstr_("warning"), 4);
				}
				else if (is_blocked)
				{
					instance.blocked_users_.insert(player_index);
					blocked_user_guard.unlock();

					ingame_logging::get().log(xorstr_("[<color=#a75cf6>notice</color>] {} blocked you"), apiuser ? apiuser->display_name() : xorstr_("an unknown user"));
					logging::push(FOREGROUND_INTENSE_RED);
					logging::add_log(xorstr_("[notice] {} blocked you\n"), apiuser ? apiuser->display_name() : xorstr_("an unknown user"));
					logging::pop();

					if (config::get<bool>(g_context.xs_overlay_toggle))
						xs_overlay::get().send(xorstr_("Void Client"), utility::format(xorstr_("{} blocked you\n"), apiuser ? apiuser->display_name() : xorstr_("an unknown user")), xorstr_("warning"), 4);

					if (config::get<bool>(g_context.anti_block))
						return;
				}
				else
					blocked_user_guard.unlock();
			}

			if (mute_index)
			{
				ingame_logging::get().log(xorstr_("[<color=#a75cf6>notice</color>] {} muted you"), apiuser ? apiuser->display_name() : xorstr_("an unknown user"));
				logging::push(FOREGROUND_INTENSE_RED);
				logging::add_log(xorstr_("[notice] {} muted you\n"), apiuser ? apiuser->display_name() : xorstr_("an unknown user"));
				logging::pop();
				break;
			}

			break;
		}
	default: break;
	}

	if (config::get<bool>(g_context.reduce_bad_activity))
	{
		try
		{
			return genuine_f(_this, event_data);
		}
		catch (const Il2CppExceptionWrapper& e)
		{
#ifdef _DEBUG
			logging::push(FOREGROUND_INTENSE_RED);
			logging::print(xorstr_("[critical] failed to process event from actor {:d} [{}]\n"), player_id, s_chars(e.ex->message));
			logging::pop();
#endif

			if (player_id)
				instance.event_map_.blacklist_user(player_id, code);

			return;
		}
	}

	return genuine_f(_this, event_data);
}
#pragma endregion

#pragma region join_leave
void detours::hk_onphotonplayerjoined(void* _this, assembler::photon_player* photon_player)
{
	//Hashtable whatthefuck { get; set; }
	static auto& instance = get();
	static auto genuine_f = instance.fetch_hook(SECSTR("OnPhotonPlayerJoined")).detour.get_original<decltype(&hk_onphotonplayerjoined)>();
	genuine_f(_this, photon_player);

	if (!g_context.reduce_bad_activity && !g_context.detect_invisibles)
		return;

	std::thread([=]
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
		if (photon_player->get_vrc_player() != nullptr || !g_context.instantiated)
			return;

		if (g_context.detect_invisibles)
		{
			std::string username = xorstr_("an unknown user");

			const auto hashtable = photon_player->get_hashtable();
			if (const auto dictionary = hashtable->get_item<assembler::system_replication::collections::dictionary*>(assembler::il2cpp::string_new(xorstr_(L"user"))))
				if (const auto object = dictionary->dictionary_get<assembler::il2cpp::il2cpp_string*>(assembler::il2cpp::string_new(xorstr_(L"displayName"))))
					username = s_chars(object);

			if (config::get<bool>(g_context.xs_overlay_toggle))
			{
				if (const auto noti = utility::format(xorstr_("{} joined invisible."), username); !xs_overlay::get().send(noti, xorstr_(""), xorstr_("warning"), 4))
				{
					logging::push(FOREGROUND_INTENSE_RED);
					logging::print(xorstr_("[critical] failed to talk to xs-overlay api [{}]\n"), xs_overlay::get().fetch_last_error());
					logging::pop();
				}
			}

			ingame_logging::get().log(xorstr_("[<color=#a75cf6>warn</color>]: {} joined invisible."), username);
			logging::push(FOREGROUND_INTENSE_RED);
			logging::add_log(xorstr_("[warn] {} joined invisible.\n"), username);
			logging::pop();
		}

		std::lock_guard guard(instance.g_mutex_);
		instance.invisible_users_.insert(photon_player->get_id());
	}).detach();
}

void detours::hk_onphotonplayerleft(void* _this, assembler::photon_player* photon_player)
{
	static auto& instance = get();
	static auto genuine_f = instance.fetch_hook(SECSTR("OnPhotonPlayerLeft")).detour.get_original<decltype(&hk_onphotonplayerleft)>();

	const auto id = photon_player->get_id();

	if (assembler::vrc::player::get_current()->get_photon_id() == id)
		return genuine_f(_this, photon_player);

	{
		std::lock_guard guard(instance.blocked_users_mutex_);
		if (instance.blocked_users_.contains(id))
			instance.blocked_users_.erase(id);
	}

	genuine_f(_this, photon_player);
}

void detours::hk_onplayerjoin(assembler::il2cpp::il2cpp_object* _this, assembler::vrc::player* player) // OnPlayerJoin string
{
	static auto& instance = get();
	static auto genuine_f = instance.fetch_hook(SECSTR("OnPlayerJoined")).detour.get_original<decltype(&hk_onplayerjoin)>();

	if (player->get_api_user()->get_id() == assembler::vrc::core::api_user::get_current()->get_id())
	{
		config::get<bool>(g_context.serialize) = false;
		instance.tickcount_ = duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		g_context.instantiated = true;

		try
		{
			const auto room_manager = assembler::room_manager::get_new();

			if (!room_manager)
				throw std::runtime_error(xorstr_("failed to get room_manager"));

			const auto api_world = room_manager->klass->static_fields->world;
			const auto api_world_instance = room_manager->klass->static_fields->world_instance;

			assembler::unity_engine::object::destroy(reinterpret_cast<assembler::unity_engine::object*>(room_manager));

			if (api_world == nullptr || api_world_instance == nullptr)
				throw std::runtime_error(xorstr_("failed to get world info"));

			if (!config::update_instance_history(api_world->get_name(), assembler::room_manager::get_room_id()))
				throw std::runtime_error(xorstr_("failed to update instance history [\"instance_history.void\"]"));

			if (config::get<bool>(g_context.xs_overlay_toggle))
			{
				const auto status = assembler::vrc::core::api_user::get_current()->get_status();
				const auto world_info = utility::format(xorstr_("Welcome to {}\r\n[{}] [Players: {:d}]"), api_world->get_name(), api_world_instance->get_access_type(), static_cast<std::int32_t>(array_length(assembler::vrc::player_manager::get_players())));

				if (!xs_overlay::get().send(xorstr_("Void Client"), std::string_view(world_info)))
					throw std::runtime_error(utility::format(xorstr_("failed to talk to xs-overlay api [{}]"), xs_overlay::get().fetch_last_error()));
			}
		}
		catch (const std::exception& e)
		{
			logging::push(FOREGROUND_INTENSE_RED);
			logging::print(xorstr_("[critical] {}\n"), e.what());
			logging::pop();
		}

		//if (instance.cached_hwid_.empty())
		//	instance.cached_hwid_ = connection_listener::get_hwid();

		//connection_listener::get().update_userlist(instance.cached_hwid_, nameplate_manager::get_userlist(), nameplate_manager::get_mutexes());

		genuine_f(_this, player);

		auto& game_manager_instance = helpers::game_manager::get();
		game_manager_instance.cache();
		game_manager_instance.on_join();

		if (config::get<bool>(g_context.chams))
			nameplate_manager::fix_mirrormasks(true);

		return;
	}

	if (config::get<bool>(g_context.join_notify))
	{
		if (!g_context.instantiated || duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - get().tickcount_ < 5000)
			return genuine_f(_this, player);

		const auto playername = player->to_string();

		if (config::get<bool>(g_context.join_notify_friends))
		{
			if (!assembler::vrc::core::api_user::is_friends_with(player->get_api_user()->get_id()))
			{
				logging::push(FOREGROUND_INTENSE_GREEN);
				logging::print_imgui(xorstr_("[notice] {} joined\n"), playername);
				logging::print(xorstr_("[notice] {} joined [{}]\n"), playername, player->get_api_user()->get_id());
				logging::pop();
				return genuine_f(_this, player);
			}
		}

		if (config::get<bool>(g_context.xs_overlay_toggle))
		{
			if (const auto noti = utility::format(xorstr_("{} joined"), playername); !xs_overlay::get().send(std::string_view(noti), xorstr_(""), xorstr_("default"), 4))
			{
				logging::push(FOREGROUND_INTENSE_RED);
				logging::print(xorstr_("[critical] failed to talk to xs-overlay api [{}]\n"), xs_overlay::get().fetch_last_error());
				logging::pop();
			}
		}
		else
			assembler::vrc_ui_manager::instance()->hud_msg(utility::format(xorstr_("[void] {} joined"), playername));

		logging::push(FOREGROUND_INTENSE_GREEN);
		logging::print_imgui(xorstr_("[notice] {} joined\n"), playername);
		logging::print(xorstr_("[notice] {} joined [{}]\n"), playername, player->get_api_user()->get_id());
		logging::pop();

		ingame_logging::get().log(xorstr_("[<color=#21cf4f>+</color>] {}"), playername);
	}

	genuine_f(_this, player);
}

void detours::hk_onplayerleft(assembler::il2cpp::il2cpp_object* _this, assembler::vrc::player* player) // OnPlayerLeft string
{
	static auto& instance = get();
	static auto genuine_f = instance.fetch_hook(SECSTR("OnPlayerLeft")).detour.get_original<decltype(&hk_onplayerleft)>();

	if (const auto userid = player->get_api_user()->get_id(); userid == assembler::vrc::core::api_user::get_current()->get_id())
	{
		instance.e7_exploit_servertime_ = 0;
		g_context.instantiated = false;
		g_context.player_attach_id = 0;

		if (g_context.anti_aim)
			g_context.anti_aim = false;

		config::get<int>(g_context.copy_event1) = NULL;

		if (g_context.block_downloads)
		{
			g_context.block_downloads = false;
			misc::toggle_download_manager(true);
		}

		if (instance.is_quickmenu_open_)
		{
			hk_onmenuclose(assembler::ui_manager_impl::instance(), false);
			instance.is_quickmenu_open_ = false;
		}

		instance.clean();
	}
	else
	{
		const auto phtn_id = player->get_photon_id();

		if (config::get<int>(g_context.copy_event1) == phtn_id)
			config::get<int>(g_context.copy_event1) = 0;

		if (g_context.player_attach_id == phtn_id)
			g_context.player_attach_id = 0;

		instance.event_map_.cleanup_user(phtn_id);

		if (config::get<bool>(g_context.nameplate_info))
			nameplate_manager::cleanup_user(phtn_id);

		if (config::get<bool>(g_context.join_notify))
		{
			const auto playername = player->to_string();

			if (duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - instance.tickcount_ < 5000)
				return genuine_f(_this, player);

			if (config::get<bool>(g_context.join_notify_friends))
			{
				if (!assembler::vrc::core::api_user::is_friends_with(userid))
				{
					logging::push(FOREGROUND_INTENSE_RED);
					logging::print_imgui(xorstr_("[notice] {} left\n"), playername);
					logging::print(xorstr_("[notice] {} left [{}]\n"), playername, player->get_api_user()->get_id());
					logging::pop();
					return genuine_f(_this, player);
				}
			}

			const auto noti = utility::format(xorstr_("{} left"), playername);
			if (config::get<bool>(g_context.xs_overlay_toggle))
			{
				if (!xs_overlay::get().send(std::string_view(noti), xorstr_(""), xorstr_("default"), 4))
				{
					logging::push(FOREGROUND_INTENSE_RED);
					logging::print(xorstr_("[critical] failed to talk to xs-overlay api [{}]\n"), xs_overlay::get().fetch_last_error());
					logging::pop();
				}
			}
			else
				assembler::vrc_ui_manager::instance()->hud_msg(noti);

			logging::push(FOREGROUND_INTENSE_RED);
			logging::print_imgui(xorstr_("[notice] {} left\n"), playername);
			logging::print(xorstr_("[notice] {} left [{}]\n"), playername, player->get_api_user()->get_id());
			logging::pop();
			ingame_logging::get().log(xorstr_("[<color=#cf2144>-</color>] {}"), playername);
		}
	}

	genuine_f(_this, player);
}

void detours::hk_onleftroom(void* _this)
{
	static auto& instance = get();
	static auto genuine_f = instance.fetch_hook(SECSTR("OnLeftRoom")).detour.get_original<decltype(&hk_onleftroom)>();

	instance.tickcount_ = duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	return genuine_f(_this);
}

#pragma endregion

#pragma region page_manager
bool detours::hk_vrcuipage_awake(assembler::unity_engine::component* _this)
{
	static auto genuine_f = get().fetch_hook(SECSTR("OnPageChange")).detour.get_original<decltype(&hk_vrcuipage_awake)>();

	// @note: should handle all tab changes just as a vanilla page would
	if (assembler::vrc_quick_menu::menu_root)
	{
		if (const auto void_menu = assembler::vrc_quick_menu::menu_root->find(xorstr_("Menu_VoidVR")))
		{
			if (const auto object_name = _this->get_game_object()->get_ws_name(); object_name == xorstr_(L"Menu_Dashboard") && void_menu->get_game_object()->get_active_self())
			{
				void_menu->get_game_object()->set_active(false);
				_this->get_game_object()->set_active(true);
			}
			else if (void_menu->get_game_object()->get_active_self() && object_name != xorstr_(L"WingMenu"))
				void_menu->get_game_object()->set_active(false);
		}
	}

	return genuine_f(_this);
}
#pragma endregion

#pragma region udon
void detours::hk_udonbehaviour_runprogramstr(assembler::unity_engine::component* _this, assembler::il2cpp::il2cpp_string* event_name)
{
	static auto& instance = get();
	static auto genuine_f = instance.fetch_hook(SECSTR("UdonBehaviour::RunProgram(string)")).detour.get_original<decltype(&hk_udonbehaviour_runprogramstr)>();

	const auto api_world = assembler::room_manager::get_class()->static_fields->world;

	if (api_world && config::get<bool>(g_context.fbt_doorbypass) && wsv_chars(api_world->fields.id) == xorstr_(L"wrld_d319c58a-dcec-47de-b5fc-21200116462c") && !wsv_chars(event_name).starts_with(xorstr_(L"_")) && _this->get_ws_name().starts_with(xorstr_(L"Room")))
		return;

	return genuine_f(_this, event_name);
}

void detours::hk_udonsync_runprogramasrpc(assembler::unity_engine::component* _this, assembler::il2cpp::il2cpp_string* a2, assembler::vrc::player* player)
{
	static auto& instance = get();
	static auto genuine_f = instance.fetch_hook(SECSTR("Udon::UdonSyncRunProgramAsRPC")).detour.get_original<decltype(&hk_udonsync_runprogramasrpc)>();

	const auto apiuser = assembler::vrc::core::api_user::get_current();

	if (!apiuser || !player)
		return genuine_f(_this, a2, player);

	auto str = ws_chars(a2);
	utility::unicode_tolower(str);

	if (g_context.skippable_sync_kills > 0 && str.contains(xorstr_(L"kill")) && player->get_photon_id() == assembler::vrc::player::get_current()->get_photon_id())
	{
		g_context.skippable_sync_kills--;
		return;
	}

	if (config::get<bool>(g_context.udon_godmode) && (str.contains(xorstr_(L"synclock")) || str.contains(xorstr_(L"kill")) || str.contains(xorstr_(L"penalty")) || str.contains(xorstr_(L"votedout")) || str.contains(xorstr_(L"freezeme"))))
		if (wsv_chars(player->get_api_user()->fields.id) != wsv_chars(apiuser->fields.id))
			return;

	genuine_f(_this, a2, player);

	if (str.contains(xorstr_(L"fire")) && config::get<bool>(g_context.murder_weapontriggers))
	{
		const auto arr = assembler::unity_engine::object::find_objects_of_type_all(assembler::vrc::sdk_base::vrc_pickup::get_global_type());
		const auto v = assembler::il2cpp::array_to_vector<assembler::vrc::sdk_base::vrc_pickup*>(arr);

		for (auto it = v.begin(); it != v.end(); ++it)
		{
			if (!*it)
				continue;

			(*it)->set_pickupable(true);
			(*it)->set_disallowtheft(false);
		}
	}
}
#pragma endregion

void detours::hk_customscenes_ctor(assembler::il2cpp::il2cpp_object* _this, assembler::vrc::core::api_world* a2)
{
	static auto& instance = get();
	static auto genuine_f = instance.fetch_hook(SECSTR("CustomScenes::ctor")).detour.get_original<decltype(&hk_customscenes_ctor)>();

	if (!config::get<bool>(g_context.virtualize_world))
		return genuine_f(_this, a2);

	// VMProtectBeginUltra("CustomScenes::Ctor");

	const auto new_world = assembler::vrc::core::api_world::ctor();
	auto& fields = new_world->fields;

	const auto world_info = utility::split(config::get<std::string>(g_context.base_virtualization), xorstr_(":::"));

	fields.id = assembler::il2cpp::string_new(world_info[0]);
	fields.asset_url = assembler::il2cpp::string_new(world_info[1]);

	// VMProtectEnd();

	return genuine_f(_this, new_world);
}

assembler::il2cpp::il2cpp_object* detours::hk_assetbundle_loadworld(assembler::il2cpp::il2cpp_object* callback, assembler::vrc::core::api_world* a2, assembler::il2cpp::il2cpp_object* a3, bool a4)
{
	static auto& instance = get();
	static auto genuine_f = instance.fetch_hook(SECSTR("AssetBundle::LoadWorld")).detour.get_original<decltype(&hk_assetbundle_loadworld)>();

	if (!config::get<bool>(g_context.virtualize_world))
		return genuine_f(callback, a2, a3, a4);

	// VMProtectBeginUltra("AssetBundle::LoadWorld");

	const auto new_world = assembler::vrc::core::api_world::ctor();
	auto& fields = new_world->fields;

	const auto world_info = utility::split(config::get<std::string>(g_context.base_virtualization), xorstr_(":::"));

	fields.id = assembler::il2cpp::string_new(world_info[0]);
	fields.asset_url = assembler::il2cpp::string_new(world_info[1]);

	// VMProtectEnd();

	return genuine_f(callback, new_world, a3, a4);
}

void detours::hk_onmenuclose(assembler::ui_manager_impl* _this, const bool a2)
{
	static auto& instance = get();
	static auto genuine_f = instance.fetch_hook(SECSTR("UIManagerImpl::OnMenuClose")).detour.get_original<decltype(&hk_onmenuclose)>();

	if (config::get<bool>(g_context.quickmenu_persistence))
	{
		if (instance.is_quickmenu_open_)
			return;
	}
	else
	{
		instance.is_quickmenu_open_ = false;
		instance.quickmenu_safety_check_ = false;
	}

	genuine_f(_this, a2);
}

void detours::hk_onmenuopen(assembler::ui_manager_impl* _this, const bool a2)
{
	static auto& instance = get();
	static auto genuine_f = instance.fetch_hook(SECSTR("UIManagerImpl::OnMenuOpen")).detour.get_original<decltype(&hk_onmenuopen)>();

	if (config::get<bool>(g_context.quickmenu_persistence))
	{
		instance.quickmenu_safety_check_ = true;
		instance.is_quickmenu_open_ = true;
	}

	genuine_f(_this, a2);
}

void detours::hk_onflowpage(assembler::il2cpp::il2cpp_object* _this, const bool a2)
{
	static auto& instance = get();
	static auto genuine_f = instance.fetch_hook(SECSTR("VRCUiPage::OnFlowPage")).detour.get_original<decltype(&hk_onflowpage)>();

	if (instance.is_quickmenu_open_ && a2 && assembler::room_manager::get_class()->static_fields->world)
	{
		instance.is_quickmenu_open_ = false;
		hk_onmenuclose(assembler::ui_manager_impl::instance(), false);
	}

	return genuine_f(_this, a2);
}

void detours::hk_onvrcuimanager_place(assembler::unity_engine::component* _this, const bool a2, const bool a3)
{
	static auto& instance = get();
	static auto genuine_f = instance.fetch_hook(SECSTR("VRCUIManager::Place")).detour.get_original<decltype(&hk_onvrcuimanager_place)>();

	if (!assembler::unity_engine::xrdevice::get_is_present() || !config::get<bool>(g_context.cozyvrmenu))
		return genuine_f(_this, a2, a3);

	const auto tracking_manager = assembler::vrc_tracking_manager::instance();
	float x_pos = tracking_manager ? tracking_manager->get_transform()->get_local_scale().x : 1.f;

	if (x_pos <= 0.f)
		x_pos = 1.f;

	const auto player_tracking_display = _this->get_transform();
	const auto unscaled_ui = player_tracking_display->find(xorstr_("UnscaledUI"));
	const auto camera_object = assembler::unity_engine::game_object::find(xorstr_("Camera (eye)"))->get_transform();
	player_tracking_display->set_position(camera_object->get_position());

	auto vec_euler = camera_object->get_rotation().to_eulerangles();
	vec_euler.x -= 30.f;
	vec_euler.z = 0.f;

	if (!assembler::vrc_player::get_current())
		vec_euler.x = vec_euler.z = 0.f;

	if (!a2)
		player_tracking_display->set_rotation(sdk::quaternion::from_eulerangles(vec_euler));

	else
	{
		const sdk::quaternion quat = sdk::quaternion::from_eulerangles(vec_euler);
		if (const auto display_rotation = player_tracking_display->get_rotation(); !(sdk::quaternion::angle(display_rotation, quat) < 15.f))
		{
			if (!(sdk::quaternion::angle(display_rotation, quat) < 25.f))
				player_tracking_display->set_rotation(sdk::quaternion::rotate_towards(display_rotation, quat, 5.f));
			else
				player_tracking_display->set_rotation(sdk::quaternion::rotate_towards(display_rotation, quat, 1.f));
		}
	}

	player_tracking_display->set_local_scale(x_pos >= 0.f ? sdk::vector(1.f, 1.f, 1.f) * x_pos : sdk::vector(1.f, 1.f, 1.f));
	unscaled_ui->set_local_scale(x_pos > FLT_EPSILON ? sdk::vector(1.f, 1.f, 1.f) * (1.f / x_pos) : sdk::vector(1.f, 1.f, 1.f));
}
#pragma endregion
