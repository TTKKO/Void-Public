/*
 *		assembler/unityengine/events/action.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's Action class
 */

#pragma once
#include "../../common.hpp"

class c_inline_detour;

namespace assembler::unity_engine::events
{
    struct unity_action : object
    {
        static unity_action* ctor(const c_inline_detour* action);
        static void stub();
    };;
}
