#pragma once

#include <format>
#include <MinHook.h>
#include "../core/sdk/hash/xorstr.hpp"

/*
 * detour hooking implementation using minhook
 * @credits: https://github.com/TsudaKageyu/minhook
 */
class c_detour_hook
{
public:
    c_detour_hook() = default;

    explicit c_detour_hook(void* p_function, void* p_detour) : p_base_fn_(p_function), p_replace_fn_(p_detour)
    {
    }

    /* first hook setup */
    bool create(void* p_function, void* p_detour)
    {
        p_base_fn_ = p_function;

        if (p_base_fn_ == nullptr)
            return false;

        p_replace_fn_ = p_detour;

        if (p_replace_fn_ == nullptr)
            return false;

        // VMProtectBeginMutation("CDetour Create");

        if (const MH_STATUS status = MH_CreateHook(p_base_fn_, p_replace_fn_, &p_original_fn_); status != MH_OK)
            throw std::runtime_error(utility::format(SECSTR("failed to create hook, status: {} [reference -> {:#08x}]"), MH_StatusToString(status), reinterpret_cast<std::uintptr_t>(p_base_fn_)));

        // VMProtectEnd();

        if (!this->replace())
            return false;

        return true;
    }

    /* replace function to our modified */
    bool replace()
    {
        // check is hook be created
        if (p_base_fn_ == nullptr)
            return false;

        // check is function not already hooked
        if (b_is_hooked_)
            return false;

        // VMProtectBeginMutation("CDetour Replace");

        if (const MH_STATUS status = MH_EnableHook(p_base_fn_); status != MH_OK)
            throw std::runtime_error(utility::format(SECSTR("failed to enable hook, status: {} [reference -> {:#08x}]"), MH_StatusToString(status), reinterpret_cast<std::uintptr_t>(p_base_fn_)));

        // VMProtectEnd();

        // switch hook state
        b_is_hooked_ = true;
        return true;
    }

    /* remove hook fully */
    bool remove()
    {
        // restore it at first
        if (!this->restore())
            return false;

        // VMProtectBeginMutation("CDetour Remove");

        if (const MH_STATUS status = MH_RemoveHook(p_base_fn_); status != MH_OK)
            throw std::runtime_error(utility::format(SECSTR("failed to remove hook, status: {} [reference -> {:#08x}]"), MH_StatusToString(status), reinterpret_cast<std::uintptr_t>(p_base_fn_)));

        // VMProtectEnd();

        return true;
    }

    /* replace swaped modified function back to original */
    bool restore()
    {
        // check is function hooked
        if (!b_is_hooked_)
            return false;

        // VMProtectBeginMutation("CDetour Restore");

        if (const MH_STATUS status = MH_DisableHook(p_base_fn_); status != MH_OK) 
            throw std::runtime_error(utility::format(SECSTR("failed to restore hook, status: {} [reference -> {:#08x}]"), MH_StatusToString(status), reinterpret_cast<std::uintptr_t>(p_base_fn_)));

        // VMProtectEnd();

        // switch hook state
        b_is_hooked_ = false;
        return true;
    }

    /* get original function pointer (not a call!) */
    template <typename Fn>
    Fn get_original()
    {
        return static_cast<Fn>(p_original_fn_);
    }

    /* returns hook state */
    _NODISCARD bool is_hooked() const
    {
        return b_is_hooked_;
    }

private:
    /* hook state */
    bool b_is_hooked_ = false;
    /* function base */
    void* p_base_fn_ = nullptr;
    /* in future that is being modified and replace original */
    void* p_replace_fn_ = nullptr;
    /* saved function to get available restore hook later */
    void* p_original_fn_ = nullptr;
};
