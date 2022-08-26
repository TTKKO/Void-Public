/*
 *		assembler/assembly-csharp/ui_vrc_list.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's VRChat UiVrcList class replication
 */

#pragma once
#include "../unityengine/component.hpp"

namespace assembler
{
    struct ui_vrc_list : unity_engine::component
    {
        static il2cpp::il2cpp_type* get_type();
        void* get_dictionary();
        void set_dictionary(void* ptr);

    private:
        static inline il2cpp::il2cpp_type* type_;
    };
}
