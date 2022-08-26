#include "apiavatar.hpp"

assembler::vrc::core::api_avatar* assembler::vrc::core::api_avatar::ctor()
{
    const auto ret = reinterpret_cast<api_avatar*>(new_object(get_global_type(), true));
    using func_t = void (*)(api_avatar*);
    static const auto func = memory::get_method<func_t>(APIAVATARCTOR);
    func(ret);
    return ret;
}

assembler::il2cpp::il2cpp_type* assembler::vrc::core::api_avatar::get_global_type()
{
    if (!type_)
        type_ = il2cpp::get_type(xorstr_("VRC.Core.ApiAvatar, VRCCore-Standalone"));

    return type_;
}

std::string assembler::vrc::core::api_avatar::get_asset_url()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_asset_url passed nullptr.\n"));
        logging::pop();
        return xorstr_("INVALID_STRING");
    }
    return s_chars(this->fields.asset_url);
}

std::string assembler::vrc::core::api_avatar::get_name()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_name passed nullptr.\n"));
        logging::pop();
        return xorstr_("INVALID_STRING");
    }
    return s_chars(this->fields.name);
}

std::string assembler::vrc::core::api_avatar::get_author_name()
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

std::string assembler::vrc::core::api_avatar::get_id()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_id passed nullptr.\n"));
        logging::pop();
        return xorstr_("INVALID_STRING");
    }
    return s_chars(*reinterpret_cast<il2cpp::il2cpp_string**>(reinterpret_cast<std::uint8_t*>(this) + 0x10));
}

std::string assembler::vrc::core::api_avatar::get_release_status()
{
    if (this == nullptr)
        return xorstr_("INVALID_STRING");

    return s_chars(this->fields.release_status);
}

void assembler::vrc::core::api_avatar::set_id(const std::string_view id)
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] set_id passed nullptr.\n"));
        logging::pop();
        return;
    }
    this->fields.id = il2cpp::string_new(id);
}
