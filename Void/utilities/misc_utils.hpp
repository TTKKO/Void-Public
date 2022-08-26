/*
 *		utilities/misc_utils.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Misc. functions used throughout the source code
 */
#ifndef MISC_UTILS_HPP
#define MISC_UTILS_HPP

#pragma once
#include "../core/sdk/hash/sha1.hpp"
#include "../core/assembler/unityengine/time.hpp"
#include "../core/assembler/vrc/sdkbase/vrcplayerapi.hpp"
#include "../core/assembler/vrc/ui/pageavatar.hpp"
#include "../core/assembler/assembly-csharp/moderationmanager.hpp"
#include "../core/assembler/unityengine/application.hpp"
#include "../core/assembler/unityengine/assetbundle.hpp"
#include "../core/assembler/assembly-csharp/udon_sync.hpp"
#include "../core/assembler/vrc/sdkbase/networking.hpp"
#include "../core/assembler/vrc/sdkbase/vrc_pickup.hpp"
#include "../core/assembler/unityengine/character_controller.hpp"
#include "../core/assembler/assembly-csharp/assetbundle_download_manager.hpp"
#include "../core/assembler/assembly-csharp/system/collections/arraylist.hpp"
#include "ingame_logging.hpp"
#include "../core/hooks/helpers/xs_overlay.hpp"

namespace assembler::vrc
{
	struct player;
}

namespace assembler::assembler::vrc::core
{
	struct api_user;
}

struct misc
{
private:
	inline static assembler::il2cpp::il2cpp_type* portal_type_ = nullptr;

public:
	inline static std::filesystem::path cached_path{};
	inline static bool cache_finished = true;
	inline static assembler::unity_engine::assetbundle* cached_assetbundle = nullptr;
	inline static assembler::unity_engine::game_object* cached_asset = nullptr;

	static bool curl_downloadfile(const char* url, std::string_view avtr);
	static void load_config();

	static void change_avatar(std::string_view avatar_id);
	static void handle_avatar_clone(bool value);
	static void toggle_flight(bool value);

	static void toggle_download_manager(bool state);
	static void remove_avatar_from_cache(std::string_view avatar_id);

	static sdk::color get_rainbow()
	{
		return sdk::color::from_hsb(std::fabsf(std::fmodf((assembler::unity_engine::time::get_time() + 1.f) * 0.1f, 2.f) - 1.f), 0.5f, 1.f);
	}

	static void drop_portal(const std::string& worldid);
	static bool teleport_pickups(const sdk::vector& position);
	static void set_pickups(bool value);
	static bool destroy_portals();

	static void udon_killall(std::int32_t* ref);
	static void murder_teleportsingle(std::wstring_view item);
	static void murder_teleportall();

	static std::string get_social_rank_for_player_list(assembler::vrc::player* player, assembler::vrc::core::api_user* user);
	static std::string get_social_rank_for_player_list_shadow(assembler::vrc::player* player, const assembler::vrc::core::api_user* user);
	static std::string get_user_rank(assembler::vrc::core::api_user* apiuser);
	static sdk::color get_user_rank_color(assembler::vrc::core::api_user* apiuser);

	static std::string get_device_id();
};

#endif
