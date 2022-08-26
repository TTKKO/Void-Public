#include "ingame_logging.hpp"

bool ingame_logging::update()
{
	for (std::size_t i = 0; i < log_list_.size(); i++)
	{
		if (log_list_.size() <= 9)
			break;

		std::lock_guard log_lock(m_lock_);
		log_list_.erase(log_list_.begin());
	}

	const float position = static_cast<float>(log_list_.size()) * -13.1f + 13.1f;

	std::stringstream opt;
	std::ranges::copy(log_list_, std::ostream_iterator<std::string>(opt, xorstr_("\r\n")));

	assembler::unity_engine::transform* text = assembler::ui_manager_impl::instance()->get_quickmenu()->get_transform()->find(xorstr_("Container/Window/QMParent/Menu_Dashboard/ScrollRect/Viewport/VerticalLayoutGroup/Carousel_Banners/VOIDDEBUG"));

	if (!text)
		return false;

	const auto component = reinterpret_cast<assembler::tmpro::tmp_text*>(text->get_component(xorstr_("TMPro.TextMeshProUGUI")));

	if (!component)
		return false;

	component->set_color({255, 255, 255, 255});
	component->set_text(opt.str());
	text->set_local_position(sdk::vector(-450.f, 85.f + position, 0.f));

	return true;
}

bool ingame_logging::update_shadow()
{
	for (std::size_t i = 0; i < log_list_.size(); i++)
	{
		if (log_list_.size() <= 9)
			break;

		std::lock_guard log_lock(m_lock_);
		log_list_.erase(log_list_.begin());
	}

	std::stringstream opt;
	std::ranges::copy(log_list_, std::ostream_iterator<std::string>(opt, xorstr_("\r\n")));

	const float position = static_cast<float>(log_list_.size()) * -13.1f + 13.1f;
	const auto out = std::regex_replace(opt.str(), std::regex(xorstr_("(<color=#?\\w+)>")), xorstr_("<color=black>"));

	assembler::unity_engine::transform* text = assembler::ui_manager_impl::instance()->get_quickmenu()->get_transform()->find(xorstr_("Container/Window/QMParent/Menu_Dashboard/ScrollRect/Viewport/VerticalLayoutGroup/Carousel_Banners/VOIDDEBUGSHADOW"));

	if (!text)
		return false;

	const auto component = reinterpret_cast<assembler::tmpro::tmp_text*>(text->get_component(xorstr_("TMPro.TextMeshProUGUI")));

	if (!component)
		return false;

	component->set_color({0, 0, 0, 255});
	component->set_text(out);
	text->set_local_position(sdk::vector(-455.f, 81.5f + position, 0.f));

	return true;
}
