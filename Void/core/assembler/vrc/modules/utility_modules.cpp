#include "utility_modules.hpp"

void utility_modules::setup()
{
	auto copyroombtn = std::make_unique<single_button>(location_, 7010, 0, 0, xorstr_("<color=#a75cf6>Copy World ID</color>"), []
	{
		utility::set_clipboard(assembler::room_manager::get_room_id());
	}, xorstr_("Copies your current world ID to your clipboard"));
	copyroombtn->set_active(false);
	single_buttons_.push_back(std::move(copyroombtn));

	auto joinroombtn = std::make_unique<single_button>(location_, 7020, 1, 0, xorstr_("<color=#a75cf6>Join Copied World ID</color>"), []
	{
		g_context.room_id = utility::get_clipboard();
	}, xorstr_("Joins the current World ID on your clipboard."));
	joinroombtn->set_active(false);
	single_buttons_.push_back(std::move(joinroombtn));

	auto changebtn = std::make_unique<single_button>(location_, 7030, 2, 0, xorstr_("<color=#a75cf6>Clone Copied Avatar ID</color>"), []
	{
		const auto clipboard = utility::get_clipboard();

		if (!clipboard.starts_with(xorstr_("avtr_")))
			return;

		g_context.changing_avatar = clipboard;
	}, xorstr_("Changes your Avatar to the Avatar ID on your clipboard."));
	changebtn->set_active(false);
	single_buttons_.push_back(std::move(changebtn));

	auto stopuspeakbtn = std::make_unique<single_button>(location_, 7040, 3, 0, xorstr_("<color=#a75cf6>Force Stop Copying USpeak</color>"), [] { config::get<int>(g_context.copy_event1) = NULL; }, xorstr_("Force stops copying USpeak Data from all players."));
	stopuspeakbtn->set_active(false);
	single_buttons_.push_back(std::move(stopuspeakbtn));

	auto blacklistbtn = std::make_unique<single_button>(location_, 7050, 0, -1, xorstr_("<color=#a75cf6>Blacklist Copied Avatar ID</color>"), []
	{
		const auto clipboard = utility::get_clipboard();
		if (!clipboard.starts_with(xorstr_("avtr_")))
			return;

		const auto wl_v = &config::get<std::vector<std::string>>(g_context.avatar_whitelist);
		if (const auto wl_position = std::ranges::find(*wl_v, clipboard); wl_position != wl_v->end())
			wl_v->erase(wl_position);

		const auto bl_v = &config::get<std::vector<std::string>>(g_context.avatar_blacklist);
		if (const auto bl_position = std::ranges::find(*bl_v, clipboard); bl_position == bl_v->end())
		{
			logging::push(FOREGROUND_INTENSE_CYAN);
			logging::add_log(xorstr_("[log] blacklisted [{}]\n"), clipboard);
			logging::pop();
			ingame_logging::get().log(xorstr_("[<color=#a75cf6>log</color>] blacklisted avatar id"));
			bl_v->push_back(clipboard);
		}
		else
		{
			logging::push(FOREGROUND_INTENSE_CYAN);
			logging::add_log(xorstr_("[log] unblacklisted [{}]\n"), clipboard);
			logging::pop();
			ingame_logging::get().log(xorstr_("[<color=#a75cf6>log</color>] unblacklisted avatar id"));
			bl_v->erase(bl_position);
		}

		misc::remove_avatar_from_cache(clipboard);
		assembler::vrc_player::get_current()->load_all_avatars();
	}, xorstr_("(un)blacklists the avatar id on your clipboard."));

	blacklistbtn->set_active(false);
	single_buttons_.push_back(std::move(blacklistbtn));

	auto whitelistbtn = std::make_unique<single_button>(location_, 7060, 1, -1, xorstr_("<color=#a75cf6>Whitelist Copied Avatar ID</color>"), []
	{
		const auto clipboard = utility::get_clipboard();
		if (!clipboard.starts_with(xorstr_("avtr_")))
			return;

		const auto bl_v = &config::get<std::vector<std::string>>(g_context.avatar_blacklist);
		if (const auto bl_position = std::ranges::find(*bl_v, clipboard); bl_position != bl_v->end())
			bl_v->erase(bl_position);

		const auto wl_v = &config::get<std::vector<std::string>>(g_context.avatar_whitelist);
		if (const auto wl_position = std::ranges::find(*wl_v, clipboard); wl_position == wl_v->end())
		{
			logging::push(FOREGROUND_INTENSE_CYAN);
			logging::add_log(xorstr_("[log] whitelisted [{}]\n"), clipboard);
			logging::pop();
			ingame_logging::get().log(xorstr_("[<color=#a75cf6>log</color>] whitelisted avatar id"));
			wl_v->push_back(clipboard);
		}
		else
		{
			logging::push(FOREGROUND_INTENSE_CYAN);
			logging::add_log(xorstr_("[log] unwhitelisted [{}]\n"), clipboard);
			logging::pop();
			ingame_logging::get().log(xorstr_("[<color=#a75cf6>log</color>] unwhitelisted avatar id"));
			wl_v->erase(wl_position);
		}

		misc::remove_avatar_from_cache(clipboard);
		assembler::vrc_player::get_current()->load_all_avatars();
	}, xorstr_("(un)whitelists the avatar id on your clipboard."));

	whitelistbtn->set_active(false);
	single_buttons_.push_back(std::move(whitelistbtn));

	auto exportfriendsbtn = std::make_unique<single_button>(location_, 7070, 2, -1, xorstr_("<color=#a75cf6>Export Friends</color>"), []
	{
		if (!helpers::friend_tool::export_friends(assembler::il2cpp::array_to_vector<assembler::il2cpp::il2cpp_string*>(assembler::vrc::core::api_user::get_friends())))
		{
			logging::push(FOREGROUND_INTENSE_RED);
			logging::add_log(xorstr_("[critical] failed to export friends.\n"));
			logging::pop();
			ingame_logging::get().log(xorstr_("[<color=#a75cf6>critical</color>] failed to export friends."));
		}
		else
		{
			logging::push(FOREGROUND_INTENSE_WHITE);
			logging::add_log(xorstr_("[notice] exported friends to %appdata%\\Void\\exports.\n"));
			logging::pop();
			ingame_logging::get().log(xorstr_(R"([<color=#a75cf6>notice</color>] exported friends to %appdata%\Void\exports.)"));
		}
	}, xorstr_("Exports friend list to be imported on another account in the future."));

	exportfriendsbtn->set_active(false);
	single_buttons_.push_back(std::move(exportfriendsbtn));

	auto importfriendsbtn = std::make_unique<single_button>(location_, 7080, 3, -1, xorstr_("<color=#a75cf6>Import Friends</color>"), []
	{
		if (!helpers::friend_tool::get().import_friends())
		{
			logging::push(FOREGROUND_INTENSE_RED);
			logging::add_log(xorstr_("[critical] failed to import friends.\n"));
			logging::pop();
			ingame_logging::get().log(xorstr_("[<color=#a75cf6>critical</color>] failed to import friends."));
		}
		else
		{
			if (!helpers::friend_tool::get().start_load_task())
			{
				logging::push(FOREGROUND_INTENSE_RED);
				logging::add_log(xorstr_("[notice] the import system is already running.\n"));
				logging::pop();
				ingame_logging::get().log(xorstr_("[<color=#a75cf6>notice</color>] the import system is already running."));
			}
			else
			{
				logging::push(FOREGROUND_INTENSE_WHITE);
				logging::add_log(xorstr_("[notice] import started at a rate of 60/hour\n"));
				logging::pop();
				ingame_logging::get().log(xorstr_("[<color=#a75cf6>notice</color>] import started at a rate of 60/hour"));

				if (!xs_overlay::get().send(xorstr_("[notice] import started at a rate of 60/hour"), xorstr_(""), xorstr_("default"), 3))
				{
					logging::push(FOREGROUND_INTENSE_RED);
					logging::print(xorstr_("[critical] failed to talk to xs-overlay api [{}]\n"), xs_overlay::get().fetch_last_error());
					logging::pop();
				}
			}
		}
	}, xorstr_("Imports friend list and sends each user a friend request. This works at a rate of 60 an hour."));

	importfriendsbtn->set_active(false);
	single_buttons_.push_back(std::move(importfriendsbtn));

	auto worldvirtualizationbtn = std::make_unique<toggle_button>(location_, 7090, 0, -3, xorstr_("<color=#a75cf6>World\r\nVirtualization</color>"), []
	{
		if (!config::get<bool>(g_context.virtualize_world))
		{
			config::get<bool>(g_context.virtualize_world) = true;
		}
	}, []
	{
		if (config::get<bool>(g_context.virtualize_world))
		{
			config::get<bool>(g_context.virtualize_world) = false;
		}
	}, xorstr_("Virtualizes your world locally."));

	worldvirtualizationbtn->set_active(false);
	toggle_buttons_.push_back(std::move(worldvirtualizationbtn));

	auto setworldbtn = std::make_unique<single_button>(location_, 7100, 1, -3, xorstr_("<color=#a75cf6>Set As\r\nVirtualized\r\nWorld</color>"), []
	{
		if (const auto world = assembler::room_manager::get_class()->static_fields->world)
		{
			auto id = world->get_id() + xorstr_(":::");
			id.append(world->asset_url());
			config::get<std::string>(g_context.base_virtualization) = id;

			logging::push(FOREGROUND_INTENSE_GREEN);
			logging::add_log(xorstr_("[notice] set virtualized world to \"{}\"\n"), s_chars(world->fields.name));
			logging::pop();
			ingame_logging::get().log(xorstr_("[<color=#a75cf6>notice</color>] set virtualized world to \"{}\""), s_chars(world->fields.name));
		}
		else
		{
			logging::push(FOREGROUND_INTENSE_RED);
			logging::add_log(xorstr_("[critical] failed to set virtualized world.\n"));
			logging::pop();
			ingame_logging::get().log(xorstr_("[<color=#a75cf6>critical</color>] failed to set virtualized world."));
		}
	}, xorstr_("Sets the world in which void will use as a base when virtualized."));

	setworldbtn->set_active(false);
	single_buttons_.push_back(std::move(setworldbtn));
}

void utility_modules::show_all() const
{
	toggle_buttons_[0]->trigger(config::get<bool>(g_context.virtualize_world));

	main_modules::get().show_back();
	show();
}
