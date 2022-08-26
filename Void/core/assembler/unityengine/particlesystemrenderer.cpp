#include "particlesystemrenderer.hpp"

assembler::il2cpp::il2cpp_type* assembler::unity_engine::particlesystemrenderer::get_global_type()
{
	if (!type_)
		type_ = il2cpp::get_type(xorstr_("UnityEngine.ParticleSystemRenderer, UnityEngine.ParticleSystemModule"));

	return type_;
}

assembler::unity_engine::mesh* assembler::unity_engine::particlesystemrenderer::get_mesh()
{
	if (!this)
		return nullptr;

	if (!get_mesh_func_)
		get_mesh_func_ = static_cast<get_mesh_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.ParticleSystemRenderer::get_mesh()")));

	return get_mesh_func_(this);
}
