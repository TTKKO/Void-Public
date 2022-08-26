/*
 *		assembler/unityengine/boxcollider.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's BoxCollider class
 */

#pragma once
#include "../unityengine/collider.hpp"

namespace assembler::unity_engine
{
    struct boxcollider : collider
    {
        static il2cpp::il2cpp_type* get_global_type();

        sdk::vector get_size();
        void set_size(const sdk::vector& size);

    private:
        static inline il2cpp::il2cpp_type* type_ = nullptr;

        using get_size_t = void(*)(boxcollider*, sdk::vector*);
        inline static get_size_t get_size_func_ = nullptr;

        using set_size_t = void(*)(boxcollider*, const sdk::vector&);
        inline static set_size_t set_size_func_ = nullptr;
    };
}
