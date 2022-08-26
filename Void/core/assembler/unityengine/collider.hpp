/*
 *		assembler/unityengine/collider.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's Collider class
 */
#pragma once
#include "../unityengine/component.hpp"

namespace assembler::unity_engine
{
    struct collider : component
    {
        void set_enabled(bool value);
        void set_is_trigger(bool value);

        // @note: index 0 is center, index 1 is extents
        std::array<sdk::vector, 2u> get_bounds();

    private:
        using set_enabled_t = void(*)(collider*, bool);
        inline static set_enabled_t set_enabled_func_ = nullptr;

        using set_is_trigger_t = void(*)(collider*, bool);
        inline static set_is_trigger_t set_is_trigger_func_ = nullptr;

        using get_bounds_t = void(*)(collider*, std::array<sdk::vector, 2u>*);
        inline static get_bounds_t get_bounds_func_ = nullptr;
    };
}
