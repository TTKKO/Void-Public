#include "game_manager.hpp"

void helpers::game_manager::cache()
{
	murder_blind_hud_ = assembler::unity_engine::game_object::find(xorstr_("Game Logic/Player HUD/Blind HUD Anim"));
	murder_flashbang_hud_ = assembler::unity_engine::game_object::find(xorstr_("Game Logic/Player HUD/Flashbang HUD Anim"));
}

void helpers::game_manager::on_join() const
{
	if (murder_blind_hud_)
		murder_blind_hud_->get_transform()->set_local_scale(config::get<bool>(g_context.murder_anti_killcam) ? sdk::vector(0.f, 0.f, 0.f) : sdk::vector(1.f, 1.f, 1.f));

	if (murder_flashbang_hud_)
		murder_flashbang_hud_->get_transform()->set_local_scale(config::get<bool>(g_context.murder_anti_killcam) ? sdk::vector(0.f, 0.f, 0.f) : sdk::vector(1.f, 1.f, 1.f));
}
