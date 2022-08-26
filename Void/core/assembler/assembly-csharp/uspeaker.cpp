#include "uspeaker.hpp"

//internal static Dictionary<whatthefuck.whatthefuck, Nullable<int>> whatthefuck; // 0x40
//private const whatthefuck.whatthefuck whatthefuck = 2;
//private static Nullable<int> whatthefuck; // 0x48
//private int whatthefuck; // 0x1B4
//private float whatthefuck; // 0x1B8
//private float whatthefuck; // 0x1BC
//private float whatthefuck; // 0x1C0
//private float whatthefuck; // 0x1C4
//private double whatthefuck; // 0x1C8
//private const float whatthefuck = 0.25;
//private const float whatthefuck = 0.75;

void assembler::uspeaker::set_bitrate(const bit_rate bitrate)
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] set_bitrate passed nullptr\n"));
        logging::pop();
        return;
    }

    this->fields.bitrate = bitrate;
}

void assembler::uspeaker::set_remotegain(const float db)
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] set_remotegain passed nullptr\n"));
        logging::pop();
        return;
    }

    this->klass->static_fields->remotegain = db;
}
