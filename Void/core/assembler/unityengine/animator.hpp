/*
 *		assembler/unityengine/animator.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's Animator class
 */

#pragma once
#include "behaviour.hpp"

namespace assembler::unity_engine
{
    struct animator : behaviour
    {
        transform* get_bone_transform(std::int32_t bone);
    private:
        using get_bone_index_from_mono_t = std::int32_t(*)(std::int32_t);
        inline static get_bone_index_from_mono_t get_bone_index_from_mono_func_ = nullptr;

        using get_bone_transform_t = transform*(*)(animator*, std::int32_t);
        inline static get_bone_transform_t get_bone_transform_func_ = nullptr;
    };
}
