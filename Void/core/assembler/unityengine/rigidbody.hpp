/*
 *		assembler/unityengine/rigidbody.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's Rigidbody class
 */

#pragma once
#include "component.hpp"

namespace assembler::unity_engine
{
    struct rigidbody : component
    {
        void set_use_gravity(bool value);
        void set_is_kinematic(bool value);

    private:
        using set_use_gravity_t = void(*)(rigidbody*, bool);
        inline static set_use_gravity_t set_use_gravity_func_ = nullptr;

        using set_is_kinematic_t = void(*)(rigidbody*, bool);
        inline static set_is_kinematic_t set_is_kinematic_func_ = nullptr;
    };
}
