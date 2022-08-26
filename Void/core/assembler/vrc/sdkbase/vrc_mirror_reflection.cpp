#include "vrc_mirror_reflection.hpp"

void assembler::vrc::sdk_base::vrc_mirror_reflection::set_reflection_layers(const std::int32_t value)
{
	if (!this)
		return;

	*reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this) + 0x1C) = value;
}

std::int32_t assembler::vrc::sdk_base::vrc_mirror_reflection::get_reflection_layers()
{
	if (!this)
		return -1;

	return *reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this) + 0x1C);
}

void assembler::vrc::sdk_base::vrc_mirror_reflection::set_resolution(const dimension value)
{
	if (!this)
		return;

	*reinterpret_cast<dimension*>(reinterpret_cast<std::uint8_t*>(this) + 0x20) = value;
}

assembler::il2cpp::il2cpp_type* assembler::vrc::sdk_base::vrc_mirror_reflection::get_global_type()
{
	if (!type_)
		type_ = il2cpp::get_type(xorstr_("VRC.SDKBase.VRC_MirrorReflection, VRCSDKBase.dll"));

	return type_;
}
