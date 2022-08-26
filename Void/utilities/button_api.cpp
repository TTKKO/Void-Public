#include "button_api.hpp"
#include "drawing.hpp"

#pragma region base
void button_base::set_location(const int page, const int x, const int y)
{
	const auto transform = button->get_transform();

	auto transform_vector = sdk::vector(-348.f, -100.f, 0.f);
	transform_vector.x += 230.f * static_cast<float>(x);
	transform_vector.y += 210.f * static_cast<float>(y);

	transform->set_local_position(transform_vector);

	const auto fmt = utility::format(xorstr_("{}{:d} ({:d},{:d})"), btn_type_, page, x, y);
	button->set_name(place_pos_ + xorstr_("/") + btn_type_ + fmt);
}

//: MonoBehaviour, IPointerEnterHandler, IEventSystemHandler, IPointerExitHandler
void button_base::set_tool_tip(const std::string_view sv_text)
{
	// @xref: private static readonly ǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅ<string> <ǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅ>k__BackingField; // 0x0
	// @xref: public string whatthefuck; // 0x18
	// @xref: public string whatthefuck; // 0x20
	// @xref: private bool whatthefuck; // 0x28
	// @xref: private bool whatthefuck; // 0x29

	if (!tooltip_type_)
		tooltip_type_ = assembler::il2cpp::get_type(xorstr_(L"ÏÌÍÏÎÍÏÎÌÏÌÌÎÌÌÏÍÌÎÏÏÌÍ, VRC.UI.Elements.dll"));

	const auto comps = button->get_components(tooltip_type_);

	if (!comps)
		return;

	for (std::size_t i = 0; i < comps->max_length; ++i)
	{
		if (i > 0)
		{
			assembler::unity_engine::object::destroy(comps->at(i));
			continue;
		}

		*reinterpret_cast<assembler::il2cpp::il2cpp_string**>(reinterpret_cast<std::uint8_t*>(comps->at(i)) + 0x18) = assembler::il2cpp::string_new(sv_text);
		*reinterpret_cast<assembler::il2cpp::il2cpp_string**>(reinterpret_cast<std::uint8_t*>(comps->at(i)) + 0x20) = assembler::il2cpp::string_new(sv_text);
	}
}
#pragma endregion

#pragma region single_button
single_button::single_button(const std::string_view sv_menu, const int page, const int x, const int y, const std::string_view sv_text, const std::function<void()>& f_action, const std::string_view sv_tooltip)
{
	place_pos_ = sv_menu;
	btn_type_ = xorstr_("Single");
	init_button(page, x, y, sv_text, f_action, sv_tooltip);
}

void single_button::set_button_text(const std::string_view sv_text)
{
	if (!text_)
		text_ = reinterpret_cast<assembler::tmpro::tmp_text*>(button->get_transform()->find(xorstr_("Text_H4"))->get_transform()->get_component(xorstr_("TMPro.TextMeshProUGUI")));
	text_->set_text(sv_text);
}

void single_button::set_action(const std::function<void()>& f_action) const
{
	const auto btn = reinterpret_cast<assembler::unity_engine::ui::button*>(button->get_component(xorstr_("UnityEngine.UI.Button")));
	btn->set_on_click(assembler::unity_engine::ui::button_clicked_event::ctor());
	btn->get_on_click()->add_listener(assembler::unity_engine::events::unity_action::ctor(create_detour(f_action)));
}

