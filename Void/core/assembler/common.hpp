/*
 *		common.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Structs, classes, and functions used throughout the source code
 */

#pragma once
#include <cstddef>
#include <cinttypes>
#include "il2cpp/il2cpp.hpp"

#define LVM_TESTING 0

#if LVM_TESTING == 1
#define SOL_LUAJIT 1
#define SOL_ALL_SAFETIES_ON 1
#include "../lvm/sol2/sol.hpp"
#endif

namespace assembler::unity_engine
{
    struct transform;
}

namespace assembler::unity_engine {

    struct __declspec(align(8)) unity_engine_object_fields {
        std::intptr_t cached_ptr;
    };

    struct unity_engine_object_rgctxs {
    };

    struct unity_engine_object_vtable {
        il2cpp::virtual_invoke_data _0_Equals;
        il2cpp::virtual_invoke_data _1_Finalize;
        il2cpp::virtual_invoke_data _2_GetHashCode;
        il2cpp::virtual_invoke_data _3_ToString;
    };

    struct unity_engine_object_c {
        il2cpp::il2cpp_class_1 _1;
        struct unity_engine_object_static_fields* static_fields;
        unity_engine_object_rgctxs* rgctx_data;
        il2cpp::il2cpp_class_2 _2;
        unity_engine_object_vtable vtable;
    };

    struct object
    {
        DELCONST(object);

        unity_engine_object_c* klass;
        void* monitor;
        unity_engine_object_fields fields;

        static object* instantiate(object* original);
        static object* instantiate(object* original, transform* parent, bool instantiate_in_world_space = false);

        std::string get_name();
        std::wstring get_ws_name();
        void set_name(std::string_view value);
        std::int32_t get_hash_code();

        static il2cpp::il2cpp_object* unload_unused_assets();
        static il2cpp::il2cpp_array* find_objects_of_type(il2cpp::il2cpp_type* type);
        static il2cpp::il2cpp_array* find_objects_of_type_all(il2cpp::il2cpp_type* type);
        static void destroy(object* obj, float t = 0.f);
        static void destroy_immediate(object* obj, bool destroy_assets = false);

    private:
        using instantiate_t = object * (*)(object*);
        inline static instantiate_t instantiate_func_ = nullptr;

        using instantiate_set_parent_t = object * (*)(object*, transform*, bool);
        inline static instantiate_set_parent_t instantiate_set_parent_func_ = nullptr;

        using get_name_t = il2cpp::il2cpp_string* (*)(object*);
        inline static get_name_t get_name_func_ = nullptr;

        using set_name_t = void(*)(object*, il2cpp::il2cpp_string*);
        inline static set_name_t set_name_func_ = nullptr;

        using unload_unused_assets_t = il2cpp::il2cpp_object* (*)();
        inline static unload_unused_assets_t unload_unused_assets_func_ = nullptr;

        using find_objects_of_type_all_t = il2cpp::il2cpp_array* (*)(il2cpp::il2cpp_type*);
        inline static find_objects_of_type_all_t find_objects_of_type_all_func_ = nullptr;

        using find_objects_of_type_t = il2cpp::il2cpp_array*(*)(il2cpp::il2cpp_type*);
        inline static find_objects_of_type_t find_objects_of_type_func_ = nullptr;

        using destroy_t = void* (*)(object*, float);
        inline static destroy_t destroy_func_ = nullptr;

        using destroy_immediate_t = void* (*)(object*, bool);
        inline static destroy_immediate_t destroy_immediate_func_ = nullptr;
    };

    struct unity_engine_object_static_fields {
        std::int32_t offset_of_instance_id_in_c_plus_plus_object;
    };
}

struct object_array
{
};
