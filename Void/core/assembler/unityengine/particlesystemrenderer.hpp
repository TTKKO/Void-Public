/*
 *		assembler/unityengine/particlesystemrenderer.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's ParticleSystemRenderer class
 */

#pragma once
#include "mesh.hpp"
#include "renderer.hpp"

namespace assembler::unity_engine
{
    struct particlesystemrenderer : renderer
    {
        static il2cpp::il2cpp_type* get_global_type();

        mesh* get_mesh();

    private:
        static inline il2cpp::il2cpp_type* type_ = nullptr;

        using get_mesh_t = mesh* (*)(particlesystemrenderer*);
        inline static get_mesh_t get_mesh_func_ = nullptr;
    };
}
