/*
 *		assembler/unityengine/transform.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's Transform class
 */

#pragma once
#include "../common.hpp"
#include "component.hpp"
#include "../../../offsets.hpp"
#include "../../sdk/datatypes/quaternion.hpp"

namespace assembler::unity_engine
{
    struct transform : component
    {
        static il2cpp::il2cpp_type* get_global_type();

        void set_rotation(const sdk::quaternion& value);
        sdk::quaternion get_rotation();

        transform* find(il2cpp::il2cpp_string* str);
        transform* find(std::string_view str);

        void set_parent(transform* parent, bool world_position_stays);
        void set_parent(transform* to);
        transform* get_parent();

        void set_local_position(const sdk::vector& value);
    	sdk::vector get_local_position();

        void set_local_scale(const sdk::vector& value);
        sdk::vector get_local_scale();

        void set_local_rotation(const sdk::quaternion& q);
        sdk::quaternion get_local_rotation();

        sdk::vector inverse_transform_point(const sdk::vector& value);

        transform* get_child(int index);
        transform* get_root();
        int child_count();
        void get_all_children();
        static void get_all_children(transform* transform);
        object* get_component_in_children_z(std::string_view type);

        sdk::vector get_forward();
        sdk::vector get_right();
        sdk::vector get_up();
        sdk::vector get_position();

        void set_position(const sdk::vector& value);
        void rotate(const sdk::vector& eulers, std::int32_t relative_to);
        //void rotate(vector3 value);

    private:
        static inline il2cpp::il2cpp_type* type_ = nullptr;

        using get_rotation_t = void (*)(transform*, sdk::quaternion*);
        inline static get_rotation_t get_rotation_func_ = nullptr;

        using set_rotation_t = void (*)(transform*, const sdk::quaternion&);
        inline static set_rotation_t set_rotation_func_ = nullptr;

        using find_t = transform * (*)(transform*, il2cpp::il2cpp_string*, bool);
        inline static find_t find_func_ = nullptr;

        using set_parent_t = void (*)(transform*, transform*, bool);
        inline static set_parent_t set_parent_func_ = nullptr;

        using set_position_t = void (*)(transform*, const sdk::vector&);
        inline static set_position_t set_position_func_ = nullptr;

        using get_position_t = void (*)(transform*, sdk::vector*);
        inline static get_position_t get_position_func_ = nullptr;

        using child_count_t = int (*)(transform*);
        inline static child_count_t child_count_func_ = nullptr;

        using get_parent_t = transform * (*)(transform*);
        inline static get_parent_t get_parent_func_ = nullptr;

        using set_local_position_t = void(*)(transform*, const sdk::vector&);
        inline static set_local_position_t set_local_position_func_ = nullptr;

        using get_local_position_t = void (*)(transform*, sdk::vector*);
        inline static get_local_position_t get_local_position_func_ = nullptr;

        using set_local_scale_t = void(*)(transform*, const sdk::vector&);
        inline static set_local_scale_t set_local_scale_func_ = nullptr;

        using get_local_scale_t = void (*)(transform*, sdk::vector*);
        inline static get_local_scale_t get_local_scale_func_ = nullptr;

        using set_local_rotation_t = void(*)(transform*, const sdk::quaternion&);
        inline static set_local_rotation_t set_local_rotation_func_ = nullptr;

        using get_local_rotation_t = void (*)(transform*, sdk::quaternion*);
        inline static get_local_rotation_t get_local_rotation_func_ = nullptr;

        using inverse_transform_point_t = void (*)(transform*, const sdk::vector&, sdk::vector*);
        inline static inverse_transform_point_t inverse_transform_point_func_ = nullptr;

        using get_child_t = transform * (*)(transform*, int32_t);
        inline static get_child_t get_child_func_ = nullptr;

        using get_root_t = transform * (*)(transform*);
        inline static get_root_t get_root_func_ = nullptr;

        //using rotate_t = void(*)(transform*, vector3, int32_t);
        //inline static rotate_t rotate_func_ = nullptr;
    };
}