#pragma once
#include "../../utilities/drawing.hpp"
#include "../../dependencies/imgui/imgui_stdlib.h"
#include "../assembler/vrc/player.hpp"
#include <unordered_set>

namespace sniffer_window
{
	void render_window(const std::vector<assembler::vrc::player*>& players);
	void print_log(std::string_view fmt);
	void clear_logs();

	inline ImGuiTextBuffer buf;
	inline ImGuiTextFilter filter;
	inline ImVector<int> line_offsets;
	inline std::mutex m_log_mutex{};
	inline std::shared_mutex sniffer_mutex{};
	inline std::unordered_set logging_players{-1, 0};

	inline bool log_self = false;
	inline bool enabled = false;
	inline bool block_outgoing = false;
	inline bool block_incoming = false;
	inline bool opened;
}