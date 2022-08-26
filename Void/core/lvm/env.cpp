#include "env.hpp"

#if LVM_TESTING == 1

void vlvm::env::print(const sol::variadic_args& va)
{
	std::stringstream ss;
	for (const auto v : va)
	{
		switch (v.get_type())
		{
		case sol::type::userdata:
			{
				if (const auto userdata = v.get<sol::userdata>(); userdata.is<sdk::vector>())
				{
					const auto& vec = userdata.as<sdk::vector>();
					ss << vec.x << xorstr_(", ") << vec.y << xorstr_(", ") << vec.z;
				}
				else if (userdata.is<sdk::quaternion>())
				{
					const auto& q = userdata.as<sdk::quaternion>();
					ss << q.x << xorstr_(", ") << q.y << xorstr_(", ") << q.z << xorstr_(", ") << q.w;
				}
				else if (userdata.is<sdk::color>())
				{
					const auto& q = userdata.as<sdk::color>();
					ss << static_cast<std::int32_t>(q[0]) << xorstr_(", ") << static_cast<std::int32_t>(q[1]) << xorstr_(", ") << static_cast<std::int32_t>(q[2]) << xorstr_(", ") << static_cast<std::int32_t>(q[3]);
				}

				break;
			}
		case sol::type::string:
			ss << v.get<std::string>();
			break;
		case sol::type::boolean:
			ss << v.get<bool>();
			break;
		case sol::type::number:
			ss << v.get<lua_Number>();
			break;
		case sol::type::function:
			ss << xorstr_("0x") << std::hex << reinterpret_cast<std::uintptr_t>(v.get<sol::function>().pointer()) << std::dec;
			break;
		case sol::type::thread:
			ss << xorstr_("0x") << std::hex << reinterpret_cast<std::uintptr_t>(v.get<sol::thread>().pointer()) << std::dec;
			break;
		case sol::type::none:
		case sol::type::nil:
		default:
			ss << xorstr_("null");
			break;
		}
	}

	logging::push(FOREGROUND_INTENSE_WHITE);
	logging::add_log(xorstr_("[log] {}\n"), ss.str());
	logging::pop();
	ingame_logging::get().log(xorstr_("[<color=#a75cf6>log</color>] {}"), ss.str());
}

void vlvm::env::warn(const sol::variadic_args& va)
{
	std::stringstream ss;
	for (const auto v : va)
	{
		switch (v.get_type())
		{
		case sol::type::userdata:
			{
				if (const auto userdata = v.get<sol::userdata>(); userdata.is<sdk::vector>())
				{
					const auto& vec = userdata.as<sdk::vector>();
					ss << vec.x << xorstr_(", ") << vec.y << xorstr_(", ") << vec.z;
				}
				else if (userdata.is<sdk::quaternion>())
				{
					const auto& q = userdata.as<sdk::quaternion>();
					ss << q.x << xorstr_(", ") << q.y << xorstr_(", ") << q.z << xorstr_(", ") << q.w;
				}
				else if (userdata.is<sdk::color>())
				{
					const auto& q = userdata.as<sdk::color>();
					ss << static_cast<std::int32_t>(q[0]) << xorstr_(", ") << static_cast<std::int32_t>(q[1]) << xorstr_(", ") << static_cast<std::int32_t>(q[2]) << xorstr_(", ") << static_cast<std::int32_t>(q[3]);
				}

				break;
			}

		case sol::type::string:
			ss << v.get<std::string>();
			break;
		case sol::type::boolean:
			ss << v.get<bool>();
			break;
		case sol::type::number:
			ss << v.get<lua_Number>();
			break;
		case sol::type::function:
			ss << xorstr_("0x") << std::hex << reinterpret_cast<std::uintptr_t>(v.get<sol::function>().pointer()) << std::dec;
			break;
		case sol::type::thread:
			ss << xorstr_("0x") << std::hex << reinterpret_cast<std::uintptr_t>(v.get<sol::thread>().pointer()) << std::dec;
			break;
		case sol::type::none:
		case sol::type::nil:
		default:
			ss << xorstr_("null");
			break;
		}
	}

	logging::push(FOREGROUND_INTENSE_YELLOW);
	logging::add_log(xorstr_("[warn] {}\n"), ss.str());
	logging::pop();
	ingame_logging::get().log(xorstr_("[<color=#a75cf6>warn</color>] {}"), ss.str());
}

