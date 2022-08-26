#include "expressionsmenu.hpp"

assembler::il2cpp::il2cpp_array* assembler::vrc::sdk3::expressionsmenu::get_controls()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_controls passed nullptr.\n"));
        logging::pop();
        return nullptr;
    }
    return *reinterpret_cast<il2cpp::il2cpp_array**>(reinterpret_cast<std::uint8_t*>(this) + 0x18);
}

std::string assembler::vrc::sdk3::expressionsmenu::control::get_name()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_name passed nullptr.\n"));
        logging::pop();
        return xorstr_("INVALID_STRING");
    }
    return s_chars(*reinterpret_cast<il2cpp::il2cpp_string**>(reinterpret_cast<std::uint8_t*>(this) + 0x10));
}

void assembler::vrc::sdk3::expressionsmenu::control::set_name(const std::string_view name)
{
    if (this == nullptr) return;
    *reinterpret_cast<il2cpp::il2cpp_string**>(reinterpret_cast<std::uint8_t*>(this) + 0x10) = il2cpp::string_new(name);
}
