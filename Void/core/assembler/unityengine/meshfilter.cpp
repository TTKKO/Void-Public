#include "meshfilter.hpp"

assembler::unity_engine::mesh* assembler::unity_engine::meshfilter::get_sharedmesh()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_sharedmesh passed nullptr.\n"));
        logging::pop();
        return nullptr;
    }
    if (!get_sharedmesh_func_) get_sharedmesh_func_ = static_cast<get_sharedmesh_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.MeshFilter::get_sharedMesh()")));
    return get_sharedmesh_func_(this);
}