void vlvm::env::error(const sol::variadic_args& va)
{
	std::stringstream ss;
	for (const auto v : va)
	{
		switch (v.get_type())
		{
		case sol::type::userdata:
			{
				if (const auto userdata = v.get<sol::userdata>(); userdata.is<sdk::vector>())
				{
					const auto& vec = userdata.as<sdk::vector>();
					ss << vec.x << xorstr_(", ") << vec.y << xorstr_(", ") << vec.z;
				}
				else if (userdata.is<sdk::quaternion>())
				{
					const auto& q = userdata.as<sdk::quaternion>();
					ss << q.x << xorstr_(", ") << q.y << xorstr_(", ") << q.z << xorstr_(", ") << q.w;
				}
				else if (userdata.is<sdk::color>())
				{
					const auto& q = userdata.as<sdk::color>();
					ss << static_cast<std::int32_t>(q[0]) << xorstr_(", ") << static_cast<std::int32_t>(q[1]) << xorstr_(", ") << static_cast<std::int32_t>(q[2]) << xorstr_(", ") << static_cast<std::int32_t>(q[3]);
				}

				break;
			}

		case sol::type::string:
			ss << v.get<std::string>();
			break;
		case sol::type::boolean:
			ss << v.get<bool>();
			break;
		case sol::type::number:
			ss << v.get<lua_Number>();
			break;
		case sol::type::function:
			ss << xorstr_("0x") << std::hex << reinterpret_cast<std::uintptr_t>(v.get<sol::function>().pointer()) << std::dec;
			break;
		case sol::type::thread:
			ss << xorstr_("0x") << std::hex << reinterpret_cast<std::uintptr_t>(v.get<sol::thread>().pointer()) << std::dec;
			break;
		case sol::type::none:
		case sol::type::nil:
		default:
			ss << xorstr_("null");
			break;
		}
	}

	logging::push(FOREGROUND_INTENSE_RED);
	logging::add_log(xorstr_("[critical] {}\n"), ss.str());
	logging::pop();
	ingame_logging::get().log(xorstr_("[<color=#a75cf6>critical</color>] {}"), ss.str());
}

bool vlvm::env::register_globals(sol::state& lua)
{
	try
	{
		lua.set_function(xorstr_("print"), &print);
		lua.set_function(xorstr_("warn"), &warn);
		lua.set_function(xorstr_("error"), &error);
	}
	catch (const sol::error& e)
	{
		logging::push(FOREGROUND_INTENSE_RED);
		logging::add_log(xorstr_("[critical] {}\n"), e.what());
		logging::pop();
		return false;
	}

	return true;
}

