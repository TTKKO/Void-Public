/*
 *		assembler/unityengine/capsulecollider.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's CapsuleCollider class
 */

#pragma once
#include "../unityengine/collider.hpp"

namespace assembler::unity_engine
{
    struct capsulecollider : collider
    {
        static il2cpp::il2cpp_type* get_global_type();

        float get_radius();
        float get_height();
        std::int32_t get_direction();

    private:
        static inline il2cpp::il2cpp_type* type_ = nullptr;

        using get_radius_t = float(*)(capsulecollider*);
        inline static get_radius_t get_radius_func_ = nullptr;

        using get_height_t = float(*)(capsulecollider*);
        inline static get_height_t get_height_func_ = nullptr;

        using get_direction_t = std::int32_t(*)(capsulecollider*);
        inline static get_direction_t get_direction_func_ = nullptr;
    };
}
