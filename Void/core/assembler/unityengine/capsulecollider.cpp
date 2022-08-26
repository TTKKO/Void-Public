#include "capsulecollider.hpp"

assembler::il2cpp::il2cpp_type* assembler::unity_engine::capsulecollider::get_global_type()
{
    if (!type_)
        type_ = il2cpp::get_type(xorstr_("UnityEngine.CapsuleCollider, UnityEngine.PhysicsModule"));

    return type_;
}

float assembler::unity_engine::capsulecollider::get_radius()
{
    if (!get_radius_func_)
        get_radius_func_ = static_cast<get_radius_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.CapsuleCollider::get_radius()")));

    return get_radius_func_(this);
}

float assembler::unity_engine::capsulecollider::get_height()
{
    if (!get_height_func_)
        get_height_func_ = static_cast<get_height_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.CapsuleCollider::get_height()")));

    return get_height_func_(this);
}

std::int32_t assembler::unity_engine::capsulecollider::get_direction()
{
    if (!get_direction_func_)
        get_direction_func_ = static_cast<get_direction_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.CapsuleCollider::get_direction()")));

    return get_direction_func_(this);
}