bool vlvm::env::register_vector3(sol::state& lua)
{
	try
	{
		sol::usertype<sdk::vector> vector3_type = lua.new_usertype<sdk::vector>(xorstr_("vector3"),
		                                                                        sol::constructors<sdk::vector(), sdk::vector(vec_t, vec_t, vec_t), sdk::vector(vec_t*), sdk::vector(const sdk::vector&)>(),
		                                                                        sol::meta_function::addition, sol::overload(static_cast<sdk::vector(sdk::vector::*)(const sdk::vector&) const>(&sdk::vector::operator+), static_cast<sdk::vector(sdk::vector::*)(vec_t) const>(&sdk::vector::operator+)),
		                                                                        sol::meta_function::subtraction, sol::overload(static_cast<sdk::vector(sdk::vector::*)(const sdk::vector&) const>(&sdk::vector::operator-), static_cast<sdk::vector(sdk::vector::*)(vec_t) const>(&sdk::vector::operator-)),
		                                                                        sol::meta_function::multiplication, sol::overload(static_cast<sdk::vector(sdk::vector::*)(const sdk::vector&) const>(&sdk::vector::operator*), static_cast<sdk::vector(sdk::vector::*)(vec_t) const>(&sdk::vector::operator*)),
		                                                                        sol::meta_function::division, sol::overload(static_cast<sdk::vector(sdk::vector::*)(const sdk::vector&) const>(&sdk::vector::operator/), static_cast<sdk::vector(sdk::vector::*)(vec_t) const>(&sdk::vector::operator/)),
		                                                                        sol::meta_function::index, sol::overload(static_cast<vec_t & (sdk::vector::*)(std::size_t i)>(&sdk::vector::operator[]), static_cast<const vec_t & (sdk::vector::*)(std::size_t i) const>(&sdk::vector::operator[])),
		                                                                        sol::meta_function::equal_to, &sdk::vector::operator==
		);

		// @note: static functions
		vector3_type.set_function(VMProtectDecryptStringA("up"), &sdk::vector::up);

		// @note: fields
		vector3_type[std::string_view(xorstr_("x"))] = sol::property(&sdk::vector::x, &sdk::vector::x);
		vector3_type[std::string_view(xorstr_("y"))] = sol::property(&sdk::vector::y, &sdk::vector::y);
		vector3_type[std::string_view(xorstr_("z"))] = sol::property(&sdk::vector::z, &sdk::vector::z);
		
		// @note: member functions
		vector3_type[std::string_view(xorstr_("is_valid"))] = &sdk::vector::is_valid;
		vector3_type[std::string_view(xorstr_("is_equal"))] = &sdk::vector::is_equal;
		vector3_type[std::string_view(xorstr_("is_zero"))] = &sdk::vector::is_zero;
		vector3_type[std::string_view(xorstr_("invalidate"))] = &sdk::vector::invalidate;
		vector3_type[std::string_view(xorstr_("length"))] = &sdk::vector::length;
		vector3_type[std::string_view(xorstr_("length_sqr"))] = &sdk::vector::length_sqr;
		vector3_type[std::string_view(xorstr_("length_2d"))] = &sdk::vector::length_2d;
		vector3_type[std::string_view(xorstr_("length_2d_sqr"))] = &sdk::vector::length_2d_sqr;
		vector3_type[std::string_view(xorstr_("dist_to"))] = &sdk::vector::dist_to;
		vector3_type[std::string_view(xorstr_("dist_to_sqr"))] = &sdk::vector::dist_to_sqr;
		vector3_type[std::string_view(xorstr_("normalized"))] = &sdk::vector::normalized;
		vector3_type[std::string_view(xorstr_("normalize_in_place"))] = &sdk::vector::normalize_in_place;
		vector3_type[std::string_view(xorstr_("dot_product"))] = &sdk::vector::dot_product;
		vector3_type[std::string_view(xorstr_("cross_product"))] = &sdk::vector::cross_product;
	}
	catch (const sol::error& e)
	{
		logging::push(FOREGROUND_INTENSE_RED);
		logging::add_log(xorstr_("[critical] {}\n"), e.what());
		logging::pop();
		return false;
	}

	return true;
}

