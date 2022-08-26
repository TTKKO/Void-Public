/*
 *		assembly-csharp/buttonclickedevent.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's VRChat ButtonClickedEvent class replication
 */
#ifndef BUTTONCLICKEDEVENT_HPP
#define BUTTONCLICKEDEVENT_HPP
 /*
  *		assembler/assembly-csharp/buttonclickedevent.hpp // @todo: move to unityengine
  *		Void
  *
  *		Copyright © 2021 Azurilex. All rights reserved.
  *		Void's ButtonClickedEvent class replication
  */

#pragma once
#include "ui_manager_impl.hpp"
#include "../unityengine/ui/button.hpp"
#include "../unityengine/events/event.hpp"

namespace assembler::unity_engine::ui
{
    struct button_clicked_event : events::unity_event
    {
        static button_clicked_event* ctor();
    };
}

#endif
