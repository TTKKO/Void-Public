#include "skinnedmeshrenderer.hpp"

assembler::il2cpp::il2cpp_type* assembler::unity_engine::skinnedmeshrenderer::get_global_type()
{
    if (!type_)
        type_ = il2cpp::get_type(xorstr_("UnityEngine.SkinnedMeshRenderer, UnityEngine.CoreModule"));

    return type_;
}

assembler::unity_engine::mesh* assembler::unity_engine::skinnedmeshrenderer::get_sharedmesh()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_sharedmesh passed nullptr.\n"));
        logging::pop();
        return nullptr;
    }
    if (!get_sharedmesh_func_) get_sharedmesh_func_ = static_cast<get_sharedmesh_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.SkinnedMeshRenderer::get_sharedMesh()")));
    return get_sharedmesh_func_(this);
}

assembler::unity_engine::transform* assembler::unity_engine::skinnedmeshrenderer::get_root_bone()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_root_bone passed nullptr.\n"));
        logging::pop();
        return nullptr;
    }
    if (!get_root_bone_func_) get_root_bone_func_ = static_cast<get_root_bone_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.SkinnedMeshRenderer::get_rootBone()")));
    return get_root_bone_func_(this);
}

assembler::il2cpp::il2cpp_array_wrapper<assembler::unity_engine::object*>* assembler::unity_engine::skinnedmeshrenderer::get_bones()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_bones passed nullptr.\n"));
        logging::pop();
        return nullptr;
    }
    if (!get_bones_func_) get_bones_func_ = static_cast<get_bones_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.SkinnedMeshRenderer::get_bones()")));
    return get_bones_func_(this);
}

void assembler::unity_engine::skinnedmeshrenderer::set_bones(il2cpp::il2cpp_array* bones)
{
    if (this == nullptr || bones == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] set_bones passed nullptr.\n"));
        logging::pop();
        return;
    }
    if (!set_bones_func_) set_bones_func_ = static_cast<set_bones_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.SkinnedMeshRenderer::set_bones(UnityEngine.Transform[])")));
    set_bones_func_(this, bones);
}
