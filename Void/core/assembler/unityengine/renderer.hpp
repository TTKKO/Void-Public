/*
 *		assembler/unityengine/rederer.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's Renderer class
 */

#pragma once
#include "../unityengine/component.hpp"

namespace assembler::unity_engine
{
    struct material;

    struct renderer : component
    {
        void set_enabled(bool value);
        material* get_material();
        il2cpp::il2cpp_array_wrapper<material*>* get_materials();
    private:
        using set_enabled_t = void (*)(renderer*, bool);
        inline static set_enabled_t set_enabled_func_ = nullptr;

        using get_material_t = material * (*)(renderer*);
        inline static get_material_t get_material_func_ = nullptr;

        using get_materials_t = il2cpp::il2cpp_array_wrapper<material*>* (*)(renderer*);
        inline static get_materials_t get_materials_func_ = nullptr;
    };
}
