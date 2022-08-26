#include "assetbundle_processor.hpp"

bool helpers::assetbundle_processor::confirm_material(assembler::unity_engine::material* m, std::uint64_t count)
{
	auto shader_name = m->get_shader()->get_ws_name();
	utility::unicode_tolower(shader_name);

	if (shader_name.contains(xorstr_(L"particle")) && count / 3 > 12000)
		return false;

	return true;
}

void helpers::assetbundle_processor::scan_transforms() const
{
	const auto transforms = assembler::il2cpp::array_to_vector<assembler::unity_engine::transform*>(assetbundle_->get_components_in_children(assembler::unity_engine::transform::get_global_type(), true));

	for (const auto transform : transforms)
	{
		// @note: child hardlimit
		if (const auto count = transform->child_count(); count > 72)
			for (std::int32_t i = 0; i < count; ++i)
				assembler::unity_engine::object::destroy_immediate(transform->get_child(i)->get_game_object(), true);
	}
}

void helpers::assetbundle_processor::scan_rigidbodies() const
{
	if (!rigidbody_type_)
		rigidbody_type_ = assembler::il2cpp::get_type(xorstr_("UnityEngine.Rigidbody, UnityEngine.PhysicsModule"));

	const auto rigidbodies = assembler::il2cpp::array_to_vector<assembler::unity_engine::object*>(assetbundle_->get_components_in_children(rigidbody_type_, true));

	// @note: hardlimit
	for (std::size_t i = 5; i < rigidbodies.size(); i++)
		assembler::unity_engine::object::destroy_immediate(rigidbodies[i]);
}

void helpers::assetbundle_processor::scan_spherecolliders() const
{
	const auto spherecolliders = assembler::il2cpp::array_to_vector<assembler::unity_engine::spherecollider*>(assetbundle_->get_components_in_children(assembler::unity_engine::spherecollider::get_global_type(), true));

	for (std::size_t i = 0; i < spherecolliders.size(); i++)
	{
		if (i > 5)
		{
			// @note: hardlimit
			spherecolliders[i]->set_enabled(false);
			continue;
		}

		// @note: bounds is too big
		if (const sdk::vector v = spherecolliders[i]->get_bounds()[1]; v.x > 50.f || v.y > 50.f || v.z > 50.f)
			spherecolliders[i]->set_enabled(false);

		// @note: radius is too big
		if (spherecolliders[i]->get_radius() > 5.f)
			spherecolliders[i]->set_enabled(false);
	}
}

void helpers::assetbundle_processor::scan_boxcolliders() const
{
	const auto boxcolliders = assembler::il2cpp::array_to_vector<assembler::unity_engine::boxcollider*>(assetbundle_->get_components_in_children(assembler::unity_engine::boxcollider::get_global_type(), true));

	for (std::size_t i = 0; i < boxcolliders.size(); i++)
	{
		if (i > 5)
		{
			// @note: hardlimit
			boxcolliders[i]->set_enabled(false);
			continue;
		}

		// @note: bounds is too big
		if (const auto v = boxcolliders[i]->get_bounds()[1]; v.x > 50.f || v.y > 50.f || v.z > 50.f)
			boxcolliders[i]->set_enabled(false);

		// @note: size is too big
 		if (const auto v = boxcolliders[i]->get_size(); v.x > 15.f || v.y > 15.f || v.z > 15.f)
			boxcolliders[i]->set_enabled(false);
	}
}

void helpers::assetbundle_processor::scan_capsulecolliders() const
{
	const auto capsulecolliders = assembler::il2cpp::array_to_vector<assembler::unity_engine::capsulecollider*>(assetbundle_->get_components_in_children(assembler::unity_engine::capsulecollider::get_global_type(), true));

	for (std::size_t i = 0; i < capsulecolliders.size(); i++)
	{
		const auto elem = capsulecolliders[i];

		if (i > 5)
		{
			// @note: hardlimit
			elem->set_enabled(false);
			continue;
		}

		// @note: bounds are too big
		if (const auto v = capsulecolliders[i]->get_bounds()[1]; v.x > 50.f || v.y > 50.f || v.z > 50.f)
			capsulecolliders[i]->set_enabled(false);

		// @note: properties are too big
		if (const auto direction = elem->get_direction(); direction > 100 || direction < -100 || elem->get_height() > 128.f || elem->get_radius() > 360.f)
			elem->set_enabled(false);
	}
}

