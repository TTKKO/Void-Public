#include "selectable.hpp"

void assembler::unity_engine::ui::selectable::set_interactable(const bool value)
{
    using func_t = void(*)(selectable*, bool);
    static const auto func = memory::get_method<func_t>(SETINTERACTABLE);
    func(this, value);
}
