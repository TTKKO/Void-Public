#include "nameplates.hpp"
#include "../../assembler/assembly-csharp/highlightsfx.hpp"
#include "../../assembler/unityengine/material.hpp"

nameplate_manager::nameplate_manager(assembler::vrc_player* player) : player_(player), apiuser_(player->get_player()->get_api_user()), nameplate_(player->get_name_plate())
{
	if (!nameplate_)
		return;

	nameplate_transform_ = nameplate_->get_transform();
}

void nameplate_manager::render_chams(const bool is_local) const
{
	const auto body = player_->get_transform()->find(xorstr_("ForwardDirection/Avatar"));

	if (!body)
		return;

	if (body->child_count() <= 0)
		return;

	if (const std::int32_t layer = config::get<bool>(g_context.chams) ? 19 : is_local ? 10 : 9; body->get_child(0)->get_game_object()->get_layer() != layer)
	{
		const auto v = assembler::il2cpp::array_to_vector<assembler::unity_engine::transform*>(body->get_game_object()->get_components_in_children(assembler::unity_engine::transform::get_global_type(), true));
		for (std::size_t i = 0; i < v.size(); ++i)
			v[i]->get_game_object()->set_layer(layer);
	}
}

void nameplate_manager::render_outline(const bool value) const
{
	const auto body = player_->get_transform()->find(xorstr_("ForwardDirection/Avatar"));

	if (!body)
		return;

	const auto smr_v = assembler::il2cpp::array_to_vector<assembler::unity_engine::skinnedmeshrenderer*>(body->get_game_object()->get_components_in_children(assembler::unity_engine::skinnedmeshrenderer::get_global_type(), false));

	for (const auto renderer : smr_v)
	{
		const auto p_materials = renderer->get_materials();

		for (std::size_t i = 0; i < p_materials->max_length; ++i)
			p_materials->at(i)->set_color(xorstr_("_HighlightColor"), sdk::color(0.701f, 0.258f, 0.96f, 1.f));
		
		assembler::highlights_fx::instance()->enable_outline(renderer, value);
	}
}

void nameplate_manager::render_colors() const
{
	sdk::color c;

	if (const auto user_id = apiuser_->get_id(); is_client_user(user_id))
		c = misc::get_rainbow();

	else if (assembler::vrc::core::api_user::is_friends_with(user_id))
		c = config::get<sdk::color>(g_context.c_friend);

	else
	{
		apiuser_->has_tag(xorstr_("admin_scripting_access")) || apiuser_->has_tag(xorstr_("admin_moderator")) || apiuser_->has_tag(xorstr_("admin"))
			? c = {239, 16, 98}
			: apiuser_->has_tag(xorstr_("system_trust_veteran"))
			? c = config::get<sdk::color>(g_context.c_trusted)
			: apiuser_->has_tag(xorstr_("system_trust_trusted"))
			? c = config::get<sdk::color>(g_context.c_known)
			: apiuser_->has_tag(xorstr_("system_trust_known"))
			? c = config::get<sdk::color>(g_context.c_user)
			: apiuser_->has_tag(xorstr_("system_trust_basic"))
			? c = config::get<sdk::color>(g_context.c_newuser)
			: c = config::get<sdk::color>(g_context.c_visitor);
	}

	nameplate_->get_name_text()->set_color(c);
}

