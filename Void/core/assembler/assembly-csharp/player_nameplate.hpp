/*
 *		assembler/assembly-csharp/player_nameplate.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's VRChat PlayerNameplate class replication
 */

#pragma once
#include "../unityengine/component.hpp"
#include "../tmpro/tmp_text.hpp"

namespace assembler::unity_engine::ui
{
    struct text;
}

namespace assembler
{
    struct player_nameplate : unity_engine::component
    {
        void show();
        void set_bool(bool val);
        tmpro::tmp_text* get_name_text();
    };
}
