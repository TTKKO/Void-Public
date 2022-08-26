/*
 *		assembler/unityengine/gui.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's Gui class
 */

#pragma once
#include "../common.hpp"
#include "../il2cpp/il2cpp.hpp"
#include "rect.hpp"
#include "texture_2d.hpp"
#include "../../sdk/datatypes/color.h"
#include "../../sdk/datatypes/matrix.hpp"

namespace assembler::unity_engine
{
    struct texture_2d;

    struct gui
    {
        DELCONST(gui);

        static void set_color(const sdk::color& c);
        static sdk::color get_color();
        static sdk::matrix get_matrix();
        static void set_matrix(const sdk::matrix& m);

    private:
        using set_color_t = void (*)(std::array<float, 4U>);
        inline static set_color_t set_color_func_ = nullptr;

        using get_color_t = void (*)(std::array<float, 4U>*);
        inline static get_color_t get_color_func_ = nullptr;

        using get_matrix_t = void (*)(sdk::matrix*);
        inline static get_matrix_t get_matrix_func_ = nullptr;

        using set_matrix_t = void(*)(const sdk::matrix&);
        inline static set_matrix_t set_matrix_func_ = nullptr;
    };
}