#include "murder4_submenu.hpp"

void murder_submenu::setup()
{
	auto go_back = std::make_unique<single_button>(location_, 15110, 3, -3, xorstr_("<color=red>Go Back</color>"), [=]
		{
			hide();
			game_modules::get().show_all();
		}, xorstr_("Go back to the previous page"));
	go_back->set_active(false);
	single_buttons_.push_back(std::move(go_back));

	auto teleportallbtn = std::make_unique<single_button>(location_, 15120, 0, 0, xorstr_("<color=#a75cf6>Teleport All Weapons</color>"), []
		{
			misc::murder_teleportall();
		}, xorstr_("Teleports all weapons to you."));
	teleportallbtn->set_active(false);
	single_buttons_.push_back(std::move(teleportallbtn));

	auto teleportknifebtn = std::make_unique<single_button>(location_, 15130, 1, 0, xorstr_("<color=#a75cf6>Teleport Knife</color>"), []
		{
			misc::murder_teleportsingle(xorstr_(L"knife"));
		}, xorstr_("Teleports the knife to you."));
	teleportknifebtn->set_active(false);
	single_buttons_.push_back(std::move(teleportknifebtn));

	auto teleportrevolverbtn = std::make_unique<single_button>(location_, 15140, 2, 0, xorstr_("<color=#a75cf6>Teleport Revolver</color>"), []
		{
			misc::murder_teleportsingle(xorstr_(L"revolver"));
		}, xorstr_("Teleports the revolver to you."));
	teleportrevolverbtn->set_active(false);
	single_buttons_.push_back(std::move(teleportrevolverbtn));

	auto teleportlugerbtn = std::make_unique<single_button>(location_, 15150, 3, 0, xorstr_("<color=#a75cf6>Teleport Luger</color>"), []
		{
			misc::murder_teleportsingle(xorstr_(L"luger"));
		}, xorstr_("Teleports the luger to you."));
	teleportlugerbtn->set_active(false);
	single_buttons_.push_back(std::move(teleportlugerbtn));

	auto teleportbeartrapbtn = std::make_unique<single_button>(location_, 15170, 0, -1, xorstr_("<color=#a75cf6>Teleport Beartrap</color>"), []
		{
			misc::murder_teleportsingle(xorstr_(L"bear"));
		}, xorstr_("Teleports the beartrap to you."));
	teleportbeartrapbtn->set_active(false);
	single_buttons_.push_back(std::move(teleportbeartrapbtn));

	auto teleportgrenadebtn = std::make_unique<single_button>(location_, 15180, 1, -1, xorstr_("<color=#a75cf6>Teleport Grenade</color>"), []
		{
			misc::murder_teleportsingle(xorstr_(L"frag"));
		}, xorstr_("Teleports the grenade to you."));
	teleportgrenadebtn->set_active(false);
	single_buttons_.push_back(std::move(teleportgrenadebtn));

	auto killallbtn = std::make_unique<single_button>(location_, 15190, 2, -1, xorstr_("<color=#a75cf6>Kill All</color>"), []
		{
			misc::udon_killall(&g_context.skippable_sync_kills);
		}, xorstr_("Kill everyone in the game. (lol)"));
	killallbtn->set_active(false);
	single_buttons_.push_back(std::move(killallbtn));

	auto antikillcambtn = std::make_unique<toggle_button>(location_, 15200, 0, -2, xorstr_("<color=#a75cf6>Anti-Killcam</color>"), []
		{
			if (!config::get<bool>(g_context.murder_anti_killcam))
			{
				config::get<bool>(g_context.murder_anti_killcam) = true;
			}
		}, []
		{
			if (config::get<bool>(g_context.murder_anti_killcam))
			{
				config::get<bool>(g_context.murder_anti_killcam) = false;
			}
		}, xorstr_("Prevents flash & blind ingame HUDs from appearing."));
	antikillcambtn->set_active(false);
	toggle_buttons_.push_back(std::move(antikillcambtn));

	auto weapontriggersbtn = std::make_unique<toggle_button>(location_, 15210, 1, -2, xorstr_("<color=#a75cf6>Weapon Triggers</color>"), []
		{
			if (!config::get<bool>(g_context.murder_weapontriggers))
			{
				config::get<bool>(g_context.murder_weapontriggers) = true;
			}
		}, []
		{
			if (config::get<bool>(g_context.murder_weapontriggers))
			{
				config::get<bool>(g_context.murder_weapontriggers) = false;
			}
		}, xorstr_("Sustains a weapon's pickupable property."));
	weapontriggersbtn->set_active(false);
	toggle_buttons_.push_back(std::move(weapontriggersbtn));
}

void murder_submenu::show_all() const
{
	toggle_buttons_[0]->trigger(config::get<bool>(g_context.murder_anti_killcam));
	toggle_buttons_[1]->trigger(config::get<bool>(g_context.murder_weapontriggers));
	show();
}
