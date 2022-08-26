#include "graphic.hpp"

void assembler::unity_engine::ui::graphic::set_color(const sdk::color& value)
{
    using func_t = void(*)(graphic*, std::array<float, 4U>);
    static const auto func = memory::get_method<func_t>(SETCOLOR);
    func(this, value.base_alpha());
}
