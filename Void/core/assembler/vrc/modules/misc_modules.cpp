#include "misc_modules.hpp"
#include "../../../hooks/helpers/nameplates.hpp"
#include "../../unityengine/character_controller.hpp"

void misc_modules::setup()
{
	auto hwidspoofbtn = std::make_unique<toggle_button>(location_, 1120, 0, 0, xorstr_("<color=#a75cf6>HWID Spoof</color>"), []
	{
		if (!config::get<bool>(g_context.fake_hwid))
		{
			config::get<bool>(g_context.fake_hwid) = true;
		}
	}, []
	{
		if (config::get<bool>(g_context.fake_hwid))
		{
			config::get<bool>(g_context.fake_hwid) = false;
		}
	}, xorstr_("Toggles hwid spoof. Restart with autoloading to take effect, make sure you save your config."));

	hwidspoofbtn->set_active(false);
	toggle_buttons_.push_back(std::move(hwidspoofbtn));

	auto fakeping_button = std::make_unique<toggle_button>(location_, 1130, 1, 0, xorstr_("<color=#a75cf6>Ping Spoof</color>"), []
	{
		if (!config::get<bool>(g_context.fake_ping))
		{
			config::get<bool>(g_context.fake_ping) = true;
		}
	}, []
	{
		if (config::get<bool>(g_context.fake_ping))
		{
			config::get<bool>(g_context.fake_ping) = false;
		}
	}, xorstr_("Spoofs your ping. Range and Value are configurable on Desktop GUI."));

	fakeping_button->set_active(false);
	toggle_buttons_.push_back(std::move(fakeping_button));

	auto offlinespoofbtn = std::make_unique<toggle_button>(location_, 1140, 2, 0,xorstr_("<color=#a75cf6>Offline Spoof</color>"), []
	{
		if (!config::get<bool>(g_context.fake_offline))
		{
			config::get<bool>(g_context.fake_offline) = true;
		}
	}, []
	{
		if (config::get<bool>(g_context.fake_offline))
		{
			config::get<bool>(g_context.fake_offline) = false;
		}
	}, xorstr_("[WARNING]: May get you banned. Spoofs your online activity."));

	offlinespoofbtn->set_active(false);
	toggle_buttons_.push_back(std::move(offlinespoofbtn));

	auto fpsspoobtn = std::make_unique<toggle_button>(location_, 1150, 3, 0, xorstr_("<color=#a75cf6>FPS Spoof</color>"), []
	{
		if (!config::get<bool>(g_context.fake_fps))
		{
			config::get<bool>(g_context.fake_fps) = true;
		}
	}, []
	{
		if (config::get<bool>(g_context.fake_fps))
		{
			config::get<bool>(g_context.fake_fps) = false;
		}
	}, xorstr_("Spoofs your FPS. Range and Value are configurable on Desktop GUI."));

	fpsspoobtn->set_active(false);
	toggle_buttons_.push_back(std::move(fpsspoobtn));

	auto questcrashbtn = std::make_unique<toggle_button>(location_, 1160, 0, -1, xorstr_("<color=#a75cf6>Quest Crash</color>"), []
	{
		if (!config::get<bool>(g_context.quest_crash))
		{
			if (config::get<bool>(g_context.collision_crash) || config::get<bool>(g_context.corrupt_asset_crash) || config::get<bool>(g_context.audio_crash))
				config::get<bool>(g_context.quest_crash) = false;
			else
			{
				config::get<bool>(g_context.quest_crash) = true;
				g_context.changing_avatar = g_context.g_avatars[2];
			}
		}
	}, []
	{
		if (config::get<bool>(g_context.quest_crash))
		{
			config::get<bool>(g_context.quest_crash) = false;
			g_context.changing_avatar = xorstr_("avtr_c4961195-1980-4a98-bb95-3cbe0e063463");
			//alien avatar
		}
	}, xorstr_("Crashes quest users, remember to toggle this off when you're done."));

	questcrashbtn->set_active(false);
	toggle_buttons_.push_back(std::move(questcrashbtn));

	auto gamecloserbtn = std::make_unique<toggle_button>(location_, 1170, 1, -1, xorstr_("<color=#a75cf6>Game Closer</color>"), []
	{
		if (!config::get<bool>(g_context.collision_crash))
		{
			if (config::get<bool>(g_context.quest_crash) || config::get<bool>(g_context.corrupt_asset_crash) || config::get<bool>(g_context.audio_crash))
				config::get<bool>(g_context.collision_crash) = false;
			else
			{
				config::get<bool>(g_context.collision_crash) = true;
				g_context.changing_avatar = g_context.g_avatars[0];
			}
		}
	}, []
	{
		if (config::get<bool>(g_context.collision_crash))
		{
			config::get<bool>(g_context.collision_crash) = false;
			g_context.changing_avatar = xorstr_("avtr_c4961195-1980-4a98-bb95-3cbe0e063463");
			//alien avatar
		}
	}, xorstr_("Closes PC users games."));

	gamecloserbtn->set_active(false);
	toggle_buttons_.push_back(std::move(gamecloserbtn));

	auto corruptedbtn = std::make_unique<toggle_button>(location_, 1180, 2, -1, xorstr_("<color=#a75cf6>Corrupt Crash</color>"), []
	{
		if (!config::get<bool>(g_context.corrupt_asset_crash))
		{
			if (config::get<bool>(g_context.quest_crash) || config::get<bool>(g_context.collision_crash) || config::get<bool>(g_context.audio_crash))
				config::get<bool>(g_context.corrupt_asset_crash) = false;
			else
			{
				config::get<bool>(g_context.corrupt_asset_crash) = true;
				g_context.changing_avatar = g_context.g_avatars[3];
			}
		}
	}, []
	{
		if (config::get<bool>(g_context.corrupt_asset_crash))
		{
			config::get<bool>(g_context.corrupt_asset_crash) = false;
			g_context.changing_avatar = xorstr_("avtr_c4961195-1980-4a98-bb95-3cbe0e063463"); //alien avatar
		}
	}, xorstr_("Uses corrupted asset to crash PC users."));

	corruptedbtn->set_active(false);
	toggle_buttons_.push_back(std::move(corruptedbtn));

	auto audiocrashbtn = std::make_unique<toggle_button>(location_, 1190, 3, -1, xorstr_("<color=#a75cf6>Shader Crash</color>"), []
	{
		if (!config::get<bool>(g_context.audio_crash))
		{
			if (config::get<bool>(g_context.quest_crash) || config::get<bool>(g_context.collision_crash) || config::get<bool>(g_context.corrupt_asset_crash))
				config::get<bool>(g_context.audio_crash) = false;
			else
			{
				config::get<bool>(g_context.audio_crash) = true;
				g_context.changing_avatar = g_context.g_avatars[1];
			}
		}
	}, []
	{
		if (config::get<bool>(g_context.audio_crash))
		{
			config::get<bool>(g_context.audio_crash) = false;
			g_context.changing_avatar = xorstr_("avtr_c4961195-1980-4a98-bb95-3cbe0e063463");
			//alien avatar
		}
	}, xorstr_("Audio crasher."));

	audiocrashbtn->set_active(false);
	toggle_buttons_.push_back(std::move(audiocrashbtn));

	auto flight_button = std::make_unique<toggle_button>(location_, 1200, 0, -2, xorstr_("<color=#a75cf6>Flight</color>"), []
	{
		if (!config::get<bool>(g_context.flight))
		{
			config::get<bool>(g_context.flight) = true;
			misc::toggle_flight(config::get<bool>(g_context.flight));
		}
	}, []
	{
		if (config::get<bool>(g_context.flight))
		{
			config::get<bool>(g_context.flight) = false;
			misc::toggle_flight(config::get<bool>(g_context.flight));
		}
	}, xorstr_("Uh... you fly..."));

	flight_button->set_active(false);
	toggle_buttons_.push_back(std::move(flight_button));

	auto espbtn = std::make_unique<toggle_button>(location_, 1210, 1, -2, xorstr_("<color=#a75cf6>Player ESP</color>"), []
	{
		if (!config::get<bool>(g_context.esp))
		{
			config::get<bool>(g_context.esp) = true;
		}
	}, []
	{
		if (config::get<bool>(g_context.esp))
		{
			config::get<bool>(g_context.esp) = false;
		}
	}, xorstr_("Toggles player capsule ESP."));

	espbtn->set_active(false);
	toggle_buttons_.push_back(std::move(espbtn));

	auto nametagsbtn = std::make_unique<toggle_button>(location_, 1220, 2, -2, xorstr_("<color=#a75cf6>Nametags</color>"), []
	{
		if (!config::get<bool>(g_context.nametags))
		{
			config::get<bool>(g_context.nametags) = true;
		}
	}, []
	{
		if (config::get<bool>(g_context.nametags))
		{
			config::get<bool>(g_context.nametags) = false;
		}
	}, xorstr_("Toggles player nametag ESP."));

	nametagsbtn->set_active(false);
	toggle_buttons_.push_back(std::move(nametagsbtn));

	auto chamsbtn = std::make_unique<toggle_button>(location_, 1230, 3, -2,xorstr_("<color=#a75cf6>Chams</color>"), []
	{
		if (!config::get<bool>(g_context.chams))
		{
			config::get<bool>(g_context.chams) = true;
			nameplate_manager::fix_mirrormasks(true);
		}
	}, []
	{
		if (config::get<bool>(g_context.chams))
		{
			config::get<bool>(g_context.chams) = false;
			nameplate_manager::fix_mirrormasks(false);
		}
	}, xorstr_("Allows you to see avatars through walls."));

	chamsbtn->set_active(false);
	toggle_buttons_.push_back(std::move(chamsbtn));

	auto highdbbtn = std::make_unique<toggle_button>(location_, 1240, 0, -3, xorstr_("<color=#a75cf6>High Decibel Microphone</color>"), []
	{
		if (!config::get<bool>(g_context.high_db))
		{
			config::get<bool>(g_context.high_db) = true;
			assembler::vrc_player::get_current()->get_uspeaker()->
			                                      set_remotegain(std::numeric_limits<float>::max());
		}
	}, []
	{
		if (config::get<bool>(g_context.high_db))
		{
			config::get<bool>(g_context.high_db) = false;
			assembler::vrc_player::get_current()->get_uspeaker()->set_remotegain(1.f);
		}
	}, xorstr_("[WARNING]: May get you banned. Complete cancer... lmao"));

	highdbbtn->set_active(false);
	toggle_buttons_.push_back(std::move(highdbbtn));

	auto exploitevent1btn = std::make_unique<toggle_button>(location_, 1250, 1, -3, xorstr_("<color=#a75cf6>E1 Distortion</color>"), []
	{
		if (!config::get<bool>(g_context.exploit_event_1))
		{
			config::get<bool>(g_context.exploit_event_1) = true;
		}
	}, []
	{
		if (config::get<bool>(g_context.exploit_event_1))
		{
			config::get<bool>(g_context.exploit_event_1) = false;
		}
	},xorstr_("void on top"));

	exploitevent1btn->set_active(false);
	toggle_buttons_.push_back(std::move(exploitevent1btn));

	auto cozyvrmenubtn = std::make_unique<toggle_button>(location_, 1260, 2, -3, xorstr_("<color=#a75cf6>Cozy VR\r\nMenu</color>"), []
		{
			if (!config::get<bool>(g_context.cozyvrmenu))
			{
				config::get<bool>(g_context.cozyvrmenu) = true;
			}
		}, []
		{
			if (config::get<bool>(g_context.cozyvrmenu))
			{
				config::get<bool>(g_context.cozyvrmenu) = false;
			}
		}, xorstr_("Positions the main VR menu based on your viewing position and angles."));

	cozyvrmenubtn->set_active(false);
	toggle_buttons_.push_back(std::move(cozyvrmenubtn));
}

