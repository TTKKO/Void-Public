#include "shader.hpp"

int32_t assembler::unity_engine::shader::property_to_id(const std::string_view name)
{
    if (!property_to_id_func_) property_to_id_func_ = static_cast<property_to_id_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.Shader::PropertyToID(System.String)")));
    return property_to_id_func_(il2cpp::string_new(name));
}

assembler::unity_engine::shader* assembler::unity_engine::shader::find(const std::string_view name)
{
    if (!find_func_) 
        find_func_ = static_cast<find_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Shader::Find(System.String)")));

    return find_func_(il2cpp::string_new(name));
}

assembler::unity_engine::shader* assembler::unity_engine::shader::find(const std::wstring_view name)
{
    if (!find_func_)
        find_func_ = static_cast<find_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Shader::Find(System.String)")));

    return find_func_(il2cpp::string_new(name));
}
