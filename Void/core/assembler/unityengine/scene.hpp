/*
 *		assembler/unityengine/scene.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's Scene class
 */

#pragma once
#include "../il2cpp/il2cpp.hpp"

namespace assembler::unity_engine
{
    struct scene
    {
        std::int32_t m_handle;

        int32_t get_buildindex();
        int32_t get_handle();
    private:
        using get_buildindex_t = int32_t(*)(int32_t);
        inline static get_buildindex_t get_buildindex_func_ = nullptr;
    };

    struct scene_manager
    {
        static bool set_active_scene(scene scenee);
        static scene get_scene_by_name(std::string_view name);
        static scene get_active_scene();

    private:
        using set_active_scene_t = bool(*)(std::int32_t*);
        inline static set_active_scene_t set_active_scene_func_ = nullptr;

        using get_active_scene_t = void(*)(scene*);
        inline static get_active_scene_t get_active_scene_func_ = nullptr;

        using get_scene_by_name_t = void(*)(il2cpp::il2cpp_string*, scene*);
        inline static get_scene_by_name_t get_scene_by_name_func_ = nullptr;
    };
}
