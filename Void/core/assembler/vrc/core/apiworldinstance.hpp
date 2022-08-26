/*
 *		assembler/vrc/core/apiworldinstance.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of VRChat's ApiWorldInstance class
 */

#pragma once
#include "api_model.hpp"

namespace assembler::vrc::core
{

	struct vrc_core_apiworldinstance_fields : vrc_core_api_model_fields {
		il2cpp::il2cpp_string* name;
		il2cpp::il2cpp_string* short_name;
		il2cpp::il2cpp_string* instance_id;
		il2cpp::il2cpp_string* world_id;
		struct VRC_Core_ApiWorld_o* world;
		std::int32_t type;
		il2cpp::il2cpp_string* owner_id;
		struct system_collections_generic_list_string_o* tags;
		std::int32_t count;
		std::int32_t capacity;
		struct System_Collections_Generic_Dictionary_string__int__o* platforms;
		il2cpp::il2cpp_string* nonce;
		il2cpp::il2cpp_string* client_version;
		std::int32_t region;
		bool active;
		bool permanent;
		struct System_Collections_Generic_List_APIUser__o* users;
	};
	struct vrc_core_apiworldinstance_rgctxs {
	};
	struct vrc_core_apiworldinstance_vtable {
		il2cpp::virtual_invoke_data _0_Equals;
		il2cpp::virtual_invoke_data _1_Finalize;
		il2cpp::virtual_invoke_data _2_GetHashCode;
		il2cpp::virtual_invoke_data _3_ToString;
		il2cpp::virtual_invoke_data _4_unknown;
		il2cpp::virtual_invoke_data _5_unknown;
		il2cpp::virtual_invoke_data _6_unknown;
		il2cpp::virtual_invoke_data _7_Clone;
		il2cpp::virtual_invoke_data _8_get_id;
		il2cpp::virtual_invoke_data _9_set_id;
		il2cpp::virtual_invoke_data _10_ShouldCache;
		il2cpp::virtual_invoke_data _11_ShouldClearOnLevelLoad;
		il2cpp::virtual_invoke_data _12_GetLifeSpan;
		il2cpp::virtual_invoke_data _13_Save;
		il2cpp::virtual_invoke_data _14_SetApiFieldsFromJson;
		il2cpp::virtual_invoke_data _15_ReadField;
		il2cpp::virtual_invoke_data _16_WriteField;
	};
	struct vrc_core_apiworldinstance_c {
		il2cpp::il2cpp_class_1 _1;
		struct vrc_core_apiworldinstance_static_fields* static_fields;
		vrc_core_apiworldinstance_rgctxs* rgctx_data;
		il2cpp::il2cpp_class_2 _2;
		vrc_core_apiworldinstance_vtable vtable;
	};
	struct api_world_instance {
		vrc_core_apiworldinstance_c* klass;
		void* monitor;
		vrc_core_apiworldinstance_fields fields;

#if LVM_TESTING == 1
		static bool initialize_lvm(sol::state& lua);
#endif

		std::string get_access_type() const;
		std::string get_instance_id() const;
		std::string get_world_id() const;
	};
	struct vrc_core_apiworldinstance_static_fields {
	};
}
