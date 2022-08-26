/*
 *		assembler/unity_engine/texture_2d.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's Texture2D class
 */

// ReSharper disable CppInconsistentNaming
#pragma once
#include "../../sdk/datatypes/color.h"
#include "../il2cpp/array_wrapper.hpp"
#include "texture.hpp"
#include <array>

namespace assembler::unity_engine
{
    struct texture_2d : texture
    {
		enum class texture_format : std::int32_t
		{
			alpha8 = 1,
			argb4444 = 2,
			rgb24 = 3,
			rgba32 = 4,
			argb32 = 5,
			rgb565 = 7,
			r16 = 9,
			dxt1 = 10,
			dxt5 = 12,
			rgba4444 = 13,
			bgra32 = 14,
			r_half = 15,
			rg_half = 16,
			rgba_half = 17,
			r_float = 18,
			rg_float = 19,
			rgba_float = 20,
			yuy2 = 21,
			rgb9_e5_float = 22,
			bc4 = 26,
			bc5 = 27,
			bc6_h = 24,
			bc7 = 25,
			dxt1_crunched = 28,
			dxt5_crunched = 29,
			pvrtc_rgb2 = 30,
			pvrtc_rgba2 = 31,
			pvrtc_rgb4 = 32,
			pvrtc_rgba4 = 33,
			etc_rgb4 = 34,
			eac_r = 41,
			eac_r_signed = 42,
			eac_rg = 43,
			eac_rg_signed = 44,
			etc2_rgb = 45,
			etc2_rgba1 = 46,
			etc2_rgba8 = 47,
			astc_4x4 = 48,
			astc_5x5 = 49,
			astc_6x6 = 50,
			astc_8x8 = 51,
			astc_10x10 = 52,
			astc_12x12 = 53,
			etc_rgb4_3ds = 60,
			etc_rgba8_3ds = 61,
			rg16 = 62,
			r8 = 63,
			etc_rgb4_crunched = 64,
			etc2_rgba8_crunched = 65,
			astc_hdr_4x4 = 66,
			astc_hdr_5x5 = 67,
			astc_hdr_6x6 = 68,
			astc_hdr_8x8 = 69,
			astc_hdr_10x10 = 70,
			astc_hdr_12x12 = 71,
			rg32 = 72,
			rgb48 = 73,
			rgba64 = 74,
			astc_rgb_4x4 = 48,
			astc_rgb_5x5 = 49,
			astc_rgb_6x6 = 50,
			astc_rgb_8x8 = 51,
			astc_rgb_10x10 = 52,
			astc_rgb_12x12 = 53,
			astc_rgba_4x4 = 54,
			astc_rgba_5x5 = 55,
			astc_rgba_6x6 = 56,
			astc_rgba_8x8 = 57,
			astc_rgba_10x10 = 58,
			astc_rgba_12x12 = 59
		};

        void set_pixel(int32_t x, int32_t y, const sdk::color& c);
        void apply();
        bool load_image(il2cpp::il2cpp_array* arr);

		static il2cpp::il2cpp_type* get_global_type();
        static texture_2d* create_external_texture(std::int32_t width, std::int32_t height, texture_format format, bool mip_chain, bool linear, ID3D11ShaderResourceView* texture);

    private:
		static inline il2cpp::il2cpp_type* type_ = nullptr;

        using set_pixel_t = void* (*)(texture_2d*, int32_t, int32_t, int32_t, std::array<float, 4U>);
        inline static set_pixel_t set_pixel_func_ = nullptr;

        using load_image_t = bool (*)(texture_2d*, il2cpp::il2cpp_array*, bool);
        inline static load_image_t load_image_func_ = nullptr;

        using apply_t = void* (*)(texture_2d*, bool, bool);
        inline static apply_t apply_func_ = nullptr;
    };
}
