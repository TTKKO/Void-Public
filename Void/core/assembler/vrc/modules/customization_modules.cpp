#include "customization_modules.hpp"

void customization_modules::setup()
{
	auto rank_colors_menu = std::make_unique<single_button>(location_, 8010, 0, 0,xorstr_("<color=#a75cf6>Custom Plates\r\nColors</color>"), [=]
	{
		main_modules::get().no_back();
		hide();
		rank_colors_submenu::get().show_all();
	}, xorstr_("Configure the color of Void's trust ranks!"));
	rank_colors_menu->set_active(false);
	single_buttons_.push_back(std::move(rank_colors_menu));

	auto notifications_menu = std::make_unique<single_button>(location_, 8020, 1, 0,xorstr_("<color=#a75cf6>Join Notifier\r\nSettings</color>"), [=]
	{
		main_modules::get().no_back();
		hide();
		notifier_submenu::get().show_all();
	}, xorstr_("Configure Void's join notifier settings"));
	notifications_menu->set_active(false);
	single_buttons_.push_back(std::move(notifications_menu));

	auto spoofing_menu = std::make_unique<single_button>(location_, 8030, 2, 0,xorstr_("<color=#a75cf6>Spoofing\r\nSettings</color>"), [=]
	{
		main_modules::get().no_back();
		hide();
		spoofing_submenu::get().show_all();
	}, xorstr_("Configure Void's spoofing settings"));
	spoofing_menu->set_active(false);
	single_buttons_.push_back(std::move(spoofing_menu));
}

void customization_modules::show_all() const
{
	main_modules::get().show_back();
	show();
}

void customization_modules::hide_all() const
{
	hide();
	spoofing_submenu::get().hide_all();
	rank_colors_submenu::get().hide_all();
	notifier_submenu::get().hide_all();
}
