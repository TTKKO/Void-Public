/*
 *		assembler/vrc/core/apiuser.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of VRChat's APIUser class
 */

#pragma once
#include "api_model.hpp"

namespace assembler::system_replication::collections
{
	struct hashtable;
}

namespace assembler::vrc::core
{
	struct __declspec(align(8)) system_collections_generic_list_string_fields {
		il2cpp::il2cpp_array* _items;
		std::int32_t _size;
		std::int32_t _version;
		il2cpp::il2cpp_object* _syncRoot;
	};

	struct system_collections_generic_list_string_rgctxs {
	};

	struct system_collections_generic_list_string_vtable {
		il2cpp::virtual_invoke_data _0_Equals;
		il2cpp::virtual_invoke_data _1_Finalize;
		il2cpp::virtual_invoke_data _2_GetHashCode;
		il2cpp::virtual_invoke_data _3_ToString;
		il2cpp::virtual_invoke_data _4_unknown;
		il2cpp::virtual_invoke_data _5_set_Item;
		il2cpp::virtual_invoke_data _6_IndexOf;
		il2cpp::virtual_invoke_data _7_Insert;
		il2cpp::virtual_invoke_data _8_unknown;
		il2cpp::virtual_invoke_data _9_unknown;
		il2cpp::virtual_invoke_data _10_System_Collections_Generic_ICollection_T_get_IsReadOnly;
		il2cpp::virtual_invoke_data _11_Add;
		il2cpp::virtual_invoke_data _12_unknown;
		il2cpp::virtual_invoke_data _13_Contains;
		il2cpp::virtual_invoke_data _14_CopyTo;
		il2cpp::virtual_invoke_data _15_Remove;
		il2cpp::virtual_invoke_data _16_System_Collections_Generic_IEnumerable_T__GetEnumerator;
		il2cpp::virtual_invoke_data _17_System_Collections_IEnumerable_GetEnumerator;
		il2cpp::virtual_invoke_data _18_System_Collections_IList_get_Item;
		il2cpp::virtual_invoke_data _19_System_Collections_IList_set_Item;
		il2cpp::virtual_invoke_data _20_System_Collections_IList_Add;
		il2cpp::virtual_invoke_data _21_System_Collections_IList_Contains;
		il2cpp::virtual_invoke_data _22_Clear;
		il2cpp::virtual_invoke_data _23_System_Collections_IList_get_IsReadOnly;
		il2cpp::virtual_invoke_data _24_System_Collections_IList_get_IsFixedSize;
		il2cpp::virtual_invoke_data _25_System_Collections_IList_IndexOf;
		il2cpp::virtual_invoke_data _26_System_Collections_IList_Insert;
		il2cpp::virtual_invoke_data _27_System_Collections_IList_Remove;
		il2cpp::virtual_invoke_data _28_RemoveAt;
		il2cpp::virtual_invoke_data _29_System_Collections_ICollection_CopyTo;
		il2cpp::virtual_invoke_data _30_unknown;
		il2cpp::virtual_invoke_data _31_System_Collections_ICollection_get_SyncRoot;
		il2cpp::virtual_invoke_data _32_System_Collections_ICollection_get_IsSynchronized;
		il2cpp::virtual_invoke_data _33_get_Item;
		il2cpp::virtual_invoke_data _34_get_Count;
	};

	struct system_collections_generic_list_string_c {
		il2cpp::il2cpp_class_1 _1;
		struct system_collections_generic_list_string_static_fields* static_fields;
		system_collections_generic_list_string_rgctxs* rgctx_data;
		il2cpp::il2cpp_class_2 _2;
		system_collections_generic_list_string_vtable vtable;
	};
	struct system_collections_generic_list_string_o {
		system_collections_generic_list_string_c* klass;
		void* monitor;
		system_collections_generic_list_string_fields fields;
	};
	struct system_collections_generic_list_string_static_fields {
		il2cpp::il2cpp_array* empty_array;
	};

