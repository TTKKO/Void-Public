/*
 *		assembler/unityengine/xrsettings.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's XRSettings class
 */

#pragma once
#include "../il2cpp/il2cpp.hpp"

namespace assembler::unity_engine
{
    struct xrsettings
    {
        static void load_device_by_name(std::string_view device_name);
        static void load_devices_by_name(il2cpp::il2cpp_array_wrapper<il2cpp::il2cpp_string*>* arr);

        static il2cpp::il2cpp_array_wrapper<il2cpp::il2cpp_string*>* get_supported_devices();

        static void set_enabled(bool value);
        static bool get_enabled();
    private:
        using load_device_by_name_t = void(*)(il2cpp::il2cpp_array*);
        inline static load_device_by_name_t load_device_by_name_func_ = nullptr;

        using get_supported_devices_t = il2cpp::il2cpp_array_wrapper<il2cpp::il2cpp_string*>*(*)();
        inline static get_supported_devices_t get_supported_devices_func_ = nullptr;

        using set_enabled_t = void(*)(bool);
        inline static set_enabled_t set_enabled_func_ = nullptr;

        using get_enabled_t = bool(*)();
        inline static get_enabled_t get_enabled_func_ = nullptr;
    };
}
