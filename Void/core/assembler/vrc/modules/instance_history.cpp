#include "instance_history.hpp"

void instance_history::setup()
{
	auto copyroombtn = std::make_unique<single_button>(location_, 13010, 0, 0, xorstr_(""), [=]
	{
		selected_ = 0;
		show_info();
	}, xorstr_(""));
	copyroombtn->set_active(false);
	single_buttons_.push_back(std::move(copyroombtn));

	auto joinroombtn = std::make_unique<single_button>(location_, 13020, 1, 0, xorstr_(""), [=]
	{
		selected_ = 1;
		show_info();
	}, xorstr_(""));
	joinroombtn->set_active(false);
	single_buttons_.push_back(std::move(joinroombtn));

	auto changebtn = std::make_unique<single_button>(location_, 13030, 2, 0, xorstr_(""), [=]
	{
		selected_ = 2;
		show_info();
	}, xorstr_(""));
	changebtn->set_active(false);
	single_buttons_.push_back(std::move(changebtn));

	auto stopuspeakbtn = std::make_unique<single_button>(location_, 13040, 3, 0, xorstr_(""), [=]
	{
		selected_ = 3;
		show_info();
	}, xorstr_("Force stops copying USpeak Data from all players."));
	stopuspeakbtn->set_active(false);
	single_buttons_.push_back(std::move(stopuspeakbtn));

	auto blacklistbtn = std::make_unique<single_button>(location_, 13050, 0, -1, xorstr_(""), [=]
	{
		selected_ = 4;
		show_info();
	}, xorstr_(""));
	blacklistbtn->set_active(false);
	single_buttons_.push_back(std::move(blacklistbtn));

	auto whitelistbtn = std::make_unique<single_button>(location_, 13060, 1, -1, xorstr_(""), [=]
	{
		selected_ = 5;
		show_info();
	}, xorstr_(""));
	whitelistbtn->set_active(false);
	single_buttons_.push_back(std::move(whitelistbtn));

	auto instance = std::make_unique<single_button>(location_, 13070, 2, -1, xorstr_(""), [=]
	{
		selected_ = 6;
		show_info();
	}, xorstr_(""));
	instance->set_active(false);
	single_buttons_.push_back(std::move(instance));

	auto instance2 = std::make_unique<single_button>(location_, 13080, 3, -1, xorstr_(""), [=]
	{
		selected_ = 7;
		show_info();
	}, xorstr_(""));
	instance2->set_active(false);
	single_buttons_.push_back(std::move(instance2));

	auto instance3 = std::make_unique<single_button>(location_, 13090, 0, -2, xorstr_(""), [=]
	{
		selected_ = 8;
		show_info();
	}, xorstr_(""));
	instance3->set_active(false);
	single_buttons_.push_back(std::move(instance3));

	auto instance4 = std::make_unique<single_button>(location_, 13100, 1, -2, xorstr_(""), [=]
	{
		selected_ = 9;
		show_info();
	}, xorstr_(""));
	instance4->set_active(false);
	single_buttons_.push_back(std::move(instance4));

	auto instance5 = std::make_unique<single_button>(location_, 13110, 2, -2, xorstr_(""), [=]
	{
		selected_ = 10;
		show_info();
	}, xorstr_(""));
	instance5->set_active(false);
	single_buttons_.push_back(std::move(instance5));

	auto instance6 = std::make_unique<single_button>(location_, 13120, 3, -2, xorstr_(""), [=]
	{
		selected_ = 11;
		show_info();
	}, xorstr_(""));
	instance6->set_active(false);
	single_buttons_.push_back(std::move(instance6));

	auto instance7 = std::make_unique<single_button>(location_, 13130, 0, -3, xorstr_(""), [=]
	{
		selected_ = 12;
		show_info();
	}, xorstr_(""));
	instance7->set_active(false);
	single_buttons_.push_back(std::move(instance7));

	auto instance8 = std::make_unique<single_button>(location_, 13140, 1, -3, xorstr_(""), [=]
	{
		selected_ = 13;
		show_info();
	}, xorstr_(""));
	instance8->set_active(false);
	single_buttons_.push_back(std::move(instance8));

	auto instance9 = std::make_unique<single_button>(location_, 13140, 2, -3, xorstr_(""), [=]
	{
		selected_ = 14;
		show_info();
	}, xorstr_(""));
	instance9->set_active(false);
	single_buttons_.push_back(std::move(instance9));

	auto dropportalbtn = std::make_unique<single_button>(location_, 13150, 0, 0, xorstr_("<color=#8960f0>Drop Portal</color>"), [=]
	{
		if (selected_ < instance_history_.size())
		{
			const auto info = utility::split(instance_history_[selected_], xorstr_(":::"));
			misc::drop_portal(info[1]);
		}
	}, xorstr_("Drop a portal to the selected instance."));
	dropportalbtn->set_active(false);
	info_buttons_.push_back(std::move(dropportalbtn));

	auto gotoroombtn = std::make_unique<single_button>(location_, 13160, 1, 0, xorstr_("<color=#8960f0>Join\r\nInstance</color>"), [=]
	{
		if (selected_ < instance_history_.size())
		{
			const auto info = utility::split(instance_history_[selected_], xorstr_(":::"));
			g_context.room_id = info[1];
		}
	}, xorstr_("Joins the selected instance."));
	gotoroombtn->set_active(false);
	info_buttons_.push_back(std::move(gotoroombtn));

	auto copyworldidbtn = std::make_unique<single_button>(location_, 13170, 2, 0, xorstr_("<color=#8960f0>Copy World ID</color>"), [=]
	{
		if (selected_ < instance_history_.size())
		{
			const auto info = utility::split(instance_history_[selected_], xorstr_(":::"));
			utility::set_clipboard(info[1]);
		}
	}, xorstr_("Copies the selected instance's world ID to your clipboard."));
	copyworldidbtn->set_active(false);
	info_buttons_.push_back(std::move(copyworldidbtn));

	auto gobackbtn = std::make_unique<single_button>(location_, 13180, 3, -3, xorstr_("<color=red>Go Back</color>"), [=]
	{
		hide_info();
	}, xorstr_("Go back to the instances page."));
	gobackbtn->set_active(false);
	info_buttons_.push_back(std::move(gobackbtn));
}

