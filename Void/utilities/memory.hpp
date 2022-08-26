/*
 *		utilities/memory.hpp
 *		Void
 *
 *		Credits: rolraw, azurilex
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Memory related functions
 */

#pragma once

#ifndef MEMORY_HPP
#define MEMORY_HPP

#include "../utilities/utilities.hpp"
#include "memory/pe32.h"

#pragma region memory_modules_definitions
#define ENGINE_DLL				SECSTRW(L"UnityPlayer.dll")
#define CLIENT_DLL				SECSTRW(L"GameAssembly.dll")
#define DX11_DLL				SECSTRW(L"d3d11.dll")
#define MONO_DLL				SECSTRW(L"mono-2.0-bdwgc.dll")
#pragma endregion

#pragma region memory_pattern_convert
#define INRANGE( x, min, max ) ((x) >= (min) && (x) <= (max))
#define GETBITS( x ) ( INRANGE( ( (x)&( ~0x20 ) ), 'A', 'F' ) ? ( ( (x)&( ~0x20 ) ) - 'A' + 0xA) : ( INRANGE( x, '0', '9' ) ? (x) - '0' : 0 ) )
#define GETBYTE( x ) ( GETBITS( (x)[0] ) << 4 | GETBITS( (x)[1] ) )
#pragma endregion

#define UNLINK(x)					\
	(x).Flink->Blink = (x).Blink;	\
	(x).Blink->Flink = (x).Flink;

#define RELINK(x, real)			\
	(x).Flink->Blink = (real);	\
	(x).Blink->Flink = (real);	\
	(real)->Blink = (x).Blink;	\
	(real)->Flink = (x).Flink;

/*
 * singleton implementation
 */
template <typename T>
class c_singleton
{
protected:
	c_singleton()
	{
	}

	~c_singleton()
	{
	}

public:
	c_singleton(const c_singleton&) = delete;
	c_singleton& operator=(const c_singleton&) = delete;

	c_singleton(c_singleton&&) = delete;
	c_singleton& operator=(c_singleton&&) = delete;

	static T& get()
	{
		static T p_instance{};
		return p_instance;
	}
};

/* virtualprotect raii wrapper */
class c_wrapped_protect
{
public:
	c_wrapped_protect(void* p_base_address, const std::size_t u_length, const DWORD dw_flags) : p_base_address_(p_base_address), u_length_(u_length)
	{
		if (!VirtualProtect(p_base_address, u_length, dw_flags, &dw_old_flags_))
			throw std::system_error(GetLastError(), std::system_category(), xorstr_("failed to protect region"));
	}

	~c_wrapped_protect()
	{
		VirtualProtect(p_base_address_, u_length_, dw_old_flags_, &dw_old_flags_);
	}

private:
	void* p_base_address_;
	std::size_t u_length_;
	DWORD dw_old_flags_{};
};

struct find_module_handle
{
	HMODULE mh_module;

	explicit find_module_handle(const HMODULE h_module) : mh_module(h_module)
	{
	}
	bool operator() (UNLINKED_MODULE const& module) const
	{
		return module.hModule == mh_module;
	}
};

namespace memory
{
	inline HMODULE void_handle;
	inline void* game_assembly_handle;
	inline void* unity_player_handle;
	inline void* mono_handle;

	inline std::vector<UNLINKED_MODULE> unlinked_modules;

	void relink_module_to_peb(HMODULE h_module);
	void unlink_module_from_peb(HMODULE h_module);

	std::uint64_t get_total_vmemory_by_proc();
	std::uint64_t get_total_vmemory_used();

	// Convert
	std::vector<std::int32_t> pattern_to_bytes(const char* sz_pattern);
	std::string bytes_to_pattern(const std::uint8_t* arr_bytes, std::size_t u_size);

	void* get_module_base_handle(std::wstring_view sz_module_name);
	void* get_module_base_handle(std::string_view sz_module_name);
	void* get_export_address(const void* p_module_base, std::string_view sz_procedure_name);

	template <typename T>
	constexpr T get_method_unity(const std::uintptr_t offset)
	{
		return reinterpret_cast<T>(static_cast<std::uint8_t*>(unity_player_handle) + offset);
	}

	template <typename T>
	constexpr T get_method(const std::uintptr_t offset)
	{
		return reinterpret_cast<T>(static_cast<std::uint8_t*>(game_assembly_handle) + offset);
	}

	template <typename T, std::size_t S>
	constexpr std::vector<T> get_filled_vector(const T& fill)
	{
		std::vector<T> vec_temp(S);
		std::fill(vec_temp.begin(), vec_temp.begin() + S, fill);
		return vec_temp;
	}

	void write_jmp(std::uint8_t* address, std::uintptr_t jmp_to, std::uintptr_t len);
	void write_call(std::uint8_t* address, std::uintptr_t call_to);
	void write_region_instruction(std::uint8_t* address, std::int32_t instruction, std::int32_t bytes);
	bool erase_headers(HMODULE h_inst);
}

#endif
