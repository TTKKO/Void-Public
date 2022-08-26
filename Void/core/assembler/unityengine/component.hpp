/*
 *		assembler/unityengine/component.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's Component class
 */

#pragma once
#include "../common.hpp"
#include "gameobject.hpp"
#include "../../sdk/datatypes/vector.h"

namespace assembler::unity_engine
{
    struct component : object
    {
        transform* get_transform();
        game_object* get_game_object();
        object* get_component(std::string_view type);
        object* get_component(il2cpp::il2cpp_type* type);
        object* get_component_in_children(std::string_view type);
        static il2cpp::il2cpp_array* find_objects_of_type_all(il2cpp::il2cpp_type* type);

    private:
        using get_transform_t = transform * (*)(component*);
        inline static get_transform_t get_transform_func_ = nullptr;

        using get_game_object_t = game_object * (*)(component*);
        inline static get_game_object_t get_game_object_func_ = nullptr;

        using get_component_t = object * (*)(component*, il2cpp::il2cpp_string*);
        inline static get_component_t get_component_func_ = nullptr;

        using find_objects_of_type_all_t = il2cpp::il2cpp_array* (*)(il2cpp::il2cpp_type*);
        inline static find_objects_of_type_all_t find_objects_of_type_all_func_ = nullptr;
    };

}
