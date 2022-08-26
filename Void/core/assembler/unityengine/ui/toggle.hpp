/*
 *		assembler/unityengine/ui/toggle.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's Unity Toggle class replication
 */

#pragma once
#include "selectable.hpp"

namespace assembler::unity_engine::ui
{
    struct toggle_clicked_event;

    struct toggle : selectable
    {
        void set(bool a, bool b = true);
        bool get_state();
        void set_toggle(toggle_clicked_event* data);
        toggle_clicked_event* get_toggle();
    };
}
