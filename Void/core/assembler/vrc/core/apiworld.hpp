/*
 *		assembler/vrc/core/apiworld.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of VRChat's ApiWorld class
 */

#pragma once
#include "api_model.hpp"

namespace assembler::vrc::core
{
	struct vrc_core_apiworld_fields : vrc_core_api_model_fields {
		il2cpp::il2cpp_string* name;
		il2cpp::il2cpp_string* image_url;
		il2cpp::il2cpp_string* thumbnail_image_url;
		il2cpp::il2cpp_string* author_name;
		il2cpp::il2cpp_string* release_status;
		std::int32_t capacity;
		std::int32_t occupants;
		std::int32_t public_occupants;
		std::int32_t private_occupants;
		il2cpp::il2cpp_string* author_id;
		system_date_time_o created_at1;
		il2cpp::il2cpp_string* asset_url;
		il2cpp::il2cpp_string* description;
		struct system_collections_generic_list_string_o* tags;
		il2cpp::il2cpp_string* unity_package_url;
		std::int32_t version;
		il2cpp::il2cpp_string* unity_version;
		std::int32_t api_version;
		std::int32_t latest_asset_version;
		system_date_time_o created_at2;
		system_date_time_o updated_at;
		system_date_time_o publication_date;
		il2cpp::il2cpp_string* platform;
		struct System_Collections_Generic_List_ApiWorldInstance__o* m_world_instances;
		struct System_Collections_Generic_Dictionary_string__int__o* instances;
		bool unity_package_updated;
		il2cpp::il2cpp_string* organization;
		bool should_add_to_author;
		il2cpp::il2cpp_string* favorite_id;
		bool is_curated;
	};
	struct vrc_core_apiworld_rgctxs {
	};
	struct vrc_core_apiworld_vtable {
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
		il2cpp::virtual_invoke_data _17_get_name;
	};
	struct vrc_core_apiworld_c {
		il2cpp::il2cpp_class_1 _1;
		struct vrc_core_apiworld_static_fields* static_fields;
		vrc_core_apiworld_rgctxs* rgctx_data;
		il2cpp::il2cpp_class_2 _2;
		vrc_core_apiworld_vtable vtable;
	};
	struct api_world {
		vrc_core_apiworld_c* klass;
		void* monitor;
		vrc_core_apiworld_fields fields;

#if LVM_TESTING == 1
		static bool initialize_lvm(sol::state& lua);
#endif
		static api_world* ctor();
		static il2cpp::il2cpp_type* get_global_type();

		std::string get_name() const;
		std::string asset_url() const;
		std::string get_id() const;
		std::string get_author_name() const;
		int get_capacity() const;

	private:
		static inline il2cpp::il2cpp_type* type_ = nullptr;
	};
	struct vrc_core_apiworld_static_fields {
		struct VRC_Core_AssetVersion_o* version;
		struct VRC_Core_AssetVersion_o* min_loadable_version;
		struct System_Collections_Generic_Dictionary_string__ApiWorld__o* local_worlds;
	};
}
