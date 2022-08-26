/*
 *		assembler/unity_engine/unity_time.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's Time class
 */

#pragma once
#include "../il2cpp/il2cpp.hpp"

namespace assembler::unity_engine
{
    struct time
    {
        static float get_delta_time();
        static float get_time();

    private:
        using time_t = float(*)();
        using delta_time_t = float(*)();

        inline static time_t time_func = nullptr;
        inline static delta_time_t delta_time_func = nullptr;
    };
}
