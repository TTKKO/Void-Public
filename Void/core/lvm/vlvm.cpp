#include "vlvm.hpp"

#if LVM_TESTING == 1

bool vlvm::initialize()
{
	env::lua.open_libraries(
		sol::lib::base, 
		sol::lib::coroutine, 
		sol::lib::math, 
		sol::lib::package, 
		sol::lib::string, 
		sol::lib::bit32, 
		sol::lib::table,
		sol::lib::io,
		sol::lib::jit
	);

	if (!env::register_globals(env::lua))
		return false;
	if (!env::register_vector3(env::lua))
		return false;
	if (!env::register_quaternion(env::lua))
		return false;
	if (!env::register_color(env::lua))
		return false;
	if (!assembler::vrc::core::api_user::initialize_lvm(env::lua))
		return false;
	if (!assembler::vrc::core::api_world::initialize_lvm(env::lua))
		return false;
	if (!assembler::vrc::core::api_world_instance::initialize_lvm(env::lua))
		return false;

	return true;
}

void vlvm::do_script(const std::string_view sz)
{
	try
	{
		switch (const auto res = env::lua.safe_script(sz); res.status())
		{
		case sol::call_status::runtime:
			{
				const sol::error e = res;
				logging::push(FOREGROUND_INTENSE_RED);
				logging::print(xorstr_("[lua runtime error] {}\n"), e.what());
				logging::pop();
				break;
			}
		case sol::call_status::memory:
			{
				const sol::error e = res;
				logging::push(FOREGROUND_INTENSE_RED);
				logging::print(xorstr_("[lua memory error] {}\n"), e.what());
				logging::pop();
				break;
			}
		case sol::call_status::handler:
			{
				const sol::error e = res;
				logging::push(FOREGROUND_INTENSE_RED);
				logging::print(xorstr_("[lua error] {}\n"), e.what());
				logging::pop();
				break;
			}
		case sol::call_status::gc:
			{
				const sol::error e = res;
				logging::push(FOREGROUND_INTENSE_RED);
				logging::print(xorstr_("[lua gc error] {}\n"), e.what());
				logging::pop();
				break;
			}
		case sol::call_status::syntax:
			{
				const sol::error e = res;
				logging::push(FOREGROUND_INTENSE_RED);
				logging::print(xorstr_("[lua syntax error] {}\n"), e.what());
				logging::pop();
				break;
			}
		case sol::call_status::file:
			{
				const sol::error e = res;
				logging::push(FOREGROUND_INTENSE_RED);
				logging::print(xorstr_("[lua file error] {}\n"), e.what());
				logging::pop();
				break;
			}

		case sol::call_status::ok:
		case sol::call_status::yielded:
		default:
			break;
		}
	}
	catch (const sol::error& e)
	{
		logging::push(FOREGROUND_INTENSE_RED);
		logging::add_log(xorstr_("[critical] {}\n"), e.what());
		logging::pop();
	}
}

#endif