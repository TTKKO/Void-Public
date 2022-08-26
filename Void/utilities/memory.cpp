#include "memory.hpp"
#include <TlHelp32.h>
#include <intrin.h>
#include <Psapi.h>

#pragma region peb_manipulation
void memory::relink_module_to_peb(const HMODULE h_module)
{
	const auto it = std::ranges::find_if(unlinked_modules, find_module_handle(h_module));

	if (it == unlinked_modules.end())
		return;

	// VMProtectBeginVirtualization("RelinkModule");

	RELINK((*it).Entry->InLoadOrderLinks, (*it).RealInLoadOrderLinks)
	RELINK((*it).Entry->InInitializationOrderLinks, (*it).RealInInitializationOrderLinks)
	RELINK((*it).Entry->InMemoryOrderLinks, (*it).RealInMemoryOrderLinks)
	RELINK((*it).Entry->HashLinks, (*it).RealHashLinks)

	// VMProtectEnd();

	unlinked_modules.erase(it);
}

void memory::unlink_module_from_peb(HMODULE h_module)
{
	// VMProtectBeginUltra("UnlinkModule (1)");

	if (const auto it = std::ranges::find_if(unlinked_modules, find_module_handle(h_module)); it != unlinked_modules.end())
		return;

	const _PEB* p_peb = reinterpret_cast<_PEB*>(__readgsqword(0x60));
	PLIST_ENTRY current_entry = p_peb->Ldr->InLoadOrderModuleList.Flink;

	// VMProtectEnd();

	while (current_entry != &p_peb->Ldr->InLoadOrderModuleList && current_entry != nullptr)
	{
		if (auto current = CONTAINING_RECORD(current_entry, _LDR_DATA_TABLE_ENTRY, InLoadOrderLinks); current->DllBase == h_module)
		{
			// VMProtectBeginVirtualization("UnlinkModule (2)");

			unlinked_modules.emplace_back(
				h_module,
				current->InLoadOrderLinks.Blink->Flink,
				current->InMemoryOrderLinks.Blink->Flink,
				current->InInitializationOrderLinks.Blink->Flink,
				current->HashLinks.Blink->Flink,
				current
			);

			UNLINK(current->InLoadOrderLinks)
			UNLINK(current->InInitializationOrderLinks)
			UNLINK(current->InMemoryOrderLinks)
			UNLINK(current->HashLinks)

			// VMProtectEnd();

			break;
		}

		current_entry = current_entry->Flink;
	}
}
#pragma endregion

std::uint64_t memory::get_total_vmemory_by_proc()
{
	PROCESS_MEMORY_COUNTERS_EX pmc{};
	K32GetProcessMemoryInfo(GetCurrentProcess(), reinterpret_cast<PROCESS_MEMORY_COUNTERS*>(&pmc), sizeof pmc);
	return pmc.WorkingSetSize;
}

std::uint64_t memory::get_total_vmemory_used()
{
	MEMORYSTATUSEX mem_info{};
	mem_info.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&mem_info);
	return mem_info.ullTotalPhys - mem_info.ullAvailPhys;
}

#pragma region module_scanning
void* memory::get_module_base_handle(const std::wstring_view sz_module_name)
{
	// VMProtectBeginMutation("GetModuleHandleW");
	const _PEB* p_peb = reinterpret_cast<_PEB*>(__readgsqword(0x60));

	if (sz_module_name.empty())
		return p_peb->ImageBaseAddress;

	for (LIST_ENTRY* p_list_entry = p_peb->Ldr->InLoadOrderModuleList.Flink; p_list_entry != &p_peb->Ldr->InLoadOrderModuleList; p_list_entry = p_list_entry->Flink)
		if (const _LDR_DATA_TABLE_ENTRY* p_entry = CONTAINING_RECORD(p_list_entry, _LDR_DATA_TABLE_ENTRY, InLoadOrderLinks); p_entry->BaseDllName.Buffer && sz_module_name == p_entry->BaseDllName.Buffer)
			return p_entry->DllBase;

#ifdef _DEBUG
	logging::push(FOREGROUND_INTENSE_RED);
	logging::print(SECSTR("[critical] module base not found: [{}]\n"), utility::unicode_ascii(sz_module_name));
	logging::pop();
#endif

	// VMProtectEnd();
	return nullptr;
}

void* memory::get_module_base_handle(std::string_view sz_module_name)
{
	// VMProtectBeginMutation("GetModuleHandle");
	const _PEB* p_peb = reinterpret_cast<_PEB*>(__readgsqword(0x60));

	if (sz_module_name.empty())
		return p_peb->ImageBaseAddress;

	const std::wstring wsz_module_name(sz_module_name.begin(), sz_module_name.end());

	for (LIST_ENTRY* p_list_entry = p_peb->Ldr->InLoadOrderModuleList.Flink; p_list_entry != &p_peb->Ldr->InLoadOrderModuleList; p_list_entry = p_list_entry->Flink)
		if (const _LDR_DATA_TABLE_ENTRY* p_entry = CONTAINING_RECORD(p_list_entry, _LDR_DATA_TABLE_ENTRY, InLoadOrderLinks); p_entry->BaseDllName.Buffer && wsz_module_name == p_entry->BaseDllName.Buffer)
			return p_entry->DllBase;

#ifdef _DEBUG
	logging::push(FOREGROUND_INTENSE_RED);
	logging::print(SECSTR("[critical] module base not found: [{}]\n"), sz_module_name);
	logging::pop();
#endif

	// VMProtectEnd();
	return nullptr;
}

