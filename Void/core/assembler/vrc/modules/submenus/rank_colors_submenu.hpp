#pragma once

#ifndef RANK_COLORS_SUBMENU_HPP
#define RANK_COLORS_SUBMENU_HPP

#include "../customization_modules.hpp"

class rank_colors_submenu : public menu_modules, public c_singleton<rank_colors_submenu>
{
    std::vector<std::unique_ptr<slider_button>> slider_buttons_{};
    std::vector<std::unique_ptr<half_single_button>> hs_buttons_{};
    std::int8_t selected_ = -1;

    void update_values() const;
public:
    void setup();
    void show_all();
    void hide_all() const;
};

#endif
