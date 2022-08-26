#include "lovense_modules.hpp"

void lovense_modules::setup()
{
	//connection_listener::get().handler.socket()->on(xorstr_("user_connected"), [&](const sio::event& ev)
	//{
	//	const auto& response_uid = ev.get_message()->get_string();
	//	if (response_uid != assembler::vrc::core::api_user::get_current()->get_id())
	//		return;

	//	logging::push(FOREGROUND_INTENSE_GREEN);
	//	logging::add_log(xorstr_("[lovense api] successfully connected to device!\n"));
	//	logging::pop();
	//	ingame_logging::get().log(xorstr_("[<color=#a75cf6>lovense api</color>] successfully connected to device!"));

	//	try
	//	{
	//		if (config::get<bool>(g_context.xs_overlay_toggle))
	//		{
	//			if (!xs_overlay::get().send(std::string_view(xorstr_("[lovense api] successfully connected to device!")), xorstr_(""), xorstr_("default"), 1.5f))
	//			{
	//				logging::push(FOREGROUND_INTENSE_RED);
	//				logging::print(xorstr_("[critical] failed to talk to xs-overlay api [{}]\n"), xs_overlay::get().fetch_last_error());
	//				logging::pop();
	//			}
	//		}
	//		else
	//			assembler::vrc_ui_manager::instance()->hud_msg(xorstr_("[lovense api] successfully connected to device!"));
	//	}
	//	catch (const std::exception& e)
	//	{
	//		logging::push(FOREGROUND_INTENSE_RED);
	//		logging::print(xorstr_("[critical] {}\n"), e.what());
	//		logging::pop();
	//	}

	//	connection_established_ = true;
	//});

	const auto text = assembler::ui_manager_impl::instance()->get_quickmenu()->get_transform()->find(xorstr_("Container/Window/QMParent/Menu_QM_Emojis/Header_Emojis/LeftItemContainer/Text_Title"));
	auto temp = static_cast<assembler::unity_engine::game_object*>(assembler::unity_engine::object::instantiate(text->get_game_object(), assembler::ui_manager_impl::instance()->get_quickmenu()->get_transform()->find(location_), true));

	text_.push_back(reinterpret_cast<assembler::tmpro::tmp_text*>(temp->get_transform()->get_component(xorstr_("TMPro.TextMeshProUGUI"))));
	text_[0]->set_text(xorstr_("<color=#fc658d>Lovense API</color>"));
	text_[0]->set_fontsize(38.f);
	reinterpret_cast<assembler::unity_engine::component*>(text_[0])->get_transform()->set_local_position(sdk::vector(-125.f, -53.f, 0.f));
	reinterpret_cast<assembler::unity_engine::component*>(text_[0])->get_game_object()->set_active(false);
	reinterpret_cast<assembler::unity_engine::component*>(text_[0])->set_name(xorstr_("text_lovense_api"));

	temp = static_cast<assembler::unity_engine::game_object*>(assembler::unity_engine::object::instantiate(text->get_game_object(), assembler::ui_manager_impl::instance()->get_quickmenu()->get_transform()->find(location_), true));
	text_.push_back(reinterpret_cast<assembler::tmpro::tmp_text*>(temp->get_transform()->get_component(xorstr_("TMPro.TextMeshProUGUI"))));
	text_[1]->set_text(xorstr_("<color=#fc658d>Presets</color>"));
	text_[1]->set_fontsize(30.f);
	reinterpret_cast<assembler::unity_engine::component*>(text_[1])->get_transform()->set_local_position(sdk::vector(-62.f, -175.f, 0.f));
	reinterpret_cast<assembler::unity_engine::component*>(text_[1])->get_game_object()->set_active(false);
	reinterpret_cast<assembler::unity_engine::component*>(text_[1])->set_name(xorstr_("text_lovense_presets"));

	auto generatebtn = std::make_unique<half_single_button>(location_, 140010, 0, 0, xorstr_("<color=#fc658d>Generate\r\nQR Code</color>"), [=]
	{
		// VMProtectBeginUltra("Lovense Generate QR");

		logging::push(FOREGROUND_INTENSE_WHITE);
		logging::add_log(xorstr_("[lovense api] requesting qr code from lovense\n"));
		logging::pop();
		ingame_logging::get().log(xorstr_("[<color=#a75cf6>lovense api</color>] requesting qr code from lovense"));

		const auto apiuser = assembler::vrc::core::api_user::get_current();
		const nlohmann::json request_data = {{xorstr_("uid"), apiuser->get_id()}, {xorstr_("uname"), apiuser->display_name()}};

		//connection_listener::get().handler.socket()->emit(xorstr_("request_qrcode"), request_data.dump(), [&](const sio::message::list& msg)
		//{
		//	try
		//	{
		//		auto& map = msg[0]->get_map();

		//		if (!map[xorstr_("result")]->get_bool())
		//			throw std::runtime_error(utility::format(xorstr_("lovense request failed with code {:d}"), map[xorstr_("code")]->get_int()));

		//		utility::set_clipboard(map[xorstr_("message")]->get_string());

		//		logging::push(FOREGROUND_INTENSE_GREEN);
		//		logging::add_log(xorstr_("[lovense api] success! copied qr code link to your clipboard, send this to your partner.\n"));
		//		logging::pop();
		//		ingame_logging::get().log(xorstr_("[<color=#a75cf6>lovense api</color>] copied qr code, send the link to your partner."));
		//	}
		//	catch (const std::exception& e)
		//	{
		//		logging::push(FOREGROUND_INTENSE_RED);
		//		logging::print(xorstr_("[lovense api error] {}\n"), e.what());
		//		logging::pop();
		//		connection_established_ = false;
		//	}
		//});

		// VMProtectEnd();
	}, xorstr_("Generates a QR code that allows you to connect to your partner. After clicking this, a link will be copied to your clipboard containing an image of the QR code, send this to your partner."));
	generatebtn->set_active(false);
	hs_buttons_.push_back(std::move(generatebtn));

	auto stopallmovementbtn = std::make_unique<half_single_button>(location_, 140020, 3, 0, xorstr_("<color=#fc658d>Stop All\r\nMovement</color>"), [=]
	{
		if (!connection_established_)
			return;

		// VMProtectBeginUltra("Lovense Stop");

		const auto apiuser = assembler::vrc::core::api_user::get_current();
		const nlohmann::json request_data = {
			{xorstr_("uid"), apiuser->get_id()},
			{xorstr_("command"), xorstr_("Function")},
			{xorstr_("action"), xorstr_("Stop")},
			{xorstr_("timeSec"), 0},
			{xorstr_("apiVer"), 1}
		};

		//connection_listener::get().handler.socket()->emit(xorstr_("lovense_command"), request_data.dump(), [&](const sio::message::list& msg)
		//{
		//	try
		//	{
		//		auto& map = msg[0]->get_map();

		//		if (!map[xorstr_("result")]->get_bool())
		//		{
		//			const auto code = map[xorstr_("code")]->get_int();
		//			if (code == 507)
		//				throw std::runtime_error(utility::format(xorstr_("looks like you're not connected to any device! [code {:d}]"), code));
		//			throw std::runtime_error(utility::format(xorstr_("lovense request failed with code {:d}"), code));
		//		}

		//		logging::push(FOREGROUND_INTENSE_GREEN);
		//		logging::add_log(xorstr_("[lovense api] stopped all device activity\n"));
		//		logging::pop();
		//		ingame_logging::get().log(xorstr_("[<color=#a75cf6>lovense api</color>] stopped all device activity"));
		//	}
		//	catch (const std::exception& e)
		//	{
		//		logging::push(FOREGROUND_INTENSE_RED);
		//		logging::print(xorstr_("[lovense api error] {}\n"), e.what());
		//		logging::pop();
		//		connection_established_ = false;
		//	}
		//});

		// VMProtectEnd();
	}, xorstr_("Stops all movement that the device is making."));
	stopallmovementbtn->set_active(false);
	hs_buttons_.push_back(std::move(stopallmovementbtn));

	auto pulsebtn = std::make_unique<half_single_button>(location_, 140030, 0, -2, xorstr_("<color=#fc658d>Pulse</color>"), [=]
	{
		if (!connection_established_)
			return;

		// VMProtectBeginUltra("Lovense Pulse");

		const auto apiuser = assembler::vrc::core::api_user::get_current();
		const nlohmann::json request_data = {
			{xorstr_("uid"), apiuser->get_id()},
			{xorstr_("command"), xorstr_("Preset")},
			{xorstr_("name"), xorstr_("Pulse")},
			{xorstr_("timeSec"), 0},
			{xorstr_("apiVer"), 1}
		};

		//connection_listener::get().handler.socket()->emit(xorstr_("lovense_command"), request_data.dump(), [&](const sio::message::list& msg)
		//{
		//	try
		//	{
		//		auto& map = msg[0]->get_map();

		//		if (!map[xorstr_("result")]->get_bool())
		//		{
		//			const auto code = map[xorstr_("code")]->get_int();
		//			if (code == 507)
		//				throw std::runtime_error(utility::format(xorstr_("looks like you're not connected to any device! [code {:d}]"), code));
		//			throw std::runtime_error(utility::format(xorstr_("lovense request failed with code {:d}"), code));
		//		}

		//		logging::push(FOREGROUND_INTENSE_GREEN);
		//		logging::add_log(xorstr_("[lovense api] set device to use \"pulse\" preset\n"));
		//		logging::pop();
		//		ingame_logging::get().log(xorstr_("[<color=#a75cf6>lovense api</color>] set device to use \"pulse\" preset"));
		//	}
		//	catch (const std::exception& e)
		//	{
		//		logging::push(FOREGROUND_INTENSE_RED);
		//		logging::print(xorstr_("[lovense api error] {}\n"), e.what());
		//		logging::pop();
		//		connection_established_ = false;
		//	}
		//});

		// VMProtectEnd();
	}, xorstr_("Runs the pulse preset on the connected device."));
	pulsebtn->set_active(false);
	hs_buttons_.push_back(std::move(pulsebtn));

	auto wavebtn = std::make_unique<half_single_button>(location_, 140040, 1, -2, xorstr_("<color=#fc658d>Wave</color>"), [=]
	{
		if (!connection_established_)
			return;

		// VMProtectBeginUltra("Lovense Wave");

		const auto apiuser = assembler::vrc::core::api_user::get_current();
		const nlohmann::json request_data = {
			{xorstr_("uid"), apiuser->get_id()},
			{xorstr_("command"), xorstr_("Preset")},
			{xorstr_("name"), xorstr_("Wave")},
			{xorstr_("timeSec"), 0},
			{xorstr_("apiVer"), 1}
		};

		//connection_listener::get().handler.socket()->emit(xorstr_("lovense_command"), request_data.dump(), [&](const sio::message::list& msg)
		//{
		//	try
		//	{
		//		auto& map = msg[0]->get_map();

		//		if (!map[xorstr_("result")]->get_bool())
		//		{
		//			const auto code = map[xorstr_("code")]->get_int();
		//			if (code == 507)
		//				throw std::runtime_error(utility::format(xorstr_("looks like you're not connected to any device! [code {:d}]"), code));
		//			throw std::runtime_error(utility::format(xorstr_("lovense request failed with code {:d}"), code));
		//		}

		//		logging::push(FOREGROUND_INTENSE_GREEN);
		//		logging::add_log(xorstr_("[lovense api] set device to use \"wave\" preset\n"));
		//		logging::pop();
		//		ingame_logging::get().log(xorstr_("[<color=#a75cf6>lovense api</color>] set device to use \"wave\" preset"));
		//	}
		//	catch (const std::exception& e)
		//	{
		//		logging::push(FOREGROUND_INTENSE_RED);
		//		logging::print(xorstr_("[lovense api error] {}\n"), e.what());
		//		logging::pop();
		//		connection_established_ = false;
		//	}
		//});

		// VMProtectEnd();
	}, xorstr_("Runs the wave preset on the connected device."));
	wavebtn->set_active(false);
	hs_buttons_.push_back(std::move(wavebtn));

	auto fireworksbtn = std::make_unique<half_single_button>(location_, 140050, 2, -2, xorstr_("<color=#fc658d>Fireworks</color>"), [=]
	{
		if (!connection_established_)
			return;

		// VMProtectBeginUltra("Lovense Fireworks");

		const auto apiuser = assembler::vrc::core::api_user::get_current();
		const nlohmann::json request_data = {
			{xorstr_("uid"), apiuser->get_id()},
			{xorstr_("command"), xorstr_("Preset")},
			{xorstr_("name"), xorstr_("Fireworks")},
			{xorstr_("timeSec"), 0},
			{xorstr_("apiVer"), 1}
		};

		//connection_listener::get().handler.socket()->emit(xorstr_("lovense_command"), request_data.dump(), [&](const sio::message::list& msg)
		//{
		//	try
		//	{
		//		auto& map = msg[0]->get_map();

		//		if (!map[xorstr_("result")]->get_bool())
		//		{
		//			const auto code = map[xorstr_("code")]->get_int();
		//			if (code == 507)
		//				throw std::runtime_error(utility::format(xorstr_("looks like you're not connected to any device! [code {:d}]"), code));
		//			throw std::runtime_error(utility::format(xorstr_("lovense request failed with code {:d}"), code));
		//		}

		//		logging::push(FOREGROUND_INTENSE_GREEN);
		//		logging::add_log(xorstr_("[lovense api] set device to use \"fireworks\" preset\n"));
		//		logging::pop();
		//		ingame_logging::get().log(xorstr_("[<color=#a75cf6>lovense api</color>] set device to use \"fireworks\" preset"));
		//	}
		//	catch (const std::exception& e)
		//	{
		//		logging::push(FOREGROUND_INTENSE_RED);
		//		logging::print(xorstr_("[lovense api error] {}\n"), e.what());
		//		logging::pop();
		//		connection_established_ = false;
		//	}
		//});

		// VMProtectEnd();
	}, xorstr_("Runs the fireworks preset on the connected device."));
	fireworksbtn->set_active(false);
	hs_buttons_.push_back(std::move(fireworksbtn));

	auto earthquakebtn = std::make_unique<half_single_button>(location_, 140060, 3, -2, xorstr_("<color=#fc658d>Earthquake</color>"), [=]
	{
		if (!connection_established_)
			return;

		// VMProtectBeginUltra("Lovense Earthquake");

		const auto apiuser = assembler::vrc::core::api_user::get_current();
		const nlohmann::json request_data = {
			{xorstr_("uid"), apiuser->get_id()},
			{xorstr_("command"), xorstr_("Preset")},
			{xorstr_("name"), xorstr_("Earthquake")},
			{xorstr_("timeSec"), 0},
			{xorstr_("apiVer"), 1}
		};

		//connection_listener::get().handler.socket()->emit(xorstr_("lovense_command"), request_data.dump(), [&](const sio::message::list& msg)
		//{
		//	try
		//	{
		//		auto& map = msg[0]->get_map();

		//		if (!map[xorstr_("result")]->get_bool())
		//		{
		//			const auto code = map[xorstr_("code")]->get_int();
		//			if (code == 507)
		//				throw std::runtime_error(utility::format(xorstr_("looks like you're not connected to any device! [code {:d}]"), code));
		//			throw std::runtime_error(utility::format(xorstr_("lovense request failed with code {:d}"), code));
		//		}

		//		logging::push(FOREGROUND_INTENSE_GREEN);
		//		logging::add_log(xorstr_("[lovense api] set device to use \"earthquake\" preset\n"));
		//		logging::pop();
		//		ingame_logging::get().log(xorstr_("[<color=#a75cf6>lovense api</color>] set device to use \"earthquake\" preset"));
		//	}
		//	catch (const std::exception& e)
		//	{
		//		logging::push(FOREGROUND_INTENSE_RED);
		//		logging::print(xorstr_("[lovense api error] {}\n"), e.what());
		//		logging::pop();
		//		connection_established_ = false;
		//	}
		//});

		// VMProtectEnd();
	}, xorstr_("Runs the earthquake preset on the connected device."));
	earthquakebtn->set_active(false);
	hs_buttons_.push_back(std::move(earthquakebtn));

	temp = static_cast<assembler::unity_engine::game_object*>(assembler::unity_engine::object::instantiate(text->get_game_object(), assembler::ui_manager_impl::instance()->get_quickmenu()->get_transform()->find(location_), true));
	text_.push_back(std::move(reinterpret_cast<assembler::tmpro::tmp_text*>(temp->get_transform()->get_component(xorstr_("TMPro.TextMeshProUGUI")))));
	text_[2]->set_text(xorstr_("<color=#fc658d>Manual Remote</color>"));
	text_[2]->set_fontsize(30.f);
	reinterpret_cast<assembler::unity_engine::component*>(text_[2])->get_transform()->set_local_position(sdk::vector(-119.f, -370.f, 0.f));
	reinterpret_cast<assembler::unity_engine::component*>(text_[2])->get_game_object()->set_active(false);
	reinterpret_cast<assembler::unity_engine::component*>(text_[2])->set_name(xorstr_("text_lovense_manual_remote"));

	slider_buttons_.emplace_back(std::make_unique<slider_button>(location_, 140070, -4, xorstr_("<color=#fc658d>Vibration</color>"), xorstr_("Increases or decreases the vibration speed.")));
	slider_buttons_[0]->set_action([=]
	{
		if (!connection_established_)
			return;

		const auto last_speed = vibration_speed_;
		vibration_speed_ = slider_buttons_[0]->this_slider->get_value();

		if (vibration_speed_ >= 0.2f && vibration_speed_ < 0.4f)
			vibration_speed_ = 0.2f;
		else if (vibration_speed_ >= 0.4f && vibration_speed_ < 0.6f)
			vibration_speed_ = 0.4f;
		else if (vibration_speed_ >= 0.6f && vibration_speed_ < 0.8f)
			vibration_speed_ = 0.6f;
		else if (vibration_speed_ >= 0.8f && vibration_speed_ < 0.98f)
			vibration_speed_ = 0.8f;
		else if (vibration_speed_ >= 0.98f)
			vibration_speed_ = 1.f;
		else
			vibration_speed_ = 0.f;

		// VMProtectBeginUltra("Lovense MVibration");

		if (vibration_speed_ == last_speed)
			return;

		slider_buttons_[0]->set_slider_text(utility::format(xorstr_("<color=#fc658d>Vibration ({:.2f}%)"), vibration_speed_));

		const auto apiuser = assembler::vrc::core::api_user::get_current();
		const nlohmann::json request_data = {
			{xorstr_("uid"), apiuser->get_id()},
			{xorstr_("command"), xorstr_("Function")},
			{xorstr_("action"), utility::format(xorstr_("Vibrate:{:d}"), static_cast<std::int32_t>(vibration_speed_ * 20.f))},
			{xorstr_("timeSec"), 0},
			{xorstr_("apiVer"), 1}
		};

		//connection_listener::get().handler.socket()->emit(xorstr_("lovense_command"), request_data.dump(), [&](const sio::message::list& msg)
		//{
		//	try
		//	{
		//		auto& map = msg[0]->get_map();

		//		if (!map[xorstr_("result")]->get_bool())
		//		{
		//			const auto code = map[xorstr_("code")]->get_int();
		//			if (code == 507)
		//				throw std::runtime_error(utility::format(xorstr_("looks like you're not connected to any device! [code {:d}]"), code));
		//			throw std::runtime_error(utility::format(xorstr_("lovense request failed with code {:d}"), code));
		//		}

		//		logging::push(FOREGROUND_INTENSE_GREEN);
		//		logging::add_log(xorstr_("[lovense api] changed device vibration to {:.2f}%\n"), vibration_speed_);
		//		logging::pop();
		//		ingame_logging::get().log(xorstr_("[<color=#a75cf6>lovense api</color>] changed device vibration to {:.2f}%"), vibration_speed_);
		//	}
		//	catch (const std::exception& e)
		//	{
		//		logging::push(FOREGROUND_INTENSE_RED);
		//		logging::print(xorstr_("[lovense api error] {}\n"), e.what());
		//		logging::pop();
		//		connection_established_ = false;
		//	}
		//});

		// VMProtectEnd();
	});
	slider_buttons_[0]->set_active(false);

	slider_buttons_.emplace_back(std::make_unique<slider_button>(location_, 140080, -5, xorstr_("<color=#fc658d>Rotation</color>"), xorstr_("Increases or decreases the rotation speed.")));
	slider_buttons_[1]->set_action([=]
	{
		if (!connection_established_)
			return;

		const auto last_speed = rotation_speed_;
		rotation_speed_ = slider_buttons_[1]->this_slider->get_value();

		if (rotation_speed_ >= 0.2f && rotation_speed_ < 0.4f)
			rotation_speed_ = 0.2f;
		else if (rotation_speed_ >= 0.4f && rotation_speed_ < 0.6f)
			rotation_speed_ = 0.4f;
		else if (rotation_speed_ >= 0.6f && rotation_speed_ < 0.8f)
			rotation_speed_ = 0.6f;
		else if (rotation_speed_ >= 0.8f && rotation_speed_ < 0.98f)
			rotation_speed_ = 0.8f;
		else if (rotation_speed_ >= 0.98f)
			rotation_speed_ = 1.f;
		else
			rotation_speed_ = 0.f;

		// VMProtectBeginUltra("Lovense MRotation");

		if (rotation_speed_ == last_speed)
			return;
		slider_buttons_[1]->set_slider_text(utility::format(xorstr_("<color=#fc658d>Rotation ({:.2f}%)"), rotation_speed_));

		const auto apiuser = assembler::vrc::core::api_user::get_current();
		const nlohmann::json request_data = {
			{xorstr_("uid"), apiuser->get_id()},
			{xorstr_("command"), xorstr_("Function")},
			{xorstr_("action"), utility::format(xorstr_("Rotate:{:d}"), static_cast<std::int32_t>(rotation_speed_ * 20.f))},
			{xorstr_("timeSec"), 0},
			{xorstr_("apiVer"), 1}
		};

		//connection_listener::get().handler.socket()->emit(xorstr_("lovense_command"), request_data.dump(), [&](const sio::message::list& msg)
		//{
		//	try
		//	{
		//		auto& map = msg[0]->get_map();

		//		if (!map[xorstr_("result")]->get_bool())
		//		{
		//			const auto code = map[xorstr_("code")]->get_int();
		//			if (code == 507)
		//				throw std::runtime_error(utility::format(xorstr_("looks like you're not connected to any device! [code {:d}]"), code));
		//			throw std::runtime_error(utility::format(xorstr_("lovense request failed with code {:d}"), code));
		//		}

		//		logging::push(FOREGROUND_INTENSE_GREEN);
		//		logging::add_log(xorstr_("[lovense api] changed device rotation to {:.2f}%\n"), rotation_speed_);
		//		logging::pop();
		//		ingame_logging::get().log(xorstr_("[<color=#a75cf6>lovense api</color>] changed device rotation to {:.2f}%"), rotation_speed_);
		//	}
		//	catch (const std::exception& e)
		//	{
		//		logging::push(FOREGROUND_INTENSE_RED);
		//		logging::print(xorstr_("[lovense api error] {}\n"), e.what());
		//		logging::pop();
		//		connection_established_ = false;
		//	}
		//});

		// VMProtectEnd();
	});
	slider_buttons_[1]->set_active(false);

	auto binds_togglebtn = std::make_unique<toggle_button>(location_, 140090, 0, -3, xorstr_("<color=#fc658d>Controller\r\nBinds</color>"), []
	{
		if (!config::get<bool>(g_context.lovense_binds))
		{
			config::get<bool>(g_context.lovense_binds) = true;
		}
	}, []
	{
		if (config::get<bool>(g_context.lovense_binds))
		{
			config::get<bool>(g_context.lovense_binds) = false;
		}
	}, xorstr_("On your *RIGHT* controller, with this option enabled, hold trigger and move your thumbstick up and down to control the toy's vibration speed."));
	binds_togglebtn->set_active(false);
	toggle_buttons_.push_back(std::move(binds_togglebtn));
}

