#include "vrcquickmenu.hpp"
#include "../unityengine/texture_2d.hpp"
#include "../assembly-csharp/system/buffer.hpp"
#include "modules/main_modules.hpp"

using namespace assembler::unity_engine;

bool assembler::vrc_quick_menu::setup_buttons()
{
	/* - Replace Emoji Text - */
	//static_cast<ui::button*>(ui_manager_impl::instance()->get_transform()->find("ShortcutMenu/EmojiButton")->get_game_object()->get_component("UnityEngine.UI.Button"))->set_normal_color(get_void());

	const auto quickmenu_loc = ui_manager_impl::instance()->get_quickmenu();
	const auto quickmenu_transform = quickmenu_loc->get_transform();
	menu_root = quickmenu_transform->find(xorstr_("Container/Window/QMParent"));

	safety_button = quickmenu_transform->find(xorstr_("Container/Window/QMParent/Menu_Dashboard/ScrollRect/Viewport/VerticalLayoutGroup/Buttons_QuickLinks/Button_Safety"));
	if (!safety_button)
		return false;

	tmpro::tmp_text* component;
	transform* text;

	if (!config::get<bool>(g_context.anti_stream)) 
	{
		text = safety_button->find(xorstr_("Text_H4"));
		reinterpret_cast<ui::graphic*>(safety_button->find(xorstr_("Background"))->get_game_object()->get_component(xorstr_("UnityEngine.UI.Image")))->set_color(sdk::color(1.f, 0.7f, 0.9f, 1.f));
		component = reinterpret_cast<tmpro::tmp_text*>(text->get_component(xorstr_("TMPro.TextMeshProUGUI")));
		component->set_text(xorstr_("<color=#a75cf6>Void</color>"));
	}

	const auto button = reinterpret_cast<ui::button*>(safety_button->get_component(xorstr_("UnityEngine.UI.Button")));
	if (!button)
		return false;


	// @xref: //Fields
	// @xref: private List<ǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅ> ǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅ; // 0x18

	// @xref: //Methods

	// @xref: public void.ctor() { }
	// @xref: protected virtual void OnDestroy() { }
	binding_type = il2cpp::get_type(xorstr_(L"ÏÍÌÌÍÎÎÍÎÏÍÏÎÎÎÎÍÌÎÏÎÍÌ, DataModel.dll"));

	button->set_on_click(ui::button_clicked_event::ctor());
	button->get_on_click()->add_listener(events::unity_action::ctor(create_detour([=]
		{
			if (const auto binding_comp = safety_button->get_component(binding_type))
				object::destroy(binding_comp);

			menu_root->find(xorstr_("Menu_Dashboard"))->get_game_object()->set_active(false);
			menu_root->find(xorstr_("Menu_VoidVR"))->get_game_object()->set_active(true);

			main_modules::get().show_main();
		})
	));

	const auto void_menu = reinterpret_cast<game_object*>(object::instantiate(quickmenu_transform->find(xorstr_("Container/Window/QMParent/Menu_ChangeAudioInputDevice"))->get_game_object(), quickmenu_transform->find(xorstr_("Container/Window/QMParent")), true));
	if (!void_menu)
		return false;

	void_menu->set_name(xorstr_("Menu_VoidVR"));
	const auto header = void_menu->get_transform()->find(xorstr_("Header_H1/LeftItemContainer"));
	if (!header)
		return false;

	const auto header_button = reinterpret_cast<ui::button*>(header->find(xorstr_("Button_Back"))->get_component(xorstr_("UnityEngine.UI.Button")));
	if (!header_button)
		return false;

	header_button->set_on_click(ui::button_clicked_event::ctor());
	header_button->get_on_click()->add_listener(events::unity_action::ctor(
		create_detour([=]
			{
				main_modules::get().show_main();
				menu_root->find(xorstr_("Menu_Dashboard"))->get_game_object()->set_active(true);
				menu_root->find(xorstr_("Menu_VoidVR"))->get_game_object()->set_active(false);
			})
	));

	text = header->find(xorstr_("Text_Title"));
	component = reinterpret_cast<tmpro::tmp_text*>(text->get_component(xorstr_("TMPro.TextMeshProUGUI")));
	component->set_text(xorstr_("<color=#a75cf6>Void</color>"));

	// @xref: public whatthefuck whatthefuck; // 0x18
	// @xref: public GameObject ǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅ; // 0x20
	// no more than that

	const auto device_type = il2cpp::get_type(xorstr_(L"ÍÍÎÌÍÌÍÏÌÍÎÍÌÎÏÌÎÌÎÍÏÏÍ, VRC.UI.Elements.dll"));
	if (const auto device_comp = void_menu->get_component(device_type))
		object::destroy(device_comp);

	object::destroy(void_menu->get_component(vrc_ui_page::get_type()));

	const auto vert = void_menu->get_transform()->find(xorstr_("ScrollRect/Viewport/VerticalLayoutGroup"));
	if (!vert)
		return false;

	object::destroy(vert->get_game_object()->get_component(xorstr_("UnityEngine.UI.VerticalLayoutGroup")));

	if (const auto children = vert->child_count(); children > 0)
		for (int i = 0; i < children; i++)
			object::destroy(vert->get_child(i)->get_game_object());

	safety_modules::get().setup();
	safety2_modules::get().setup();
	misc_modules::get().setup();
	misc2_modules::get().setup();
	utility_modules::get().setup();
	config_modules::get().setup();
	customization_modules::get().setup();
	game_modules::get().setup();
	instance_history::get().setup();
	lovense_modules::get().setup();
	portable_mirror_modules::get().setup();
	rank_colors_submenu::get().setup();
	notifier_submenu::get().setup();
	spoofing_submenu::get().setup();
	murder_submenu::get().setup();
	main_modules::get().setup();

	return true;
}

