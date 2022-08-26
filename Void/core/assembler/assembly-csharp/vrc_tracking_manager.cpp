#include "vrc_tracking_manager.hpp"

assembler::vrc_tracking_manager* assembler::vrc_tracking_manager::instance()
{
	return *static_cast<vrc_tracking_manager**>(class_from_system_type(get_global_type())->static_fields);
}

assembler::il2cpp::il2cpp_type* assembler::vrc_tracking_manager::get_global_type()
{
	if (!global_type_)
		global_type_ = il2cpp::get_type(xorstr_(L"лннмоолмолмнлмоллмонлол, Assembly-CSharp.dll"));

	return global_type_;
}
