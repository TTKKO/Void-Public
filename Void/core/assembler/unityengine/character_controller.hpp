#pragma once
#include "collider.hpp"

namespace assembler::unity_engine
{
	struct character_controller : collider
	{
	private:
		inline static il2cpp::il2cpp_type* global_type_ = nullptr;

	public:
		static il2cpp::il2cpp_type* get_global_type()
		{
			if (!global_type_)
				global_type_ = il2cpp::get_type(xorstr_("UnityEngine.CharacterController, UnityEngine.PhysicsModule"));

			return global_type_;
		}

	};
}