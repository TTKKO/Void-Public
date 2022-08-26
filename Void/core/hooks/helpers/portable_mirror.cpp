#include "portable_mirror.hpp"

void helpers::portable_mirror::update_optimization(const bool value) const
{
	if (!mirror_)
		return;

	if (!assembler::vrc_player::get_current())
		return;

	auto mirror_reflection = static_cast<assembler::vrc::sdk_base::vrc_mirror_reflection*>(mirror_->get_component(xorstr_("VRC_MirrorReflection")));
	if (!mirror_reflection)
		mirror_reflection = static_cast<assembler::vrc::sdk_base::vrc_mirror_reflection*>(mirror_->add_component_str(xorstr_("VRC_MirrorReflection")));

	mirror_reflection->set_reflection_layers(value ? 263680 : -1025);
}

void helpers::portable_mirror::update_pickupable(const bool value) const
{
	if (!mirror_)
		return;

	if (!assembler::vrc_player::get_current())
		return;

	auto pickup = static_cast<assembler::vrc::sdk_base::vrc_pickup*>(mirror_->get_component(xorstr_("VRC_Pickup")));
	if (!pickup)
		pickup = static_cast<assembler::vrc::sdk_base::vrc_pickup*>(mirror_->add_component_str(xorstr_("VRC_Pickup")));

	pickup->set_pickupable(value);
}

void helpers::portable_mirror::update_scaling(const float x, const float y) const
{
	if (!mirror_)
		return;

	if (!assembler::vrc_player::get_current())
		return;

	const auto mirror_transform = mirror_->get_transform();

	const auto current_pos = mirror_transform->get_position();
	const auto current_scale = mirror_transform->get_local_scale();

	mirror_transform->set_local_scale(sdk::vector(x, y, 1.f));
	mirror_transform->set_position(sdk::vector(current_pos.x, current_pos.y + (y - current_scale.y) / 2, current_pos.z));
}

void helpers::portable_mirror::reset_position() const
{
	if (!mirror_)
		return;

	const auto player = assembler::vrc_player::get_current();

	if (!player)
		return;

	const auto player_transform = player->get_transform();
	const auto mirror_transform = mirror_->get_transform();

	auto position = player_transform->get_position() + player_transform->get_forward();
	position.y += config::get<float>(g_context.mirror_scale_y) / 2.f;

	mirror_transform->set_position(position);
	mirror_transform->set_rotation(player_transform->get_rotation());
	mirror_transform->set_local_scale(sdk::vector(config::get<float>(g_context.mirror_scale_x), config::get<float>(g_context.mirror_scale_y), 1.f));
}

void helpers::portable_mirror::cleanup()
{
	if (mirror_)
		mirror_ = nullptr;
}

void helpers::portable_mirror::toggle_mirror()
{
	if (mirror_)
	{
		assembler::unity_engine::object::destroy(mirror_);
		mirror_ = nullptr;
	}
	else
	{
		const auto player = assembler::vrc_player::get_current();

		if (!player)
			return;

		const auto player_transform = player->get_transform();

		if (!player_transform)
			return;

		auto position = player_transform->get_position() + player_transform->get_forward();
		position.y += config::get<float>(g_context.mirror_scale_y) / 2.f;
		
		const auto mirror = assembler::unity_engine::game_object::create_primitive(5); // @note: QUAD

		if (!mirror)
			return;

		const auto mirror_transform = mirror->get_transform();

		mirror_transform->set_position(position);
		mirror_transform->set_rotation(player_transform->get_rotation());
		mirror_transform->set_local_scale(sdk::vector(config::get<float>(g_context.mirror_scale_x), config::get<float>(g_context.mirror_scale_y), 1.f));

		mirror->set_name(xorstr_("VOID_MIRROR"));

		assembler::unity_engine::object::destroy(mirror->get_component(xorstr_("Collider")));

		auto box_collider = static_cast<assembler::unity_engine::boxcollider*>(mirror->get_component(xorstr_("BoxCollider")));
		if (!box_collider)
			box_collider = static_cast<assembler::unity_engine::boxcollider*>(mirror->add_component_str(xorstr_("BoxCollider")));

		box_collider->set_size(sdk::vector(1.f, 1.f, 0.05f));
		box_collider->set_is_trigger(true);

		auto meshrenderer = static_cast<assembler::unity_engine::meshrenderer*>(mirror->get_component(xorstr_("MeshRenderer")));
		if (!meshrenderer)
			meshrenderer = static_cast<assembler::unity_engine::meshrenderer*>(mirror->add_component_str(xorstr_("MeshRenderer")));

		meshrenderer->get_material()->set_shader(assembler::unity_engine::shader::find(xorstr_(L"FX/MirrorReflection")));

		auto mirror_reflection = static_cast<assembler::vrc::sdk_base::vrc_mirror_reflection*>(mirror->get_component(xorstr_("VRC_MirrorReflection")));
		if (!mirror_reflection)
			mirror_reflection = static_cast<assembler::vrc::sdk_base::vrc_mirror_reflection*>(mirror->add_component_str(xorstr_("VRC_MirrorReflection")));

		mirror_reflection->set_reflection_layers(config::get<bool>(g_context.optimized_mirror) ? 263680 : -1025);
		mirror_reflection->set_resolution(assembler::vrc::sdk_base::vrc_mirror_reflection::dimension::x2048);

		auto pickup = static_cast<assembler::vrc::sdk_base::vrc_pickup*>(mirror->get_component(xorstr_("VRC_Pickup")));
		if (!pickup)
			pickup = static_cast<assembler::vrc::sdk_base::vrc_pickup*>(mirror->add_component_str(xorstr_("VRC_Pickup")));

		pickup->set_proximity(0.3f);
		pickup->set_pickupable(config::get<bool>(g_context.mirror_pickup));
		pickup->set_allow_manipulation_when_equipped(false);

		auto rigidbody = static_cast<assembler::unity_engine::rigidbody*>(mirror->get_component(xorstr_("Rigidbody")));
		if (!rigidbody)
			rigidbody = static_cast<assembler::unity_engine::rigidbody*>(mirror->add_component_str(xorstr_("Rigidbody")));

		rigidbody->set_use_gravity(false);
		rigidbody->set_is_kinematic(true);

		mirror_ = mirror;
	}
}
