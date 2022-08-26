#include "menu_modules.hpp"

void menu_modules::hide() const
{
    for (auto it = toggle_buttons_.begin(); it != toggle_buttons_.end(); ++it)
        (*it)->set_active(false);
    for (auto it = single_buttons_.begin(); it != single_buttons_.end(); ++it)
        (*it)->set_active(false);
}

void menu_modules::show() const
{
	for (auto it = toggle_buttons_.begin(); it != toggle_buttons_.end(); ++it)
        (*it)->set_active(true);
    for (auto it = single_buttons_.begin(); it != single_buttons_.end(); ++it)
        (*it)->set_active(true);
}
