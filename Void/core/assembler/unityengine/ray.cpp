#include "ray.hpp"
#include "../il2cpp/il2cpp.hpp"


assembler::unity_engine::ray* assembler::unity_engine::ray::ctor(const sdk::vector& origin,
                                                                 const sdk::vector& direction)
{
    const auto ret = reinterpret_cast<ray*>(il2cpp::new_object(xorstr_("UnityEngine.Ray, UnityEngine.CoreModule")));
    using func_t = void (*)(ray*, const sdk::vector&, const sdk::vector&);
    static const auto func = memory::get_method<func_t>(RAYCTOR);
    func(ret, origin, direction);
    return ret;
}

bool assembler::unity_engine::ray::raycast(ray* ray, raycast_hit* hit_info)
{
    static const auto klass = class_from_system_type(il2cpp::get_type(xorstr_("UnityEngine.Physics, UnityEngine.PhysicsModule")));
    return il2cpp::call_mifunc<bool>(klass, 26, ray, hit_info);
}
