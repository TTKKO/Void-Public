/*
 *		assembler/unityengine/cursor.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's Cursor class
 */

#pragma once
#include "../common.hpp"
#include "../il2cpp/il2cpp.hpp"

namespace assembler::unity_engine
{
    enum class cursor_lock_mode : int
    {
        none = 0,
        locked = 1,
        confined = 2
    };


    struct cursor
    {
        DELCONST(cursor);

        static void set_visible(bool value);
        static void set_lock_state(cursor_lock_mode mode);
        static cursor_lock_mode get_lock_state();

    private:
        using set_visible_t = void(*)(bool);
        inline static set_visible_t set_visible_func_ = nullptr;

        using set_lock_state_t = void(*)(cursor_lock_mode);
        inline static set_lock_state_t set_lock_state_func_ = nullptr;

        using get_lock_state_t = cursor_lock_mode(*)();
        inline static get_lock_state_t get_lock_state_func_ = nullptr;
    };
}
