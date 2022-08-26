/*
 *		utilities/drawing.hpp
 *		Void
 *
 *		Credits: rolraw, azurilex
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		DirectX drawing implementation
 */

#pragma once

#ifndef DRAWING_HPP
#define DRAWING_HPP

#include <functional>
#include <deque>
#include <mutex>
#include <shared_mutex>
#include <any>
#include "../core/sdk/datatypes/color.h"

#include "../dependencies/imgui/imgui.h"
#include "../dependencies/imgui/imgui_freetype.h"
#include "../dependencies/imgui/imgui_internal.h"
#include "../dependencies/imgui/imgui_impl_win32.h"
#include "../dependencies/imgui/imgui_impl_dx11.h"

#include "../resources/whitney.h"
#include "../resources/void_logo.h"
#include "../resources/checkmark.h"

#include "../globals.hpp"
#include <format>

namespace byte_resources
{
	// main			13		autohinting
	inline ImFont* whitney;

	// extra		14		bold
	inline ImFont* verdana_small_bold;

	// extra		14		bold
	inline ImFont* verdana_medium_bold;

	// extra		15		autohinting
	inline ImFont* verdana_small;

	// extra		16		autohinting
	inline ImFont* verdana_medium;

	// extra		20		autohinting
	inline ImFont* verdana_big;

	inline ID3D11ShaderResourceView* void_logo;
	inline ID3D11ShaderResourceView* checkmark;
}

namespace ImGui
{
	//@credits: https://github.com/rollraw/qo0-base

	// Main
	void HelpMarker(const char* sz_description);
	bool ListBox(const char* sz_label, int* i_current_item, std::function<const char*(int)> p_lambda, int n_items_count, int i_height_in_items);
	bool HotKey(const char* sz_label, int* p_value);
	bool MultiCombo(const char* sz_label, std::vector<bool>& vec_values, const std::string_view* arr_items, int n_items_count);

	// Wrappers
	bool Combo(const char* sz_label, std::vector<int>& vec_values, int n_index, const char* sz_items_separated_by_zeros, int n_height_in_items = -1);
	bool Checkbox(const char* sz_label, std::vector<bool>& vec_values, std::size_t n_index);
	bool SliderFloat(const char* sz_label, std::vector<float>& vec_values, int n_index, float fl_min, float fl_max, const char* sz_format = "%.3f", float fl_power = 1.0f);
	bool SliderInt(const char* sz_label, std::vector<int>& vec_values, int n_index, int i_min, int i_max, const char* sz_format = "%d");
	bool ColorEdit3(const char* sz_label, sdk::color* p_color, ImGuiColorEditFlags flags);
	bool ColorEdit4(const char* sz_label, sdk::color* p_color, ImGuiColorEditFlags flags);
}

namespace drawing
{
	// @credits: https://github.com/rollraw/qo0-base

	bool setup(ID3D11Device* p_device, ID3D11DeviceContext* p_context, HWND wnd);
	void destroy();
	void set_colors();
	void set_rgb_colors(float hue);

	bool load_image(ID3D11Device* p_device, ID3D11ShaderResourceView** shader_view, const std::uint8_t* data, UINT width, UINT height);

	inline bool initialized = false;
}

#endif
