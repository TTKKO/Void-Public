#include "vrcuipopupmanager.hpp"

assembler::vrc_ui_popup_manager* assembler::vrc_ui_popup_manager::instance()
{
    using func_t = vrc_ui_popup_manager * (*)();
    static const auto func = memory::get_method<func_t>(VRCUIPOPUPMANAGER);
    return func();
}

void assembler::vrc_ui_popup_manager::show_alert(const std::string_view str1, const std::string_view str2, const float delay)
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] show_alert passed nullptr\n"));
        logging::pop();
        return;
    }
    using func_t = void(*)(vrc_ui_popup_manager*, il2cpp::il2cpp_string*, il2cpp::il2cpp_string*, float);
    static const auto func = memory::get_method<func_t>(SHOWALERT);
    func(this, il2cpp::string_new(str1), il2cpp::string_new(str2), delay);
}

void assembler::vrc_ui_popup_manager::show_popup(const std::string_view title, const std::string_view init_text, const std::int32_t input_type, const bool is_numeric, const std::string_view confirm_text, system_replication::action* on_complete, system_replication::action* on_cancel, const std::string_view placeholder_text, const bool close_on_complete, system_replication::action* on_popup_shown, const bool unknown, const std::int32_t char_limit)
{
	using func_t = void(*)(vrc_ui_popup_manager*, il2cpp::il2cpp_string*, il2cpp::il2cpp_string*, std::int32_t, bool, il2cpp::il2cpp_string*, system_replication::action*, system_replication::action*, il2cpp::il2cpp_string*, bool, system_replication::action*, bool, std::int32_t);
    static const auto func = memory::get_method<func_t>(0xC65910);
    func(this, il2cpp::string_new(title), il2cpp::string_new(init_text), input_type, is_numeric, il2cpp::string_new(confirm_text), on_complete, on_cancel, il2cpp::string_new(placeholder_text), close_on_complete, on_popup_shown, unknown, char_limit);
}
