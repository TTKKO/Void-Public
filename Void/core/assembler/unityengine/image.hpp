/*
 *		assembler/unityengine/image.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's Image class
 */

#pragma once
#include "../common.hpp"
#include "../..//sdk/datatypes/color.h"
#include "ui/graphic.hpp"

namespace assembler::unity_engine::ui
{
    struct sprite;

    struct material;

    struct image : graphic
    {
        sprite* get_sprite();
        void set_sprite(sprite* value);
        material* get_material();
        void set_material(material* value);
        sdk::color get_color();
    };
}
