#include "camera_handler.hpp"

assembler::unity_engine::camera* helpers::camera::create_camera(mode type, const sdk::vector& rotation, const float fov) const
{
	const auto go = assembler::unity_engine::game_object::cctor(std::to_string(static_cast<std::int32_t>(type)) + xorstr_("Camera"));
	const auto transform = go->get_transform();

	if (!transform)
		return nullptr;

	const auto ref_transform = reference_camera_->get_transform();

	transform->set_local_scale(ref_transform->get_local_scale());
	transform->set_parent(ref_transform);
	transform->set_rotation(ref_transform->get_rotation());
	transform->rotate(rotation, 1);
	transform->set_position(ref_transform->get_position() + transform->get_forward() * -2.f);

	const auto cam = static_cast<assembler::unity_engine::camera*>(go->add_component(xorstr_("UnityEngine.Camera, UnityEngine.CoreModule")));

	if (!cam)
		return nullptr;

	cam->set_enabled(false);
	cam->set_field_of_view(fov);
	cam->set_near_clip_plane(cam->get_near_clip_plane() / 4.f);

	return cam;
}

bool helpers::camera::initialize()
{
	auto camera_object = assembler::unity_engine::game_object::find(xorstr_("Camera (eye)"));

	if (!camera_object)
	{
		camera_object = assembler::unity_engine::game_object::find(xorstr_("CenterEyeAnchor"));

		if (!camera_object)
			return false;
	}

	reference_camera_ = static_cast<assembler::unity_engine::camera*>(camera_object->get_component(assembler::il2cpp::get_type(xorstr_("UnityEngine.Camera, UnityEngine.CoreModule"))));

	if (!reference_camera_)
		return false;

	camera_back_ = create_camera(mode::back, sdk::vector(), 75.f);
	camera_front_ = create_camera(mode::front, sdk::vector(0.f, 180.f, 0.f), 75.f);

	if (!camera_back_ || !camera_front_)
		return false;

	return true;
}

bool helpers::camera::toggle(const mode val)
{
	if (!camera_back_ || !camera_front_ || val > mode::front || val < mode::no_value)
		return false;

	if (val == mode::no_value)
	{
		switch (current_mode_)
		{
		case mode::off:
			{
				current_mode_ = mode::back;
				camera_back_->set_enabled(true);
				camera_front_->set_enabled(false);
				break;
			}
		case mode::back:
			{
				current_mode_ = mode::front;
				camera_back_->set_enabled(false);
				camera_front_->set_enabled(true);
				break;
			}
		case mode::front:
			{
				current_mode_ = mode::off;
				camera_back_->set_enabled(false);
				camera_front_->set_enabled(false);
				break;
			}

		case mode::no_value: break;
		}
	}
	else
	{
		switch (val)
		{
		case mode::off:
		{
			current_mode_ = val;
			camera_back_->set_enabled(false);
			camera_front_->set_enabled(false);
			break;
		}
		case mode::back:
		{
			current_mode_ = val;
			camera_back_->set_enabled(true);
			camera_front_->set_enabled(false);
			break;
		}
		case mode::front:
		{
			current_mode_ = val;
			camera_back_->set_enabled(false);
			camera_front_->set_enabled(true);
			break;
		}

		case mode::no_value: break;
		}
	}

	return true;
}

void helpers::camera::handle() const
{
	if (current_mode_ == mode::off || !camera_back_ || !camera_front_)
		return;

	if (const auto scroll = assembler::unity_engine::input::get_axis(xorstr_("Mouse ScrollWheel")); scroll > 0.f)
	{
		const auto back_transform = camera_back_->get_transform();
		const auto front_transform = camera_front_->get_transform();

		back_transform->set_position(back_transform->get_position() + back_transform->get_forward() * 0.1f);
		front_transform->set_position(front_transform->get_position() - front_transform->get_forward() * 0.1f);
	}
	else if (scroll < 0.f)
	{
		const auto back_transform = camera_back_->get_transform();
		const auto front_transform = camera_front_->get_transform();

		back_transform->set_position(back_transform->get_position() - back_transform->get_forward() * 0.1f);
		front_transform->set_position(front_transform->get_position() + front_transform->get_forward() * 0.1f);
	}
}
