/*
 *		assembler/vrc/player.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of VRChat's Player class
 */

#pragma once
#include <iostream>
#include "../common.hpp"
#include "../unityengine/transform.hpp"
#include "../unityengine/component.hpp"

namespace assembler
{
    struct vrc_player;
}

namespace assembler::vrc::sdk_base
{
    struct vrc_player_api;
}

namespace assembler::vrc::core
{
    struct api_user;
}

namespace assembler::vrc
{
    struct player : unity_engine::component
    {
        sdk_base::vrc_player_api* get_vrc_player_api();
        std::string to_string();
        static player* get_current();
        std::int32_t get_photon_id();
        core::api_user* get_api_user();
        vrc_player* get_vrc_player();
    };
}
