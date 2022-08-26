#include "safety_modules.hpp"

void safety_modules::setup()
{
	auto antiportal_button = std::make_unique<toggle_button>(location_, 2110, 0, 0,xorstr_("<color=#a75cf6>Anti-Portal</color>"), []
	{
		if (!config::get<bool>(g_context.anti_portal))
		{
			config::get<bool>(g_context.anti_portal) = true;
		}
	}, []
	{
		if (config::get<bool>(g_context.anti_portal))
		{
			config::get<bool>(g_context.anti_portal) = false;
		}
	}, xorstr_("Removes portal colliders"));

	antiportal_button->set_active(false);
	toggle_buttons_.push_back(std::move(antiportal_button));

	auto antiworldtriggersbtn = std::make_unique<toggle_button>(location_, 2120, 1, 0,xorstr_("<color=#a75cf6>Anti-World Triggers</color>"), []
	{
		if (!config::get<bool>(g_context.anti_worldtriggers))
		{
			config::get<bool>(g_context.anti_worldtriggers) = true;
		}
	}, []
	{
		if (config::get<bool>(g_context.anti_worldtriggers))
		{
			config::get<bool>(g_context.anti_worldtriggers) = false;
		}
	}, xorstr_("Attempts to block world triggers"));

	antiworldtriggersbtn->set_active(false);
	toggle_buttons_.push_back(std::move(antiworldtriggersbtn));

	auto antiudonbtn = std::make_unique<toggle_button>(location_, 2130, 2, 0, xorstr_("<color=#a75cf6>Anti-Udon Events</color>"), []
	{
		if (!config::get<bool>(g_context.anti_udon_events))
		{
			config::get<bool>(g_context.anti_udon_events) = true;
		}
	}, []
	{
		if (config::get<bool>(g_context.anti_udon_events))
		{
			config::get<bool>(g_context.anti_udon_events) = false;
		}
	}, xorstr_("Attempts to block udon events"));

	antiudonbtn->set_active(false);
	toggle_buttons_.push_back(std::move(antiudonbtn));

	auto antiuspeakbtn = std::make_unique<toggle_button>(location_, 2150, 0, -1,xorstr_("<color=#a75cf6>Anti-USpeak Exploit</color>"), []
	{
		if (!config::get<bool>(g_context.anti_uspeak_exploit))
		{
			config::get<bool>(g_context.anti_uspeak_exploit) = true;
		}
	}, []
	{
		if (config::get<bool>(g_context.anti_uspeak_exploit))
		{
			config::get<bool>(g_context.anti_uspeak_exploit) = false;
		}
	}, xorstr_("Prevents users from sending malicious USpeak packets"));
	antiuspeakbtn->set_active(false);
	toggle_buttons_.push_back(std::move(antiuspeakbtn));

	auto antiownershipdesyncbtn = std::make_unique<toggle_button>(location_, 2160, 1, -1,xorstr_("<color=#a75cf6>Anti-Master DC</color>"), []
	{
		if (!config::get<bool>(g_context.anti_master_dc))
		{
			config::get<bool>(g_context.anti_master_dc) = true;
		}
	}, []
	{
		if (config::get<bool>(g_context.anti_master_dc))
		{
			config::get<bool>(g_context.anti_master_dc) = false;
		}
	}, xorstr_("Prevents disconnection as master."));

	antiownershipdesyncbtn->set_active(false);
	toggle_buttons_.push_back(std::move(antiownershipdesyncbtn));

	auto reducebadactivitybtn = std::make_unique<toggle_button>(location_, 2170, 2, -1,xorstr_("<color=#a75cf6>Reduce Bad Activity</color>"), []
	{
		if (!config::get<bool>(g_context.reduce_bad_activity))
		{
			config::get<bool>(g_context.reduce_bad_activity) = true;
		}
	}, []
	{
		if (config::get<bool>(g_context.reduce_bad_activity))
		{
			config::get<bool>(g_context.reduce_bad_activity) = false;
		}
	}, xorstr_(
		"Attempts to reduce bad activity as much as possible."));

	reducebadactivitybtn->set_active(false);
	toggle_buttons_.push_back(std::move(reducebadactivitybtn));

	auto antiobjectspambtn = std::make_unique<toggle_button>(location_, 2180, 3, -1,xorstr_("<color=#a75cf6>Anti-Object Spam</color>"), []
	{
		if (!config::get<bool>(g_context.anti_object_spam))
		{
			config::get<bool>(g_context.anti_object_spam) = true;
		}
	}, []
	{
		if (config::get<bool>(g_context.anti_object_spam))
		{
			config::get<bool>(g_context.anti_object_spam) = false;
		}
	}, xorstr_("Pickups become local."));

	antiobjectspambtn->set_active(false);
	toggle_buttons_.push_back(std::move(antiobjectspambtn));

	auto avatarblacklistbtn = std::make_unique<toggle_button>(location_, 2190, 0, -2,xorstr_("<color=#a75cf6>Avatar Blacklist</color>"), []
	{
		if (!config::get<
			bool>(g_context.anti_blacklisted_avatars))
		{
			config::get<bool>(g_context.anti_blacklisted_avatars)
				= true;
		}
	}, []
	{
		if (config::get<bool>(g_context.anti_blacklisted_avatars))
		{
			config::get<bool>(g_context.anti_blacklisted_avatars) =
				false;
		}
	}, xorstr_("Enables VOID's avatar blacklist system."));

	avatarblacklistbtn->set_active(false);
	toggle_buttons_.push_back(std::move(avatarblacklistbtn));

	auto antiaudocrashbtn = std::make_unique<toggle_button>(location_, 2200, 1, -2,xorstr_("<color=#a75cf6>Anti-Audio Crash</color>"), []
	{
		if (!config::get<bool>(g_context.anti_audio_crash))
		{
			config::get<bool>(g_context.anti_audio_crash) = true;
		}
	}, []
	{
		if (config::get<bool>(g_context.anti_audio_crash))
		{
			config::get<bool>(g_context.anti_audio_crash) = false;
		}
	}, xorstr_("Attempts to block malicious audio packets."));

	antiaudocrashbtn->set_active(false);
	toggle_buttons_.push_back(std::move(antiaudocrashbtn));

	auto antiavatarcrashbtn = std::make_unique<toggle_button>(location_, 2210, 2, -2,xorstr_("<color=#a75cf6>Anti-Avatar Crash</color>"), []
	{
		if (!config::get<bool>(g_context.anti_avatar_crash))
		{
			config::get<bool>(g_context.anti_avatar_crash) = true;
		}
	}, []
	{
		if (config::get<bool>(g_context.anti_avatar_crash))
		{
			config::get<bool>(g_context.anti_avatar_crash) = false;
		}
	}, xorstr_(
		"Attempts to block malicious avatars. (will show up as an ERROR robot)"));

	antiavatarcrashbtn->set_active(false);
	toggle_buttons_.push_back(std::move(antiavatarcrashbtn));

	auto detectinvisiblesbtn = std::make_unique<toggle_button>(location_, 2220, 3, -2,xorstr_("<color=#a75cf6>Detect Invisibles</color>"), []
	{
		if (!config::get<bool>(g_context.detect_invisibles))
		{
			config::get<bool>(g_context.detect_invisibles) = true;
		}
	}, []
	{
		if (config::get<bool>(g_context.detect_invisibles))
		{
			config::get<bool>(g_context.detect_invisibles) = false;
		}
	}, xorstr_("Logs invisible users."));

	detectinvisiblesbtn->set_active(false);
	toggle_buttons_.push_back(std::move(detectinvisiblesbtn));

	auto anticamerafreezebtn = std::make_unique<toggle_button>(location_, 2140, 3, 0,xorstr_("<color=#a75cf6>Anti-Video URL</color>"), []
	{
		if (!config::get<bool>(g_context.anti_video_exploit))
		{
			config::get<bool>(g_context.anti_video_exploit) =
				true;
		}
	}, []
	{
		if (config::get<bool>(g_context.anti_video_exploit))
		{
			config::get<bool>(g_context.anti_video_exploit) = false;
		}
	}, xorstr_("Prevents users from playing videos from unknown sources."));

	anticamerafreezebtn->set_active(false);
	toggle_buttons_.push_back(std::move(anticamerafreezebtn));

	auto preventportalsbtn = std::make_unique<toggle_button>(location_, 2230, 0, -3,xorstr_("<color=#a75cf6>Prevent Portals</color>"), []
	{
		if (!config::get<bool>(g_context.prevent_portals))
		{
			config::get<bool>(g_context.prevent_portals) = true;
		}
	}, []
	{
		if (config::get<bool>(g_context.prevent_portals))
		{
			config::get<bool>(g_context.prevent_portals) = false;
		}
	}, xorstr_("Automatically destroys spawned portals."));

	preventportalsbtn->set_active(false);
	toggle_buttons_.push_back(std::move(preventportalsbtn));

	auto antiblockbtn = std::make_unique<toggle_button>(location_, 2240, 1, -3, xorstr_("<color=#a75cf6>Anti-Block</color>"), []
	{
		if (!config::get<bool>(g_context.anti_block))
		{
			config::get<bool>(g_context.anti_block) = true;
		}
	}, []
	{
		if (config::get<bool>(g_context.anti_block))
		{
			config::get<bool>(g_context.anti_block) = false;
		}
	}, xorstr_("Allows you to see users who have you blocked."));

	antiblockbtn->set_active(false);
	toggle_buttons_.push_back(std::move(antiblockbtn));

	auto antiinstancelockbtn = std::make_unique<toggle_button>(location_, 2250, 2, -3,xorstr_("<color=#a75cf6>Anti-Instance Lock</color>"), []
	{
		if (!config::get<bool>(g_context.anti_instance_lock))
		{
			config::get<bool>(g_context.anti_instance_lock) = true;
		}
	}, []
	{
		if (config::get<bool>(g_context.anti_instance_lock))
		{
			config::get<bool>(g_context.anti_instance_lock) = false;
		}
	}, xorstr_("Prevents the instance lock exploit locally."));

	antiinstancelockbtn->set_active(false);
	toggle_buttons_.push_back(std::move(antiinstancelockbtn));
}