bool nameplate_manager::render_tags() const
{
	std::lock_guard lock_guard(shared_mutexes_[1]);
	if (userplates_.contains(apiuser_->get_id()) && !nameplate_->get_transform()->find(xorstr_("Contents/VOIDSTATS")))
	{
		const auto pos = nameplate_transform_->find(xorstr_("Contents"));

		if (!pos)
			return false;

		const auto instatiation = pos->find(xorstr_("Quick Stats"))->get_game_object();

		if (!instatiation)
			return false;

		const auto obj = reinterpret_cast<assembler::unity_engine::game_object*>(assembler::unity_engine::object::instantiate(instatiation, pos, true));

		if (!obj)
			return false;

		const auto obj_transform = obj->get_transform();

		for (std::size_t i = 0; i < obj_transform->child_count(); i++)
		{
			if (obj_transform->get_child(static_cast<std::int32_t>(i))->get_name() == xorstr_("Trust Text"))
				continue;

			assembler::unity_engine::object::destroy(obj_transform->get_child(static_cast<std::int32_t>(i))->get_game_object());
		}

		obj_transform->set_local_position(sdk::vector(0.f, 60.f, 0.f));
		obj->set_name(xorstr_("VOIDSTATS"));

		const auto text = obj_transform->find(xorstr_("Trust Text"));

		if (!text)
			return false;

		const auto text_component = reinterpret_cast<assembler::tmpro::tmp_text*>(text->get_component(xorstr_("TMPro.TextMeshProUGUI")));

		if (!text_component)
			return false;

		text_component->set_text(xorstr_("<b>") + userplates_[apiuser_->get_id()] + xorstr_("</b>"));

		text->set_name(xorstr_("VOIDTEXT"));
		text->get_game_object()->set_active(true);

		if (!obj->get_active_self())
			obj->set_active(true);

		return true;
	}
	return true;
}

bool nameplate_manager::render_info() const
{
	assembler::unity_engine::transform* info = nameplate_transform_->find(xorstr_("Contents/VOIDINFO"));
	if (!info)
	{
		const auto pos = nameplate_transform_->find(xorstr_("Contents"));

		if (!pos)
			return false;

		const auto obj = reinterpret_cast<assembler::unity_engine::game_object*>(assembler::unity_engine::object::instantiate(pos->find(xorstr_("Quick Stats"))->get_game_object(), pos, true));

		if (!obj)
			return false;

		const auto obj_transform = obj->get_transform();

		for (std::size_t i = 0; i < obj_transform->child_count(); i++)
		{
			if (obj_transform->get_child(static_cast<std::int32_t>(i))->get_name() == xorstr_("Trust Text"))
				continue;

			assembler::unity_engine::object::destroy(obj_transform->get_child(static_cast<std::int32_t>(i))->get_game_object());
		}

		info = obj_transform;
		info->set_local_position(sdk::vector(0.f, -60.f, 0.f));
		obj->set_name(xorstr_("VOIDINFO"));

		const auto text = info->find(xorstr_("Trust Text"));

		if (!text)
			return false;

		text->set_name(xorstr_("VOIDTEXT"));
		text->get_game_object()->set_active(true);

		if (!obj->get_active_self())
			obj->set_active(true);
	}

	bool flag = false;
	const auto status_line = nameplate_transform_->find(xorstr_("Contents/Status Line"));

	if (!status_line)
		return false;

	for (std::int32_t i = 0; i < status_line->child_count(); ++i)
	{
		if (status_line->get_child(i)->get_game_object()->get_active_self())
		{
			if (const auto location = info->get_local_position().y; location != -86.f)
				info->set_local_position(sdk::vector(0.f, -86.f, 0.f));

			flag = false;
			break;
		}
		flag = true;
	}
	if (flag && info->get_local_position().y != -60.f)
		info->set_local_position(sdk::vector(0.f, -60.f, 0.f));

	const auto photonplayer = player_->get_player();
	const auto player_api = photonplayer->get_vrc_player_api();
	const auto text = reinterpret_cast<assembler::tmpro::tmp_text*>(info->find(xorstr_("VOIDTEXT"))->get_component(xorstr_("TMPro.TextMeshProUGUI")));

	if (!text || !photonplayer || !player_api)
		return false;

	auto color = sdk::color(177, 123, 211);
	const auto user_id = apiuser_->get_id();

	if (is_client_user(user_id))
		color = misc::get_rainbow();

	std::string_view stability = xorstr_("<color=#ffffff>[</color><color=#2ee876>Stable</color><color=#ffffff>]</color> ");

	if (events_map_.contains(photonplayer->get_photon_id()))
		if (duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - events_map_.at(photonplayer->get_photon_id()) > 5000)
			stability = xorstr_("<color=#ffffff>[</color><color=#eb345e>Lagging</color><color=#ffffff>]</color> ");

	const auto output = utility::format(
		xorstr_("<color=#{}><color=#ffffff>[</color>{:d}<color=#ffffff>]</color> {}{}{}{}{}<color=#ffffff>PNG:</color> {:d} <color=#ffffff>|</color> <color=#ffffff>FPS:</color> {:d}</color>"),

		color.get_hex(),
		photonplayer->get_photon_id(),
		player_api->get_is_master() ? xorstr_("<color=#ffffff>[</color>M<color=#ffffff>]</color> ") : xorstr_(""),
		player_api->is_vr() ? apiuser_->get_is_on_mobile() ? xorstr_("<color=#ffffff>[</color>QST<color=#ffffff>]</color> ") : xorstr_("<color=#ffffff>[</color>PCVR<color=#ffffff>]</color> ") : xorstr_("<color=#ffffff>[</color>PC<color=#ffffff>]</color> "),
		stability,
		player_->get_api_avatar()->get_release_status() == xorstr_("private") ? xorstr_("<color=#ffffff>[</color>PR<color=#ffffff>]</color> ") : xorstr_("<color=#ffffff>[</color>PU<color=#ffffff>]</color> "),
		assembler::moderation_manager::instance()->check_moderation(user_id, assembler::moderation_manager::moderation_type::block) ? xorstr_("<color=#ffffff>[</color>B<color=#ffffff>]</color> ") : xorstr_(""),
		player_->get_ping(),
		player_->get_fps()
	);

	text->set_text(output);

	return true;
}

