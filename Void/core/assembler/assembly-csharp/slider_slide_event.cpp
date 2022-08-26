#include "slider_slide_event.hpp"
#include "ui_manager_impl.hpp"

using namespace assembler::unity_engine::ui;

slider_clicked_event* slider_clicked_event::ctor()
{
    const auto onclick_template = ui_manager_impl::instance()->get_quickmenu()->get_transform()->find(xorstr_("Container/Window/QMParent/Menu_AudioSettings/Content/Audio/VolumeSlider_World/Slider"))->get_component(xorstr_("UnityEngine.UI.Slider"));
    const auto button_clicked_new = reinterpret_cast<slider_clicked_event*>(il2cpp::new_object_from_class(reinterpret_cast<il2cpp::il2cpp_class*>(reinterpret_cast<slider*>(onclick_template)->get_on_slide()->klass), false));
    using func_t = void (*)(slider_clicked_event*);
    static const auto func = memory::get_method<func_t>(TOGGLECLICKEDEVENTCTOR);
    func(button_clicked_new);
    return button_clicked_new;
}
