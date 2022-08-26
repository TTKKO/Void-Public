#include "ui_vrc_list.hpp"

assembler::il2cpp::il2cpp_type* assembler::ui_vrc_list::get_type()
{
	// @xref: protected readonly Dictionary<int, List<ApiModel>> ǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅ; // 0xD0

	if (!type_)
		type_ = il2cpp::get_type(xorstr_(L"ÌÍÍÍÎÏÍÎÌÍÍÎÌÎÎÏÍÏÍÏÏÎÌ, Assembly-CSharp.dll"));
		//type_ = reinterpret_cast<il2cpp::il2cpp_type*>(type_get_object(il2cpp::locate_type(xorstr_("Assembly-CSharp.dll"), 1284)));

	return type_;
}

void* assembler::ui_vrc_list::get_dictionary()
{
	return *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(this) + 0xD0);
}

void assembler::ui_vrc_list::set_dictionary(void* ptr)
{
	*reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(this) + 0xD0) = ptr;
}
