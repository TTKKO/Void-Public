/*
 *		assembler/unityengine/assetbundle.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's AssetBundle class
 */

#pragma once
#include "../common.hpp"

namespace assembler::unity_engine
{
    struct assetbundle : object
    {
        static assetbundle* load_from_file(std::string_view path);
        il2cpp::il2cpp_array* get_all_asset_names();
        object* load_asset(std::wstring_view prefab, il2cpp::il2cpp_type* type);
        void unload(bool remove_all_objects);

    private:

        using load_from_file_t = assetbundle*(*)(il2cpp::il2cpp_string*, std::uint32_t, std::uintptr_t);
        inline static load_from_file_t load_from_file_func_ = nullptr;

        using get_all_asset_names_t = il2cpp::il2cpp_array* (*)(assetbundle*);
        inline static get_all_asset_names_t get_all_asset_names_func_ = nullptr;

        using load_asset_t = object * (*)(assetbundle*, il2cpp::il2cpp_string*, il2cpp::il2cpp_type*);
        inline static load_asset_t load_asset_func_ = nullptr;

        using unload_t = void (*)(assetbundle*, bool);
        inline static unload_t unload_func_ = nullptr;
    };
}
