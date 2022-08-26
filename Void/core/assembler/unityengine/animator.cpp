#include "animator.hpp"

assembler::unity_engine::transform* assembler::unity_engine::animator::get_bone_transform(const std::int32_t bone)
{
	if (!this)
		return nullptr;

	if (bone < 0 || bone >= 55)
	{
		logging::push(FOREGROUND_INTENSE_RED);
		logging::print(xorstr_("[critical] bone is out of range [{:d}]\n"), bone);
		logging::pop();
		return nullptr;
	}

	if (!get_bone_index_from_mono_func_)
		get_bone_index_from_mono_func_ = static_cast<get_bone_index_from_mono_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.HumanTrait::GetBoneIndexFromMono(System.Int32)")));

	if (!get_bone_transform_func_)
		get_bone_transform_func_ = static_cast<get_bone_transform_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Animator::GetBoneTransformInternal(System.Int32)")));

	const auto bone_index = get_bone_index_from_mono_func_(bone);
	return get_bone_transform_func_(this, bone_index);
}
