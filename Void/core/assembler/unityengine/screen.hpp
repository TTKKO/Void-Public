/*
 *		assembler/unityengine/screen.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's Screen class
 */

#pragma once
#include "../il2cpp/il2cpp.hpp"

namespace assembler::unity_engine
{
    struct screen
    {
        static int32_t get_height();
        static int32_t get_width();

    private:
        using get_height_t = int32_t(*)();
        inline static get_height_t get_height_func_ = nullptr;

        using get_width_t = int32_t(*)();
        inline static get_width_t get_width_func_ = nullptr;
    };
}
