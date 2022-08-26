#include "misc2_modules.hpp"
#include "../../../hooks/helpers/camera_handler.hpp"

void misc2_modules::setup()
{
	auto serializebtn = std::make_unique<toggle_button>(location_, 4110, 0, 0, xorstr_("<color=#a75cf6>Deserialize</color>"), []
	{
		if (!config::get<bool>(g_context.serialize))
		{
			config::get<bool>(g_context.serialize) = true;
			misc::handle_avatar_clone(true);
		}
	}, []
	{
		if (config::get<bool>(g_context.serialize))
		{
			config::get<bool>(g_context.serialize) = false;
			misc::handle_avatar_clone(false);
		}
	}, xorstr_("Stop sending events temporarily, think of it as lagswitching."));
	serializebtn->set_active(false);
	toggle_buttons_.push_back(std::move(serializebtn));

	auto invisjoinbtn = std::make_unique<toggle_button>(location_, 4120, 1, 0, xorstr_("<color=#a75cf6>Invisible Join</color>"), []
	{
		if (!config::get<bool>(g_context.invisible_join))
		{
			config::get<bool>(g_context.invisible_join) = true;
		}
	}, []
	{
		if (config::get<bool>(g_context.invisible_join))
		{
			config::get<bool>(g_context.invisible_join) = false;
		}
	}, xorstr_("Join lobbies undetected."));
	invisjoinbtn->set_active(false);
	toggle_buttons_.push_back(std::move(invisjoinbtn));

	auto instancelockbtn = std::make_unique<toggle_button>(location_, 4130, 2, 0,xorstr_("<color=#a75cf6>Instance Lock</color>"), []
	{
		if (!config::get<bool>(g_context.instance_lock))
		{
			config::get<bool>(g_context.instance_lock) = true;
		}
	}, []
	{
		if (config::get<bool>(g_context.instance_lock))
		{
			config::get<bool>(g_context.instance_lock) = false;
		}
	}, xorstr_("Locks the instance as master using an exploit."));
	instancelockbtn->set_active(false);
	toggle_buttons_.push_back(std::move(instancelockbtn));

	auto emojispambtn = std::make_unique<toggle_button>(location_, 4140, 2, -1, xorstr_("<color=#a75cf6>Emoji Spam</color>"), []
	{
		if (!config::get<bool>(g_context.emoji_spam))
		{
			config::get<bool>(g_context.emoji_spam) = true;
		}
	}, []
	{
		if (config::get<bool>(g_context.emoji_spam))
		{
			config::get<bool>(g_context.emoji_spam) = false;
		}
	}, xorstr_("Spams the emoji specified in the desktop menu. If you haven't configured this, do so in the desktop menu."));
	emojispambtn->set_active(false);
	toggle_buttons_.push_back(std::move(emojispambtn));

	auto thirdpersonbtn = std::make_unique<toggle_button>(location_, 4150, 1, -1, xorstr_("<color=#a75cf6>Thirdperson</color>"), []
	{
		if (!g_context.third_person)
		{
			g_context.third_person = true;
			helpers::camera::get().toggle(static_cast<helpers::camera::mode>(config::get<int>(g_context.thirdperson_mode)));
		}
	}, []
	{
		if (g_context.third_person)
		{
			g_context.third_person = false;
			helpers::camera::get().toggle(helpers::camera::mode::off);
		}
	}, xorstr_("Toggles thirdperson. This will use the same mode specified inside the desktop menu."));

	thirdpersonbtn->set_active(false);
	toggle_buttons_.push_back(std::move(thirdpersonbtn));

	auto deserializebindsbtn = std::make_unique<toggle_button>(location_, 4160, 0, -1, xorstr_("<color=#a75cf6>Deserialization\r\nBinds</color>"), []
		{
			if (!config::get<bool>(g_context.deserialize_bind))
			{
				config::get<bool>(g_context.deserialize_bind) = true;
			}
		}, []
		{
			if (config::get<bool>(g_context.deserialize_bind))
			{
				config::get<bool>(g_context.deserialize_bind) = false;
			}
		}, xorstr_("Allows you to toggle deserialization when pressing both triggers on your controllers in unison."));

	deserializebindsbtn->set_active(false);
	toggle_buttons_.push_back(std::move(deserializebindsbtn));

	auto antiattachbtn = std::make_unique<toggle_button>(location_, 4170, 3, 0, xorstr_("<color=#a75cf6>Anti-Attach\r\n(Infinite Pos.)</color>"), []
		{
			if (!g_context.anti_aim)
				g_context.anti_aim = true;
		}, []
		{
			if (g_context.anti_aim)
				g_context.anti_aim = false;
		}, xorstr_("Spoofs your photon position to break users cameras if they are attached to you."));
	antiattachbtn->set_active(false);
	toggle_buttons_.push_back(std::move(antiattachbtn));
}

void misc2_modules::show_all() const
{
	main_modules::get().show_back();
	show();
	toggle_buttons_[0]->trigger(config::get<bool>(g_context.serialize));
	toggle_buttons_[1]->trigger(config::get<bool>(g_context.invisible_join));
	toggle_buttons_[2]->trigger(config::get<bool>(g_context.instance_lock));
	toggle_buttons_[3]->trigger(config::get<bool>(g_context.emoji_spam));
	toggle_buttons_[4]->trigger(g_context.third_person);
	toggle_buttons_[5]->trigger(config::get<bool>(g_context.deserialize_bind));
	toggle_buttons_[6]->trigger(g_context.anti_aim);

}
