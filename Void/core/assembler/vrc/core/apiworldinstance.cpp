#include "apiworldinstance.hpp"

#if LVM_TESTING == 1
bool assembler::vrc::core::api_world_instance::initialize_lvm(sol::state& lua)
{
	try
	{
		auto core_table = lua[std::string_view(xorstr_("vrc"))].get_or_create<sol::table>()[std::string_view(xorstr_("core"))].get_or_create<sol::table>();

		sol::usertype<api_world_instance> apiuser_type = core_table.new_usertype<api_world_instance>(xorstr_("api_world_instance"), sol::no_constructor);

		// @note: member functions
		apiuser_type[std::string_view(xorstr_("get_instance_id"))] = &api_world_instance::get_instance_id;
		apiuser_type[std::string_view(xorstr_("get_access_type"))] = &api_world_instance::get_access_type;
		apiuser_type[std::string_view(xorstr_("get_world_id"))] = &api_world_instance::get_world_id;
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

std::string assembler::vrc::core::api_world_instance::get_access_type() const
{
	if (this == nullptr)
	{
		logging::push(FOREGROUND_INTENSE_BLUE);
		logging::print(xorstr_("[assembler] get_access_type passed nullptr.\n"));
		logging::pop();
		return xorstr_("");
	}

	//using func_t = uint32_t * (*)(api_world_instance*);
	//const auto func = memory::get_method<func_t>(GETACCESSTYPE);
	//auto accesstype = func(this);

	switch (this->fields.type)
	{
	case 0:
		return xorstr_("Public");
	case 1:
		return xorstr_("Friends+");
	case 2:
		return xorstr_("Friends");
	case 3:
		return xorstr_("Invite Only");
	case 4:
		return xorstr_("Invite+");
	case 5:
		return xorstr_("Private");
	default:
		return xorstr_("None");
	}
}

std::string assembler::vrc::core::api_world_instance::get_instance_id() const
{
	if (this == nullptr)
	{
		logging::push(FOREGROUND_INTENSE_BLUE);
		logging::print(xorstr_("[assembler] get_instance_id passed nullptr.\n"));
		logging::pop();
		return xorstr_("INVALID_STRING");
	}
	return s_chars(this->fields.instance_id);
}

std::string assembler::vrc::core::api_world_instance::get_world_id() const
{
	if (this == nullptr)
	{
		logging::push(FOREGROUND_INTENSE_BLUE);
		logging::print(xorstr_("[assembler] get_world_id passed nullptr.\n"));
		logging::pop();
		return xorstr_("INVALID_STRING");
	}
	return s_chars(this->fields.world_id);
}
