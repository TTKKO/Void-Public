/*
 *		assembler/unityengine/spherecollider.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's SphereCollider class
 */

#pragma once
#include "collider.hpp"

namespace assembler::unity_engine
{
    struct spherecollider : collider
    {
        static il2cpp::il2cpp_type* get_global_type();
        float get_radius();

    private:
        static inline il2cpp::il2cpp_type* type_ = nullptr;

        using get_radius_t = float(*)(spherecollider*);
        inline static get_radius_t get_radius_func_ = nullptr;
    };
}
