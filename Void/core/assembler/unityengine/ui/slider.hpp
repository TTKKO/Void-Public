/*
 *		assembler/unityengine/ui/slider.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's Unity Slider class replication
 */

#pragma once
#include "selectable.hpp"
#include "../../../sdk/datatypes/color.h"

namespace assembler::unity_engine::ui
{
    struct slider_clicked_event;

    struct slider : selectable
    {
        slider_clicked_event* get_on_slide();
        void set_on_slide(slider_clicked_event* value);
        float get_value();
        void set_value(float value);
    };
}
