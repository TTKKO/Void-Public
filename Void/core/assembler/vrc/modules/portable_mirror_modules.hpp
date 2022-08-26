#pragma once

#ifndef PORTABLE_MIRROR_MODULES_HPP
#define PORTABLE_MIRROR_MODULES_HPP

#include "main_modules.hpp"
#include "../../../hooks/helpers/portable_mirror.hpp"

class portable_mirror_modules : public menu_modules, public c_singleton<portable_mirror_modules>
{
    std::vector<std::unique_ptr<slider_button>> slider_buttons_;

public:
    void setup();

    void show_all() const;
    void hide_all() const;
};

#endif
