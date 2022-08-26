#pragma once
#include <mutex>
#include <shared_mutex>
#include <unordered_set>

#include "../../../utilities/misc_utils.hpp"
#include "../../assembler/unityengine/recttransform.hpp"
#include "../../assembler/unityengine/skinnedmeshrenderer.hpp"
#include "../../assembler/unityengine/meshrenderer.hpp"
#include "../../assembler/vrc/sdkbase/vrc_mirror_reflection.hpp"

class nameplate_manager
{
	static inline std::unordered_map<std::int32_t, std::uint64_t> events_map_{};
	static inline std::unordered_set<std::string> userlist_{};
	static inline std::unordered_map<std::string, std::string> userplates_{};
	static inline std::unordered_map<std::int32_t, std::int32_t> mirror_map_{};

	static inline std::mutex nm_mutex_{};
	static inline std::array <std::shared_mutex, 2u> shared_mutexes_{};

	assembler::vrc_player* player_ = nullptr;
	assembler::vrc::core::api_user* apiuser_ = nullptr;
	assembler::player_nameplate* nameplate_ = nullptr;
	assembler::unity_engine::transform* nameplate_transform_ = nullptr;

	void render_chams(bool is_local) const;
	void render_outline(bool value) const;
public:
	static void set_tags(const nlohmann::json& ref);
	static void cleanup_user(std::int32_t player);
	static void cleanup(bool full_clean);
	static void update_user(std::int32_t player);
	static void fix_mirrormasks(bool no_restore);

	static std::unordered_set<std::string>& get_userlist();
	static std::unordered_map<std::string, std::string>& get_userplates();
	static std::array<std::shared_mutex, 2ull>& get_mutexes();

	nameplate_manager() = default;
	explicit nameplate_manager(assembler::vrc_player* player);

	void render_colors() const;
	_NODISCARD bool render_tags() const;
	_NODISCARD bool render_info() const;
	void render_blocked(bool is_blocked) const;
	void overrender() const;

	static bool is_client_user(const std::string& id);
	_NODISCARD bool is_ready() const;
};
