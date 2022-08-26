#include "assetbundle_download_manager.hpp"

assembler::assetbundle_download_manager* assembler::assetbundle_download_manager::instance()
{
	// @xref: private const int whatthefuck = 60;
	// @xref: private const int whatthefuck = 10;
	// @xref: private const long whatthefuck = 1073741824;
	// @xref: private const int whatthefuck = 86400;
	// @xref: private const long ǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅ = 21474836480;
	// @xref: private const int whatthefuck = 2592000;

	if (!abdm_type_)
		abdm_type_ = il2cpp::get_type(xorstr_(L"ÍÌÏÎÌÎÍÏÍÏÌÎÌÎÎÏÌÌÏÌÏÎÍ, Assembly-CSharp.dll"));

	return reinterpret_cast<assetbundle_download_manager_class*>(class_from_system_type(abdm_type_))->static_fields->instance;
}

std::pair<assembler::system_replication::collections::queue*, assembler::system_replication::collections::queue*> assembler::assetbundle_download_manager::get_queues()
{
	if (!this)
		return std::make_pair(nullptr, nullptr);

	return std::make_pair(this->fields.queue_1, this->fields.queue_2);
}

std::string assembler::assetbundle_download::get_id()
{
	if (!this)
		return xorstr_("INVALID_STRING");

	return s_chars(*reinterpret_cast<il2cpp::il2cpp_string**>(reinterpret_cast<std::uint8_t*>(this) + 0x18));
}

assembler::unity_engine::assetbundle* assembler::assetbundle_download::get_assetbundle()
{
	if (!this)
		return nullptr;

	return *reinterpret_cast<unity_engine::assetbundle**>(reinterpret_cast<std::uint8_t*>(this) + 0x78);
}

assembler::unity_engine::game_object* assembler::assetbundle_download::get_game_object()
{
	if (!this)
		return nullptr;

	return *reinterpret_cast<unity_engine::game_object**>(reinterpret_cast<std::uint8_t*>(this) + 0x70);
}