void lovense_modules::increase_vibration()
{
	if (!connection_established_ || vibration_speed_ > 0.8f)
		return;

	vibration_speed_ += 0.2f;

	slider_buttons_[0]->this_slider->set_value(vibration_speed_);
	slider_buttons_[0]->set_slider_text(utility::format(xorstr_("<color=#fc658d>Vibration ({:.2f}%)"), vibration_speed_));

	// VMProtectBeginUltra("Lovense IVibration");

	const auto apiuser = assembler::vrc::core::api_user::get_current();
	const nlohmann::json request_data = {
		{xorstr_("uid"), apiuser->get_id()},
		{xorstr_("command"), xorstr_("Function")},
		{xorstr_("action"), utility::format(xorstr_("Vibrate:{:d}"), static_cast<std::int32_t>(vibration_speed_ * 20.f))},
		{xorstr_("timeSec"), 0},
		{xorstr_("apiVer"), 1}
	};

	//connection_listener::get().handler.socket()->emit(xorstr_("lovense_command"), request_data.dump(), [&](const sio::message::list& msg)
	//{
	//	try
	//	{
	//		auto& map = msg[0]->get_map();

	//		if (!map[xorstr_("result")]->get_bool())
	//		{
	//			const auto code = map[xorstr_("code")]->get_int();
	//			if (code == 507)
	//				throw std::runtime_error(utility::format(xorstr_("looks like you're not connected to any device! [code {:d}]"), code));
	//			throw std::runtime_error(utility::format(xorstr_("lovense request failed with code {:d}"), code));
	//		}

	//		logging::push(FOREGROUND_INTENSE_GREEN);
	//		logging::add_log(xorstr_("[lovense api] increased device vibration to {:.2f}%\n"), vibration_speed_);
	//		logging::pop();
	//		ingame_logging::get().log(xorstr_("[<color=#a75cf6>lovense api</color>] increased device vibration to {:.2f}%"), vibration_speed_);
	//	}
	//	catch (const std::exception& e)
	//	{
	//		logging::push(FOREGROUND_INTENSE_RED);
	//		logging::print(xorstr_("[lovense api error] {}\n"), e.what());
	//		logging::pop();
	//		connection_established_ = false;
	//	}
	//});

	// VMProtectEnd();
}

