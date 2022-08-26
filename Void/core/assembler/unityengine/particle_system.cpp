#include "particle_system.hpp"

assembler::il2cpp::il2cpp_type* assembler::unity_engine::particle_system::get_global_type()
{
    if (!type_)
        type_ = il2cpp::get_type(xorstr_("UnityEngine.ParticleSystem, UnityEngine.ParticleSystemModule"));

    return type_;
}

float assembler::unity_engine::particle_system::size_over_lifetime::get_size_multiplier()
{
    if (!this)
        return NULL;

    if (!get_size_multiplier_func_)
        get_size_multiplier_func_ = static_cast<get_size_multiplier_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.ParticleSystem/SizeOverLifetimeModule::get_sizeMultiplier_Injected(UnityEngine.ParticleSystem/SizeOverLifetimeModule&)")));

    auto v5 = this;
    return get_size_multiplier_func_(&v5);
}

void assembler::unity_engine::particle_system::size_over_lifetime::set_size_multiplier(const float value)
{
    if (!this)
        return;

    if (!set_size_multiplier_func_)
        set_size_multiplier_func_ = static_cast<set_size_multiplier_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.ParticleSystem/SizeOverLifetimeModule::set_sizeMultiplier_Injected(UnityEngine.ParticleSystem/SizeOverLifetimeModule&,System.Single)")));

    auto v5 = this;
    return set_size_multiplier_func_(&v5, value);
}

float assembler::unity_engine::particle_system::size_by_speed::get_size_multiplier()
{
    if (!this)
        return NULL;

    if (!get_size_multiplier_func_)
        get_size_multiplier_func_ = static_cast<get_size_multiplier_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.ParticleSystem/SizeBySpeedModule::get_sizeMultiplier_Injected(UnityEngine.ParticleSystem/SizeBySpeedModule&)")));

    auto v5 = this;
    return get_size_multiplier_func_(&v5);
}

void assembler::unity_engine::particle_system::size_by_speed::set_size_multiplier(const float value)
{
    if (!this)
        return;

    if (!set_size_multiplier_func_)
        set_size_multiplier_func_ = static_cast<set_size_multiplier_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.ParticleSystem/SizeBySpeedModule::set_sizeMultiplier_Injected(UnityEngine.ParticleSystem/SizeBySpeedModule&,System.Single")));

    auto v5 = this;
    return set_size_multiplier_func_(&v5, value);
}

std::int32_t assembler::unity_engine::particle_system::get_max_particles()
{
    if (this == nullptr)
        return NULL;

    if (!get_max_particles_func_)
        get_max_particles_func_ = static_cast<get_max_particles_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.ParticleSystem/MainModule::get_maxParticles_Injected(UnityEngine.ParticleSystem/MainModule&)")));

    auto v5 = this;
    return get_max_particles_func_(&v5);
}

float assembler::unity_engine::particle_system::get_start_size()
{
    if (this == nullptr)
        return NULL;

    if (!get_start_size_func_)
        get_start_size_func_ = static_cast<get_start_size_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.ParticleSystem/MainModule::get_startSizeMultiplier_Injected(UnityEngine.ParticleSystem/MainModule&)")));

    auto v5 = this;
    return get_start_size_func_(&v5);
}

void assembler::unity_engine::particle_system::set_start_size(const float value)
{
    if (this == nullptr)
        return;

    if (!set_start_size_func_)
        set_start_size_func_ = static_cast<set_start_size_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.ParticleSystem/MainModule::set_startSizeMultiplier_Injected(UnityEngine.ParticleSystem/MainModule&,System.Single)")));

    auto v5 = this;
	set_start_size_func_(&v5, value);
}

float assembler::unity_engine::particle_system::get_emission_rate()
{
    if (!this)
        return NULL;

    if (!get_emission_rate_func_)
        get_emission_rate_func_ = static_cast<get_emission_rate_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.ParticleSystem/EmissionModule::get_rateOverTimeMultiplier_Injected(UnityEngine.ParticleSystem/EmissionModule&)")));

    auto v5 = this;
    return get_emission_rate_func_(&v5);
}
