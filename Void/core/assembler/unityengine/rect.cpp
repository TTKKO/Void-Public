#include "rect.hpp"

float assembler::unity_engine::rect::get_width()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_width passed nullptr.\n"));
        logging::pop();
        return NULL;
    }
    return *reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this) + 0x8);
}

float assembler::unity_engine::rect::get_height()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_height passed nullptr.\n"));
        logging::pop();
        return NULL;
    }
    return *reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this) + 0xC);
}
