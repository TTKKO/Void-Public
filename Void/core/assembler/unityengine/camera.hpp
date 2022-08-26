/*
 *		assembler/unityengine/camera.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's Camera class
 */

#pragma once
#include "behaviour.hpp"

namespace assembler::unity_engine
{
    struct camera : behaviour
    {
        static camera* get_main();
        sdk::vector world_to_screen_point(const sdk::vector& position);
        void set_field_of_view(float fov);
        float get_near_clip_plane();
        void set_near_clip_plane(float val);

    private:
        using get_main_t = camera * (*)();
        inline static get_main_t get_main_func_ = nullptr;

        using world_to_screen_point_t = void (*)(camera*, const sdk::vector&, int64_t, sdk::vector*);
        inline static world_to_screen_point_t world_to_screen_point_func_ = nullptr;

        using set_field_of_view_t = void (*)(camera*, float);
        inline static set_field_of_view_t set_field_of_view_func_ = nullptr;

        using get_near_clip_plane_t = float (*)(camera*);
        inline static get_near_clip_plane_t get_near_clip_plane_func_ = nullptr;

        using set_near_clip_plane_t = void (*)(camera*, float);
        inline static set_near_clip_plane_t set_near_clip_plane_func_ = nullptr;
    };
}
