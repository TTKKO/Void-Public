/*
 *		assembler/assembly-csharp/vrc_eventreplicator.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's VRChat VRCEventReplicator class replication
 */

#pragma once
#include "../il2cpp/il2cpp.hpp"
#include "../unityengine/component.hpp"

namespace assembler
{
    struct vrc_eventreplicator : unity_engine::component
    {
        void process_events(bool toggle);
    };
}