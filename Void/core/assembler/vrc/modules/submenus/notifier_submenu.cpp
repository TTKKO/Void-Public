#include "notifier_submenu.hpp"

void notifier_submenu::setup()
{
	auto go_back = std::make_unique<single_button>(location_, 11110, 3, -3, xorstr_("<color=red>Go Back</color>"), [=]
	{
		hide_all();
		customization_modules::get().show_all();
	}, xorstr_("Go back to the previous page"));
	go_back->set_active(false);
	single_buttons_.push_back(std::move(go_back));

	auto friendsonlybtn = std::make_unique<toggle_button>(location_, 11120, 0, 0, xorstr_("<color=#a75cf6>Friends Only</color>"), []
	{
		if (!config::get<bool>(g_context.join_notify_friends))
		{
			config::get<bool>(g_context.join_notify_friends) = true;
		}
	}, []
	{
		if (config::get<bool>(g_context.join_notify_friends))
		{
			config::get<bool>(g_context.join_notify_friends) = false;
		}
	}, xorstr_("Only notifies you if a friend joins the lobby."));

	friendsonlybtn->set_active(false);
	toggle_buttons_.push_back(std::move(friendsonlybtn));
}

void notifier_submenu::show_all() const
{
	show();
	toggle_buttons_[0]->trigger(config::get<bool>(g_context.join_notify_friends));
}

void notifier_submenu::hide_all() const
{
	hide();
}
