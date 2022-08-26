#pragma once

#ifndef UTILITY_MODULES_HPP
#define UTILITY_MODULES_HPP

#include "main_modules.hpp"
#include "../../../hooks/helpers/friend_tool.hpp"

class utility_modules : public menu_modules, public c_singleton<utility_modules>
{
public:
    void setup();
    void show_all() const;
};

#endif
