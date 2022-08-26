/*
 *		assembler/vrc/vrcsocialmenu.hpp
 *		Void
 *
 *		Copyright � 2021 Azurilex. All rights reserved.
 *		Void's VRChat quick menu integration
 */

#pragma once
#include "../../globals.hpp"
#include "../unityengine/collider.hpp"
#include "../../../utilities/misc_utils.hpp"
#include "../assembly-csharp/uspeaker.hpp"
#include "../assembly-csharp/roommanager.hpp"
#include "../assembly-csharp/vrcuipage.hpp"
#include "../unityengine/ui/graphic.hpp"
#include <thread>

namespace assembler::vrc_quick_menu
{
    inline il2cpp::il2cpp_type* binding_type = nullptr;
    inline unity_engine::transform* menu_root = nullptr;
    inline unity_engine::transform* safety_button = nullptr;

    bool setup_buttons();
    bool player_list();
    bool init_vr_debug();
    bool restore_vr_debug();
    bool vr_debug_update();
}