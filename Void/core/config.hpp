#pragma once
#include <any>
#include <filesystem>
#include <deque>
#include <vector>
#include "sdk/datatypes/color.h"
#include "sdk/hash/fnv1a.h"
#include "../utilities/utilities.hpp"

#include <ShlObj.h>
#include <json.hpp>

#pragma region config_definitions
#define C_ADD_VARIABLE( Type, szName, pDefault ) const std::uint32_t szName = config::add_variable<Type>(sdk::hash::fnv1a::hash_const(#szName), sdk::hash::fnv1a::hash_const(#Type), pDefault);
#define C_ADD_VARIABLE_VECTOR( Type, uSize, szName, pDefault ) const std::uint32_t szName = config::add_variable<std::vector<Type>>(sdk::hash::fnv1a::hash_const(#szName), sdk::hash::fnv1a::hash_const("std::vector<" #Type ">"), memory::get_filled_vector<Type, uSize>(pDefault));
#define C_INVALID_VARIABLE (std::size_t)(-1)
#pragma endregion

struct variable_object_t
{
    variable_object_t(const sdk::hash::fnv1a_t u_name_hash, const sdk::hash::fnv1a_t u_type_hash, std::any&& p_default) : u_name_hash(u_name_hash), u_type_hash(u_type_hash), p_value(std::move(p_default))
    {
    }

    ~variable_object_t() = default;

    /* get casted variable value */
    template <typename T>
    T& get()
    {
        return *static_cast<T*>(std::any_cast<T>(&p_value));
    }

    /* emplace casted variable value */
    template <typename T>
    void set(T value)
    {
        p_value.emplace<T>(value);
    }

    sdk::hash::fnv1a_t u_name_hash = 0x0;
    sdk::hash::fnv1a_t u_type_hash = 0x0;
    std::any p_value = {};
};

/*
 * CONFIGURATION
 * cheat variables file control (save/load/remove)
 */
namespace config // @credits: ducarii
{
    // Main
    /* create directories, create and load default config */
    bool setup(std::string_view sz_default_file_name);
    bool save(std::string_view sz_file_name);
    bool load(std::string_view sz_file_name);

    bool update_instance_history(std::string_view world_name, std::string_view instance);
    bool read_instance_history(std::vector<std::string>& vec);

    bool toggle_autoload();
    void remove(std::size_t n_index);
    void refresh();

    // Get
    std::size_t get_variable_index(sdk::hash::fnv1a_t u_name_hash);
    std::filesystem::path get_working_path();

    // Values
    const std::filesystem::path fs_path = get_working_path() / xorstr_("settings");
    inline std::deque<std::string> vec_file_names = {};
    inline std::vector<variable_object_t> vec_variables = {};

    // Templates
    /* returns casted variable value at given index */
    template <typename T>
    T& get(const std::uint32_t n_index)
    {
        return vec_variables.at(n_index).get<T>();
    }

    /* add new configuration variable to massive, and return index of it */
    template <typename T>
    constexpr std::uint32_t add_variable(const sdk::hash::fnv1a_t u_name_hash, const sdk::hash::fnv1a_t u_type_hash, const T p_default)
    {
        vec_variables.emplace_back(u_name_hash, u_type_hash, std::make_any<T>(p_default));
        return static_cast<std::uint32_t>(vec_variables.size()) - 1u;
    }
}
