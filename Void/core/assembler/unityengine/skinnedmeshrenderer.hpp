/*
 *		assembler/unityengine/skinnedmeshrenderer.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's SkinnedMeshRenderer class
 */

#pragma once
#include "renderer.hpp"

namespace assembler::unity_engine
{
    struct mesh;

    struct skinnedmeshrenderer : renderer
    {
        static il2cpp::il2cpp_type* get_global_type();

        mesh* get_sharedmesh();
        transform* get_root_bone();
        il2cpp::il2cpp_array_wrapper<object*>* get_bones();
        void set_bones(il2cpp::il2cpp_array* bones);

    private:
        static inline il2cpp::il2cpp_type* type_ = nullptr;

        using get_sharedmesh_t = mesh * (*)(skinnedmeshrenderer*);
        inline static get_sharedmesh_t get_sharedmesh_func_ = nullptr;

        using get_root_bone_t = transform * (*)(skinnedmeshrenderer*);
        inline static get_root_bone_t get_root_bone_func_ = nullptr;

        using get_bones_t = il2cpp::il2cpp_array_wrapper<object*>* (*)(skinnedmeshrenderer*);
        inline static get_bones_t get_bones_func_ = nullptr;

        using set_bones_t = void (*)(skinnedmeshrenderer*, il2cpp::il2cpp_array*);
        inline static set_bones_t set_bones_func_ = nullptr;
    };
}
