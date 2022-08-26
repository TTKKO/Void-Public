/*
 *		assembler/unityengine/ui/selectable.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's Selectable class
 */

#pragma once
#include "../component.hpp"

namespace assembler::unity_engine::ui
{
    struct selectable : component
    {
        void set_interactable(bool value);
    };
}
