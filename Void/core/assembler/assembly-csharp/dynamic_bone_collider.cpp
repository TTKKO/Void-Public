#include "dynamic_bone_collider.hpp"

assembler::dynamic_bone_collider::bounds assembler::dynamic_bone_collider::get_bounds()
{
    return *reinterpret_cast<bounds*>(reinterpret_cast<std::uint8_t*>(this) + 0x30);
}
