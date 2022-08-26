/*
 *		assembler/assembly-csharp/vrcuipopupmanager.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's VRChat VRCUiPopupManager class replication
 */

#pragma once
#include "../unityengine/component.hpp"
#include "system/system_action.hpp"

namespace assembler
{
    struct vrc_ui_popup_manager : unity_engine::component
    {
        static vrc_ui_popup_manager* instance();
        void show_alert(std::string_view str1, std::string_view str2, float delay);
        void show_popup(std::string_view title, std::string_view init_text, std::int32_t input_type, bool is_numeric, std::string_view confirm_text, system_replication::action* on_complete, system_replication::action* on_cancel, std::string_view placeholder_text = xorstr_("Enter text..."), bool close_on_complete = true, system_replication::action* on_popup_shown = nullptr, bool unknown = false, std::int32_t char_limit = 0);
    };
}
