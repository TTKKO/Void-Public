/*
 *		assembler/unityengine/ui/button.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's Unity Button class replication
 */

#pragma once
#include "selectable.hpp"
#include "../../../sdk/datatypes/color.h"

namespace assembler::unity_engine::ui
{
    struct button_clicked_event;

    struct button : selectable
    {
        button_clicked_event* get_on_click();
        void set_on_click(button_clicked_event* value);
        void set_normal_color(const sdk::color& c = {0.f, 0.f, 0.f, 1.f});
    };
}
