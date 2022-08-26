/*
 *		assembler/vrc/core/pipeline_manager.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of VRChat's PipelineManager class
 */

#pragma once
#include "../../common.hpp"

namespace assembler::vrc::core
{
    struct api_user;

	struct vrc_core_pipelinemanager_fields : unity_engine::unity_engine_object_fields {
		bool launched_from_sdk_pipeline;
		bool completed_sdk_pipeline;
		il2cpp::il2cpp_string* blueprint_id;
		api_user* user;
		std::int32_t content_type;
		il2cpp::il2cpp_string* asset_bundle_unity_version;
		std::int32_t fallback_status;
		std::int32_t owned;
	};
	struct vrc_core_pipelinemanager_rgctxs {
	};
	struct vrc_core_pipelinemanager_vtable {
		il2cpp::virtual_invoke_data _0_Equals;
		il2cpp::virtual_invoke_data _1_Finalize;
		il2cpp::virtual_invoke_data _2_GetHashCode;
		il2cpp::virtual_invoke_data _3_ToString;
	};
	struct vrc_core_pipelinemanager_c {
		il2cpp::il2cpp_class_1 _1;
		struct vrc_core_pipelinemanager_static_fields* static_fields;
		vrc_core_pipelinemanager_rgctxs* rgctx_data;
		il2cpp::il2cpp_class_2 _2;
		vrc_core_pipelinemanager_vtable vtable;
	};
	struct pipeline_manager {
		vrc_core_pipelinemanager_c* klass;
		void* monitor;
		vrc_core_pipelinemanager_fields fields;

		_NODISCARD std::string get_blueprint_id() const;
		_NODISCARD std::string get_assetbundle_version() const;
		_NODISCARD api_user* get_api_user() const;
	};
	struct vrc_core_pipelinemanager_static_fields {
	};
}
