#include "config_modules.hpp"

void config_modules::setup()
{
	auto autoinjectbtn = std::make_unique<single_button>(location_, 3110, 0, 0,xorstr_("<color=#a75cf6>Autoload\r\nVOID</color>"), []
	{
		if (!config::toggle_autoload())
		{
			logging::push(FOREGROUND_INTENSE_RED);
			logging::add_log(xorstr_(
				"[error] Failed to (un)setup Void's autoloader\n"));
			logging::pop();
		}
	}, xorstr_("Sets up Void's autoinjection system."));
	autoinjectbtn->set_active(false);
	single_buttons_.push_back(std::move(autoinjectbtn));

	auto saveconfigbtn = std::make_unique<single_button>(location_, 3120, 1, 0, xorstr_("<color=#a75cf6>Save\r\nConfig</color>"), []
	{
		if (!config::save(xorstr_("config.void")))
		{
			logging::push(FOREGROUND_RED);
			logging::print(xorstr_("[error] failed to save \"{}\" config\n"), xorstr_("config.void"));
			logging::pop();
		}
	}, xorstr_("Saves your current configuration."));
	saveconfigbtn->set_active(false);
	single_buttons_.push_back(std::move(saveconfigbtn));

	auto loadconfigbtn = std::make_unique<single_button>(location_, 3130, 2, 0, xorstr_("<color=#a75cf6>Load\r\nConfig</color>"), []
	{
		if (!config::load(xorstr_("config.void")))
		{
			logging::push(FOREGROUND_RED);
			logging::print(xorstr_("[error] failed to load \"{}\" config\n"), xorstr_("config.void"));
			logging::pop();
		}
		else misc::load_config();
	}, xorstr_("Loads your configuration file."));
	loadconfigbtn->set_active(false);
	single_buttons_.push_back(std::move(loadconfigbtn));

	auto discordrpcbtn = std::make_unique<toggle_button>(location_, 3140, 3, 0, xorstr_("<color=#a75cf6>DiscordRPC</color>"), []
	{
		if (!config::get<bool>(g_context.discord_rpc_toggle))
		{
			config::get<bool>(g_context.discord_rpc_toggle) = true;
			g_context.g_discord = std::make_unique<discord_sdk>();
		}
	}, []
	{
		if (config::get<bool>(g_context.discord_rpc_toggle))
		{
			config::get<bool>(g_context.discord_rpc_toggle) = false;
			g_context.g_discord.reset();
		}
	}, xorstr_(
		"VOID Discord RPC integration, this will respect your VRC status."));
	discordrpcbtn->set_active(false);
	toggle_buttons_.push_back(std::move(discordrpcbtn));

	auto xsoverlaybtn = std::make_unique<toggle_button>(location_, 3140, 0, -1,xorstr_("<color=#a75cf6>XS-Overlay Integration</color>"), []
	{
		if (!config::get<bool>(g_context.xs_overlay_toggle))
		{
			config::get<bool>(g_context.xs_overlay_toggle) = true;

			try
			{
				if (!xs_overlay::get().is_connected())
				{
					if (!xs_overlay::get().initialize())
						throw std::runtime_error(utility::format(xorstr_("failed to initialize xs-overlay api [{}]"), xs_overlay::get().fetch_last_error()));

					logging::push(FOREGROUND_INTENSE_GREEN);
					logging::print(xorstr_("[xs-overlay] successfully connected to api\n"));
					logging::pop();
				}
			}
			catch (const std::exception& e)
			{
				logging::push(FOREGROUND_INTENSE_RED);
				logging::print(xorstr_("[critical] {}\n"), e.what());
				logging::pop();

				xs_overlay::get().shutdown();
				config::get<bool>(g_context.xs_overlay_toggle) = false;
			}
		}
	}, []
	{
		if (config::get<bool>(g_context.xs_overlay_toggle))
		{
			config::get<bool>(g_context.xs_overlay_toggle) = false;
			if (xs_overlay::get().shutdown())
			{
				logging::push(FOREGROUND_YELLOW);
				logging::print(xorstr_("[xs-overlay] successfully disconnected from api\n"));
				logging::pop();
			}
		}
	}, xorstr_("Integrates Void's notifications with XS-Overlay's Notification API"));

	xsoverlaybtn->set_active(false);
	toggle_buttons_.push_back(std::move(xsoverlaybtn));

	auto playerlistbtn = std::make_unique<toggle_button>(location_, 3150, 1, -1, xorstr_("<color=#a75cf6>QuickMenu\r\nPlayer List</color>"), []
	{
		if (!config::get<bool>(g_context.player_list_toggle))
		{
			config::get<bool>(g_context.player_list_toggle) = true;
		}
	}, []
	{
		if (config::get<bool>(g_context.player_list_toggle))
		{
			config::get<bool>(g_context.player_list_toggle) = false;

			if (const auto player_text =
					assembler::ui_manager_impl::instance()->get_quickmenu()
					                                      ->
					                                      get_transform()->find(xorstr_("Container/VOIDPLAYERLIST"));
				player_text != nullptr)
				assembler::unity_engine::object::destroy(player_text->get_game_object());
			if (const auto player_text =
					assembler::ui_manager_impl::instance()->get_quickmenu()
					                                      ->
					                                      get_transform()->find(xorstr_("Container/VOIDPLAYERLISTSHADOW"));
				player_text
				!= nullptr)
				assembler::unity_engine::object::destroy(player_text->get_game_object());
			if (const auto player_text =
					assembler::ui_manager_impl::instance()->get_quickmenu()
					                                      ->
					                                      get_transform()->find(xorstr_("Container/VOIDPANEL"));
				player_text != nullptr)
				assembler::unity_engine::object::destroy(player_text->get_game_object());
		}
	}, xorstr_("Toggles the QuickMenu playerlist."));

	playerlistbtn->set_active(false);
	toggle_buttons_.push_back(std::move(playerlistbtn));

	auto vrdebugbtn = std::make_unique<toggle_button>(location_, 3160, 2, -1,xorstr_("<color=#a75cf6>QuickMenu\r\nDebug Log</color>"), []
	{
		try
		{
			if (!config::get<bool>(g_context.qm_debug_log))
			{
				config::get<bool>(g_context.qm_debug_log) = true;
				if (!assembler::vrc_quick_menu::init_vr_debug())
					throw std::runtime_error(
						xorstr_(
							"failed to initialize vr debug menu. couldn't find components required"));
			}
		}
		catch (const std::exception& ex)
		{
			logging::push(FOREGROUND_INTENSE_RED);
			logging::print(xorstr_("[critical] {}\n"), ex.what());
			logging::pop();
		}
	}, []
	{
		try
		{
			if (config::get<bool>(g_context.qm_debug_log))
			{
				config::get<bool>(g_context.qm_debug_log) = false;

				if (!assembler::vrc_quick_menu::restore_vr_debug())
					throw std::runtime_error(xorstr_("failed to restore vr debug menu. couldn't find void's components."));
			}
		}
		catch (const std::exception& ex)
		{
			logging::push(FOREGROUND_INTENSE_RED);
			logging::print(xorstr_("[critical] {}\n"), ex.what());
			logging::pop();
		}
	}, xorstr_("Toggles the QuickMenu debug log."));

	vrdebugbtn->set_active(false);
	toggle_buttons_.push_back(std::move(vrdebugbtn));

	auto customplatesbtn = std::make_unique<toggle_button>(location_, 3170, 2, -2,xorstr_("<color=#a75cf6>Custom Plates</color>"), []
	{
		if (!config::get<bool>(g_context.custom_plates))
		{
			config::get<bool>(g_context.custom_plates) = true;
		}
	}, []
	{
		if (config::get<bool>(g_context.custom_plates))
		{
			config::get<bool>(g_context.custom_plates) = false;
		}
	}, xorstr_("Toggles Void's custom nameplates."));

	customplatesbtn->set_active(false);
	toggle_buttons_.push_back(std::move(customplatesbtn));

	auto joinnotifierbtn = std::make_unique<toggle_button>(location_, 3180, 0, -2,xorstr_("<color=#a75cf6>Join Notifier</color>"), []
	{
		if (!config::get<bool>(g_context.join_notify))
		{
			config::get<bool>(g_context.join_notify) = true;
		}
	}, []
	{
		if (config::get<bool>(g_context.join_notify))
		{
			config::get<bool>(g_context.join_notify) = false;
		}
	}, xorstr_("Sends logs and a HUD message when a player joins/leaves."));

	joinnotifierbtn->set_active(false);
	toggle_buttons_.push_back(std::move(joinnotifierbtn));

	auto nameplateinfobtn = std::make_unique<toggle_button>(location_, 3190, 3, -2,xorstr_("<color=#a75cf6>Nameplate Info</color>"), []
	{
		if (!config::get<bool>(g_context.nameplate_info))
		{
			config::get<bool>(g_context.nameplate_info) = true;
		}
	}, []
	{
		if (config::get<bool>(g_context.nameplate_info))
		{
			config::get<bool>(g_context.nameplate_info) = false;

			const auto v = assembler::il2cpp::array_to_vector<assembler::vrc::player*>(assembler::vrc::player_manager::get_players());
			for (auto it = v.cbegin(); it != v.cend(); ++it)
			{
				const auto np = (*it)->get_vrc_player()->get_name_plate()->get_transform();
				if (assembler::unity_engine::transform* info = np->find(xorstr_("Contents/VOIDINFO")))
					assembler::unity_engine::object::destroy(info->get_game_object());
			}
		}
	}, xorstr_("Renders player information below users nameplates."));

	nameplateinfobtn->set_active(false);
	toggle_buttons_.push_back(std::move(nameplateinfobtn));

	auto displayonlinebtn = std::make_unique<toggle_button>(location_, 3200, 1, -2, xorstr_("<color=#a75cf6>Display\r\nVoid Online</color>"), []
		{
			if (!config::get<bool>(g_context.display_online))
			{
				config::get<bool>(g_context.display_online) = true;
				if (const auto apiuser = assembler::vrc::core::api_user::get_current())
				{
					//connection_listener::get().refresh_activity(connection_listener::get_hwid(), apiuser->get_id(), config::get<bool>(g_context.display_online));
				}
			}
		}, []
		{
			if (config::get<bool>(g_context.display_online))
			{
				config::get<bool>(g_context.display_online) = false;
				if (const auto apiuser = assembler::vrc::core::api_user::get_current())
				{
					//connection_listener::get().refresh_activity(connection_listener::get_hwid(), apiuser->get_id(), config::get<bool>(g_context.display_online));
				}
			}
		}, xorstr_("When toggled off, other Void users will not be able to see you running Void."));

	displayonlinebtn->set_active(false);
	toggle_buttons_.push_back(std::move(displayonlinebtn));

	auto quickmenupersistencebtn = std::make_unique<toggle_button>(location_, 3210, 3, -1, xorstr_("<color=#a75cf6>QuickMenu\r\nPersistence</color>"), []
		{
			if (!config::get<bool>(g_context.quickmenu_persistence))
			{
				config::get<bool>(g_context.quickmenu_persistence) = true;
			}
		}, []
		{
			if (config::get<bool>(g_context.quickmenu_persistence))
			{
				config::get<bool>(g_context.quickmenu_persistence) = false;
			}
		}, xorstr_("Stops your QuickMenu from closing on it's own when you move."));
	quickmenupersistencebtn->set_active(false);
	toggle_buttons_.push_back(std::move(quickmenupersistencebtn));
}

void config_modules::show_all() const
{
	main_modules::get().show_back();
	show();

	toggle_buttons_[0]->trigger(config::get<bool>(g_context.discord_rpc_toggle));
	toggle_buttons_[1]->trigger(config::get<bool>(g_context.xs_overlay_toggle));
	toggle_buttons_[2]->trigger(config::get<bool>(g_context.player_list_toggle));
	toggle_buttons_[3]->trigger(config::get<bool>(g_context.qm_debug_log));
	toggle_buttons_[4]->trigger(config::get<bool>(g_context.custom_plates));
	toggle_buttons_[5]->trigger(config::get<bool>(g_context.join_notify));
	toggle_buttons_[6]->trigger(config::get<bool>(g_context.nameplate_info));
	toggle_buttons_[7]->trigger(config::get<bool>(g_context.display_online));
	toggle_buttons_[8]->trigger(config::get<bool>(g_context.quickmenu_persistence));
}

void config_modules::hide_all() const
{
	hide();
}
