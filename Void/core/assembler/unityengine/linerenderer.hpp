/*
 *		assembler/unityengine/linerenderer.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's LineRenderer class
 */

#pragma once
#include "renderer.hpp"

namespace assembler::unity_engine
{
    struct linerenderer : renderer
    {
        static il2cpp::il2cpp_type* get_global_type();


    private:
        static inline il2cpp::il2cpp_type* global_type_ = nullptr;
    };
}
