#include "action.hpp"
#include "../../../../detours/cinlinedetour.hpp"

using namespace assembler::unity_engine::events;

unity_action* unity_action::ctor(const c_inline_detour* action)
{
    const auto obj = reinterpret_cast<unity_action*>(il2cpp::new_object(xorstr_("UnityEngine.Events.UnityAction, UnityEngine")));
    using func_t = void (*)(unity_action*, void*, std::intptr_t);
    static const auto func = memory::get_method<func_t>(UNITYACTIONCTOR);

    func(obj, nullptr, reinterpret_cast<std::intptr_t>(stub));

    using funcpointer_t = void(*)();
    *(reinterpret_cast<funcpointer_t*>(obj) + 2) = action->get_ptr();
    return obj;
}

void unity_action::stub()
{
}
