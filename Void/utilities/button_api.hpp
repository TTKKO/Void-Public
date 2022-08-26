/*
 *		utilities/buttonapi.hpp
 *		Void
 *
 *		Copyright ? 2021 Azurilex. All rights reserved.
 *		Void's ButtonAPI
 */

#pragma once
#include "../core/assembler/unityengine/transform.hpp"
#include "../core/assembler/unityengine/events/action.hpp"
#include "../core/assembler/unityengine/ui/button.hpp"
#include "../core/assembler/unityengine/ui/slider.hpp"
#include "../detours/cinlinedetour.hpp"
#include "../core/assembler/assembly-csharp/vrcuimanager.hpp"
#include "../core/assembler/assembly-csharp/toggleclickedevent.hpp"
#include "../core/assembler/assembly-csharp/buttonclickedevent.hpp"
#include "../core/assembler/assembly-csharp/slider_slide_event.hpp"
#include "../core/assembler/unityengine/sprite.hpp"
#include "../core/assembler/unityengine/image.hpp"
#include "../core/assembler/unityengine/recttransform.hpp"

class button_base
{
protected:
    static inline assembler::il2cpp::il2cpp_type* slider_binding_type_ = nullptr;
    std::string place_pos_;
    std::string btn_type_;
    assembler::il2cpp::il2cpp_type* tooltip_type_ = nullptr;

public:
    assembler::unity_engine::game_object* button{};

    void set_location(int page, int x, int y);
    void set_tool_tip(std::string_view sv_text);

    void set_active(const bool value) const
    {
        button->set_active(value);
    }

    static assembler::unity_engine::transform* fetch(const std::string_view str)
    {
        return assembler::ui_manager_impl::instance()->get_quickmenu()->get_transform()->find(str);
    }
};

class single_button : public button_base
{
public:
    single_button() = default;
    single_button(std::string_view sv_menu, int page, int x, int y, std::string_view sv_text, const std::function<void()>& f_action, std::string_view sv_tooltip);
    void set_button_text(std::string_view sv_text);
private:
    assembler::tmpro::tmp_text* text_ = nullptr;
    void set_action(const std::function<void()>& f_action) const;
    void init_button(int page, int x, int y, std::string_view sv_text, const std::function<void()>& f_action, std::string_view sv_tooltip);
};

class half_single_button : public button_base
{
public:
    half_single_button() = default;
    half_single_button(std::string_view sv_menu, int page, int x, int y, std::string_view sv_text, const std::function<void()>& f_action, std::string_view sv_tooltip);
    void set_color(const sdk::color& color) const;
    void set_button_text(std::string_view sv_text);
private:
    assembler::tmpro::tmp_text* text_ = nullptr;
    void set_action(const std::function<void()>& f_action) const;
    void set_location(int page, int button_x_loc, int button_y_loc);
    void init_button(int page, int x, int y, std::string_view sv_text, const std::function<void()>& f_action, std::string_view sv_tooltip);
};

class toggle_button : public button_base
{
public:
    toggle_button() = default;
    toggle_button(std::string_view sv_menu, int page, int x, int y, std::string_view sv_text_on, const std::function<void()>& f_action_on, const std::function<void()>& f_action_off, std::string_view sv_tooltip);
    void trigger(bool a = true) const;
private:
    static inline assembler::unity_engine::ui::sprite* toggle_on_ = nullptr;

    void set_image() const;
    void set_location(int page, int button_x_loc, int button_y_loc);
    void set_action(const std::function<void()>& button_on_action, const std::function<void()>& button_off_action) const;
    void set_text(std::string_view button_on_text) const;
    void init_button(int page, int x, int y, std::string_view sv_text_on, const std::function<void()>& f_action_on, const std::function<void()>& f_action_off, std::string_view sv_tooltip);
};

class slider_button : public button_base
{
public:
    assembler::unity_engine::ui::slider* this_slider = nullptr;
    assembler::tmpro::tmp_text* this_text = nullptr;
    slider_button() = default;
    slider_button(std::string_view sv_menu, int page, int y, std::string_view sv_text, std::string_view sv_tooltip);
    void set_action(const std::function<void()>& f_action);
    void set_slider_text(std::string_view sv_text);
private:
    void set_location(int page, int y);
    void init_slider(int page, int y, std::string_view sv_text, std::string_view sv_tooltip);
};
