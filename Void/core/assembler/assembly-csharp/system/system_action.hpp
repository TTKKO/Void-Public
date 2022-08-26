/*
 *		assembler/assembly-csharp/system/system_action.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Windows System Buffer class replication
 */

#ifndef SYSTEM_ACTION_HPP
#define SYSTEM_ACTION_HPP

#pragma once
#include "../../common.hpp"

class c_inline_detour;

namespace assembler::system_replication
{
    struct action : il2cpp::il2cpp_object
    {
        static action* ctor(const c_inline_detour* action);
        static void run_time_method();
    };
}

#endif
