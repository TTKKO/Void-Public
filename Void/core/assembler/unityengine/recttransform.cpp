#include "recttransform.hpp"

void assembler::unity_engine::rect_transform::set_anchor_max(const sdk::vector_2d& value)
{
    if (!set_anchor_max_func_) 
        set_anchor_max_func_ = static_cast<set_anchor_max_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.RectTransform::set_anchorMax_Injected(UnityEngine.Vector2&)")));

    return set_anchor_max_func_(this, value);
}

void assembler::unity_engine::rect_transform::set_size_delta(const sdk::vector_2d& value)
{
    if (!set_size_delta_func_)
        set_size_delta_func_ = static_cast<set_size_delta_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.RectTransform::set_sizeDelta_Injected(UnityEngine.Vector2&)")));

	set_size_delta_func_(this, value);
}
