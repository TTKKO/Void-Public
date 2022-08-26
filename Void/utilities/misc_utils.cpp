#include "misc_utils.hpp"
#include "../core/assembler/unityengine/scene.hpp"

bool misc::curl_downloadfile(const char* url, const std::string_view avtr)
{
	// VMProtectBeginUltra("Curl DL");

	const std::filesystem::path directory = config::get_working_path() / xorstr_("vrca_downloads");

	if (!is_directory(directory))
	{
		std::filesystem::remove(directory);
		if (!create_directories(directory))
			return false;
	}

	const std::filesystem::path saving = directory / avtr;

	if (CURL* curl = curl_easy_init())
	{
		FILE* fp = nullptr;
		if (const errno_t fopenret = fopen_s(&fp, saving.string().c_str(), xorstr_("wb")); fopenret != 0) return false;
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

		// @note: useragent from firefox cus vrchat doesn't like curl i guess
		curl_easy_setopt(curl, CURLOPT_USERAGENT, xorstr_("Mozilla / 5.0 (Windows NT 10.0; Win64; x64; rv:93.0) Gecko / 20100101 Firefox / 93.0"));
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, utility::write_data_callback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		const CURLcode res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		fclose(fp);
		if (res == CURLE_OK) return true;
		return false;
	}

	// VMProtectEnd();
	return false;
}

void misc::load_config()
{
	g_context.player_attach_id = 0;
	g_context.player_attach = false;
	g_context.block_downloads = false;

	config::get<bool>(g_context.invisible_join) = false;
	config::get<bool>(g_context.exploit_event_1) = false;
	config::get<int>(g_context.copy_event1) = 0;
	config::get<bool>(g_context.collision_crash) = false;
	config::get<bool>(g_context.corrupt_asset_crash) = false;
	config::get<bool>(g_context.audio_crash) = false;
	config::get<bool>(g_context.quest_crash) = false;

	if (config::get<bool>(g_context.discord_rpc_toggle))
		g_context.g_discord = std::make_unique<discord_sdk>();

	if (config::get<bool>(g_context.fps_target))
		assembler::unity_engine::application::set_target_frame_rate(config::get<int>(g_context.fps_target_i));

	try
	{
		if (!config::get<bool>(g_context.xs_overlay_toggle) && xs_overlay::get().is_connected())
		{
			if (xs_overlay::get().shutdown())
			{
				logging::push(FOREGROUND_YELLOW);
				logging::print(xorstr_("[xs-overlay] successfully disconnected from api\n"));
				logging::pop();
			}
		}
		else if (config::get<bool>(g_context.xs_overlay_toggle) && !xs_overlay::get().is_connected())
		{
			if (!xs_overlay::get().initialize())
				throw std::runtime_error(utility::format(xorstr_("failed to initialize xs-overlay api [{}]"), xs_overlay::get().fetch_last_error()));

			logging::push(FOREGROUND_INTENSE_GREEN);
			logging::print(xorstr_("[xs-overlay] successfully connected to api\n"));
			logging::pop();
		}
	}
	catch (const std::exception& e)
	{
		logging::push(FOREGROUND_INTENSE_RED);
		logging::print(xorstr_("[critical] {}\n"), e.what());
		logging::pop();

		xs_overlay::get().shutdown();
		config::get<bool>(g_context.xs_overlay_toggle) = false;
	}
}