void helpers::assetbundle_processor::scan_lights() const
{
	if (!lights_type_)
		lights_type_ = assembler::il2cpp::get_type(xorstr_("UnityEngine.Light, UnityEngine.CoreModule"));

	const auto lights = assembler::il2cpp::array_to_vector<assembler::unity_engine::object*>(assetbundle_->get_components_in_children(lights_type_, true));

	// @note: hardlimit
	for (std::size_t i = 24; i < lights.size(); i++)
		assembler::unity_engine::object::destroy_immediate(lights[i]);
}

void helpers::assetbundle_processor::scan_cloths() const
{
	const auto cloths = assembler::il2cpp::array_to_vector<assembler::unity_engine::cloth*>(assetbundle_->get_components_in_children(assembler::unity_engine::cloth::get_global_type(), true));

	for (std::size_t i = 0; i < cloths.size(); i++)
	{
		if (i > 10)
		{
			// @note: hardlimit
			cloths[i]->set_enabled(false);
			continue;
		}

		const auto meshrenderer = reinterpret_cast<assembler::unity_engine::meshrenderer*>(cloths[i]->get_game_object()->get_component(xorstr_("MeshRenderer")));
		const auto meshfilter = reinterpret_cast<assembler::unity_engine::meshfilter*>(meshrenderer->get_game_object()->get_component(xorstr_("MeshFilter")));

		if (!meshrenderer || !meshfilter)
		{
			// @note: no mesh, don't render
			cloths[i]->set_enabled(false);
			continue;
		}

		SEH_START
			const auto shared_mesh = meshfilter->get_sharedmesh();

			if (!shared_mesh)
			{
				// @note: no mesh, don't render
				cloths[i]->set_enabled(false);
				meshrenderer->set_enabled(false);
				continue;
			}

			assembler::il2cpp::il2cpp_array_wrapper<std::int32_t>* triangles;
			try
			{
				triangles = shared_mesh->get_triangles();
			}
			catch (const std::length_error& e)
			{

				// @note: mesh is fucked
				logging::push(FOREGROUND_INTENSE_CYAN);
				logging::add_log(xorstr_("[anti-avatar crash] caught native engine error [{}]\n"), e.what());
				logging::pop();

				assembler::unity_engine::object::destroy_immediate(shared_mesh);
				assembler::unity_engine::object::destroy_immediate(meshrenderer);
				assembler::unity_engine::object::destroy_immediate(meshfilter);
				assembler::unity_engine::object::destroy_immediate(cloths[i]);
				continue;
			}

			if (!triangles)
				continue;

			if (!triangles->max_length || triangles->max_length / 3 > 2000)
			{
				// @note: too many polys
				cloths[i]->set_enabled(false);
				meshrenderer->set_enabled(false);

				continue;
			}
		SEH_END

		const auto spheres = assembler::il2cpp::array_to_vector<assembler::unity_engine::cloth_sphere_collider_pair*>(cloths[i]->get_sphere_colliders());

		if (spheres.size() > 64)
		{
			// @note: sphere is too big
			cloths[i]->set_enabled(false);
			meshrenderer->set_enabled(false);
			continue;
		}

		for (const auto sphere : spheres)
		{
			if (!sphere->get_first() || !sphere->get_second())
			{
				// @note: missing twin in pair
				cloths[i]->set_enabled(false);
				meshrenderer->set_enabled(false);
			}
		}
	}
}

