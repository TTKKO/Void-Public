/*
 *		assembler/unityengine/mesh.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's Mesh class
 */

#pragma once
#include "../common.hpp"
#include "../il2cpp/array_wrapper.hpp"

namespace assembler::unity_engine
{
    struct mesh : object
    {
        enum class vertex_attribute : std::int32_t
        {
            position = 0,
            normal = 1,
            tangent = 2,
            color = 3,
            tex_coord0 = 4,
            tex_coord1 = 5,
            tex_coord2 = 6,
            tex_coord3 = 7,
            tex_coord4 = 8,
            tex_coord5 = 9,
            tex_coord6 = 10,
            tex_coord7 = 11,
            blend_weight = 12,
            blend_indices = 13
        };

        static std::int32_t default_dimension_for_channel(vertex_attribute channel);
        il2cpp::il2cpp_array_wrapper<std::int32_t>* get_triangles();

        bool can_access();
        bool get_is_readable();
        std::int32_t get_submesh_count();
        std::int32_t get_vertex_count();
        std::int32_t get_blendshape_count();

    private:
        using get_triangles_t = il2cpp::il2cpp_array_wrapper<std::int32_t>* (*)(mesh*, uint32_t, bool);
        inline static get_triangles_t get_triangles_func_ = nullptr;

        using can_access_t = bool (*)(mesh*);
        inline static can_access_t can_access_func_ = nullptr;

        using get_is_readable_t = bool (*)(mesh*);
        inline static get_is_readable_t get_is_readable_func_ = nullptr;

        using get_submesh_count_t = std::int32_t (*)(mesh*);
        inline static get_submesh_count_t get_submesh_count_func_ = nullptr;

        using get_vertex_count_t = std::int32_t(*)(mesh*);
        inline static get_vertex_count_t get_vertex_count_func_ = nullptr;

        using get_blendshape_count_t = std::int32_t(*)(mesh*);
        inline static get_blendshape_count_t get_blendshape_count_func_ = nullptr;
    };
}
