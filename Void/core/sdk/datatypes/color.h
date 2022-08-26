#pragma once

#ifndef COLOR_SDK_HPP
#define COLOR_SDK_HPP

#include <array>
#include <d3d11.h>
#include <DirectXPackedVector.h>
#include <string>
#include <cmath>
#include "../../../dependencies/imgui/imgui.h"
#include "../hash/xorstr.hpp"

#define D3DCOLOR_ARGB(a,r,g,b) \
	((DWORD)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))

#define HEX_COLOR_RGB(r,g,b) \
	(DWORD)((((r)&0xff) << 16) + (((g) & 0xff) << 8) + ((b) & 0xff));

enum
{
    color_r = 0,
    color_g = 1,
    color_b = 2,
    color_a = 3
};

struct color_rgb_exp32
{
    std::byte r, g, b;
    signed char exponent;
};

namespace sdk
{
    class color
    {
    public:
    	color() = default;

        /* default color constructor (in: 0 - 255) */
        constexpr color(const std::uint8_t r, const std::uint8_t g, const std::uint8_t b, const std::uint8_t a = 255) :
            arr_color_({ r, g, b, a })
        {
        }

        constexpr color(const int r, const int g, const int b, const int a = 255) :
            arr_color_({
                static_cast<std::uint8_t>(r), static_cast<std::uint8_t>(g), static_cast<std::uint8_t>(b),
                static_cast<std::uint8_t>(a)
            })
        {
        }

        /* float color constructor (in: 0.0 - 1.0) */
        constexpr color(const float r, const float g, const float b, const float a = 1.0f) :
            arr_color_({
                static_cast<std::uint8_t>(r * 255.f), static_cast<std::uint8_t>(g * 255.f),
                static_cast<std::uint8_t>(b * 255.f), static_cast<std::uint8_t>(a * 255.f)
            })
        {
        }

        explicit constexpr color(const std::array<float, 4U> c) : arr_color_({
            static_cast<std::uint8_t>(c[color_r] * 255.f), static_cast<std::uint8_t>(c[color_g] * 255.f),
            static_cast<std::uint8_t>(c[color_b] * 255.f), static_cast<std::uint8_t>(c[color_a] * 255.f)
        })
        {
        }

        /* output color to given variables */
        void get(std::uint8_t& r, std::uint8_t& g, std::uint8_t& b, std::uint8_t& a) const
        {
            r = arr_color_.at(color_r);
            g = arr_color_.at(color_g);
            b = arr_color_.at(color_b);
            a = arr_color_.at(color_a);
        }

        /* convert color to directx argb */
        _NODISCARD constexpr DirectX::PackedVector::XMCOLOR get_d3d() const
        {
            return D3DCOLOR_ARGB(arr_color_.at(color_a), arr_color_.at(color_r), arr_color_.at(color_g), arr_color_.at(color_b));
        }

        _NODISCARD std::string get_hex() const
        {
            char hexcol[16];
            snprintf(hexcol, sizeof hexcol, xorstr_("%02x%02x%02x"), arr_color_.at(color_r), arr_color_.at(color_g), arr_color_.at(color_b));
            return { hexcol };
        }

        /* convert color to imgui rgba */
        _NODISCARD ImU32 get_u32(const float fl_alpha_multiplier = 1.0f) const
        {
            return ImGui::GetColorU32(this->get_vec4(fl_alpha_multiplier));
        }

        /* convert color to imgui vector */
        _NODISCARD ImVec4 get_vec4(const float fl_alpha_multiplier = 1.0f) const
        {
            return { this->base<color_r>(), this->base<color_g>(), this->base<color_b>(), this->base<color_a>() * fl_alpha_multiplier };
        }

        constexpr std::uint8_t& operator[](const std::size_t i)
        {
            return this->arr_color_.data()[i];
        }

        constexpr const std::uint8_t& operator[](const std::size_t i) const
        {
            return this->arr_color_.data()[i];
        }

        constexpr bool operator==(const color& col_second) const
        {
        	return this->arr_color_ == col_second.arr_color_;
        }

        constexpr bool operator!=(const color& col_second) const
        {
            return !operator==(col_second);
        }

        color& operator=(const color& col_from)
        {
            arr_color_.at(0) = col_from.arr_color_.at(color_r);
            arr_color_.at(1) = col_from.arr_color_.at(color_g);
            arr_color_.at(2) = col_from.arr_color_.at(color_b);
            arr_color_.at(3) = col_from.arr_color_.at(color_a);
            return *this;
        }

        /* returns certain R/G/B/A value */
        template <std::size_t N>
        _NODISCARD std::uint8_t get() const
        {
            static_assert(N >= color_r && N <= color_a, "given index is out of range");
            return arr_color_[N];
        }

        /* returns copy of color with changed certain R/G/B/A value to given value */
        template <std::size_t N>
        _NODISCARD constexpr color set(const std::uint8_t n_value) const
        {
            static_assert(N >= color_r && N <= color_a, "given index is out of range");

            color col_copy = *this;
            col_copy.arr_color_[N] = n_value;
            return col_copy;
        }