void helpers::assetbundle_processor::scan_trailrenderers()
{
	if (!trailrenderer_type_)
		trailrenderer_type_ = assembler::il2cpp::get_type(xorstr_("UnityEngine.TrailRenderer, UnityEngine.CoreModule"));

	const auto trailrenderers = assembler::il2cpp::array_to_vector<assembler::unity_engine::trailrenderer*>(assetbundle_->get_components_in_children(trailrenderer_type_, true));

	for (std::size_t i = 0; i < trailrenderers.size(); i++)
	{
		if (i > 36)
		{
			// @note: hardlimit
			trailrenderers[i]->set_enabled(false);
			continue;
		}

		const auto material = trailrenderers[i]->get_material();
		if (!material || trailrenderers[i]->get_materials()->max_length > 6)
		{
			// @note: too many materials or no materials at all
			trailrenderers[i]->set_enabled(false);
			continue;
		}

		materials_.push_back(material);
	}
}

void helpers::assetbundle_processor::scan_linerenderers()
{
	const auto linerenderers = assembler::il2cpp::array_to_vector<assembler::unity_engine::linerenderer*>(assetbundle_->get_components_in_children(assembler::unity_engine::linerenderer::get_global_type(), true));

	for (std::size_t i = 0; i < linerenderers.size(); i++)
	{
		if (i > 24)
		{
			// @note: hardlimit
			linerenderers[i]->set_enabled(false);
			continue;
		}

		const auto material = linerenderers[i]->get_material();
		if (!material || linerenderers[i]->get_materials()->max_length > 6)
		{
			// @note: too many materials or no materials at all
			linerenderers[i]->set_enabled(false);
			continue;
		}

		materials_.push_back(material);
	}
}

void helpers::assetbundle_processor::scan_particlesystems()
{
	const auto particlesystems = assembler::il2cpp::array_to_vector<assembler::unity_engine::particle_system*>(assetbundle_->get_components_in_children(assembler::unity_engine::particle_system::get_global_type(), true));

	for (const auto particlesystem : particlesystems)
	{
		const auto particle_sys_renderer = static_cast<assembler::unity_engine::particlesystemrenderer*>(particlesystem->get_component(assembler::unity_engine::particlesystemrenderer::get_global_type()));

		if (!particle_sys_renderer)
		{
			// @note: no renderer to render particlesystem
			assembler::unity_engine::object::destroy_immediate(particlesystem);
			continue;
		}

		const auto particles = particlesystem->get_max_particles();

		if (particles > 2000 || particles == 0)
		{
			// @note: too many particles or none at all
			assembler::unity_engine::object::destroy_immediate(particle_sys_renderer);
			assembler::unity_engine::object::destroy_immediate(particlesystem);
			continue;
		}

		particle_count_ += particles;
		if (particles > particle_count_ || particlesystem->get_emission_rate() >= 6.f)
		{
			// @note: check for overflow
			assembler::unity_engine::object::destroy_immediate(particle_sys_renderer);
			assembler::unity_engine::object::destroy_immediate(particlesystem);
			continue;
		}

		// @note: too big
		if (particlesystem->get_start_size() > 20.f)
			particlesystem->set_start_size(0.5f);

		const auto material = particle_sys_renderer->get_material();
		const auto mesh = particle_sys_renderer->get_mesh();

		if (!mesh || !material || particle_sys_renderer->get_materials()->max_length > 6)
		{
			// @note: too many materials or no materials at all or no mesh
			assembler::unity_engine::object::destroy_immediate(particle_sys_renderer);
			assembler::unity_engine::object::destroy_immediate(particlesystem);

			continue;
		}

		assembler::il2cpp::il2cpp_array_wrapper<std::int32_t>* triangles;
		try
		{
			triangles = mesh->get_triangles();
		}
		catch (const std::length_error& e)
		{
			// @note: mesh is fucked
			logging::push(FOREGROUND_INTENSE_CYAN);
			logging::add_log(xorstr_("[anti-avatar crash] caught native engine error [{}]\n"), e.what());
			logging::pop();

			assembler::unity_engine::object::destroy_immediate(mesh);
			assembler::unity_engine::object::destroy_immediate(particle_sys_renderer);
			assembler::unity_engine::object::destroy_immediate(particlesystem);
			continue;
		}

		if (!triangles)
		{
			materials_.push_back(material);
			continue;
		}

		if (!triangles->max_length || triangles->max_length / 3 > 12000)
		{
			// @note: too many polys
			assembler::unity_engine::object::destroy_immediate(particle_sys_renderer);
			assembler::unity_engine::object::destroy_immediate(particlesystem);

			continue;
		}

		materials_.push_back(material);
	}
}

