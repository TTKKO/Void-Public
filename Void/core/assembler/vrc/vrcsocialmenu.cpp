#include "vrcsocialmenu.hpp"
#include "playermanager.hpp"
#include "../../utilities/ingame_logging.hpp"
#include "../assembly-csharp/system/system_action.hpp"
#include "../../../utilities/button_api.hpp"

using namespace assembler::unity_engine;

assembler::vrc::core::api_user* assembler::vrc_player_menu::current_user()
{
	// @xref: private const string ǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅ = "UI.SelectedUser.UserActions";
	// @xref: private const string ǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅ = "UI.SelectedUser.PerUserInteraction";
	// @xref: private const string ǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅ = "UI.SelectedUser.InstanceModeratorActions";
	// @xref: private const string ǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅ = "UI.SelectedUser.DevTools";

	if (!selected_user_type)
		selected_user_type = il2cpp::get_type(xorstr_(L"ÎÌÍÍÎÏÍÏÌÎÌÎÏÎÍÍÌÏÍÏÌÏÌ, VRC.UI.Elements"));

	const auto selection_manager = user_selection_manager::instance();
	auto user = selection_manager->fields.apiuser2;

	if (!user)
	{
		user = vrc::core::api_user::get_current();
		const auto object = ui_manager_impl::instance()->get_quickmenu()->get_transform()->find(xorstr_("Container/Window/QMParent/Menu_SelectedUser_Local"));

		if (!object)
			return user;

		const auto comp = object->get_component(selected_user_type);

		if (!comp)
			return user;

		user = *reinterpret_cast<vrc::core::api_user**>(reinterpret_cast<std::uint8_t*>(*reinterpret_cast<il2cpp::il2cpp_object**>(reinterpret_cast<std::uint8_t*>(comp) + 0x140)) + 0x10);

		if (!user)
			user = vrc::core::api_user::get_current();
	}

	return user;
}

assembler::vrc::core::api_user* assembler::vrc_social_menu::current_user()
{
	return reinterpret_cast<vrc::core::api_user*>(get_field(reinterpret_cast<il2cpp::il2cpp_object*>(vrc_ui_page::get_page(xorstr_("UserInterface/MenuContent/Screens/UserInfo"))), xorstr_("VRC.Core.APIUser")));
}

transform* assembler::vrc_social_menu::create_button(const std::string& btn_text, const int btn_x_location, const int btn_y_location, const c_inline_detour* btn_action)
{
	const auto transform = instantiate_gameobject();

	if (!transform)
		return nullptr;

	transform->get_game_object()->set_name(xorstr_("VOID") + btn_text);
	transform->set_local_position(sdk::vector(static_cast<float>(btn_x_location), static_cast<float>(btn_y_location), 0));

	reinterpret_cast<ui::image*>(transform->find(xorstr_("Image"))->get_component(xorstr_("UnityEngine.UI.Image")))->set_color(sdk::color(0.701f, 0.258f, 0.96f, 1.f));
	reinterpret_cast<ui::text*>(transform->get_child(0)->get_child(0)->get_component(xorstr_("UnityEngine.UI.Text")))->set_text(btn_text);
	const auto btn = reinterpret_cast<ui::button*>(transform->get_component(xorstr_("UnityEngine.UI.Button")));

	btn->set_on_click(ui::button_clicked_event::ctor());
	btn->get_on_click()->add_listener(events::unity_action::ctor(btn_action));
	return transform;
}

transform* assembler::vrc_social_menu::instantiate_gameobject()
{
	const auto root = vrc_ui_manager::instance(); // TODO: delete VRCUIManager out of instance name
	const auto preinst = root->get_transform()->find(xorstr_("MenuContent/Screens/UserInfo/Buttons/RightSideButtons/RightUpperButtonColumn/EditBioButton"))->get_game_object();

	if (!preinst)
		return nullptr;

	const auto gameobject = reinterpret_cast<game_object*>(object::instantiate(preinst, vrc_ui_manager::instance()->get_transform()->find(xorstr_("MenuContent/Screens/UserInfo/User Panel/"))));
	return gameobject->get_transform();
}

