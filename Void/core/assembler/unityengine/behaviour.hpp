/*
 *		assembler/unityengine/behaviour.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's Behaviour class
 */

#pragma once
#include "../unityengine/component.hpp"

namespace assembler::unity_engine
{
    struct behaviour : component
    {
        void set_enabled(bool val);
    private:
        using set_enabled_t = void (*)(behaviour*, bool);
        inline static set_enabled_t set_enabled_func_ = nullptr;
    };
}

