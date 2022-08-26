#ifndef PORTABLE_MIRROR_HPP
#define PORTABLE_MIRROR_HPP

#pragma once
#include "../../assembler/unityengine/transform.hpp"
#include "../../assembler/unityengine/boxcollider.hpp"
#include "../../assembler/unityengine/meshrenderer.hpp"
#include "../../assembler/unityengine/material.hpp"
#include "../../assembler/unityengine/rigidbody.hpp"
#include "../../assembler/unityengine/shader.hpp"
#include "../../assembler/vrc/sdkbase/vrc_mirror_reflection.hpp"
#include "../../assembler/vrc/sdkbase/vrc_pickup.hpp"
#include "../../assembler/assembly-csharp/vrcplayer.hpp"
#include "../../globals.hpp"

namespace helpers
{
	class portable_mirror : public c_singleton<portable_mirror>
	{
		assembler::unity_engine::game_object* mirror_ = nullptr;
	public:
		void update_optimization(bool value) const;
		void update_pickupable(bool value) const;
		void update_scaling(float x, float y) const;
		void reset_position() const;
		void cleanup();
		void toggle_mirror();
	};
}

#endif