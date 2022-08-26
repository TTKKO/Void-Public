/*
 *		assembler/il2cpp/il2cpp.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of il2cpp
 */

// ReSharper disable CppInconsistentNaming
// ReSharper disable once CppInconsistentNaming

#ifndef IL2CPP_HPP
#define IL2CPP_HPP

#pragma once
#include <string>
#include "../../../utilities/memory.hpp"
#include "../../../offsets.hpp"
#include "array_wrapper.hpp"
#include <array>

#define DELCONST(_CLASS) \
    _CLASS() = delete; \
    ~_CLASS() = delete; \
    _CLASS(const _CLASS &) = delete; \
    _CLASS &operator = (const _CLASS &) = delete; \
    _CLASS(_CLASS &&) = delete; \
    _CLASS &operator = (_CLASS &&) = delete

namespace assembler::il2cpp
{
	il2cpp_image* get_corlib();
    void* resolve_icall(const char* sz_text);
    void free(void* src);

    // @note: method_info
    const method_info* fetch_method_info(const il2cpp_class* klass, std::string_view sz_text);
    const method_info* fetch_method_info(const il2cpp_class* klass, std::uint16_t idx);
    void dump_method_info(const il2cpp_class* klass);

    // @note: array
    std::uint32_t array_length(const il2cpp_array* arr);
    std::uint32_t array_get_byte_length(il2cpp_array* arr);
    void array_clear(il2cpp_array* arr, std::size_t idx, std::size_t len);

    template <typename T>
    il2cpp_array_wrapper<T>* array_new(il2cpp_class* klass, const std::size_t len)
    {
        using func_t = il2cpp_array_wrapper<T>* (*)(il2cpp_class*, std::size_t);
        static const auto func = reinterpret_cast<func_t>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_array_new")));
        return func(klass, len);
    }

    // @note: assembly
    il2cpp_image* assembly_get_image(il2cpp_assembly* assm);

    // @note: class
    il2cpp_type* class_enum_basetype(il2cpp_class* klass);
    il2cpp_type* class_get_type(il2cpp_class* klass);
    il2cpp_image* class_get_image(il2cpp_class* klass);
    property_info* class_get_property_from_name(il2cpp_class* klass, const char* sz_text);
    field_info* class_get_field_from_name(il2cpp_object* obj, const char* sz_text);
    il2cpp_object* new_object_from_class(il2cpp_class* obj, bool system_type = false);
    field_info* get_field_by_index(il2cpp_class* klass, std::size_t idx);
    field_info* get_fields(il2cpp_class* klass, void** iter);

    // @note: domain
    il2cpp_domain* current_domain();
    il2cpp_assembly** domain_get_assemblies(il2cpp_domain* dom, std::size_t* size);
    il2cpp_assembly* domain_assembly_open(il2cpp_domain* dom, const char* sz_text);

    // @note: exception
    void raise_exception(il2cpp_exception* e);
    il2cpp_exception* exception_from_name_msg(il2cpp_image* img, const char* sz_namespace, const char* sz_name, const char* sz_message);
    il2cpp_exception* get_exception_argument_null(const char* sz_arg);

    // @note: gc
    void gc_collect(std::int32_t generations);
    std::int64_t gc_get_used_size();
    std::int64_t gc_get_heap_size();

    // @note: field
    il2cpp_type* field_get_type(field_info* field);
    const char* field_get_name(field_info* field);
    il2cpp_object* field_get_value_object(field_info* field, il2cpp_object* obj);
    void field_set_value(il2cpp_object* obj, field_info* field, void* value);
    void field_get_value(il2cpp_object* obj, field_info* field, void* value);
    void field_static_set_value(field_info* field, void* value);
    void field_static_get_value(field_info* field, void* value);
    il2cpp_object* get_field(il2cpp_object* obj, const char* sz_text);
    il2cpp_class* field_get_parent(field_info* field);

    // @note: object
    il2cpp_class* object_get_class(il2cpp_object* obj);
    std::uint32_t object_get_size(il2cpp_object* obj);
    il2cpp_object* object_new(il2cpp_class* klass);
    il2cpp_object* new_object(std::string_view sz_text);
    il2cpp_object* new_object(il2cpp_type* type, bool is_system_object);
    il2cpp_object* new_object_from_object(il2cpp_object* obj, bool is_system_type = false);
    void* object_unbox(il2cpp_object* obj);
    char* get_object_type_name(il2cpp_object* obj);
    il2cpp_object* value_box(std::string_view sz_type, void* data);
    il2cpp_object* value_box_not_system(std::string_view sz_type, void* data);
    il2cpp_type* get_object_type(il2cpp_object* obj);

