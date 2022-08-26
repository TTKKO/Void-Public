#include "photon_player.hpp"

std::int32_t assembler::photon_player::get_id()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_id passed nullptr\n"));
        logging::pop();
        return -1;
    }
    return *reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this) + 0x18);
}

assembler::vrc_player* assembler::photon_player::get_vrc_player()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_vrc_player passed nullptr\n"));
        logging::pop();
        return nullptr;
    }

    return *reinterpret_cast<vrc_player**>(reinterpret_cast<std::uint8_t*>(this) + 0x20);
}

assembler::system_replication::collections::hashtable* assembler::photon_player::get_hashtable()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_hashtable passed nullptr\n"));
        logging::pop();
        return nullptr;
    }
    return *reinterpret_cast<system_replication::collections::hashtable**>(reinterpret_cast<std::uint8_t*>(this) + 0x48);
}
