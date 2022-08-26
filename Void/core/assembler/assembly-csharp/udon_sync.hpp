/*
 *		assembler/assembly-csharp/udon_sync.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's VRChat UdonSync class replication
 */

#pragma once
#include "../unityengine/component.hpp"

namespace assembler
{
    struct udon_sync : unity_engine::component
    {
        static il2cpp::il2cpp_type* get_type();
    private:
        static inline il2cpp::il2cpp_type* type_;
    };
}
