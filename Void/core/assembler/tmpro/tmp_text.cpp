#include "tmp_text.hpp"

assembler::il2cpp::il2cpp_class* assembler::tmpro::tmp_text::get_global_class()
{
    if (!global_class_)
        global_class_ = class_from_system_type(il2cpp::get_type(xorstr_("TMPro.TMP_Text, Unity.TextMeshPro")));
    return global_class_;
}


void assembler::tmpro::tmp_text::set_is_overlay(const bool value)
{
    if (this == nullptr) 
        return;

    using func_t = void(*)(tmp_text*, bool);
    static const auto func = memory::get_method<func_t>(SETISOVERLAY);
    func(this, value);
}

void assembler::tmpro::tmp_text::set_text(const std::string_view text)
{
    if (this == nullptr) 
        return;

    il2cpp::call_vfunc<void>(this->klass, 66, this, il2cpp::string_new(text));
}

void assembler::tmpro::tmp_text::set_color(const sdk::color& c)
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] set_color passed nullptr\n"));
        logging::pop();
        return;
    }

    il2cpp::call_vfunc<void>(this->klass, 23, this, c.base_alpha());
}

void assembler::tmpro::tmp_text::set_fontsize(const float value)
{
	using func_t = void(*)(tmp_text*, float);
    static const auto func = memory::get_method<func_t>(TMPSETFONTSIZE);
    func(this, value);
}

void assembler::tmpro::tmp_text::set_word_wrapping(const bool value)
{
    *reinterpret_cast<bool*>(reinterpret_cast<std::uint8_t*>(this) + 0x2C8) = value;
}