bool assembler::vrc_quick_menu::player_list() // @note: more efficient than creating text for every single player
{
	const auto quickmenu_loc = ui_manager_impl::instance()->get_quickmenu();

	transform* pos = quickmenu_loc->get_transform()->find(xorstr_("Container"));
	transform* early_access_loc = quickmenu_loc->get_transform()->find(xorstr_("Container/Window/QMParent/Menu_Dashboard/Header_H1/LeftItemContainer/Text_Title"));
	transform* panel_loc = quickmenu_loc->get_transform()->find(xorstr_("Container/Window/QMParent/BackgroundLayer01"));

	if (!pos || !early_access_loc || !panel_loc)
		return false;

	auto players = il2cpp::array_to_vector<vrc::player*>(vrc::player_manager::get_players());

	try {
		std::ranges::partition(players, [](vrc::player* p)
		{
			const auto id = p->get_api_user()->get_id();
			return p->get_vrc_player_api()->get_is_master() || id == vrc::core::api_user::get_current()->get_id() || vrc::core::api_user::is_friends_with(id);
		});
	}
	catch (const std::exception& e)
	{
		logging::push(FOREGROUND_INTENSE_RED);
		logging::print(xorstr_("[critical] failed to partition vector -> {}\n"), e.what());
		logging::pop();
		return false;
	}

	if (const auto player_text = quickmenu_loc->get_transform()->find(xorstr_("Container/VOIDPANEL")); player_text == nullptr)
	{
		const auto instantiate = object::instantiate(panel_loc->get_game_object(), pos, true);
		const auto panel_transform = reinterpret_cast<game_object*>(instantiate)->get_transform();

		panel_transform->set_local_position(sdk::vector(950.f, 0.f, 0.f));
		panel_transform->set_local_scale(sdk::vector(0.55f, 1.f, 1.f));
		panel_transform->set_name(xorstr_("VOIDPANEL"));
	}

	auto playerlist_shadow_text = quickmenu_loc->get_transform()->find(xorstr_("Container/VOIDPLAYERLISTSHADOW"));
	if (playerlist_shadow_text == nullptr)
	{
		const auto instantiate = object::instantiate(early_access_loc->get_game_object(), pos, true);
		playerlist_shadow_text = reinterpret_cast<game_object*>(instantiate)->get_transform();
		playerlist_shadow_text->set_name(xorstr_("VOIDPLAYERLISTSHADOW"));
	}

	auto playerlist_text = quickmenu_loc->get_transform()->find(xorstr_("Container/VOIDPLAYERLIST"));
	if (playerlist_text == nullptr)
	{
		const auto instantiate = object::instantiate(early_access_loc->get_game_object(), pos, true);
		playerlist_text = reinterpret_cast<game_object*>(instantiate)->get_transform();
		playerlist_text->set_name(xorstr_("VOIDPLAYERLIST"));
	}

	float position = 440.f;
	const auto normal_component = reinterpret_cast<tmpro::tmp_text*>(playerlist_text->get_component(xorstr_("TMPro.TextMeshProUGUI")));
	const auto shadow_component = reinterpret_cast<tmpro::tmp_text*>(playerlist_shadow_text->get_component(xorstr_("TMPro.TextMeshProUGUI")));

	if (!normal_component || !shadow_component)
		return false;

	auto normal_text = utility::format(xorstr_("<color=#a75cf6>void {} build {} | {}\r\n\r\noccupants: [{:d}]</color>\r\n"), stage, build, msg, players.size());
	auto shadow_text = utility::format(xorstr_("<color=black>void {} build {} | {}\r\n\r\noccupants :[{:d}]</color>\r\n"), stage, build, msg, players.size());

	for (std::size_t i = 0; i < players.size(); i++)
	{
		if (i < 32)
		{
			const auto apiuser = players[i]->get_api_user();

			if (!apiuser)
				continue;

			shadow_text += misc::get_social_rank_for_player_list_shadow(players[i], apiuser) + xorstr_("\r\n");
			normal_text += misc::get_social_rank_for_player_list(players[i], apiuser) + xorstr_("\r\n");
			position -= 13.1f;
		}
		else if (i >= 32)
		{
			shadow_text += xorstr_("<color=black>...more</color>\r\n");
			normal_text += xorstr_("<color=#a75cf6>...more</color>\r\n");
			position -= 13.1f;
			break;
		}
	}

	playerlist_shadow_text->set_local_position(sdk::vector(690.f, position - 3.5f, 5.75f));
	shadow_component->set_text(shadow_text);
	shadow_component->set_fontsize(20.f);

	playerlist_text->set_local_position(sdk::vector(695.f, position, 5.75f));
	normal_component->set_text(normal_text);
	normal_component->set_fontsize(20.f);

	return true;
}

