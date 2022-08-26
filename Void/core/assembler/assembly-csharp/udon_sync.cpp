#include "udon_sync.hpp"

assembler::il2cpp::il2cpp_type* assembler::udon_sync::get_type()
{
	// @xref: private bool whatthefuck; // 0x50
	// @xref: public UdonBehaviour ǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅ; // 0x58
	// @xref: internal whatthefuck.whatthefuck[] whatthefuck; // 0x60
	// @xref: internal whatthefuck<whatthefuck> whatthefuck; // 0x68
	// @xref: internal whatthefuck whatthefuck; // 0x70
	// @xref: private whatthefuck whatthefuck; // 0x78

	if (!type_)
		type_ = il2cpp::get_type(xorstr_(L"ÎÌÎÎÌÌÏÎÌÌÍÏÍÎÍÎÌÌÍÍÍÌÌ, Assembly-CSharp.dll"));

	return type_;
}
