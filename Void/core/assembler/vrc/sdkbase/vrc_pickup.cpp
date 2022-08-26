#include "vrc_pickup.hpp"

assembler::il2cpp::il2cpp_type* assembler::vrc::sdk_base::vrc_pickup::get_global_type()
{
	if (!type_)
		type_ = il2cpp::get_type(xorstr_("VRC.SDKBase.VRC_Pickup, VRCSDKBase.dll"));

	return type_;
}

void assembler::vrc::sdk_base::vrc_pickup::set_pickupable(const bool value)
{
	if (!this)
		return;

	*reinterpret_cast<bool*>(reinterpret_cast<std::uint8_t*>(this) + 0x98) = value;
}

void assembler::vrc::sdk_base::vrc_pickup::set_disallowtheft(const bool value)
{
	if (!this)
		return;

	*reinterpret_cast<bool*>(reinterpret_cast<std::uint8_t*>(this) + 0x1C) = value;
}

void assembler::vrc::sdk_base::vrc_pickup::set_proximity(const float value)
{
	if (!this)
		return;

	*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this) + 0x9C) = value;
}

void assembler::vrc::sdk_base::vrc_pickup::set_allow_manipulation_when_equipped(const bool value)
{
	if (!this)
		return;

	*reinterpret_cast<bool*>(reinterpret_cast<std::uint8_t*>(this) + 0x30) = value;
}
