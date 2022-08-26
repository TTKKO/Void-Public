/*
 *		assembler/unityengine/gameobject.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's GameObject class
 */

#pragma once
#include <string>
#include "../il2cpp/array_wrapper.hpp"
#include "../common.hpp"

namespace assembler::unity_engine
{
    struct transform;
    struct component;

    struct game_object : object
    {
        static game_object* cctor(std::string_view name);
        void set_active(bool value);
        void set_layer(std::int32_t value);
        std::int32_t get_layer();
        transform* get_transform();

        component* add_component_str(std::string_view klass);
        component* add_component(std::string_view type);
        component* add_component(il2cpp::il2cpp_type* type);

        object* get_component(std::string_view type);
        object* get_component(il2cpp::il2cpp_type* type);
        il2cpp::il2cpp_array_wrapper<component*>* get_components(il2cpp::il2cpp_type* type);

        static game_object* create_primitive(int32_t type);

        object* get_component_in_children(std::string_view type);
        il2cpp::il2cpp_array* get_components_in_children(std::string_view type, bool a);
        il2cpp::il2cpp_array* get_components_in_children(il2cpp::il2cpp_type* type, bool a);

        bool get_active_self();
        static game_object* find(std::string_view name);

    private:
        using cctor_t = void (*)(game_object*, il2cpp::il2cpp_string*);
        inline static cctor_t cctor_func_ = nullptr;

        using set_active_t = void(*)(game_object*, bool);
        inline static set_active_t set_active_func_ = nullptr;

        using set_layer_t = void(*)(game_object*, int32_t);
        inline static set_layer_t set_layer_func_ = nullptr;

        using get_layer_t = int32_t(*)(game_object*);
        inline static get_layer_t get_layer_func_ = nullptr;

        using get_transforn_t = transform * (*)(game_object*);
        inline static get_transforn_t get_transforn_func_ = nullptr;

        using get_components_in_children_t =  il2cpp::il2cpp_array* (*)(game_object*, il2cpp::il2cpp_type*, bool, bool, bool, bool, std::uintptr_t);
        inline static get_components_in_children_t get_components_in_children_func_ = nullptr;

        using add_component_str_t = component * (*)(game_object*, il2cpp::il2cpp_string*);
        inline static add_component_str_t add_component_str_func_ = nullptr;

        using add_component_t = component * (*)(game_object*, il2cpp::il2cpp_type*);
        inline static add_component_t add_component_func_ = nullptr;

        using get_component_by_name_t = object * (*)(game_object*, il2cpp::il2cpp_string*);
        inline static get_component_by_name_t get_component_by_name_func_ = nullptr;

        using get_component_t = object* (*)(game_object*, il2cpp::il2cpp_type*);
        inline static get_component_t get_component_func_ = nullptr;

        using get_components_t = il2cpp::il2cpp_array_wrapper<component*>* (*)(game_object*, il2cpp::il2cpp_type*, bool, bool, bool, bool, object*);
        inline static get_components_t get_components_func_ = nullptr;

        using create_primitive_t = game_object * (*)(int32_t);
        inline static create_primitive_t create_primitive_func_ = nullptr;

        using get_component_in_children_t = object * (*)(game_object*, il2cpp::il2cpp_type*, bool);
        inline static get_component_in_children_t get_component_in_children_func_ = nullptr;

        using get_active_self_t = bool (*)(game_object*);
        inline static get_active_self_t get_active_self_func_ = nullptr;

        using find_t = game_object * (*)(il2cpp::il2cpp_string*);
        inline static find_t find_func_ = nullptr;
    };
}
