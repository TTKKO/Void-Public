#include "game_modules.hpp"

void game_modules::setup()
{
	auto murder4_submenu = std::make_unique<single_button>(location_, 150010, 0, 0, xorstr_("<color=#a75cf6>Murder 4</color>"), [=]
		{
			main_modules::get().no_back();
			hide();
			murder_submenu::get().show_all();
		}, xorstr_("Shows Murder 4 modules."));

	murder4_submenu->set_active(false);
	single_buttons_.push_back(std::move(murder4_submenu));

	auto antironulls = std::make_unique<toggle_button>(location_, 150020, 1, 0, xorstr_("<color=#a75cf6>FBT Anti-Doorlock</color>"), []
		{
			if (!config::get<bool>(g_context.fbt_doorbypass))
			{
				config::get<bool>(g_context.fbt_doorbypass) = true;
			}
		}, []
		{
			if (config::get<bool>(g_context.fbt_doorbypass))
			{
				config::get<bool>(g_context.fbt_doorbypass) = false;
			}
		}, xorstr_("Prevents locked doors in FBT Heaven."));

	antironulls->set_active(false);
	toggle_buttons_.push_back(std::move(antironulls));

	auto antiaudiomixersbtn = std::make_unique<toggle_button>(location_, 15030, 2, 0, xorstr_("<color=#a75cf6>Udon\r\nGodmode</color>"), []
		{
			if (!config::get<bool>(g_context.udon_godmode))
			{
				config::get<bool>(g_context.udon_godmode) = true;
			}
		}, []
		{
			if (config::get<bool>(g_context.udon_godmode))
			{
				config::get<bool>(g_context.udon_godmode) = false;
			}
		}, xorstr_("Attempts to prevent udon death scripts."));

	antiaudiomixersbtn->set_active(false);
	toggle_buttons_.push_back(std::move(antiaudiomixersbtn));

	auto udonnamespoofbtn = std::make_unique<toggle_button>(location_, 15040, 3, 0, xorstr_("<color=#a75cf6>Patreon Udon\r\nName Spoof</color>"), []
		{
			if (!config::get<bool>(g_context.udon_namespoof))
				config::get<bool>(g_context.udon_namespoof) = true;

			if (!config::get<bool>(g_context.udon_namespoof_patreon))
				config::get<bool>(g_context.udon_namespoof_patreon) = true;
		}, []
		{
			if (config::get<bool>(g_context.udon_namespoof))
				config::get<bool>(g_context.udon_namespoof) = false;

			if (!config::get<bool>(g_context.udon_namespoof_patreon))
				config::get<bool>(g_context.udon_namespoof_patreon) = false;
		}, xorstr_("Spoofs your Udon name automatically to a World's Patreon member."));

	udonnamespoofbtn->set_active(false);
	toggle_buttons_.push_back(std::move(udonnamespoofbtn));
}

void game_modules::show_all() const
{
	main_modules::get().show_back();
	show();
	toggle_buttons_[0]->trigger(config::get<bool>(g_context.fbt_doorbypass));
	toggle_buttons_[1]->trigger(config::get<bool>(g_context.udon_godmode));
	toggle_buttons_[2]->trigger(config::get<bool>(g_context.udon_namespoof));
}

void game_modules::hide_all() const
{
	hide();
	murder_submenu::get().hide();
}
