/*
 *		assembler/unityengine/springjoint.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's SpringJoint class
 */

#pragma once
#include "component.hpp"

namespace assembler::unity_engine
{
    struct springjoint : component
    {
        static il2cpp::il2cpp_type* get_global_type();

        float get_spring();
        void set_spring(float v);
        float get_damper();
        void set_damper(float v);
        float get_min_distance();
        void set_min_distance(float v);
        float get_max_distance();
        void set_max_distance(float v);
        float get_tolerance();
        void set_tolerance(float v);

    private:
        inline static il2cpp::il2cpp_type* type_ = nullptr;

        using get_spring_t = float(*)(springjoint*);
        inline static get_spring_t get_spring_func_ = nullptr;

        using set_spring_t = void(*)(springjoint*, float);
        inline static set_spring_t set_spring_func_ = nullptr;

        using get_damper_t = float(*)(springjoint*);
        inline static get_damper_t get_damper_func_ = nullptr;

        using set_damper_t = void(*)(springjoint*, float);
        inline static set_damper_t set_damper_func_ = nullptr;

        using get_min_distance_t = float(*)(springjoint*);
        inline static get_min_distance_t get_min_distance_func_ = nullptr;

        using set_min_distance_t = void(*)(springjoint*, float);
        inline static set_min_distance_t set_min_distance_func_ = nullptr;

        using get_max_distance_t = float(*)(springjoint*);
        inline static get_max_distance_t get_max_distance_func_ = nullptr;

        using set_max_distance_t = void(*)(springjoint*, float);
        inline static set_max_distance_t set_max_distance_func_ = nullptr;

        using get_tolerance_t = float(*)(springjoint*);
        inline static get_tolerance_t get_tolerance_func_ = nullptr;

        using set_tolerance_t = void(*)(springjoint*, float);
        inline static set_tolerance_t set_tolerance_func_ = nullptr;
    };
}
