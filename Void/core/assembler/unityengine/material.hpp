/*
 *		assembler/unityengine/material.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's Material class
 */

#pragma once
#include "../common.hpp"
#include "../../sdk/datatypes/color.h"

namespace assembler::unity_engine
{
    struct texture;
    struct shader;

    struct material : object
    {
        void set_color(std::string_view name, const sdk::color& value);
        void set_pass(int32_t p);
        shader* get_shader();
        int32_t get_first_property_name_id_by_atrribute(int32_t value);
        void set_maintexture(texture* tex);
        void set_shader(shader* s);

    private:
        using set_color_t = void(*)(material*, int32_t, std::array<float, 4U>);
        inline static set_color_t set_color_func_ = nullptr;

        using set_pass_t = void (*)(material*, int32_t);
        inline static set_pass_t set_pass_func_ = nullptr;

        using get_shader_t = shader * (*)(material*);
        inline static get_shader_t get_shader_func_ = nullptr;

        using get_first_property_name_id_by_atrribute_t = int32_t(*)(material*, int32_t);
        inline static get_first_property_name_id_by_atrribute_t get_first_property_name_id_by_atrribute_func_ = nullptr;

        using set_maintexture_t = void(*)(material*, uint32_t, texture*);
        inline static set_maintexture_t set_maintexture_func_ = nullptr;

        using set_shader_t = void (*)(material*, shader*);
        inline static set_shader_t set_shader_func_ = nullptr;
    };
}
