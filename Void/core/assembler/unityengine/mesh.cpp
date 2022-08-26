#include "mesh.hpp"

std::int32_t assembler::unity_engine::mesh::default_dimension_for_channel(const vertex_attribute channel)
{
    if (channel == vertex_attribute::position || channel == vertex_attribute::normal)
        return 3;

    if (channel >= vertex_attribute::tex_coord0 && channel <= vertex_attribute::tex_coord7)
        return 2;

    if (channel != vertex_attribute::tangent && channel != vertex_attribute::color)
        return 0; // @note: should raise exception

    return 4;
}

assembler::il2cpp::il2cpp_array_wrapper<std::int32_t>* assembler::unity_engine::mesh::get_triangles()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_triangles passed nullptr.\n"));
        logging::pop();
        return nullptr;
    }
    if (!this->can_access())
        return array_new<std::int32_t>(class_from_system_type(il2cpp::get_type(xorstr_("System.Int32"))), 0);

    if (!get_triangles_func_) 
        get_triangles_func_ = static_cast<get_triangles_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Mesh::GetTrianglesImpl(System.Int32,System.Boolean)")));

    return get_triangles_func_(this, 0xFFFFFFFF, true);
}

bool assembler::unity_engine::mesh::can_access()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] can_access passed nullptr.\n"));
        logging::pop();
        return false;
    }
    if (!can_access_func_) can_access_func_ = static_cast<can_access_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Mesh::get_canAccess()")));
    return can_access_func_(this);
}

bool assembler::unity_engine::mesh::get_is_readable()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_is_readable passed nullptr.\n"));
        logging::pop();
        return false;
    }
    if (!get_is_readable_func_) get_is_readable_func_ = static_cast<get_is_readable_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Mesh::get_isReadable()")));
    return get_is_readable_func_(this);
}

std::int32_t assembler::unity_engine::mesh::get_submesh_count()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_submesh_count passed nullptr.\n"));
        logging::pop();
        return 0;
    }

    if (!get_submesh_count_func_) 
        get_submesh_count_func_ = static_cast<get_submesh_count_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Mesh::get_subMeshCount()")));

	return get_submesh_count_func_(this);
}

std::int32_t assembler::unity_engine::mesh::get_vertex_count()
{
    if (!this)
        return 0;

    if (!get_vertex_count_func_)
        get_vertex_count_func_ = static_cast<get_vertex_count_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Mesh::get_vertexCount()")));

    return get_vertex_count_func_(this);
}

std::int32_t assembler::unity_engine::mesh::get_blendshape_count()
{
    if (!this)
        return 0;

    if (!get_blendshape_count_func_)
        get_blendshape_count_func_ = static_cast<get_blendshape_count_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Mesh::get_blendShapeCount()")));

    return get_blendshape_count_func_(this);
}
