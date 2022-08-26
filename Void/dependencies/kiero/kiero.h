#ifndef __KIERO_H__
#define __KIERO_H__

#include <stdint.h>

#define KIERO_VERSION "1.2.12"

#define KIERO_INCLUDE_D3D9   0 // 1 if you need d3d9 hook
#define KIERO_INCLUDE_D3D10  0 // 1 if you need d3d10 hook
#define KIERO_INCLUDE_D3D11  1 // 1 if you need d3d11 hook
#define KIERO_INCLUDE_D3D12  0 // 1 if you need d3d12 hook
#define KIERO_INCLUDE_OPENGL 0 // 1 if you need opengl hook
#define KIERO_INCLUDE_VULKAN 0 // 1 if you need vulkan hook
#define KIERO_USE_MINHOOK    1 // 1 if you will use kiero::bind function

#define KIERO_ARCH_X64 0
#define KIERO_ARCH_X86 0

#if defined(_M_X64)
# undef  KIERO_ARCH_X64
# define KIERO_ARCH_X64 1
#else
# undef  KIERO_ARCH_X86
# define KIERO_ARCH_X86 1
#endif

#if KIERO_ARCH_X64
using uint150_t = uint64_t;
#else
typedef uint32_t uint150_t;
#endif

namespace kiero
{
    struct status
    {
        enum Enum
        {
            unknown_error = -1,
            not_supported_error = -2,
            module_not_found_error = -3,

            already_initialized_error = -4,
            not_initialized_error = -5,

            success = 0,
        };
    };

    struct render_type
    {
        enum Enum
        {
            none,
            d3d9,
            d3d10,
            d3d11,
            d3d12,
            opengl,
            vulkan,
            Auto
        };
    };

    status::Enum init(render_type::Enum render_type);
    void shutdown();

    status::Enum bind(uint16_t index, void** original, void* function);
    void unbind(uint16_t index);

    render_type::Enum get_render_type();
    uint150_t* get_methods_table();
}

#endif // __KIERO_H__