bool assembler::vrc_quick_menu::init_vr_debug()
{
	const auto quickmenu_loc = ui_manager_impl::instance()->get_quickmenu();
	const auto text = quickmenu_loc->get_transform()->find(xorstr_("Container/Window/QMParent/Menu_Dashboard/ScrollRect/Viewport/VerticalLayoutGroup/Carousel_Banners/Image_MASK/Image"));

	if (!text)
	{
		config::get<bool>(g_context.qm_debug_log) = false;
		return false;
	}

	text->set_local_scale(sdk::vector(0.f, 0.f, 0.f));

	// Create Shadow Text
	transform* pos = quickmenu_loc->get_transform()->find(xorstr_("Container/Window/QMParent/Menu_Dashboard/ScrollRect/Viewport/VerticalLayoutGroup/Carousel_Banners"));
	transform* ea_text = quickmenu_loc->get_transform()->find(xorstr_("Container/Window/QMParent/Menu_Dashboard/Header_H1/LeftItemContainer/Text_Title"));

	if (!pos || !ea_text)
	{
		config::get<bool>(g_context.qm_debug_log) = false;
		return false;
	}

	auto instantiate = object::instantiate(ea_text->get_game_object(), pos, true);
	auto string_element = static_cast<game_object*>(instantiate)->get_transform();
	auto component = reinterpret_cast<tmpro::tmp_text*>(string_element->get_component(xorstr_("TMPro.TextMeshProUGUI")));
	component->set_text(xorstr_("<color=black>void | debug logs</color>"));
	component->set_fontsize(26);
	string_element->set_name(xorstr_("VOIDDEBUGTITLESHADOW"));
	string_element->set_local_position(sdk::vector(-455.f, 126.5f, 0.f));


	instantiate = object::instantiate(ea_text->get_game_object(), pos, true);
	string_element = static_cast<game_object*>(instantiate)->get_transform();
	component = reinterpret_cast<tmpro::tmp_text*>(string_element->get_component(xorstr_("TMPro.TextMeshProUGUI")));
	component->set_text(xorstr_("<color=#a75cf6>void | debug logs</color>"));
	component->set_fontsize(26);
	string_element->set_name(xorstr_("VOIDDEBUGTITLE"));
	string_element->set_local_position(sdk::vector(-450.f, 130.f, 0.f));


	instantiate = object::instantiate(ea_text->get_game_object(), pos, true);
	string_element = static_cast<game_object*>(instantiate)->get_transform();
	component = reinterpret_cast<tmpro::tmp_text*>(string_element->get_component(xorstr_("TMPro.TextMeshProUGUI")));
	component->set_text(xorstr_(""));
	component->set_fontsize(20);
	string_element->set_name(xorstr_("VOIDDEBUGSHADOW"));


	instantiate = object::instantiate(ea_text->get_game_object(), pos, true);
	string_element = static_cast<game_object*>(instantiate)->get_transform();
	component = reinterpret_cast<tmpro::tmp_text*>(string_element->get_component(xorstr_("TMPro.TextMeshProUGUI")));
	component->set_text(xorstr_(""));
	component->set_fontsize(20);
	string_element->set_name(xorstr_("VOIDDEBUG"));
	return true;
}

