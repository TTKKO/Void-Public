/*
 *		assembler/vrc/playermanager.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of VRChat's PlayerManager class
 */

#pragma once
#include "../il2cpp/il2cpp.hpp"

namespace assembler::vrc
{
    struct player;

    struct player_manager
    {
        static player* get_player(il2cpp::il2cpp_string* user_id);
        static player* get_player(std::string_view user_id);
        static player* get_player(std::int32_t photon_id);
        static il2cpp::il2cpp_array* get_players();
        static float get_distance_between(player* from, player* to);
    };
}
