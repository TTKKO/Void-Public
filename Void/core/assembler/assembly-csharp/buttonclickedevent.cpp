#include "buttonclickedevent.hpp"

using namespace assembler::unity_engine::ui;

button_clicked_event* button_clicked_event::ctor()
{
    const auto onclick_template = ui_manager_impl::instance()->get_quickmenu()->get_transform()->find(xorstr_("Container/Window/QMParent/Menu_Dashboard/ScrollRect/Viewport/VerticalLayoutGroup/Buttons_QuickActions/Button_GoHome"))->get_component(xorstr_("UnityEngine.UI.Button"));
    const auto button_clicked_new = reinterpret_cast<button_clicked_event*>(il2cpp::new_object_from_class(reinterpret_cast<il2cpp::il2cpp_class*>(reinterpret_cast<button*>(onclick_template)->get_on_click()->klass), false));

    using func_t = void (*)(button_clicked_event*);
    static const auto func = memory::get_method<func_t>(BUTTONCLICKCTOR);
    func(button_clicked_new);
    return button_clicked_new;
}
