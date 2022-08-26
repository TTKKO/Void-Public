/*
 *		assembler/assembly-csharp/slider_slide_event.hpp // @todo: move to unityengine
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's VRChat SliderSlideEvent class replication
 */

#pragma once
#include "../unityengine/ui/slider.hpp"
#include "../unityengine/events/event.hpp"

namespace assembler::unity_engine::ui
{
    struct slider_clicked_event : events::unity_event
    {
        static slider_clicked_event* ctor();
    };
}
