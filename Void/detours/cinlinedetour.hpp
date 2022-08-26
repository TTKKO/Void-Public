/*
 *		detours/cinlinedetour.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
  *		Copyright © 2019 Greengray. All rights reserved.
 *		Inline detouring
 */

#pragma once
#include <cstdint>
#include <functional>
#include <cstddef>
#include <utility>

class c_inline_detour
{
public:
    c_inline_detour(const c_inline_detour&);
    c_inline_detour& operator =(const c_inline_detour&);
    c_inline_detour(c_inline_detour&&) noexcept;
    c_inline_detour& operator =(c_inline_detour&&) noexcept;

private:
    std::uint8_t* m_p_tour_ = nullptr;

    std::function<void()> m_func_;

    constexpr static std::size_t tour_offset = 128;

    static void tramp(void* p_memory, const void* p_func) noexcept
    {
        const auto fp = reinterpret_cast<std::uintptr_t>(p_func);
        const auto* f = reinterpret_cast<const uint8_t*>(&fp);

        const std::uint8_t t[]{

            // call <next>
            0xE8, 0x00, 0x00, 0x00, 0x00,
            // pop rax
            0x58,
            // mov rcx, rax
            0x48, 0x8B, 0xC8,

            // mov rax, p_func
            0x48, 0xB8, f[0], f[1], f[2], f[3], f[4], f[5], f[6], f[7],
            // jmp rax
            0xFF, 0xE0,

            // int 3 breakpoint
            0xCC,
        };

        std::copy_n(t, sizeof t, static_cast<std::uint8_t*>(p_memory));
    }

    static void proxy(const std::uintptr_t rip)
    {
        const std::uintptr_t base = rip & ~static_cast<std::uintptr_t>(0xFFF);
        const c_inline_detour* p_this = *reinterpret_cast<const c_inline_detour* const*>(base);
        return p_this->m_func_();
    }

    void init() noexcept
    {
        m_p_tour_ = static_cast<std::uint8_t*>(VirtualAlloc(nullptr, 0x1000, MEM_COMMIT, PAGE_EXECUTE_READWRITE));
        *reinterpret_cast<c_inline_detour**>(m_p_tour_) = this;
        const auto p_func = m_p_tour_ + tour_offset;

        tramp(p_func, &proxy);
    }

public:
    explicit c_inline_detour(std::function<void()> func) : m_func_(std::move(func))
    {
        init();
    }

    ~c_inline_detour()
    {
        if (m_p_tour_)
        {
            VirtualFree(m_p_tour_, 0, MEM_RELEASE);
            m_p_tour_ = nullptr;
        }
    }

    using func_type = void(*)();
    _NODISCARD func_type get_ptr() const
    {
        return reinterpret_cast<func_type>(m_p_tour_ + tour_offset);
    }
};

class c_detour_manager
{
    std::vector<std::unique_ptr<c_inline_detour>> m_detours_{};

public:
    c_inline_detour* create(const std::function<void()>& fn)
    {
        return m_detours_.emplace_back(std::make_unique<c_inline_detour>(fn)).get();
    }

    static c_detour_manager& get_singleton()
    {
        static c_detour_manager instance;
        return instance;
    }
};

inline c_inline_detour* create_detour(const std::function<void()>& fn)
{
    return c_detour_manager::get_singleton().create(fn);
}
