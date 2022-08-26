/*
 *		assembler/unityengine/animation.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's Animation class
 */

#pragma once
#include "../il2cpp/il2cpp.hpp"

namespace assembler::unity_engine
{
    struct animation
    {
        static il2cpp::il2cpp_type* get_global_type();

        void stop();

    private:
        static inline il2cpp::il2cpp_type* type_ = nullptr;

        using stop_t = void(*)(animation*);
        inline static stop_t stop_func_ = nullptr;
    };
}
