/*
 *		assembler/unityengine/meshrenderer.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's MeshRenderer class
 */

#pragma once
#include "renderer.hpp"

namespace assembler::unity_engine
{
    struct meshrenderer : renderer
    {
    private:
        inline static il2cpp::il2cpp_type* global_type_ = nullptr;
    public:
    	static il2cpp::il2cpp_type* get_global_type()
        {
            if (!global_type_)
                global_type_ = il2cpp::get_type(xorstr_("UnityEngine.MeshRenderer, UnityEngine.CoreModule"));

            return global_type_;
        }
    };
}