void lovense_modules::decrease_vibration()
{
	if (!connection_established_ || vibration_speed_ < 0.2f)
		return;

	vibration_speed_ -= 0.2f;

	slider_buttons_[0]->this_slider->set_value(vibration_speed_);
	slider_buttons_[0]->set_slider_text(utility::format(xorstr_("<color=#fc658d>Vibration ({:.2f}%)"), vibration_speed_));

	// VMProtectBeginUltra("Lovense DVibration");

	const auto apiuser = assembler::vrc::core::api_user::get_current();
	const nlohmann::json request_data = {
		{xorstr_("uid"), apiuser->get_id()},
		{xorstr_("command"), xorstr_("Function")},
		{xorstr_("action"), utility::format(xorstr_("Vibrate:{:d}"), static_cast<std::int32_t>(vibration_speed_ * 20.f))},
		{xorstr_("timeSec"), 0},
		{xorstr_("apiVer"), 1}
	};

	//connection_listener::get().handler.socket()->emit(xorstr_("lovense_command"), request_data.dump(), [&](const sio::message::list& msg)
	//{
	//	try
	//	{
	//		auto& map = msg[0]->get_map();

	//		if (!map[xorstr_("result")]->get_bool())
	//		{
	//			const auto code = map[xorstr_("code")]->get_int();
	//			if (code == 507)
	//				throw std::runtime_error(utility::format(xorstr_("looks like you're not connected to any device! [code {:d}]"), code));
	//			throw std::runtime_error(utility::format(xorstr_("lovense request failed with code {:d}"), code));
	//		}

	//		logging::push(FOREGROUND_INTENSE_GREEN);
	//		logging::add_log(xorstr_("[lovense api] decreased device vibration to {:.2f}%\n"), vibration_speed_);
	//		logging::pop();
	//		ingame_logging::get().log(xorstr_("[<color=#a75cf6>lovense api</color>] decreased device vibration to {:.2f}%"), vibration_speed_);
	//	}
	//	catch (const std::exception& e)
	//	{
	//		logging::push(FOREGROUND_INTENSE_RED);
	//		logging::print(xorstr_("[lovense api error] {}\n"), e.what());
	//		logging::pop();
	//		connection_established_ = false;
	//	}
	//});

	// VMProtectEnd();
}

