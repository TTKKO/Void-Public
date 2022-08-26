/*
 *		assembler/unityengine/ui/text.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's Text class
 */

#pragma once
#include "../component.hpp"
#include "graphic.hpp"

namespace assembler::unity_engine::ui
{
    struct text : graphic
    {
        void set_fontsize(int size);
        void set_text(std::string_view value);
        std::string get_text();
        void set_support_rich_text(const bool& value);
    };
}
