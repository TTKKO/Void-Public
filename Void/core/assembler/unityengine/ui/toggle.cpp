#include "toggle.hpp"
#include "toggle.hpp"

void assembler::unity_engine::ui::toggle::set(const bool a, const bool b)
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] set passed nullptr\n"));
        logging::pop();
        return;
    }

    using func_t = void (*)(toggle*, bool, bool);
    static const auto func = memory::get_method<func_t>(TOGGLESET);
    func(this, a, b);
}

bool assembler::unity_engine::ui::toggle::get_state()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_state passed nullptr\n"));
        logging::pop();
        return NULL;
    }
    return *reinterpret_cast<bool*>(reinterpret_cast<std::uint8_t*>(this) + 0x118);
}

void assembler::unity_engine::ui::toggle::set_toggle(toggle_clicked_event* data)
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] set_toggle passed nullptr\n"));
        logging::pop();
        return;
    }
    const auto state = reinterpret_cast<toggle_clicked_event**>(reinterpret_cast<std::uint8_t*>(this) + 0x110);
    *state = data;
}

assembler::unity_engine::ui::toggle_clicked_event* assembler::unity_engine::ui::toggle::get_toggle()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_toggle passed nullptr\n"));
        logging::pop();
        return nullptr;
    }
    return *reinterpret_cast<toggle_clicked_event**>(reinterpret_cast<std::uint8_t*>(this) + 0x110);
}
