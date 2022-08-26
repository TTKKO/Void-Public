#pragma once

#ifndef SAFETY_MODULES_HPP
#define SAFETY_MODULES_HPP

#include "main_modules.hpp"

class safety_modules : public menu_modules, public c_singleton<safety_modules>
{
public:
    void setup();
    void show_all() const;
};

#endif
