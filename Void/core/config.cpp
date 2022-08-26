#include "config.hpp"

bool config::setup(const std::string_view sz_default_file_name)
{
	if (!is_directory(fs_path))
	{
		std::filesystem::remove(fs_path);
		if (!create_directories(fs_path))
			return false;
	}

	if (!exists(fs_path / sz_default_file_name))
		if (!save(sz_default_file_name))
			return false;

	if (!load(sz_default_file_name))
		return false;

	refresh();
	return true;
}

bool config::save(std::string_view sz_file_name)
{
	std::filesystem::path fs_file_path(sz_file_name);
	if (fs_file_path.extension() != xorstr_(".void"))
		fs_file_path.replace_extension(xorstr_(".void"));

	const std::string sz_file = std::filesystem::path(fs_path / fs_file_path).string();
	nlohmann::json config = {};

	try
	{
		for (auto& variable : vec_variables)
		{
			nlohmann::json entry = {};

			// save hashes to compare it later
			entry[xorstr_("name-id")] = variable.u_name_hash;
			entry[xorstr_("type-id")] = variable.u_type_hash;

			// get current variable
			switch (variable.u_type_hash)
			{
			case sdk::hash::fnv1a::hash_const("int"):
				{
					entry[xorstr_("value")] = variable.get<int>();
					break;
				}
			case sdk::hash::fnv1a::hash_const("float"):
				{
					entry[xorstr_("value")] = variable.get<float>();
					break;
				}
			case sdk::hash::fnv1a::hash_const("bool"):
				{
					entry[xorstr_("value")] = variable.get<bool>();
					break;
				}
			case sdk::hash::fnv1a::hash_const("std::string"):
				{
					entry[xorstr_("value")] = variable.get<std::string>();
					break;
				}
			case sdk::hash::fnv1a::hash_const("sdk::color"):
				{
					const auto& col_variable = variable.get<sdk::color>();

					// store RGBA as sub-node
					nlohmann::json sub = {};

					// fill node with all color values
					sub.emplace_back(col_variable.get<color_r>());
					sub.emplace_back(col_variable.get<color_g>());
					sub.emplace_back(col_variable.get<color_b>());
					sub.emplace_back(col_variable.get<color_a>());

					entry[xorstr_("value")] = sub.dump();
					break;
				}
			case sdk::hash::fnv1a::hash_const("std::vector<bool>"):
				{
					const auto& vec_bools = variable.get<std::vector<bool>>();

					// store vector values as sub-node
					nlohmann::json sub = {};

					// fill node with all vector values
					for (const auto&& b_value : vec_bools)
						sub.push_back(b_value);

					entry[xorstr_("value")] = sub.dump();
					break;
				}
			case sdk::hash::fnv1a::hash_const("std::vector<std::string>"):
				{
					const auto& vec_strings = variable.get<std::vector<std::string>>();

					nlohmann::json sub = {};

					for (const auto& b_value : vec_strings)
						sub.emplace_back(b_value);

					entry[xorstr_("value")] = sub.dump();
					break;
				}
			case sdk::hash::fnv1a::hash_const("std::vector<int>"):
				{
					const auto& vec_ints = variable.get<std::vector<int>>();

					// store vector values as sub-node
					nlohmann::json sub = {};

					// fill node with all vector values
					for (const auto& i_value : vec_ints)
						sub.emplace_back(i_value);

					entry[xorstr_("value")] = sub.dump();
					break;
				}
			case sdk::hash::fnv1a::hash_const("std::vector<float>"):
				{
					const auto& vec_floats = variable.get<std::vector<float>>();

					// store vector values as sub-node
					nlohmann::json sub = {};

					// fill node with all vector values
					for (const auto& fl_value : vec_floats)
						sub.emplace_back(fl_value);

					entry[xorstr_("value")] = sub.dump();
					break;
				}
			default:
				break;
			}

			// add current variable to config
			config.push_back(entry);
		}
	}
	catch (const nlohmann::detail::exception& ex)
	{
		logging::push(FOREGROUND_INTENSE_RED);
		logging::print(xorstr_("[error] json save failed: {}\n"), ex.what());
		logging::pop();
		return false;
	}

	// open output config file
	std::ofstream ofs_out_file(sz_file, std::ios::out | std::ios::trunc);

	if (!ofs_out_file.good())
		return false;

	try
	{
		// write stored variables
		ofs_out_file << config.dump(4);
		ofs_out_file.close();
	}
	catch (std::ofstream::failure& ex)
	{
		logging::push(FOREGROUND_INTENSE_RED);
		logging::print(xorstr_("[error] failed to save configuration: {}\n"), ex.what());
		logging::pop();
		return false;
	}

	return true;
}