void single_button::init_button(const int page, const int x, const int y, const std::string_view sv_text, const std::function<void()>& f_action, const std::string_view sv_tooltip)
{
	assembler::unity_engine::transform* btn_template = fetch(xorstr_("Container/Window/QMParent/Menu_Dashboard/ScrollRect/Viewport/VerticalLayoutGroup/Buttons_QuickActions/SitStandCalibrateButton/Button_CalibrateFBT"));

	button = reinterpret_cast<assembler::unity_engine::game_object*>(assembler::unity_engine::object::instantiate(btn_template->get_game_object(), fetch(place_pos_), true));
	button->get_transform()->set_local_position(sdk::vector(-348, -100, 0));
	assembler::unity_engine::object::destroy(button->get_transform()->find(xorstr_("Icon"))->get_transform()->get_game_object());

	button->get_transform()->find(xorstr_("Text_H4"))->get_transform()->set_local_position(sdk::vector(0.f, -25.f, 0.f));
	reinterpret_cast<assembler::unity_engine::ui::graphic*>(button->get_transform()->find(xorstr_("Background"))->get_component(xorstr_("UnityEngine.UI.Image")))->set_color(sdk::color(1.f, 0.7f, 0.9f, 1.f));

	set_location(page, x, y);
	set_button_text(sv_text);
	set_tool_tip(sv_tooltip);
	set_action(f_action);

	button->set_active(true);
}
#pragma endregion

#pragma region half_single_button
half_single_button::half_single_button(const std::string_view sv_menu, const int page, const int x, const int y, const std::string_view sv_text, const std::function<void()>& f_action, const std::string_view sv_tooltip)
{
	place_pos_ = sv_menu;
	btn_type_ = xorstr_("Half");
	init_button(page, x, y, sv_text, f_action, sv_tooltip);
}

void half_single_button::set_color(const sdk::color& color) const
{
	text_->set_color(color);
}

void half_single_button::set_button_text(const std::string_view sv_text)
{
	if (!text_)
		text_ = reinterpret_cast<assembler::tmpro::tmp_text*>(button->get_transform()->find(xorstr_("Text_H4"))->get_transform()->get_component(xorstr_("TMPro.TextMeshProUGUI")));

	text_->set_text(sv_text);
}

void half_single_button::set_action(const std::function<void()>& f_action) const
{
	const auto btn = reinterpret_cast<assembler::unity_engine::ui::button*>(button->get_component(xorstr_("UnityEngine.UI.Button")));
	btn->set_on_click(assembler::unity_engine::ui::button_clicked_event::ctor());
	btn->get_on_click()->add_listener(assembler::unity_engine::events::unity_action::ctor(create_detour(f_action)));
}

void half_single_button::set_location(const int page, const int button_x_loc, const int button_y_loc)
{
	const auto transform = button->get_transform();

	auto transform_vector = sdk::vector(-348.f, -12.f, 0.f);
	transform_vector.x += 230.f * static_cast<float>(button_x_loc);
	transform_vector.y += 105.f * static_cast<float>(button_y_loc);

	transform->set_local_position(transform_vector);

	const auto fmt = utility::format(xorstr_("{}{:d} ({:d},{:d})"), btn_type_, page, button_x_loc, button_y_loc);
	button->set_name(place_pos_ + xorstr_("/") + btn_type_ + fmt);
}

void half_single_button::init_button(const int page, const int x, const int y, const std::string_view sv_text, const std::function<void()>& f_action, const std::string_view sv_tooltip)
{
	assembler::unity_engine::transform* btn_template = fetch(xorstr_("Container/Window/QMParent/Menu_Dashboard/ScrollRect/Viewport/VerticalLayoutGroup/Buttons_QuickActions/SitStandCalibrateButton/Button_CalibrateFBT"));
	button = reinterpret_cast<assembler::unity_engine::game_object*>(assembler::unity_engine::object::instantiate(btn_template->get_game_object(), fetch(place_pos_), true));
	button->get_transform()->set_local_position(sdk::vector(-348, -12, 0));
	assembler::unity_engine::object::destroy(button->get_transform()->find(xorstr_("Icon"))->get_transform()->get_game_object());
	button->get_transform()->find(xorstr_("Text_H4"))->get_transform()->set_local_position(sdk::vector(0.f, -65.f, 0.f));

	const auto background = button->get_transform()->find(xorstr_("Background"));
	reinterpret_cast<assembler::unity_engine::ui::graphic*>(background->get_component(xorstr_("UnityEngine.UI.Image")))->set_color(sdk::color(1.f, 0.7f, 0.9f, 1.f));
	reinterpret_cast<assembler::unity_engine::rect_transform*>(background->get_component(xorstr_("RectTransform")))->set_anchor_max(sdk::vector_2d(1.f, 0.5f));

	set_location(page, x, y);
	set_button_text(sv_text);
	set_tool_tip(sv_tooltip);
	set_action(f_action);

	button->set_active(true);
}
#pragma endregion