#pragma region utility
void misc::handle_avatar_clone(const bool value)
{
	if (value)
	{
		const auto player = assembler::vrc_player::get_current();
		const auto player_transform = player->get_transform();

		if (const auto avi = player_transform->find(xorstr_("ForwardDirection/Avatar")))
		{
			const auto clone = static_cast<assembler::unity_engine::game_object*>(assembler::unity_engine::object::instantiate(avi->get_game_object(), player_transform->get_parent(), true));
			clone->set_name(xorstr_("VOID_DESERIALIZED"));
			assembler::unity_engine::object::destroy(clone->get_component(xorstr_("VRIK")));
			assembler::unity_engine::object::destroy(clone->get_component(xorstr_("FullBodyBipedIK")));
			clone->get_transform()->set_local_position(player_transform->get_local_position());
			clone->get_transform()->set_rotation(player_transform->get_rotation());
			const auto animator = static_cast<assembler::unity_engine::animator*>(clone->get_component(xorstr_("Animator")));

			if (!animator)
				return;

			if (const auto avi_head = animator->get_bone_transform(static_cast<std::int32_t>(assembler::unity_engine::human_body_bones::head)))
				avi_head->set_local_scale(sdk::vector(1.f, 1.f, 1.f));

			if (config::get<bool>(g_context.chams))
				return;

			const auto v = assembler::il2cpp::array_to_vector<assembler::unity_engine::transform*>(clone->get_components_in_children(assembler::unity_engine::transform::get_global_type(), true));
			for (std::size_t i = 0; i < v.size(); ++i)
				v[i]->get_game_object()->set_layer(9);
		}
	}
	else
	{
		if (const auto avi = assembler::unity_engine::game_object::find(xorstr_("VOID_DESERIALIZED")))
			assembler::unity_engine::object::destroy(avi);
	}
}

void misc::toggle_flight(const bool value)
{
	const auto collider = reinterpret_cast<assembler::unity_engine::character_controller*>(assembler::vrc_player::get_current()->get_game_object()->get_component(assembler::unity_engine::character_controller::get_global_type()));
	collider->set_enabled(!value);
}

void misc::change_avatar(const std::string_view avatar_id)
{
	const auto apiavatar = assembler::vrc::core::api_avatar::ctor();
	apiavatar->set_id(avatar_id);
	assembler::vrc::ui::page_avatar::force_change(apiavatar, xorstr_("AvatarMenu"), nullptr);
}
#pragma endregion

#pragma region assetbundle_manager
void misc::toggle_download_manager(const bool state)
{
	const auto abdm = assembler::assetbundle_download_manager::instance();

	if (!abdm)
		return;

	reinterpret_cast<assembler::unity_engine::behaviour*>(abdm)->set_enabled(state);

	if (state)
	{
		const auto [fst, scnd] = abdm->get_queues();
		fst->clear();
		scnd->clear();

		assembler::unity_engine::object::unload_unused_assets();
	}
}

void misc::remove_avatar_from_cache(const std::string_view avatar_id)
{
	const auto abdm = assembler::assetbundle_download_manager::instance();

	if (!abdm)
		return;

	const auto [fst, scnd] = abdm->get_queues();

	for (std::int32_t i = 0; i < fst->get_count(); ++i)
		if (const auto obj = static_cast<assembler::assetbundle_download*>(fst->dequeue()); obj->get_id() != avatar_id)
			fst->enqueue(obj);

	const auto dictionary = abdm->fields.ptr2;

	std::vector<assembler::il2cpp::il2cpp_string*> cached_avatars;
	cached_avatars.reserve(dictionary->fields.count);

	const auto enumerator = dictionary->get_keys()->get_enumerator();

	while (enumerator->move_next()) 
		cached_avatars.push_back(static_cast<assembler::il2cpp::il2cpp_string*>(enumerator->fields.current_key));

	for (const auto bundle : cached_avatars)
	{
		const auto entry = dictionary->dictionary_get<assembler::assetbundle_download*>(bundle);
		if (!entry)
			continue;

		if (entry->get_id() == avatar_id)
		{
			try
			{
				entry->get_assetbundle()->unload(false);
				assembler::unity_engine::object::destroy_immediate(entry->get_game_object(), true);
				dictionary->remove(bundle);
			}
			catch (const Il2CppExceptionWrapper&)
			{
				dictionary->remove(bundle);
			}
		}
	}

	assembler::il2cpp::gc_collect(0);
	assembler::il2cpp::gc_collect(1);

	assembler::unity_engine::object::unload_unused_assets();
}
#pragma endregion

