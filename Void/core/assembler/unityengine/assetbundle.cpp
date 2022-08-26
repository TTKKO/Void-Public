#include "assetbundle.hpp"

assembler::unity_engine::assetbundle* assembler::unity_engine::assetbundle::load_from_file(const std::string_view path)
{
    if (!load_from_file_func_)
        load_from_file_func_ = static_cast<load_from_file_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.AssetBundle::LoadFromFile_Internal(System.String,System.UInt32,System.UInt64)")));

    return load_from_file_func_(il2cpp::string_new(path), 0, 0);
}

assembler::il2cpp::il2cpp_array* assembler::unity_engine::assetbundle::get_all_asset_names()
{
    if (!get_all_asset_names_func_)
        get_all_asset_names_func_ = static_cast<get_all_asset_names_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.AssetBundle::GetAllAssetNames()")));

    return get_all_asset_names_func_(this);
}

assembler::unity_engine::object* assembler::unity_engine::assetbundle::load_asset(const std::wstring_view prefab, il2cpp::il2cpp_type* type)
{
    if (!load_asset_func_)
        load_asset_func_ = static_cast<load_asset_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.AssetBundle::LoadAsset_Internal(System.String,System.Type)")));

    return load_asset_func_(this, il2cpp::string_new(prefab), type);
}

void assembler::unity_engine::assetbundle::unload(const bool remove_all_objects)
{
    if (!unload_func_)
        unload_func_ = static_cast<unload_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.AssetBundle::Unload(System.Boolean)")));

    return unload_func_(this, remove_all_objects);
}
