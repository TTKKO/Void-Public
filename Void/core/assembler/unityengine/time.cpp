#include "time.hpp"

float assembler::unity_engine::time::get_delta_time()
{
    if (!delta_time_func) delta_time_func = static_cast<delta_time_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.Time::get_deltaTime()")));
    return delta_time_func();
}

float assembler::unity_engine::time::get_time()
{
    if (!time_func) time_func = static_cast<time_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Time::get_time()")));
    return time_func();
}
