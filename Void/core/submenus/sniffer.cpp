#include "sniffer.hpp"

void sniffer_window::render_window(const std::vector<assembler::vrc::player*>& players)
{
	const ImGuiStyle& style = ImGui::GetStyle();
	const ImGuiIO& io = ImGui::GetIO();

	ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Once, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSize(ImVec2(560, 510), ImGuiCond_Always);

	static const std::string title = xorstr_("void ") + std::string(stage) + xorstr_(" build ") + std::string(build) + xorstr_(" | photon net sniffer");
	ImGui::Begin(title.c_str(), &opened, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
	{
		ImGui::Columns(2, nullptr, false);
		{
			ImGui::BeginChild(xorstr_("events.1"), ImVec2(-1, 280), true, ImGuiWindowFlags_MenuBar);
			{
				if (ImGui::BeginMenuBar())
				{
					ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0.5f, 0.5f));
					ImGui::Selectable(xorstr_("events##master"), true, ImGuiSelectableFlags_None, ImVec2(50, 0));
					ImGui::PopStyleVar();
					ImGui::Spacing();
					if (ImGui::Button(xorstr_("toggle all"), ImVec2(-1.f, 0.f)))
					{
						const auto vec = &config::get<std::vector<bool>>(g_context.vec_packet_log);
						if (std::ranges::find(vec->begin(), vec->end(), false) != vec->end())
							std::fill(vec->begin(), vec->end(), true);
						else
							std::fill(vec->begin(), vec->end(), false);
					}

					ImGui::EndMenuBar();
				}

				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));

				ImGui::Checkbox(xorstr_("uspeak audio [1]"), config::get<std::vector<bool>>(g_context.vec_packet_log), global_variables::uspeak_audio);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("adds this event to the list"));
				ImGui::Checkbox(xorstr_("executive message [2]"), config::get<std::vector<bool>>(g_context.vec_packet_log), global_variables::executive_message);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("adds this event to the list"));
				ImGui::Checkbox(xorstr_("masterclient sync start [3]"), config::get<std::vector<bool>>(g_context.vec_packet_log), global_variables::mc_sync_start);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("adds this event to the list"));
				ImGui::Checkbox(xorstr_("cached event [4]"), config::get<std::vector<bool>>(g_context.vec_packet_log), global_variables::cached_event);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("adds this event to the list"));
				ImGui::Checkbox(xorstr_("masterclient sync finished [5]"), config::get<std::vector<bool>>(g_context.vec_packet_log), global_variables::mc_sync_finished);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("adds this event to the list"));
				ImGui::Checkbox(xorstr_("vrchat rpc [6]"), config::get<std::vector<bool>>(g_context.vec_packet_log), global_variables::vrchat_rpc);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("adds this event to the list"));
				ImGui::Checkbox(xorstr_("serialized data (unreliable) [7]"), config::get<std::vector<bool>>(g_context.vec_packet_log), global_variables::serialized_data_unreliable);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("adds this event to the list"));
				ImGui::Checkbox(xorstr_("interest management [8]"), config::get<std::vector<bool>>(g_context.vec_packet_log), global_variables::interest_management);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("adds this event to the list"));
				ImGui::Checkbox(xorstr_("serialized data (reliable) [9]"), config::get<std::vector<bool>>(g_context.vec_packet_log), global_variables::serialized_data_reliable);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("adds this event to the list"));
				ImGui::Checkbox(xorstr_("set actor properties [40]"), config::get<std::vector<bool>>(g_context.vec_packet_log), global_variables::set_actor_properties);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("adds this event to the list"));
				ImGui::Checkbox(xorstr_("set actor properties (internal) [42]"), config::get<std::vector<bool>>(g_context.vec_packet_log), global_variables::set_actor_properties2);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("adds this event to the list"));
				ImGui::Checkbox(xorstr_("physbones permissions [60]"), config::get<std::vector<bool>>(g_context.vec_packet_log), global_variables::physbones_permissions);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("adds this event to the list"));
				ImGui::Checkbox(xorstr_("photon rpc [200]"), config::get<std::vector<bool>>(g_context.vec_packet_log), global_variables::photon_rpc);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("adds this event to the list"));
				ImGui::Checkbox(xorstr_("send serialize (unreliable) [201]"), config::get<std::vector<bool>>(g_context.vec_packet_log), global_variables::send_serialize);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("adds this event to the list"));
				ImGui::Checkbox(xorstr_("object instantiation [202]"), config::get<std::vector<bool>>(g_context.vec_packet_log), global_variables::object_instantiation);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("adds this event to the list"));
				ImGui::Checkbox(xorstr_("close connection [203]"), config::get<std::vector<bool>>(g_context.vec_packet_log), global_variables::close_connection);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("adds this event to the list"));
				ImGui::Checkbox(xorstr_("destroy object [204]"), config::get<std::vector<bool>>(g_context.vec_packet_log), global_variables::destroy_object);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("adds this event to the list"));
				ImGui::Checkbox(xorstr_("remove cached rpcs [205]"), config::get<std::vector<bool>>(g_context.vec_packet_log), global_variables::remove_cached_rpcs);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("adds this event to the list"));
				ImGui::Checkbox(xorstr_("send serialize [206]"), config::get<std::vector<bool>>(g_context.vec_packet_log), global_variables::send_serialize_reliable);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("adds this event to the list"));
				ImGui::Checkbox(xorstr_("assign master [208]"), config::get<std::vector<bool>>(g_context.vec_packet_log), global_variables::assign_master);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("adds this event to the list"));
				ImGui::Checkbox(xorstr_("ownership request [209]"), config::get<std::vector<bool>>(g_context.vec_packet_log), global_variables::ownership_request);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("adds this event to the list"));
				ImGui::Checkbox(xorstr_("ownership request [210]"), config::get<std::vector<bool>>(g_context.vec_packet_log), global_variables::ownership_transfer);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("adds this event to the list"));
				ImGui::Checkbox(xorstr_("auth event [223]"), config::get<std::vector<bool>>(g_context.vec_packet_log), global_variables::auth_event);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("adds this event to the list"));
				ImGui::Checkbox(xorstr_("lobby stats [224]"), config::get<std::vector<bool>>(g_context.vec_packet_log), global_variables::lobby_stats);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("adds this event to the list"));
				ImGui::Checkbox(xorstr_("app stats [226]"), config::get<std::vector<bool>>(g_context.vec_packet_log), global_variables::app_stats);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("adds this event to the list"));
				ImGui::Checkbox(xorstr_("game list update [229]"), config::get<std::vector<bool>>(g_context.vec_packet_log), global_variables::game_list_update);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("adds this event to the list"));
				ImGui::Checkbox(xorstr_("game list [230]"), config::get<std::vector<bool>>(g_context.vec_packet_log), global_variables::game_list);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("adds this event to the list"));
				ImGui::Checkbox(xorstr_("cache slice changed [250]"), config::get<std::vector<bool>>(g_context.vec_packet_log), global_variables::cache_slice_changed);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("adds this event to the list"));
				ImGui::Checkbox(xorstr_("error info [251]"), config::get<std::vector<bool>>(g_context.vec_packet_log), global_variables::error_info);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("adds this event to the list"));
				ImGui::Checkbox(xorstr_("properties changed [253]"), config::get<std::vector<bool>>(g_context.vec_packet_log), global_variables::properties_changed);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("adds this event to the list"));
				ImGui::Checkbox(xorstr_("leave [254]"), config::get<std::vector<bool>>(g_context.vec_packet_log), global_variables::leave);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("adds this event to the list"));
				ImGui::Checkbox(xorstr_("join [255]"), config::get<std::vector<bool>>(g_context.vec_packet_log), global_variables::join);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("adds this event to the list"));

				ImGui::PopStyleVar();
				ImGui::EndChild();
			}

			ImGui::NextColumn();

			static float settings_size = 0.f;
			ImGui::BeginChild(xorstr_("settings.1"), ImVec2(0, settings_size), true, ImGuiWindowFlags_MenuBar);
			{
				if (ImGui::BeginMenuBar())
				{
					ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0.5f, 0.5f));
					ImGui::Selectable(xorstr_("settings##master"), true, ImGuiSelectableFlags_None, ImVec2(50, 0));
					ImGui::PopStyleVar();
					ImGui::EndMenuBar();
				}
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));

				ImGui::Checkbox(xorstr_("sniffing activated"), &enabled);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("activates photon network sniffer logging"));
				if (ImGui::Checkbox(xorstr_("block selected from sending"), &block_outgoing))
				{
					if (block_outgoing)
					{
						block_outgoing = false;
						ImGui::OpenPopup(xorstr_("warning##outgoing.warning"));
					}
				}
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("blocks selected events from being sent by you"));
				if (ImGui::Checkbox(xorstr_("block selected from receiving"), &block_incoming))
				{
					if (block_incoming)
					{
						block_incoming = false;
						ImGui::OpenPopup(xorstr_("warning##incoming.warning"));
					}
				}
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("blocks selected events from being received locally (from all players, ignores selection)"));

				ImGui::PopStyleVar();

				if (ImGui::BeginPopupModal(xorstr_("warning##outgoing.warning"), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize))
				{
					ImGui::Text(xorstr_("enabling this can cause undeseriable effects to your game."));
					ImGui::Text(xorstr_("if you wish to proceed, click \"yes\", otherwise, click \"no\"."));

					ImGui::Spacing();

					if (ImGui::Button(xorstr_("yes."), ImVec2(30, 0)))
					{
						block_outgoing = true;
						ImGui::CloseCurrentPopup();
					}
					ImGui::SameLine();
					if (ImGui::Button(xorstr_("no."), ImVec2(30, 0)))
						ImGui::CloseCurrentPopup();

					ImGui::EndPopup();
				}

				if (ImGui::BeginPopupModal(xorstr_("warning##incoming.warning"), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize))
				{
					ImGui::Text(xorstr_("enabling this can cause undeseriable effects to your game."));
					ImGui::Text(xorstr_("if you wish to proceed, click \"yes\", otherwise, click \"no\"."));

					ImGui::Spacing();

					if (ImGui::Button(xorstr_("yes."), ImVec2(30, 0)))
					{
						block_incoming = true;
						ImGui::CloseCurrentPopup();
					}
					ImGui::SameLine();
					if (ImGui::Button(xorstr_("no."), ImVec2(30, 0)))
						ImGui::CloseCurrentPopup();

					ImGui::EndPopup();
				}

				settings_size = ImGui::GetCursorPosY() + style.ItemSpacing.y;
				ImGui::EndChild();
			}

			static float outgoing_size = 0.f;
			ImGui::BeginChild(xorstr_("outgoing.1"), ImVec2(0, outgoing_size), true, ImGuiWindowFlags_MenuBar);
			{
				if (ImGui::BeginMenuBar())
				{
					ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0.5f, 0.5f));
					ImGui::Selectable(xorstr_("outgoing##master"), true, ImGuiSelectableFlags_None, ImVec2(50, 0));
					ImGui::PopStyleVar();
					ImGui::EndMenuBar();
				}
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));

				ImGui::Checkbox(xorstr_("self"), &log_self);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("sniffs your own outgoing photon packets"));

				ImGui::PopStyleVar();
				outgoing_size = ImGui::GetCursorPosY() + style.ItemSpacing.y;
				ImGui::EndChild();
			}

			ImGui::BeginChild(xorstr_("incoming.1"), ImVec2(-1.f, 136.f), true, ImGuiWindowFlags_MenuBar);
			{
				if (ImGui::BeginMenuBar())
				{
					ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0.5f, 0.5f));
					ImGui::Selectable(xorstr_("incoming##master"), true, ImGuiSelectableFlags_None, ImVec2(50, 0));
					ImGui::PopStyleVar();
					ImGui::EndMenuBar();
				}
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));

				static bool server = true;
				if (ImGui::Checkbox(xorstr_("server"), &server))
				{
					std::lock_guard guard(sniffer_mutex);

					if (!server && logging_players.contains(0))
					{
						logging_players.erase(-1);
						logging_players.erase(0);
					}
					else if (server && !logging_players.contains(0))
					{
						logging_players.insert(-1);
						logging_players.insert(0);
					}
				}
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("sniffs the server's incoming photon packets"));

				if (g_context.instantiated)
				{
					for (const auto player : players)
					{
						const auto viewid = player->get_photon_id();

						if (viewid == assembler::vrc::player::get_current()->get_photon_id())
							continue;

						bool is_toggled = false;
						{
							std::lock_guard guard(sniffer_mutex);
							is_toggled = logging_players.contains(viewid);
						}

						if (ImGui::Checkbox(player->get_api_user()->display_name().c_str(), &is_toggled))
						{
							is_toggled = !is_toggled;

							std::lock_guard guard(sniffer_mutex);
							if (is_toggled)
								logging_players.erase(viewid);
							else
								logging_players.insert(viewid);
						}
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip(xorstr_("select this player to sniff their packets"));
					}
				}

				ImGui::PopStyleVar();
				ImGui::EndChild();
			}

			ImGui::EndColumns();
		}

		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));
		ImGui::Separator();

		if (ImGui::Button(xorstr_("clear"), ImVec2(0.f, 17.f)))
			clear_logs();
		ImGui::SameLine();
		if (ImGui::Button(xorstr_("copy"), ImVec2(0.f, 17.f)))
			ImGui::LogToClipboard();

		ImGui::Separator();
		ImGui::PopStyleVar();

		ImGui::BeginChild(xorstr_("scrolling2"), ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar);
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

			const char* buf_start = buf.begin();
			const char* buf_end = buf.end();

			ImGuiListClipper clipper;

			if (line_offsets.Size > 2)
				clipper.Begin(line_offsets.Size - 1);
			else
				clipper.Begin(line_offsets.Size);

			while (clipper.Step())
			{
				for (std::int32_t line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
				{
					const char* line_start = buf_start + line_offsets[line_no];
					const char* line_end = line_no + 1 < line_offsets.Size ? buf_start + line_offsets[line_no + 1] - 1 : buf_end;
					ImGui::TextUnformatted(line_start, line_end);
				}
			}
			clipper.End();

			ImGui::PopStyleVar();
			ImGui::PopStyleVar();

			if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
				ImGui::SetScrollHereY(1.0f);

			ImGui::EndChild();
		}

		ImGui::End();
	}
}

void sniffer_window::print_log(const std::string_view fmt)
{
	int old_size = buf.size();

	std::lock_guard lock_guard(m_log_mutex);
	buf.append(fmt.data());

	for (const std::int32_t new_size = buf.size(); old_size < new_size; old_size++)
		if (buf[old_size] == '\n')
			line_offsets.push_back(old_size + 1);
}

void sniffer_window::clear_logs()
{
	std::lock_guard lock_guard(m_log_mutex);
	buf.clear();
	line_offsets.clear();
	line_offsets.push_back(0);
}
