#pragma once

#ifndef MISC2_MODULES_HPP
#define MISC2_MODULES_HPP

#include "main_modules.hpp"

class misc2_modules : public menu_modules, public c_singleton<misc2_modules>
{
public:
    void setup();
    void show_all() const;
};

#endif
