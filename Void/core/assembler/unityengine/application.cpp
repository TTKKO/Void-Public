#include "application.hpp"

bool assembler::unity_engine::application::is_focused()
{
    if (!is_focused_func_) is_focused_func_ = static_cast<is_focused_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.Application::get_isFocused()")));
    return is_focused_func_();
}

void assembler::unity_engine::application::set_target_frame_rate(const std::int32_t framerate)
{
    if (!set_target_frame_rate_func_) 
        set_target_frame_rate_func_ = static_cast<set_target_frame_rate_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Application::set_targetFrameRate(System.Int32)")));
    return set_target_frame_rate_func_(framerate);
}
