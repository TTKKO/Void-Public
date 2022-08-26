#pragma once

#ifndef NOTIFIER_SUBMENU_HPP
#define NOTIFIER_SUBMENU_HPP

#include "../customization_modules.hpp"

class notifier_submenu : public menu_modules, public c_singleton<notifier_submenu>
{
public:
    void setup();
    void show_all() const;
    void hide_all() const;
};

#endif
