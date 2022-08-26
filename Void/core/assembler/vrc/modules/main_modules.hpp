#pragma once

#ifndef MAIN_MODULES_HPP
#define MAIN_MODULES_HPP

#include "menu_modules.hpp"
#include "config_modules.hpp"
#include "safety_modules.hpp"
#include "safety2_modules.hpp"
#include "misc_modules.hpp"
#include "misc2_modules.hpp"
#include "utility_modules.hpp"
#include "customization_modules.hpp"
#include "instance_history.hpp"
#include "lovense_modules.hpp"
#include "game_modules.hpp"
#include "portable_mirror_modules.hpp"

class main_modules : public menu_modules, public c_singleton<main_modules>
{
public:
    void setup();
    void show_back() const;
    void show_main() const;
    void no_back() const;
    void back() const;
};

#endif
