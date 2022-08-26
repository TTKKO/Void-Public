/*
 *		assembler/unityengine/ui/graphic.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's Graphic class
 */

#pragma once
#include "../component.hpp"
#include "../../../sdk/datatypes/color.h"
#include <array>

namespace assembler::unity_engine::ui
{
    struct graphic : component
    {
        void set_color(const sdk::color& value);
    };
}

