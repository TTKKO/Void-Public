#include "common.hpp"
#include "il2cpp/il2cpp.hpp"

assembler::unity_engine::object* assembler::unity_engine::object::instantiate(object* original)
{
	if (original == nullptr)
		return nullptr;

	if (!instantiate_func_)
		instantiate_func_ = static_cast<instantiate_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Object::Internal_CloneSingle(UnityEngine.Object)")));

	const auto ret = instantiate_func_(original);

	if (!ret || ret->fields.cached_ptr == NULL)
		return nullptr;

	return ret;
}

std::string assembler::unity_engine::object::get_name()
{
	if (this == nullptr) 
		return xorstr_("INVALID_STRING");

	if (!get_name_func_)
		get_name_func_ = static_cast<get_name_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Object::GetName(UnityEngine.Object)")));

	return s_chars(get_name_func_(this));
}

std::wstring assembler::unity_engine::object::get_ws_name()
{
	if (this == nullptr)
		return xorstr_(L"INVALID_STRING");

	if (!get_name_func_)
		get_name_func_ = static_cast<get_name_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Object::GetName(UnityEngine.Object)")));

	return ws_chars(get_name_func_(this));
}

void assembler::unity_engine::object::set_name(const std::string_view value)
{
	if (!set_name_func_)
		set_name_func_ = static_cast<set_name_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Object::SetName(UnityEngine.Object,System.String)")));

	set_name_func_(this, il2cpp::string_new(value));
}

std::int32_t assembler::unity_engine::object::get_hash_code()
{
	return -1640531535 * (reinterpret_cast<std::uint32_t>(this) >> 3);
}

assembler::il2cpp::il2cpp_object* assembler::unity_engine::object::unload_unused_assets()
{
	if (!unload_unused_assets_func_)
		unload_unused_assets_func_ = static_cast<unload_unused_assets_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Resources::UnloadUnusedAssets()")));

	return unload_unused_assets_func_();
}

assembler::il2cpp::il2cpp_array* assembler::unity_engine::object::find_objects_of_type(il2cpp::il2cpp_type* type)
{
	if (!find_objects_of_type_func_)
		find_objects_of_type_func_ = static_cast<find_objects_of_type_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Object::FindObjectsOfType(System.Type)")));

	return find_objects_of_type_func_(type);
}

assembler::il2cpp::il2cpp_array* assembler::unity_engine::object::find_objects_of_type_all(il2cpp::il2cpp_type* type)
{
	if (!find_objects_of_type_all_func_)
		find_objects_of_type_all_func_ = static_cast<find_objects_of_type_all_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Resources::FindObjectsOfTypeAll(System.Type)")));

	return find_objects_of_type_all_func_(type);
}

void assembler::unity_engine::object::destroy(object* obj, const float t)
{
	if (obj == nullptr)
	{
		logging::print(xorstr_("[error] destroy passed a nullptr\n"));
		return;
	}

	if (!destroy_func_)
		destroy_func_ = static_cast<destroy_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Object::Destroy(UnityEngine.Object,System.Single)")));

	destroy_func_(obj, t);
}

void assembler::unity_engine::object::destroy_immediate(object* obj, const bool destroy_assets)
{
	if (obj == nullptr)
	{
		logging::print(xorstr_("[error] destroy_immediate passed a nullptr\n"));
		return;
	}

	if (!destroy_immediate_func_)
		destroy_immediate_func_ = static_cast<destroy_immediate_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Object::DestroyImmediate(UnityEngine.Object,System.Boolean)")));
	destroy_immediate_func_(obj, destroy_assets);
}

assembler::unity_engine::object* assembler::unity_engine::object::instantiate(object* original, transform* parent, const bool instantiate_in_world_space)
{
	if (original == nullptr)
		return nullptr;

	if (parent == nullptr)
		return instantiate(original);

	if (!instantiate_set_parent_func_)
		instantiate_set_parent_func_ = static_cast<instantiate_set_parent_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Object::Internal_CloneSingleWithParent(UnityEngine.Object,UnityEngine.Transform,System.Boolean)")));

	const auto ret = instantiate_set_parent_func_(original, parent, instantiate_in_world_space);

	if (!ret || ret->fields.cached_ptr == NULL)
		return nullptr;

	return ret;
}

//Object* Object::ctor()
//{
//	auto ret = (Object*)IL2CPP::NewObject("System.Object");
//	using func_t = void (*)(Object* _this);
//	func_t func = GetMethod<func_t>(0x439670);
//	func(ret);
//	return ret;
//}
