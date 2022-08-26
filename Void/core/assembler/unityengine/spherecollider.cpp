#include "spherecollider.hpp"

assembler::il2cpp::il2cpp_type* assembler::unity_engine::spherecollider::get_global_type()
{
    if (!type_)
        type_ = il2cpp::get_type(xorstr_("UnityEngine.SphereCollider, UnityEngine.PhysicsModule"));

    return type_;
}

float assembler::unity_engine::spherecollider::get_radius()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_radius passed nullptr.\n"));
        logging::pop();
        return NULL;
    }
    if (!get_radius_func_) get_radius_func_ = static_cast<get_radius_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.SphereCollider::get_radius()")));
    return get_radius_func_(this);
}
