#pragma once

#ifndef GAME_MODULES_HPP
#define GAME_MODULES_HPP

#include "main_modules.hpp"
#include "submenus/murder4_submenu.hpp"

class game_modules : public menu_modules, public c_singleton<game_modules>
{
public:
    void setup();
    void show_all() const;
    void hide_all() const;
};

#endif
