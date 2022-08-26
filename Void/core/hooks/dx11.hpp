#pragma once
#include "../../dependencies/kiero/kiero.h"
#include "../assembler/unityengine/screen.hpp"
#include "../menu.hpp"

namespace dx11_hook
{
	enum class vtable : std::int32_t
    {
        present = 8,
        resize_buffers = 13
    };

    using present = HRESULT(__stdcall*)(IDXGISwapChain*, UINT, UINT);
    using resizebuffers = HRESULT(__stdcall*)(IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT);

    inline present o_present;
    inline resizebuffers o_resizebuffers;

    inline ID3D11Device* p_device = nullptr;
    inline ID3D11DeviceContext* p_context = nullptr;
    inline ID3D11RenderTargetView* main_render_target_view = nullptr;
    inline assembler::il2cpp::il2cpp_thread* current_thread = nullptr;
    inline bool initialize_present = false;
    inline float hue = 0.f;

    void render_player();
    LRESULT __stdcall wnd_proc(HWND h_wnd, UINT u_msg, WPARAM w_param, LPARAM l_param);
    HRESULT __stdcall hk_present(IDXGISwapChain* p_swap_chain, UINT sync_interval, UINT flags);
    HRESULT __stdcall hk_resizebuffers(IDXGISwapChain* p_swap_chain, UINT buffer_count, UINT width, UINT height, DXGI_FORMAT new_format, UINT swap_chain_flags);

    kiero::status::Enum init();
    void restore();
}