#include "collider.hpp"

void assembler::unity_engine::collider::set_enabled(const bool value)
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] set_enabled passed nullptr.\n"));
        logging::pop();
        return;
    }
    if (!set_enabled_func_) set_enabled_func_ = static_cast<set_enabled_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.Collider::set_enabled(System.Boolean)")));
    set_enabled_func_(this, value);
}

void assembler::unity_engine::collider::set_is_trigger(const bool value)
{
    if (!this)
        return;

    if (!set_is_trigger_func_) 
        set_is_trigger_func_ = static_cast<set_is_trigger_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Collider::set_isTrigger(System.Boolean)")));

    set_is_trigger_func_(this, value);
}

std::array<sdk::vector, 2> assembler::unity_engine::collider::get_bounds()
{
    auto ret = std::array{ sdk::vector(), sdk::vector() };

    if (!this)
        return ret;

    if (!get_bounds_func_)
        get_bounds_func_ = static_cast<get_bounds_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Collider::get_bounds_Injected(UnityEngine.Bounds&)")));

    get_bounds_func_(this, &ret);

    return ret;
}