bool assembler::vrc_quick_menu::restore_vr_debug()
{
	const auto quickmenu_loc = ui_manager_impl::instance()->get_quickmenu();

	if (const auto player_text = quickmenu_loc->get_transform()->find(xorstr_("Container/Window/QMParent/Menu_Dashboard/ScrollRect/Viewport/VerticalLayoutGroup/Carousel_Banners/VOIDDEBUG")); player_text != nullptr)
		object::destroy(player_text->get_game_object());
	else
		return false;

	if (const auto player_text = quickmenu_loc->get_transform()->find(xorstr_("Container/Window/QMParent/Menu_Dashboard/ScrollRect/Viewport/VerticalLayoutGroup/Carousel_Banners/VOIDDEBUGSHADOW")); player_text != nullptr)
		object::destroy(player_text->get_game_object());
	else
		return false;

	if (const auto player_text = quickmenu_loc->get_transform()->find(xorstr_("Container/Window/QMParent/Menu_Dashboard/ScrollRect/Viewport/VerticalLayoutGroup/Carousel_Banners/VOIDDEBUGTITLE")); player_text != nullptr)
		object::destroy(player_text->get_game_object());
	else
		return false;

	if (const auto player_text = quickmenu_loc->get_transform()->find(xorstr_("Container/Window/QMParent/Menu_Dashboard/ScrollRect/Viewport/VerticalLayoutGroup/Carousel_Banners/VOIDDEBUGTITLESHADOW")); player_text != nullptr)
		object::destroy(player_text->get_game_object());
	else
		return false;

	if (const auto image = quickmenu_loc->get_transform()->find(xorstr_("Container/Window/QMParent/Menu_Dashboard/ScrollRect/Viewport/VerticalLayoutGroup/Carousel_Banners/Image_MASK/Image"))->get_transform(); image != nullptr)
		image->set_local_scale(sdk::vector(1.f, 1.f, 1.f));
	else
		return false;

	return true;
}

bool assembler::vrc_quick_menu::vr_debug_update()
{
	if (!config::get<bool>(g_context.qm_debug_log))
		return true;

	if (!ingame_logging::get().update())
		return false;

	if (!ingame_logging::get().update_shadow())
		return false;

	return true;
}
