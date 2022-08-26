#pragma once

#ifndef SAFETY2_MODULES_HPP
#define SAFETY2_MODULES_HPP

#include "main_modules.hpp"

class safety2_modules : public menu_modules, public c_singleton<safety2_modules>
{
public:
    void setup();
    void show_all() const;
};

#endif
