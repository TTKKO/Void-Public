#include "dynamic_bone.hpp"
#include <intrin.h>
#include "../unityengine/transform.hpp"

assembler::unity_engine::transform* assembler::dynamic_bone::get_root()
{
	return *reinterpret_cast<unity_engine::transform**>(reinterpret_cast<std::uint8_t*>(this) + 0x18);
}
