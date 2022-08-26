#pragma once

#ifndef LOVENSE_MODULES_HPP
#define LOVENSE_MODULES_HPP

#include "main_modules.hpp"

class lovense_modules : public menu_modules, public c_singleton<lovense_modules>
{
    std::vector<std::unique_ptr<slider_button>> slider_buttons_;
    std::vector<std::unique_ptr<half_single_button>> hs_buttons_;
    std::vector<assembler::tmpro::tmp_text*> text_{};

    std::float_t vibration_speed_ = 0.f;
    std::float_t rotation_speed_ = 0.f;

    bool connection_established_ = false;

    bool modifying_vibration_ = false;
    bool modifying_rotation_ = false;
public:
    void setup();

    void increase_vibration();
    void decrease_vibration();

    void show_all() const;
    void hide_all() const;
};

#endif
