/*
 *		globals.hpp
 *		Void
 *
 *		Created by Azurilex on 09/17/2021
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Global definitions and variables
 */


#ifndef GLOBALS_HPP
#define GLOBALS_HPP
#pragma once
#include "discordrpc/discord.hpp"
#include "core/config.hpp"

#define TEST 0
constexpr auto build = "107";
#if TEST == 1
constexpr auto stage = "test";
#else
constexpr auto stage = "main";
#endif

inline std::string msg = xorstr_("www.invalid.gg");

struct global_variables
{
	// @note: config vars
    // @note: packet logging
    enum e_packet_types : std::size_t
    {
	    uspeak_audio, // @ note: 1
        executive_message, // @ note: 2
        mc_sync_start, // @ note: 3
        cached_event, // @ note: 4
        mc_sync_finished, // @ note: 5
        vrchat_rpc, // @ note: 6
        serialized_data_unreliable, // @ note: 7
        interest_management, // @ note: 8
        serialized_data_reliable, // @ note: 9
        executive_moderation, // @ note: 33
        set_actor_properties, // @ note: 40
        set_actor_properties2, // @note: 42
        physbones_permissions, // @ note: 60
        photon_rpc, // @ note: 200
        send_serialize, // @ note: 201
        object_instantiation, // @ note: 202
        close_connection, // @ note: 203
        destroy_object, // @ note: 204
        remove_cached_rpcs, // @ note: 205
        send_serialize_reliable, // @ note: 206
        assign_master, // @ note: 208
        ownership_request, // @ note: 209
        ownership_transfer, // @ note: 210
        auth_event, // @ note: 223
        lobby_stats, // @ note: 224
        app_stats, // @ note: 226
        game_list_update, // @ note: 229
        game_list, // @ note: 230
        cache_slice_changed, // @ note: 250
        error_info, // @ note: 251
        properties_changed, // @ note: 253
        leave, // @ note: 254
        join // @ note: 255
    };
    C_ADD_VARIABLE_VECTOR(bool, join+1, vec_packet_log, false);

    // @note: rendering
    C_ADD_VARIABLE(bool, nametags, false);
    C_ADD_VARIABLE(bool, esp, false);
    C_ADD_VARIABLE(bool, chams, false);
    C_ADD_VARIABLE(bool, dx11_esp, false);
    C_ADD_VARIABLE(bool, dx11_tracers, false);

    // @note: safety
    C_ADD_VARIABLE(std::vector<std::string>, avatar_blacklist, {});
    C_ADD_VARIABLE(std::vector<std::string>, avatar_whitelist, {});
    C_ADD_VARIABLE(std::vector<std::string>, user_event_blacklist, {});
    C_ADD_VARIABLE(bool, anti_portal, false);
    C_ADD_VARIABLE(bool, anti_worldtriggers, false);
    C_ADD_VARIABLE(bool, anti_udon_events, false);
    C_ADD_VARIABLE(bool, anti_master_dc, false);
    C_ADD_VARIABLE(bool, anti_aa12, false);
    C_ADD_VARIABLE(bool, anti_block, false);
    C_ADD_VARIABLE(bool, anti_video_exploit, false);
    C_ADD_VARIABLE(bool, anti_audio_crash, false);
    C_ADD_VARIABLE(bool, reduce_bad_activity, false);
    C_ADD_VARIABLE(bool, anti_uspeak_exploit, false);
    C_ADD_VARIABLE(bool, detect_invisibles, false);
    C_ADD_VARIABLE(bool, anti_object_spam, false);
    C_ADD_VARIABLE(bool, anti_avatar_crash, false);
    C_ADD_VARIABLE(bool, anti_blacklisted_avatars, false);
    C_ADD_VARIABLE(bool, anti_avatar_audio, false);
    C_ADD_VARIABLE(bool, anti_head_sit, false);
    C_ADD_VARIABLE(bool, prevent_portals, false);
    C_ADD_VARIABLE(bool, portal_takeover, false);
    C_ADD_VARIABLE(bool, anti_instance_lock, false);
    C_ADD_VARIABLE(bool, allow_friends, false);
    C_ADD_VARIABLE(bool, anti_ro_nulls, false);
    C_ADD_VARIABLE(bool, anti_audio_mixers, false);
    C_ADD_VARIABLE(bool, anti_oob, false);
    C_ADD_VARIABLE(bool, anti_array_overflow, false);
    C_ADD_VARIABLE(bool, anti_stream, false);

