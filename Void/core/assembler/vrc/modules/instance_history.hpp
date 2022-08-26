#pragma once

#ifndef INSTANCE_HISTORY_HPP
#define INSTANCE_HISTORY_HPP

#include "main_modules.hpp"

class instance_history : public menu_modules, public c_singleton<instance_history>
{
    std::uint8_t selected_ = -1;
    std::vector<std::string> instance_history_{};
    std::vector<std::unique_ptr<single_button>> info_buttons_{};
public:
    void setup();
    void hide_all() const;
    void show_all();
    void show_info() const;
    void hide_info();
};

#endif
