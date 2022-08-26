#include "xrdevice.hpp"

bool assembler::unity_engine::xrdevice::get_is_present()
{
    if (!get_is_present_func_) 
        get_is_present_func_ = static_cast<get_is_present_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.XR.XRDevice::get_isPresent()")));

    return get_is_present_func_();
}

assembler::il2cpp::il2cpp_string* assembler::unity_engine::xrdevice::get_model()
{
    if (!get_model_func_)
        get_model_func_ = static_cast<get_model_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.XR.XRDevice::get_model()")));

    return get_model_func_();
}
