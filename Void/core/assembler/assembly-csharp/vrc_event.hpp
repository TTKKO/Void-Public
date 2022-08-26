/*
 *		assembler/assembly-csharp/vrc_event.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's VRChat VRCEvent class replication
 */

#pragma once
#include "../il2cpp/il2cpp.hpp"
#include "../unityengine/component.hpp"
#include "vrc_eventreplicator.hpp"

namespace assembler
{
    enum class vrc_event_type : std::int32_t
    {
        mesh_visibility = 0,
        animation_float = 1,
        animation_bool = 2,
        animation_trigger = 3,
        audio_trigger = 4,
        play_animation = 5,
        send_message = 6,
        set_particle_playing = 7,
        teleport_player = 8,
        run_console_command = 9,
        set_game_object_active = 10,
        set_web_panel_uri = 11,
        set_web_panel_volume = 12,
        spawn_object = 13,
        send_rpc = 14,
        activate_custom_trigger = 15,
        destroy_object = 16,
        set_layer = 17,
        set_material = 18,
        add_health = 19,
        add_damage = 20,
        set_component_active = 21,
        animation_int = 22,
        animation_int_add = 24,
        animation_int_subtract = 25,
        animation_int_multiply = 26,
        animation_int_divide = 27,
        add_velocity = 28,
        set_velocity = 29,
        add_angular_velocity = 30,
        set_angular_velocity = 31,
        add_force = 32,
        set_ui_text = 33,
        call_udon_method = 34,
    };

    struct system_nullable_int_fields {
        int32_t value;
        bool has_value;
    };

    struct system_nullable_int_o {
        system_nullable_int_fields fields;
    };

    struct __declspec(align(8)) vrc_sdk_base_vrc_event_handler_vrc_event_fields {
    	il2cpp::il2cpp_string* name;
        vrc_event_type event_type;
    	il2cpp::il2cpp_string* parameter_string;
        std::int32_t parameter_bool_op;
        bool parameter_bool;
        float parameter_float;
        std::int32_t parameter_int;
        unity_engine::game_object* parameter_object;
    	il2cpp::il2cpp_array* parameter_objects;
        il2cpp::il2cpp_array* parameter_bytes;
    	system_nullable_int_o parameter_bytes_version;
        bool take_ownership_of_target;
    };
    struct vrc_sdk_base_vrc_event_handler_vrc_event_rgctxs {
    };
    struct vrc_sdk_base_vrc_event_handler_vrc_event_vtable {
        il2cpp::virtual_invoke_data _0_Equals;
        il2cpp::virtual_invoke_data _1_Finalize;
        il2cpp::virtual_invoke_data _2_GetHashCode;
        il2cpp::virtual_invoke_data _3_ToString;
    };
    struct vrc_sdk_base_vrc_event_handler_vrc_event_c {
        il2cpp::il2cpp_class_1 _1;
        struct vrc_sdk_base_vrc_event_handler_vrc_event_static_fields* static_fields;
        vrc_sdk_base_vrc_event_handler_vrc_event_rgctxs* rgctx_data;
        il2cpp::il2cpp_class_2 _2;
        vrc_sdk_base_vrc_event_handler_vrc_event_vtable vtable;
    };
    struct vrc_event {
        vrc_sdk_base_vrc_event_handler_vrc_event_c* klass;
        void* monitor;
        vrc_sdk_base_vrc_event_handler_vrc_event_fields fields;
    };
    struct vrc_sdk_base_vrc_event_handler_vrc_event_static_fields {
    };
}
