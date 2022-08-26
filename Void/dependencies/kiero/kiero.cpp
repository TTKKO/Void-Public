#include "kiero.h"
#include "../../core/sdk/hash/xorstr.hpp"
#include <cassert>

#if KIERO_INCLUDE_D3D9
# include <d3d9.h>
#endif

#if KIERO_INCLUDE_D3D10
# include <dxgi.h>
# include <d3d10_1.h>
# include <d3d10.h>
#endif

#if KIERO_INCLUDE_D3D11
# include <dxgi.h>
# include <d3d11.h>
#endif

#if KIERO_INCLUDE_D3D12
# include <dxgi.h>
# include <d3d12.h>
#endif

#if KIERO_INCLUDE_OPENGL
# include <gl/GL.h>
#endif

#if KIERO_INCLUDE_VULKAN
# include <vulkan/vulkan.h>
#endif

#if KIERO_USE_MINHOOK
#include <MinHook.h>
#endif

#ifdef _UNICODE
# define KIERO_TEXT(text) xorstr_(L##text)
#else
# define KIERO_TEXT(text) xorstr_(text)
#endif

#define KIERO_ARRAY_SIZE(arr) ((size_t)(sizeof(arr)/sizeof(arr[0])))

static kiero::render_type::Enum g_render_type = kiero::render_type::none;
static uint150_t* g_methods_table = nullptr;

