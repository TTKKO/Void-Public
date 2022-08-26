/*
 *		assembler/unityengine/recttransform.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's RectTransform class
 */

#pragma once
#include "transform.hpp"

namespace assembler::unity_engine
{
    struct rect_transform : transform
    {
        void set_anchor_max(const sdk::vector_2d& value);
        void set_size_delta(const sdk::vector_2d& value);
    private:
        using set_anchor_max_t = void (*)(rect_transform*, const sdk::vector_2d&);
        inline static set_anchor_max_t set_anchor_max_func_ = nullptr;

        using set_size_delta_t = void (*)(rect_transform*, const sdk::vector_2d&);
        inline static set_size_delta_t set_size_delta_func_ = nullptr;
    };
}
