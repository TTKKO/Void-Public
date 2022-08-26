/*
 *		assembler/assembly-csharp/assetbundle_download_manager.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's AssetBundleDownloadManager class replication
 */

#pragma once
#include "system/collections/queue.hpp"
#include "system/collections/dictionary.hpp"
#include "../unityengine/behaviour.hpp"
#include "../unityengine/assetbundle.hpp"

namespace assembler
{
	struct assetbundle_download_manager_fields : unity_engine::unity_engine_object_fields {
		il2cpp::il2cpp_object* ptr1;
		system_replication::collections::dictionary* ptr2;
		system_replication::collections::queue* queue_1;
		il2cpp::il2cpp_object* ptr3;
		system_replication::collections::queue* queue_2;
	};

	struct assetbundle_download_manager_vtable {
		il2cpp::virtual_invoke_data _0_Equals;
		il2cpp::virtual_invoke_data _1_Finalize;
		il2cpp::virtual_invoke_data _2_GetHashCode;
		il2cpp::virtual_invoke_data _3_ToString;
	};
	struct assetbundle_download_manager_class {
		il2cpp::il2cpp_class_1 _1;
		struct assetbundle_download_manager_static_fields* static_fields;
		struct assetbundle_download_manager_rgctxs* rgctx_data;
		il2cpp::il2cpp_class_2 _2;
		assetbundle_download_manager_vtable vtable;
	};

	struct assetbundle_download_manager
	{
		assetbundle_download_manager_class* klass;
		void* monitor;
		assetbundle_download_manager_fields fields;

		static assetbundle_download_manager* instance();
		std::pair<system_replication::collections::queue*, system_replication::collections::queue*> get_queues();

	private:
		static inline il2cpp::il2cpp_type* abdm_type_ = nullptr;
	};

	struct assetbundle_download_manager_static_fields
	{
		assetbundle_download_manager* instance;
	};

	struct assetbundle_download : il2cpp::il2cpp_object
	{
		std::string get_id();
		unity_engine::assetbundle* get_assetbundle();
		unity_engine::game_object* get_game_object();
	};
}
