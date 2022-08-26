#pragma once

#ifndef MURDER4_SUBMENU_HPP
#define MURDER4_SUBMENU_HPP

#include "../customization_modules.hpp"

class murder_submenu : public menu_modules, public c_singleton<murder_submenu>
{
public:
    void setup();
    void show_all() const;
};

#endif
