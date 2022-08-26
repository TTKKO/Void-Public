/*
 *		assembler/assembly-csharp/dynamic_bone_collider.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's VRChat DynamicBoneCollider class replication
 */

#pragma once
#include "../unityengine/component.hpp"

namespace assembler
{
    struct dynamic_bone_collider : unity_engine::component
    {
    	enum class bounds : int
        {
            outside = 0,
            inside = 1
        };

        bounds get_bounds();
    };
}