void safety_modules::show_all() const
{
	main_modules::get().show_back();
	show();
	toggle_buttons_[0]->trigger(config::get<bool>(g_context.anti_portal));
	toggle_buttons_[1]->trigger(config::get<bool>(g_context.anti_worldtriggers));
	toggle_buttons_[2]->trigger(config::get<bool>(g_context.anti_udon_events));
	toggle_buttons_[3]->trigger(config::get<bool>(g_context.anti_uspeak_exploit));
	toggle_buttons_[4]->trigger(config::get<bool>(g_context.anti_master_dc));
	toggle_buttons_[5]->trigger(config::get<bool>(g_context.reduce_bad_activity));
	toggle_buttons_[6]->trigger(config::get<bool>(g_context.anti_object_spam));
	toggle_buttons_[7]->trigger(config::get<bool>(g_context.anti_blacklisted_avatars));
	toggle_buttons_[8]->trigger(config::get<bool>(g_context.anti_audio_crash));
	toggle_buttons_[9]->trigger(config::get<bool>(g_context.anti_avatar_crash));
	toggle_buttons_[10]->trigger(config::get<bool>(g_context.detect_invisibles));
	toggle_buttons_[11]->trigger(config::get<bool>(g_context.anti_video_exploit));
	toggle_buttons_[12]->trigger(config::get<bool>(g_context.prevent_portals));
	toggle_buttons_[13]->trigger(config::get<bool>(g_context.anti_block));
	toggle_buttons_[14]->trigger(config::get<bool>(g_context.anti_instance_lock));
}