void* memory::get_export_address(const void* p_module_base, const std::string_view sz_procedure_name)
{
	// VMProtectBeginMutation("GetExportAddress");

	const auto p_address = static_cast<const std::uint8_t*>(p_module_base);
	const auto p_dos_header = static_cast<const IMAGE_DOS_HEADER*>(p_module_base);
	const auto p_nt_headers = reinterpret_cast<const IMAGE_NT_HEADERS*>(p_address + p_dos_header->e_lfanew);
	const IMAGE_OPTIONAL_HEADER64* p_optional_header = &p_nt_headers->OptionalHeader;

	const auto u_export_size = p_optional_header->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size;
	const auto u_export_address = p_optional_header->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;

	if (u_export_size <= 0u) // @note: shouldn't happen
		return nullptr;

	const auto p_export_directory = reinterpret_cast<const IMAGE_EXPORT_DIRECTORY*>(p_address + u_export_address);
	const auto p_names_rva = reinterpret_cast<const DWORD*>(p_address + p_export_directory->AddressOfNames);
	const auto p_functions_rva = reinterpret_cast<const DWORD*>(p_address + p_export_directory->AddressOfFunctions);
	const auto p_name_ordinals = reinterpret_cast<const std::uint16_t*>(p_address + p_export_directory->AddressOfNameOrdinals);

	// @note: binary search
	DWORD u_right = p_export_directory->NumberOfNames;
	DWORD u_left = 0;

	while (u_right != u_left)
	{
		const DWORD u_middle = u_left + (u_right - u_left >> 1u);
		const int i_result = sz_procedure_name.compare(reinterpret_cast<const char*>(p_address + p_names_rva[u_middle]));

		if (i_result == 0)
			return const_cast<void*>(static_cast<const void*>(p_address + p_functions_rva[p_name_ordinals[u_middle]]));

		if (i_result > 0)
			u_left = u_middle;
		else
			u_right = u_middle;
	}

	logging::push(FOREGROUND_INTENSE_RED);
	logging::print(SECSTR("[critical] export not found: [{}]\n"), sz_procedure_name);
	logging::pop();

	// VMProtectEnd();
	return nullptr;
}
#pragma endregion

#pragma region memory_manipulation
void memory::write_jmp(std::uint8_t* address, const std::uintptr_t jmp_to, const std::uintptr_t len)
{
	c_wrapped_protect protection(address, len, PAGE_EXECUTE_READWRITE);

	const auto dw_rel_addr = jmp_to - reinterpret_cast<std::uintptr_t>(address) - 5;
	*address = 0xE9;
	*reinterpret_cast<std::uintptr_t*>(address + 0x1) = dw_rel_addr;

	for (std::uintptr_t x = 0x5; x < len; x++)
		*(address + x) = 0x90;
}

void memory::write_call(std::uint8_t* address, const std::uintptr_t call_to)
{
	c_wrapped_protect protection(address, 0x5, PAGE_EXECUTE_READWRITE);

	const auto dw_rel_addr = call_to - reinterpret_cast<std::uintptr_t>(address) - 5;
	*address = 0xE8;
	*reinterpret_cast<std::uintptr_t*>(address + 0x1) = dw_rel_addr;
}

void memory::write_region_instruction(std::uint8_t* address, const std::int32_t instruction, const std::int32_t bytes)
{
	c_wrapped_protect protection(address, bytes, PAGE_EXECUTE_READWRITE);
	memset(address, instruction, bytes);
}

bool memory::erase_headers(const HMODULE h_inst)
{
	// VMProtectBeginUltra("EraseHeaders");

	const auto p_dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(h_inst);
	const auto p_nt_header = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<std::uint8_t*>(p_dos_header) + static_cast<std::uintptr_t>(p_dos_header->e_lfanew));

	DWORD protection;

	//if (!VMProtectIsProtected())
	//	return false;
	//if (VMProtectIsDebuggerPresent(true))
	//	return false;
	//if (!VMProtectIsValidImageCRC())
	//	return false;

	if (VirtualProtect(p_dos_header, sizeof IMAGE_DOS_HEADER, PAGE_EXECUTE_READWRITE, &protection))
	{
		RtlSecureZeroMemory(p_dos_header, sizeof IMAGE_DOS_HEADER);
		VirtualProtect(p_dos_header, sizeof IMAGE_DOS_HEADER, protection, nullptr);
	}

	protection = 0;
	if (p_nt_header && VirtualProtect(p_nt_header, sizeof IMAGE_NT_HEADERS, PAGE_EXECUTE_READWRITE, &protection))
	{
		RtlSecureZeroMemory(p_nt_header, sizeof IMAGE_NT_HEADERS);
		VirtualProtect(p_nt_header, sizeof IMAGE_NT_HEADERS, protection, nullptr);
	}

	// VMProtectEnd();

	return true;
}
#pragma endregion
