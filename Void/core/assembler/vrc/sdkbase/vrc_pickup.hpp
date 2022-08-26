/*
 *		assembler/vrc/sdkbase/vrc_pickup.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of VRChat's VRC_Pickup class
 */
#ifndef VRC_PICKUP_HPP
#define VRC_PICKUP_HPP

#pragma once

#include "../../unityengine/component.hpp"

namespace assembler::vrc::sdk_base
{
    struct vrc_pickup : unity_engine::component
    {
        static il2cpp::il2cpp_type* get_global_type();

        void set_pickupable(bool value);
        void set_disallowtheft(bool value);
        void set_proximity(float value);
        void set_allow_manipulation_when_equipped(bool value);

    private:
        static inline il2cpp::il2cpp_type* type_ = nullptr;
    };
}

#endif