bool vlvm::env::register_quaternion(sol::state& lua)
{
	try
	{
		auto quaternion_type = lua.new_usertype<sdk::quaternion>(xorstr_("quaternion"),
			sol::constructors<sdk::quaternion(), sdk::quaternion(float, float, float, float), sdk::quaternion(const sdk::quaternion&)>(),
			sol::meta_function::addition, &sdk::quaternion::operator+,
			sol::meta_function::multiplication, sol::overload(static_cast<sdk::quaternion(sdk::quaternion::*)(const sdk::quaternion&) const>(&sdk::quaternion::operator*), static_cast<sdk::quaternion(sdk::quaternion::*)(const float&) const>(&sdk::quaternion::operator*)),
			sol::meta_function::equal_to, &sdk::quaternion::operator==
			);

		// @note: static functions
		quaternion_type.set_function(VMProtectDecryptStringA("from_eulerangles"), &sdk::quaternion::from_eulerangles);
		quaternion_type.set_function(VMProtectDecryptStringA("inverse"), &sdk::quaternion::inverse);
		quaternion_type.set_function(VMProtectDecryptStringA("angle_axis"), &sdk::quaternion::angle_axis);
		quaternion_type.set_function(VMProtectDecryptStringA("angle"), &sdk::quaternion::angle);
		quaternion_type.set_function(VMProtectDecryptStringA("lerp"), &sdk::quaternion::lerp);
		quaternion_type.set_function(VMProtectDecryptStringA("slerp"), &sdk::quaternion::slerp);
		quaternion_type.set_function(VMProtectDecryptStringA("dot"), static_cast<float(*)(const sdk::quaternion&, const sdk::quaternion&)>(&sdk::quaternion::dot));
		quaternion_type.set_function(VMProtectDecryptStringA("look_rotation"), sol::overload(static_cast<sdk::quaternion(*)(const sdk::vector&)>(&sdk::quaternion::look_rotation), static_cast<sdk::quaternion(*)(const sdk::vector&, const sdk::vector&)>(&sdk::quaternion::look_rotation)));

		// @note: fields
		quaternion_type[std::string_view(xorstr_("x"))] = sol::property(&sdk::quaternion::x, &sdk::quaternion::x);
		quaternion_type[std::string_view(xorstr_("y"))] = sol::property(&sdk::quaternion::y, &sdk::quaternion::y);
		quaternion_type[std::string_view(xorstr_("z"))] = sol::property(&sdk::quaternion::z, &sdk::quaternion::z);
		quaternion_type[std::string_view(xorstr_("w"))] = sol::property(&sdk::quaternion::w, &sdk::quaternion::w);

		// @note: member functions
		quaternion_type[std::string_view(xorstr_("normalized"))] = &sdk::quaternion::normalized;
		quaternion_type[std::string_view(xorstr_("normalize"))] = &sdk::quaternion::normalize;
		quaternion_type[std::string_view(xorstr_("conjugate"))] = &sdk::quaternion::conjugate;
		quaternion_type[std::string_view(xorstr_("inverse"))] = &sdk::quaternion::conjugate;
		quaternion_type[std::string_view(xorstr_("set_eulerangles"))] = &sdk::quaternion::set_eulerangles;
		quaternion_type[std::string_view(xorstr_("dot"))] = static_cast<float(sdk::quaternion::*)(const sdk::quaternion&) const>(&sdk::quaternion::dot);
		quaternion_type[std::string_view(xorstr_("set_look_rotation"))] = sol::overload(static_cast<void(sdk::quaternion::*)(const sdk::vector&)>(&sdk::quaternion::set_look_rotation), static_cast<void(sdk::quaternion::*)(const sdk::vector&, const sdk::vector&)>(&sdk::quaternion::set_look_rotation));
		
	}
	catch (const sol::error& e)
	{
		logging::push(FOREGROUND_INTENSE_RED);
		logging::add_log(xorstr_("[critical] {}\n"), e.what());
		logging::pop();
		return false;
	}

	return true;
}

bool vlvm::env::register_color(sol::state& lua)
{
	try
	{
		sol::usertype<sdk::color> color_type = lua.new_usertype<sdk::color>(xorstr_("color"),
			sol::constructors<sdk::color(), sdk::color(int, int, int, int)>(),
			sol::meta_function::equal_to, &sdk::color::operator==
			);

		// @note: static functions
		color_type.set_function(VMProtectDecryptStringA("from_hsb"), &sdk::color::from_hsb);

		// @note: member functions
		color_type[std::string_view(xorstr_("brightness"))] = &sdk::color::brightness;
		color_type[std::string_view(xorstr_("hue"))] = &sdk::color::hue;
		color_type[std::string_view(xorstr_("saturation"))] = &sdk::color::saturation;
		color_type[std::string_view(xorstr_("hex"))] = &sdk::color::get_hex;

	}
	catch (const sol::error& e)
	{
		logging::push(FOREGROUND_INTENSE_RED);
		logging::add_log(xorstr_("[critical] {}\n"), e.what());
		logging::pop();
		return false;
	}

	return true;
}

#endif
