/*
 *		assembler/assembly-csharp/dynamic_bone.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's VRChat DynamicBone class replication
 */

#pragma once
#include "../unityengine/component.hpp"

namespace assembler
{
    struct dynamic_bone : unity_engine::component
    {
        unity_engine::transform* get_root();
    };
}
