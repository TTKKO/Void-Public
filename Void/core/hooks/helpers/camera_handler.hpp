#pragma once
#include "../../assembler/unityengine/camera.hpp"
#include "../../assembler/unityengine/transform.hpp"
#include "../../assembler/unityengine/input.hpp"

namespace helpers {
	class camera : public c_singleton<camera>
	{
	public:

		enum class mode : std::int32_t
		{
			no_value = -1,
			off,
			back,
			front
		};

	private:
		assembler::unity_engine::camera* camera_back_ = nullptr;
		assembler::unity_engine::camera* camera_front_ = nullptr;
		assembler::unity_engine::camera* reference_camera_ = nullptr;
		mode current_mode_ = mode::off;

		assembler::unity_engine::camera* create_camera(mode type, const sdk::vector& rotation, float fov) const;
	public:
		bool initialize();
		bool toggle(mode val = mode::no_value);
		void handle() const;
	};
}
