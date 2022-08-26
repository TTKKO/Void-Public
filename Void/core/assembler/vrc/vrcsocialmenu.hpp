/*
 *		assembler/vrc/vrcsocialmenu.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's VRChat social menu integration
 */

#pragma once
#include "../unityengine/ui/gridlayoutgroup.hpp"
#include "../unityengine/ui/text.hpp"
#include "../unityengine/image.hpp"
#include "../assembly-csharp/vrcuipage.hpp"
#include "../assembly-csharp/buttonclickedevent.hpp"
#include "../assembly-csharp/userselectionmanager.hpp"
#include "../vrc/sdkbase/vrcplayerapi.hpp"
#include "../../../utilities/button_api.hpp"

namespace assembler::vrc_social_menu
{
    inline std::vector<unity_engine::transform*> social_buttons;

	unity_engine::transform* instantiate_gameobject();
    vrc::core::api_user* current_user();
    unity_engine::transform* create_button(const std::string& btn_text, int btn_x_location, int btn_y_location, const c_inline_detour* btn_action);

    bool setup_buttons();
    void restore();
}

namespace assembler::vrc_player_menu
{
    inline il2cpp::il2cpp_type* selected_user_type = nullptr;
    inline std::vector<std::unique_ptr<single_button>> player_menu_buttons;

    vrc::core::api_user* current_user();
    bool setup_buttons();
    void init_buttons(std::string_view loc);
    void restore();
}