void nameplate_manager::render_blocked(const bool is_blocked) const
{
	const auto void_plate = nameplate_transform_->get_parent()->find(xorstr_("VOID_BLOCKED_PLATE"));

	if (!is_blocked && !assembler::moderation_manager::instance()->check_moderation(apiuser_->fields.id, assembler::moderation_manager::moderation_type::block))
	{
		if (void_plate)
			assembler::unity_engine::object::destroy_immediate(void_plate->get_game_object());

		return;
	}

	if (void_plate)
	{
		if (const auto plate_object = void_plate->get_game_object(); !plate_object->get_active_self())
			plate_object->set_active(true);

		if (const auto child = void_plate->get_child(0)->get_game_object(); !child->get_active_self())
			child->set_active(true);

		return;
	}

	const auto local = assembler::vrc_player::get_current()->get_name_plate();

	if (!local || nameplate_transform_->get_game_object()->get_active_self())
		return;

	const auto void_plate_t = reinterpret_cast<assembler::unity_engine::game_object*>(assembler::unity_engine::object::instantiate(local->get_game_object(), nameplate_transform_->get_parent(), true));

	if (!void_plate_t)
		return;

	void_plate_t->set_name(xorstr_("VOID_BLOCKED_PLATE"));

	if (const auto np_c = void_plate_t->get_component(reinterpret_cast<assembler::il2cpp::il2cpp_type*>(type_get_object(class_get_type(reinterpret_cast<assembler::il2cpp::il2cpp_object*>(nameplate_)->klass)))))
		assembler::unity_engine::object::destroy_immediate(np_c);

	void_plate_t->set_active(true);
	const auto plate_transform = void_plate_t->get_transform();

	plate_transform->set_local_rotation({0.f, 0.f, 0.f, 1.f});
	plate_transform->set_local_position(sdk::vector(0.f, 0.f, 0.f));
	plate_transform->set_local_scale(sdk::vector(1.f, 1.f, 1.f));

	const auto np_content = plate_transform->find(xorstr_("Contents"));

	if (!np_content)
		return;

	np_content->get_game_object()->set_active(true);

	for (int i = 0; i < np_content->child_count(); ++i)
	{
		if (const auto go = np_content->get_child(i)->get_game_object(); go->get_ws_name() != xorstr_(L"Main"))
			go->set_active(false);
		else
			go->set_active(true);
	}

	const auto text = reinterpret_cast<assembler::tmpro::tmp_text*>(np_content->find(xorstr_("Main/Text Container/Name"))->get_component(xorstr_("TMPro.TextMeshProUGUI")));

	if (!text)
		return;

	text->set_color({0, 0, 0, 255});
	text->set_text(apiuser_->display_name());

	if (!text)
		return;

	const auto rt = reinterpret_cast<assembler::unity_engine::rect_transform*>(np_content->get_component(xorstr_("RectTransform")));

	if (!rt)
		return;

	rt->set_size_delta(sdk::vector_2d(300.f, 0.f));

	np_content->find(xorstr_("Main/Text Container/Sub Text"))->get_game_object()->set_active(false);
}