#pragma region toggle_button
void toggle_button::set_image() const
{
	if (!toggle_on_)
		toggle_on_ = assembler::unity_engine::ui::sprite::create_custom(64, 64, byte_resources::checkmark);

	const auto icon = button->get_transform()->find(xorstr_("Icon_On"));

	if (!icon)
		return;

	const auto image = static_cast<assembler::unity_engine::ui::image*>(icon->get_component(xorstr_("UnityEngine.UI.Image")));

	if (!image)
		return;

	image->set_sprite(toggle_on_);
}

void toggle_button::set_location(const int page, const int button_x_loc, const int button_y_loc)
{
	const auto transform = button->get_transform();

	auto transform_vector = sdk::vector(-348.f, -132.f, 0.f);
	transform_vector.x += 230.f * static_cast<float>(button_x_loc);
	transform_vector.y += 210.f * static_cast<float>(button_y_loc); // @note: offset

	transform->set_local_position(transform_vector);

	const auto fmt = utility::format(xorstr_("{}{:d} ({:d},{:d})"), btn_type_, page, button_x_loc, button_y_loc);
	button->set_name(place_pos_ + xorstr_("/") + btn_type_ + fmt);
}

toggle_button::toggle_button(const std::string_view sv_menu, const int page, const int x, const int y, const std::string_view sv_text_on, const std::function<void()>& f_action_on, const std::function<void()>& f_action_off, const std::string_view sv_tooltip)
{
	place_pos_ = sv_menu;
	btn_type_ = xorstr_("Toggle");
	init_button(page, x, y, sv_text_on, f_action_on, f_action_off, sv_tooltip);
}

void toggle_button::trigger(const bool a) const
{
	const auto button_component = reinterpret_cast<assembler::unity_engine::ui::toggle*>(button->get_component(xorstr_("UnityEngine.UI.Toggle")));
	button_component->set(a);
}

void toggle_button::set_action(const std::function<void()>& button_on_action, const std::function<void()>& button_off_action) const
{
	const auto button_component = reinterpret_cast<assembler::unity_engine::ui::toggle*>(button->get_component(xorstr_("UnityEngine.UI.Toggle")));

	button_component->set_toggle(assembler::unity_engine::ui::toggle_clicked_event::ctor());
	button_component->get_toggle()->add_listener(assembler::unity_engine::events::unity_action::ctor(create_detour([=]
	{
		if (!button_component->get_state())
			button_on_action();
		else
			button_off_action();
	})));
}

void toggle_button::set_text(const std::string_view button_on_text) const
{
	const auto text_component = reinterpret_cast<assembler::tmpro::tmp_text*>(button->get_transform()->find(xorstr_("Text_H4"))->get_transform()->get_component(xorstr_("TMPro.TextMeshProUGUI")));
	text_component->set_text(button_on_text);
}

