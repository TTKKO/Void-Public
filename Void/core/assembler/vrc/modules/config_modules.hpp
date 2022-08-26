#pragma once

#ifndef CONFIG_MODULES_HPP
#define CONFIG_MODULES_HPP

#include "main_modules.hpp"

class config_modules : public menu_modules, public c_singleton<config_modules>
{
public:
    void setup();
    void show_all() const;
    void hide_all() const;
};

#endif
