/*
 *		assembler/vrc/core/api_model.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of VRChat's ApiModel class
 */

#pragma once
#include "../../common.hpp"

namespace assembler::vrc::core
{
	struct system_date_time_fields {
		std::uint64_t date_data;
	};

	struct system_date_time_o {
		system_date_time_fields fields;
	};

	struct __declspec(align(8)) vrc_core_api_model_fields {
		il2cpp::il2cpp_string* id;
		bool populated;
		il2cpp::il2cpp_string* endpoint;
		std::int32_t supported_platforms;
	};

	struct vrc_core_api_model_rgct_xs {
	};

	struct vrc_core_api_model_v_table {
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

	struct vrc_core_api_model_c {
		il2cpp::il2cpp_class_1 _1;
		struct vrc_core_api_model_static_fields* static_fields;
		vrc_core_api_model_rgct_xs* rgctx_data;
		il2cpp::il2cpp_class_2 _2;
		vrc_core_api_model_v_table vtable;
	};

	struct api_model {
		vrc_core_api_model_c* klass;
		void* monitor;
		vrc_core_api_model_fields fields;
	};

	struct vrc_core_api_model_static_fields {
		struct System_Collections_Generic_Dictionary_string_ApiContainer_o* activeRequests;
		std::int32_t currentRemainingDepth;
		struct System_Collections_Generic_Dictionary_Type_MethodInfo_o* CreateFromJsonCache;
		struct System_Collections_Generic_Dictionary_Type_List_string_o* _requiredProperties;
		struct System_Collections_Generic_Dictionary_Type_List_PropertyInfo_o* _targetProperties;
		struct System_Collections_Generic_Dictionary_Type_Dictionary_string_PropertyInfo_o* foundProperties;
	};
}