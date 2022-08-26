/*
 *		assembler/assembly-csharp/moderationmanager.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's VRChat PhotonPlayer class replication
 */

#pragma once
#include "system/collections/dictionary.hpp"


namespace assembler
{
    struct vrc_player;

    struct photon_player : il2cpp::il2cpp_object
    {
        DELCONST(photon_player);

        std::int32_t get_id();
        vrc_player* get_vrc_player();
        system_replication::collections::hashtable* get_hashtable();
    };
}