#pragma region object_manipulation
void misc::drop_portal(const std::string& worldid)
{
	const auto vectorstrings = utility::split(worldid, xorstr_(":"));

	auto v = assembler::vrc_player::get_current()->get_transform()->get_position();
	v += assembler::vrc_player::get_current()->get_transform()->get_forward() * 2.f;

	static constexpr sdk::quaternion rotation(0.5f, 0.5f, 0.5f, 0.5f);
	const auto game_object = assembler::vrc::sdk_base::networking::instantiate(0, xorstr_("Portals/PortalInternalDynamic"), v, rotation);

	int i_placeholder = 0;
	const auto objs = assembler::system_replication::collections::create_object_array(reinterpret_cast<assembler::unity_engine::object*>(assembler::il2cpp::string_new(vectorstrings[0])), reinterpret_cast<assembler::unity_engine::object*>(assembler::il2cpp::string_new(vectorstrings[1])), assembler::il2cpp::value_box(xorstr_("System.Int32"), &i_placeholder));
	assembler::vrc::sdk_base::networking::rpc(7, game_object, xorstr_("ConfigurePortal"), objs);
}

bool misc::teleport_pickups(const sdk::vector& position)
{
	// @note: component, vrc_pickup
	const auto objects = array_to_vector<assembler::unity_engine::component*>(assembler::unity_engine::component::find_objects_of_type_all(assembler::vrc::sdk_base::vrc_pickup::get_global_type()));

	for (auto it = objects.begin(); it != objects.end(); ++it)
	{
		const auto go = (*it)->get_game_object();
		if (!go->get_active_self())
			continue;

		if (!assembler::vrc::sdk_base::networking::is_owner(go))
			assembler::vrc::sdk_base::networking::set_owner(assembler::vrc::sdk_base::vrc_player_api::get_current(), go);

		(*it)->get_transform()->set_position(position);
	}

	return true;
}

void misc::set_pickups(const bool value)
{
	const auto objs = assembler::unity_engine::component::find_objects_of_type_all(assembler::vrc::sdk_base::vrc_pickup::get_global_type());
	const auto objects = array_to_vector<assembler::unity_engine::transform*>(objs);

	for (auto it = objects.cbegin(); it != objects.cend(); ++it)
	{
		if (*it == nullptr)
			continue;

		auto name = (*it)->get_name();
		utility::ascii_tolower(name);

		if (name.contains(xorstr_("viewfinder")))
			continue;

		if (name.contains(xorstr_("avatardebugconsole")))
			continue;

		(*it)->get_game_object()->set_active(value);
	}
}


bool misc::destroy_portals()
{
	//4193
	//private GameObject clElements; // 0x48
	//private GameObject friendsPortalElements; // 0x50
	//private GameObject invalidDestinationElements; // 0x58
	//private Renderer[] whatthefuck; // 0xE0
	//private Collider[] whatthefuck; // 0xE8
	//private ApiWorld whatthefuck; // 0x70

	//0xD0 = instance id
	//0x38 = world id

	if (!g_context.instantiated)
		return true;

	if (!portal_type_)
		portal_type_ = assembler::il2cpp::get_type(xorstr_(L"ÏÍÌÏÏÍÎÍÌÏÏÌÍÎÏÏÎÏÎÏÏÌÎ, Assembly-CSharp.dll"));

	if (!portal_type_)
		return false;

	SEH_START
		const auto objects = array_to_vector<assembler::unity_engine::transform*>(assembler::unity_engine::component::find_objects_of_type_all(portal_type_));

		for (auto it = objects.cbegin(); it != objects.cend(); ++it)
		{
			const auto instance_id = s_chars(*reinterpret_cast<assembler::il2cpp::il2cpp_string**>(reinterpret_cast<std::uint8_t*>((*it)->get_component(portal_type_)) + 0xD0));
			if (instance_id == xorstr_("www.invalid.gg")) continue;

			assembler::unity_engine::object::destroy((*it)->get_parent()->get_game_object());
		}
	SEH_END

	return true;
}
#pragma endregion