    // @note: monitor
    void monitor_enter(il2cpp_object* obj);
    void monitor_exit(il2cpp_object* obj);

    // @note: string
    il2cpp_string* string_new(std::wstring_view sz_text);
    il2cpp_string* string_new(std::string_view sz_text);
    std::string s_chars(const il2cpp_string* sz_text);
    std::wstring ws_chars(il2cpp_string* sz_text);
    std::wstring_view wsv_chars(il2cpp_string* sz_text);

    // @note: thread
    il2cpp_thread* thread_attach(il2cpp_domain* dom);
    void thread_detach(il2cpp_thread* t);

    // @note: type:
    il2cpp_class* class_from_system_type(il2cpp_type* t);
    il2cpp_class* class_from_type(il2cpp_type* t);
    il2cpp_type* locate_type(const char* sz_text, std::size_t idx);
    il2cpp_type* get_type(il2cpp_string* sz_text);
    il2cpp_type* get_type(std::wstring_view sz_text);
    il2cpp_type* get_type(std::string_view sz_text);
    std::string type_to_string(il2cpp_type* t);
    char* type_get_name(il2cpp_type* t);
    il2cpp_object* type_get_object(il2cpp_type* t);

    // @note: image
    il2cpp_assembly* image_get_assembly(il2cpp_image* img);
    std::size_t image_get_class_count(il2cpp_image* img);
    il2cpp_class* image_get_class(il2cpp_image* img, std::size_t idx);
    const char* image_get_name(il2cpp_image* img);

    constexpr il2cpp_method_pointer get_vfunc(const il2cpp_class* klass, const std::uint8_t n_index)
    {
        return klass->vtable[n_index].methodPtr;
    }

    constexpr const method_info* get_vmethod(const il2cpp_class* klass, const std::uint8_t n_index)
    {
        return klass->vtable[n_index].method;
    }

    template <typename T, typename ... ArgsT>
    constexpr T call_vfunc(const il2cpp_class* klass, const std::uint8_t n_index, ArgsT ... arg_list)
    {
        using virtual_fn = T(__thiscall*)(decltype(arg_list)..., const method_info*);
        return reinterpret_cast<virtual_fn>(
            klass->vtable[n_index].methodPtr)(arg_list..., klass->vtable[n_index].method
                );
    }

    template <typename T, typename ... ArgsT>
    constexpr T call_mifunc(const method_info* mi, ArgsT ... arg_list)
    {
        using virtual_fn = T(__thiscall*)(decltype(arg_list)..., const method_info*);
        return reinterpret_cast<virtual_fn>(mi->methodPointer)(arg_list..., mi);
    }

    template <typename T, typename ... ArgsT>
    constexpr T call_mifunc(const il2cpp_class* klass, const std::uint16_t n_index, ArgsT ... arg_list)
    {
        using virtual_fn = T(__thiscall*)(decltype(arg_list)..., const method_info*);
        return reinterpret_cast<virtual_fn>(
            klass->_1.methods[n_index]->methodPointer)(arg_list..., klass->_1.methods[n_index]
        );
    }

    template <typename T>
	std::vector<T> array_to_vector(il2cpp_array* arr)
    {
        if (arr == nullptr)
            return {};

        const auto arr_size = array_get_byte_length(arr);
        const auto arr_length = array_length(arr);

        if (arr_length == 0)
            return {};

        const auto arr_elem_size = arr_length ? arr_size / arr_length : 0;
        const auto arr_obj_size = object_get_size(arr) - arr_size;

        try 
        {
            return std::vector<T>(
                reinterpret_cast<T*>(reinterpret_cast<std::uint8_t*>(arr) + arr_obj_size + arr_elem_size * 0),
                reinterpret_cast<T*>(reinterpret_cast<std::uint8_t*>(arr) + arr_obj_size + arr_elem_size * arr_length)
                );
        }
        catch (const std::exception& e)
        {
            logging::push(FOREGROUND_INTENSE_RED);
            logging::print(xorstr_("[critical] {}\n"), e.what());
            logging::pop();
            return {};
        }
    }
}

struct Il2CppExceptionWrapper
{
	assembler::il2cpp::il2cpp_exception* ex;
    explicit Il2CppExceptionWrapper(assembler::il2cpp::il2cpp_exception* ex) : ex(ex) {}
};

#endif
