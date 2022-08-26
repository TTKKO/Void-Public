/*
 *		assembler/assembly-csharp/toggleclickedevent.hpp // @todo: move to unityengine
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's VRChat ToggleClickedEvent class replication
 */

#pragma once
#include "ui_manager_impl.hpp"
#include "../unityengine/ui/toggle.hpp"
#include "../unityengine/events/event.hpp"

namespace assembler::unity_engine::ui
{
    struct toggle_clicked_event : events::unity_event
    {
        static toggle_clicked_event* ctor();
    };
}