#pragma region udon
void misc::udon_killall(std::int32_t* ref)
{
	*ref = 0;

	const auto objs = assembler::system_replication::collections::create_object_array(reinterpret_cast<assembler::unity_engine::object*>(assembler::il2cpp::string_new(xorstr_("SyncKill"))));

	const auto arr = assembler::unity_engine::object::find_objects_of_type_all(assembler::udon_sync::get_type());
	const auto v = assembler::il2cpp::array_to_vector<assembler::udon_sync*>(arr);

	for (auto it = v.begin(); it != v.end(); ++it)
	{
		if ((*it)->get_game_object()->get_ws_name().contains(xorstr_(L"Player Node")))
		{
			++* ref;
			assembler::vrc::sdk_base::networking::rpc(0, (*it)->get_game_object(), xorstr_("UdonSyncRunProgramAsRPC"), objs);
		}
	}
}

void misc::murder_teleportsingle(const std::wstring_view item)
{
	const auto arr = assembler::unity_engine::object::find_objects_of_type_all(assembler::vrc::sdk_base::vrc_pickup::get_global_type());
	const auto v = assembler::il2cpp::array_to_vector<assembler::vrc::sdk_base::vrc_pickup*>(arr);

	for (auto it = v.begin(); it != v.end(); ++it)
	{
		auto object_name = (*it)->get_game_object()->get_ws_name();
		utility::unicode_tolower(object_name);

		if (object_name.contains(item))
		{
			assembler::vrc::sdk_base::networking::set_owner(assembler::vrc::sdk_base::vrc_player_api::get_current(), (*it)->get_game_object());
			(*it)->get_transform()->set_position(assembler::vrc_player::get_current()->get_transform()->get_position() + sdk::vector::up());
			(*it)->set_pickupable(true);
			(*it)->set_disallowtheft(false);
		}
	}
}

void misc::murder_teleportall()
{
	const auto arr = assembler::unity_engine::object::find_objects_of_type_all(assembler::vrc::sdk_base::vrc_pickup::get_global_type());
	const auto v = assembler::il2cpp::array_to_vector<assembler::vrc::sdk_base::vrc_pickup*>(arr);

	for (auto it = v.begin(); it != v.end(); ++it)
	{
		auto object_name = (*it)->get_game_object()->get_ws_name();
		utility::unicode_tolower(object_name);

		if (object_name.contains(xorstr_(L"shotgun")) || object_name.contains(xorstr_(L"luger")) || object_name.contains(xorstr_(L"knife")) || object_name.contains(xorstr_(L"revolver")) || object_name.contains(xorstr_(L"frag")) || object_name.contains(xorstr_(L"bear")))
		{
			assembler::vrc::sdk_base::networking::set_owner(assembler::vrc::sdk_base::vrc_player_api::get_current(), (*it)->get_game_object());
			(*it)->get_transform()->set_position(assembler::vrc_player::get_current()->get_transform()->get_position() + sdk::vector::up());
			(*it)->set_pickupable(true);
			(*it)->set_disallowtheft(false);
		}
	}
}
#pragma endregion

#pragma region format_users
std::string misc::get_social_rank_for_player_list(assembler::vrc::player* player, assembler::vrc::core::api_user* user)
{
	const auto vrcplayer = player->get_vrc_player();

	return utility::format(

		xorstr_("<color=#dbdbdb><b>{}{}{}</b>{} [PNG: <color=#a75cf6>{:d}</color>] [FPS: <color=#a75cf6>{:d}</color>]</color>"),

		player->get_vrc_player_api()->get_is_master() ? xorstr_("[<color=#9576e8>M</color>] ") : xorstr_(""),
		player->get_vrc_player_api()->is_vr() ? xorstr_("[<color=#9576e8>VR</color>] ") : xorstr_(""),
		assembler::moderation_manager::instance()->check_moderation(user->get_id(), assembler::moderation_manager::moderation_type::block) ? xorstr_("[<color=#9576e8>B</color>] ") : xorstr_(""),
		get_user_rank(user),
		vrcplayer->get_ping(),
		vrcplayer->get_fps()

	);
}

