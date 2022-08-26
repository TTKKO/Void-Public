#include "layer_mask.hpp"

int32_t assembler::unity_engine::layer_mask::name_to_layer(const std::string_view name)
{
    if (!name_to_layer_func_) name_to_layer_func_ = static_cast<name_to_layer_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.LayerMask::NameToLayer(System.String)")));
    return name_to_layer_func_(il2cpp::string_new(name));
}
