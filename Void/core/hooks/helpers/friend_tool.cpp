#include "friend_tool.hpp"

bool helpers::friend_tool::is_ready() const
{
	return !is_working_ || task_.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
}

bool helpers::friend_tool::save_temporary() const
{
	const auto root = config::get_working_path();

	if (!exists(root))
		return false;

	const auto exports_dir = root / xorstr_("exports");

	if (!exists(exports_dir))
		if (!create_directory(exports_dir))
			return false;

	const auto exports_file = exports_dir / xorstr_("exports.void.tmp");

	std::wofstream ofs_out_file(exports_file, std::ios::out | std::ios::trunc);
	//test
	if (!ofs_out_file.good())
		return false;

	try
	{
		for (const auto& e : friends_)
			ofs_out_file << e << xorstr_(L"\n");

		ofs_out_file.close();
	}
	catch (std::wofstream::failure& e)
	{
		logging::push(FOREGROUND_INTENSE_RED);
		logging::print(xorstr_("[error] failed to export friends: {}\n"), e.what());
		logging::pop();

		return false;
	}

	return true;
}

bool helpers::friend_tool::export_friends(const std::vector<assembler::il2cpp::il2cpp_string*>& v_friends)
{
	const auto root = config::get_working_path();

	if (!exists(root))
		return false;

	const auto exports_dir = root / xorstr_("exports");

	if (!exists(exports_dir))
		if (!create_directory(exports_dir))
			return false;

	const auto exports_file = exports_dir / xorstr_("exports.void");

	std::wofstream ofs_out_file(exports_file, std::ios::out | std::ios::trunc);

	if (!ofs_out_file.good())
		return false;

	try
	{
		for (const auto& e : v_friends)
		{
			const auto content = ws_chars(e);

			if (content == xorstr_(L"INVALID_STRING"))
				continue;

			ofs_out_file << content << xorstr_(L"\n");
		}

		ofs_out_file.close();
	}
	catch (std::wofstream::failure& e)
	{
		logging::push(FOREGROUND_INTENSE_RED);
		logging::print(xorstr_("[error] failed to export friends: {}\n"), e.what());
		logging::pop();

		return false;
	}

	return true;
}

bool helpers::friend_tool::import_friends()
{
	const auto root = config::get_working_path();

	if (!exists(root))
		return false;

	const auto exports_dir = root / xorstr_("exports");

	if (!exists(exports_dir))
		return false;

	auto exports_file = exports_dir / xorstr_("exports.void");

	if (!exists(exports_file))
	{
		exports_file = exports_dir / xorstr_("exports.void.tmp");
		if (!exists(exports_file))
			return false;
	}

	std::wifstream ifs_input_file(exports_file, std::ios::in);

	if (!ifs_input_file.good())
		return false;

	friends_.clear();

	try
	{
		for (std::wstring line; std::getline(ifs_input_file, line);)
			friends_.emplace_back(line);

		ifs_input_file.close();
	}
	catch (const std::wifstream::failure& ex)
	{
		logging::push(FOREGROUND_INTENSE_RED);
		logging::print(xorstr_("[error] failed to import friends: {}\n"), ex.what());
		logging::pop();

		return false;
	}

	if (friends_.empty())
		return false;

	return true;
}

void helpers::friend_tool::load_friends()
{
	// VMProtectBeginUltra("FriendTool Load");

	const auto il2cpp_thread = thread_attach(assembler::il2cpp::current_domain());

	is_working_ = true;

	if (friends_.empty())
		return;

	const auto root = config::get_working_path();

	if (!exists(root))
		return;

	const auto exports_dir = root / xorstr_("exports");

	try
	{
		if (!exists(exports_dir))
			return;

		if (const auto exports_file = exports_dir / xorstr_("exports.void"); exists(exports_file))
		{
			if (exists(exports_dir / xorstr_("exports.void.tmp")))
				std::filesystem::remove(exports_dir / xorstr_("exports.void.tmp"));

			copy(exports_file, exports_dir / xorstr_("exports.void.tmp"));

			if (exists(exports_dir / xorstr_("exports.void.old")))
				remove(exports_dir / xorstr_("exports.void.old"));

			rename(exports_file, exports_dir / xorstr_("exports.void.old"));
		}
	}
	catch (const std::filesystem::filesystem_error& e)
	{
		logging::push(FOREGROUND_INTENSE_RED);
		logging::print(xorstr_("[critical] failed to write files: {}\n"), e.what());
		logging::pop();
		return;
	}

	auto it = friends_.begin();
	while (it != friends_.end())
	{
		const auto user = assembler::vrc::core::api_user::ctor();

		if ((*it).empty())
		{
			it = friends_.erase(it);
			continue;
		}

		user->fields.id = assembler::il2cpp::string_new(*it);

		if (!assembler::room_manager::get_class()->static_fields->world)
		{
			std::this_thread::sleep_for(std::chrono::seconds(30));
			continue;
		}

		if (assembler::vrc::core::api_user::is_friends_with(user->fields.id))
		{
			it = friends_.erase(it);

			if (!save_temporary())
			{
				logging::push(FOREGROUND_INTENSE_RED);
				logging::print(xorstr_("[critical] failed to save temporary friends file! continuing...\n"));
				logging::pop();
			}

			continue;
		}

		assembler::vrc::core::api_user::send_friend_request(user);
		it = friends_.erase(it);

		if (!save_temporary())
		{
			logging::push(FOREGROUND_INTENSE_RED);
			logging::print(xorstr_("[critical] failed to save temporary friends file! continuing...\n"));
			logging::pop();
		}

		std::this_thread::sleep_for(std::chrono::minutes(1));
	}

	logging::push(FOREGROUND_INTENSE_GREEN);
	logging::add_log(xorstr_("[notice] friend importing has completed.\n"));
	logging::pop();

	if (exists(exports_dir / xorstr_("exports.void.tmp")))
		remove(exports_dir / xorstr_("exports.void.tmp"));

	thread_detach(il2cpp_thread);

	is_working_ = false;
	// VMProtectEnd();
}

bool helpers::friend_tool::start_load_task()
{
	// VMProtectBeginUltra("FriendTool Start");

	if (!is_ready())
		return false;

	task_ = std::async(std::launch::async, &friend_tool::load_friends, this);

	// VMProtectEnd();
	return true;
}
