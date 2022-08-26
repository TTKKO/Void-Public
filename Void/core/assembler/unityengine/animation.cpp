#include "animation.hpp"

assembler::il2cpp::il2cpp_type* assembler::unity_engine::animation::get_global_type()
{
    if (!type_)
        type_ = il2cpp::get_type(xorstr_("UnityEngine.Animation, UnityEngine.AnimationModule"));

    return type_;
}

void assembler::unity_engine::animation::stop()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] stop passed nullptr.\n"));
        logging::pop();
        return;
    }
    if (!stop_func_) stop_func_ = static_cast<stop_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.Animation::INTERNAL_CALL_Stop(UnityEngine.Animation)")));
    return stop_func_(this);
}
