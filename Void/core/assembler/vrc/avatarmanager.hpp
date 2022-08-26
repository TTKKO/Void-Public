#pragma once
#include "core/apiavatar.hpp"

namespace assembler
{
    struct vrc_player;
}

namespace assembler::vrc
{
    struct avatarmanager : unity_engine::object
    {
        core::api_avatar* get_api_avatar();
        vrc_player* get_vrc_player();
    };
}
