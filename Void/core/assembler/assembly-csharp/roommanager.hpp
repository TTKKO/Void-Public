/*
 *		assembler/assembly-csharp/roommanager.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's VRChat RoomManager class replication
 */

#pragma once
#include "../unityengine/component.hpp"

namespace assembler
{
	namespace vrc::core
    {
        struct api_world_instance;
        struct api_world;
    }

	struct room_manager_fields : unity_engine::unity_engine_object_fields {
		struct System_Action_o* _k_BackingField;
		System_Action_o* _19_k_BackingField;
	};
	struct room_manager_rgctxs {
	};
	struct room_manager_vtable {
		il2cpp::virtual_invoke_data _0_Equals;
		il2cpp::virtual_invoke_data _1_Finalize;
		il2cpp::virtual_invoke_data _2_GetHashCode;
		il2cpp::virtual_invoke_data _3_ToString;
		il2cpp::virtual_invoke_data _4_;
		il2cpp::virtual_invoke_data _5_;
		il2cpp::virtual_invoke_data _6_;
		il2cpp::virtual_invoke_data _7_;
		il2cpp::virtual_invoke_data _8_;
		il2cpp::virtual_invoke_data _9_;
		il2cpp::virtual_invoke_data _10_;
		il2cpp::virtual_invoke_data _11_;
		il2cpp::virtual_invoke_data _12_;
		il2cpp::virtual_invoke_data _13_;
		il2cpp::virtual_invoke_data _14_;
	};
	struct room_manager_c {
		il2cpp::il2cpp_class_1 _1;
		struct room_manager_static_fields* static_fields;
		room_manager_rgctxs* rgctx_data;
		il2cpp::il2cpp_class_2 _2;
		room_manager_vtable vtable;
	};
	struct room_manager {
		room_manager_c* klass;
		void* monitor;
		room_manager_fields fields;

	private:
		static inline il2cpp::il2cpp_type* type_ = nullptr;
	public:
		static room_manager_c* get_class();
		static il2cpp::il2cpp_type* get_type();
		static room_manager* get_new();
		static std::string get_room_id();
	};
	struct room_manager_static_fields {
		bool random_bool;
		vrc::core::api_world* world;
		vrc::core::api_world_instance* world_instance;
	};
}
