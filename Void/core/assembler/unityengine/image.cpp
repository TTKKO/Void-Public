#include "image.hpp"
#include "../../../offsets.hpp"

assembler::unity_engine::ui::sprite* assembler::unity_engine::ui::image::get_sprite()
{
    return *reinterpret_cast<sprite**>(reinterpret_cast<std::uint8_t*>(this) + 0xC8);
}

void assembler::unity_engine::ui::image::set_sprite(sprite* value)
{
    using func_t = sprite* (*)(image*, sprite*);
    static const auto func = memory::get_method<func_t>(SETSPRITEIMAGE);
    func(this, value);
}

assembler::unity_engine::ui::material* assembler::unity_engine::ui::image::get_material()
{
    using func_t = material* (*)(image*);
    static const auto func = memory::get_method<func_t>(GETMATERIALIMAGE);
    return func(this);
}

void assembler::unity_engine::ui::image::set_material(material* value)
{
    using func_t = material* (*)(image*, material*);
    static const auto func = memory::get_method<func_t>(SETMATERIALIMAGE);
    func(this, value);
}

sdk::color assembler::unity_engine::ui::image::get_color()
{
    return sdk::color(*reinterpret_cast<std::array<float, 4U>*>(reinterpret_cast<std::uint8_t*>(this) + 0x20));
}
