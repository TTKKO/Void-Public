#include "text.hpp"
#include "../../il2cpp/il2cpp.hpp"


void assembler::unity_engine::ui::text::set_fontsize(const int size)
{
    using func_t = void(*)(text*, int);
    static const auto func = memory::get_method<func_t>(SET_FONTSIZE);
    func(this, size);
}

void assembler::unity_engine::ui::text::set_text(const std::string_view value)
{
    //memory::call_vfunc<void>(text_interface, 8, this, value);
    using func_t = void (*)(text*, il2cpp::il2cpp_string*);
    static const auto func = memory::get_method<func_t>(SET_TEXT);
    func(this, il2cpp::string_new(value));
}

std::string assembler::unity_engine::ui::text::get_text()
{
    return s_chars(*reinterpret_cast<il2cpp::il2cpp_string**>(reinterpret_cast<std::uint8_t*>(this) + 0xD0));
}

void assembler::unity_engine::ui::text::set_support_rich_text(const bool& value)
{
    using func_t = il2cpp::il2cpp_string* (*)(text*, const bool&);
    static const auto func = memory::get_method<func_t>(RICHTEXT);
    func(this, value);
}
