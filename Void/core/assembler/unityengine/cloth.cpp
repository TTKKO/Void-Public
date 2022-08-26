#include "cloth.hpp"

assembler::unity_engine::spherecollider* assembler::unity_engine::cloth_sphere_collider_pair::get_first()
{
    if (this == nullptr) return nullptr;
    return *reinterpret_cast<spherecollider**>(reinterpret_cast<std::uint8_t*>(this) + 0x0);
}

assembler::unity_engine::spherecollider* assembler::unity_engine::cloth_sphere_collider_pair::get_second()
{
    if (this == nullptr) return nullptr;
    return *reinterpret_cast<spherecollider**>(reinterpret_cast<std::uint8_t*>(this) + 0x8);
}

assembler::il2cpp::il2cpp_type* assembler::unity_engine::cloth::get_global_type()
{
    if (!type_)
        type_ = il2cpp::get_type(xorstr_("UnityEngine.Cloth, UnityEngine.ClothModule"));

    return type_;
}

void assembler::unity_engine::cloth::set_enabled(const bool value)
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] set_enabled passed nullptr.\n"));
        logging::pop();
        return;
    }
    if (!set_enabled_func_)
        set_enabled_func_ = static_cast<set_enabled_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Cloth::set_enabled(System.Boolean)")));
    
    set_enabled_func_(this, value);
}

assembler::il2cpp::il2cpp_array* assembler::unity_engine::cloth::get_sphere_colliders()
{
    if (this == nullptr) return nullptr;
    
    if (!get_sphere_colliders_func_)
        get_sphere_colliders_func_ = static_cast<get_sphere_colliders_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Cloth::get_sphereColliders()")));
    
    return get_sphere_colliders_func_(this);
}
