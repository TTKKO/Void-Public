/*
 *		assembler/il2cpp/structures/structures.h
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of IL2CPP's structures
 */

// ReSharper disable CppInconsistentNaming
#pragma once
#include <cmath>

namespace assembler::il2cpp
{
	using il2cpp_method_pointer = void(*)();

	struct method_info;

	typedef void* (*invoker_method)(il2cpp_method_pointer, const method_info*, void*, void**);

	typedef std::int32_t type_definition_index;
	typedef std::int32_t custom_attribute_index;
	typedef std::int32_t method_index;
	typedef std::int32_t type_index;
	typedef std::int32_t typedefinition_index;

	struct virtual_invoke_data
	{
		il2cpp_method_pointer methodPtr;
		const method_info* method;
	};

	struct il2cpp_type
	{
		void* data;
		unsigned int bits;
	};

	struct il2cpp_class;

	struct il2cpp_object
	{
		il2cpp_class* klass;
		void* monitor;
	};

	typedef std::size_t il2cpp_array_size_t;
	typedef std::int32_t il2cpp_array_lower_bound_t;

	struct il2cpp_array_bounds
	{
		il2cpp_array_size_t length;
		il2cpp_array_lower_bound_t lower_bound;
	};

	struct il2cpp_array : il2cpp_object
	{
		il2cpp_array_bounds* bounds;
		il2cpp_array_size_t max_length;
	};

	union il2cpp_rgctx_data
	{
		void* rgctxDataDummy;
		const method_info* method;
		const il2cpp_type* type;
		il2cpp_class* klass;
	};

	struct property_info
	{
		il2cpp_class* parent;
		const char* name;
		const method_info* get;
		const method_info* set;
		std::uint32_t attrs;
		std::uint32_t token;
	};

	struct field_info
	{
		const char* name;
		const il2cpp_type* type;
		il2cpp_class* parent;
		std::int32_t offset;
		std::uint32_t token;
	};

	struct method_info
	{
		il2cpp_method_pointer methodPointer;
		void* invoker_method;
		const char* name;
		il2cpp_class* klass;
		const il2cpp_type* return_type;
		const void* parameters;

		union
		{
			const il2cpp_rgctx_data* rgctx_data;
			const void* methodDefinition;
		};

		union
		{
			const void* genericMethod;
			const void* genericContainer;
		};

		std::uint32_t token;
		std::uint16_t flags;
		std::uint16_t iflags;
		std::uint16_t slot;
		std::uint8_t parameters_count;
		std::uint8_t bitflags;
	};

	using il2cpp_char = wchar_t;

	struct il2cpp_string : il2cpp_object
	{
		std::int32_t length;
		il2cpp_char chars[32];
	};

	typedef std::int32_t il2cpp_hresult_t;

	struct il2cpp_exception
	{
		il2cpp_object object;
		il2cpp_string* className;
		il2cpp_string* message;
		il2cpp_object* _data;
		il2cpp_exception* inner_ex;
		il2cpp_string* _helpURL;
		il2cpp_array* trace_ips;
		il2cpp_string* stack_trace;
		il2cpp_string* remote_stack_trace;
		int remote_stack_index;
		il2cpp_object* _dynamicMethods;
		il2cpp_hresult_t hresult;
		il2cpp_string* source;
		il2cpp_object* safeSerializationManager;
		il2cpp_array* captured_traces;
		il2cpp_array* native_trace_ips;
	};

	struct il2cpp_assembly_name
	{
		const char* name;
		const char* culture;
		const std::uint8_t* public_key;
		std::uint32_t hash_alg;
		std::int32_t hash_len;
		std::uint32_t flags;
		std::int32_t major;
		std::int32_t minor;
		std::int32_t build;
		std::int32_t revision;
		std::uint8_t public_key_token[8];
	};

	struct il2cpp_range
	{
		std::int32_t start;
		std::int32_t length;
	};

