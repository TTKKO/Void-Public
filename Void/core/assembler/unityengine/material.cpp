#include "material.hpp"

#include "shader.hpp"
#include "../il2cpp/il2cpp.hpp"

void assembler::unity_engine::material::set_color(const std::string_view name, const sdk::color& value)
{
    const auto id = shader::property_to_id(name);
    if (!set_color_func_) set_color_func_ = static_cast<set_color_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.Material::SetColorImpl_Injected(System.Int32,UnityEngine.Color&)")));
    set_color_func_(this, id, value.base_alpha());
}

void assembler::unity_engine::material::set_pass(const int32_t p)
{
    if (!set_pass_func_) set_pass_func_ = static_cast<set_pass_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.Material::SetPass(System.Int32)")));
    set_pass_func_(this, p);
}


assembler::unity_engine::shader* assembler::unity_engine::material::get_shader()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_shader passed nullptr.\n"));
        logging::pop();
        return nullptr;
    }
    if (!get_shader_func_) get_shader_func_ = static_cast<get_shader_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.Material::get_shader()")));
    return get_shader_func_(this);
}

int32_t assembler::unity_engine::material::get_first_property_name_id_by_atrribute(const int32_t value)
{
    if (!get_first_property_name_id_by_atrribute_func_) get_first_property_name_id_by_atrribute_func_ = static_cast<
        get_first_property_name_id_by_atrribute_t>(il2cpp::resolve_icall(xorstr_(
        "UnityEngine.Material::GetFirstPropertyNameIdByAttribute(UnityEngine.Rendering.ShaderPropertyFlags)")));
    return get_first_property_name_id_by_atrribute_func_(this, value);
}

void assembler::unity_engine::material::set_maintexture(texture* tex)
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] set_maintexture passed nullptr.\n"));
        logging::pop();
        return;
    }
    auto v6 = this->get_first_property_name_id_by_atrribute(128);
    if (v6 < 0) v6 = shader::property_to_id(xorstr_("_MainTex"));
    if (!set_maintexture_func_) set_maintexture_func_ = static_cast<set_maintexture_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.Material::SetTextureImpl(System.Int32,UnityEngine.Texture)")));
    set_maintexture_func_(this, v6, tex);
}

void assembler::unity_engine::material::set_shader(shader* s)
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] set_shader passed nullptr.\n"));
        logging::pop();
        return;
    }
    if (!set_shader_func_) set_shader_func_ = static_cast<set_shader_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.Material::set_shader(UnityEngine.Shader)")));
    set_shader_func_(this, s);
}
