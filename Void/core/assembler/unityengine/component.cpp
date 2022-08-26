#include "component.hpp"
#include "../../../utilities/ingame_logging.hpp"

assembler::unity_engine::transform* assembler::unity_engine::component::get_transform()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_transform passed nullptr.\n"));
        logging::pop();
        return nullptr;
    }

    if (!get_transform_func_) 
        get_transform_func_ = static_cast<get_transform_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Component::get_transform()")));

    return get_transform_func_(this);
}

assembler::unity_engine::game_object* assembler::unity_engine::component::get_game_object()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_game_object passed nullptr.\n"));
        logging::pop();
        return nullptr;
    }

    if (!get_game_object_func_) 
        get_game_object_func_ = static_cast<get_game_object_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Component::get_gameObject()")));

    return get_game_object_func_(this);
}

assembler::unity_engine::object* assembler::unity_engine::component::get_component(const std::string_view type)
{
    if (this == nullptr) 
        return nullptr;

    if (!get_component_func_) 
        get_component_func_ = static_cast<get_component_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Component::GetComponent(System.String)")));

    return get_component_func_(this, il2cpp::string_new(type));
}

assembler::unity_engine::object* assembler::unity_engine::component::get_component(il2cpp::il2cpp_type* type)
{
    const auto obj = this->get_game_object();

    if (!obj) 
        return nullptr;

    return obj->get_component(type);
}

assembler::unity_engine::object* assembler::unity_engine::component::get_component_in_children(const std::string_view type)
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_component_in_children passed nullptr.\n"));
        logging::pop();
        return nullptr;
    }

    const auto obj = this->get_game_object();

    if (!obj) 
        return nullptr;

    return obj->get_component_in_children(type);
}

assembler::il2cpp::il2cpp_array* assembler::unity_engine::component::find_objects_of_type_all(il2cpp::il2cpp_type* type)
{
    if (type == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] find_objects_of_type_all passed nullptr.\n"));
        logging::pop();
        return nullptr;
    }

    if (!find_objects_of_type_all_func_) 
        find_objects_of_type_all_func_ = static_cast<find_objects_of_type_all_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Resources::FindObjectsOfTypeAll(System.Type)")));

    return find_objects_of_type_all_func_(type);
}