void instance_history::hide_all() const
{
	hide();
	for (auto it = info_buttons_.begin(); it != info_buttons_.end(); ++it)
		(*it)->set_active(false);
}

void instance_history::show_all()
{
	main_modules::get().show_back();
	show();

	if (!config::read_instance_history(instance_history_))
	{
		logging::push(FOREGROUND_INTENSE_RED);
		logging::print(xorstr_("[critical] failed to read instance history [\"instance_history.void\"]"));
		logging::pop();
		instance_history_ = {};
	}

	for (std::size_t i = 0; i < single_buttons_.size(); i++)
	{
		if (i < instance_history_.size())
		{
			const auto info = utility::split(instance_history_[i], xorstr_(":::"));
			const auto instance_info = utility::split(info[1], xorstr_(":"));
			std::string the_prefix_you_want = instance_info[1].substr(0, instance_info[1].find(xorstr_("~")));

			single_buttons_[i]->set_button_text(utility::format(xorstr_("<color=#8960f0>{}\r\n{}</color>"), info[0], the_prefix_you_want));
		}
	}
}

void instance_history::show_info() const
{
	main_modules::get().no_back();
	hide();

	for (auto it = info_buttons_.begin(); it != info_buttons_.end(); ++it)
		(*it)->set_active(true);
}

void instance_history::hide_info()
{
	for (auto it = info_buttons_.begin(); it != info_buttons_.end(); ++it)
		(*it)->set_active(false);

	show_all();
}
