#include "spoofing_submenu.hpp"

void spoofing_submenu::setup()
{
	auto go_back = std::make_unique<single_button>(location_, 12010, 3, -3, xorstr_("<color=red>Go Back</color>"), [=]
	{
		hide_all();
		customization_modules::get().show_all();
	}, xorstr_("Go back to the previous page"));

	go_back->set_active(false);
	single_buttons_.push_back(std::move(go_back));

	const auto text = assembler::ui_manager_impl::instance()->get_quickmenu()->get_transform()->find(xorstr_("Container/Window/QMParent/Menu_QM_Emojis/Header_Emojis/LeftItemContainer/Text_Title"));
	auto temp = static_cast<assembler::unity_engine::game_object*>(assembler::unity_engine::object::instantiate(text->get_game_object(), assembler::ui_manager_impl::instance()->get_quickmenu()->get_transform()->find(location_), true));

	text_.push_back(reinterpret_cast<assembler::tmpro::tmp_text*>(temp->get_transform()->get_component(xorstr_("TMPro.TextMeshProUGUI"))));
	text_[0]->set_text(xorstr_("<color=#a75cf6>Ping Spoof</color>"));
	text_[0]->set_fontsize(30.f);
	reinterpret_cast<assembler::unity_engine::component*>(text_[0])->get_transform()->set_local_position(sdk::vector(-90.f, -20.f, 0.f));
	reinterpret_cast<assembler::unity_engine::component*>(text_[0])->get_game_object()->set_active(false);

	slider_buttons_.emplace_back(std::make_unique<slider_button>(location_, 12020, 0, xorstr_("<color=#a75cf6>Value</color>"), xorstr_("Value slider (0-1000)")));
	slider_buttons_[0]->set_action([=]
	{
		const auto value = static_cast<int>(slider_buttons_[0]->this_slider->get_value() * 1000.f);
		slider_buttons_[0]->set_slider_text(xorstr_("<color=#a75cf6>Value (") + std::to_string(value) + xorstr_(")</color>"));
		config::get<int>(g_context.fake_ping_i) = value;
	});
	slider_buttons_[0]->set_active(false);

	slider_buttons_.emplace_back(std::make_unique<slider_button>(location_, 12030, -1, xorstr_("<color=#a75cf6>Range</color>"), xorstr_("Range slider (0-1000)")));
	slider_buttons_[1]->set_action([=]
	{
		const auto value = static_cast<int>(slider_buttons_[1]->this_slider->get_value() * 1000.f);
		slider_buttons_[1]->set_slider_text(xorstr_("<color=#a75cf6>Range (") + std::to_string(value) + xorstr_(")</color>"));
		config::get<int>(g_context.fake_ping_range) = value;
	});
	slider_buttons_[1]->set_active(false);

	temp = static_cast<assembler::unity_engine::game_object*>(assembler::unity_engine::object::instantiate(text->get_game_object(), assembler::ui_manager_impl::instance()->get_quickmenu()->get_transform()->find(location_), true));
	text_.push_back(reinterpret_cast<assembler::tmpro::tmp_text*>(temp->get_transform()->get_component(xorstr_("TMPro.TextMeshProUGUI"))));
	text_[1]->set_text(xorstr_("<color=#a75cf6>FPS Spoof</color>"));
	text_[1]->set_fontsize(30.f);
	reinterpret_cast<assembler::unity_engine::component*>(text_[1])->get_transform()->set_local_position(sdk::vector(-85.f, -300.f, 0.f));
	reinterpret_cast<assembler::unity_engine::component*>(text_[1])->get_game_object()->set_active(false);

	slider_buttons_.emplace_back(std::make_unique<slider_button>(location_, 12040, -3, xorstr_("<color=#a75cf6>Value</color>"), xorstr_("Value slider (0-1000)")));
	slider_buttons_[2]->set_action([=]
	{
		const auto value = static_cast<int>(slider_buttons_[2]->this_slider->get_value() * 1000.f);
		slider_buttons_[2]->set_slider_text(xorstr_("<color=#a75cf6>Value (") + std::to_string(value) + xorstr_(")</color>"));
		config::get<int>(g_context.fake_fps_i) = value;
	});
	slider_buttons_[2]->set_active(false);

	slider_buttons_.emplace_back(std::make_unique<slider_button>(location_, 12050, -4, xorstr_("<color=#a75cf6>Range</color>"), xorstr_("Range slider (0-1000)")));
	slider_buttons_[3]->set_action([=]
	{
		const auto value = static_cast<int>(slider_buttons_[3]->this_slider->get_value() * 1000.f);
		slider_buttons_[3]->set_slider_text(xorstr_("<color=#a75cf6>Range (") + std::to_string(value) + xorstr_(")</color>"));
		config::get<int>(g_context.fake_fps_range) = value;
	});
	slider_buttons_[3]->set_active(false);

	auto trusteduserbtn = std::make_unique<half_single_button>(location_, 12060, 0, -7, xorstr_("<color=#a75cf6>Regen HWID</color>"), []
	{
		config::get<std::string>(g_context.set_hwid) = misc::get_device_id();
	}, xorstr_("Regenerates your HWID for this config. Make sure you save afterwards."));
	trusteduserbtn->set_active(false);
	hs_buttons_.push_back(std::move(trusteduserbtn));
}

