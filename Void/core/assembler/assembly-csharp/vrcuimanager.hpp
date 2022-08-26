/*
 *		assembler/assembly-csharp/vrcuimanager.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's VRChat VRCUiManager class replication
 */

#pragma once
#include "../unityengine/component.hpp"

namespace assembler
{
    struct vrc_ui_manager : unity_engine::component
    {
        static vrc_ui_manager* instance();
        void hud_msg(std::string_view text);
    };
}