	struct il2cpp_token_range_pair
	{
		std::uint32_t token;
		il2cpp_range range;
	};

	union il2cpp_rgctx_definition_data
	{
		std::int32_t rgctxDataDummy;
		method_index methodIndex;
		type_index typeIndex;
	};

	enum il2cpp_rgctx_datatype 
	{
		IL2CPP_RGCTX_DATA_INVALID,
		IL2CPP_RGCTX_DATA_TYPE,
		IL2CPP_RGCTX_DATA_CLASS,
		IL2CPP_RGCTX_DATA_METHOD,
		IL2CPP_RGCTX_DATA_ARRAY,
	};

	struct il2cpp_rgctx_definition
	{
		il2cpp_rgctx_datatype type;
		il2cpp_rgctx_definition_data data;
	};

	struct il2cpp_token_index_method_tuple
	{
		std::uint32_t token;
		std::int32_t index;
		void** method;
		std::uint32_t genericMethodIndex;
	};

	struct il2cpp_token_adjustor_thunkpair
	{
		std::uint32_t token;
		il2cpp_method_pointer adjustorThunk;
	};

	struct il2cpp_method_exceution_contextinfo
	{
		type_index typeIndex;
		std::int32_t nameIndex;
		std::int32_t scopeIndex;
	};

	struct il2cpp_method_exceution_contextinfo_index
	{
		std::int32_t startIndex;
		std::int32_t count;
	};

	struct il2cpp_method_scope
	{
		std::int32_t startOffset;
		std::int32_t endOffset;
	};

	struct il2cpp_method_header_info
	{
		std::int32_t code_size;
		std::int32_t startScope;
		std::int32_t numScopes;
	};

	enum sequence_point_kind
	{
		kSequencePointKind_Normal,
		kSequencePointKind_StepOut
	};

	struct il2cpp_sequence_point_source_file
	{
		const char* file;
		std::uint8_t hash[16];
	};

	struct il2cpp_sequence_point
	{
		method_index methodDefinitionIndex;
		std::int32_t sourceFileIndex;
		std::int32_t lineStart, lineEnd;
		std::int32_t columnStart, columnEnd;
		std::int32_t ilOffset;
		sequence_point_kind kind;
		std::int32_t isActive;
		std::int32_t id;
	};

	struct il2cpp_catch_point
	{
		method_index methodDefinitionIndex;
		type_index catchTypeIndex;
		std::int32_t ilOffset;
		std::int32_t tryId;
		std::int32_t parentTryId;
	};

	struct il2cpp_type_source_file_pair
	{
		typedefinition_index klassIndex;
		std::int32_t sourceFileIndex;
	};

	struct il2cpp_debugger_metadata_registration
	{
		il2cpp_method_exceution_contextinfo* methodExecutionContextInfos;
		il2cpp_method_exceution_contextinfo_index* methodExecutionContextInfoIndexes;
		il2cpp_method_scope* methodScopes;
		il2cpp_method_header_info* methodHeaderInfos;
		il2cpp_sequence_point_source_file* sequencePointSourceFiles;
		std::int32_t numSequencePoints;
		il2cpp_sequence_point* sequencePoints;
		std::int32_t numCatchPoints;
		il2cpp_catch_point* catchPoints;
		std::int32_t numTypeSourceFileEntries;
		il2cpp_type_source_file_pair* typeSourceFiles;
		const char** methodExecutionContextInfoStrings;
	};

	struct il2cpp_code_gen_module
	{
		const char* moduleName;
		const std::uint32_t methodPointerCount;
		const il2cpp_method_pointer* methodPointers;
		const std::uint32_t adjustorThunkCount;
		const il2cpp_token_adjustor_thunkpair* adjustorThunks;
		const std::int32_t* invokerIndices;
		const std::uint32_t reversePInvokeWrapperCount;
		const il2cpp_token_index_method_tuple* reversePInvokeWrapperIndices;
		const std::uint32_t rgctxRangesCount;
		const il2cpp_token_range_pair* rgctxRanges;
		const std::uint32_t rgctxsCount;
		const il2cpp_rgctx_definition* rgctxs;
		const il2cpp_debugger_metadata_registration* debuggerMetadata;
	};

