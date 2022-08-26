#pragma once

#ifndef MISC_MODULES_HPP
#define MISC_MODULES_HPP

#include "main_modules.hpp"

class misc_modules : public menu_modules, public c_singleton<misc_modules>
{
public:
    void setup();
    void show_all() const;
};

#endif
