#pragma once

#ifndef CUSTOMIZATION_MODULES_HPP
#define CUSTOMIZATION_MODULES_HPP

#include "main_modules.hpp"
#include "submenus/rank_colors_submenu.hpp"
#include "submenus/notifier_submenu.hpp"
#include "submenus/spoofing_submenu.hpp"

class customization_modules : public menu_modules, public c_singleton<customization_modules>
{
public:
    void setup();
    void show_all() const;
    void hide_all() const;
};

#endif
