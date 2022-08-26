/*
 *		assembler/unityengine/particle_system.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's ParticleSystem class
 */

#pragma once
#include "../unityengine/component.hpp"

namespace assembler::unity_engine
{
    struct particle_system : component
    {
        static il2cpp::il2cpp_type* get_global_type();

        struct size_over_lifetime
        {
            float get_size_multiplier();
            void set_size_multiplier(float value);

        private:
            using get_size_multiplier_t = float(*)(size_over_lifetime**);
            inline static get_size_multiplier_t get_size_multiplier_func_ = nullptr;

            using set_size_multiplier_t = void(*)(size_over_lifetime**, float);
            inline static set_size_multiplier_t set_size_multiplier_func_ = nullptr;
        };

        struct size_by_speed
        {
            float get_size_multiplier();
            void set_size_multiplier(float value);

        private:
            using get_size_multiplier_t = float(*)(size_by_speed**);
            inline static get_size_multiplier_t get_size_multiplier_func_ = nullptr;

            using set_size_multiplier_t = void(*)(size_by_speed**, float);
            inline static set_size_multiplier_t set_size_multiplier_func_ = nullptr;
        };

    	size_over_lifetime* get_size_over_lifetime()
        {
            return reinterpret_cast<size_over_lifetime*>(this);
        }

        size_by_speed* get_size_by_speed()
    	{
            return reinterpret_cast<size_by_speed*>(this);
    	}

    	std::int32_t get_max_particles();

        float get_start_size();
        void set_start_size(float value);

        float get_emission_rate();

    private:
        inline static il2cpp::il2cpp_type* type_ = nullptr;

        using get_max_particles_t = std::int32_t(*)(particle_system**);
        inline static get_max_particles_t get_max_particles_func_ = nullptr;

        using get_start_size_t = float(*)(particle_system**);
        inline static get_start_size_t get_start_size_func_ = nullptr;

        using set_start_size_t = void(*)(particle_system**, float);
        inline static set_start_size_t set_start_size_func_ = nullptr;

        using get_emission_rate_t = float(*)(particle_system**);
        inline static get_emission_rate_t get_emission_rate_func_ = nullptr;
    };
}