void helpers::assetbundle_processor::scan_animations() const
{
	const auto animations = assembler::il2cpp::array_to_vector<assembler::unity_engine::animation*>(assetbundle_->get_components_in_children(assembler::unity_engine::animation::get_global_type(), true));

	// @note: stop all animations
	for (const auto animation : animations)
		animation->stop();
}

void helpers::assetbundle_processor::scan_springjoints() const
{
	const auto springjoints = assembler::il2cpp::array_to_vector<assembler::unity_engine::springjoint*>(assetbundle_->get_components_in_children(assembler::unity_engine::springjoint::get_global_type(), true));

	for (const auto springjoint : springjoints)
	{
		// @note: fix springjoint properties
		if (springjoint->get_damper() > 5.f)
			springjoint->set_damper(5.f);
		if (springjoint->get_max_distance() > 5.f)
			springjoint->set_max_distance(0.f);
		if (springjoint->get_min_distance() > 5.f)
			springjoint->set_min_distance(0.f);
		if (springjoint->get_spring() > 200.f)
			springjoint->set_spring(200.f);
		if (springjoint->get_tolerance() > 1.f)
			springjoint->set_spring(1.f);
	}
}

void helpers::assetbundle_processor::scan_aimiks() const
{
	if (!aimiks_type_)
		aimiks_type_ = assembler::il2cpp::get_type(xorstr_("RootMotion.FinalIK.AimIK, Assembly-CSharp-firstpass"));

	const auto aimiks = assembler::il2cpp::array_to_vector<assembler::unity_engine::object*>(assetbundle_->get_components_in_children(aimiks_type_, true));

	// @note: there are bad
	for (const auto aimik : aimiks)
		assembler::unity_engine::object::destroy_immediate(aimik);
}

void helpers::assetbundle_processor::scan_skinnedmeshrenderers()
{
	const auto skinnedmeshrenderers = assembler::il2cpp::array_to_vector<assembler::unity_engine::skinnedmeshrenderer*>(assetbundle_->get_components_in_children(assembler::unity_engine::skinnedmeshrenderer::get_global_type(), true));

	for (std::size_t i = 0; i < skinnedmeshrenderers.size(); i++)
	{
		if (i > 84)
		{
			// @note: hardlimit
			skinnedmeshrenderers[i]->set_enabled(false);
			continue;
		}

		const auto skinnedmeshrenderer = skinnedmeshrenderers[i];
		const auto material = skinnedmeshrenderer->get_material();

		std::uint64_t poly_count = 0;

		SEH_START
			const auto shared_mesh = skinnedmeshrenderer->get_sharedmesh();

			if (!shared_mesh || !material)
			{
				// @note: no mesh or no material
				assembler::unity_engine::object::destroy_immediate(skinnedmeshrenderer);
				continue;
			}

			if (const auto materials_size = skinnedmeshrenderer->get_materials()->max_length; materials_size != static_cast<std::uint32_t>(shared_mesh->get_submesh_count()) || materials_size > 32ul)
			{
				// @note: too many materials
				assembler::unity_engine::object::destroy_immediate(skinnedmeshrenderer);
				continue;
			}

			assembler::il2cpp::il2cpp_array_wrapper<std::int32_t>* triangles;
			try
			{
				triangles = shared_mesh->get_triangles();
			}
			catch (const std::length_error& e)
			{
				// @note: mesh is fucked
				logging::push(FOREGROUND_INTENSE_CYAN);
				logging::add_log(xorstr_("[anti-avatar crash] caught native engine error [{}]\n"), e.what());
				logging::pop();

				assembler::unity_engine::object::destroy_immediate(shared_mesh);
				assembler::unity_engine::object::destroy_immediate(skinnedmeshrenderer);
				continue;
			}

			if (!triangles)
			{
				materials_.push_back(material);
				continue;
			}

			poly_count = triangles->max_length;
			if (!poly_count || poly_count / 3 > 350000)
			{
				// @note: too many polys
				assembler::unity_engine::object::destroy_immediate(skinnedmeshrenderer);
				continue;
			}
		SEH_END


		if (!confirm_material(material, poly_count))
		{
			assembler::unity_engine::object::destroy_immediate(skinnedmeshrenderer);
			continue;
		}

		materials_.push_back(material);
	}
}

