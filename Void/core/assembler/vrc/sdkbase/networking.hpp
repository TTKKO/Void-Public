/*
 *		assembler/vrc/sdkbase/networking.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of VRChat's Networking class
 */

#pragma once
#include "../../../sdk/datatypes/vector.h"
#include "../../../sdk/datatypes/quaternion.hpp"
#include "../../unityengine/gameobject.hpp"

// Namespace: VRC.SDKBase
// public static class Networking
namespace assembler::vrc::sdk_base
{
	struct vrc_player_api;

	struct __declspec(align(8)) vrc_sdkbase_networking_fields {
	};
	struct vrc_sdkbase_networking_vtable {
		il2cpp::virtual_invoke_data _0_Equals;
		il2cpp::virtual_invoke_data _1_Finalize;
		il2cpp::virtual_invoke_data _2_GetHashCode;
		il2cpp::virtual_invoke_data _3_ToString;
	};
	struct vrc_sdkbase_networking_c {
		il2cpp::il2cpp_class_1 _1;
		struct vrc_sdkbase_networking_static_fields* static_fields;
		struct vrc_sdkbase_networking_rgctxs* rgctx_data;
		il2cpp::il2cpp_class_2 _2;
		vrc_sdkbase_networking_vtable vtable;
	};
	struct networking {
		vrc_sdkbase_networking_c* klass;
		void* monitor;
		vrc_sdkbase_networking_fields fields;

		static bool go_to_room(std::string_view room_id);
		static unity_engine::game_object* instantiate(std::int32_t broadcast, std::string_view prefab_path_or_dynamic_prefab_name, const sdk::vector& position, const sdk::quaternion& rotation);
		static void rpc(std::int32_t target_clients, unity_engine::game_object* target_object, std::string_view method_name, object_array* parameters);
		static std::int32_t get_server_time_in_milliseconds();
		static il2cpp::il2cpp_array* decode_parameters(il2cpp::il2cpp_array* arr);
		static il2cpp::il2cpp_array* encode_parameters(il2cpp::il2cpp_array* arr);
		static void set_owner(vrc_player_api* player, unity_engine::game_object* object);
		static bool is_owner(unity_engine::game_object* object);
		static vrc_player_api* get_current();

	private:
		static inline vrc_sdkbase_networking_c* global_class_ = nullptr;
		static vrc_sdkbase_networking_c* global_class();
	};
	struct vrc_sdkbase_networking_static_fields {
		il2cpp::il2cpp_object* get_unique_name;
		il2cpp::il2cpp_object* rpc;
		il2cpp::il2cpp_object* rp_cto_player;
		il2cpp::il2cpp_object* is_network_settled;
		il2cpp::il2cpp_object* is_master;
		il2cpp::il2cpp_object* is_suffering;
		il2cpp::il2cpp_object* is_instance_owner;
		il2cpp::il2cpp_object* local_player;
		il2cpp::il2cpp_object* is_owner;
		il2cpp::il2cpp_object* set_owner;
		il2cpp::il2cpp_object* is_object_ready;
		il2cpp::il2cpp_object* instantiate;
		il2cpp::il2cpp_object* get_owner;
		il2cpp::il2cpp_object* parameter_encoder;
		il2cpp::il2cpp_object* parameter_decoder;
		il2cpp::il2cpp_object* destroy;
		il2cpp::il2cpp_object* scene_event_handler;
		il2cpp::il2cpp_object* go_to_room;
		il2cpp::il2cpp_object* get_network_date_time;
		il2cpp::il2cpp_object* get_server_time_in_seconds;
		il2cpp::il2cpp_object* get_server_time_in_milliseconds;
		il2cpp::il2cpp_object* calculate_server_delta_time;
		il2cpp::il2cpp_object* safe_start_coroutine;
		il2cpp::il2cpp_object* get_event_dispatcher;
	};
}
