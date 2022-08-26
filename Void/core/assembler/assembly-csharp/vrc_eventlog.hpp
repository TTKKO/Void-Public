/*
 *		assembler/assembly-csharp/vrc_eventlog.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's VRChat VRCEventLog class replication
 */

#pragma once
#include "vrc_event.hpp"

namespace assembler
{
    struct vrc_eventlog : unity_engine::component
    {
        struct event_log_entry : il2cpp::il2cpp_object
        {
            std::int32_t get_sender_id();
            vrc_event* get_vrc_event();
            std::string get_name();
        };

        void should_process_events(bool toggle);
        vrc_eventreplicator* get_eventreplicator();
        static vrc_eventlog* instance();

    private:
        static il2cpp::field_info* static_instance_;
    };
}