	struct il2cpp_assembly;

	struct il2cpp_name_to_type_definition_index_hashtable;

	struct il2cpp_image
	{
		const char* name;
		const char* nameNoExt;
		il2cpp_assembly* assembly;
		type_definition_index typeStart;
		std::uint32_t typeCount;
		type_definition_index exportedTypeStart;
		std::uint32_t exportedTypeCount;
		custom_attribute_index customAttributeStart;
		std::uint32_t customAttributeCount;
		method_index entryPointIndex;
		il2cpp_name_to_type_definition_index_hashtable* nameToClassHashTable;
		const il2cpp_code_gen_module* codeGenModule;
		std::uint32_t token;
		std::uint8_t dynamic;
	};

	struct il2cpp_assembly
	{
		il2cpp_image* image;
		std::uint32_t token;
		std::int32_t referencedAssemblyStart;
		std::int32_t referencedAssemblyCount;
		il2cpp_assembly_name aname;
	};

	struct il2cpp_marshal_by_ref_object
	{
		il2cpp_object obj;
		il2cpp_object* identity;
	};

	struct il2cpp_domain;

	struct il2cpp_app_domain
	{
		il2cpp_marshal_by_ref_object mbr;
		il2cpp_domain* data;
	};

	struct il2cpp_app_domain_setup
	{
		il2cpp_object object;
		il2cpp_string* application_base;
		il2cpp_string* application_name;
		il2cpp_string* cache_path;
		il2cpp_string* configuration_file;
		il2cpp_string* dynamic_base;
		il2cpp_string* license_file;
		il2cpp_string* private_bin_path;
		il2cpp_string* private_bin_path_probe;
		il2cpp_string* shadow_copy_directories;
		il2cpp_string* shadow_copy_files;
		std::uint8_t publisher_policy;
		std::uint8_t path_changed;
		int loader_optimization;
		std::uint8_t disallow_binding_redirects;
		std::uint8_t disallow_code_downloads;
		il2cpp_object* activation_arguments;
		il2cpp_object* domain_initializer;
		il2cpp_object* application_trust;
		il2cpp_array* domain_initializer_args;
		std::uint8_t disallow_appbase_probe;
		il2cpp_array* configuration_bytes;
		il2cpp_array* serialized_non_primitives;
	};

	struct il2cpp_app_context
	{
		il2cpp_object obj;
		std::int32_t domain_id;
		std::int32_t context_id;
		void* static_data;
	};

	struct il2cpp_domain
	{
		il2cpp_app_domain* domain;
		il2cpp_app_domain_setup* setup;
		il2cpp_app_context* default_context;
		const char* friendly_name;
		std::uint32_t domain_id;
		volatile int threadpool_jobs;
		void* agent_info;
	};

	struct il2cpp_internal_thread
	{
		il2cpp_object obj;
		int lock_thread_id;
		void* handle;
		void* native_handle;
		il2cpp_array* cached_culture_info;
		il2cpp_char* name;
		int name_len;
		std::uint32_t state;
		il2cpp_object* abort_exc;
		int abort_state_handle;
		std::uint64_t tid;
		std::intptr_t debugger_thread;
		void** static_data;
		void* runtime_thread_info;
		il2cpp_object* current_appcontext;
		il2cpp_object* root_domain_thread;
		il2cpp_array* _serialized_principal;
		int _serialized_principal_version;
		void* appdomain_refs;
		std::int32_t interruption_requested;
		void* synch_cs;
		std::uint8_t threadpool_thread;
		std::uint8_t thread_interrupt_requested;
		int stack_size;
		std::uint8_t apartment_state;
		int critical_region_level;
		int managed_id;
		std::uint32_t small_id;
		void* manage_callback;
		void* interrupt_on_stop;
		std::intptr_t flags;
		void* thread_pinning_ref;
		void* abort_protected_block_count;
		std::int32_t priority;
		void* owned_mutexes;
		void* suspended;
		std::int32_t self_suspended;
		std::size_t thread_state;
		std::size_t unused2;
		void* last;
	};

