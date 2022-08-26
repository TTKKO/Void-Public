#include "gameobject.hpp"

assembler::unity_engine::game_object* assembler::unity_engine::game_object::cctor(const std::string_view name)
{
    const auto gameobject_type = il2cpp::get_type(xorstr_("UnityEngine.GameObject, UnityEngine.CoreModule"));
    const auto constructed = reinterpret_cast<game_object*>(new_object(gameobject_type, true));

    if (!cctor_func_) 
        cctor_func_ = static_cast<cctor_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.GameObject::Internal_CreateGameObject(UnityEngine.GameObject,System.String)")));

    cctor_func_(constructed, il2cpp::string_new(name));
    return constructed;
}

void assembler::unity_engine::game_object::set_active(const bool value)
{
    if (!set_active_func_) 
        set_active_func_ = static_cast<set_active_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.GameObject::SetActive(System.Boolean)")));

    set_active_func_(this, value);
}

void assembler::unity_engine::game_object::set_layer(const std::int32_t value)
{
    if (!set_layer_func_) set_layer_func_ = static_cast<set_layer_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.GameObject::set_layer(System.Int32)")));
    set_layer_func_(this, value);
}

std::int32_t assembler::unity_engine::game_object::get_layer()
{
    if (!get_layer_func_) get_layer_func_ = static_cast<get_layer_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.GameObject::get_layer()")));
    return get_layer_func_(this);
}

assembler::unity_engine::transform* assembler::unity_engine::game_object::get_transform()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_transform passed nullptr.\n"));
        logging::pop();
        return nullptr;
    }
    if (!get_transforn_func_) 
        get_transforn_func_ = static_cast<get_transforn_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.GameObject::get_transform()")));
    return get_transforn_func_(this);
}

assembler::unity_engine::component* assembler::unity_engine::game_object::add_component_str(const std::string_view klass)
{
    if (!add_component_str_func_) 
        add_component_str_func_ = static_cast<add_component_str_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.GameObject::AddComponentInternal(System.String)")));
    return add_component_str_func_(this, il2cpp::string_new(klass));
}

// Converts string type with IL2CPP::GetType
assembler::unity_engine::component* assembler::unity_engine::game_object::add_component(const std::string_view type)
{
    if (!add_component_func_) add_component_func_ = static_cast<add_component_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.GameObject::Internal_AddComponentWithType(System.Type)")));
    return add_component_func_(this, il2cpp::get_type(type));
}

assembler::unity_engine::component* assembler::unity_engine::game_object::add_component(il2cpp::il2cpp_type* type)
{
    if (!add_component_func_) add_component_func_ = static_cast<add_component_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.GameObject::Internal_AddComponentWithType(System.Type)")));
    return add_component_func_(this, type);
}

assembler::unity_engine::object* assembler::unity_engine::game_object::get_component(const std::string_view type)
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_component passed nullptr.\n"));
        logging::pop();
        return nullptr;
    }

    if (!get_component_by_name_func_) get_component_by_name_func_ = static_cast<get_component_by_name_t>(
        il2cpp::resolve_icall(xorstr_("UnityEngine.GameObject::GetComponentByName(System.String)")));
    return get_component_by_name_func_(this, il2cpp::string_new(type));
}

assembler::unity_engine::game_object* assembler::unity_engine::game_object::create_primitive(const int32_t type)
{
    if (!create_primitive_func_) 
        create_primitive_func_ = static_cast<create_primitive_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.GameObject::CreatePrimitive(UnityEngine.PrimitiveType)")));

    return create_primitive_func_(type);
}

assembler::unity_engine::object* assembler::unity_engine::game_object::get_component_in_children(const std::string_view type)
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_component_in_children passed nullptr.\n"));
        logging::pop();
        return nullptr;
    }

    if (!get_component_in_children_func_) 
        get_component_in_children_func_ = static_cast<get_component_in_children_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.GameObject::GetComponentInChildren(System.Type,System.Boolean)")));

	return get_component_in_children_func_(this, il2cpp::get_type(type), false);
}

assembler::il2cpp::il2cpp_array* assembler::unity_engine::game_object::get_components_in_children(const std::string_view type, const bool a)
{
    if (this == nullptr)
        return nullptr;

    if (!get_components_in_children_func_) 
        get_components_in_children_func_ = static_cast<get_components_in_children_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.GameObject::GetComponentsInternal(System.Type,System.Boolean,System.Boolean,System.Boolean,System.Boolean,System.Object)")));

    return get_components_in_children_func_(this, il2cpp::get_type(type), false, true, a, false, NULL);
}

assembler::il2cpp::il2cpp_array* assembler::unity_engine::game_object::get_components_in_children(il2cpp::il2cpp_type* type, bool a)
{
    if (this == nullptr)
        return nullptr;

    if (!get_components_in_children_func_)
        get_components_in_children_func_ = static_cast<get_components_in_children_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.GameObject::GetComponentsInternal(System.Type,System.Boolean,System.Boolean,System.Boolean,System.Boolean,System.Object)")));

    return get_components_in_children_func_(this, type, false, true, a, false, NULL);
}

//il2cpp::il2cpp_array* UnityEngine::GameObject::GetComponentsInChildren(IL2CPP::Type* type)
//{
//	using func_t = il2cpp::il2cpp_array* (*)(GameObject* _this, IL2CPP::Type* type);
//
//	func_t func = GetMethod<func_t>(0ax1C9A920);
//
//	return func(this, type);
//}

bool assembler::unity_engine::game_object::get_active_self()
{
    if (!get_active_self_func_) 
        get_active_self_func_ = static_cast<get_active_self_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.GameObject::get_activeSelf()")));

    return get_active_self_func_(this);
}

assembler::unity_engine::game_object* assembler::unity_engine::game_object::find(const std::string_view name)
{
    if (!find_func_) 
        find_func_ = static_cast<find_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.GameObject::Find(System.String)")));

	return find_func_(il2cpp::string_new(name));
}

assembler::unity_engine::object* assembler::unity_engine::game_object::get_component(il2cpp::il2cpp_type* type)
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_component passed nullptr\n"));
        logging::pop();
        return nullptr;
    }
    if (!get_component_func_) 
        get_component_func_ = static_cast<get_component_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.GameObject::GetComponent(System.Type)")));

    return get_component_func_(this, type);
}

assembler::il2cpp::il2cpp_array_wrapper<assembler::unity_engine::component*>* assembler::unity_engine::game_object::get_components(il2cpp::il2cpp_type* type)
{
    if (this == nullptr)
        return nullptr;

    if (!get_components_func_)
        get_components_func_ = static_cast<get_components_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.GameObject::GetComponentsInternal(System.Type,System.Boolean,System.Boolean,System.Boolean,System.Boolean,System.Object)")));

    return get_components_func_(this, type, false, false, true, false, nullptr);
}
