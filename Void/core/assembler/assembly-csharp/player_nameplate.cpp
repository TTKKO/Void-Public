#include "player_nameplate.hpp"

void assembler::player_nameplate::show()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] show passed nullptr\n"));
        logging::pop();
        return;
    }
    this->get_game_object()->set_active(true);
}

void assembler::player_nameplate::set_bool(const bool val)
{
	*reinterpret_cast<bool*>(reinterpret_cast<std::uint8_t*>(this) + 0x238) = val;
}

assembler::tmpro::tmp_text* assembler::player_nameplate::get_name_text()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_name_text passed nullptr\n"));
        logging::pop();
        return nullptr;
    }

    return *reinterpret_cast<tmpro::tmp_text**>(reinterpret_cast<std::uint8_t*>(this) + 0x20);
}
