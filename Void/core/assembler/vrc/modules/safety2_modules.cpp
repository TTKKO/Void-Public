#include "safety2_modules.hpp"

void safety2_modules::setup()
{
	auto antiavataraudiobtn = std::make_unique<toggle_button>(location_, 5110, 0, 0,xorstr_("<color=#a75cf6>Anti-Avatar Audio</color>"), []
	{
		if (!config::get<bool>(g_context.anti_avatar_audio))
		{
			config::get<bool>(g_context.anti_avatar_audio) = true;
		}
	}, []
	{
		if (config::get<bool>(g_context.anti_avatar_audio))
		{
			config::get<bool>(g_context.anti_avatar_audio) = false;
		}
	}, xorstr_(
		"Prevents avatars with audio attached from showing. (avatar audio=cringe)"));

	antiavataraudiobtn->set_active(false);
	toggle_buttons_.push_back(std::move(antiavataraudiobtn));

	auto antironulls = std::make_unique<toggle_button>(location_, 5120, 1, 0, xorstr_("<color=#a75cf6>Anti-RO.Nulls</color>"), []
	{
		if (!config::get<bool>(g_context.anti_ro_nulls))
		{
			config::get<bool>(g_context.anti_ro_nulls) = true;
		}
	}, []
	{
		if (config::get<bool>(g_context.anti_ro_nulls))
		{
			config::get<bool>(g_context.anti_ro_nulls) = false;
		}
	}, xorstr_(
		"Anti's corrupted asset bundles and similar avis. Explained vague for secrecy."));

	antironulls->set_active(false);
	toggle_buttons_.push_back(std::move(antironulls));

	auto antiaudiomixersbtn = std::make_unique<toggle_button>(location_, 5130, 2, 0,xorstr_("<color=#a75cf6>Anti-Audio Mixers</color>"), []
	{
		if (!config::get<bool>(g_context.anti_audio_mixers))
		{
			config::get<bool>(g_context.anti_audio_mixers) = true;
		}
	}, []
	{
		if (config::get<bool>(g_context.anti_audio_mixers))
		{
			config::get<bool>(g_context.anti_audio_mixers) = false;
		}
	}, xorstr_("Anti's malicious audio mixers on avatars. Keep this on."));

	antiaudiomixersbtn->set_active(false);
	toggle_buttons_.push_back(std::move(antiaudiomixersbtn));

	auto antiarrayoverflowbtn = std::make_unique<toggle_button>(location_, 5140, 3, 0,xorstr_("<color=#a75cf6>Anti-Array Overflow</color>"), []
	{
		if (!config::get<bool>(g_context.anti_array_overflow))
		{
			config::get<bool>(g_context.anti_array_overflow) = true;
		}
	}, []
	{
		if (config::get<bool>(g_context.anti_array_overflow))
		{
			config::get<bool>(g_context.anti_array_overflow) =
				false;
		}
	}, xorstr_("Prevents a stackoverflow when a bad bundle gets loaded into memory. Keep this on."));

	antiarrayoverflowbtn->set_active(false);
	toggle_buttons_.push_back(std::move(antiarrayoverflowbtn));

	auto antioobbtn = std::make_unique<toggle_button>(location_, 5150, 0, -1, xorstr_("<color=#a75cf6>Anti-OOB</color>"), []
	{
		if (!config::get<bool>(g_context.anti_oob))
		{
			config::get<bool>(g_context.anti_oob) = true;
		}
	}, []
	{
		if (config::get<bool>(g_context.anti_oob))
		{
			config::get<bool>(g_context.anti_oob) = false;
		}
	}, xorstr_("Anti's majority of corrupted asset bundles. Explained vague for secrecy."));

	antioobbtn->set_active(false);
	toggle_buttons_.push_back(std::move(antioobbtn));

	auto antinodeexploitbtn = std::make_unique<toggle_button>(location_, 5160, 1, -1, xorstr_("<color=#a75cf6>Anti-Node Overflow</color>"), []
	{
		if (!config::get<bool>(g_context.anti_aa12))
		{
			config::get<bool>(g_context.anti_aa12) = true;
		}
	}, []
	{
		if (config::get<bool>(g_context.anti_aa12))
		{
			config::get<bool>(g_context.anti_aa12) = false;
		}
	}, xorstr_("Patches a stackoverflow bug inside UnityPlayer."));

	antinodeexploitbtn->set_active(false);
	toggle_buttons_.push_back(std::move(antinodeexploitbtn));

	auto blockdownloadsbtn = std::make_unique<toggle_button>(location_, 5170, 2, -1, xorstr_("<color=#a75cf6>Block Downloads</color>"), []
	{
		if (!g_context.block_downloads)
			g_context.block_downloads = true;
			misc::toggle_download_manager(!g_context.block_downloads);
	}, []
	{
		if (g_context.block_downloads)
			g_context.block_downloads = false;
			misc::toggle_download_manager(!g_context.block_downloads);
	}, xorstr_("Blocks VRChat's download manager temporarily."));

	blockdownloadsbtn->set_active(false);
	toggle_buttons_.push_back(std::move(blockdownloadsbtn));

	auto allowfriendsbtn = std::make_unique<toggle_button>(location_, 5180, 3, -1, xorstr_("<color=#a75cf6>Allow Friends</color>"), []
	{
		if (!config::get<bool>(g_context.allow_friends))
		{
			config::get<bool>(g_context.allow_friends) = true;
		}
	}, []
	{
		if (config::get<bool>(g_context.allow_friends))
		{
			config::get<bool>(g_context.allow_friends) = false;
		}
	}, xorstr_("Allows friends to bypass VOID's antis."));

	allowfriendsbtn->set_active(false);
	toggle_buttons_.push_back(std::move(allowfriendsbtn));

	auto streamermodebtn = std::make_unique<toggle_button>(location_, 5190, 0, -2, xorstr_("<color=#a75cf6>Streamer Mode</color>"), []
	{
		if (!config::get<bool>(g_context.anti_stream))
		{
			config::get<bool>(g_context.anti_stream) = true;
		}
	}, []
	{
		if (config::get<bool>(g_context.anti_stream))
		{
			config::get<bool>(g_context.anti_stream) = false;
		}
	}, xorstr_("Hides your name and \"stealthifies\" void's vr menu (On load only! Save & restart for this to take effect)"));

	streamermodebtn->set_active(false);
	toggle_buttons_.push_back(std::move(streamermodebtn));
}

void safety2_modules::show_all() const
{
	main_modules::get().show_back();
	show();
	toggle_buttons_[0]->trigger(config::get<bool>(g_context.anti_avatar_audio));
	toggle_buttons_[1]->trigger(config::get<bool>(g_context.anti_ro_nulls));
	toggle_buttons_[2]->trigger(config::get<bool>(g_context.anti_audio_mixers));
	toggle_buttons_[3]->trigger(config::get<bool>(g_context.anti_array_overflow));
	toggle_buttons_[4]->trigger(config::get<bool>(g_context.anti_oob));
	toggle_buttons_[5]->trigger(config::get<bool>(g_context.anti_aa12));
	toggle_buttons_[6]->trigger(g_context.block_downloads);
	toggle_buttons_[7]->trigger(config::get<bool>(g_context.allow_friends));
	toggle_buttons_[8]->trigger(config::get<bool>(g_context.anti_stream));
}