bool assembler::vrc_social_menu::setup_buttons()
{
	/*
	x += 155
	y 550 is up
	y 625 is down
	*/
	//next: 320
	const auto teleportbtn = create_button(xorstr_("Teleport"), 110, -675, create_detour([=]
	{
		const auto current_selected_user = current_user();

		if (current_selected_user == nullptr)
			return;

		const auto player = vrc::player_manager::get_player(current_selected_user->get_id());

		if (current_selected_user->get_id() == vrc::core::api_user::get_current()->get_id())
			return;

		vrc::sdk_base::vrc_player_api::get_current()->teleport_to(player->get_vrc_player_api());
	}));

	if (!teleportbtn) 
		return false;
	social_buttons.push_back(teleportbtn);

	const auto dropportalbtn = create_button(xorstr_("Drop Portal"), 325, -675, create_detour([=]
	{
		const auto current_selected_user = current_user();

		if (current_selected_user == nullptr)
			return;

		if (moderation_manager::instance()->check_moderation(current_selected_user->fields.id, moderation_manager::moderation_type::block))
			return;

		if (const auto location = current_selected_user->get_location(); location != xorstr_("private") && location.contains("wrld_"))
			misc::drop_portal(location);
	}));

	if (!dropportalbtn) 
		return false;
	social_buttons.push_back(dropportalbtn);

	const auto downloadiconbtn = create_button(xorstr_("Download Icon"), 540, -675, create_detour([=]
	{
		const auto current_selected_user = current_user();

		if (current_selected_user == nullptr)
			return;

		logging::push(FOREGROUND_INTENSE_WHITE);
		logging::add_log("[notice] beginning icon download...\n");
		logging::pop();

		ingame_logging::get().log(xorstr_("[<color=#a75cf6>notice</color>] beginning icon download..."));

		std::thread([=]
		{
			if (misc::curl_downloadfile(current_selected_user->get_usericon().c_str(), current_selected_user->get_id() + xorstr_(".png")))
			{
				logging::push(FOREGROUND_INTENSE_GREEN);
				logging::add_log("[notice] download completed.\n");
				logging::pop();
				ingame_logging::get().log(xorstr_("[<color=#a75cf6>notice</color>] download completed."));
			}
			else
			{
				logging::push(FOREGROUND_INTENSE_RED);
				logging::add_log("[notice] download failed.\n");
				logging::pop();
				ingame_logging::get().log(xorstr_("[<color=#a75cf6>notice</color>] download failed."));
			}
		}).detach();
	}));

	if (!downloadiconbtn)
		return false;
	social_buttons.push_back(downloadiconbtn);

	return true;
}

void assembler::vrc_social_menu::restore()
{
	for (const auto& fst : social_buttons)
	{
		object::destroy(fst->get_game_object());
		//delete snd;
	}
}

bool assembler::vrc_player_menu::setup_buttons()
{
	const auto pos = ui_manager_impl::instance()->get_quickmenu()->get_transform()->find(xorstr_("Container/Window/QMParent/Menu_SelectedUser_Local/ScrollRect/Viewport/VerticalLayoutGroup"));
	const auto void_header = static_cast<transform*>(object::instantiate(pos->find(xorstr_("QM_Foldout_UserActions")), pos, true));

	if (!void_header)
		return false;

	void_header->set_name(xorstr_("VOID_ACTIONS"));
	const auto text = reinterpret_cast<tmpro::tmp_text*>(void_header->find(xorstr_("Label"))->get_component(xorstr_("TMPro.TextMeshProUGUI")));
	text->set_text(xorstr_("VOID Actions"));
	text->set_color(sdk::color(0.701f, 0.259f, 0.96f, 1.f));

	const auto void_buttons = static_cast<game_object*>(object::instantiate(pos->find(xorstr_("Buttons_UserActions")), pos, true));

	if (!void_buttons)
		return false;

	void_buttons->set_name(xorstr_("VOID_BUTTON_ACTIONS"));
	const auto button_actions = pos->find(xorstr_("VOID_BUTTON_ACTIONS"))->get_transform();

	for (std::size_t i = 0; i < static_cast<std::size_t>(button_actions->child_count()); i++)
		object::destroy(button_actions->get_child(static_cast<int>(i))->get_game_object());

	init_buttons(xorstr_("Container/Window/QMParent/Menu_SelectedUser_Local/ScrollRect/Viewport/VerticalLayoutGroup/VOID_BUTTON_ACTIONS"));
	return true;
}