bool config::load(std::string_view sz_file_name)
{
	// get utf-8 full path to config
	const std::string sz_file = std::filesystem::path(fs_path / sz_file_name).string();
	nlohmann::json config = {};

	// open input config file
	std::ifstream ifs_input_file(sz_file, std::ios::in);

	if (!ifs_input_file.good())
		return false;

	try
	{
		// parse saved variables
		config = nlohmann::json::parse(ifs_input_file, nullptr, false);

		// check is json parse failed
		if (config.is_discarded())
			return false;

		ifs_input_file.close();
	}
	catch (std::ifstream::failure& ex)
	{
		logging::push(FOREGROUND_INTENSE_RED);
		logging::print(xorstr_("[error] failed to load configuration: {}\n"), ex.what());
		logging::pop();
		return false;
	}

	try
	{
		for (const auto& variable : config)
		{
			const std::size_t n_index = get_variable_index(variable[xorstr_("name-id")].get<sdk::hash::fnv1a_t>());

			if (n_index == C_INVALID_VARIABLE)
				continue;

			auto& entry = vec_variables.at(n_index);

			switch (variable[xorstr_("type-id")].get<sdk::hash::fnv1a_t>())
			{
			case sdk::hash::fnv1a::hash_const("bool"):
				{
					entry.set<bool>(variable[xorstr_("value")].get<bool>());
					break;
				}
			case sdk::hash::fnv1a::hash_const("float"):
				{
					entry.set<float>(variable[xorstr_("value")].get<float>());
					break;
				}
			case sdk::hash::fnv1a::hash_const("int"):
				{
					entry.set<int>(variable[xorstr_("value")].get<int>());
					break;
				}
			case sdk::hash::fnv1a::hash_const("std::string"):
				{
					entry.set<std::string>(variable[xorstr_("value")].get<std::string>());
					break;
				}
			case sdk::hash::fnv1a::hash_const("sdk::color"):
				{
					const nlohmann::json vector = nlohmann::json::parse(variable[xorstr_("value")].get<std::string>());

					entry.set<sdk::color>(sdk::color(
						vector.at(0).get<std::uint8_t>(),
						vector.at(1).get<std::uint8_t>(),
						vector.at(2).get<std::uint8_t>(),
						vector.at(3).get<std::uint8_t>()
					));

					break;
				}
			case sdk::hash::fnv1a::hash_const("std::vector<bool>"):
				{
					const nlohmann::json vector = nlohmann::json::parse(variable[xorstr_("value")].get<std::string>());
					auto& vec_bools = entry.get<std::vector<bool>>();

					for (std::size_t i = 0U; i < vector.size(); i++)
						if (i < vec_bools.size())
							vec_bools.at(i) = vector.at(i).get<bool>();

					break;
				}
			case sdk::hash::fnv1a::hash_const("std::vector<int>"):
				{
					const nlohmann::json vector = nlohmann::json::parse(variable[xorstr_("value")].get<std::string>());
					auto& vec_ints = entry.get<std::vector<int>>();

					for (std::size_t i = 0U; i < vector.size(); i++)
						if (i < vec_ints.size())
							vec_ints.at(i) = vector.at(i).get<int>();

					break;
				}
			case sdk::hash::fnv1a::hash_const("std::vector<std::string>"):
				{
					const nlohmann::json vector = nlohmann::json::parse(variable[xorstr_("value")].get<std::string>());

					auto& vec_strings = entry.get<std::vector<std::string>>();

					vec_strings.clear();
					vec_strings.reserve(vector.size());

					for (std::size_t i = 0U; i < vector.size(); i++)
						vec_strings.emplace_back(vector.at(i).get<std::string>());

					break;
				}
			case sdk::hash::fnv1a::hash_const("std::vector<float>"):
				{
					const nlohmann::json vector = nlohmann::json::parse(variable[xorstr_("value")].get<std::string>());
					auto& vec_floats = entry.get<std::vector<float>>();

					for (std::size_t i = 0U; i < vector.size(); i++)
						if (i < vec_floats.size())
							vec_floats.at(i) = vector.at(i).get<float>();

					break;
				}
			default:
				break;
			}
		}
	}
	catch (const nlohmann::detail::exception& ex)
	{
		logging::push(FOREGROUND_INTENSE_RED);
		logging::print(xorstr_("[error] failed to load configuration: {}\n"), ex.what());
		logging::pop();
		return false;
	}

	return true;
}

