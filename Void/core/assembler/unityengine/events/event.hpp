/*
 *		assembler/unityengine/events/event.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's Event class
 */

#pragma once
#include "../component.hpp"

namespace assembler::unity_engine::events
{
    struct unity_action;

    struct unity_event : component
    {
        void add_listener(unity_action* call);
    };
}