    // @note: malicious
    C_ADD_VARIABLE(bool, corrupt_asset_crash, false);
    C_ADD_VARIABLE(bool, audio_crash, false);
    C_ADD_VARIABLE(bool, quest_crash, false);
    C_ADD_VARIABLE(bool, collision_crash, false);

    // @note: lovense
    C_ADD_VARIABLE(bool, lovense_binds, false);

    // @note: colors 179 66 245
    C_ADD_VARIABLE(sdk::color, color_primtv6, sdk::color(149, 98, 239));
    C_ADD_VARIABLE(sdk::color, color_accent1, sdk::color(156, 79, 239))
    C_ADD_VARIABLE(sdk::color, color_accent0, sdk::color(170, 107, 241));
    C_ADD_VARIABLE(sdk::color, color_accent2, sdk::color(123, 80, 240));

    // @note: exploits
    C_ADD_VARIABLE(bool, serialize, false);
    C_ADD_VARIABLE(bool, exploit_event_1, false);
    C_ADD_VARIABLE(bool, event_7_test, false);
    C_ADD_VARIABLE(bool, high_db, false);
    C_ADD_VARIABLE(bool, emoji_spam, false);
    C_ADD_VARIABLE(int, emoji_to_spam, 0);
    C_ADD_VARIABLE(bool, instance_lock, false);
    C_ADD_VARIABLE(bool, invisible_join, false);
    C_ADD_VARIABLE(int, copy_event1, 0);

    // @note: spoofing
    C_ADD_VARIABLE(bool, fake_ping, false);
    C_ADD_VARIABLE(int, fake_ping_i, 69);
    C_ADD_VARIABLE(int, fake_ping_range, 0);
    C_ADD_VARIABLE(bool, fake_hwid, false);
    C_ADD_VARIABLE(std::string, set_hwid, xorstr_(""));
    C_ADD_VARIABLE(bool, fake_fps, false);
    C_ADD_VARIABLE(int, fake_fps_i, 69);
    C_ADD_VARIABLE(int, fake_fps_range, 0);
    C_ADD_VARIABLE(bool, fake_offline, false);
    C_ADD_VARIABLE(int, fps_target_i, 144);
    C_ADD_VARIABLE(bool, fps_target, false);

    // @note: games
    C_ADD_VARIABLE(bool, udon_namespoof, false);
    C_ADD_VARIABLE(bool, udon_namespoof_patreon, false);
    C_ADD_VARIABLE(std::string, udon_namespoof_name, xorstr_("Austin"));
    C_ADD_VARIABLE(bool, fbt_doorbypass, false);
    C_ADD_VARIABLE(bool, murder_anti_killcam, false);
    C_ADD_VARIABLE(bool, murder_weapontriggers, false);
    C_ADD_VARIABLE(bool, udon_godmode, false);

    // @note: utils/fun
    C_ADD_VARIABLE(int, thirdperson_mode, 1);
    C_ADD_VARIABLE(bool, flight, false);
    C_ADD_VARIABLE(float, flight_speed, 10.f);
    C_ADD_VARIABLE(bool, click_teleport, false);
    C_ADD_VARIABLE(int, status_mode, 0);
    C_ADD_VARIABLE(bool, rotate_avatar, false);
    C_ADD_VARIABLE(bool, deserialize_bind, false);
    C_ADD_VARIABLE(std::string, base_virtualization, xorstr_("wrld_6124f26b-c348-4ef7-bab8-d41fb304c420:::https://api.vrchat.cloud/api/1/file/file_b2ea2db2-6c02-4821-9ebe-53123a49dd40/71/file"));
    C_ADD_VARIABLE(bool, virtualize_world, false);
    C_ADD_VARIABLE(bool, cozyvrmenu, false);

