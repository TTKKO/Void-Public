#include "system_action.hpp"
#include "../../../../detours/cinlinedetour.hpp"

assembler::system_replication::action* assembler::system_replication::action::ctor(const c_inline_detour* action)
{
    const auto obj = reinterpret_cast<system_replication::action*>(il2cpp::new_object(xorstr_("System.Action, mscorlib")));
    using func_t = void (*)(system_replication::action*, void*, std::intptr_t);
    static const auto func = memory::get_method<func_t>(UNITYACTIONCTOR);

    func(obj, nullptr, reinterpret_cast<std::intptr_t>(run_time_method));

    using funcpointer_t = void(*)();
    *(reinterpret_cast<funcpointer_t*>(obj) + 2) = action->get_ptr();
    return obj;
}

void assembler::system_replication::action::run_time_method()
{
    // balls
}
