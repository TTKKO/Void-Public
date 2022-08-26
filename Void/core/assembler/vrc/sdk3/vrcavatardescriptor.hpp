#pragma once
#include "expressionsmenu.hpp"

namespace assembler::vrc::sdk3
{
    struct vrcavatardescriptor : unity_engine::object
    {
        expressionsmenu* get_expressionsmenu();
    };
}
