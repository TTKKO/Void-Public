#include "vrc_eventreplicator.hpp"

void assembler::vrc_eventreplicator::process_events(const bool toggle)
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] process_events passed nullptr\n"));
        logging::pop();
        return;
    }
    *reinterpret_cast<bool*>(reinterpret_cast<std::uint8_t*>(this) + 0x40) = toggle;
}
