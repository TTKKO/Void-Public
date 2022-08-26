#pragma once
#include "../../unityengine/behaviour.hpp"

namespace assembler::vrc::sdk_base
{
    struct vrc_mirror_reflection : unity_engine::behaviour
    {
        enum class dimension : std::int32_t
        {
        	Auto = 0,
			x256 = 256,
        	x512 = 512,
			x1024 = 1024,
            x2048 = 2048
        };

        static il2cpp::il2cpp_type* get_global_type();

        void set_reflection_layers(std::int32_t value);
        std::int32_t get_reflection_layers();

        void set_resolution(dimension value);

    private:
        inline static il2cpp::il2cpp_type* type_ = nullptr;
    };
}
