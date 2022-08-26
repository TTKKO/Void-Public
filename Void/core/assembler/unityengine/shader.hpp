/*
 *		assembler/unityengine/shader.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's Shader class
 */

#pragma once
#include "../unityengine/component.hpp"

namespace assembler::unity_engine
{
    struct shader : object
    {
        static int32_t property_to_id(std::string_view name);
        static shader* find(std::string_view name);
        static shader* find(std::wstring_view name);

    private:
        using property_to_id_t = int32_t(*)(il2cpp::il2cpp_string*);
        inline static property_to_id_t property_to_id_func_ = nullptr;

        using find_t = shader * (*)(il2cpp::il2cpp_string*);
        inline static find_t find_func_ = nullptr;
    };
}