kiero::status::Enum kiero::init(const render_type::Enum render_type)
{
    if (g_render_type != render_type::none)
    {
        return status::already_initialized_error;
    }

    if (render_type != render_type::none)
    {
        if (render_type >= render_type::d3d9 && render_type <= render_type::d3d12)
        {
            WNDCLASSEX window_class;
            window_class.cbSize = sizeof(WNDCLASSEX);
            window_class.style = CS_HREDRAW | CS_VREDRAW;
            window_class.lpfnWndProc = DefWindowProc;
            window_class.cbClsExtra = 0;
            window_class.cbWndExtra = 0;
            window_class.hInstance = GetModuleHandle(nullptr);
            window_class.hIcon = nullptr;
            window_class.hCursor = nullptr;
            window_class.hbrBackground = nullptr;
            window_class.lpszMenuName = nullptr;
            window_class.lpszClassName = KIERO_TEXT("Kiero");
            window_class.hIconSm = nullptr;

            ::RegisterClassEx(&window_class);

            HWND window = ::CreateWindow(window_class.lpszClassName, KIERO_TEXT("Kiero DirectX Window"), WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, NULL, NULL, window_class.hInstance, NULL);

            if (render_type == render_type::d3d9)
            {
#if KIERO_INCLUDE_D3D9
				HMODULE libD3D9;
				if ((libD3D9 = ::GetModuleHandle(KIERO_TEXT("d3d9.dll"))) == NULL)
				{
					::DestroyWindow(window);
					::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
					return Status::ModuleNotFoundError;
				}

				void* Direct3DCreate9;
				if ((Direct3DCreate9 = ::GetProcAddress(libD3D9, "Direct3DCreate9")) == NULL)
				{
					::DestroyWindow(window);
					::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
					return Status::UnknownError;
				}

				LPDIRECT3D9 direct3D9;
				if ((direct3D9 = ((LPDIRECT3D9(__stdcall*)(uint32_t))(Direct3DCreate9))(D3D_SDK_VERSION)) == NULL)
				{
					::DestroyWindow(window);
					::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
					return Status::UnknownError;
				}

				D3DPRESENT_PARAMETERS params;
				params.BackBufferWidth = 0;
				params.BackBufferHeight = 0;
				params.BackBufferFormat = D3DFMT_UNKNOWN;
				params.BackBufferCount = 0;
				params.MultiSampleType = D3DMULTISAMPLE_NONE;
				params.MultiSampleQuality = NULL;
				params.SwapEffect = D3DSWAPEFFECT_DISCARD;
				params.hDeviceWindow = window;
				params.Windowed = 1;
				params.EnableAutoDepthStencil = 0;
				params.AutoDepthStencilFormat = D3DFMT_UNKNOWN;
				params.Flags = NULL;
				params.FullScreen_RefreshRateInHz = 0;
				params.PresentationInterval = 0;

				LPDIRECT3DDEVICE9 device;
				if (direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_NULLREF, window, D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_DISABLE_DRIVER_MANAGEMENT, &params, &device) < 0)
				{
					direct3D9->Release();
					::DestroyWindow(window);
					::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
					return Status::UnknownError;
				}

				g_methodsTable = (uint150_t*)::calloc(119, sizeof(uint150_t));
				::memcpy(g_methodsTable, *(uint150_t**)device, 119 * sizeof(uint150_t));

#if KIERO_USE_MINHOOK
				MH_Initialize();
#endif

				device->Release();
				device = NULL;

				direct3D9->Release();
				direct3D9 = NULL;

				g_renderType = RenderType::d3d9;

				::DestroyWindow(window);
				::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);

				return Status::Success;
#endif
            }
            else if (render_type == render_type::d3d10)
            {
#if KIERO_INCLUDE_D3D10
				HMODULE libDXGI;
				HMODULE libD3D10;
				if ((libDXGI = ::GetModuleHandle(KIERO_TEXT("dxgi.dll"))) == NULL || (libD3D10 = ::GetModuleHandle(KIERO_TEXT("d3d10.dll"))) == NULL)
				{
					::DestroyWindow(window);
					::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
					return Status::ModuleNotFoundError;
				}

				void* CreateDXGIFactory;
				if ((CreateDXGIFactory = ::GetProcAddress(libDXGI, "CreateDXGIFactory")) == NULL)
				{
					::DestroyWindow(window);
					::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
					return Status::UnknownError;
				}

				IDXGIFactory* factory;
				if (((long(__stdcall*)(const IID&, void**))(CreateDXGIFactory))(__uuidof(IDXGIFactory), (void**)&factory) < 0)
				{
					::DestroyWindow(window);
					::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
					return Status::UnknownError;
				}

				IDXGIAdapter* adapter;
				if (factory->EnumAdapters(0, &adapter) == DXGI_ERROR_NOT_FOUND)
				{
					::DestroyWindow(window);
					::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
					return Status::UnknownError;
				}

				void* D3D10CreateDeviceAndSwapChain;
				if ((D3D10CreateDeviceAndSwapChain = ::GetProcAddress(libD3D10, "D3D10CreateDeviceAndSwapChain")) == NULL)
				{
					::DestroyWindow(window);
					::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
					return Status::UnknownError;
				}

				DXGI_RATIONAL refreshRate;
				refreshRate.Numerator = 60;
				refreshRate.Denominator = 1;

				DXGI_MODE_DESC bufferDesc;
				bufferDesc.Width = 100;
				bufferDesc.Height = 100;
				bufferDesc.RefreshRate = refreshRate;
				bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
				bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
				bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

				DXGI_SAMPLE_DESC sampleDesc;
				sampleDesc.Count = 1;
				sampleDesc.Quality = 0;

				DXGI_SWAP_CHAIN_DESC swapChainDesc;
				swapChainDesc.BufferDesc = bufferDesc;
				swapChainDesc.SampleDesc = sampleDesc;
				swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
				swapChainDesc.BufferCount = 1;
				swapChainDesc.OutputWindow = window;
				swapChainDesc.Windowed = 1;
				swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
				swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

				IDXGISwapChain* swapChain;
				ID3D10Device* device;

				if (((long(__stdcall*)(
					IDXGIAdapter*,
					D3D10_DRIVER_TYPE,
					HMODULE,
					UINT,
					UINT,
					DXGI_SWAP_CHAIN_DESC*,
					IDXGISwapChain**,
					ID3D10Device**))(D3D10CreateDeviceAndSwapChain))(adapter, D3D10_DRIVER_TYPE_HARDWARE, NULL, 0, D3D10_SDK_VERSION, &swapChainDesc, &swapChain, &device) < 0)
				{
					::DestroyWindow(window);
					::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
					return Status::UnknownError;
				}

				g_methodsTable = (uint150_t*)::calloc(116, sizeof(uint150_t));
				::memcpy(g_methodsTable, *(uint150_t**)swapChain, 18 * sizeof(uint150_t));
				::memcpy(g_methodsTable + 18, *(uint150_t**)device, 98 * sizeof(uint150_t));

#if KIERO_USE_MINHOOK
				MH_Initialize();
#endif

				swapChain->Release();
				swapChain = NULL;

				device->Release();
				device = NULL;

				::DestroyWindow(window);
				::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);

				g_renderType = RenderType::d3d10;

				return Status::Success;
#endif
            }
            else if (render_type == render_type::d3d11)
            {
#if KIERO_INCLUDE_D3D11
            	D3D_FEATURE_LEVEL feature_level;
                constexpr D3D_FEATURE_LEVEL feature_levels[] = {D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_11_0};

                DXGI_RATIONAL refresh_rate;
                refresh_rate.Numerator = 60;
                refresh_rate.Denominator = 1;

                DXGI_MODE_DESC buffer_desc;
                buffer_desc.Width = 100;
                buffer_desc.Height = 100;
                buffer_desc.RefreshRate = refresh_rate;
                buffer_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
                buffer_desc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
                buffer_desc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

                DXGI_SAMPLE_DESC sample_desc;
                sample_desc.Count = 1;
                sample_desc.Quality = 0;

                DXGI_SWAP_CHAIN_DESC swap_chain_desc;
                swap_chain_desc.BufferDesc = buffer_desc;
                swap_chain_desc.SampleDesc = sample_desc;
                swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
                swap_chain_desc.BufferCount = 1;
                swap_chain_desc.OutputWindow = window;
                swap_chain_desc.Windowed = 1;
                swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
                swap_chain_desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

                IDXGISwapChain* swap_chain;
                ID3D11Device* device;
                ID3D11DeviceContext* context;

				HMODULE lib_d3d11;
				if ((lib_d3d11 = ::GetModuleHandle(KIERO_TEXT("d3d11.dll"))) == nullptr)
				{
					DestroyWindow(window);
					::UnregisterClass(window_class.lpszClassName, window_class.hInstance);
					return status::module_not_found_error;
				}

				void* D3D11CreateDeviceAndSwapChain;
				if ((D3D11CreateDeviceAndSwapChain = GetProcAddress(lib_d3d11, xorstr_("D3D11CreateDeviceAndSwapChain"))) == nullptr)
				{
					DestroyWindow(window);
					::UnregisterClass(window_class.lpszClassName, window_class.hInstance);
					return status::unknown_error;
				}

				if (static_cast<long(*)(IDXGIAdapter*, D3D_DRIVER_TYPE, HMODULE, UINT, const D3D_FEATURE_LEVEL*, UINT, UINT, const DXGI_SWAP_CHAIN_DESC*, IDXGISwapChain**, ID3D11Device**, D3D_FEATURE_LEVEL*, ID3D11DeviceContext**)>(
					D3D11CreateDeviceAndSwapChain)(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, feature_levels, 2, D3D11_SDK_VERSION, &swap_chain_desc, &swap_chain, &device, &feature_level, &context) < 0)
				{
					DestroyWindow(window);
					::UnregisterClass(window_class.lpszClassName, window_class.hInstance);
					return status::unknown_error;
				}

                g_methods_table = static_cast<uint150_t*>(calloc(205, sizeof(uint150_t)));
                memcpy(g_methods_table, *reinterpret_cast<uint150_t**>(swap_chain), 18 * sizeof(uint150_t));
                memcpy(g_methods_table + 18, *reinterpret_cast<uint150_t**>(device), 43 * sizeof(uint150_t));
                memcpy(g_methods_table + 18 + 43, *reinterpret_cast<uint150_t**>(context), 144 * sizeof(uint150_t));

#if KIERO_USE_MINHOOK
                MH_Initialize();
#endif

                swap_chain->Release();
                swap_chain = nullptr;

                device->Release();
                device = nullptr;

                context->Release();
                context = nullptr;

                DestroyWindow(window);
                ::UnregisterClass(window_class.lpszClassName, window_class.hInstance);

                g_render_type = render_type::d3d11;

                return status::success;
#endif
            }
            else if (render_type == render_type::d3d12)
            {
#if KIERO_INCLUDE_D3D12
				HMODULE libDXGI;
				HMODULE libD3D12;
				if ((libDXGI = ::GetModuleHandle(KIERO_TEXT("dxgi.dll"))) == NULL || (libD3D12 = ::GetModuleHandle(KIERO_TEXT("d3d12.dll"))) == NULL)
				{
					::DestroyWindow(window);
					::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
					return Status::ModuleNotFoundError;
				}

				void* CreateDXGIFactory;
				if ((CreateDXGIFactory = ::GetProcAddress(libDXGI, "CreateDXGIFactory")) == NULL)
				{
					::DestroyWindow(window);
					::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
					return Status::UnknownError;
				}

				IDXGIFactory* factory;
				if (((long(__stdcall*)(const IID&, void**))(CreateDXGIFactory))(__uuidof(IDXGIFactory), (void**)&factory) < 0)
				{
					::DestroyWindow(window);
					::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
					return Status::UnknownError;
				}

				IDXGIAdapter* adapter;
				if (factory->EnumAdapters(0, &adapter) == DXGI_ERROR_NOT_FOUND)
				{
					::DestroyWindow(window);
					::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
					return Status::UnknownError;
				}

				void* D3D12CreateDevice;
				if ((D3D12CreateDevice = ::GetProcAddress(libD3D12, "D3D12CreateDevice")) == NULL)
				{
					::DestroyWindow(window);
					::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
					return Status::UnknownError;
				}

				ID3D12Device* device;
				if (((long(__stdcall*)(IUnknown*, D3D_FEATURE_LEVEL, const IID&, void**))(D3D12CreateDevice))(adapter, D3D_FEATURE_LEVEL_11_0, __uuidof(ID3D12Device), (void**)&device) < 0)
				{
					::DestroyWindow(window);
					::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
					return Status::UnknownError;
				}

				D3D12_COMMAND_QUEUE_DESC queueDesc;
				queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
				queueDesc.Priority = 0;
				queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
				queueDesc.NodeMask = 0;

				ID3D12CommandQueue* commandQueue;
				if (device->CreateCommandQueue(&queueDesc, __uuidof(ID3D12CommandQueue), (void**)&commandQueue) < 0)
				{
					::DestroyWindow(window);
					::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
					return Status::UnknownError;
				}

				ID3D12CommandAllocator* commandAllocator;
				if (device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator), (void**)&commandAllocator) < 0)
				{
					::DestroyWindow(window);
					::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
					return Status::UnknownError;
				}

				ID3D12GraphicsCommandList* commandList;
				if (device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator, NULL, __uuidof(ID3D12GraphicsCommandList), (void**)&commandList) < 0)
				{
					::DestroyWindow(window);
					::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
					return Status::UnknownError;
				}

				DXGI_RATIONAL refreshRate;
				refreshRate.Numerator = 60;
				refreshRate.Denominator = 1;

				DXGI_MODE_DESC bufferDesc;
				bufferDesc.Width = 100;
				bufferDesc.Height = 100;
				bufferDesc.RefreshRate = refreshRate;
				bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
				bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
				bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

				DXGI_SAMPLE_DESC sampleDesc;
				sampleDesc.Count = 1;
				sampleDesc.Quality = 0;

				DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
				swapChainDesc.BufferDesc = bufferDesc;
				swapChainDesc.SampleDesc = sampleDesc;
				swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
				swapChainDesc.BufferCount = 2;
				swapChainDesc.OutputWindow = window;
				swapChainDesc.Windowed = 1;
				swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
				swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

				IDXGISwapChain* swapChain;
				if (factory->CreateSwapChain(commandQueue, &swapChainDesc, &swapChain) < 0)
				{
					::DestroyWindow(window);
					::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
					return Status::UnknownError;
				}

				g_methodsTable = (uint150_t*)::calloc(150, sizeof(uint150_t));
				::memcpy(g_methodsTable, *(uint150_t**)device, 44 * sizeof(uint150_t));
				::memcpy(g_methodsTable + 44, *(uint150_t**)commandQueue, 19 * sizeof(uint150_t));
				::memcpy(g_methodsTable + 44 + 19, *(uint150_t**)commandAllocator, 9 * sizeof(uint150_t));
				::memcpy(g_methodsTable + 44 + 19 + 9, *(uint150_t**)commandList, 60 * sizeof(uint150_t));
				::memcpy(g_methodsTable + 44 + 19 + 9 + 60, *(uint150_t**)swapChain, 18 * sizeof(uint150_t));