void toggle_button::init_button(const int page, const int x, const int y, const std::string_view sv_text_on, const std::function<void()>& f_action_on, const std::function<void()>& f_action_off, const std::string_view sv_tooltip)
{
	assembler::unity_engine::transform* btn_template = fetch(xorstr_("Container/Window/QMParent/Menu_Settings/Panel_QM_ScrollRect/Viewport/VerticalLayoutGroup/Buttons_UI_Elements_Row_2/Button_ToggleFallbackIcon"));

	button = reinterpret_cast<assembler::unity_engine::game_object*>(assembler::unity_engine::object::instantiate(btn_template->get_game_object(), fetch(place_pos_), true));
	button->get_transform()->set_local_position(sdk::vector(-348, -100, 0));

	reinterpret_cast<assembler::unity_engine::ui::graphic*>(button->get_transform()->find(xorstr_("Background"))->get_component(xorstr_("UnityEngine.UI.Image")))->set_color(sdk::color(1.f, 0.7f, 0.9f, 1.f));

	set_image();
	set_location(page, x, y);
	set_text(sv_text_on);
	set_tool_tip(sv_tooltip);
	set_action(f_action_off, f_action_on);

	button->set_active(true);
}
#pragma endregion

#pragma region slider_button
slider_button::slider_button(const std::string_view sv_menu, const int page, const int y, const std::string_view sv_text, const std::string_view sv_tooltip)
{
	place_pos_ = sv_menu;
	btn_type_ = xorstr_("Slider");
	init_slider(page, y, sv_text, sv_tooltip);
}

void slider_button::set_location(const int page, const int y)
{
	const auto transform = button->get_transform();

	sdk::vector transform_vector = transform->get_local_position();
	transform_vector.x = -80.f;
	transform_vector.y += 90.f * static_cast<float>(y);

	transform->set_local_position(transform_vector);

	const auto fmt = utility::format(xorstr_("{}{:d} ({:d})"), btn_type_, page, y);
	button->set_name(btn_type_ + fmt);
}

void slider_button::set_slider_text(const std::string_view sv_text)
{
	if (!this_text)
	{
		const auto text = button->get_transform()->find(xorstr_("Text_QM_H4"))->get_transform();
		this_text = reinterpret_cast<assembler::tmpro::tmp_text*>(text->get_component(xorstr_("TMPro.TextMeshProUGUI")));
		text->set_local_position(sdk::vector(-300.f, 40.f, 0.f));
		this_text->set_word_wrapping(false);
	}

	this_text->set_text(sv_text);
}

void slider_button::set_action(const std::function<void()>& f_action)
{
	const auto slider = button->get_transform()->find(xorstr_("Slider"));

	// @xref: public Slider whatthefuck; // 0x18
	// @xref: private ǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅ<float> ǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅ; // 0x20

	if (!slider_binding_type_)
		slider_binding_type_ = assembler::il2cpp::get_type(xorstr_(L"ÌÎÎÌÍÍÌÎÏÌÎÌÎÌÍÏÍÌÎÏÏÌÌ, DataModel.dll"));

	// @note: fixes lag
	const auto bind = reinterpret_cast<assembler::unity_engine::component*>(slider->get_component(slider_binding_type_));
	assembler::unity_engine::object::destroy(bind);

	this_slider = reinterpret_cast<assembler::unity_engine::ui::slider*>(slider->get_component(xorstr_("UnityEngine.UI.Slider")));
	this_slider->set_on_slide(assembler::unity_engine::ui::slider_clicked_event::ctor());
	this_slider->get_on_slide()->add_listener(assembler::unity_engine::events::unity_action::ctor(create_detour(f_action)));
}

void slider_button::init_slider(const int page, const int y, const std::string_view sv_text, const std::string_view sv_tooltip)
{
	assembler::unity_engine::transform* btn_template = fetch(xorstr_("Container/Window/QMParent/Menu_AudioSettings/Content/Audio/VolumeSlider_World"));

	button = reinterpret_cast<assembler::unity_engine::game_object*>(assembler::unity_engine::object::instantiate(btn_template->get_game_object(), fetch(place_pos_), true));
	button->get_transform()->set_local_position(sdk::vector(-348, -100, 0));

	set_location(page, y);
	set_slider_text(sv_text);
	set_tool_tip(sv_tooltip);

	button->set_active(true);
}
#pragma endregion
