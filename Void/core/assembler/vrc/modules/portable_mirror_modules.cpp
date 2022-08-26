#include "portable_mirror_modules.hpp"

void portable_mirror_modules::setup()
{
	auto spawnbtn = std::make_unique<single_button>(location_, 160010, 0, 0, xorstr_("<color=#2faceb>Spawn\r\nor\r\nDespawn</color>"), [=]
		{
			helpers::portable_mirror::get().toggle_mirror();
		}, xorstr_("Spawns a portable mirror in front of you."));
	spawnbtn->set_active(false);
	single_buttons_.push_back(std::move(spawnbtn));

	auto optimizedbtn = std::make_unique<toggle_button>(location_, 160020, 1, 0, xorstr_("<color=#2faceb>Optimized</color>"), []
		{
			if (!config::get<bool>(g_context.optimized_mirror))
			{
				config::get<bool>(g_context.optimized_mirror) = true;
				helpers::portable_mirror::get().update_optimization(config::get<bool>(g_context.optimized_mirror));
			}
		}, []
		{
			if (config::get<bool>(g_context.optimized_mirror))
			{
				config::get<bool>(g_context.optimized_mirror) = false;
				helpers::portable_mirror::get().update_optimization(config::get<bool>(g_context.optimized_mirror));
			}
		}, xorstr_("Prevents the mirror from rendering background objects."));
	optimizedbtn->set_active(false);
	toggle_buttons_.push_back(std::move(optimizedbtn));

	auto pickupablebtn = std::make_unique<toggle_button>(location_, 160030, 2, 0, xorstr_("<color=#2faceb>Pickupable</color>"), []
		{
			if (!config::get<bool>(g_context.mirror_pickup))
			{
				config::get<bool>(g_context.mirror_pickup) = true;
				helpers::portable_mirror::get().update_pickupable(config::get<bool>(g_context.mirror_pickup));
			}
		}, []
		{
			if (config::get<bool>(g_context.mirror_pickup))
			{
				config::get<bool>(g_context.mirror_pickup) = false;
				helpers::portable_mirror::get().update_pickupable(config::get<bool>(g_context.mirror_pickup));
			}
		}, xorstr_("Allows you to pickup the portable mirror."));
	pickupablebtn->set_active(false);
	toggle_buttons_.push_back(std::move(pickupablebtn));

	auto resetposbtn = std::make_unique<single_button>(location_, 160040, 3, 0, xorstr_("<color=#2faceb>Reset Pos</color>"), [=]
		{
			helpers::portable_mirror::get().reset_position();
		}, xorstr_("Resets the mirror's position relative to your player."));
	resetposbtn->set_active(false);
	single_buttons_.push_back(std::move(resetposbtn));

	slider_buttons_.emplace_back(std::make_unique<slider_button>(location_, 160050, -3, utility::format(xorstr_("<color=#2faceb>Scale X ({:.1f})</color>"), config::get<float>(g_context.mirror_scale_x)), xorstr_("Adjust the mirror's scale on the X Axis (0-18).")));
	slider_buttons_[0]->set_action([=]
		{
			config::get<float>(g_context.mirror_scale_x) = slider_buttons_[0]->this_slider->get_value() * 18.f;
			slider_buttons_[0]->set_slider_text(utility::format(xorstr_("<color=#2faceb>Scale X ({:.1f})</color>"), config::get<float>(g_context.mirror_scale_x)));
			helpers::portable_mirror::get().update_scaling(config::get<float>(g_context.mirror_scale_x), config::get<float>(g_context.mirror_scale_y));
		});
	slider_buttons_[0]->set_active(false);

	slider_buttons_.emplace_back(std::make_unique<slider_button>(location_, 160060, -4, utility::format(xorstr_("<color=#2faceb>Scale Y ({:.1f})</color>"), config::get<float>(g_context.mirror_scale_y)), xorstr_("Adjust the mirror's scale on the Y Axis (0-18).")));
	slider_buttons_[1]->set_action([=]
		{
			config::get<float>(g_context.mirror_scale_y) = slider_buttons_[1]->this_slider->get_value() * 18.f;
			slider_buttons_[1]->set_slider_text(utility::format(xorstr_("<color=#2faceb>Scale Y ({:.1f})</color>"), config::get<float>(g_context.mirror_scale_y)));
			helpers::portable_mirror::get().update_scaling(config::get<float>(g_context.mirror_scale_x), config::get<float>(g_context.mirror_scale_y));
		});
	slider_buttons_[1]->set_active(false);
}

void portable_mirror_modules::show_all() const
{
	main_modules::get().show_back();

	slider_buttons_[0]->set_slider_text(utility::format(xorstr_("<color=#2faceb>Scale X ({:.1f})</color>"), config::get<float>(g_context.mirror_scale_x)));
	slider_buttons_[0]->this_slider->set_value(config::get<float>(g_context.mirror_scale_x) / 18.f);

	slider_buttons_[1]->set_slider_text(utility::format(xorstr_("<color=#2faceb>Scale Y ({:.1f})</color>"), config::get<float>(g_context.mirror_scale_y)));
	slider_buttons_[1]->this_slider->set_value(config::get<float>(g_context.mirror_scale_y) / 18.f);

	for (auto it = slider_buttons_.begin(); it != slider_buttons_.end(); ++it)
		(*it)->set_active(true);

	show();

	toggle_buttons_[0]->trigger(config::get<bool>(g_context.optimized_mirror));
	toggle_buttons_[1]->trigger(config::get<bool>(g_context.mirror_pickup));
}

void portable_mirror_modules::hide_all() const
{
	for (auto it = slider_buttons_.begin(); it != slider_buttons_.end(); ++it)
		(*it)->set_active(false);

	hide();
}
