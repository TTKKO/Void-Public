#include "cursor.hpp"

void assembler::unity_engine::cursor::set_visible(const bool value)
{
    if (!set_visible_func_) set_visible_func_ = static_cast<set_visible_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.Cursor::set_visible(System.Boolean)")));
    return set_visible_func_(value);
}

void assembler::unity_engine::cursor::set_lock_state(const cursor_lock_mode mode)
{
    if (!set_lock_state_func_) set_lock_state_func_ = static_cast<set_lock_state_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.Cursor::set_lockState(UnityEngine.CursorLockMode)")));
    return set_lock_state_func_(mode);
}

assembler::unity_engine::cursor_lock_mode assembler::unity_engine::cursor::get_lock_state()
{
    if (!get_lock_state_func_) get_lock_state_func_ = static_cast<get_lock_state_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.Cursor::get_lockState()")));
    return get_lock_state_func_();
}