	struct vrc_core_apiuser_fields : vrc_core_api_model_fields
	{
		il2cpp::il2cpp_string* blob;
		il2cpp::il2cpp_string* display_name;
		il2cpp::il2cpp_string* username;
		il2cpp::il2cpp_string* bio;
		system_collections_generic_list_string_o* bio_links;
		il2cpp::il2cpp_string* location;
		il2cpp::il2cpp_string* avatar_id;
		il2cpp::il2cpp_string* fallback_id;
		bool has_email;
		bool has_birthday;
		bool is_friend;
		il2cpp::il2cpp_string* friend_key;
		il2cpp::il2cpp_string* friend_request_status;
		il2cpp::il2cpp_string* last_login;
		il2cpp::il2cpp_string* date_joined;
		std::int32_t developer_type;
		struct System_Collections_Generic_List_VRCEvent__o* events;
		std::int32_t accepted_tos_version;
		il2cpp::il2cpp_string* current_avatar_image_url;
		il2cpp::il2cpp_string* current_avatar_thumbnail_image_url;
		il2cpp::il2cpp_string* auth_token;
		bool email_verified;
		bool has_pending_email;
		il2cpp::il2cpp_string* obfuscated_pending_email;
		system_collections_generic_list_string_o* friend_i_ds;
		il2cpp::il2cpp_string* current_avatar_asset_url;
		struct System_Collections_Generic_Dictionary_string__object__o* steam_details;
		il2cpp::il2cpp_string* world_id;
		il2cpp::il2cpp_string* instance_id;
		il2cpp::il2cpp_string* obfuscated_email;
		bool unsubscribe;
		bool has_logged_in_from_client;
		system_collections_generic_list_string_o* past_display_names;
		il2cpp::il2cpp_string* home_location;
		system_collections_generic_list_string_o* tags;
		il2cpp::il2cpp_string* status;
		il2cpp::il2cpp_string* status_description;
		system_collections_generic_list_string_o* status_history;
		il2cpp::il2cpp_string* state;
		bool allow_avatar_copying;
		il2cpp::il2cpp_string* user_icon;
		il2cpp::il2cpp_string* profile_pic_override;
		il2cpp::il2cpp_string* last_platform;
		bool two_factor_auth_enabled;
		System_Collections_Generic_Dictionary_string__object__o* two_factor_auth_methods;
		struct System_Collections_Generic_Dictionary_string__string__o* language_tags_dictionary;
		system_collections_generic_list_string_o* languages_display_names;
		system_collections_generic_list_string_o* languages_short_names;
	};

	struct vrc_core_apiuser_vtable
	{
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

	struct vrc_core_apiuser_c
	{
		il2cpp::il2cpp_class_1 _1;
		struct vrc_core_apiuser_static_fields* static_fields;
		struct vrc_core_apiuser_rgctxs* rgctx_data;
		il2cpp::il2cpp_class_2 _2;
		vrc_core_apiuser_vtable vtable;
	};

	struct api_user
	{
		vrc_core_apiuser_c* klass;
		void* monitor;
		vrc_core_apiuser_fields fields;

		_NODISCARD std::string get_status() const; //private string <status>k__BackingField; // 0x118
		_NODISCARD std::string get_status_description() const; //private string <statusDescription>k__BackingField; // 0x120
		void set_status_description(std::string_view argument);

#if LVM_TESTING == 1
		static bool initialize_lvm(sol::state& lua);
#endif
		static bool is_friends_with(il2cpp::il2cpp_string* user_id);
		static bool is_friends_with(std::string_view user_id); // isFriendsWith

		_NODISCARD il2cpp::il2cpp_array* get_tags() const;
		bool has_tag(std::string_view user_id); // hasTag(string tag)
		static api_user* get_current(); // public static APIUser get_CurrentUser

		_NODISCARD il2cpp::il2cpp_array* get_past_displaynames() const;

		_NODISCARD std::string get_usericon() const;
		_NODISCARD std::string display_name() const;
		void set_display_name(std::string_view name);
		_NODISCARD std::string get_id() const;
		_NODISCARD std::string get_vrca() const;
		_NODISCARD std::string get_location() const;
		_NODISCARD std::string get_world_id() const;
		_NODISCARD std::string get_instance_id() const;

		static void send_friend_request(api_user* user);
		static il2cpp::il2cpp_array* get_friends();
		static api_user* ctor();
		static il2cpp::il2cpp_type* get_global_type();

		_NODISCARD bool get_is_on_mobile() const;

	private:
		static inline il2cpp::il2cpp_type* type_ = nullptr;
		static inline vrc_core_apiuser_c* global_class_ = nullptr;
	};

	struct vrc_core_apiuser_static_fields
	{
		system_replication::collections::hashtable* status_default_descriptions;
		api_user* current_user;
	};
}
