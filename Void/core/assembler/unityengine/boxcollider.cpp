#include "boxcollider.hpp"

assembler::il2cpp::il2cpp_type* assembler::unity_engine::boxcollider::get_global_type()
{
    if (!type_)
        type_ = il2cpp::get_type(xorstr_("UnityEngine.BoxCollider, UnityEngine.PhysicsModule"));

    return type_;
}

sdk::vector assembler::unity_engine::boxcollider::get_size()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_size passed nullptr.\n"));
        logging::pop();
        return sdk::vector{};
    }

    auto v = sdk::vector(0, 0, 0);
    if (!get_size_func_) get_size_func_ = static_cast<get_size_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.BoxCollider::get_size_Injected(UnityEngine.Vector3&)")));
    get_size_func_(this, &v);
    return v;
}

void assembler::unity_engine::boxcollider::set_size(const sdk::vector& size)
{
    if (!set_size_func_)
        set_size_func_ = static_cast<set_size_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.BoxCollider::set_size_Injected(UnityEngine.Vector3&)")));

    set_size_func_(this, size);
}
