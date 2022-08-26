#pragma once

// @credits: rolraw

#ifndef SDK_INPUT_SYSTEM_HPP
#define SDK_INPUT_SYSTEM_HPP

#include <array>
#include "../hooks/dx11.hpp"

enum class ekey_state : int
{
    none,
    down,
    up,
    released
};

/*
 * INPUT SYSTEM
 * listen and handle key states
 */
namespace input_sys
{
    // Values
    /* last processed key states */

    inline HWND h_window = nullptr;
    inline WNDPROC p_old_wnd_proc = nullptr;

    inline std::array<ekey_state, 256u> arr_key_state = {};

    bool setup(IDXGISwapChain* p_swap_chain);
    bool process(UINT u_msg, WPARAM w_param, LPARAM l_param);
    void restore();

    /* is given key being held */
    inline bool is_key_down(const std::uint32_t u_button_code)
    {
        if (!u_button_code)
            return false;

        return arr_key_state.at(u_button_code) == ekey_state::down;
    }

    /* was given key released */
    inline bool is_key_released(const std::uint32_t u_button_code)
    {
        if (!u_button_code)
            return false;

        if (arr_key_state.at(u_button_code) == ekey_state::released)
        {
            arr_key_state.at(u_button_code) = ekey_state::up;
            return true;
        }

        return false;
    }
}

#endif