void helpers::assetbundle_processor::scan_meshrenderers()
{
	const auto meshrenderers = assembler::il2cpp::array_to_vector<assembler::unity_engine::meshrenderer*>(assetbundle_->get_components_in_children(assembler::unity_engine::meshrenderer::get_global_type(), true));

	for (std::size_t i = 0; i < meshrenderers.size(); i++)
	{
		const auto meshrenderer = meshrenderers[i];
		const auto meshfilter = static_cast<assembler::unity_engine::meshfilter*>(meshrenderer->get_game_object()->get_component(xorstr_("MeshFilter")));

		if (!meshfilter)
		{
			// @note: no meshfilter for meshrenderer
			assembler::unity_engine::object::destroy_immediate(meshrenderer);
			continue;
		}

		if (i > 56)
		{
			// @note: hardlimit
			assembler::unity_engine::object::destroy_immediate(meshrenderer);
			assembler::unity_engine::object::destroy_immediate(meshfilter);
			continue;
		}

		SEH_START
			if (const auto& v = meshrenderer->get_transform()->get_local_scale(); v.x > 5.f || v.y > 5.f || v.z > 5.f)
			{
				// @note: scaled too high
				assembler::unity_engine::object::destroy_immediate(meshrenderer);
				assembler::unity_engine::object::destroy_immediate(meshfilter);

				continue;
			}

			if (meshrenderer->get_materials()->max_length > 6ul)
			{
				// @note: too many materials
				assembler::unity_engine::object::destroy_immediate(meshrenderer);
				assembler::unity_engine::object::destroy_immediate(meshfilter);

				continue;
			}
		SEH_END

		const auto material = meshrenderer->get_material();
		std::uint64_t poly_count = 0;

		SEH_START
			const auto shared_mesh = meshfilter->get_sharedmesh();

			if (!shared_mesh || !material)
			{
				// @note: no mesh or no material
				assembler::unity_engine::object::destroy_immediate(meshrenderer);
				assembler::unity_engine::object::destroy_immediate(meshfilter);

				continue;
			}

			if (shared_mesh->get_vertex_count() > 15000)
			{
				// @note: too many vertices, laggy
				assembler::unity_engine::object::destroy_immediate(meshrenderer);
				assembler::unity_engine::object::destroy_immediate(meshfilter);
				continue;
			}

			assembler::il2cpp::il2cpp_array_wrapper<std::int32_t>* triangles;
			try
			{
				triangles = shared_mesh->get_triangles();
			}
			catch (const std::length_error& e)
			{
				// @note: mesh is fucked
				logging::push(FOREGROUND_INTENSE_CYAN);
				logging::add_log(xorstr_("[anti-avatar crash] caught native engine error [{}]\n"), e.what());
				logging::pop();

				assembler::unity_engine::object::destroy_immediate(shared_mesh);
				assembler::unity_engine::object::destroy_immediate(meshrenderer);
				assembler::unity_engine::object::destroy_immediate(meshfilter);
				continue;
			}

			if (!triangles)
			{
				materials_.push_back(material);
				continue;
			}

			poly_count = triangles->max_length;
			if (!poly_count || poly_count / 3 > 40000)
			{
				// @note: too many polys
				assembler::unity_engine::object::destroy_immediate(meshrenderer);
				assembler::unity_engine::object::destroy_immediate(meshfilter);

				continue;
			}
		SEH_END

		if (!confirm_material(material, poly_count))
		{
			assembler::unity_engine::object::destroy_immediate(meshrenderer);
			assembler::unity_engine::object::destroy_immediate(meshfilter);

			continue;
		}

		materials_.push_back(material);
	}
}

