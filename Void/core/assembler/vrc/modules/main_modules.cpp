#include "main_modules.hpp"
#include "shellapi.h"

void main_modules::setup()
{
	auto safety_modules = std::make_unique<single_button>(location_, 110, 0, 0,xorstr_("<color=#a75cf6>Safety\r\nModules</color>"), [=]
	{
		safety_modules::get().show_all();
	}, xorstr_("View Void's safety modules"));
	safety_modules->set_active(true);
	single_buttons_.push_back(std::move(safety_modules));

	auto misc_modules = std::make_unique<single_button>(location_, 120, 1, 0,xorstr_("<color=#a75cf6>Misc.\r\nModules</color>"), [=]
	{
		misc_modules::get().show_all();
	}, xorstr_("View Void's misc modules"));
	misc_modules->set_active(true);
	single_buttons_.push_back(std::move(misc_modules));

	auto utility_modules = std::make_unique<single_button>(location_, 130, 2, 0,xorstr_("<color=#a75cf6>Utility\r\nModules</color>"), [=]
	{
		utility_modules::get().show_all();
	}, xorstr_("View Void's utility modules"));
	utility_modules->set_active(true);
	single_buttons_.push_back(std::move(utility_modules));

	auto config_modules = std::make_unique<single_button>(location_, 140, 3, 0,xorstr_("<color=#a75cf6>Config\r\nModules</color>"), [=]
	{
		config_modules::get().show_all();
	}, xorstr_("View Void's config settings"));
	config_modules->set_active(true);
	single_buttons_.push_back(std::move(config_modules));

	auto safety2_modules = std::make_unique<single_button>(location_, 150, 0, -1,xorstr_("<color=#a75cf6>Safety\r\nModules\r\nPage 2</color>"), [=]
	{
		safety2_modules::get().show_all();
	},xorstr_("View Void's safety modules"));
	safety2_modules->set_active(true);
	single_buttons_.push_back(std::move(safety2_modules));

	auto misc2_modules = std::make_unique<single_button>(location_, 160, 1, -1,xorstr_("<color=#a75cf6>Misc.\r\nModules\r\nPage 2</color>"), [=]
	{
		misc2_modules::get().show_all();
	}, xorstr_("View Void's misc modules"));
	misc2_modules->set_active(true);
	single_buttons_.push_back(std::move(misc2_modules));

	auto custom_modules = std::make_unique<single_button>(location_, 170, 3, -1,xorstr_("<color=#a75cf6>Module Settings</color>"), [=]
	{
		customization_modules::get().show_all();
	}, xorstr_("View Void's module settings"));
	custom_modules->set_active(true);
	single_buttons_.push_back(std::move(custom_modules));

	auto go_back = std::make_unique<single_button>(location_, 1110, 3, -3, xorstr_("<color=red>Go Back</color>"), [=]
	{
		show_main();
	}, xorstr_("Go back to the previous page"));
	go_back->set_active(false);
	single_buttons_.push_back(std::move(go_back));

	auto instance_history = std::make_unique<single_button>(location_, 180, 0, -3,xorstr_("<color=#a75cf6>Instance History</color>"), [=]
	{
		instance_history::get().hide_info();
	}, xorstr_("View Void's module settings"));
	instance_history->set_active(true);
	single_buttons_.push_back(std::move(instance_history));

	auto lovense_modules = std::make_unique<single_button>(location_, 190, 0, -2,xorstr_("<color=#fc658d>Lovense\r\nIntegration</color>"), [=]
	{
		lovense_modules::get().show_all();
	}, xorstr_("View Void's Lovense integration settings"));
	lovense_modules->set_active(true);
	single_buttons_.push_back(std::move(lovense_modules));

	auto game_modules = std::make_unique<single_button>(location_, 200, 2, -1, xorstr_("<color=#a75cf6>Game Modules</color>"), [=]
		{
			game_modules::get().show_all();
		}, xorstr_("View Void's game module"));
	game_modules->set_active(true);
	single_buttons_.push_back(std::move(game_modules));

	auto portable_mirror = std::make_unique<single_button>(location_, 210, 1, -2, xorstr_("<color=#2faceb>Portable\r\nMirror</color>"), [=]
		{
			portable_mirror_modules::get().show_all();
		}, xorstr_("View Void's game module"));
	portable_mirror->set_active(true);
	single_buttons_.push_back(std::move(portable_mirror));

	auto discord_btn = std::make_unique<single_button>(location_, 220, 1, -3, xorstr_("<color=#5865F2>Discord</color>"), [=]
		{
			const auto res = ShellExecuteW(nullptr, SECSTRW(L"open"), SECSTRW(L"https://invalid.gg/discord"), nullptr, nullptr, SW_SHOWNORMAL);
			if (static_cast<std::int32_t>(reinterpret_cast<std::uintptr_t>(res)) <= 32)
			{
				logging::push(FOREGROUND_INTENSE_RED);
				logging::print(xorstr_("[critical] failed to open discord invite [code {:d}]\n"), GetLastError());
				logging::pop();
			}
		}, xorstr_("Opens Void's Discord invite in your web browser."));
	discord_btn->set_active(true);
	single_buttons_.push_back(std::move(discord_btn));
}

void main_modules::show_back() const
{
	hide();
	single_buttons_[7]->set_active(true);
}

void main_modules::show_main() const
{
	safety_modules::get().hide();
	safety2_modules::get().hide();
	misc_modules::get().hide();
	misc2_modules::get().hide();
	utility_modules::get().hide();
	config_modules::get().hide_all();
	customization_modules::get().hide_all();
	lovense_modules::get().hide_all();
	game_modules::get().hide_all();
	portable_mirror_modules::get().hide_all();
	instance_history::get().hide_all();

	show();
	single_buttons_[7]->set_active(false);
}

void main_modules::no_back() const
{
	single_buttons_[7]->set_active(false);
}

void main_modules::back() const
{
	single_buttons_[7]->set_active(true);
}
