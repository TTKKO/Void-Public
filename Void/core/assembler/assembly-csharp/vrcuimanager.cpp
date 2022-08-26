#include "vrcuimanager.hpp"


assembler::vrc_ui_manager* assembler::vrc_ui_manager::instance()
{
    using func_t = vrc_ui_manager*(*)();
    static const auto func = memory::get_method<func_t>(VRCUIMANAGER);
    return func();
}

void assembler::vrc_ui_manager::hud_msg(const std::string_view text)
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] hud_msg passed nullptr\n"));
        logging::pop();
        return;
    }
    using func_t = void (*)(vrc_ui_manager*, il2cpp::il2cpp_string*);
    static const auto func = memory::get_method<func_t>(HUDMSG);
    func(this, il2cpp::string_new(text));
}
