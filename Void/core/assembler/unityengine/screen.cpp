#include "screen.hpp"

int32_t assembler::unity_engine::screen::get_height()
{
    if (!get_height_func_) get_height_func_ = static_cast<get_height_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.Screen::get_height()")));
    return get_height_func_();
}

int32_t assembler::unity_engine::screen::get_width()
{
    if (!get_width_func_) get_width_func_ = static_cast<get_width_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.Screen::get_width()")));
    return get_width_func_();
}
