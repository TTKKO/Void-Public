/*
 *		assembler/unityengine/gl.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's GL class
 */

#pragma once
#include "../common.hpp"
#include "../il2cpp/il2cpp.hpp"
#include "../../sdk/datatypes/color.h"
#include "../../sdk/datatypes/vector.h"

namespace assembler::unity_engine
{
    struct gl
    {
        DELCONST(gl);

        enum begin_mode
        {
            points = 0x0000,
            lines = 0x0001,
            line_loop = 0x0002,
            line_strip = 0x0003,
            triangles = 0x0004,
            triangle_strip = 0x0005,
            triangle_fan = 0x0006,
            quads = 0x0007,
            quad_strip = 0x0008,
            polygon = 0x0009
        };

        static void vertex3(const sdk::vector& vec);
        static void push_matrix();
        static void pop_matrix();
        static void load_ortho();
        static void begin(int32_t mode);
        static void color(const sdk::color& c);
        static void end();

    private:
        using vertex3_t = void(*)(float, float, float);
        inline static vertex3_t vertex3_func_ = nullptr;

        using push_matrix_t = void(*)();
        inline static push_matrix_t push_matrix_func_ = nullptr;

        using pop_matrix_t = void(*)();
        inline static pop_matrix_t pop_matrix_func_ = nullptr;

        using load_ortho_t = void(*)();
        inline static load_ortho_t load_ortho_func_ = nullptr;

        using begin_t = void(*)(int32_t);
        inline static begin_t begin_func_ = nullptr;

        using color_t = void(*)(std::array<float, 4U>);
        inline static color_t color_func_ = nullptr;

        using end_t = void(*)();
        inline static end_t end_func_ = nullptr;
    };
}
