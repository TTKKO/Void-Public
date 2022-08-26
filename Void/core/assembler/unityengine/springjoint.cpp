#include "springjoint.hpp"

assembler::il2cpp::il2cpp_type* assembler::unity_engine::springjoint::get_global_type()
{
    if (!type_)
        type_ = il2cpp::get_type(xorstr_("UnityEngine.SpringJoint, UnityEngine.PhysicsModule"));

    return type_;
}

float assembler::unity_engine::springjoint::get_spring()
{
    if (!get_spring_func_) get_spring_func_ = static_cast<get_spring_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.SpringJoint::get_spring()")));
    return get_spring_func_(this);
}

void assembler::unity_engine::springjoint::set_spring(const float v)
{
    if (!set_spring_func_) set_spring_func_ = static_cast<set_spring_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.SpringJoint::set_spring(System.Single)")));
    set_spring_func_(this, v);
}

float assembler::unity_engine::springjoint::get_damper()
{
    if (!get_damper_func_) get_damper_func_ = static_cast<get_damper_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.SpringJoint::get_damper()")));
    return get_damper_func_(this);
}

void assembler::unity_engine::springjoint::set_damper(const float v)
{
    if (!set_damper_func_) set_damper_func_ = static_cast<set_damper_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.SpringJoint::set_damper(System.Single)")));
    return set_damper_func_(this, v);
}

float assembler::unity_engine::springjoint::get_min_distance()
{
    if (!get_min_distance_func_) get_min_distance_func_ = static_cast<get_min_distance_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.SpringJoint::get_minDistance()")));
    return get_min_distance_func_(this);
}

void assembler::unity_engine::springjoint::set_min_distance(const float v)
{
    if (!set_min_distance_func_) set_min_distance_func_ = static_cast<set_min_distance_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.SpringJoint::set_minDistance(System.Single)")));
    return set_min_distance_func_(this, v);
}

float assembler::unity_engine::springjoint::get_max_distance()
{
    if (!get_max_distance_func_) get_max_distance_func_ = static_cast<get_max_distance_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.SpringJoint::get_maxDistance()")));
    return get_max_distance_func_(this);
}

void assembler::unity_engine::springjoint::set_max_distance(const float v)
{
    if (!set_max_distance_func_) set_max_distance_func_ = static_cast<set_max_distance_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.SpringJoint::set_maxDistance(System.Single)")));
    return set_max_distance_func_(this, v);
}

float assembler::unity_engine::springjoint::get_tolerance()
{
    if (!get_tolerance_func_) get_tolerance_func_ = static_cast<get_tolerance_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.SpringJoint::get_tolerance()")));
    return get_tolerance_func_(this);
}

void assembler::unity_engine::springjoint::set_tolerance(const float v)
{
    if (!set_tolerance_func_) set_tolerance_func_ = static_cast<set_tolerance_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.SpringJoint::set_tolerance(System.Single)")));
    return set_tolerance_func_(this, v);
}
