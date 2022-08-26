#include "input_system.hpp"
#include <dxgi.h>

bool input_sys::setup(IDXGISwapChain* p_swap_chain)
{
    // VMProtectBeginMutation("InputSystem");

    DXGI_SWAP_CHAIN_DESC sd;
    p_swap_chain->GetDesc(&sd);
    h_window = sd.OutputWindow;

    if (h_window == nullptr)
        return false;

    p_old_wnd_proc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(h_window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(dx11_hook::wnd_proc)));

    if (p_old_wnd_proc == nullptr)
        return false;

    // VMProtectEnd();

    return true;
}

bool input_sys::process(const UINT u_msg, const WPARAM w_param, LPARAM l_param)
{
    // prevent process when e.g. binding something in-menu
    if (menu_window::mainmenu_opened && w_param != config::get<int>(g_context.menu_key))
        return false;

    // current active key
    int n_key = 0;
    // current active key state
    auto state = ekey_state::none;

    switch (u_msg)
    {
    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
        if (w_param < 256U)
        {
            n_key = w_param;
            state = ekey_state::down;
        }
        break;
    case WM_KEYUP:
    case WM_SYSKEYUP:
        if (w_param < 256U)
        {
            n_key = w_param;
            state = ekey_state::up;
        }
        break;
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_LBUTTONDBLCLK:
        n_key = VK_LBUTTON;
        state = u_msg == WM_LBUTTONUP ? ekey_state::up : ekey_state::down;
        break;
    case WM_RBUTTONDOWN:
    case WM_RBUTTONUP:
    case WM_RBUTTONDBLCLK:
        n_key = VK_RBUTTON;
        state = u_msg == WM_RBUTTONUP ? ekey_state::up : ekey_state::down;
        break;
    case WM_MBUTTONDOWN:
    case WM_MBUTTONUP:
    case WM_MBUTTONDBLCLK:
        n_key = VK_MBUTTON;
        state = u_msg == WM_MBUTTONUP ? ekey_state::up : ekey_state::down;
        break;
    case WM_XBUTTONDOWN:
    case WM_XBUTTONUP:
    case WM_XBUTTONDBLCLK:
        n_key = GET_XBUTTON_WPARAM(w_param) == XBUTTON1 ? VK_XBUTTON1 : VK_XBUTTON2;
        state = u_msg == WM_XBUTTONUP ? ekey_state::up : ekey_state::down;
        break;
    default:
        return false;
    }

    // save key states

    if (state == ekey_state::up && arr_key_state.at(n_key) == ekey_state::down)
        // if swap states it will be pressed state
        arr_key_state.at(n_key) = ekey_state::released;
    else
        arr_key_state.at(n_key) = state;

    return true;
}

void input_sys::restore()
{
    if (p_old_wnd_proc != nullptr)
    {
        SetWindowLongPtrW(h_window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(p_old_wnd_proc));
        p_old_wnd_proc = nullptr;
    }
}
