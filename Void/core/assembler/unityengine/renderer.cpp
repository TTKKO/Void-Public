#include "renderer.hpp"

#include "../common.hpp"
#include "../../../offsets.hpp"

void assembler::unity_engine::renderer::set_enabled(const bool value)
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] set_enabled passed nullptr.\n"));
        logging::pop();
        return;
    }
    if (!set_enabled_func_) set_enabled_func_ = static_cast<set_enabled_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.Renderer::set_enabled(System.Boolean)")));
    set_enabled_func_(this, value);
}

assembler::unity_engine::material* assembler::unity_engine::renderer::get_material()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_material passed nullptr.\n"));
        logging::pop();
        return nullptr;
    }
    if (!get_material_func_) get_material_func_ = static_cast<get_material_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.Renderer::GetMaterial()")));
    return get_material_func_(this);
}

assembler::il2cpp::il2cpp_array_wrapper<assembler::unity_engine::material*>* assembler::unity_engine::renderer::get_materials()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_materials passed nullptr.\n"));
        logging::pop();
        return nullptr;
    }
    if (!get_materials_func_) get_materials_func_ = static_cast<get_materials_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.Renderer::GetMaterialArray()")));
    return get_materials_func_(this);
}

//UnityEngine::Material* UnityEngine::Renderer::SharedMaterial()
//{
//	using func_t = Material * (*)(Renderer* _this);
//
//	func_t func = GetMethod<func_t>(0Ax391F630);
//
//	return func(this);
//}
