/*
 *		assembler/unityengine/meshfilter.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's MeshFilter class
 */

#pragma once
#include "../UnityEngine/component.hpp"

namespace assembler::unity_engine
{
    struct mesh;

    struct meshfilter : component
    {
        mesh* get_sharedmesh();

    private:
        using get_sharedmesh_t = mesh * (*)(meshfilter*);
        inline static get_sharedmesh_t get_sharedmesh_func_ = nullptr;
    };
}
