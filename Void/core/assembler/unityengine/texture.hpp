/*
 *		assembler/unityengine/texture.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's Texture class
 */

#pragma once
#include "../common.hpp"
#include "../il2cpp/il2cpp.hpp"

namespace assembler::unity_engine
{
    struct texture : object
    {
        void set_wrap_mode(int32_t value);
        std::int32_t get_width();
        std::int32_t get_height();
    private:
        using set_wrap_mode_t = void* (*)(texture*, int32_t);
        inline static set_wrap_mode_t set_wrap_mode_func_ = nullptr;

        using get_width_t = int32_t(*)(texture*);
        inline static get_width_t get_width_func_ = nullptr;

        using get_height_t = int32_t(*)(texture*);
        inline static get_height_t get_height_func_ = nullptr;
    };
}
