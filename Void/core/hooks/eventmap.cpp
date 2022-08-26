#include "eventmap.hpp"

#include <ranges>

std::size_t event_map::convert_packet_to_config_type(const std::uint8_t value)
{
	switch (value)
	{
	case uspeak_audio: return global_variables::uspeak_audio;
	case executive_message: return global_variables::executive_message;
	case mc_sync_start: return global_variables::mc_sync_start;
	case cached_event: return global_variables::cached_event;
	case mc_sync_finished: return global_variables::mc_sync_finished;
	case vrchat_rpc: return global_variables::vrchat_rpc;
	case serialized_data_unreliable: return global_variables::serialized_data_unreliable;
	case interest_management: return global_variables::interest_management;
	case serialized_data_reliable: return global_variables::serialized_data_reliable;
	case executive_moderation: return global_variables::executive_moderation;
	case set_actor_properties: return global_variables::set_actor_properties;
	case set_actor_properties2: return global_variables::set_actor_properties2;
	case physbones_permissions: return global_variables::physbones_permissions;
	case photon_rpc: return global_variables::photon_rpc;
	case send_serialize: return global_variables::send_serialize;
	case object_instantiation: return global_variables::object_instantiation;
	case close_connection: return global_variables::close_connection;
	case destroy_object: return global_variables::destroy_object;
	case remove_cached_rpcs: return global_variables::remove_cached_rpcs;
	case send_serialize_reliable: return global_variables::send_serialize_reliable;
	case assign_master: return global_variables::assign_master;
	case ownership_request: return global_variables::ownership_request;
	case ownership_transfer: return global_variables::ownership_transfer;
	case auth_event: return global_variables::auth_event;
	case lobby_stats: return global_variables::lobby_stats;
	case app_stats: return global_variables::app_stats;
	case game_list_update: return global_variables::game_list_update;
	case game_list: return global_variables::game_list;
	case cache_slice_changed: return global_variables::cache_slice_changed;
	case error_info: return global_variables::error_info;
	case properties_changed: return global_variables::properties_changed;
	case leave: return global_variables::leave;
	case join: return global_variables::join;
	default: return 256;
	}
}

#pragma region map_logic
event_map::event_map() : current_time_(0)
{
}

bool event_map::is_user_blocked(const std::string& userid) const
{
	if (const auto v = config::get<std::vector<std::string>>(g_context.user_event_blacklist); std::ranges::find(v, userid) != v.end())
		return true;

	return false;
}

void event_map::cleanup()
{
	SEH_START
		std::lock_guard etguard(event_table_mutex_);
		event_table_.clear();
		std::lock_guard blguard(blacklisted_users_mutex_);
		blacklisted_users_.clear();
		std::lock_guard spsguard(sends_per_second_mutex_);
		sends_per_sec_.clear();
	SEH_END
}

void event_map::cleanup_user(const std::int32_t sender_id)
{
	// @note: https://en.cppreference.com/w/cpp/container/map/erase_if
	try
	{
		std::lock_guard etguard(event_table_mutex_);

		std::erase_if(event_table_, [&](const auto& item)
		{
			const auto& [key, value] = item;
			return key.first == sender_id;
		});
	}
	catch (const std::exception& e)
	{
		logging::push(FOREGROUND_INTENSE_RED);
		logging::print(xorstr_("[critical] {}\n"), e.what());
		logging::pop();
	}
}

void event_map::only_allow_per_seccond(const std::string& event_name, const std::int32_t amount)
{
	if (allowed_sends_per_sec_.contains(event_name))
		return;

	std::lock_guard apsguard(allowed_per_second_mutex_);
	allowed_sends_per_sec_[event_name] = amount;
}

void event_map::forgive_user(const std::int32_t id, const std::uint8_t code)
{
	try
	{
		if (is_blacklisted(id, code))
		{
			std::lock_guard guard(blacklisted_users_mutex_);
			blacklisted_users_.erase(std::make_pair(id, code));
		}
	}
	catch (const std::exception& e)
	{
		logging::push(FOREGROUND_INTENSE_RED);
		logging::print(xorstr_("[critical] {}\n"), e.what());
		logging::pop();
	}
}

