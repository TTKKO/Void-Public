/*
 *		assembler/unityengine/xrdevice.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's XRDevice class
 */

#pragma once
#include "../il2cpp/il2cpp.hpp"

namespace assembler::unity_engine
{
    struct xrdevice
    {
        static bool get_is_present();
        static il2cpp::il2cpp_string* get_model();

    private:
        using get_is_present_t = bool(*)();
        inline static get_is_present_t get_is_present_func_ = nullptr;

        using get_model_t = il2cpp::il2cpp_string* (*)();
        inline static get_model_t get_model_func_ = nullptr;
    };
}
