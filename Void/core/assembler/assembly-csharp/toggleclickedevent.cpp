#include "toggleclickedevent.hpp"

using namespace assembler::unity_engine::ui;

toggle_clicked_event* toggle_clicked_event::ctor()
{
    const auto onclick_template = ui_manager_impl::instance()->get_quickmenu()->get_transform()->find(xorstr_("Container/Window/QMParent/Menu_Settings/Panel_QM_ScrollRect/Viewport/VerticalLayoutGroup/Buttons_UI_Elements_Row_2/Button_ToggleFallbackIcon"))->get_component(xorstr_("UnityEngine.UI.Toggle"));
    const auto button_clicked_new = reinterpret_cast<toggle_clicked_event*>(il2cpp::new_object_from_class(reinterpret_cast<il2cpp::il2cpp_class*>(reinterpret_cast<toggle*>(onclick_template)->get_toggle()->klass), false));
    using func_t = void (*)(toggle_clicked_event*);
    static const auto func = memory::get_method<func_t>(TOGGLECLICKEDEVENTCTOR);
    func(button_clicked_new);
    return button_clicked_new;
}
