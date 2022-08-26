/*
 *		assembler/mono/structures/structures.h
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Mono's structures
 */


#pragma once
#include <cmath>
#include <windows.h>

namespace assembler::mono
{
	struct mono_string;
	using mono_image_open_status_t = enum
	{
		MONO_IMAGE_OK,
		MONO_IMAGE_ERROR_ERRNO,
		MONO_IMAGE_MISSING_ASSEMBLYREF,
		MONO_IMAGE_IMAGE_INVALID
	};

	struct mono_image
	{
		int ref_count;
		void* raw_data_handle;
		char* raw_data;
		uint32_t raw_data_len;
		uint8_t raw_buffer_used : 1;
		uint8_t raw_data_allocated : 1;
		uint8_t fileio_used : 1;
#ifdef _WIN32
		// Module was loaded using LoadLibrary.
		uint8_t is_module_handle : 1;
		// Module entry point is _CorDllMain.
		uint8_t has_entry_point : 1;
#endif
	};

	struct gslist
	{
		void* data;
		gslist* next;
	};

	struct mono_assembly_name {
		const char* name;
		const char* culture;
		const char* hash_value;
		const std::uint8_t* public_key;

		std::uint8_t public_key_token[17];
		uint32_t hash_alg;
		uint32_t hash_len;
		uint32_t flags;
		uint16_t major, minor, build, revision, arch;

		bool without_version;
		bool without_culture;
		bool without_public_key_token;
	};

	struct mono_assembly
	{
		std::uint32_t ref_count; /* use atomic operations only */
		char* basedir;
		mono_assembly_name aname;
		mono_image* image;
	};

	struct mono_domain
	{
		std::uint8_t			 shit[192];
		std::int32_t             shadow_serial;
		unsigned char			 inet_family_hint; // used in socket-io.c as a cache
		gslist*					domain_assemblies;
		mono_assembly* entry_assembly;
		char* friendly_name;
	};

	constexpr int a = sizeof(mono_domain);

	struct mono_class
	{
	};

	struct mono_desc
	{
	};

	struct mono_method
	{
	};

	struct mono_object
	{
	};

	struct mono_string
	{
		mono_object obj;
		int32_t length;
		wchar_t *chars;
	};

	using mono_handle_t = struct mono_handle_t
	{
	};
}