void spoofing_submenu::show_all() const
{
	if (config::get<int>(g_context.fake_ping_i) <= 1000)
	{
		const auto value = static_cast<float>(config::get<int>(g_context.fake_ping_i)) / 1000.f;
		slider_buttons_[0]->this_slider->set_value(value);
		slider_buttons_[0]->set_slider_text(xorstr_("<color=#a75cf6>Value (") + std::to_string(config::get<int>(g_context.fake_ping_i)) + xorstr_(")</color>"));
	}
	if (config::get<int>(g_context.fake_ping_range) <= 1000)
	{
		const auto value = static_cast<float>(config::get<int>(g_context.fake_ping_range)) / 1000.f;
		slider_buttons_[1]->this_slider->set_value(value);
		slider_buttons_[1]->set_slider_text(xorstr_("<color=#a75cf6>Range (") + std::to_string(config::get<int>(g_context.fake_ping_range)) + xorstr_(")</color>"));
	}
	if (config::get<int>(g_context.fake_fps_i) <= 1000)
	{
		const auto value = static_cast<float>(config::get<int>(g_context.fake_fps_i)) / 1000.f;
		slider_buttons_[2]->this_slider->set_value(value);
		slider_buttons_[2]->set_slider_text(xorstr_("<color=#a75cf6>Value (") + std::to_string(config::get<int>(g_context.fake_fps_i)) + xorstr_(")</color>"));
	}
	if (config::get<int>(g_context.fake_fps_range) <= 1000)
	{
		const auto value = static_cast<float>(config::get<int>(g_context.fake_fps_range)) / 1000.f;
		slider_buttons_[3]->this_slider->set_value(value);
		slider_buttons_[3]->set_slider_text(xorstr_("<color=#a75cf6>Range (") + std::to_string(config::get<int>(g_context.fake_fps_range)) + xorstr_(")</color>"));
	}

	for (auto it = hs_buttons_.begin(); it != hs_buttons_.end(); ++it)
		(*it)->set_active(true);
	for (auto it = slider_buttons_.begin(); it != slider_buttons_.end(); ++it)
		(*it)->set_active(true);
	for (auto it = text_.begin(); it != text_.end(); ++it)
		reinterpret_cast<assembler::unity_engine::component*>(*it)->get_game_object()->set_active(true);

	show();
}

void spoofing_submenu::hide_all() const
{
	for (auto it = hs_buttons_.begin(); it != hs_buttons_.end(); ++it)
		(*it)->set_active(false);
	for (auto it = slider_buttons_.begin(); it != slider_buttons_.end(); ++it)
		(*it)->set_active(false);
	for (auto it = text_.begin(); it != text_.end(); ++it)
		reinterpret_cast<assembler::unity_engine::component*>(*it)->get_game_object()->set_active(false);
	hide();
}
