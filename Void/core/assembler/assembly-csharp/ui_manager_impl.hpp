/*
 *		assembler/assembly-csharp/ui_manager_impl.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's VRChat UiManagerImpl class replication
 */

#pragma once
#include "../unityengine/component.hpp"
#include "vrcplayer.hpp"

namespace assembler
{
    struct ui_manager_impl : unity_engine::component
    {
        static ui_manager_impl* instance();
        unity_engine::game_object* get_quickmenu();
        vrc::core::api_user* selected_user();
    };
}

