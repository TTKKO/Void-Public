#include "highlightsfx.hpp"
#include "../../../offsets.hpp"

assembler::highlights_fx* assembler::highlights_fx::instance()
{
    using func_t = highlights_fx*(*)();
    static const auto func = memory::get_method<func_t>(HLFXGETINSTANCE);
    return func();
}

void assembler::highlights_fx::enable_outline(unity_engine::renderer* renderer, const bool value)
{
    if (!this || !renderer)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] enable_outline passed nullptr\n"));
        logging::pop();
        return;
    }
    using func_t = highlights_fx * (*)(highlights_fx*, unity_engine::renderer*, bool);
    static const auto func = memory::get_method<func_t>(HLFXTOGGLERENDERER);
    func(this, renderer, value);
}

assembler::unity_engine::material* assembler::highlights_fx::get_material()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_material passed nullptr\n"));
        logging::pop();
        return nullptr;
    }
    return *reinterpret_cast<unity_engine::material**>(reinterpret_cast<std::uint8_t*>(this) + 0x38);
}
