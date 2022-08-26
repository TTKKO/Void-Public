/*
 *		assembler/unityengine/gizmos.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's Gizmos class
 */

#pragma once
#include "../common.hpp"
#include "../../sdk/datatypes/vector.h"
#include "../il2cpp/il2cpp.hpp"

namespace assembler::unity_engine
{
    struct gizmos
    {
        DELCONST(gizmos);

        static void draw_cube(const sdk::vector& center, const sdk::vector& size);

    private:
        using draw_cube_t = void(*)(const sdk::vector&, const sdk::vector&);
        inline static draw_cube_t draw_cube_ = nullptr;
    };
}
