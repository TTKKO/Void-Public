#include "gizmos.hpp"

void assembler::unity_engine::gizmos::draw_cube(const sdk::vector& center, const sdk::vector& size)
{
    if (!draw_cube_) draw_cube_ = static_cast<draw_cube_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.Gizmos::DrawCube_Injected(UnityEngine.Vector3&,UnityEngine.Vector3&)")));
    draw_cube_(center, size);
}