bool config::update_instance_history(std::string_view world_name, std::string_view instance)
{
	const auto root = get_working_path();

	if (root.empty() || !exists(root))
		return false;

	const auto sz_file = std::filesystem::path(root / xorstr_("instance_history.void"));
	const auto sz_temp_file = std::filesystem::path(root / xorstr_("instance_history.void.tmp"));

	if (!exists(sz_file))
	{
		try
		{
			std::ofstream output(sz_file);
			output.close();
		}
		catch (const std::ofstream::failure& e)
		{
			logging::push(FOREGROUND_INTENSE_RED);
			logging::print(xorstr_("[error] failed to read instance history {}\n"), e.what());
			logging::pop();
			return false;
		}
	}

	std::ifstream infile;
	infile.open(sz_file.string());

	if (!infile.good())
		return false;

	try
	{
		std::ofstream ofs_out_file(sz_temp_file, std::ios::out | std::ios::trunc);
		if (!ofs_out_file.good())
			return false;

		std::string line;
		std::vector<std::string> lines;

		while (std::getline(infile, line))
			lines.push_back(line);

		lines.push_back(utility::format(xorstr_("{}:::{}"), world_name, instance));

		while (lines.size() >= 16)
			lines.erase(lines.begin());

		for (std::vector<std::string>::const_iterator i = lines.begin(); i != lines.end(); ++i)
			ofs_out_file << *i << xorstr_("\n");

		ofs_out_file.close();
		infile.close();

		remove(sz_file);
		rename(sz_temp_file, sz_file);
	}
	catch (const std::exception& e)
	{
		logging::push(FOREGROUND_INTENSE_RED);
		logging::print(xorstr_("[error] failed to save instance_history: {}\n"), e.what());
		logging::pop();
		return false;
	}

	return true;
}

bool config::read_instance_history(std::vector<std::string>& vec)
{
	const auto root = get_working_path();

	if (root.empty() || !exists(root))
		return false;

	const auto sz_file = std::filesystem::path(root / xorstr_("instance_history.void"));

	if (!exists(sz_file))
	{
		try
		{
			std::ofstream output(sz_file);
			output.close();
		}
		catch (const std::ofstream::failure& e)
		{
			logging::push(FOREGROUND_INTENSE_RED);
			logging::print(xorstr_("[error] failed to read instance history {}\n"), e.what());
			logging::pop();
			return false;
		}
	}

	try
	{
		std::ifstream infile(sz_file.string());
		if (!infile.good())
			return false;

		vec.clear();

		std::string str;
		while (std::getline(infile, str))
			if (str.size() > 0)
				vec.push_back(str);

		infile.close();

		std::ranges::reverse(vec);
	}
	catch (const std::ifstream::failure& ex)
	{
		logging::push(FOREGROUND_INTENSE_RED);
		logging::print(xorstr_("[error] failed to read instance history {}\n"), ex.what());
		logging::pop();
		return false;
	}
	return true;
}