void assembler::vrc_player_menu::init_buttons(const std::string_view loc)
{
	auto safety_modules2 = std::make_unique<single_button>(loc, 120, 0, 0, xorstr_("<color=#a75cf6>Force Clone</color>"), []
	{
		const auto user = current_user();
		if (user == nullptr)
			return;

		const auto player = vrc::player_manager::get_player(user->get_id());

		if (!player)
			return;

		if (player->get_vrc_player()->get_api_avatar()->get_release_status() == xorstr_("private"))
			return;

		g_context.changing_avatar = player->get_vrc_player()->get_api_avatar()->get_id();
	}, xorstr_("Force clones the player's avatar."));

	safety_modules2->set_active(true);
	player_menu_buttons.push_back(std::move(safety_modules2));

	auto safety_modules3 = std::make_unique<single_button>(loc, 130, 0, 0, xorstr_("<color=#a75cf6>Block ALL Events</color>"), []
	{
		const auto user = current_user();

		if (user == nullptr)
			return;

		const auto id = user->get_id();

		if (const auto v = &config::get<std::vector<std::string>>(g_context.user_event_blacklist); std::ranges::find(*v, id) == v->end())
			v->push_back(id);
		else
			std::erase(*v, id);
	}, xorstr_("Blocks EVERY single event sent by this player."));

	safety_modules3->set_active(true);
	player_menu_buttons.push_back(std::move(safety_modules3));

	auto safety_modules4 = std::make_unique<single_button>(loc, 140, 0, 0, xorstr_("<color=#a75cf6>Blacklist Avatar</color>"), []
	{
		const auto user = current_user();
		if (user == nullptr)
			return;

		const auto player = vrc::player_manager::get_player(user->get_id());

		if (!player)
			return;

		const auto apiavatar = player->get_vrc_player()->get_api_avatar();
		const auto id = apiavatar->get_id();

		const auto wl_v = &config::get<std::vector<std::string>>(g_context.avatar_whitelist);
		if (const auto wl_position = std::ranges::find(*wl_v, id); wl_position != wl_v->end())
			wl_v->erase(wl_position);

		const auto bl_v = &config::get<std::vector<std::string>>(g_context.avatar_blacklist);
		if (const auto bl_position = std::ranges::find(*bl_v, id); bl_position == bl_v->end())
		{
			logging::push(FOREGROUND_INTENSE_CYAN);
			logging::add_log(xorstr_("[log] blacklisted \"{}\" by \"{}\" [{}]\n"), apiavatar->get_name(), apiavatar->get_author_name(), id);
			logging::pop();
			ingame_logging::get().log(xorstr_("[<color=#a75cf6>log</color>] blacklisted avatar"));
			bl_v->push_back(id);
		}

		else
		{
			logging::push(FOREGROUND_INTENSE_CYAN);
			logging::add_log(xorstr_("[log] unblacklisted \"{}\" by \"{}\" [{}]\n"), apiavatar->get_name(), apiavatar->get_author_name(), id);
			logging::pop();
			ingame_logging::get().log(xorstr_("[<color=#a75cf6>log</color>] unblacklisted avatar"));
			bl_v->erase(bl_position);
		}

		misc::remove_avatar_from_cache(id);
		player->get_vrc_player()->load_avatar(true);
	}, xorstr_("Blacklists this player's avatar."));
	safety_modules4->set_active(true);
	player_menu_buttons.push_back(std::move(safety_modules4));

	auto safety_modules3_5 = std::make_unique<single_button>(loc, 140, 0, 0, xorstr_("<color=#a75cf6>Whitelist Avatar</color>"), []
	{
		const auto user = current_user();

		if (user == nullptr)
			return;

		const auto player = vrc::player_manager::get_player(user->get_id());

		if (!player)
			return;

		const auto apiavatar = player->get_vrc_player()->get_api_avatar();
		const auto id = apiavatar->get_id();

		const auto bl_v = &config::get<std::vector<std::string>>(g_context.avatar_blacklist);
		if (const auto bl_position = std::ranges::find(*bl_v, id); bl_position != bl_v->end())
			bl_v->erase(bl_position);

		const auto wl_v = &config::get<std::vector<std::string>>(g_context.avatar_whitelist);
		if (const auto wl_position = std::ranges::find(*wl_v, id); wl_position == wl_v->end())
		{
			logging::push(FOREGROUND_INTENSE_CYAN);
			logging::add_log(xorstr_("[log] whitelisted \"{}\" by \"{}\" [{}]\n"), apiavatar->get_name(), apiavatar->get_author_name(), id);
			logging::pop();
			ingame_logging::get().log(xorstr_("[<color=#a75cf6>log</color>] whitelisted avatar"));
			wl_v->push_back(id);
		}

		else
		{
			logging::push(FOREGROUND_INTENSE_CYAN);
			logging::add_log(xorstr_("[log] unwhitelisted \"{}\" by \"{}\" [{}]\n"), apiavatar->get_name(), apiavatar->get_author_name(), id);
			logging::pop();
			ingame_logging::get().log(xorstr_("[<color=#a75cf6>log</color>] unwhitelisted avatar"));
			wl_v->erase(wl_position);
		}

		misc::remove_avatar_from_cache(id);
		player->get_vrc_player()->load_avatar(true);
	}, xorstr_("Whitelists this player's avatar."));

	safety_modules3_5->set_active(true);
	player_menu_buttons.push_back(std::move(safety_modules3_5));

	auto safety_modules5 = std::make_unique<single_button>(loc, 160, 0, 0, xorstr_("<color=#a75cf6>Copy Avatar ID</color>"), []
	{
		const auto user = current_user();
		if (user == nullptr)
			return;

		const auto player = vrc::player_manager::get_player(user->get_id());

		if (!player)
			return;

		const std::string id = player->get_vrc_player()->get_api_avatar()->get_id();
		utility::set_clipboard(id);
	}, xorstr_("Copy's this player's Avatar ID."));

	safety_modules5->set_active(true);
	player_menu_buttons.push_back(std::move(safety_modules5));

	auto safety_modules6 = std::make_unique<single_button>(loc, 170, 0, 0, xorstr_("<color=#a75cf6>Copy USpeak Data</color>"), []
	{
		const auto user = current_user();
		if (user == nullptr)
			return;

		const auto player = vrc::player_manager::get_player(user->get_id());

		if (!player)
			return;

		if (config::get<int>(g_context.copy_event1) == player->get_photon_id())
			config::get<int>(g_context.copy_event1) = NULL;
		else
			config::get<int>(g_context.copy_event1) = player->get_photon_id();
	}, xorstr_("Copy's this player's USpeak Data."));

	safety_modules6->set_active(true);
	player_menu_buttons.push_back(std::move(safety_modules6));

	auto safety_modules7 = std::make_unique<single_button>(loc, 170, 0, 0, xorstr_("<color=#a75cf6>Download Avatar</color>"), []
	{
		const auto user = current_user();

		if (user == nullptr)
			return;

		const auto player = vrc::player_manager::get_player(user->get_id());

		if (!player)
			return;

		logging::push(FOREGROUND_INTENSE_WHITE);
		logging::add_log(xorstr_("[notice] beginning avatar download...\n"));
		logging::pop();

		ingame_logging::get().log(xorstr_("[<color=#a75cf6>notice</color>] beginning avatar download..."));
		const auto apiavatar = player->get_vrc_player()->get_api_avatar();

		std::thread([=]
		{
			if (misc::curl_downloadfile(apiavatar->get_asset_url().c_str(), apiavatar->get_id() + xorstr_(".vrca")))
			{
				logging::push(FOREGROUND_INTENSE_GREEN);
				logging::add_log("[notice] download completed.\n");
				logging::pop();
				ingame_logging::get().log(xorstr_("[<color=#a75cf6>notice</color>] download completed."));
			}
			else
			{
				logging::push(FOREGROUND_INTENSE_RED);
				logging::add_log("[notice] download failed.\n");
				logging::pop();
				ingame_logging::get().log(xorstr_("[<color=#a75cf6>notice</color>] download failed."));
			}
		}).detach();
	}, xorstr_("Downloads this player's avatar VRCA."));

	safety_modules7->set_active(true);
	player_menu_buttons.push_back(std::move(safety_modules7));

	auto teleportpickupsbtn = std::make_unique<single_button>(loc, 180, 0, 0, xorstr_("<color=#a75cf6>Teleport Pickups</color>"), []
	{
		const auto user = current_user();

		if (user == nullptr)
			return;

		const auto player = vrc::player_manager::get_player(user->get_id());

		if (!player)
			return;

		misc::teleport_pickups(player->get_vrc_player()->get_transform()->get_position());
	}, xorstr_("Teleports all pickups to the player."));

	teleportpickupsbtn->set_active(true);
	player_menu_buttons.push_back(std::move(teleportpickupsbtn));

	auto attachplayerbtn = std::make_unique<single_button>(loc, 190, 0, 0, xorstr_("<color=#a75cf6>Player Attach</color>"), []
	{
		if (!g_context.player_attach)
		{
			const auto user = current_user();

			if (user == nullptr)
				return;

			const auto userid = user->get_id();

			if (userid == vrc::core::api_user::get_current()->get_id())
				return;

			const auto player = vrc::player_manager::get_player(userid);

			if (!player)
				return;

			if (player != nullptr || player->get_photon_id() != vrc::player::get_current()->get_photon_id())
			{
				g_context.player_attach_id = player->get_photon_id();
				g_context.player_attach = true;
			}

			else if (g_context.player_attach_id)
				g_context.player_attach_id = false;
		}
		else
		{
			g_context.player_attach_id = 0;
			g_context.player_attach = false;
		}
	}, xorstr_("Attaches you to the selected player's head."));

	attachplayerbtn->set_active(true);
	player_menu_buttons.push_back(std::move(attachplayerbtn));

	auto teleportbtn = std::make_unique<single_button>(loc, 200, 1, 0, xorstr_("<color=#a75cf6>Teleport</color>"), []
	{
		const auto current_selected_user = current_user();

		if (current_selected_user == nullptr)
			return;

		const auto player = vrc::player_manager::get_player(current_selected_user->get_id());

		if (current_selected_user->get_id() == vrc::core::api_user::get_current()->get_id())
			return;

		vrc::sdk_base::vrc_player_api::get_current()->teleport_to(player->get_vrc_player_api());
	}, xorstr_("Teleports you to the selected player."));

	teleportbtn->set_active(true);
	player_menu_buttons.push_back(std::move(teleportbtn));
}

void assembler::vrc_player_menu::restore()
{
	const auto pos = ui_manager_impl::instance()->get_quickmenu()->get_transform()->find(xorstr_("Container/Window/QMParent/Menu_SelectedUser_Local/ScrollRect/Viewport/VerticalLayoutGroup"));
	const auto header = pos->find(xorstr_("VOID_BUTTON_ACTIONS"))->get_game_object();
	const auto column = pos->find(xorstr_("VOID_ACTIONS"))->get_game_object();

	object::destroy(header);
	object::destroy(column);

	for (const auto& button : player_menu_buttons)
	{
		object::destroy(button->button);
	}
}
