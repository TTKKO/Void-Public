#include "apiworld.hpp"

#if LVM_TESTING == 1
bool assembler::vrc::core::api_world::initialize_lvm(sol::state& lua)
{
    try
    {
        auto core_table = lua[std::string_view(xorstr_("vrc"))].get_or_create<sol::table>()[std::string_view(xorstr_("core"))].get_or_create<sol::table>();

        sol::usertype<api_world> apiuser_type = core_table.new_usertype<api_world>(xorstr_("api_world"), sol::factories(&api_world::ctor));

        // @note: member functions
        apiuser_type[std::string_view(xorstr_("get_id"))] = &api_world::get_id;
        apiuser_type[std::string_view(xorstr_("get_vrca"))] = &api_world::asset_url;
        apiuser_type[std::string_view(xorstr_("get_author_name"))] = &api_world::get_author_name;
        apiuser_type[std::string_view(xorstr_("get_name"))] = &api_world::get_name;
        apiuser_type[std::string_view(xorstr_("get_capacity"))] = &api_world::get_capacity;
    }
    catch (const sol::error& e)
    {
        logging::push(FOREGROUND_INTENSE_RED);
        logging::print(xorstr_("[critical] {}\n"), e.what());
        logging::pop();
        return false;
    }

    return true;
}
#endif

std::string assembler::vrc::core::api_world::get_name() const
{
    if (this == nullptr) return xorstr_("loading");
    return s_chars(this->fields.name);
}

std::string assembler::vrc::core::api_world::asset_url() const
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] asset_url passed nullptr.\n"));
        logging::pop();
        return xorstr_("INVALID_STRING");
    }
    return s_chars(this->fields.asset_url);
}

std::string assembler::vrc::core::api_world::get_id() const
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_id passed nullptr.\n"));
        logging::pop();
        return xorstr_("INVALID_STRING");
    }

    return s_chars(this->fields.id);
}

std::string assembler::vrc::core::api_world::get_author_name() const
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_author_name passed nullptr.\n"));
        logging::pop();
        return xorstr_("INVALID_STRING");
    }
    return s_chars(this->fields.author_name);
}

int assembler::vrc::core::api_world::get_capacity() const
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_capacity passed nullptr.\n"));
        logging::pop();
        return NULL;
    }
    return this->fields.capacity;
}

assembler::vrc::core::api_world* assembler::vrc::core::api_world::ctor()
{
    const auto ret = reinterpret_cast<api_world*>(new_object(get_global_type(), true));

    using func_t = void (*)(api_world*);
    static const auto func = memory::get_method<func_t>(APIWORLDCTOR);
    func(ret);
    return ret;
}

assembler::il2cpp::il2cpp_type* assembler::vrc::core::api_world::get_global_type()
{
    if (!type_)
        type_ = il2cpp::get_type(xorstr_("VRC.Core.ApiWorld, VRCCore-Standalone"));

    return type_;
}
