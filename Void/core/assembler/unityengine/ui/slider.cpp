#include "slider.hpp"

assembler::unity_engine::ui::slider_clicked_event* assembler::unity_engine::ui::slider::get_on_slide()
{
    return *reinterpret_cast<slider_clicked_event**>(reinterpret_cast<std::uint8_t*>(this) + 0x120);
}

void assembler::unity_engine::ui::slider::set_on_slide(slider_clicked_event* value)
{
    using func_t = void(*)(slider*, slider_clicked_event*);
    static const auto func = memory::get_method<func_t>(SETONSLIDE);
    func(this, value);
}

float assembler::unity_engine::ui::slider::get_value()
{
    return *reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this) + 0x118);
}

void assembler::unity_engine::ui::slider::set_value(const float value)
{
    *reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this) + 0x118) = value;
}
