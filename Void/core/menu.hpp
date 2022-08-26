/*
 *		hooking/menu.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's ImGUI menu integration
 */
#ifndef MENU_HPP
#define MENU_HPP

#pragma once
#include "lvm/vlvm.hpp"
#include "assembler/mono/mono.hpp"
#include "hooks/helpers/friend_tool.hpp"
#include "assembler/unityengine/character_controller.hpp"
#include <date/date.h>
#include "submenus/sniffer.hpp"

class ctab
{
public:
    const char* sz_name = nullptr;
    std::function<void()> p_render_function = nullptr;
};

namespace menu_window
{
    void main_window(const ImColor& rainbow);

    inline int i_main_tab = 0;
    inline bool is_typing = false;
    inline bool mainmenu_opened = false;
}


#if TEST == 1
namespace dumper_window
{
    void render_window();
    bool dump();

    inline bool mainmenu_opened;
    inline assembler::mono::mono_image* selected = nullptr;
    inline assembler::mono::mono_assembly* selected_asm = nullptr;
    inline std::vector<assembler::mono::mono_image*> modules{};
}
#endif

namespace tabs
{
    // Get
    /* render tabs selection */
    template <std::size_t S> // not a best way, but we stay using cheaper, fixed-sized arrays instead dynamic vectors
    void render(const char* sz_tab_bar, const std::array<ctab, S>& arr_tabs, int* n_current_tab, ImGuiTabBarFlags flags = ImGuiTabBarFlags_NoCloseWithMiddleMouseButton | ImGuiTabBarFlags_NoTooltip);

    // playerlist
    void render_playerlist(const ImGuiIO& io, const ImGuiStyle& style, const ImColor& rainbow);

    // Tabs
    void misc();
    void safety();
    void utilities();
    void games();
#if LVM_TESTING == 1
    void lvm_tab();
#endif
    void configuration();
    void players();

    // Values
    /* current selected sub-tab in visuals tab */
    inline std::vector<assembler::vrc::player*> v_players{};
    inline std::string sz_config_file = {};
    inline assembler::vrc::player* selectedplayer = nullptr;

    inline int i_selected_config = 0;
    inline int i_spoof_tab = 0;
    inline int i_extended_tab = 0;
    inline int i_selected_color = 0;

    inline bool playerlist_active = false;
}

#endif
