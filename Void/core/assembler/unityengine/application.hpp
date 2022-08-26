/*
 *		assembler/unityengine/application.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's Application class
 */

#pragma once
#include "../common.hpp"
#include "../../../offsets.hpp"
#include "../il2cpp/il2cpp.hpp"

namespace assembler::unity_engine
{
    struct application
    {
        static bool is_focused();
        static void set_target_frame_rate(std::int32_t framerate);

    private:
        using is_focused_t = bool(*)();
        inline static is_focused_t is_focused_func_ = nullptr;

        using set_target_frame_rate_t = void(*)(std::int32_t);
        inline static set_target_frame_rate_t set_target_frame_rate_func_ = nullptr;
    };
}