#if KIERO_USE_MINHOOK
				MH_Initialize();
#endif

				device->Release();
				device = NULL;

				commandQueue->Release();
				commandQueue = NULL;

				commandAllocator->Release();
				commandAllocator = NULL;

				commandList->Release();
				commandList = NULL;

				swapChain->Release();
				swapChain = NULL;

				::DestroyWindow(window);
				::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);

				g_renderType = RenderType::d3d12;

				return Status::Success;
#endif
            }

            DestroyWindow(window);
            ::UnregisterClass(window_class.lpszClassName, window_class.hInstance);

            return status::not_supported_error;
        }
        if (render_type != render_type::Auto)
        {
            if (render_type == render_type::opengl)
            {
#if KIERO_INCLUDE_OPENGL
				HMODULE libOpenGL32;
				if ((libOpenGL32 = ::GetModuleHandle(KIERO_TEXT("opengl32.dll"))) == NULL)
				{
					return status::module_not_found_error;
				}

				const char* const methodsNames[] = {
					"glAccum", "glAlphaFunc", "glAreTexturesResident", "glArrayElement", "glBegin", "glBindTexture", "glBitmap", "glBlendFunc", "glCallList", "glCallLists", "glClear", "glClearAccum",
					"glClearColor", "glClearDepth", "glClearIndex", "glClearStencil", "glClipPlane", "glColor3b", "glColor3bv", "glColor3d", "glColor3dv", "glColor3f", "glColor3fv", "glColor3i", "glColor3iv",
					"glColor3s", "glColor3sv", "glColor3ub", "glColor3ubv", "glColor3ui", "glColor3uiv", "glColor3us", "glColor3usv", "glColor4b", "glColor4bv", "glColor4d", "glColor4dv", "glColor4f",
					"glColor4fv", "glColor4i", "glColor4iv", "glColor4s", "glColor4sv", "glColor4ub", "glColor4ubv", "glColor4ui", "glColor4uiv", "glColor4us", "glColor4usv", "glColorMask", "glColorMaterial",
					"glColorPointer", "glCopyPixels", "glCopyTexImage1D", "glCopyTexImage2D", "glCopyTexSubImage1D", "glCopyTexSubImage2D", "glCullFaceglCullFace", "glDeleteLists", "glDeleteTextures",
					"glDepthFunc", "glDepthMask", "glDepthRange", "glDisable", "glDisableClientState", "glDrawArrays", "glDrawBuffer", "glDrawElements", "glDrawPixels", "glEdgeFlag", "glEdgeFlagPointer",
					"glEdgeFlagv", "glEnable", "glEnableClientState", "glEnd", "glEndList", "glEvalCoord1d", "glEvalCoord1dv", "glEvalCoord1f", "glEvalCoord1fv", "glEvalCoord2d", "glEvalCoord2dv",
					"glEvalCoord2f", "glEvalCoord2fv", "glEvalMesh1", "glEvalMesh2", "glEvalPoint1", "glEvalPoint2", "glFeedbackBuffer", "glFinish", "glFlush", "glFogf", "glFogfv", "glFogi", "glFogiv",
					"glFrontFace", "glFrustum", "glGenLists", "glGenTextures", "glGetBooleanv", "glGetClipPlane", "glGetDoublev", "glGetError", "glGetFloatv", "glGetIntegerv", "glGetLightfv", "glGetLightiv",
					"glGetMapdv", "glGetMapfv", "glGetMapiv", "glGetMaterialfv", "glGetMaterialiv", "glGetPixelMapfv", "glGetPixelMapuiv", "glGetPixelMapusv", "glGetPointerv", "glGetPolygonStipple",
					"glGetString", "glGetTexEnvfv", "glGetTexEnviv", "glGetTexGendv", "glGetTexGenfv", "glGetTexGeniv", "glGetTexImage", "glGetTexLevelParameterfv", "glGetTexLevelParameteriv",
					"glGetTexParameterfv", "glGetTexParameteriv", "glHint", "glIndexMask", "glIndexPointer", "glIndexd", "glIndexdv", "glIndexf", "glIndexfv", "glIndexi", "glIndexiv", "glIndexs", "glIndexsv",
					"glIndexub", "glIndexubv", "glInitNames", "glInterleavedArrays", "glIsEnabled", "glIsList", "glIsTexture", "glLightModelf", "glLightModelfv", "glLightModeli", "glLightModeliv", "glLightf",
					"glLightfv", "glLighti", "glLightiv", "glLineStipple", "glLineWidth", "glListBase", "glLoadIdentity", "glLoadMatrixd", "glLoadMatrixf", "glLoadName", "glLogicOp", "glMap1d", "glMap1f",
					"glMap2d", "glMap2f", "glMapGrid1d", "glMapGrid1f", "glMapGrid2d", "glMapGrid2f", "glMaterialf", "glMaterialfv", "glMateriali", "glMaterialiv", "glMatrixMode", "glMultMatrixd",
					"glMultMatrixf", "glNewList", "glNormal3b", "glNormal3bv", "glNormal3d", "glNormal3dv", "glNormal3f", "glNormal3fv", "glNormal3i", "glNormal3iv", "glNormal3s", "glNormal3sv",
					"glNormalPointer", "glOrtho", "glPassThrough", "glPixelMapfv", "glPixelMapuiv", "glPixelMapusv", "glPixelStoref", "glPixelStorei", "glPixelTransferf", "glPixelTransferi", "glPixelZoom",
					"glPointSize", "glPolygonMode", "glPolygonOffset", "glPolygonStipple", "glPopAttrib", "glPopClientAttrib", "glPopMatrix", "glPopName", "glPrioritizeTextures", "glPushAttrib",
					"glPushClientAttrib", "glPushMatrix", "glPushName", "glRasterPos2d", "glRasterPos2dv", "glRasterPos2f", "glRasterPos2fv", "glRasterPos2i", "glRasterPos2iv", "glRasterPos2s",
					"glRasterPos2sv", "glRasterPos3d", "glRasterPos3dv", "glRasterPos3f", "glRasterPos3fv", "glRasterPos3i", "glRasterPos3iv", "glRasterPos3s", "glRasterPos3sv", "glRasterPos4d",
					"glRasterPos4dv", "glRasterPos4f", "glRasterPos4fv", "glRasterPos4i", "glRasterPos4iv", "glRasterPos4s", "glRasterPos4sv", "glReadBuffer", "glReadPixels", "glRectd", "glRectdv", "glRectf",
					"glRectfv", "glRecti", "glRectiv", "glRects", "glRectsv", "glRenderMode", "glRotated", "glRotatef", "glScaled", "glScalef", "glScissor", "glSelectBuffer", "glShadeModel", "glStencilFunc",
					"glStencilMask", "glStencilOp", "glTexCoord1d", "glTexCoord1dv", "glTexCoord1f", "glTexCoord1fv", "glTexCoord1i", "glTexCoord1iv", "glTexCoord1s", "glTexCoord1sv", "glTexCoord2d",
					"glTexCoord2dv", "glTexCoord2f", "glTexCoord2fv", "glTexCoord2i", "glTexCoord2iv", "glTexCoord2s", "glTexCoord2sv", "glTexCoord3d", "glTexCoord3dv", "glTexCoord3f", "glTexCoord3fv",
					"glTexCoord3i", "glTexCoord3iv", "glTexCoord3s", "glTexCoord3sv", "glTexCoord4d", "glTexCoord4dv", "glTexCoord4f", "glTexCoord4fv", "glTexCoord4i", "glTexCoord4iv", "glTexCoord4s",
					"glTexCoord4sv", "glTexCoordPointer", "glTexEnvf", "glTexEnvfv", "glTexEnvi", "glTexEnviv", "glTexGend", "glTexGendv", "glTexGenf", "glTexGenfv", "glTexGeni", "glTexGeniv", "glTexImage1D",
					"glTexImage2D", "glTexParameterf", "glTexParameterfv", "glTexParameteri", "glTexParameteriv", "glTexSubImage1D", "glTexSubImage2D", "glTranslated", "glTranslatef", "glVertex2d",
					"glVertex2dv", "glVertex2f", "glVertex2fv", "glVertex2i", "glVertex2iv", "glVertex2s", "glVertex2sv", "glVertex3d", "glVertex3dv", "glVertex3f", "glVertex3fv", "glVertex3i", "glVertex3iv",
					"glVertex3s", "glVertex3sv", "glVertex4d", "glVertex4dv", "glVertex4f", "glVertex4fv", "glVertex4i", "glVertex4iv", "glVertex4s", "glVertex4sv", "glVertexPointer", "glViewport"
				};

				size_t size = KIERO_ARRAY_SIZE(methodsNames);

				g_methods_table = (uint150_t*)::calloc(size, sizeof(uint150_t));

				for (int i = 0; i < size; i++)
				{
					g_methods_table[i] = (uint150_t)::GetProcAddress(libOpenGL32, methodsNames[i]);
				}

#if KIERO_USE_MINHOOK
				MH_Initialize();
#endif

				g_render_type = render_type::opengl;

				return status::success;
#endif
            }
            else if (render_type == render_type::vulkan)
            {
#if KIERO_INCLUDE_VULKAN
				HMODULE libVulkan;
				if ((libVulkan = GetModuleHandle(KIERO_TEXT("vulkan-1.dll"))) == NULL)
				{
					return Status::ModuleNotFoundError;
				}

				const char* const methodsNames[] = {
					"vkCreateInstance", "vkDestroyInstance", "vkEnumeratePhysicalDevices", "vkGetPhysicalDeviceFeatures", "vkGetPhysicalDeviceFormatProperties", "vkGetPhysicalDeviceImageFormatProperties",
					"vkGetPhysicalDeviceProperties", "vkGetPhysicalDeviceQueueFamilyProperties", "vkGetPhysicalDeviceMemoryProperties", "vkGetInstanceProcAddr", "vkGetDeviceProcAddr", "vkCreateDevice",
					"vkDestroyDevice", "vkEnumerateInstanceExtensionProperties", "vkEnumerateDeviceExtensionProperties", "vkEnumerateDeviceLayerProperties", "vkGetDeviceQueue", "vkQueueSubmit", "vkQueueWaitIdle",
					"vkDeviceWaitIdle", "vkAllocateMemory", "vkFreeMemory", "vkMapMemory", "vkUnmapMemory", "vkFlushMappedMemoryRanges", "vkInvalidateMappedMemoryRanges", "vkGetDeviceMemoryCommitment",
					"vkBindBufferMemory", "vkBindImageMemory", "vkGetBufferMemoryRequirements", "vkGetImageMemoryRequirements", "vkGetImageSparseMemoryRequirements", "vkGetPhysicalDeviceSparseImageFormatProperties",
					"vkQueueBindSparse", "vkCreateFence", "vkDestroyFence", "vkResetFences", "vkGetFenceStatus", "vkWaitForFences", "vkCreateSemaphore", "vkDestroySemaphore", "vkCreateEvent", "vkDestroyEvent",
					"vkGetEventStatus", "vkSetEvent", "vkResetEvent", "vkCreateQueryPool", "vkDestroyQueryPool", "vkGetQueryPoolResults", "vkCreateBuffer", "vkDestroyBuffer", "vkCreateBufferView", "vkDestroyBufferView",
					"vkCreateImage", "vkDestroyImage", "vkGetImageSubresourceLayout", "vkCreateImageView", "vkDestroyImageView", "vkCreateShaderModule", "vkDestroyShaderModule", "vkCreatePipelineCache",
					"vkDestroyPipelineCache", "vkGetPipelineCacheData", "vkMergePipelineCaches", "vkCreateGraphicsPipelines", "vkCreateComputePipelines", "vkDestroyPipeline", "vkCreatePipelineLayout",
					"vkDestroyPipelineLayout", "vkCreateSampler", "vkDestroySampler", "vkCreateDescriptorSetLayout", "vkDestroyDescriptorSetLayout", "vkCreateDescriptorPool", "vkDestroyDescriptorPool",
					"vkResetDescriptorPool", "vkAllocateDescriptorSets", "vkFreeDescriptorSets", "vkUpdateDescriptorSets", "vkCreateFramebuffer", "vkDestroyFramebuffer", "vkCreateRenderPass", "vkDestroyRenderPass",
					"vkGetRenderAreaGranularity", "vkCreateCommandPool", "vkDestroyCommandPool", "vkResetCommandPool", "vkAllocateCommandBuffers", "vkFreeCommandBuffers", "vkBeginCommandBuffer", "vkEndCommandBuffer",
					"vkResetCommandBuffer", "vkCmdBindPipeline", "vkCmdSetViewport", "vkCmdSetScissor", "vkCmdSetLineWidth", "vkCmdSetDepthBias", "vkCmdSetBlendConstants", "vkCmdSetDepthBounds",
					"vkCmdSetStencilCompareMask", "vkCmdSetStencilWriteMask", "vkCmdSetStencilReference", "vkCmdBindDescriptorSets", "vkCmdBindIndexBuffer", "vkCmdBindVertexBuffers", "vkCmdDraw", "vkCmdDrawIndexed",
					"vkCmdDrawIndirect", "vkCmdDrawIndexedIndirect", "vkCmdDispatch", "vkCmdDispatchIndirect", "vkCmdCopyBuffer", "vkCmdCopyImage", "vkCmdBlitImage", "vkCmdCopyBufferToImage", "vkCmdCopyImageToBuffer",
					"vkCmdUpdateBuffer", "vkCmdFillBuffer", "vkCmdClearColorImage", "vkCmdClearDepthStencilImage", "vkCmdClearAttachments", "vkCmdResolveImage", "vkCmdSetEvent", "vkCmdResetEvent", "vkCmdWaitEvents",
					"vkCmdPipelineBarrier", "vkCmdBeginQuery", "vkCmdEndQuery", "vkCmdResetQueryPool", "vkCmdWriteTimestamp", "vkCmdCopyQueryPoolResults", "vkCmdPushConstants", "vkCmdBeginRenderPass", "vkCmdNextSubpass",
					"vkCmdEndRenderPass", "vkCmdExecuteCommands"
				};

				size_t size = KIERO_ARRAY_SIZE(methodsNames);

				g_methodsTable = (uint150_t*)::calloc(size, sizeof(uint150_t));

				for (int i = 0; i < size; i++)
				{
					g_methodsTable[i] = (uint150_t)::GetProcAddress(libVulkan, methodsNames[i]);
				}

#if KIERO_USE_MINHOOK
				MH_Initialize();
#endif

				g_renderType = RenderType::vulkan;

				return Status::Success;
#endif
            }

            return status::not_supported_error;
        }
        render_type::Enum type = render_type::none;

        if (::GetModuleHandle(KIERO_TEXT("d3d9.dll")) != nullptr)
        {
            type = render_type::d3d9;
        }
        else if (::GetModuleHandle(KIERO_TEXT("d3d10.dll")) != nullptr)
        {
            type = render_type::d3d10;
        }
        else if (::GetModuleHandle(KIERO_TEXT("d3d11.dll")) != nullptr)
        {
            type = render_type::d3d11;
        }
        else if (::GetModuleHandle(KIERO_TEXT("d3d12.dll")) != nullptr)
        {
            type = render_type::d3d12;
        }
        else if (::GetModuleHandle(KIERO_TEXT("opengl32.dll")) != nullptr)
        {
            type = render_type::opengl;
        }
        else if (::GetModuleHandle(KIERO_TEXT("vulkan-1.dll")) != nullptr)
        {
            type = render_type::vulkan;
        }
        else
        {
            return status::not_supported_error;
        }

        return init(type);
    }

    return status::success;
}

void kiero::shutdown()
{
    if (g_render_type != render_type::none)
    {
#if KIERO_USE_MINHOOK
        MH_DisableHook(nullptr);
#endif

        free(g_methods_table);
        g_methods_table = nullptr;
        g_render_type = render_type::none;
    }
}

kiero::status::Enum kiero::bind(uint16_t _index, void** _original, void* _function)
{
    // TODO: Need own detour function

    assert(_original != NULL && _function != NULL);

    if (g_render_type != render_type::none)
    {
#if KIERO_USE_MINHOOK
	    if (const auto target = reinterpret_cast<void*>(g_methods_table[_index]); MH_CreateHook(target, _function, _original) != MH_OK || MH_EnableHook(target) != MH_OK)
            return status::unknown_error;
#endif

        return status::success;
    }

    return status::not_initialized_error;
}

void kiero::unbind(uint16_t _index)
{
    if (g_render_type != render_type::none)
    {
#if KIERO_USE_MINHOOK
        MH_DisableHook(reinterpret_cast<void*>(g_methods_table[_index]));
#endif
    }
}

kiero::render_type::Enum kiero::get_render_type()
{
    return g_render_type;
}

uint150_t* kiero::get_methods_table()
{
    return g_methods_table;
}