void lovense_modules::show_all() const
{
	main_modules::get().show_back();

	slider_buttons_[0]->this_slider->set_value(vibration_speed_);
	slider_buttons_[0]->set_slider_text(utility::format(xorstr_("<color=#fc658d>Vibration ({:.2f}%)"), vibration_speed_));

	slider_buttons_[1]->this_slider->set_value(rotation_speed_);
	slider_buttons_[1]->set_slider_text(utility::format(xorstr_("<color=#fc658d>Rotation ({:.2f}%)"), rotation_speed_));

	toggle_buttons_[0]->trigger(config::get<bool>(g_context.lovense_binds));

	for (auto it = hs_buttons_.begin(); it != hs_buttons_.end(); ++it)
		(*it)->set_active(true);
	for (auto it = slider_buttons_.begin(); it != slider_buttons_.end(); ++it)
		(*it)->set_active(true);
	for (auto it = text_.begin(); it != text_.end(); ++it)
		reinterpret_cast<assembler::unity_engine::component*>(*it)->get_game_object()->set_active(true);

	show();
}

void lovense_modules::hide_all() const
{
	for (auto it = hs_buttons_.begin(); it != hs_buttons_.end(); ++it)
		(*it)->set_active(false);
	for (auto it = slider_buttons_.begin(); it != slider_buttons_.end(); ++it)
		(*it)->set_active(false);
	for (auto it = text_.begin(); it != text_.end(); ++it)
		reinterpret_cast<assembler::unity_engine::component*>(*it)->get_game_object()->set_active(false);

	hide();
}
