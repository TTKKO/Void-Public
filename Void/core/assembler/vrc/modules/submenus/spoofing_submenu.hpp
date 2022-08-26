#pragma once

#ifndef SPOOFING_SUBMENU_HPP
#define SPOOFING_SUBMENU_HPP

#include "../customization_modules.hpp"

class spoofing_submenu : public menu_modules, public c_singleton<spoofing_submenu>
{
    std::vector<std::unique_ptr<slider_button>> slider_buttons_{};
    std::vector<std::unique_ptr<half_single_button>> hs_buttons_{};
    std::int8_t selected_ = -1;

    std::vector<assembler::tmpro::tmp_text*> text_{};

public:
    void setup();
    void show_all() const;
    void hide_all() const;
};

#endif
