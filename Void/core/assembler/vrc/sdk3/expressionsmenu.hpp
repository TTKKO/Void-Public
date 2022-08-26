#pragma once
#include "../../common.hpp"
#include "../../il2cpp/array_wrapper.hpp"

namespace assembler::vrc::sdk3
{
    struct expressionsmenu : il2cpp::il2cpp_object
    {
        il2cpp::il2cpp_array* get_controls();

        struct control : il2cpp_object
        {
            std::string get_name();
            void set_name(std::string_view name);
        };
    };
}
