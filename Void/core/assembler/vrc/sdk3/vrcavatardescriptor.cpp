#include "vrcavatardescriptor.hpp"

assembler::vrc::sdk3::expressionsmenu* assembler::vrc::sdk3::vrcavatardescriptor::get_expressionsmenu()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_expressionsmenu passed nullptr.\n"));
        logging::pop();
        return nullptr;
    }
    if (this == nullptr) return nullptr;
    return *reinterpret_cast<expressionsmenu**>(reinterpret_cast<std::uint8_t*>(this) + 0xB0);
}