void misc_modules::show_all() const
{
	main_modules::get().show_back();
	show();
	toggle_buttons_[0]->trigger(config::get<bool>(g_context.fake_hwid));
	toggle_buttons_[1]->trigger(config::get<bool>(g_context.fake_ping));
	toggle_buttons_[2]->trigger(config::get<bool>(g_context.fake_offline));
	toggle_buttons_[3]->trigger(config::get<bool>(g_context.fake_fps));
	toggle_buttons_[4]->trigger(config::get<bool>(g_context.quest_crash));
	toggle_buttons_[5]->trigger(config::get<bool>(g_context.collision_crash));
	toggle_buttons_[6]->trigger(config::get<bool>(g_context.corrupt_asset_crash));
	toggle_buttons_[7]->trigger(config::get<bool>(g_context.audio_crash));
	toggle_buttons_[8]->trigger(config::get<bool>(g_context.flight));
	toggle_buttons_[9]->trigger(config::get<bool>(g_context.esp));
	toggle_buttons_[10]->trigger(config::get<bool>(g_context.nametags));
	toggle_buttons_[11]->trigger(config::get<bool>(g_context.chams));
	toggle_buttons_[12]->trigger(config::get<bool>(g_context.high_db));
	toggle_buttons_[13]->trigger(config::get<bool>(g_context.exploit_event_1));
	toggle_buttons_[14]->trigger(config::get<bool>(g_context.cozyvrmenu));
}