void helpers::assetbundle_processor::scan_audiosources()
{
	if (!has_constructed_audiosources_)
	{
		has_constructed_audiosources_ = true;

		if (!audiosources_type_)
			audiosources_type_ = assembler::il2cpp::get_type(xorstr_("UnityEngine.AudioSource, UnityEngine.AudioModule"));

		audiosources_ = assembler::il2cpp::array_to_vector<assembler::unity_engine::object*>(assetbundle_->get_components_in_children(audiosources_type_, true));
	}

	// @note: hardlimit
	for (std::size_t i = 15; i < audiosources_.size(); i++)
		assembler::unity_engine::object::destroy_immediate(audiosources_[i]);
}

void helpers::assetbundle_processor::scan_shaders()
{
	for (auto it = materials_.begin(); it != materials_.end(); ++it)
	{
		const auto shader = (*it)->get_shader();
		auto shader_name = shader->get_ws_name();

		if (const auto s = assembler::unity_engine::shader::find(shader_name); s != nullptr)
		{
			// @note: if shader is from engine, replace it with one we know is directly from the engine (no spoofing)
			(*it)->set_shader(s);
			continue;
		}

		utility::unicode_tolower(shader_name);

		// @note: is shader whitelisted
		if (!shader_whitelist.contains(shader_name))
		{
			try
			{
				// @note: is shader poiyomi
				if (std::regex_match(shader_name, poiyomi_regex))
					continue;
			}
			catch (const std::regex_error&)
			{
				// @note: exception, set to standard
				(*it)->set_shader(assembler::unity_engine::shader::find(xorstr_(L"Standard")));
				continue;
			}

			// @note: failed all checks, set to standard
			logging::add_log(xorstr_("[debug] non-whitelisted shader removed [{}]\n"), utility::unicode_ascii(shader_name));
			(*it)->set_shader(assembler::unity_engine::shader::find(xorstr_(L"Standard")));
		}
	}
}

//void helpers::assetbundle_processor::postprocess_skinnedmeshrenderers() const
//{
//	for (const auto skinnedmeshrenderer : skinnedmeshrenderers_)
//	{
//		if (!skinnedmeshrenderer)
//			continue;
//
//		assembler::unity_engine::transform* zero_scale_root = nullptr;
//		const auto bones = skinnedmeshrenderer->get_bones();
//
//		for (std::size_t i = 0; i < bones->max_length; ++i)
//		{
//			if (bones->at(i))
//				continue;
//
//			if (!zero_scale_root)
//			{
//				const auto new_go = assembler::unity_engine::game_object::cctor(xorstr_("zero-scale"));
//				zero_scale_root = new_go->get_transform();
//				zero_scale_root->set_parent(skinnedmeshrenderer->get_root_bone(), false);
//				zero_scale_root->set_local_scale(sdk::vector(0.f, 0.f, 0.f));
//			}
//
//			bones->at(i) = zero_scale_root;
//		}
//
//		if (zero_scale_root)
//			skinnedmeshrenderer->set_bones(bones);
//	}
//}

void helpers::assetbundle_processor::remove_audiosources()
{
	if (!has_constructed_audiosources_)
	{
		has_constructed_audiosources_ = true;

		if (!audiosources_type_)
			audiosources_type_ = assembler::il2cpp::get_type(xorstr_("UnityEngine.AudioSource, UnityEngine.AudioModule"));

		audiosources_ = assembler::il2cpp::array_to_vector<assembler::unity_engine::object*>(assetbundle_->get_components_in_children(audiosources_type_, true));
	}

	for (auto it = audiosources_.begin(); it != audiosources_.end(); ++it)
		assembler::unity_engine::object::destroy_immediate(*it);
}
