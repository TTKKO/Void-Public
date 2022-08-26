/*
 *		assembler/assembly-csharp/eventdata.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's VRChat EventData (for photon) class replication
 */

#pragma once
#include "../unityengine/component.hpp"

namespace assembler
{
	struct __declspec(align(8)) exitgames_client_photon_eventdata_fields {
		std::uint8_t code;
		struct ExitGames_Client_Photon_ParameterDictionary_o* parameters;
		std::uint8_t sender_key;
		std::int32_t sender;
		std::uint8_t custom_data_key;
		il2cpp::il2cpp_object* custom_data;
	};
	struct exitgames_client_photon_eventdata_rgctxs {
	};
	struct exitgames_client_photon_eventdata_vtable {
		il2cpp::virtual_invoke_data _0_Equals;
		il2cpp::virtual_invoke_data _1_Finalize;
		il2cpp::virtual_invoke_data _2_GetHashCode;
		il2cpp::virtual_invoke_data _3_ToString;
	};
	struct exitgames_client_photon_eventdata_c {
		il2cpp::il2cpp_class_1 _1;
		struct exitgames_client_photon_eventdata_static_fields* static_fields;
		exitgames_client_photon_eventdata_rgctxs* rgctx_data;
		il2cpp::il2cpp_class_2 _2;
		exitgames_client_photon_eventdata_vtable vtable;
	};
	struct event_data {
		exitgames_client_photon_eventdata_c* klass;
		void* monitor;
		exitgames_client_photon_eventdata_fields fields;

		il2cpp::il2cpp_object* get_custom_data();
		il2cpp::il2cpp_object* get_item(std::uint8_t key);
	};
	struct exitgames_client_photon_eventdata_static_fields {
	};
}