void event_map::forgive_user_timout(const std::int32_t id, const std::uint8_t code)
{
	std::this_thread::sleep_for(std::chrono::seconds(3));
	forgive_user(id, code);
}

bool event_map::is_blacklisted(const std::int32_t sender_id, const std::uint8_t code)
{
	std::lock_guard guard(blacklisted_users_mutex_);
	return blacklisted_users_.contains(std::make_pair(sender_id, code));
}

void event_map::blacklist_user(const std::int32_t sender_id, const std::uint8_t code)
{
	if (is_blacklisted(sender_id, code))
		return;

	std::lock_guard guard(blacklisted_users_mutex_);
	blacklisted_users_.insert(std::make_pair(sender_id, code));

	std::thread(&event_map::forgive_user_timout, this, sender_id, code).detach();
}

bool event_map::is_event_safe(const std::string& event_name, const std::uint8_t event_code, const std::int32_t sender_id)
{
	if (is_blacklisted(sender_id, event_code))
		return false;

	if (const auto total_ms = duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count(); total_ms / 100 - current_time_ / 100 > 10)
	{
		current_time_ = total_ms;

		for (auto& map : sends_per_sec_ | std::ranges::views::values)
		{
			std::lock_guard spsguard(sends_per_second_mutex_);
			map.clear();
		}
	}
	else
	{
		// @note: safeguard if event doesn't get caught
		// @credits: requi for logic

		std::lock_guard spsguard(sends_per_second_mutex_);

		if (!sends_per_sec_.contains(sender_id))
			sends_per_sec_.emplace(sender_id, std::map<std::string, std::int32_t>{});

		if (!sends_per_sec_[sender_id].contains(event_name))
			sends_per_sec_[sender_id][event_name] = 1;

		else sends_per_sec_[sender_id][event_name]++;

		if (!allowed_sends_per_sec_.contains(event_name))
			return true;

		if (sends_per_sec_[sender_id][event_name] > allowed_sends_per_sec_[event_name])
		{
			if (sender_id)
			{
				const auto apiuser = assembler::vrc::player_manager::get_player(sender_id)->get_api_user();
				ingame_logging::get().log(SECSTR("[<color=#a75cf6>rba</color>] too much {} from {}"), event_name, apiuser->display_name());
				logging::push(FOREGROUND_INTENSE_BLUE);
				logging::add_log(SECSTR("[rba] too much {} from {}\n"), event_name, apiuser->display_name());
				logging::pop();
			}
			blacklist_user(sender_id, event_code);
			return false;
		}
	}

	return true;
}
#pragma endregion

#pragma region byte_parser

// @note: repetition logic
bool event_map::is_event_mapped(std::uint8_t event_code, std::int32_t sender_id, std::vector<std::uint8_t>& data)
{
	const auto event_pair = std::make_pair(sender_id, event_code);

	if (!event_table_.contains(event_pair))
	{
		std::lock_guard event_table_guard(event_table_mutex_);
		event_table_.emplace(event_pair, data);
		return false;
	}

	auto& old_data = event_table_.at(event_pair);
	const std::vector data_copy(data);

	try
	{
		if (old_data.size() >= 9 && data.size() >= 9)
		{
			data.erase(data.begin(), data.begin() + 9);
			old_data.erase(old_data.begin(), old_data.begin() + 9);

			if (old_data == data)
			{
				old_data = data_copy;
				return true;
			}
		}

		if (old_data.size() >= 81 && data.size() >= 81 && event_code != 9)
		{
			data.erase(data.begin(), data.begin() + 51);
			data.erase(data.begin() + 29, data.end());
			old_data.erase(old_data.begin(), old_data.begin() + 51);
			old_data.erase(old_data.begin() + 29, old_data.end());

			if (old_data == data)
			{
				old_data = data_copy;
				return true;
			}
		}
	}
	catch (const std::exception& e)
	{
		logging::push(FOREGROUND_INTENSE_RED);
		logging::print(xorstr_("[critical] {}\n"), e.what());
		logging::pop();
	}

	old_data = data_copy;

	return false;
}

std::vector<std::uint8_t>& event_map::retrieve_previous_bytes(const std::pair<std::int32_t, std::uint8_t> key)
{
	std::lock_guard event_table_guard(event_table_mutex_);
	return event_table_[key];
}
#pragma endregion
