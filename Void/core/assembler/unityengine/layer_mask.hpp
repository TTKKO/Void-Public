/*
 *		assembler/unityengine/layer_mask.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's LayerMask class
 */

#pragma once
#include "../common.hpp"
#include "../il2cpp/il2cpp.hpp"

namespace assembler::unity_engine
{
    struct layer_mask
    {
        DELCONST(layer_mask);

        static int32_t name_to_layer(std::string_view name);

    private:
        using name_to_layer_t = int32_t(*)(il2cpp::il2cpp_string*);
        inline static name_to_layer_t name_to_layer_func_ = nullptr;
    };
}