	struct il2cpp_reflection_type
	{
		il2cpp_object object;
		const il2cpp_type* type;
	};

	struct il2cpp_reflection_method
	{
		il2cpp_object object;
		const method_info* method;
		il2cpp_string* name;
		il2cpp_reflection_type* reftype;
	};

	struct il2cpp_delegate
	{
		il2cpp_object object;
		il2cpp_method_pointer method_ptr;
		invoker_method invoke_impl;
		il2cpp_object* target;
		const method_info* method;
		void* delegate_trampoline;
		std::intptr_t extraArg;
		std::uint8_t** method_code;
		il2cpp_reflection_method* method_info;
		il2cpp_reflection_method* original_method_info;
		il2cpp_object* data;
		std::uint8_t method_is_virtual;
	};

	struct il2cpp_thread
	{
		il2cpp_object obj;
		il2cpp_internal_thread* internal_thread;
		il2cpp_object* start_obj;
		il2cpp_exception* pending_exception;
		il2cpp_object* principal;
		std::int32_t principal_version;
		il2cpp_delegate* delegate;
		il2cpp_object* executionContext;
		std::uint8_t executionContextBelongsToOuterScope;
	};

	struct il2cpp_class_1
	{
		il2cpp_image* image;
		void* gc_desc;
		const char* name;
		const char* namespaze;
		il2cpp_type byval_arg;
		il2cpp_type this_arg;
		il2cpp_class* element_class;
		il2cpp_class* castClass;
		il2cpp_class* declaringType;
		il2cpp_class* parent;
		void* generic_class;
		void* typeDefinition;
		void* interopData;
		il2cpp_class* klass;
		field_info* fields;
		void* events;
		const property_info** properties;
		const method_info** methods;
		il2cpp_class** nestedTypes;
		il2cpp_class** implementedInterfaces;
		void* interfaceOffsets;
	};

	struct il2cpp_class_2
	{
		il2cpp_class** typeHierarchy;
		void* unity_user_data;
		std::uint32_t initializationExceptionGCHandle;
		std::uint32_t cctor_started;
		std::uint32_t cctor_finished;
		std::size_t cctor_thread;
		std::int32_t genericContainerIndex;
		std::uint32_t instance_size;
		std::uint32_t actualSize;
		std::uint32_t element_size;
		std::int32_t native_size;
		std::uint32_t static_fields_size;
		std::uint32_t thread_static_fields_size;
		std::int32_t thread_static_fields_offset;
		std::uint32_t flags;
		std::uint32_t token;
		std::uint16_t method_count;
		std::uint16_t property_count;
		std::uint16_t field_count;
		std::uint16_t event_count;
		std::uint16_t nested_type_count;
		std::uint16_t vtable_count;
		std::uint16_t interfaces_count;
		std::uint16_t interface_offsets_count;
		std::uint8_t typeHierarchyDepth;
		std::uint8_t genericRecursionDepth;
		std::uint8_t rank;
		std::uint8_t minimumAlignment;
		std::uint8_t naturalAligment;
		std::uint8_t packingSize;
		std::uint8_t bitflags1;
		std::uint8_t bitflags2;
	};

	struct il2cpp_class
	{
		il2cpp_class_1 _1;
		void* static_fields;
		il2cpp_rgctx_data* rgctx_data;
		il2cpp_class_2 _2;
		virtual_invoke_data vtable[255];
	};
}
