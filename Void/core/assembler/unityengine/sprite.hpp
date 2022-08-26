/*
 *		assembler/unity_engine/sprite.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's Sprite class
 */

#pragma once
#include "component.hpp"
#include "texture_2d.hpp"
#include "rect.hpp"

namespace assembler::unity_engine::ui
{
    struct sprite : component
    {
    	enum sprite_mesh_type
        {
            full_rect,
            tight
        };

        static sprite* create(texture_2d* texture, const rect& rect, const sdk::vector_2d& pivot, float thing, std::uint32_t wtf, sprite_mesh_type type, const sdk::vector_4d& box, bool aids);
        static sprite* create_custom(std::int32_t width, std::int32_t height, ID3D11ShaderResourceView* dx_texture);

    private:
        using create_t = sprite* (*)(texture_2d*, const rect&, const sdk::vector_2d&, float, std::uint32_t, sprite_mesh_type, const sdk::vector_4d&, bool);
        inline static create_t create_func_ = nullptr;
    };
}
