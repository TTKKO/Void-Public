#include "gui.hpp"
#include <iostream>

void assembler::unity_engine::gui::set_color(const sdk::color& c)
{
    if (!set_color_func_) set_color_func_ = static_cast<set_color_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.GUI::set_color_Injected(UnityEngine.Color&)")));
    set_color_func_(c.base_alpha());
}

sdk::color assembler::unity_engine::gui::get_color()
{
    if (!get_color_func_) get_color_func_ = static_cast<get_color_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.GUI::get_color_Injected(UnityEngine.Color&)")));
    auto c = std::array<float, 4U>();
    get_color_func_(&c);
    return sdk::color(c);
}

sdk::matrix assembler::unity_engine::gui::get_matrix()
{
    if (!get_matrix_func_) get_matrix_func_ = static_cast<get_matrix_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.GUIClip::GetMatrix_Injected(UnityEngine.Matrix4x4&)")));
    auto m = sdk::matrix();
    get_matrix_func_(&m);
    return m;
}

void assembler::unity_engine::gui::set_matrix(const sdk::matrix& m)
{
    if (!set_matrix_func_) set_matrix_func_ = static_cast<set_matrix_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.GUIClip::SetMatrix_Injected(UnityEngine.Matrix4x4&)")));
    set_matrix_func_(m);
}
