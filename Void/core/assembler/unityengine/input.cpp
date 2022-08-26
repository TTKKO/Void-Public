#include "input.hpp"

bool assembler::unity_engine::input::get_key_down(const std::string_view name)
{
    if (!get_key_down_string_func_) 
        get_key_down_string_func_ = static_cast<get_key_down_string_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Input::GetKeyDownString(System.String)")));

    return get_key_down_string_func_(il2cpp::string_new(name));
}

bool assembler::unity_engine::input::get_key_down(const key_code key)
{
    if (!get_key_down_func_) 
        get_key_down_func_ = static_cast<get_key_down_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Input::GetKeyDownInt(UnityEngine.KeyCode)")));

    return get_key_down_func_(key);
}

bool assembler::unity_engine::input::get_key_up(const key_code key)
{
    if (!get_key_up_func_)
        get_key_up_func_ = static_cast<get_key_up_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Input::GetKeyUpInt(UnityEngine.KeyCode)")));

    return get_key_up_func_(key);
}

bool assembler::unity_engine::input::get_key(const std::string_view name)
{
    if (!get_key_string_func_) 
        get_key_string_func_ = static_cast<get_key_string_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Input::GetButtonDown(System.String)")));

    return get_key_string_func_(il2cpp::string_new(name));
}

bool assembler::unity_engine::input::get_key(const key_code name)
{
    if (!get_key_func_) 
        get_key_func_ = static_cast<get_key_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Input::GetKeyInt(UnityEngine.KeyCode)")));

    return get_key_func_(name);
}

float assembler::unity_engine::input::get_axis(const std::string_view axis_name)
{
    if (!get_axis_func_) 
        get_axis_func_ = static_cast<get_axis_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Input::GetAxis(System.String)")));

    return get_axis_func_(il2cpp::string_new(axis_name));
}

bool assembler::unity_engine::input::get_button_down(const std::string_view btn_name)
{
    if (!get_button_down_func_) 
        get_button_down_func_ = static_cast<get_button_down_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Input::GetButtonDown(System.String)")));

    return get_button_down_func_(il2cpp::string_new(btn_name));
}
