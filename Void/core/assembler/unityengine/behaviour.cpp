#include "behaviour.hpp"

void assembler::unity_engine::behaviour::set_enabled(const bool val)
{
    if (!set_enabled_func_)
        set_enabled_func_ = static_cast<set_enabled_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Behaviour::set_enabled(System.Boolean)")));

    set_enabled_func_(this, val);
}
