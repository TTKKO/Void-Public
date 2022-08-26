#pragma once

#ifndef MENU_MODULES_HPP
#define MENU_MODULES_HPP

#include "../../../../utilities/button_api.hpp"
#include "../../../../utilities/ingame_logging.hpp"
#include "../../../hooks/helpers/xs_overlay.hpp"

class menu_modules
{
protected:
    static inline const std::string location_ = xorstr_("Container/Window/QMParent/Menu_VoidVR/ScrollRect/Viewport/VerticalLayoutGroup");
    std::vector<std::unique_ptr<toggle_button>> toggle_buttons_{};
    std::vector<std::unique_ptr<single_button>> single_buttons_{};
public:
    void hide() const;
    void show() const;
};

#endif
