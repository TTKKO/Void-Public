#include "button.hpp"
#include <filesystem>
#include <iostream>

using namespace assembler::unity_engine::ui;

button_clicked_event* button::get_on_click()
{
    using func_t = button_clicked_event*(*)(button*);
    static const auto func = memory::get_method<func_t>(GETONCLICK);
    return func(this);
}

void button::set_on_click(button_clicked_event* value)
{
    using func_t = void (*)(button*, button_clicked_event*);
    static const auto func = memory::get_method<func_t>(SETONCLICK);
    func(this, value);
}

void button::set_normal_color(const sdk::color& c)
{
    *reinterpret_cast<std::array<float, 4U>*>(reinterpret_cast<std::uint8_t*>(this) + 0x4C) = c.base_alpha();
}