bool config::toggle_autoload()
{
	const auto root = get_working_path();

	if (root.empty() || !exists(root))
		return false;

	const auto proxy = root / xorstr_("glu32.dll");

	if (!exists(proxy))
		return false;

	wchar_t buffer[MAX_PATH] = {0};
	GetModuleFileNameW(nullptr, buffer, MAX_PATH);
	const std::wstring buffer_string(buffer);

	const std::size_t pos = buffer_string.find_last_of(xorstr_(L"\\/"));
	const std::filesystem::path exepath = buffer_string.substr(0, pos);

	if (!exists(exepath))
		return false;

	const auto new_proxy = exepath / xorstr_("glu32.dll");

	try
	{
		if (exists(new_proxy))
		{
			const auto old = exepath / xorstr_("glu32.dll");
			const auto _new = exepath / xorstr_("VOID_NO_AUTOLOAD_glu32.dll");
			std::filesystem::rename(old, _new);

			logging::push(FOREGROUND_INTENSE_GREEN);
			logging::add_log(xorstr_("[log] Void will no longer autoload when you run VRChat\n"));
			logging::pop();

			return true;
		}

		if (exists(exepath / xorstr_("VOID_NO_AUTOLOAD_glu32.dll")))
		{
			const auto old = exepath / xorstr_("VOID_NO_AUTOLOAD_glu32.dll");
			const auto _new = exepath / xorstr_("glu32.dll");
			std::filesystem::rename(old, _new);

			logging::push(FOREGROUND_INTENSE_GREEN);
			logging::add_log(xorstr_("[log] Void will now autoload whenever you run VRChat\n"));
			logging::pop();

			return true;
		}
	}
	catch (const std::filesystem::filesystem_error& e)
	{
		logging::push(FOREGROUND_INTENSE_RED);
		logging::print(xorstr_("[error] failed to toggle autoloader {}\n"), e.what());
		logging::pop();

		return false;
	}

	try
	{
		std::ifstream src(proxy, std::ios::binary);
		std::ofstream dst(new_proxy, std::ios::binary);

		dst << src.rdbuf();
		src.close();
		dst.close();
	}
	catch (const std::ios_base::failure& ex)
	{
		logging::push(FOREGROUND_INTENSE_RED);
		logging::print(xorstr_("[error] failed to get loader {}\n"), ex.what());
		logging::pop();

		return false;
	}


	logging::push(FOREGROUND_INTENSE_GREEN);
	logging::add_log(xorstr_("[log] void will now autoload whenever you run vrchat\n"));
	logging::pop();

	return true;
}

void config::remove(const std::size_t n_index)
{
	const std::string& sz_file_name = vec_file_names.at(n_index);

	// unable delete default config
	if (sz_file_name == xorstr_("config.void"))
		return;

	// get utf-8 full path to config
	const std::string sz_file = std::filesystem::path(fs_path / sz_file_name).string();
	std::filesystem::remove(sz_file);
}

void config::refresh()
{
	vec_file_names.clear();

	for (const auto& it : std::filesystem::directory_iterator(fs_path))
		if (it.path().filename().extension() == xorstr_(".void"))
			vec_file_names.emplace_back(it.path().filename().string());
}

std::size_t config::get_variable_index(const sdk::hash::fnv1a_t u_name_hash)
{
	for (std::size_t i = 0U; i < vec_variables.size(); i++)
		if (vec_variables.at(i).u_name_hash == u_name_hash)
			return i;

	return C_INVALID_VARIABLE;
}

std::filesystem::path config::get_working_path()
{
	try
	{
		// VMProtectBeginMutation("Get Temporary");

		PWSTR path_tmp;
		if (FAILED(SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, nullptr, &path_tmp)))
		{
			CoTaskMemFree(path_tmp);

			logging::push(FOREGROUND_INTENSE_RED);
			logging::print(SECSTR("[critical] failed to get working directory\n"));
			logging::pop();

			return {};
		}

		std::filesystem::path fs_working_path = path_tmp;

		CoTaskMemFree(path_tmp);

		fs_working_path /= SECSTR("Void");

		// VMProtectEnd();

		return fs_working_path;
	}
	catch (std::filesystem::filesystem_error& e)
	{
		logging::push(FOREGROUND_INTENSE_RED);
		logging::print(SECSTR("[critical] failed to get working directory [{}]\n"), e.what());
		logging::pop();
		return {};
	}
}
