/*
 *		hooks/eventmap.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Photon event parser
 */
#ifndef EVENTMAP_HPP
#define EVENTMAP_HPP

#pragma once
#include <mutex>
#include <unordered_set>

#include "../../utilities/utilities.hpp"
#include "../../globals.hpp"
#include "../assembler/vrc/playermanager.hpp"
#include "../../utilities/ingame_logging.hpp"
#include "../assembler/vrc/udon/serialization/odinserializer/properbitconverter.hpp"

// @note: required to use pair keylookup in hashmaps/sets
struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& pair) const { return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second); }
};

class event_map
{
    static inline std::unordered_map<std::pair<std::int32_t, std::uint8_t>, std::vector<std::uint8_t>, pair_hash> event_history_{};

    std::unordered_map<std::int32_t, std::map<std::string, std::int32_t>> sends_per_sec_{};
    std::unordered_map<std::string, std::int32_t> allowed_sends_per_sec_{};
    std::unordered_map<std::pair<std::int32_t, std::uint8_t>, std::vector<std::uint8_t>, pair_hash> event_table_{};
    std::unordered_set<std::pair<std::int32_t, std::uint8_t>, pair_hash> blacklisted_users_{};
    std::mutex event_table_mutex_;
    std::mutex blacklisted_users_mutex_;
    std::mutex sends_per_second_mutex_;
    std::mutex allowed_per_second_mutex_;

    std::int64_t current_time_;

    void forgive_user(std::int32_t id, std::uint8_t code);
    void forgive_user_timout(std::int32_t id, std::uint8_t code);
public:
    enum e_photon_packet : std::uint8_t
    {
        uspeak_audio = 1,
        executive_message = 2,
        mc_sync_start = 3,
        cached_event = 4,
        mc_sync_finished = 5,
        vrchat_rpc = 6,
        serialized_data_unreliable = 7,
        interest_management = 8,
        serialized_data_reliable = 9,
        executive_moderation = 33,
        set_actor_properties = 40,
        set_actor_properties2 = 42,
        physbones_permissions = 60,
        photon_rpc = 200,
        send_serialize = 201,
        object_instantiation = 202,
        close_connection = 203,
        destroy_object = 204,
        remove_cached_rpcs = 205,
        send_serialize_reliable = 206,
        destroy_player = 207,
        assign_master = 208,
        ownership_request = 209,
        ownership_transfer = 210,
        vacant_view_ids = 211,
        auth_event = 223,
        lobby_stats = 224,
        app_stats = 226,
        game_list_update = 229,
        game_list = 230,
        cache_slice_changed = 250,
        error_info = 251,
        properties_changed = 253,
        leave = 254,
        join
    };

    inline static const std::unordered_map<std::string, std::int32_t> rpc_parameter_count = {
        {SECSTR("ReceiveVoiceStatsSyncRPC"), 3},
        {SECSTR("InformOfBadConnection"), 2},
        {SECSTR("initUSpeakSenderRPC"), 1},
        {SECSTR("InteractWithStationRPC"), 1},
        {SECSTR("SpawnEmojiRPC"), 3},
        {SECSTR("SanityCheck"), 3},
        {SECSTR("PlayEmoteRPC"), 1},
        {SECSTR("TeleportRPC"), 4},
        {SECSTR("CancelRPC"), 0},
        {SECSTR("SetTimerRPC"), 1},
        {SECSTR("_DestroyObject"), 1},
        {SECSTR("_InstantiateObject"), 4},
        {SECSTR("_SendOnSpawn"), 1},
        {SECSTR("ConfigurePortal"), 3},
        {SECSTR("UdonSyncRunProgramAsRPC"), 1},
        {SECSTR("ChangeVisibility"), 1},
        {SECSTR("PhotoCapture"), 0},
        {SECSTR("TimerBloop"), 0},
        {SECSTR("ReloadAvatarNetworkedRPC"), 0},
        {SECSTR("InternalApplyOverrideRPC"), 1},
        {SECSTR("AddURL"), 1},
        {SECSTR("Play"), 0},
        {SECSTR("Pause"), 0},
        {SECSTR("SendVoiceSetupToPlayerRPC"), 0},
        {SECSTR("SendStrokeRPC"), 1}
    };

    inline static const std::unordered_map<std::string, std::pair<std::int32_t, std::int32_t>> rate_limit_values = {
        {SECSTR("Generic"), std::make_pair(500, 500)},
        {SECSTR("ReceiveVoiceStatsSyncRPC"), std::make_pair(348, 64)},
        {SECSTR("InformOfBadConnection"), std::make_pair(64, 6)},
        {SECSTR("initUSpeakSenderRPC"), std::make_pair(256, 6)},
        {SECSTR("InteractWithStationRPC"), std::make_pair(128, 32)},
        {SECSTR("SpawnEmojiRPC"), std::make_pair(32, 1)},
        {SECSTR("SanityCheck"), std::make_pair(256, 32)},
        {SECSTR("PlayEmoteRPC"), std::make_pair(256, 6)},
        {SECSTR("TeleportRPC"), std::make_pair(256, 16)},
        {SECSTR("CancelRPC"), std::make_pair(256, 32)},
        {SECSTR("SetTimerRPC"), std::make_pair(256, 64)},
        {SECSTR("_DestroyObject"), std::make_pair(512, 128)},
        {SECSTR("_InstantiateObject"), std::make_pair(512, 128)},
        {SECSTR("_SendOnSpawn"), std::make_pair(512, 128)},
        {SECSTR("ConfigurePortal"), std::make_pair(10, 1)},
        {SECSTR("UdonSyncRunProgramAsRPC"), std::make_pair(512, 128)},
        {SECSTR("ChangeVisibility"), std::make_pair(128, 12)},
        {SECSTR("PhotoCapture"), std::make_pair(128, 32)},
        {SECSTR("TimerBloop"), std::make_pair(128, 16)},
        {SECSTR("ReloadAvatarNetworkedRPC"), std::make_pair(128, 12)},
        {SECSTR("InternalApplyOverrideRPC"), std::make_pair(512, 128)},
        {SECSTR("AddURL"), std::make_pair(64, 6)},
        {SECSTR("Play"), std::make_pair(64, 6)},
        {SECSTR("Pause"), std::make_pair(64, 6)},
        {SECSTR("SendVoiceSetupToPlayerRPC"), std::make_pair(512, 6)},
        {SECSTR("SendStrokeRPC"), std::make_pair(512, 32)}
    };
    static std::size_t convert_packet_to_config_type(std::uint8_t value);

    bool is_blacklisted(std::int32_t sender_id, std::uint8_t code);
    event_map();
    _NODISCARD bool is_user_blocked(const std::string& userid) const;

	void set_current_time()
    {
        current_time_ = duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    }

    void cleanup();
    void cleanup_user(std::int32_t sender_id);
    void only_allow_per_seccond(const std::string& event_name, std::int32_t amount);
    void blacklist_user(std::int32_t sender_id, std::uint8_t code);
    bool is_event_safe(const std::string& event_name, std::uint8_t event_code, std::int32_t sender_id);

    bool is_event_mapped(std::uint8_t event_code, std::int32_t sender_id, std::vector<std::uint8_t>& data);
    std::vector<std::uint8_t>& retrieve_previous_bytes(std::pair<std::int32_t, std::uint8_t> key);
};

#endif
