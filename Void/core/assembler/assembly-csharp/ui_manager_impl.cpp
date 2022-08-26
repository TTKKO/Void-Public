#include "ui_manager_impl.hpp"
#include "../il2cpp/il2cpp.hpp"
#include "../unityengine/gameobject.hpp"

assembler::ui_manager_impl* assembler::ui_manager_impl::instance()
{
    using func_t = ui_manager_impl*(*)();
    static const auto func = memory::get_method<func_t>(UIMANAGERIMPL);
    return func();
}

assembler::unity_engine::game_object* assembler::ui_manager_impl::get_quickmenu()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_quickmenu passed nullptr\n"));
        logging::pop();
        return nullptr;
    }

    /*
		Canvas_QuickMenu
		INVALID_STRING
		Canvas_QuickMenu(Clone)
		INVALID_STRING
		INVALID_STRING
		MenuContent
     */

    return *reinterpret_cast<unity_engine::game_object**>(reinterpret_cast<std::uint8_t*>(this) + 0x70);
}

assembler::vrc::core::api_user* assembler::ui_manager_impl::selected_user()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] selected_user passed nullptr\n"));
        logging::pop();
        return nullptr;
    }
    return *reinterpret_cast<vrc::core::api_user**>(reinterpret_cast<std::uint8_t*>(this) + 0x208);
}
