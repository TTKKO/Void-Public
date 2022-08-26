/*
 *		assembler/assembly-csharp/highlightsfx.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's VRChat HighlightsFX class replication
 */

#pragma once
#include "../common.hpp"

namespace assembler::unity_engine
{
    struct material;
    struct renderer;
}

namespace assembler
{
    struct highlights_fx : il2cpp::il2cpp_object
    {
        DELCONST(highlights_fx);

        static highlights_fx* instance();
        void enable_outline(unity_engine::renderer* renderer, bool value);
        unity_engine::material* get_material();
    };
}

//private static whatthefuck <whatthefuck>k__BackingField; // 0x0
//protected readonly HashSet<Renderer> whatthefuck; // 0x28
//protected Shader whatthefuck; // 0x30
//protected Material whatthefuck; // 0x38