        /* returns copy of color with multiplied certain R/G/B/A value by given value */
        template <std::size_t N>
        _NODISCARD constexpr color multiplier(const float fl_value) const
        {
            static_assert(N >= color_r && N <= color_a, "given index is out of range");

            color col_copy = *this;
            col_copy.arr_color_[N] = static_cast<std::uint8_t>(static_cast<float>(col_copy.arr_color_[N]) * fl_value);
            return col_copy;
        }

        /* returns copy of color with divided certain R/G/B/A value by given value */
        template <std::size_t N>
        _NODISCARD constexpr color divider(const int i_value) const
        {
            static_assert(N >= color_r && N <= color_a, "given index is out of range");

            color col_copy = *this;
            col_copy.arr_color_[N] /= i_value;
            return col_copy;
        }

        /* returns certain R/G/B/A float value (in: 0 - 255, out: 0.0 - 1.0) */
        template <std::size_t N>
        _NODISCARD constexpr float base() const
        {
            static_assert(N >= color_r && N <= color_a, "given index is out of range");
            return arr_color_[N] / 255.f;
        }

        /* convert color to float array (in: 0 - 255, out: 0.0 - 1.0) */
        _NODISCARD constexpr std::array<float, 3U> base() const
        {
            std::array<float, 3U> arr_base_color = {};
            arr_base_color.at(color_r) = this->base<color_r>();
            arr_base_color.at(color_g) = this->base<color_g>();
            arr_base_color.at(color_b) = this->base<color_b>();
            return arr_base_color;
        }

        /* set color from float array (in: 0.0 - 1.0, out: 0 - 255) */
        static constexpr color from_base3(float arr_base[3])
        {
            return { arr_base[0], arr_base[1], arr_base[2] };
        }

        /* convert color to float array w/ alpha (in: 0 - 255, out: 0.0 - 1.0) */
        _NODISCARD constexpr std::array<float, 4U> base_alpha() const
        {
            std::array<float, 4U> arr_base_color = {};
            arr_base_color.at(color_r) = this->base<color_r>();
            arr_base_color.at(color_g) = this->base<color_g>();
            arr_base_color.at(color_b) = this->base<color_b>();
            arr_base_color.at(color_a) = this->base<color_a>();
            return arr_base_color;
        }

        /* set color from float array w/ alpha (in: 0.0 - 1.0, out: 0 - 255) */
        static constexpr color from_base4(float arr_base[4])
        {
            return {arr_base[0], arr_base[1], arr_base[2], arr_base[3]};
        }

        _NODISCARD float hue() const
        {
            if (arr_color_.at(color_r) == arr_color_.at(color_g) && arr_color_.at(color_g) == arr_color_.at(color_b))
                return 0.f;

            const float r = this->base<color_r>();
            const float g = this->base<color_g>();
            const float b = this->base<color_b>();

            const float fl_max = std::max(r, std::max(g, b));
            const float fl_min = std::min(r, std::min(g, b));

            if (fl_max == fl_min)
                return 0.f;

            const float fl_delta = fl_max - fl_min;
            float fl_hue = 0.f;

            if (fl_max == r)
                fl_hue = (g - b) / fl_delta;
            else if (fl_max == g)
                fl_hue = 2.f + (b - r) / fl_delta;
            else if (fl_max == b)
                fl_hue = 4.f + (r - g) / fl_delta;

            fl_hue *= 60.f;

            if (fl_hue < 0.f)
                fl_hue += 360.f;

            return fl_hue / 360.f;
        }

        _NODISCARD float saturation() const
        {
            const float r = this->base<color_r>();
            const float g = this->base<color_g>();
            const float b = this->base<color_b>();

            const float fl_max = std::max(r, std::max(g, b)), flMin = std::min(r, std::min(g, b));
            const float fl_delta = fl_max - flMin;

            if (fl_max == 0.f)
                return fl_delta;

            return fl_delta / fl_max;
        }

        _NODISCARD float brightness() const
        {
            const float r = this->base<color_r>();
            const float g = this->base<color_g>();
            const float b = this->base<color_b>();

            return std::max(r, std::max(g, b));
        }

        /* return RGB color converted from HSB/HSV color */
        static color from_hsb(const float fl_hue, const float fl_saturation, const float fl_brightness)
        {
            const float h = std::fmodf(fl_hue, 1.0f) / (60.0f / 360.0f);
            const int i = static_cast<int>(h);
            const float f = h - static_cast<float>(i);
            const float p = fl_brightness * (1.0f - fl_saturation);
            const float q = fl_brightness * (1.0f - fl_saturation * f);
            const float t = fl_brightness * (1.0f - fl_saturation * (1.0f - f));

            float r, g, b;

            switch (i)
            {
            case 0:
                r = fl_brightness, g = t, b = p;
                break;
            case 1:
                r = q, g = fl_brightness, b = p;
                break;
            case 2:
                r = p, g = fl_brightness, b = t;
                break;
            case 3:
                r = p, g = q, b = fl_brightness;
                break;
            case 4:
                r = t, g = p, b = fl_brightness;
                break;
            case 5:
            default:
                r = fl_brightness, g = p, b = q;
                break;
            }

            return { r, g, b };
        }

    private:
        std::array<std::uint8_t, 4U> arr_color_;
    };
}

#endif
