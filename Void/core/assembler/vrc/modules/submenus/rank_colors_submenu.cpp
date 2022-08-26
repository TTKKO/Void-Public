#include "rank_colors_submenu.hpp"

void rank_colors_submenu::update_values() const
{
	switch (selected_)
	{
	case 0:
		{
			config::get<sdk::color>(g_context.c_visitor) =
			{
				slider_buttons_[0]->this_slider->get_value(),
				slider_buttons_[1]->this_slider->get_value(),
				slider_buttons_[2]->this_slider->get_value()
			};
			hs_buttons_[0]->set_button_text(utility::format(
				xorstr_("<color=#{}>Visitors</color>"), config::get<sdk::color>(g_context.c_visitor).get_hex()));
			break;
		}
	case 1:
		{
			config::get<sdk::color>(g_context.c_newuser) =
			{
				slider_buttons_[0]->this_slider->get_value(),
				slider_buttons_[1]->this_slider->get_value(),
				slider_buttons_[2]->this_slider->get_value()
			};
			hs_buttons_[1]->set_button_text(utility::format(
				xorstr_("<color=#{}>New Users</color>"), config::get<sdk::color>(g_context.c_newuser).get_hex()));
			break;
		}
	case 2:
		{
			config::get<sdk::color>(g_context.c_user) =
			{
				slider_buttons_[0]->this_slider->get_value(),
				slider_buttons_[1]->this_slider->get_value(),
				slider_buttons_[2]->this_slider->get_value()
			};
			hs_buttons_[2]->set_button_text(utility::format(
				xorstr_("<color=#{}>Users</color>"), config::get<sdk::color>(g_context.c_user).get_hex()));
			break;
		}
	case 3:
		{
			config::get<sdk::color>(g_context.c_known) =
			{
				slider_buttons_[0]->this_slider->get_value(),
				slider_buttons_[1]->this_slider->get_value(),
				slider_buttons_[2]->this_slider->get_value()
			};
			hs_buttons_[3]->set_button_text(utility::format(
				xorstr_("<color=#{}>Known Users</color>"), config::get<sdk::color>(g_context.c_known).get_hex()));
			break;
		}
	case 4:
		{
			config::get<sdk::color>(g_context.c_trusted) =
			{
				slider_buttons_[0]->this_slider->get_value(),
				slider_buttons_[1]->this_slider->get_value(),
				slider_buttons_[2]->this_slider->get_value()
			};
			hs_buttons_[4]->set_button_text(utility::format(
				xorstr_("<color=#{}>Trusted Users</color>"), config::get<sdk::color>(g_context.c_trusted).get_hex()));
			break;
		}
	case 5:
		{
			config::get<sdk::color>(g_context.c_friend) =
			{
				slider_buttons_[0]->this_slider->get_value(),
				slider_buttons_[1]->this_slider->get_value(),
				slider_buttons_[2]->this_slider->get_value()
			};
			hs_buttons_[5]->set_button_text(utility::format(
				xorstr_("<color=#{}>Friends</color>"), config::get<sdk::color>(g_context.c_friend).get_hex()));
			break;
		}
	default:
		{
			hs_buttons_[0]->set_button_text(utility::format(xorstr_("<color=#{}>Visitors</color>"), config::get<sdk::color>(g_context.c_visitor).get_hex()));
			hs_buttons_[1]->set_button_text(utility::format(xorstr_("<color=#{}>New Users</color>"), config::get<sdk::color>(g_context.c_newuser).get_hex()));
			hs_buttons_[2]->set_button_text(utility::format(xorstr_("<color=#{}>Users</color>"), config::get<sdk::color>(g_context.c_user).get_hex()));
			hs_buttons_[3]->set_button_text(utility::format(xorstr_("<color=#{}>Known Users</color>"), config::get<sdk::color>(g_context.c_known).get_hex()));
			hs_buttons_[4]->set_button_text(utility::format(xorstr_("<color=#{}>Trusted Users</color>"), config::get<sdk::color>(g_context.c_trusted).get_hex()));
			hs_buttons_[5]->set_button_text(utility::format(xorstr_("<color=#{}>Friends</color>"), config::get<sdk::color>(g_context.c_friend).get_hex()));
		}
	}
}