void nameplate_manager::overrender() const
{
	const auto go = nameplate_transform_->get_parent()->get_game_object();

	if (!go)
		return;

	const auto is_local = wsv_chars(apiuser_->fields.id) == wsv_chars(assembler::vrc::core::api_user::get_current()->fields.id);

	if (config::get<bool>(g_context.nametags) && !is_local)
	{
		if (go->get_layer() != 19)
			go->set_layer(19);
	}
	else
	{
		if (go->get_layer() != 12)
			go->set_layer(12);
	}


	render_chams(is_local);
	//render_outline(true);
}

bool nameplate_manager::is_client_user(const std::string& id)
{
	std::lock_guard lock_guard(shared_mutexes_[0]);
	return userlist_.contains(id);
}

bool nameplate_manager::is_ready() const
{
	return nameplate_transform_ && apiuser_;
}

void nameplate_manager::update_user(const std::int32_t player)
{
	std::lock_guard guard(nm_mutex_);
	events_map_[player] = duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

std::unordered_set<std::string>& nameplate_manager::get_userlist()
{
	return userlist_;
}

std::unordered_map<std::string, std::string>& nameplate_manager::get_userplates()
{
	return userplates_;
}

std::array<std::shared_mutex, 2ull>& nameplate_manager::get_mutexes()
{
	return shared_mutexes_;
}

void nameplate_manager::set_tags(const nlohmann::json& ref)
{
	userplates_ = ref;
}

void nameplate_manager::cleanup_user(const std::int32_t player)
{
	if (events_map_.contains(player))
	{
		std::lock_guard guard(nm_mutex_);
		events_map_.erase(player);
	}
}

void nameplate_manager::cleanup(const bool full_clean)
{
	mirror_map_.clear();
	std::lock_guard guard(nm_mutex_);
	events_map_.clear();
}

void nameplate_manager::fix_mirrormasks(const bool no_restore)
{
	const auto v = array_to_vector<assembler::vrc::sdk_base::vrc_mirror_reflection*>(assembler::unity_engine::game_object::find_objects_of_type_all(assembler::vrc::sdk_base::vrc_mirror_reflection::get_global_type()));

	if (no_restore)
	{
		mirror_map_.clear();
		mirror_map_.reserve(v.size());

		for (std::size_t i = 0; i < v.size(); ++i)
		{
			mirror_map_[v[i]->get_hash_code()] = v[i]->get_reflection_layers();
			v[i]->set_reflection_layers(-1025);
		}
	}
	else
	{
		if (mirror_map_.size() == 0)
			return;

		for (std::size_t i = 0; i < v.size(); ++i)
			if (const auto hashcode = v[i]->get_hash_code(); mirror_map_.contains(hashcode))
				v[i]->set_reflection_layers(mirror_map_.at(hashcode));

		mirror_map_.clear();
	}
}
