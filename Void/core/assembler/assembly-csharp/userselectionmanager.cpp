#include "userselectionmanager.hpp"

assembler::user_selection_manager* assembler::user_selection_manager::instance()
{
	return static_cast<user_selection_manager_staticfields*>(get_global_klass()->static_fields)->instance;
}

assembler::il2cpp::il2cpp_class* assembler::user_selection_manager::get_global_klass()
{
	// Fields
	// @xref: [CompilerGeneratedAttribute] // RVA: 0x1F30 Offset: 0x1330 VA: 0x180001F30
	// @xref: private static whatthefuck <whatthefuck>k__BackingField; // 0x0
	// @xref: private APIUser ǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅ; // 0x18
	// @xref: private APIUser whatthefuck; // 0x20
	// @xref: [CompilerGeneratedAttribute] // RVA: 0x1F30 Offset: 0x1330 VA: 0x180001F30
	// @xref: private readonly whatthefuck<whatthefuck> <whatthefuck>k__BackingField; // 0x28
	// @xref: [CompilerGeneratedAttribute] // RVA: 0x1F30 Offset: 0x1330 VA: 0x180001F30
	// @xref: private readonly whatthefuck<whatthefuck> <whatthefuck>k__BackingField; // 0x30

	if (!global_klass_)
		global_klass_ = class_from_system_type(il2cpp::get_type(xorstr_(L"ÌÌÏÎÎÏÏÏÍÎÎÌÎÍÏÎÎÌÎÎÏÎÌ, Assembly-CSharp.dll")));

	return global_klass_;
}