void rank_colors_submenu::setup()
{
	auto go_back = std::make_unique<single_button>(location_, 10010, 3, -3, xorstr_("<color=red>Go Back</color>"), [=]
	{
		hide_all();
		customization_modules::get().show_all();
	}, xorstr_("Go back to the previous page"));
	go_back->set_active(false);
	single_buttons_.push_back(std::move(go_back));

	slider_buttons_.emplace_back(std::make_unique<slider_button>(location_, 10080, -3, xorstr_("<color=#FF0000>Red</color>"), xorstr_("Red slider (0-255)")));
	slider_buttons_[0]->set_action([=]
	{
		slider_buttons_[0]->set_slider_text(xorstr_("<color=#FF0000>Red (") + std::to_string(static_cast<std::int32_t>(slider_buttons_[0]->this_slider->get_value() * 255.f)) + xorstr_(")</color>"));
		update_values();
	});
	slider_buttons_[0]->set_active(false);

	slider_buttons_.emplace_back(std::make_unique<slider_button>(location_, 10090, -4, xorstr_("<color=#00FF00>Green</color>"), xorstr_("Green slider (0-255)")));
	slider_buttons_[1]->set_action([=]
	{
		slider_buttons_[1]->set_slider_text(xorstr_("<color=#00FF00>Green (") + std::to_string(static_cast<std::int32_t>(slider_buttons_[1]->this_slider->get_value() * 255.f)) + xorstr_(")</color>"));
		update_values();
	});
	slider_buttons_[1]->set_active(false);

	slider_buttons_.emplace_back(std::make_unique<slider_button>(location_, 10100, -5, xorstr_("<color=#0000FF>Blue</color>"), xorstr_("Blue slider (0-255)")));
	slider_buttons_[2]->set_action([=]
	{
		slider_buttons_[2]->set_slider_text(xorstr_("<color=#0000FF>Blue (") + std::to_string(static_cast<std::int32_t>(slider_buttons_[2]->this_slider->get_value() * 255.f)) + xorstr_(")</color>"));
		update_values();
	});
	slider_buttons_[2]->set_active(false);

	auto visitorsbtn = std::make_unique<half_single_button>(location_, 10020, 0, 0, utility::format(xorstr_("<color=#{}>Visitors</color>"), config::get<sdk::color>(g_context.c_visitor).get_hex()), [=]
	{
		selected_ = 0;
		const auto col = &config::get<sdk::color>(g_context.c_visitor);
		slider_buttons_[0]->this_slider->set_value(col->base_alpha()[0]);
		slider_buttons_[0]->set_slider_text(xorstr_("<color=#FF0000>Red (") + std::to_string(col->operator[](0)) + xorstr_(")</color>"));
		slider_buttons_[1]->this_slider->set_value(col->base_alpha()[1]);
		slider_buttons_[1]->set_slider_text(xorstr_("<color=#00FF00>Green (") + std::to_string(col->operator[](1)) + xorstr_(")</color>"));
		slider_buttons_[2]->this_slider->set_value(col->base_alpha()[2]);
		slider_buttons_[2]->set_slider_text(xorstr_("<color=#0000FF>Blue (") + std::to_string(col->operator[](2)) + xorstr_(")</color>"));

		slider_buttons_[0]->set_active(false);
		slider_buttons_[1]->set_active(false);
		slider_buttons_[2]->set_active(false);
		slider_buttons_[0]->set_active(true);
		slider_buttons_[1]->set_active(true);
		slider_buttons_[2]->set_active(true);
	}, xorstr_("Select \"Visitors\""));
	hs_buttons_.push_back(std::move(visitorsbtn));

	auto newusersbtn = std::make_unique<half_single_button>(location_, 10030, 1, 0, utility::format(xorstr_("<color=#{}>New Users</color>"), config::get<sdk::color>(g_context.c_newuser).get_hex()), [=]
	{
		selected_ = 1;

		const auto col = &config::get<sdk::color>(g_context.c_newuser);
		slider_buttons_[0]->this_slider->set_value(col->base_alpha()[0]);
		slider_buttons_[0]->set_slider_text(xorstr_("<color=#FF0000>Red (") + std::to_string(col->operator[](0)) + xorstr_(")</color>"));
		slider_buttons_[1]->this_slider->set_value(col->base_alpha()[1]);
		slider_buttons_[1]->set_slider_text(xorstr_("<color=#00FF00>Green (") + std::to_string(col->operator[](1)) + xorstr_(")</color>"));
		slider_buttons_[2]->this_slider->set_value(col->base_alpha()[2]);
		slider_buttons_[2]->set_slider_text(xorstr_("<color=#0000FF>Blue (") + std::to_string(col->operator[](2)) + xorstr_(")</color>"));

		slider_buttons_[0]->set_active(false);
		slider_buttons_[1]->set_active(false);
		slider_buttons_[2]->set_active(false);
		slider_buttons_[0]->set_active(true);
		slider_buttons_[1]->set_active(true);
		slider_buttons_[2]->set_active(true);
	}, xorstr_("Select \"New Users\""));
	hs_buttons_.push_back(std::move(newusersbtn));

	auto userbtn = std::make_unique<half_single_button>(location_, 10040, 2, 0, utility::format(xorstr_("<color=#{}>Users</color>"), config::get<sdk::color>(g_context.c_user).get_hex()), [=]
	{
		selected_ = 2;

		const auto col = &config::get<sdk::color>(g_context.c_user);
		slider_buttons_[0]->this_slider->set_value(col->base_alpha()[0]);
		slider_buttons_[0]->set_slider_text(xorstr_("<color=#FF0000>Red (") + std::to_string(col->operator[](0)) + xorstr_(")</color>"));
		slider_buttons_[1]->this_slider->set_value(col->base_alpha()[1]);
		slider_buttons_[1]->set_slider_text(xorstr_("<color=#00FF00>Green (") + std::to_string(col->operator[](1)) + xorstr_(")</color>"));
		slider_buttons_[2]->this_slider->set_value(col->base_alpha()[2]);
		slider_buttons_[2]->set_slider_text(xorstr_("<color=#0000FF>Blue (") + std::to_string(col->operator[](2)) + xorstr_(")</color>"));

		slider_buttons_[0]->set_active(false);
		slider_buttons_[1]->set_active(false);
		slider_buttons_[2]->set_active(false);
		slider_buttons_[0]->set_active(true);
		slider_buttons_[1]->set_active(true);
		slider_buttons_[2]->set_active(true);
	}, xorstr_("Select \"Users\""));
	hs_buttons_.push_back(std::move(userbtn));

	auto knownuserbtn = std::make_unique<half_single_button>(location_, 10050, 3, 0, utility::format(xorstr_("<color=#{}>Known Users</color>"), config::get<sdk::color>(g_context.c_known).get_hex()), [=]
	{
		selected_ = 3;

		const auto col = &config::get<sdk::color>(g_context.c_known);
		slider_buttons_[0]->this_slider->set_value(col->base_alpha()[0]);
		slider_buttons_[0]->set_slider_text(xorstr_("<color=#FF0000>Red (") + std::to_string(col->operator[](0)) + xorstr_(")</color>"));
		slider_buttons_[1]->this_slider->set_value(col->base_alpha()[1]);
		slider_buttons_[1]->set_slider_text(xorstr_("<color=#00FF00>Green (") + std::to_string(col->operator[](1)) + xorstr_(")</color>"));
		slider_buttons_[2]->this_slider->set_value(col->base_alpha()[2]);
		slider_buttons_[2]->set_slider_text(xorstr_("<color=#0000FF>Blue (") + std::to_string(col->operator[](2)) + xorstr_(")</color>"));

		slider_buttons_[0]->set_active(false);
		slider_buttons_[1]->set_active(false);
		slider_buttons_[2]->set_active(false);
		slider_buttons_[0]->set_active(true);
		slider_buttons_[1]->set_active(true);
		slider_buttons_[2]->set_active(true);
	}, xorstr_("Select \"Known Users\""));
	hs_buttons_.push_back(std::move(knownuserbtn));

	auto trusteduserbtn = std::make_unique<half_single_button>(location_, 10060, 1, -1, utility::format(xorstr_("<color=#{}>Trusted Users</color>"), config::get<sdk::color>(g_context.c_trusted).get_hex()), [=]
	{
		selected_ = 4;

		const auto col = &config::get<sdk::color>(g_context.c_trusted);
		slider_buttons_[0]->this_slider->set_value(col->base_alpha()[0]);
		slider_buttons_[0]->set_slider_text(xorstr_("<color=#FF0000>Red (") + std::to_string(col->operator[](0)) + xorstr_(")</color>"));
		slider_buttons_[1]->this_slider->set_value(col->base_alpha()[1]);
		slider_buttons_[1]->set_slider_text(xorstr_("<color=#00FF00>Green (") + std::to_string(col->operator[](1)) + xorstr_(")</color>"));
		slider_buttons_[2]->this_slider->set_value(col->base_alpha()[2]);
		slider_buttons_[2]->set_slider_text(xorstr_("<color=#0000FF>Blue (") + std::to_string(col->operator[](2)) + xorstr_(")</color>"));

		slider_buttons_[0]->set_active(false);
		slider_buttons_[1]->set_active(false);
		slider_buttons_[2]->set_active(false);
		slider_buttons_[0]->set_active(true);
		slider_buttons_[1]->set_active(true);
		slider_buttons_[2]->set_active(true);
	}, xorstr_("Select \"Trusted Users\""));
	hs_buttons_.push_back(std::move(trusteduserbtn));

	auto friendsbtn = std::make_unique<half_single_button>(location_, 10070, 2, -1, utility::format(xorstr_("<color=#{}>Friends</color>"), config::get<sdk::color>(g_context.c_friend).get_hex()), [=]
	{
		selected_ = 5;

		const auto col = &config::get<sdk::color>(g_context.c_friend);
		slider_buttons_[0]->this_slider->set_value(col->base_alpha()[0]);
		slider_buttons_[0]->set_slider_text(xorstr_("<color=#FF0000>Red (") + std::to_string(col->operator[](0)) + xorstr_(")</color>"));
		slider_buttons_[1]->this_slider->set_value(col->base_alpha()[1]);
		slider_buttons_[1]->set_slider_text(xorstr_("<color=#00FF00>Green (") + std::to_string(col->operator[](1)) + xorstr_(")</color>"));
		slider_buttons_[2]->this_slider->set_value(col->base_alpha()[2]);
		slider_buttons_[2]->set_slider_text(xorstr_("<color=#0000FF>Blue (") + std::to_string(col->operator[](2)) + xorstr_(")</color>"));

		slider_buttons_[0]->set_active(false);
		slider_buttons_[1]->set_active(false);
		slider_buttons_[2]->set_active(false);
		slider_buttons_[0]->set_active(true);
		slider_buttons_[1]->set_active(true);
		slider_buttons_[2]->set_active(true);
	}, xorstr_("Select \"Friends\""));
	hs_buttons_.push_back(std::move(friendsbtn));

	hs_buttons_[0]->set_active(false);
	hs_buttons_[1]->set_active(false);
	hs_buttons_[2]->set_active(false);
	hs_buttons_[3]->set_active(false);
	hs_buttons_[4]->set_active(false);
	hs_buttons_[5]->set_active(false);
}

void rank_colors_submenu::show_all()
{
	slider_buttons_[0]->set_slider_text(xorstr_("<color=#FF0000>Red</color>"));
	slider_buttons_[1]->set_slider_text(xorstr_("<color=#00FF00>Green</color>"));
	slider_buttons_[2]->set_slider_text(xorstr_("<color=#0000FF>Blue</color>"));

	for (auto it = hs_buttons_.begin(); it != hs_buttons_.end(); ++it)
		(*it)->set_active(true);
	for (auto it = slider_buttons_.begin(); it != slider_buttons_.end(); ++it)
		(*it)->set_active(true);

	show();

	selected_ = -1;
	update_values();
}

void rank_colors_submenu::hide_all() const
{
	for (auto it = hs_buttons_.begin(); it != hs_buttons_.end(); ++it)
		(*it)->set_active(false);
	for (auto it = slider_buttons_.begin(); it != slider_buttons_.end(); ++it)
		(*it)->set_active(false);

	hide();
}
