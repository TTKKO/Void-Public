#pragma once
#include <mutex>
#include "../../../globals.hpp"
#include "../../assembler/unityengine/transform.hpp"
#include "../../assembler/unityengine/gameobject.hpp"

namespace helpers
{
	class game_manager : public c_singleton<game_manager>
	{
		assembler::unity_engine::game_object* murder_blind_hud_ = nullptr;
		assembler::unity_engine::game_object* murder_flashbang_hud_ = nullptr;
	public:

		void cache();
		void on_join() const;
	};
}