std::string misc::get_social_rank_for_player_list_shadow(assembler::vrc::player* player, const assembler::vrc::core::api_user* user)
{
	const auto vrcplayer = player->get_vrc_player();

	return utility::format(

		xorstr_("<color=black><b>{}{}{}</b>{} [PNG: {:d}] [FPS: {:d}]</color>"),

		player->get_vrc_player_api()->get_is_master() ? xorstr_("[M] ") : xorstr_(""),
		player->get_vrc_player_api()->is_vr() ? xorstr_("[VR] ") : xorstr_(""),
		assembler::moderation_manager::instance()->check_moderation(user->get_id(), assembler::moderation_manager::moderation_type::block) ? xorstr_("[B] ") : xorstr_(""),
		user->display_name(),
		vrcplayer->get_ping(),
		vrcplayer->get_fps()

	);
}

std::string misc::get_user_rank(assembler::vrc::core::api_user* apiuser)
{
	const std::string display_name = apiuser->display_name();

	std::string rank = xorstr_("<color=");

	if (assembler::vrc::core::api_user::is_friends_with(apiuser->get_id()))
		rank += xorstr_("#fce621>");
	else if (apiuser->has_tag(xorstr_("admin_scripting_access")) || apiuser->has_tag(xorstr_("admin_moderator")) || apiuser->has_tag(xorstr_("admin")))
		rank += xorstr_("#ef1062>");
	else if (apiuser->has_tag(xorstr_("system_trust_veteran")))
		rank += utility::format(xorstr_("#{}>"), config::get<sdk::color>(g_context.c_trusted).get_hex());
	else if (apiuser->has_tag(xorstr_("system_trust_trusted")))
		rank += utility::format(xorstr_("#{}>"), config::get<sdk::color>(g_context.c_known).get_hex());
	else if (apiuser->has_tag(xorstr_("system_trust_known")))
		rank += utility::format(xorstr_("#{}>"), config::get<sdk::color>(g_context.c_user).get_hex());
	else if (apiuser->has_tag(xorstr_("system_trust_basic")))
		rank += utility::format(xorstr_("#{}>"), config::get<sdk::color>(g_context.c_newuser).get_hex());
	else
		rank += utility::format(xorstr_("#{}>"), config::get<sdk::color>(g_context.c_visitor).get_hex());

	rank += display_name;
	rank += xorstr_("</color>");

	return rank;
}

sdk::color misc::get_user_rank_color(assembler::vrc::core::api_user* apiuser)
{
	if (assembler::vrc::core::api_user::is_friends_with(apiuser->get_id()))
		return { 252, 230, 33 };
	if (apiuser->has_tag(xorstr_("admin_scripting_access")) || apiuser->has_tag(xorstr_("admin_moderator")) || apiuser->has_tag(xorstr_("admin")))
		return { 239, 16, 98 };
	if (apiuser->has_tag(xorstr_("system_trust_veteran")))
		return config::get<sdk::color>(g_context.c_trusted);
	if (apiuser->has_tag(xorstr_("system_trust_trusted")))
		return config::get<sdk::color>(g_context.c_known);
	if (apiuser->has_tag(xorstr_("system_trust_known")))
		return config::get<sdk::color>(g_context.c_user);
	if (apiuser->has_tag(xorstr_("system_trust_basic")))
		return config::get<sdk::color>(g_context.c_newuser);

	return { 250, 250, 250 };
}
#pragma endregion

std::string misc::get_device_id()
{
	// VMProtectBeginMutation("GetDeviceID");

	GUID guid;
	if (CoCreateGuid(&guid) != S_OK)
		return SECSTR("failed to obtain device identifier.");

	char guid_str[37];
	sprintf(guid_str,
		SECSTR("%08lX-%04hX-%04hX-%02hhX%02hhX-%02hhX%02hhX%02hhX%02hhX%02hhX%02hhX"),
		guid.Data1, guid.Data2, guid.Data3,
		guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
		guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);

	char hex[SHA1_HEX_SIZE];
	sdk::hash::sha1(guid_str).finalize().print_hex(hex);
	// VMProtectEnd();
	return hex;
}
