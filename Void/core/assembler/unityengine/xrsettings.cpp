#include "xrsettings.hpp"

void assembler::unity_engine::xrsettings::load_device_by_name(const std::string_view device_name)
{
	if (!load_device_by_name_func_) 
		load_device_by_name_func_ = static_cast<load_device_by_name_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.XR.XRSettings::LoadDeviceByName(System.String[])")));

	const auto arr = array_new<il2cpp::il2cpp_string*>(il2cpp::class_from_system_type(il2cpp::get_type(xorstr_("System.String"))), 1ull);
	arr->at(0) = il2cpp::string_new(device_name);

	load_device_by_name_func_(arr);
}

void assembler::unity_engine::xrsettings::load_devices_by_name(il2cpp::il2cpp_array_wrapper<il2cpp::il2cpp_string*>* arr)
{
	if (!load_device_by_name_func_)
		load_device_by_name_func_ = static_cast<load_device_by_name_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.XR.XRSettings::LoadDeviceByName(System.String[])")));

	load_device_by_name_func_(arr);
}

assembler::il2cpp::il2cpp_array_wrapper<assembler::il2cpp::il2cpp_string*>* assembler::unity_engine::xrsettings::get_supported_devices()
{
	if (!get_supported_devices_func_)
		get_supported_devices_func_ = static_cast<get_supported_devices_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.XR.XRSettings::get_supportedDevices()")));

	return get_supported_devices_func_();
}

void assembler::unity_engine::xrsettings::set_enabled(const bool value)
{
	if (!set_enabled_func_)
		set_enabled_func_ = static_cast<set_enabled_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.XR.XRSettings::set_enabled(System.Boolean)")));

	set_enabled_func_(value);
}

bool assembler::unity_engine::xrsettings::get_enabled()
{
	if (!get_enabled_func_)
		get_enabled_func_ = static_cast<get_enabled_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.XR.XRSettings::get_enabled()")));

	return get_enabled_func_();
}
