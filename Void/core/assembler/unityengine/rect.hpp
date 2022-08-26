/*
 *		assembler/unityengine/rect.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's Rect class
 */

#pragma once

#include "../common.hpp"

namespace assembler::unity_engine
{
    struct rect
    {
        float x;
        float y;
        float width;
        float height;

        explicit constexpr rect(const float x, const float y, const float width, const float height) : x(x), y(y), width(width), height(height) {}

        float get_width();
        float get_height();
    };
}