    // @note: config
    C_ADD_VARIABLE(bool, display_online, true);
    C_ADD_VARIABLE(bool, discord_rpc_toggle, false);
    C_ADD_VARIABLE(bool, xs_overlay_toggle, false);
    C_ADD_VARIABLE(bool, nameplate_info, false);
    C_ADD_VARIABLE(bool, player_list_toggle, false);
    C_ADD_VARIABLE(bool, desktop_debug_log, true);
    C_ADD_VARIABLE(bool, qm_debug_log, false);
    C_ADD_VARIABLE(bool, quickmenu_persistence, false);
    C_ADD_VARIABLE(bool, custom_plates, true);
    C_ADD_VARIABLE(bool, player_info, false);
    C_ADD_VARIABLE(bool, join_notify, false);
    C_ADD_VARIABLE(bool, join_notify_friends, false);
    C_ADD_VARIABLE(bool, rgb_elements, false);
    C_ADD_VARIABLE(bool, watermark, true);
    C_ADD_VARIABLE(bool, statistics, true);

    // @note: mirror
    C_ADD_VARIABLE(float, mirror_scale_x, 4.f);
    C_ADD_VARIABLE(float, mirror_scale_y, 2.5f);
    C_ADD_VARIABLE(bool, optimized_mirror, false);
    C_ADD_VARIABLE(bool, mirror_pickup, false);

    // @note: keybinds
    C_ADD_VARIABLE(int, flight_key, 0x0);
    C_ADD_VARIABLE(int, esp_key, 0x0);
    C_ADD_VARIABLE(int, deserialize_key, 0x0);
    C_ADD_VARIABLE(int, thirdperson_key, 0x0);
    C_ADD_VARIABLE(int, menu_key, 0x4C);
    C_ADD_VARIABLE(int, playerlist_key, 0x09);
    C_ADD_VARIABLE(int, panic_key, 0xDC);

    // @note: trust colors
    C_ADD_VARIABLE(sdk::color, c_visitor, sdk::color(255, 255, 255));
    C_ADD_VARIABLE(sdk::color, c_newuser, sdk::color(29, 124, 255));
    C_ADD_VARIABLE(sdk::color, c_user, sdk::color(42, 207, 91));
    C_ADD_VARIABLE(sdk::color, c_known, sdk::color(255, 124, 66))
    C_ADD_VARIABLE(sdk::color, c_trusted, sdk::color(145, 50, 230));
    C_ADD_VARIABLE(sdk::color, c_friend, sdk::color(252, 230, 33));

    // @note: globals
    bool instantiated = false;
    bool player_attach = false;
    bool third_person = false;
    bool block_downloads = false;
    bool anti_aim = false;

    std::int32_t skippable_sync_kills = 0;
    std::int32_t player_attach_id = 0;

    std::string load_device = xorstr_("NONE");
    std::string changing_avatar{};
    std::string room_id{};

    std::unique_ptr<discord_sdk> g_discord{};

    static inline const std::array<std::string, 4> g_avatars =
    {
        std::string(SECSTR("avtr_96c2e9e4-6d1d-4c11-a880-d6fc1783aa4f")), //game closer
        std::string(SECSTR("avtr_d7707f7b-b3da-4284-80ba-5d3a27d8506a")), //shader
        std::string(SECSTR("avtr_15fcf5f3-af72-4fa7-9453-93efd57328fa")), //quest
        std::string(SECSTR("avtr_24eadfb3-95e1-405f-8e4f-0dfe885f46e6"))  //corrupted
    };

} inline g_context;

#endif
