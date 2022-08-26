/*
 *		assembler/unityengine/ray.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's Ray class
 */

#pragma once

#include "../common.hpp"
#include "../../sdk/datatypes/vector.h"

namespace assembler::unity_engine
{
    struct raycast_hit
    {
        float point[3];
    	float normal[3];
        std::uint32_t faceid;
        float distance;
        float uv[2];
        std::int32_t collider;
    };

    struct ray
    {
        float origin[3];
        float direction[3];

        static ray* ctor(const sdk::vector& origin, const sdk::vector& direction);
        static bool raycast(ray* ray, raycast_hit* hit_info);
    };
}
