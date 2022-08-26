/*
 *		assembler/unityengine/cloth.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's Cloth class
 */

#pragma once
#include "component.hpp"

namespace assembler::unity_engine
{
    struct spherecollider;

    struct cloth_sphere_collider_pair : il2cpp::il2cpp_object
    {
        spherecollider* get_first();
        spherecollider* get_second();
    };

    struct cloth : component
    {
        static il2cpp::il2cpp_type* get_global_type();

        void set_enabled(bool value);
        il2cpp::il2cpp_array* get_sphere_colliders();

    private:
        static inline il2cpp::il2cpp_type* type_ = nullptr;

        using set_enabled_t = void(*)(cloth*, bool);
        inline static set_enabled_t set_enabled_func_ = nullptr;

        using get_sphere_colliders_t = il2cpp::il2cpp_array*(*)(cloth*);
        inline static get_sphere_colliders_t get_sphere_colliders_func_ = nullptr;
    };
}
