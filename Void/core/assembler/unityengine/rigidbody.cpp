#include "rigidbody.hpp"

void assembler::unity_engine::rigidbody::set_use_gravity(const bool value)
{
    if (!this)
        return;

    if (!set_use_gravity_func_)
        set_use_gravity_func_ = static_cast<set_use_gravity_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Rigidbody::set_useGravity(System.Boolean)")));

    return set_use_gravity_func_(this, value);
}

void assembler::unity_engine::rigidbody::set_is_kinematic(const bool value)
{
    if (!this)
        return;

    if (!set_is_kinematic_func_)
        set_is_kinematic_func_ = static_cast<set_is_kinematic_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Rigidbody::set_isKinematic(System.Boolean)")));

    return set_is_kinematic_func_(this, value);
}
