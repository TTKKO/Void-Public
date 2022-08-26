#include "menu.hpp"

const std::pair<const char*, std::uint32_t> arr_colors[] =
{
	{"[visitor]", g_context.c_visitor},
	{"[new_user]", g_context.c_newuser},
	{"[user]", g_context.c_user},
	{"[known_user]", g_context.c_known},
	{"[trusted_user]", g_context.c_trusted},
	{"[friend]", g_context.c_friend}
};

void menu_window::main_window(const ImColor& rainbow)
{
	const ImGuiStyle& style = ImGui::GetStyle();
	const ImGuiIO& io = ImGui::GetIO();

	ImVec2 size(0.f, 0.f);

	if (config::get<bool>(g_context.rgb_elements))
		drawing::set_rgb_colors(dx11_hook::hue);

#pragma region watermark_and_stats
	if (config::get<bool>(g_context.watermark) || config::get<bool>(g_context.statistics))
	{
		ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(0.f, 0.f, 0.f, 0.03f));
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.f, 0.f, 0.f, 0.03f));

		// hmm, another one watermark
		ImDrawList* p_background_draw_list = ImGui::GetBackgroundDrawList();
		ImGui::BeginMainMenuBar();
		{
			ImGui::PushFont(byte_resources::verdana_small_bold);
			ImGui::Dummy(ImVec2(1, 1));

#pragma region watermark

			const ImVec4& c_highlight = config::get<bool>(g_context.rgb_elements) ? rainbow.Value : config::get<sdk::color>(g_context.color_accent0).get_vec4();
			if (config::get<bool>(g_context.watermark))
			{
				static const ImVec2 vec_name_size = ImGui::CalcTextSize(utility::format(xorstr_("void {} build {} | {} | {}"), stage, build, utility::get_date(), utility::get_time()).c_str());
				ImGui::SetCursorPosX(ImGui::GetContentRegionAvail().x - vec_name_size.x);

				ImGui::TextColored(c_highlight, xorstr_("void "));
				ImGui::SameLine(0.f, 0.f);
				ImGui::Text(stage);
				ImGui::SameLine(0.f, 0.f);
				ImGui::TextColored(c_highlight, xorstr_(" build "));
				ImGui::SameLine(0.f, 0.f);
				ImGui::Text(build);
				ImGui::SameLine(0.f, 0.f);
				ImGui::TextColored(c_highlight, xorstr_(" | "));
				ImGui::SameLine(0.f, 0.f);
				ImGui::Text(utility::get_date().c_str());
				ImGui::SameLine(0.f, 0.f);
				ImGui::TextColored(c_highlight, xorstr_(" | "));
				ImGui::SameLine(0.f, 0.f);
				ImGui::Text(utility::get_time().c_str());
			}
#pragma endregion

#pragma region statistics
			if (config::get<bool>(g_context.statistics))
			{
				ImGui::SameLine(10.f);

				ImGui::Text(utility::format(xorstr_("{:.3f}"), 1000.f / io.Framerate).c_str());
				ImGui::SameLine(0.f, 0.f);
				ImGui::TextColored(c_highlight, xorstr_("ms"));
				ImGui::SameLine(0.f, 0.f);
				ImGui::Text(xorstr_("/"));
				ImGui::SameLine(0.f, 0.f);
				ImGui::TextColored(c_highlight, xorstr_("frame ("));
				ImGui::SameLine(0.f, 0.f);
				ImGui::Text(std::to_string(static_cast<std::int32_t>(io.Framerate)).c_str());
				ImGui::SameLine(0.f, 0.f);
				ImGui::TextColored(c_highlight, xorstr_(" fps)"));

				ImGui::SameLine(0.f, 10.f);

				ImGui::Text(utility::format(xorstr_("{:.2f}"), static_cast<double>(memory::get_total_vmemory_used()) / 1073741824.0).c_str());
				ImGui::SameLine(0.f, 0.f);
				ImGui::TextColored(c_highlight, xorstr_("gb used"));
				ImGui::SameLine(0.f, 0.f);
				ImGui::Text(xorstr_(" ("));
				ImGui::SameLine(0.f, 0.f);
				ImGui::Text(utility::format(xorstr_("{:.2f}"), static_cast<double>(memory::get_total_vmemory_by_proc()) / 1073741824.0).c_str());
				ImGui::SameLine(0.f, 0.f);
				ImGui::TextColored(c_highlight, xorstr_("gb"));
				ImGui::SameLine(0.f, 0.f);
				ImGui::Text(xorstr_(" vrchat)"));

				if (const auto vrcplayer = assembler::vrc_player::get_current())
				{
					const auto pos = vrcplayer->get_transform()->get_position();
					ImGui::SameLine(0.f, 10.f);
					ImGui::TextColored(c_highlight, xorstr_("["));
					ImGui::SameLine(0.f, 0.f);
					ImGui::Text(utility::format(xorstr_("{:.2f}"), pos.x).c_str());
					ImGui::SameLine(0.f, 0.f);
					ImGui::TextColored(c_highlight, xorstr_(", "));
					ImGui::SameLine(0.f, 0.f);
					ImGui::Text(utility::format(xorstr_("{:.2f}"), pos.y).c_str());
					ImGui::SameLine(0.f, 0.f);
					ImGui::TextColored(c_highlight, xorstr_(", "));
					ImGui::SameLine(0.f, 0.f);
					ImGui::Text(utility::format(xorstr_("{:.2f}"), pos.z).c_str());
					ImGui::SameLine(0.f, 0.f);
					ImGui::TextColored(c_highlight, xorstr_("]"));
				}
			}
#pragma endregion

			ImGui::PopFont();
			size += ImGui::GetWindowSize();
			ImGui::EndMainMenuBar();
		}
		if (config::get<bool>(g_context.watermark))
			p_background_draw_list->AddImage(byte_resources::void_logo, { size.x + 2.f, size.y - 15.f }, { size.x + 2.f - 240.f, size.y - 15.f + 204.f });

		ImGui::PopStyleColor(2);
	}
#pragma endregion

#pragma region debug_log
	if (config::get<bool>(g_context.desktop_debug_log))
	{
		ImGui::SetNextWindowSize({ 490, 200 }, ImGuiCond_Appearing);
		ImGui::SetNextWindowPos({ 8.f, 2.f + size.y }, ImGuiCond_Appearing);

		ImGui::PushStyleColor(ImGuiCol_MenuBarBg, { 0.f, 0.f, 0.f, 0.03f });
		ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0.f, 0.f, 0.f, 0.03f });
		ImGui::Begin(xorstr_("void debug"), nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
		{
			ImGui::PushFont(byte_resources::verdana_small);

			logging::draw(rainbow, config::get<bool>(g_context.rgb_elements));

			ImGui::PopFont();
			ImGui::End();
		}
		ImGui::PopStyleColor(2);
	}
#pragma endregion

	if (tabs::playerlist_active)
		tabs::render_playerlist(io, style, rainbow);

#pragma region mainmenu
	if (mainmenu_opened)
	{
		ImGui::SetNextWindowPos({ io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f }, ImGuiCond_Once, { 0.5f, 0.5f });
		ImGui::SetNextWindowSize({ 500.f, 327.f }, ImGuiCond_Always);

		//ImGui::PushFont(byte_resources::whitney);
		const auto title = utility::format(xorstr_("void {} build {} | {}"), stage, build, msg);
		ImGui::Begin(title.c_str(), &mainmenu_opened, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
		{
			const ImVec2 vec_position = ImGui::GetCursorScreenPos();
			const float fl_window_width = ImGui::GetWindowWidth();
			ImDrawList* p_window_draw_list = ImGui::GetWindowDrawList();

			// push clip so separator will be drawn at maximal window bounds
			ImGui::PushClipRect(ImVec2(vec_position.x - 8.f, vec_position.y - 8.f), ImVec2(vec_position.x + fl_window_width - 8.f, vec_position.y - 6.f), false);

			if (ImGui::GetScrollY() == 0.f)
			{
				if (!config::get<bool>(g_context.rgb_elements))
				{
					p_window_draw_list->AddRectFilledMultiColor(ImVec2(vec_position.x - 8.f, vec_position.y - 6.f), ImVec2(vec_position.x + fl_window_width - fl_window_width / 3.f - 8.f, vec_position.y - 8.f), IM_COL32(112, 100, 214, 255), IM_COL32(107, 91, 163, 255), IM_COL32(107, 91, 163, 255), IM_COL32(112, 100, 214, 255));
					p_window_draw_list->AddRectFilledMultiColor(ImVec2(vec_position.x + fl_window_width - fl_window_width / 3.f - 8.f, vec_position.y - 6.f), ImVec2(vec_position.x + fl_window_width - 8.f, vec_position.y - 8.f), IM_COL32(107, 91, 163, 255), IM_COL32(112, 100, 214, 255), IM_COL32(112, 100, 214, 255), IM_COL32(107, 91, 163, 255));
				}
				else
				{
					p_window_draw_list->AddRectFilled(ImVec2(vec_position.x - 8.f, vec_position.y - 6.f), ImVec2(vec_position.x + fl_window_width - fl_window_width / 3.f - 8.f, vec_position.y - 8.f), rainbow);
					p_window_draw_list->AddRectFilled(ImVec2(vec_position.x + fl_window_width - fl_window_width / 3.f - 8.f, vec_position.y - 6.f), ImVec2(vec_position.x + fl_window_width - 8.f, vec_position.y - 8.f), rainbow);
				}
			}

			ImGui::PopClipRect();

			static auto players_identifier = xorstr("players");
			static auto safety_identifier = xorstr("safety");
			static auto misc_identifier = xorstr("miscellaneous");
			static auto utilities_identifier = xorstr("utilities");
			static auto games_identifier = xorstr("games");
#if LVM_TESTING == 1
			static auto lvm_identifier = xorstr("lvm");
#endif
			static auto config_identifier = xorstr("configuration");

			// add tabs
			static const std::array arr_tabs =
			{
				ctab{players_identifier.crypt_get(), &tabs::players},
				ctab{safety_identifier.crypt_get(), &tabs::safety},
				ctab{misc_identifier.crypt_get(), &tabs::misc},
				ctab{utilities_identifier.crypt_get(), &tabs::utilities},
				ctab{games_identifier.crypt_get(), &tabs::games},
#if LVM_TESTING == 1
				ctab{lvm_identifier.crypt_get(), &tabs::lvm_tab},
#endif
				ctab{config_identifier.crypt_get(), &tabs::configuration}
			};
			tabs::render<arr_tabs.size()>(xorstr_("main_tabs"), arr_tabs, &i_main_tab, ImGuiTabBarFlags_NoCloseWithMiddleMouseButton | ImGuiTabBarFlags_FittingPolicyMask_);

			ImGui::End();
		}

#if TEST == 1
		if (dumper_window::opened)
			dumper_window::render_window();
#endif
		if (sniffer_window::opened)
			sniffer_window::render_window(tabs::v_players);

		//ImGui::PopFont();
	}
#pragma endregion
}

#pragma region menu_tabs
template <std::size_t S>
void tabs::render(const char* sz_tab_bar, const std::array<ctab, S>& arr_tabs, int* n_current_tab, const ImGuiTabBarFlags flags)
{
	// is empty check
	if (arr_tabs.empty())
		return;

	if (ImGui::BeginTabBar(sz_tab_bar, flags))
	{
		for (std::size_t i = 0U; i < arr_tabs.size(); i++)
		{
			// add tab
			if (ImGui::BeginTabItem(arr_tabs.at(i).sz_name))
			{
				// set current tab index
				*n_current_tab = static_cast<std::int32_t>(i);
				ImGui::EndTabItem();
			}
		}

		// render inner tab
		if (arr_tabs.at(*n_current_tab).p_render_function != nullptr)
			arr_tabs.at(*n_current_tab).p_render_function();

		ImGui::EndTabBar();
	}
}
#pragma endregion

#pragma region tab_rendering
void tabs::render_playerlist(const ImGuiIO& io, const ImGuiStyle& style, const ImColor& rainbow)
{
	ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x / 3.5f, io.DisplaySize.y / 2.2f), ImGuiCond_Always);
	ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(0.f, 0.f, 0.f, 0.03f));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.f, 0.f, 0.f, 0.03f));
	ImGui::Begin(xorstr_("void playerlist"), &playerlist_active, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
	{
		static float playerlist_height = 0.f;
		ImGui::BeginChild(xorstr_("playerlist"), ImVec2(-1.f, playerlist_height));
		{
			const ImVec4& c_highlight = config::get<bool>(g_context.rgb_elements) ? rainbow.Value : config::get<sdk::color>(g_context.color_accent0).get_vec4();

			ImGui::PushFont(byte_resources::verdana_big);
			const auto window_width = ImGui::GetWindowSize().x;
			const auto text_width = ImGui::CalcTextSize(utility::format("void playerlist - [{:d}]", v_players.size()).c_str()).x;
			ImGui::Spacing();
			ImGui::SetCursorPosX((window_width - text_width) * 0.5f);
			ImGui::TextColored(c_highlight, xorstr_("void "));
			ImGui::SameLine(0.f, 0.f);
			ImGui::Text(xorstr_("playerlist"));
			ImGui::SameLine(0.f, 0.f);
			ImGui::TextColored(c_highlight, xorstr_(" - ["));
			ImGui::SameLine(0.f, 0.f);
			ImGui::Text(utility::format(xorstr_("{:d}"), v_players.size()).c_str());
			ImGui::SameLine(0.f, 0.f);
			ImGui::TextColored(c_highlight, xorstr_("] "));
			ImGui::Spacing();
			ImGui::PopFont();

			playerlist_height = ImGui::GetCursorPosY() + style.ItemSpacing.y;

			ImGui::EndChild();
		}

		ImGui::Spacing();

		ImGui::BeginChild(xorstr_("playerlist children"));
		{
			if (g_context.instantiated)
			{
				const ImVec4& c_highlight = config::get<bool>(g_context.rgb_elements) ? rainbow.Value : config::get<sdk::color>(g_context.color_accent0).get_vec4();
				ImGui::PushFont(byte_resources::verdana_medium_bold);
				ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(style.Colors[ImGuiCol_SeparatorActive].x, style.Colors[ImGuiCol_SeparatorActive].y, style.Colors[ImGuiCol_SeparatorActive].z, 0.3f));

				for (std::size_t i = 0; i < v_players.size(); ++i)
				{
					const auto apiuser = v_players[i]->get_api_user();
					const auto vrcplayerapi = v_players[i]->get_vrc_player_api();
					const auto vrcplayer = v_players[i]->get_vrc_player();

					if (!i)
						ImGui::Spacing();

					ImGui::Spacing();

					ImGui::Columns(2);
					{
						ImGui::TextColored(c_highlight, xorstr_("["));
						ImGui::SameLine(0.f, 0.f);
						ImGui::Text(utility::format(xorstr_("{:d}"), v_players[i]->get_photon_id()).c_str());
						ImGui::SameLine(0.f, 0.f);
						ImGui::TextColored(c_highlight, xorstr_("] "));
						ImGui::SameLine(0.f, 0.f);

						if (vrcplayerapi->get_is_master())
						{
							ImGui::TextColored(c_highlight, xorstr_("["));
							ImGui::SameLine(0.f, 0.f);
							ImGui::Text(xorstr_("M"));
							ImGui::SameLine(0.f, 0.f);
							ImGui::TextColored(c_highlight, xorstr_("] "));
							ImGui::SameLine(0.f, 0.f);
						}

						ImGui::TextColored(c_highlight, xorstr_("["));
						ImGui::SameLine(0.f, 0.f);
						ImGui::Text(vrcplayerapi->is_vr() ? apiuser->get_is_on_mobile() ? xorstr_("QST") : xorstr_("PCVR") : xorstr_("PC"));
						ImGui::SameLine(0.f, 0.f);
						ImGui::TextColored(c_highlight, xorstr_("] "));
						ImGui::SameLine(0.f, 0.f);
						ImGui::TextColored(nameplate_manager::is_client_user(apiuser->get_id()) ? rainbow.Value : misc::get_user_rank_color(apiuser).get_vec4(), apiuser->display_name().c_str());
					}
					ImGui::NextColumn();
					{
						ImGui::Text(utility::format(xorstr_("{:d}"), vrcplayer->get_ping()).c_str());
						ImGui::SameLine(0.f, 0.f);
						ImGui::TextColored(c_highlight, xorstr_("ms"));
						ImGui::SameLine(0.f, 0.f);
						ImGui::TextColored(c_highlight, xorstr_(" : "));
						ImGui::SameLine(0.f, 0.f);
						ImGui::Text(utility::format(xorstr_("{:d}"), vrcplayer->get_fps()).c_str());
						ImGui::SameLine(0.f, 0.f);
						ImGui::TextColored(c_highlight, xorstr_("fps"));
					}

					ImGui::Columns(1);
					ImGui::Spacing();
					ImGui::Separator();
				}

				ImGui::PopFont();
				ImGui::PopStyleColor();
			}
			ImGui::EndChild();
		}


		ImGui::End();
	}
	ImGui::PopStyleColor(2);
}

void tabs::misc()
{
	const ImGuiStyle& style = ImGui::GetStyle();
	ImGui::Spacing();
	ImGui::Columns(2, nullptr, false);
	{
		ImGui::BeginChild(xorstr_("spoof.1"), ImVec2(0, 120), true, ImGuiWindowFlags_MenuBar);
		{
			if (ImGui::BeginMenuBar())
			{
				ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0.5f, 0.5f));
				ImGui::Selectable(xorstr_("spoof##master"), true, ImGuiSelectableFlags_None, ImVec2(50, 0));
				ImGui::PopStyleVar();
				ImGui::EndMenuBar();
			}

			static auto ping_identifier = xorstr("ping");
			static auto fps_identifier = xorstr("fps");
			static auto hwid_identifier = xorstr("hwid");
			static auto offline_identifier = xorstr("offline");
			static auto udonname_identifier = xorstr("udoname");

			static const std::array arr_esp_tabs =
			{
				ctab{
					ping_identifier.crypt_get(), [&style]
					{
						ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));

						ImGui::Checkbox(xorstr_("enabled"), &config::get<bool>(g_context.fake_ping));
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip(xorstr_("toggle ping spoof."));
						ImGui::InputInt(xorstr_("value"), &config::get<int>(g_context.fake_ping_i));
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip(xorstr_("value that you want your spoofed ping to appear as."));
						ImGui::SliderInt(xorstr_("range"), &config::get<int>(g_context.fake_ping_range), 0, 400);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip(
								xorstr_("use this if you want your spoofed ping to look 'legit'. 0 is none."));

						ImGui::PopStyleVar();
					}
				},
				ctab{
					fps_identifier.crypt_get(), [&style]
					{
						ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));

						ImGui::Checkbox(xorstr_("enabled"), &config::get<bool>(g_context.fake_fps));
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip(xorstr_("toggle fps spoof."));
						ImGui::InputInt(xorstr_("value"), &config::get<int>(g_context.fake_fps_i));
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip(xorstr_("value that you want your spoofed fps to appear as."));
						ImGui::SliderInt(xorstr_("range"), &config::get<int>(g_context.fake_fps_range), 0, 1000);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip(xorstr_("use this if you want your spoofed fps to look 'legit'. 0 is none."));

						ImGui::PopStyleVar();
					}
				},
				ctab{
					hwid_identifier.crypt_get(), [&style]
					{
						ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));

						ImGui::Checkbox(xorstr_("enabled"), &config::get<bool>(g_context.fake_hwid));
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip(xorstr_("toggles hwid spoof. restart with autoloading to take effect. make sure you save your config."));
						if (ImGui::Button(xorstr_("regenerate"), ImVec2(-1, 17)))
							config::get<std::string>(g_context.set_hwid) = misc::get_device_id();
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip(xorstr_("regenerates your hwid for this config. make sure you save afterwards."));

						ImGui::PopStyleVar();
					}
				},
				ctab{
					offline_identifier.crypt_get(), [&style]
					{
						ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));

						ImGui::Checkbox(xorstr_("enabled"), &config::get<bool>(g_context.fake_offline));
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip(xorstr_("toggle offline spoof. this is known to get you banned."));

						ImGui::PopStyleVar();
					}
				},
				ctab{
					udonname_identifier.crypt_get(), [&style]
					{
						ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));

						ImGui::Checkbox(xorstr_("enabled"), &config::get<bool>(g_context.udon_namespoof));
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip(xorstr_("spoofs your udon name to the provided text."));

						ImGui::Spacing();

						ImGui::Checkbox(xorstr_("patreon mode"), &config::get<bool>(g_context.udon_namespoof_patreon));
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip(xorstr_("spoofs your udon name automatically to a world's patreon member."));

						if (!config::get<bool>(g_context.udon_namespoof_patreon))
						{
							ImGui::InputText(xorstr_("name"), &config::get<std::string>(g_context.udon_namespoof_name));
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip(xorstr_("whatever name you would like to spoof as."));
						}

						ImGui::PopStyleVar();
					}
				}
			};

			tabs::render<arr_esp_tabs.size()>(xorstr_("spoof_1"), arr_esp_tabs, &i_spoof_tab);
			ImGui::EndChild();
		}

		static float exploits_size = 0.f;
		ImGui::BeginChild(xorstr_("exploits.2"), ImVec2(0, exploits_size), true, ImGuiWindowFlags_MenuBar);
		{
			if (ImGui::BeginMenuBar())
			{
				ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0.5f, 0.5f));
				ImGui::Selectable(xorstr_("exploits##master"), true, ImGuiSelectableFlags_None, ImVec2(50, 0));
				ImGui::PopStyleVar();
				ImGui::EndMenuBar();
			}

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));

			if (ImGui::Checkbox(xorstr_("deserialize movement"), &config::get<bool>(g_context.serialize)))
				misc::handle_avatar_clone(config::get<bool>(g_context.serialize));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("disables movement while enabled."));
			ImGui::Checkbox(xorstr_("invisible join"), &config::get<bool>(g_context.invisible_join));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("join lobbies undetected."));
			ImGui::Checkbox(xorstr_("instance lock"), &config::get<bool>(g_context.instance_lock));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("locks the instance as master using an exploit."));
			ImGui::Checkbox(xorstr_("e1 distortion"), &config::get<bool>(g_context.exploit_event_1));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("void on top"));
			ImGui::Checkbox(xorstr_("anti-attach (infinite pos)"), &g_context.anti_aim);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("spoofs your photon position to break users cameras if they are attached to you"));
#if TEST == 1
			ImGui::Checkbox(xorstr_("e7 interpolation"), &config::get<bool>(g_context.event_7_test));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("void on top"));
#endif
			//ImGui::Checkbox(xorstr_("e6 malformation"), &config::get<bool>(g_context.exploit_event_6));
			//if (ImGui::IsItemHovered())
			//	ImGui::SetTooltip(xorstr_("void on top"));

			ImGui::PopStyleVar();
			exploits_size = ImGui::GetCursorPosY() + style.ItemSpacing.y;
			ImGui::EndChild();
		}

		static float util_size = 0.f;
		ImGui::BeginChild(xorstr_("util.3"), ImVec2(0, util_size), true, ImGuiWindowFlags_MenuBar);
		{
			if (ImGui::BeginMenuBar())
			{
				ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0.5f, 0.5f));
				ImGui::Selectable(xorstr_("util##master"), true, ImGuiSelectableFlags_None, ImVec2(50, 0));
				ImGui::PopStyleVar();
				ImGui::EndMenuBar();
			}

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));

			if (ImGui::Checkbox(xorstr_("flight"), &config::get<bool>(g_context.flight)))
				misc::toggle_flight(config::get<bool>(g_context.flight));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("toggles flight and noclip."));
			ImGui::SliderFloat(xorstr_("speed##FLIGHTSPEED"), &config::get<float>(g_context.flight_speed), 2.f, 20.f);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("sets your flight speed to given value."));
			if (ImGui::Checkbox(xorstr_("thirdperson"), &g_context.third_person))
			{
				if (g_context.third_person)
					helpers::camera::get().toggle(static_cast<helpers::camera::mode>(config::get<int>(g_context.thirdperson_mode)));
				else
					helpers::camera::get().toggle(helpers::camera::mode::off);
			}
			if (g_context.third_person)
				if (ImGui::Combo(xorstr_("mode"), &config::get<int>(g_context.thirdperson_mode), xorstr_("none\0back\0front")))
					helpers::camera::get().toggle(static_cast<helpers::camera::mode>(config::get<int>(g_context.thirdperson_mode)));
			ImGui::Checkbox(xorstr_("click teleport"), &config::get<bool>(g_context.click_teleport));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("when enabled, hold ctrl+click to teleport where your camera is aimed"));
			ImGui::Checkbox(xorstr_("avatar rotation"), &config::get<bool>(g_context.rotate_avatar));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("use '1' or '3' on your keyboard to rotate your avatar."));

			if (ImGui::Checkbox(xorstr_("target fps"), &config::get<bool>(g_context.fps_target)))
				assembler::unity_engine::application::set_target_frame_rate(config::get<int>(g_context.fps_target_i));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("changes vrchat's target framerate. allows you to target more than 90 fps."));
			if (ImGui::SliderInt(xorstr_("value##TARGETFPS"), &config::get<int>(g_context.fps_target_i), 30, 360))
			{
				if (config::get<bool>(g_context.fps_target))
					assembler::unity_engine::application::set_target_frame_rate(config::get<int>(g_context.fps_target_i));
				else
					assembler::unity_engine::application::set_target_frame_rate(90);
			}
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("sets your framerate to the given value."));

			ImGui::PopStyleVar();
			util_size = ImGui::GetCursorPosY() + style.ItemSpacing.y;
			ImGui::EndChild();
		}

		ImGui::NextColumn();

		static float safety_settings_size3 = 0.f;
		ImGui::BeginChild(xorstr_("malicious.4"), ImVec2(0, safety_settings_size3), true, ImGuiWindowFlags_MenuBar);
		{
			if (ImGui::BeginMenuBar())
			{
				ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0.5f, 0.5f));
				ImGui::Selectable(xorstr_("malicious##master"), true, ImGuiSelectableFlags_None, ImVec2(50, 0));
				ImGui::PopStyleVar();
				ImGui::EndMenuBar();
			}

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));

			if (ImGui::Checkbox(xorstr_("game closer"), &config::get<bool>(g_context.collision_crash)))
			{
				if (config::get<bool>(g_context.quest_crash) || config::get<bool>(g_context.corrupt_asset_crash) || config::get<bool>(g_context.audio_crash))
					config::get<bool>(g_context.collision_crash) = false;

				else if (config::get<bool>(g_context.collision_crash))
					g_context.changing_avatar = g_context.g_avatars[0];
				else
					g_context.changing_avatar = xorstr_("avtr_c4961195-1980-4a98-bb95-3cbe0e063463"); //alien avatar
			}
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("closes pc user's games."));
			if (ImGui::Checkbox(xorstr_("quest crash"), &config::get<bool>(g_context.quest_crash)))
			{
				if (config::get<bool>(g_context.collision_crash) || config::get<bool>(g_context.corrupt_asset_crash) || config::get<bool>(g_context.audio_crash))
					config::get<bool>(g_context.quest_crash) = false;

				else if (config::get<bool>(g_context.quest_crash))
					g_context.changing_avatar = g_context.g_avatars[2];
				else
					g_context.changing_avatar = xorstr_("avtr_c4961195-1980-4a98-bb95-3cbe0e063463"); //alien avatar
			}
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("crashes quest users."));
			if (ImGui::Checkbox(xorstr_("corrupted asset crash"), &config::get<bool>(g_context.corrupt_asset_crash)))
			{
				if (config::get<bool>(g_context.quest_crash) || config::get<bool>(g_context.collision_crash) || config::get<bool>(g_context.audio_crash))
					config::get<bool>(g_context.corrupt_asset_crash) = false;

				else if (config::get<bool>(g_context.corrupt_asset_crash))
					g_context.changing_avatar = g_context.g_avatars[3];
				else
					g_context.changing_avatar = xorstr_("avtr_c4961195-1980-4a98-bb95-3cbe0e063463"); //alien avatar
			}
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("crashes pc users, hits more clients."));
			if (ImGui::Checkbox(xorstr_("shader crash"), &config::get<bool>(g_context.audio_crash)))
			{
				if (config::get<bool>(g_context.quest_crash) || config::get<bool>(g_context.collision_crash) || config::get<bool>(g_context.corrupt_asset_crash))
					config::get<bool>(g_context.audio_crash) = false;

				else if (config::get<bool>(g_context.audio_crash))
					g_context.changing_avatar = g_context.g_avatars[1];
				else
					g_context.changing_avatar = xorstr_("avtr_c4961195-1980-4a98-bb95-3cbe0e063463"); //alien avatar
			}
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("crashes pc users, hits more clients."));
			if (ImGui::Checkbox(xorstr_("high decibel mic"), &config::get<bool>(g_context.high_db)))
			{
				if (config::get<bool>(g_context.high_db))
					assembler::vrc_player::get_current()->get_uspeaker()->set_remotegain(std::numeric_limits<float>::max());
				else assembler::vrc_player::get_current()->get_uspeaker()->set_remotegain(1.f);
			}
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("cancer..."));

			ImGui::Checkbox(xorstr_("emoji spam"), &config::get<bool>(g_context.emoji_spam));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("spams the specified emoji"));
			if (config::get<bool>(g_context.emoji_spam))
				ImGui::Combo(xorstr_("emoji"), &config::get<int>(g_context.emoji_to_spam), xorstr_("none\0angry\0flushed\0crying\0frown\0wave\0brah\0heart_eyes\0pumpkin\0kiss\0laughing\0skull\0smile\0ghost\0neutral\0cool\0think\0thumbs_down\0thumbs_up\0silly\0mouth_open\0bat\0cloud\0flames\0snowflake\0snowball\0splash\0cobweb\0beer\0candy\0candycane\0candycorn\0cheers\0coconut\0gingebread\0icecream\0pineapple\0pizza\0tomato\0beach_ball\0coal\0party\0gift\0presents\0safety_tube\0mistletoe\0money\0sunscreen\0cheap_glasses\0boo\0broken_heart\0alert\0go\0heart\0music\0question_mark\0no_entry\0zzz"));

			ImGui::PopStyleVar();
			safety_settings_size3 = ImGui::GetCursorPosY() + style.ItemSpacing.y;
			ImGui::EndChild();
		}

		static float safety_settings_size4 = 0.f;
		ImGui::BeginChild(xorstr_("render.5"), ImVec2(0, safety_settings_size4), true, ImGuiWindowFlags_MenuBar);
		{
			if (ImGui::BeginMenuBar())
			{
				ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0.5f, 0.5f));
				ImGui::Selectable(xorstr_("render##master"), true, ImGuiSelectableFlags_None, ImVec2(50, 0));
				ImGui::PopStyleVar();
				ImGui::EndMenuBar();
			}

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));

			ImGui::Checkbox(xorstr_("nametags"), &config::get<bool>(g_context.nametags));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("allows you to see names through walls."));
			if (ImGui::Checkbox(xorstr_("chams"), &config::get<bool>(g_context.chams)))
				nameplate_manager::fix_mirrormasks(config::get<bool>(g_context.chams));

			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("allows you to see avatars through walls."));
			ImGui::Checkbox(xorstr_("capsule esp"), &config::get<bool>(g_context.esp));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("allows you to see capsules through walls."));
			ImGui::Checkbox(xorstr_("directx esp"), &config::get<bool>(g_context.dx11_esp));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("internal esp rendered by void without any vrc interaction."));
			ImGui::Checkbox(xorstr_("directx tracers"), &config::get<bool>(g_context.dx11_tracers));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("internal tracers rendered by void without any vrc interaction."));

			ImGui::PopStyleVar();
			safety_settings_size4 = ImGui::GetCursorPosY() + style.ItemSpacing.y;
			ImGui::EndChild();
		}

		static float keybinds_size = 0.f;
		ImGui::BeginChild(xorstr_("binds.6"), ImVec2(0, keybinds_size), true, ImGuiWindowFlags_MenuBar);
		{
			if (ImGui::BeginMenuBar())
			{
				ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0.5f, 0.5f));
				ImGui::Selectable(xorstr_("binds##master"), true, ImGuiSelectableFlags_None, ImVec2(50, 0));
				ImGui::PopStyleVar();
				ImGui::EndMenuBar();
			}

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));

			ImGui::HotKey(xorstr_("flight bind"), &config::get<int>(g_context.flight_key));
			ImGui::HotKey(xorstr_("esp bind"), &config::get<int>(g_context.esp_key));
			ImGui::HotKey(xorstr_("deserialize bind"), &config::get<int>(g_context.deserialize_key));
			ImGui::HotKey(xorstr_("thirdperson bind"), &config::get<int>(g_context.thirdperson_key));

			ImGui::PopStyleVar();
			keybinds_size = ImGui::GetCursorPosY() + style.ItemSpacing.y;
			ImGui::EndChild();
		}
	}

	ImGui::Columns(1);
}

void tabs::safety()
{
	const ImGuiStyle& style = ImGui::GetStyle();
	ImGui::Spacing();
	ImGui::Columns(2, nullptr, false);
	{
		static float safety_settings_size = 0.f;

		ImGui::BeginChild(xorstr_("avatar.1"), ImVec2(0, safety_settings_size), true, ImGuiWindowFlags_MenuBar);
		{
			if (ImGui::BeginMenuBar())
			{
				ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0.5f, 0.5f));
				ImGui::Selectable(xorstr_("avatar##master"), true, ImGuiSelectableFlags_None, ImVec2(50, 0));
				ImGui::PopStyleVar();
				ImGui::EndMenuBar();
			}

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));

			ImGui::Checkbox(
				xorstr_("anti-blacklisted avatars"), &config::get<bool>(g_context.anti_blacklisted_avatars));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("toggles void's avatar blacklist."));
			ImGui::Checkbox(xorstr_("anti-avatar crash"), &config::get<bool>(g_context.anti_avatar_crash));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("attempts to prevent avatar crashes."));
			ImGui::Checkbox(xorstr_("anti-avatar audio"), &config::get<bool>(g_context.anti_avatar_audio));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("blocks avatars containing audio."));
			ImGui::Checkbox(xorstr_("anti-audio crash"), &config::get<bool>(g_context.anti_audio_crash));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("prevents audio crashes."));
			if (ImGui::Checkbox(xorstr_("block downloads"), &g_context.block_downloads))
				misc::toggle_download_manager(!g_context.block_downloads);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("blocks vrchat's download manager temporarily."));
			ImGui::Checkbox(xorstr_("allow friends"), &config::get<bool>(g_context.allow_friends));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("allow friends to bypass antis."));

			ImGui::PopStyleVar();
			safety_settings_size = ImGui::GetCursorPosY() + style.ItemSpacing.y;
			ImGui::EndChild();
		}

		static float safety_settings_size2 = 0.f;
		ImGui::BeginChild(xorstr_("photon.2"), ImVec2(0, safety_settings_size2), true, ImGuiWindowFlags_MenuBar);
		{
			if (ImGui::BeginMenuBar())
			{
				ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0.5f, 0.5f));
				ImGui::Selectable(xorstr_("photon##master"), true, ImGuiSelectableFlags_None, ImVec2(50, 0));
				ImGui::PopStyleVar();
				ImGui::EndMenuBar();
			}

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));

			ImGui::Checkbox(xorstr_("reduce bad activity"), &config::get<bool>(g_context.reduce_bad_activity));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("prevents users sending possibly mallicious events."));
			ImGui::Checkbox(xorstr_("anti-uspeak exploit"), &config::get<bool>(g_context.anti_uspeak_exploit));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("prevents users sending malicious uspeak packets."));
			ImGui::Checkbox(xorstr_("anti-object spam"), &config::get<bool>(g_context.anti_object_spam));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("pickups become local."));
			ImGui::Checkbox(xorstr_("anti-block"), &config::get<bool>(g_context.anti_block));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("displays users who have blocked you."));
			ImGui::Checkbox(xorstr_("anti-master dc"), &config::get<bool>(g_context.anti_master_dc));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("prevents disconnection as master."));
			ImGui::Checkbox(xorstr_("anti-instance lock"), &config::get<bool>(g_context.anti_instance_lock));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("prevents the instance lock exploit locally."));
			ImGui::Checkbox(xorstr_("detect invisibles"), &config::get<bool>(g_context.detect_invisibles));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("detects invisible players. Must be enabled before joining a lobby."));

			ImGui::PopStyleVar();
			safety_settings_size2 = ImGui::GetCursorPosY() + style.ItemSpacing.y;
			ImGui::EndChild();
		}

		ImGui::NextColumn();

		static float safety_settings_size3 = 0.f;
		ImGui::BeginChild(xorstr_("world.3"), ImVec2(0, safety_settings_size3), true, ImGuiWindowFlags_MenuBar);
		{
			if (ImGui::BeginMenuBar())
			{
				ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0.5f, 0.5f));
				ImGui::Selectable(xorstr_("world##master"), true, ImGuiSelectableFlags_None, ImVec2(50, 0));
				ImGui::PopStyleVar();
				ImGui::EndMenuBar();
			}

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));

			ImGui::Checkbox(xorstr_("anti-portal"), &config::get<bool>(g_context.anti_portal));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("removes portal colliders."));
			ImGui::Checkbox(xorstr_("anti-world triggers"), &config::get<bool>(g_context.anti_worldtriggers));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("blocks all world triggers."));
			ImGui::Checkbox(xorstr_("anti-udon events"), &config::get<bool>(g_context.anti_udon_events));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("blocks all udon events."));
			ImGui::Checkbox(xorstr_("anti-video url"), &config::get<bool>(g_context.anti_video_exploit));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("prevents users from playing videos from unknown sources."));
			ImGui::Checkbox(xorstr_("streamer mode"), &config::get<bool>(g_context.anti_stream));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("hides your name and \"stealthifies\" void's vr menu (on load only! save & restart for this to take effect)"));
			ImGui::Checkbox(xorstr_("prevent portals"), &config::get<bool>(g_context.prevent_portals));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("Automatically destroys spawned portals."));

			ImGui::PopStyleVar();
			safety_settings_size3 = ImGui::GetCursorPosY() + style.ItemSpacing.y;
			ImGui::EndChild();
		}

		static float options_size = 0.f;
		ImGui::BeginChild(xorstr_("assetbundles.4"), ImVec2(0, options_size), true, ImGuiWindowFlags_MenuBar);
		{
			if (ImGui::BeginMenuBar())
			{
				ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0.5f, 0.5f));
				ImGui::Selectable(xorstr_("bad bundles##master"), true, ImGuiSelectableFlags_None, ImVec2(70, 0));
				ImGui::PopStyleVar();
				ImGui::EndMenuBar();
			}

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));

			ImGui::Checkbox(xorstr_("anti-oob"), &config::get<bool>(g_context.anti_oob));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("anti's majority of corrupted asset bundles. explained vague for secrecy."));
			ImGui::Checkbox(xorstr_("anti-node overflow"), &config::get<bool>(g_context.anti_aa12));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("anti's aa12 and similar avis. explained vague for secrecy."));
			ImGui::Checkbox(xorstr_("anti-array overflow"), &config::get<bool>(g_context.anti_array_overflow));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(
					xorstr_("prevents a stackoverflow when a bad bundle gets loaded into memory. keep this on."));
			ImGui::Checkbox(xorstr_("anti-ro.nulls"), &config::get<bool>(g_context.anti_ro_nulls));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(
					xorstr_("anti's corrupted asset bundles and similar avis. explained vague for secrecy."));
			ImGui::Checkbox(xorstr_("anti-audio mixers"), &config::get<bool>(g_context.anti_audio_mixers));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("anti's malicious audio mixers on avatars. keep this on."));

			ImGui::PopStyleVar();
			options_size = ImGui::GetCursorPosY() + style.ItemSpacing.y;
			ImGui::EndChild();
		}
	}

	ImGui::Columns(1);
}

void tabs::utilities()
{
	const ImGuiStyle& style = ImGui::GetStyle();
	ImGui::Spacing();

	ImGui::Columns(2, nullptr, false);
	{
		ImGui::BeginChild(xorstr_("utilities.1"), ImVec2(), true, ImGuiWindowFlags_MenuBar);
		{
			if (ImGui::BeginMenuBar())
			{
				ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0.5f, 0.5f));
				ImGui::Selectable(xorstr_("utilities##master"), true, ImGuiSelectableFlags_None, ImVec2(50, 0));
				ImGui::PopStyleVar();
				ImGui::EndMenuBar();
			}

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));

			if (ImGui::Button(xorstr_("copy world id"), ImVec2(-1, 17)))
				utility::set_clipboard(assembler::room_manager::get_room_id());
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("copies your current world id to your clipboard."));
			if (ImGui::Button(xorstr_("join copied world id"), ImVec2(-1, 17)))
				g_context.room_id = utility::get_clipboard();
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("joins your copied world id."));
			if (ImGui::Button(xorstr_("force stop copying uspeak"), ImVec2(-1, 17)))
				config::get<int>(g_context.copy_event1) = NULL;
			if (ImGui::Button(xorstr_("clone copied avatar id"), ImVec2(-1, 17)))
			{
				if (const auto clipboard = utility::get_clipboard(); !clipboard.starts_with(xorstr_("avtr_")))
				{
					logging::push(FOREGROUND_INTENSE_RED);
					logging::add_log(xorstr_("[warn] not a valid avatar id\n"));
					logging::pop();
				}
				else g_context.changing_avatar = clipboard;
			}

			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("changes your avatar to the avatar id on your clipboard."));
			if (ImGui::Button(xorstr_("blacklist copied avatar id"), ImVec2(-1, 17)))
			{
				if (const auto clipboard = utility::get_clipboard(); !clipboard.starts_with(xorstr_("avtr_")))
				{
					logging::push(FOREGROUND_INTENSE_RED);
					logging::add_log(xorstr_("[warn] not a valid avatar id\n"));
					logging::pop();
				}
				else
				{
					const auto wl_v = &config::get<std::vector<std::string>>(g_context.avatar_whitelist);
					if (const auto wl_position = std::ranges::find(*wl_v, clipboard); wl_position != wl_v->end())
						wl_v->erase(wl_position);

					const auto bl_v = &config::get<std::vector<std::string>>(g_context.avatar_blacklist);
					if (const auto bl_position = std::ranges::find(*bl_v, clipboard); bl_position == bl_v->end())
					{
						logging::push(FOREGROUND_INTENSE_CYAN);
						logging::add_log(xorstr_("[log] blacklisted [{}]\n"), clipboard);
						logging::pop();
						bl_v->push_back(clipboard);
					}
					else
					{
						logging::push(FOREGROUND_INTENSE_CYAN);
						logging::add_log(xorstr_("[log] unblacklisted [{}]\n"), clipboard);
						logging::pop();
						bl_v->erase(bl_position);
					}

					if (g_context.instantiated)
					{
						misc::remove_avatar_from_cache(clipboard);
						assembler::vrc_player::get_current()->load_all_avatars();
					}
				}
			}
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("(un)blacklists the avatar id on your clipboard."));

			if (ImGui::Button(xorstr_("whitelist copied avatar id"), ImVec2(-1, 17)))
			{
				if (const auto clipboard = utility::get_clipboard(); !clipboard.starts_with(xorstr_("avtr_")))
				{
					logging::push(FOREGROUND_INTENSE_RED);
					logging::add_log(xorstr_("[warn] not a valid avatar id\n"));
					logging::pop();
				}
				else
				{
					const auto bl_v = &config::get<std::vector<std::string>>(g_context.avatar_blacklist);
					if (const auto bl_position = std::ranges::find(*bl_v, clipboard); bl_position != bl_v->end())
						bl_v->erase(bl_position);

					const auto wl_v = &config::get<std::vector<std::string>>(g_context.avatar_whitelist);
					if (const auto wl_position = std::ranges::find(*wl_v, clipboard); wl_position == wl_v->end())
					{
						logging::push(FOREGROUND_INTENSE_CYAN);
						logging::add_log(xorstr_("[log] whitelisted [{}]\n"), clipboard);
						logging::pop();
						wl_v->push_back(clipboard);
					}
					else
					{
						logging::push(FOREGROUND_INTENSE_CYAN);
						logging::add_log(xorstr_("[log] unwhitelisted [{}]\n"), clipboard);
						logging::pop();
						wl_v->erase(wl_position);
					}

					if (g_context.instantiated)
					{
						misc::remove_avatar_from_cache(clipboard);
						assembler::vrc_player::get_current()->load_all_avatars();
					}
				}
			}
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("(un)whitelist the avatar id on your clipboard."));

			if (ImGui::Button(xorstr_("export friends"), ImVec2(-1, 17)))
			{
				if (!helpers::friend_tool::export_friends(assembler::il2cpp::array_to_vector<assembler::il2cpp::il2cpp_string*>(assembler::vrc::core::api_user::get_friends())))
				{
					logging::push(FOREGROUND_INTENSE_RED);
					logging::add_log(xorstr_("[critical] failed to export friends.\n"));
					logging::pop();
					ingame_logging::get().log(xorstr_("[<color=#a668f8>critical</color>] failed to export friends."));
				}
				else
				{
					logging::push(FOREGROUND_INTENSE_WHITE);
					logging::add_log(xorstr_("[notice] exported friends to %appdata%\\Void\\exports.\n"));
					logging::pop();
					ingame_logging::get().log(xorstr_(R"([<color=#a668f8>notice</color>] exported friends to %appdata%\Void\exports.)"));
				}
			}
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("exports friend list to be imported on another account in the future."));

			if (ImGui::Button(xorstr_("import friends"), ImVec2(-1, 17)))
			{
				if (!helpers::friend_tool::get().import_friends())
				{
					logging::push(FOREGROUND_INTENSE_RED);
					logging::add_log(xorstr_("[critical] failed to import friends.\n"));
					logging::pop();
					ingame_logging::get().log(xorstr_("[<color=#a668f8>critical</color>] failed to import friends."));
				}
				else
				{
					if (!helpers::friend_tool::get().start_load_task())
					{
						logging::push(FOREGROUND_INTENSE_RED);
						logging::add_log(xorstr_("[notice] the import system is already running.\n"));
						logging::pop();
						ingame_logging::get().log(xorstr_("[<color=#a668f8>notice</color>] the import system is already running."));
					}
					else
					{
						logging::push(FOREGROUND_INTENSE_WHITE);
						logging::add_log(xorstr_("[notice] import started at a rate of 60/hour\n"));
						logging::pop();
						ingame_logging::get().log(xorstr_("[<color=#a668f8>notice</color>] import started at a rate of 60/hour"));

						if (!xs_overlay::get().send(xorstr_("[notice] import started at a rate of 60/hour"), xorstr_(""), xorstr_("default"), 3))
						{
							logging::push(FOREGROUND_INTENSE_RED);
							logging::print(xorstr_("[critical] failed to talk to xs-overlay api [{}]\n"), xs_overlay::get().fetch_last_error());
							logging::pop();
						}
					}
				}
			}
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("imports friend list and sends each user a friend request. this works at a rate of 60 an hour."));

			ImGui::PopStyleVar();
			ImGui::EndChild();
		}

		ImGui::NextColumn();

		static float virtualization_size = 0.f;
		ImGui::BeginChild(xorstr_("virtualization.1"), ImVec2(0.f, virtualization_size), true, ImGuiWindowFlags_MenuBar);
		{
			if (ImGui::BeginMenuBar())
			{
				ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0.5f, 0.5f));
				ImGui::Selectable(xorstr_("virtualization##master"), true, ImGuiSelectableFlags_None, ImVec2(70, 0));
				ImGui::PopStyleVar();
				ImGui::EndMenuBar();
			}

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));

			ImGui::Checkbox(xorstr_("world virtualization"), &config::get<bool>(g_context.virtualize_world));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("virtualizes your world locally."));

			if (ImGui::Button(xorstr_("set world"), ImVec2(-1, 17)))
			{
				if (const auto world = assembler::room_manager::get_class()->static_fields->world)
				{
					auto id = world->get_id() + xorstr_(":::");
					id.append(world->asset_url());
					config::get<std::string>(g_context.base_virtualization) = id;

					logging::push(FOREGROUND_INTENSE_GREEN);
					logging::add_log(xorstr_("[notice] set virtualized world to \"{}\"\n"), s_chars(world->fields.name));
					logging::pop();
					ingame_logging::get().log(xorstr_("[<color=#a668f8>notice</color>] set virtualized world to \"{}\""), s_chars(world->fields.name));
				}
				else
				{
					logging::push(FOREGROUND_INTENSE_RED);
					logging::add_log(xorstr_("[critical] failed to set virtualized world.\n"));
					logging::pop();
					ingame_logging::get().log(xorstr_("[<color=#a668f8>critical</color>] failed to set virtualized world."));
				}
			}
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("sets the world in which void will use as a base when virtualized."));

			ImGui::PopStyleVar();
			virtualization_size = ImGui::GetCursorPosY() + style.ItemSpacing.y;
			ImGui::EndChild();
		}

		static float photonnetsniffer_size = 0.f;
		ImGui::BeginChild(xorstr_("photon net sniffer"), ImVec2(0.f, photonnetsniffer_size), true, ImGuiWindowFlags_MenuBar);
		{
			if (ImGui::BeginMenuBar())
			{
				ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0.5f, 0.5f));
				ImGui::Selectable(xorstr_("photon net sniffer##master"), true, ImGuiSelectableFlags_None, ImVec2(100, 0));
				ImGui::PopStyleVar();
				ImGui::EndMenuBar();
			}

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));

			if (ImGui::Button(xorstr_("open photon net sniffer"), ImVec2(-1, 17)))
				sniffer_window::opened = !sniffer_window::opened;
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("opens photon network sniffer"));

			ImGui::PopStyleVar();
			photonnetsniffer_size = ImGui::GetCursorPosY() + style.ItemSpacing.y;
			ImGui::EndChild();
		}

#if TEST == 1
		static float asmdumper_size = 0.f;
		ImGui::BeginChild(xorstr_(".net asm walker"), ImVec2(0.f, asmdumper_size), true, ImGuiWindowFlags_MenuBar);
		{
			if (ImGui::BeginMenuBar())
			{
				ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0.5f, 0.5f));
				ImGui::Selectable(xorstr_(".net asm walker##master"), true, ImGuiSelectableFlags_None, ImVec2(100, 0));
				ImGui::PopStyleVar();
				ImGui::EndMenuBar();
			}

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));

			if (ImGui::Button(xorstr_("open assembly walker"), ImVec2(-1, 17)))
			{
				if (memory::mono_handle)
				{
					dumper_window::modules = assembler::mono::fetch_images();
					dumper_window::opened = !dumper_window::opened;
				}
				else
					ImGui::OpenPopup(xorstr_("void##.netasmwalker.error"));
			}
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("opens void's .net assembly walker"));

			ImGui::PopStyleVar();

			if (ImGui::BeginPopupModal(xorstr_("void##.netasmwalker.error"), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize))
			{
				ImGui::Text(xorstr_("no mono runtimes were found."));
				ImGui::Spacing();

				if (ImGui::Button(xorstr_("ok."), ImVec2(30, 0)))
					ImGui::CloseCurrentPopup();

				ImGui::EndPopup();
			}

			asmdumper_size = ImGui::GetCursorPosY() + style.ItemSpacing.y;
			ImGui::EndChild();
		}
#endif
	}
	ImGui::Columns(1);
}

void tabs::games()
{
	const ImGuiStyle& style = ImGui::GetStyle();
	ImGui::Spacing();
	ImGui::Columns(2, nullptr, false);
	{
		static float general_size = 0.f;

		ImGui::BeginChild(xorstr_("general.1"), ImVec2(0, general_size), true, ImGuiWindowFlags_MenuBar);
		{
			if (ImGui::BeginMenuBar())
			{
				ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0.5f, 0.5f));
				ImGui::Selectable(xorstr_("general##master"), true, ImGuiSelectableFlags_None, ImVec2(70.f, 0));
				ImGui::PopStyleVar();
				ImGui::EndMenuBar();
			}

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));

			ImGui::Checkbox(xorstr_("udon-godmode"), &config::get<bool>(g_context.udon_godmode));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("attempts to prevent udon death scripts."));

			ImGui::PopStyleVar();
			general_size = ImGui::GetCursorPosY() + style.ItemSpacing.y;
			ImGui::EndChild();
		}

		static float fbt_size = 0.f;

		ImGui::BeginChild(xorstr_("fbt heaven.1"), ImVec2(0, fbt_size), true, ImGuiWindowFlags_MenuBar);
		{
			if (ImGui::BeginMenuBar())
			{
				ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0.5f, 0.5f));
				ImGui::Selectable(xorstr_("fbt heaven##master"), true, ImGuiSelectableFlags_None, ImVec2(70.f, 0));
				ImGui::PopStyleVar();
				ImGui::EndMenuBar();
			}

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));

			ImGui::Checkbox(xorstr_("anti-doorlock"), &config::get<bool>(g_context.fbt_doorbypass));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("prevents locked doors."));

			ImGui::PopStyleVar();
			fbt_size = ImGui::GetCursorPosY() + style.ItemSpacing.y;
			ImGui::EndChild();
		}
		ImGui::NextColumn();

		static float murder4_size = 0.f;

		ImGui::BeginChild(xorstr_("murder 4.1"), ImVec2(0, murder4_size), true, ImGuiWindowFlags_MenuBar);
		{
			if (ImGui::BeginMenuBar())
			{
				ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0.5f, 0.5f));
				ImGui::Selectable(xorstr_("murder 4##master"), true, ImGuiSelectableFlags_None, ImVec2(70.f, 0));
				ImGui::PopStyleVar();
				ImGui::EndMenuBar();
			}

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));

			if (ImGui::Button(xorstr_("teleport all weapons"), ImVec2(-1, 17)))
				misc::murder_teleportall();
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("teleports all weapons to you."));

			if (ImGui::Button(xorstr_("teleport knife"), ImVec2(-1, 17)))
				misc::murder_teleportsingle(xorstr_(L"knife"));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("teleports the knife to you."));

			if (ImGui::Button(xorstr_("teleport revolver"), ImVec2(-1, 17)))
				misc::murder_teleportsingle(xorstr_(L"revolver"));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("teleports the revolver to you."));

			if (ImGui::Button(xorstr_("teleport luger"), ImVec2(-1, 17)))
				misc::murder_teleportsingle(xorstr_(L"luger"));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("teleports the luger to you."));

			if (ImGui::Button(xorstr_("teleport shotgun"), ImVec2(-1, 17)))
				misc::murder_teleportsingle(xorstr_(L"shotgun"));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("teleports the shotgun to you."));

			if (ImGui::Button(xorstr_("teleport beartrap"), ImVec2(-1, 17)))
				misc::murder_teleportsingle(xorstr_(L"bear"));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("teleports the beartrap to you."));

			if (ImGui::Button(xorstr_("teleport grenade"), ImVec2(-1, 17)))
				misc::murder_teleportsingle(xorstr_(L"frag"));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("teleports the grenade to you."));

			if (ImGui::Button(xorstr_("kill all"), ImVec2(-1, 17)))
				misc::udon_killall(&g_context.skippable_sync_kills);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("kills everyone in the game. lol"));

			ImGui::Checkbox(xorstr_("anti-killcam"), &config::get<bool>(g_context.murder_anti_killcam));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("prevents flash & blind ingame huds from appearing."));
			ImGui::Checkbox(xorstr_("weapon triggers"), &config::get<bool>(g_context.murder_weapontriggers));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("sustains a weapon's pickupable property."));

			ImGui::PopStyleVar();
			murder4_size = ImGui::GetCursorPosY() + style.ItemSpacing.y;
			ImGui::EndChild();
		}
	}
	ImGui::Columns(1);
}

#if LVM_TESTING == 1
void tabs::lvm_tab()
{
	const ImGuiStyle& style = ImGui::GetStyle();
	ImGui::Spacing();

	ImGui::BeginChild(xorstr_("editor.1"), ImVec2(), true, ImGuiWindowFlags_MenuBar);
	{
		if (ImGui::BeginMenuBar())
		{
			ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0.5f, 0.5f));
			ImGui::Selectable(xorstr_("editor##master"), true, ImGuiSelectableFlags_None, ImVec2(50, 0));
			ImGui::PopStyleVar();
			ImGui::EndMenuBar();
		}

		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));

		ImGui::InputTextMultiline(xorstr_(""), &vlvm::queued_script, ImVec2(467.f, 200.f));

		if (ImGui::IsItemActive())
			menu_window::is_typing = true;
		else
			menu_window::is_typing = false;
		

		if (ImGui::Button(xorstr_("run"), ImVec2(-1, 17)))
			vlvm::do_script(vlvm::queued_script);

		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(xorstr_("runs the script in void's lua virtual machine."));

		ImGui::SameLine();

		if (ImGui::Button(xorstr_("clear"), ImVec2(-1, 17)))
			vlvm::queued_script.clear();

		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(xorstr_("clears the script window."));

		ImGui::PopStyleVar();
		ImGui::EndChild();
	}
}
#endif

void tabs::configuration()
{
	const ImGuiStyle& style = ImGui::GetStyle();
	ImGui::Spacing();
	ImGui::Columns(2, nullptr, false);
	{
		static float void_size = 0.f;

		ImGui::BeginChild(xorstr_("void.1"), ImVec2(0, void_size), true, ImGuiWindowFlags_MenuBar);
		{
			if (ImGui::BeginMenuBar())
			{
				ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0.5f, 0.5f));
				ImGui::Selectable(xorstr_("void##master"), true, ImGuiSelectableFlags_None, ImVec2(50, 0));
				ImGui::PopStyleVar();
				ImGui::EndMenuBar();
			}

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));

			if (ImGui::Button(xorstr_("autoload void"), ImVec2(-1, 17)))
			{
				if (!config::toggle_autoload())
				{
					logging::push(FOREGROUND_INTENSE_RED);
					logging::add_log(xorstr_("[error] failed to (un)setup void's autoloader\n"));
					logging::pop();
				}
			}
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("sets up void's autoloader. if enabled, void will automatically load alongside vrchat."));
			ImGui::Checkbox(xorstr_("watermark"), &config::get<bool>(g_context.watermark));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("adds watermark to top right of screen."));
			ImGui::Checkbox(xorstr_("statistics"), &config::get<bool>(g_context.statistics));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("adds game statistics to the top left of screen."));
			if (ImGui::Checkbox(xorstr_("display online"), &config::get<bool>(g_context.display_online)))
			{
				if (const auto apiuser = assembler::vrc::core::api_user::get_current())
				{
					//connection_listener::get().refresh_activity(connection_listener::get_hwid(), apiuser->get_id(), config::get<bool>(g_context.display_online));
				}
			}
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("when toggled off, other void users will not be able to see you running void."));
			if (ImGui::Checkbox(xorstr_("rainbow elements"), &config::get<bool>(g_context.rgb_elements)))
				if (!config::get<bool>(g_context.rgb_elements))
					drawing::set_colors();
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("certain elements from void will now be rainbow."));
			ImGui::HotKey(xorstr_("menu bind"), &config::get<int>(g_context.menu_key));
			ImGui::HotKey(xorstr_("playerlist bind"), &config::get<int>(g_context.playerlist_key));

			ImGui::PopStyleVar();
			void_size = ImGui::GetCursorPosY() + style.ItemSpacing.y;
			ImGui::EndChild();
		}

		static float game_settings = 0.f;
		ImGui::BeginChild(xorstr_("game.2"), ImVec2(0, game_settings), true, ImGuiWindowFlags_MenuBar);
		{
			if (ImGui::BeginMenuBar())
			{
				ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0.5f, 0.5f));
				ImGui::Selectable(xorstr_("game##master"), true, ImGuiSelectableFlags_None, ImVec2(50, 0));
				ImGui::PopStyleVar();
				ImGui::EndMenuBar();
			}

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));

			if (ImGui::Checkbox(xorstr_("discordrpc"), &config::get<bool>(g_context.discord_rpc_toggle)))
			{
				if (!config::get<bool>(g_context.discord_rpc_toggle))
					g_context.g_discord.reset();
				else
					g_context.g_discord = std::make_unique<discord_sdk>();
			}

			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("toggles discordrpc, this will respect your VRC status."));

			if (ImGui::Checkbox(xorstr_("xs-overlay integration"), &config::get<bool>(g_context.xs_overlay_toggle)))
			{
				try
				{
					if (!config::get<bool>(g_context.xs_overlay_toggle))
					{
						if (xs_overlay::get().shutdown())
						{
							logging::push(FOREGROUND_YELLOW);
							logging::print(xorstr_("[xs-overlay] successfully disconnected from api\n"));
							logging::pop();
						}
					}
					else
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
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(
					xorstr_("toggles xs-overlay integration. you must have xs-overlay running to use this."));

			if (ImGui::Checkbox(xorstr_("nameplate info"), &config::get<bool>(g_context.nameplate_info)))
			{
				if (!config::get<bool>(g_context.nameplate_info))

					for (auto it = v_players.cbegin(); it != v_players.cend(); ++it)
					{
						const auto np = (*it)->get_vrc_player()->get_name_plate()->get_transform();
						if (assembler::unity_engine::transform* info = np->find(xorstr_("Contents/VOIDINFO")))
							assembler::unity_engine::object::destroy(info->get_game_object());
					}
			}
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("renders player information below users nameplates."));

			ImGui::Checkbox(xorstr_("desktop debug"), &config::get<bool>(g_context.desktop_debug_log));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("toggles void's desktop debug menu."));
			if (ImGui::Checkbox(xorstr_("quickmenu playerlist"), &config::get<bool>(g_context.player_list_toggle)))
			{
				if (!config::get<bool>(g_context.player_list_toggle))
				{
					const auto quickmenu_loc = assembler::ui_manager_impl::instance()->get_quickmenu();
					if (const auto player_text = quickmenu_loc->get_transform()->find(xorstr_("Container/VOIDPLAYERLIST")); player_text != nullptr)
						assembler::unity_engine::object::destroy(player_text->get_game_object());
					if (const auto player_text = quickmenu_loc->get_transform()->find(xorstr_("Container/VOIDPLAYERLISTSHADOW")); player_text != nullptr)
						assembler::unity_engine::object::destroy(player_text->get_game_object());
					if (const auto player_text = quickmenu_loc->get_transform()->find(xorstr_("Container/VOIDPANEL")); player_text != nullptr)
						assembler::unity_engine::object::destroy(player_text->get_game_object());
				}
			}
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("toggles void's playerlist in vrc's quickmenu."));
			if (ImGui::Checkbox(xorstr_("quickmenu debug"), &config::get<bool>(g_context.qm_debug_log)))
			{
				try
				{
					if (!config::get<bool>(g_context.qm_debug_log))
					{
						if (!assembler::vrc_quick_menu::restore_vr_debug())
							throw std::runtime_error(xorstr_("failed to restore vr debug menu. couldn't find void's components."));
					}
					else
					{
						if (!assembler::vrc_quick_menu::init_vr_debug())
							throw std::runtime_error(xorstr_("failed to initialize vr debug menu. couldn't find components required"));
					}
				}
				catch (const std::exception& ex)
				{
					logging::push(FOREGROUND_INTENSE_RED);
					logging::print(xorstr_("[critical] {}\n"), ex.what());
					logging::pop();
				}
			}
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("toggles void's debug log in vrc's quickmenu."));

			ImGui::Checkbox(xorstr_("quickmenu persistence"), &config::get<bool>(g_context.quickmenu_persistence));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("stops your quickmenu from closing on it's own when you move."));

			ImGui::PopStyleVar();
			game_settings = ImGui::GetCursorPosY() + style.ItemSpacing.y;
			ImGui::EndChild();
		}

		ImGui::NextColumn();

		static std::string sz_current_config = {};
		static float fl_config_child_size = 0.f;

		ImGui::BeginChild(xorstr_("configuration.3"), ImVec2(0, fl_config_child_size), true, ImGuiWindowFlags_MenuBar);
		{
			if (ImGui::BeginMenuBar())
			{
				ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0.5f, 0.5f));
				ImGui::Selectable(xorstr_("configuration##master"), true, ImGuiSelectableFlags_None, ImVec2(80, 0));
				ImGui::PopStyleVar();
				ImGui::EndMenuBar();
			}

			ImGui::Columns(2, xorstr_("#CONFIG"), false);
			{
				ImGui::PushItemWidth(-1);

				ImGui::ListBox(xorstr_("##config.list"), &i_selected_config, [](const int n_index)
				{
					// return current displaying configuration name
					return config::vec_file_names.at(n_index).c_str();
				}, static_cast<std::int32_t>(config::vec_file_names.size()), 5);

				sz_current_config = !config::vec_file_names.empty() ? config::vec_file_names.at(i_selected_config) : "";
				ImGui::PopItemWidth();
			}
			ImGui::NextColumn();
			{
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));
				ImGui::PushItemWidth(-1);
				if (ImGui::InputTextWithHint(xorstr_("##config.file"), xorstr_("create new..."), &sz_config_file, ImGuiInputTextFlags_EnterReturnsTrue))
				{
					if (!config::save(sz_config_file))
					{
						logging::push(FOREGROUND_RED);
						logging::print(xorstr_("[error] failed to create \"{}\" config\n"), sz_config_file);
						logging::pop();
					}

					sz_config_file.clear();
					config::refresh();
				}
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("press enter to create new configuration."));

				if (ImGui::Button(xorstr_("save"), ImVec2(-1, 15)))
				{
					if (!config::save(sz_current_config))
					{
						logging::push(FOREGROUND_RED);
						logging::print(xorstr_("[error] failed to save \"{}\" config\n"), sz_current_config);
						logging::pop();
					}
				}
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("saves current config."));

				if (ImGui::Button(xorstr_("load"), ImVec2(-1, 15)))
				{
					if (!config::load(sz_current_config))
					{
						logging::push(FOREGROUND_RED);
						logging::print(xorstr_("[error] failed to load \"{}\" config\n"), sz_config_file);
						logging::pop();
					}
					else misc::load_config();
				}
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("press enter to create new configuration."));

				if (ImGui::Button(xorstr_("remove"), ImVec2(-1, 15)))
					ImGui::OpenPopup(xorstr_("void##config.remove"));
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("removes selected config."));

				if (ImGui::Button(xorstr_("refresh"), ImVec2(-1, 15)))
					config::refresh();
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("refreshes config list."));

				ImGui::PopItemWidth();
				ImGui::PopStyleVar();
			}
			ImGui::Columns(1);

			if (ImGui::BeginPopupModal(xorstr_("void##config.remove"), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize))
			{
				ImGui::Text(xorstr_("would you like to remove \"%s\"?"), sz_current_config.c_str());
				ImGui::Spacing();

				if (ImGui::Button(xorstr_("yes."), ImVec2(30, 0)))
				{
					config::remove(i_selected_config);
					i_selected_config = 0;
					config::refresh();
					ImGui::CloseCurrentPopup();
				}

				ImGui::SameLine();

				if (ImGui::Button(xorstr_("no."), ImVec2(30, 0)))
					ImGui::CloseCurrentPopup();

				ImGui::EndPopup();
			}

			fl_config_child_size = ImGui::GetCursorPosY() + style.ItemSpacing.y;
			ImGui::EndChild();
		}

		static float fl_extended_size = 0.f;
		ImGui::BeginChild(xorstr_("extended.4"), ImVec2(0, fl_extended_size), true, ImGuiWindowFlags_MenuBar);
		{
			if (ImGui::BeginMenuBar())
			{
				ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0.5f, 0.5f));
				ImGui::Selectable(xorstr_("extended##master"), true, ImGuiSelectableFlags_None, ImVec2(50, 0));
				ImGui::PopStyleVar();
				ImGui::EndMenuBar();
			}

			static auto cp_identifier = xorstr("custom plates");
			static auto jn_identifier = xorstr("join notifier");

			static const std::array arr_extended_tabs =
			{
				ctab{
					cp_identifier.crypt_get(), [&style]
					{
						ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));

						ImGui::Checkbox(xorstr_("enabled"), &config::get<bool>(g_context.custom_plates));
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip(xorstr_("toggles void's custom nameplates."));

						const char* sz_color_names[IM_ARRAYSIZE(arr_colors)];
						for (int i = 0; i < IM_ARRAYSIZE(arr_colors); i++)
							sz_color_names[i] = arr_colors[i].first;

						ImGui::Spacing();
						ImGui::PushItemWidth(-1);

						ImGui::ListBox(xorstr_("##colors.select"), &i_selected_color, sz_color_names,
						               IM_ARRAYSIZE(sz_color_names), 4);
						if (ImGui::ColorEdit4(xorstr_("##colors.picker"), &config::get<sdk::color>(arr_colors[i_selected_color].second), ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_AlphaPreviewHalf))
							drawing::set_colors();

						ImGui::PopItemWidth();
						ImGui::PopStyleVar();
					}
				},
				ctab{
					jn_identifier.crypt_get(), [&style]
					{
						ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));

						ImGui::Checkbox(xorstr_("enabled"), &config::get<bool>(g_context.join_notify));
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip(xorstr_("sends logs and a hud message when a player joins/leaves.."));
						ImGui::Checkbox(xorstr_("friends only"), &config::get<bool>(g_context.join_notify_friends));
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip(xorstr_("only sends notifications if the player is a friend."));

						ImGui::PopStyleVar();
					}
				}
			};

			tabs::render<arr_extended_tabs.size()>(xorstr_("extended_1"), arr_extended_tabs, &i_extended_tab);
			fl_extended_size = ImGui::GetCursorPosY() + style.ItemSpacing.y;
			ImGui::EndChild();
		}
	}

	ImGui::Columns(1);
}

void tabs::players()
{
	const ImGuiStyle& style = ImGui::GetStyle();
	ImGui::Spacing();

	ImGui::Columns(2, nullptr, false);
	{
		ImGui::BeginChild(xorstr_("functions.1"), ImVec2(), true, ImGuiWindowFlags_MenuBar);
		{
			if (ImGui::BeginMenuBar())
			{
				ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0.5f, 0.5f));
				ImGui::Selectable(xorstr_("functions##master"), true, ImGuiSelectableFlags_None, ImVec2(50, 0));
				ImGui::PopStyleVar();

				if (selectedplayer != nullptr)
					ImGui::Text((std::string(xorstr_("user: ")) + selectedplayer->get_api_user()->display_name()).c_str());

				ImGui::EndMenuBar();
			}

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));

			if (ImGui::Button(xorstr_("teleport"), ImVec2(-1, 17)) && selectedplayer)
			{
				if (selectedplayer->get_api_user()->get_id() != assembler::vrc::core::api_user::get_current()->get_id())
				{
					if (const auto vrcplayerapi = selectedplayer->get_vrc_player_api(); vrcplayerapi != nullptr)
					{
						assembler::vrc::sdk_base::vrc_player_api::get_current()->teleport_to(vrcplayerapi);
						selectedplayer = nullptr;
					}
				}
			}
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("teleports to the user."));

			if (ImGui::Button(xorstr_("download vrca"), ImVec2(-1, 17)) && selectedplayer)
			{
				logging::push(FOREGROUND_INTENSE_WHITE);
				logging::add_log(xorstr_("[notice] beginning avatar download...\n"));
				logging::pop();
				ingame_logging::get().log(xorstr_("[<color=#a668f8>notice</color>] beginning avatar download..."));

				const auto apiavatar = selectedplayer->get_vrc_player()->get_api_avatar();
				std::thread([=]
				{
					if (misc::curl_downloadfile(apiavatar->get_asset_url().c_str(), apiavatar->get_id() + xorstr_(".vrca")))
					{
						logging::push(FOREGROUND_INTENSE_GREEN);
						logging::add_log(xorstr_("[notice] download completed.\n"));
						logging::pop();
						ingame_logging::get().log(xorstr_("[<color=#a668f8>notice</color>] download completed."));

						if (config::get<bool>(g_context.xs_overlay_toggle))
						{
							if (!xs_overlay::get().send(xorstr_("[notice] download completed"), xorstr_(""), xorstr_("default"), 3))
							{
								logging::push(FOREGROUND_INTENSE_RED);
								logging::print(xorstr_("[critical] failed to talk to xs-overlay api [{}]\n"), xs_overlay::get().fetch_last_error());
								logging::pop();
							}
						}
					}
					else
					{
						logging::push(FOREGROUND_INTENSE_RED);
						logging::add_log("[notice] download failed.\n");
						logging::pop();
						ingame_logging::get().log(xorstr_("[<color=#a668f8>notice</color>] download failed."));

						if (config::get<bool>(g_context.xs_overlay_toggle))
						{
							if (!xs_overlay::get().send(xorstr_("[notice] download failed"), xorstr_(""), xorstr_("error"), 3))
							{
								logging::push(FOREGROUND_INTENSE_RED);
								logging::print(xorstr_("[critical] failed to talk to xs-overlay api [{}]\n"), xs_overlay::get().fetch_last_error());
								logging::pop();
							}
						}
					}
				}).detach();

				selectedplayer = nullptr;
			}
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("downloads this player's avatar vrca."));

			if (ImGui::Button(xorstr_("copy avatar asset id"), ImVec2(-1, 17)) && selectedplayer)
			{
				const auto string = selectedplayer->get_vrc_player()->get_api_avatar()->get_id();
				utility::set_clipboard(string);
				selectedplayer = nullptr;
			}
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("copy the user's avatar's asset id."));

			if (ImGui::Button(xorstr_("copy avatar asset url"), ImVec2(-1, 17)) && selectedplayer)
			{
				const std::string id = selectedplayer->get_vrc_player()->get_api_avatar()->get_asset_url();
				utility::set_clipboard(id);
				selectedplayer = nullptr;
			}
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("copy the user's avatar's asset url."));

			if (ImGui::Button(xorstr_("force clone"), ImVec2(-1, 17)) && selectedplayer)
			{
				if (selectedplayer->get_api_user()->get_id() != assembler::vrc::core::api_user::get_current()->get_id())
				{
					if (selectedplayer->get_vrc_player()->get_api_avatar()->get_release_status() != xorstr_("private"))
						g_context.changing_avatar = selectedplayer->get_vrc_player()->get_api_avatar()->get_id();
					else
					{
						logging::push(FOREGROUND_INTENSE_RED);
						logging::add_log(xorstr_("[error] clone failed, avatar is private.\n"));
						logging::pop();
					}

					selectedplayer = nullptr;
				}
			}

			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("force clones the user's avatar if it's public."));

			if (ImGui::Button(xorstr_("block events"), ImVec2(-1, 17)) && selectedplayer)
			{
				const auto id = selectedplayer->get_api_user()->get_id();
				const auto v = &config::get<std::vector<std::string>>(g_context.user_event_blacklist);

				if (std::ranges::find(*v, id) == v->end())
					v->push_back(id);
				else
					std::erase(*v, id);

				selectedplayer = nullptr;
			}
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("blocks all events sent by the user. to unblock click me again."));

			if (ImGui::Button(xorstr_("blacklist avatar"), ImVec2(-1, 17)) && selectedplayer)
			{
				const auto apiavatar = selectedplayer->get_vrc_player()->get_api_avatar();
				const auto id = apiavatar->get_id();

				const auto wl_v = &config::get<std::vector<std::string>>(g_context.avatar_whitelist);
				if (const auto wl_position = std::ranges::find(*wl_v, id); wl_position != wl_v->end())
					wl_v->erase(wl_position);

				const auto bl_v = &config::get<std::vector<std::string>>(g_context.avatar_blacklist);
				if (const auto bl_position = std::ranges::find(*bl_v, id); bl_position == bl_v->end())
				{
					logging::push(FOREGROUND_INTENSE_CYAN);
					logging::add_log(xorstr_("[log] blacklisted \"{}\" by \"{}\" [{}]\n"), apiavatar->get_name(), apiavatar->get_author_name(), id);
					logging::pop();
					bl_v->push_back(id);
				}
				else
				{
					logging::push(FOREGROUND_INTENSE_CYAN);
					logging::add_log(xorstr_("[log] unblacklisted \"{}\" by \"{}\" [{}]\n"), apiavatar->get_name(), apiavatar->get_author_name(), id);
					logging::pop();
					bl_v->erase(bl_position);
				}

				misc::remove_avatar_from_cache(id);
				selectedplayer->get_vrc_player()->load_avatar(true);
				selectedplayer = nullptr;
			}

			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("adds avatar to void's blacklist."));

			if (ImGui::Button(xorstr_("whitelist avatar"), ImVec2(-1, 17)) && selectedplayer)
			{
				const auto apiavatar = selectedplayer->get_vrc_player()->get_api_avatar();
				const auto id = apiavatar->get_id();

				const auto bl_v = &config::get<std::vector<std::string>>(g_context.avatar_blacklist);
				if (const auto bl_position = std::ranges::find(*bl_v, id); bl_position != bl_v->end())
					bl_v->erase(bl_position);

				const auto wl_v = &config::get<std::vector<std::string>>(g_context.avatar_whitelist);
				if (const auto wl_position = std::ranges::find(*wl_v, id); wl_position == wl_v->end())
				{
					logging::push(FOREGROUND_INTENSE_CYAN);
					logging::add_log(xorstr_("[log] whitelisted \"{}\" by \"{}\" [{}]\n"), apiavatar->get_name(), apiavatar->get_author_name(), id);
					logging::pop();
					wl_v->push_back(id);
				}
				else
				{
					logging::push(FOREGROUND_INTENSE_CYAN);
					logging::add_log(xorstr_("[log] unwhitelisted \"{}\" by \"{}\" [{}]\n"), apiavatar->get_name(), apiavatar->get_author_name(), id);
					logging::pop();
					wl_v->erase(wl_position);
				}

				misc::remove_avatar_from_cache(id);
				selectedplayer->get_vrc_player()->load_avatar(true);
				selectedplayer = nullptr;
			}
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("adds avatar to void's whitelist."));

			if (ImGui::Button(xorstr_("copy uspeak data"), ImVec2(-1, 17)) && selectedplayer)
			{
				if (selectedplayer->get_photon_id() != assembler::vrc::player::get_current()->get_photon_id())
				{
					if (config::get<int>(g_context.copy_event1) == selectedplayer->get_photon_id())
						config::get<int>(g_context.copy_event1) = NULL;
					else
						config::get<int>(g_context.copy_event1) = selectedplayer->get_photon_id();

					selectedplayer = nullptr;
				}
				else config::get<int>(g_context.copy_event1) = NULL;
			}
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("copy's this player's uspeak data."));

			//if (ImGui::Button(xorstr_("copy ik data"), ImVec2(-1, 17)))
			//{
			//	if (selectedplayer != nullptr)
			//	{
			//		if (selectedplayer->get_photon_id() != assembler::vrc::player::get_current()->get_photon_id())
			//		{
			//			if (g_context.copy_event7 == selectedplayer->get_photon_id())
			//				g_context.copy_event7 = NULL;
			//			else
			//				g_context.copy_event7 = selectedplayer->get_photon_id();

			//			selectedplayer = nullptr;
			//		}
			//	}
			//	else g_context.copy_event7 = NULL;
			//}

			if (ImGui::Button(xorstr_("teleport pickups"), ImVec2(-1, 17)) && selectedplayer)
			{
				misc::teleport_pickups(selectedplayer->get_vrc_player()->get_transform()->get_position());
				selectedplayer = nullptr;
			}
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("teleports all pickups to player."));

			if (ImGui::Button(xorstr_("player attach"), ImVec2(-1, 17)))
			{
				if (!g_context.player_attach)
				{
					if (selectedplayer != nullptr)
					{
						if (selectedplayer->get_photon_id() != assembler::vrc::player::get_current()->get_photon_id())
						{
							g_context.player_attach_id = selectedplayer->get_photon_id();
							g_context.player_attach = true;
						}
					}
				}
				else
				{
					g_context.player_attach = false;
					g_context.player_attach_id = 0;
				}

				selectedplayer = nullptr;
			}
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(xorstr_("attaches you to the selected player's head."));

			ImGui::PopStyleVar();
			ImGui::EndChild();
		}

		ImGui::NextColumn();

		ImGui::BeginChild(xorstr_("players.2"), ImVec2(), true, ImGuiWindowFlags_MenuBar);
		{
			if (ImGui::BeginMenuBar())
			{
				ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0.5f, 0.5f));
				ImGui::Selectable(xorstr_("players##master"), true, ImGuiSelectableFlags_None, ImVec2(50, 0));
				ImGui::PopStyleVar();
				ImGui::EndMenuBar();
			}

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));

			if (g_context.instantiated)
				for (auto it = v_players.begin(); it != v_players.end(); ++it)
					if (ImGui::Button((*it)->get_api_user()->display_name().c_str(), ImVec2(-1, 17)))
						selectedplayer = *it;

			ImGui::PopStyleVar();
			ImGui::EndChild();
		}
	}

	ImGui::Columns(1);
}

#if TEST == 1
void dumper_window::render_window()
{
	const ImGuiStyle& style = ImGui::GetStyle();
	const ImGuiIO& io = ImGui::GetIO();

	ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Once, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSize(ImVec2(380, 600), ImGuiCond_Always);

	const std::string title = xorstr_("void ") + std::string(stage) + xorstr_(" build ") + std::string(build) + xorstr_(" | .net asm walker");
	ImGui::Begin(title.c_str(), &mainmenu_opened, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
	{
		const ImVec2 vec_position = ImGui::GetCursorScreenPos();
		const float fl_window_width = ImGui::GetWindowWidth();

		// push clip so separator will be drawn at maximal window bounds
		ImGui::PushClipRect(ImVec2(vec_position.x - 8.f, vec_position.y - 8.f), ImVec2(vec_position.x + fl_window_width - 8.f, vec_position.y - 6.f), false);
		ImGui::PopClipRect();

		ImGui::BeginChild(xorstr_("modules.1"), ImVec2(0, 407), true, ImGuiWindowFlags_MenuBar);
		{
			if (ImGui::BeginMenuBar())
			{
				ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0.5f, 0.5f));
				ImGui::Selectable(xorstr_("modules##master"), true, ImGuiSelectableFlags_None, ImVec2(50, 0));
				ImGui::PopStyleVar();

				if (selected)
					ImGui::Text(std::vformat(xorstr_("module: {}.dll"), std::make_format_args(image_get_name(selected))).c_str());
				else
					ImGui::Text(xorstr_("module: none"));

				ImGui::EndMenuBar();
			}

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));

			for (std::size_t i = 0; i < modules.size(); ++i)
			{
				if (ImGui::Button((std::string(image_get_name(modules[i])) + xorstr_(".dll")).c_str(), ImVec2(-1, 17))) 
				{
					selected = modules[i];
					selected_asm = image_get_assembly(selected);
				}

				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("select this module"));
			}

			ImGui::PopStyleVar();
			ImGui::EndChild();
		}

		ImGui::BeginChild(xorstr_("info.1"), ImVec2(), true, ImGuiWindowFlags_MenuBar);
		{
			if (ImGui::BeginMenuBar())
			{
				ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0.5f, 0.5f));
				ImGui::Selectable(xorstr_("info##master"), true, ImGuiSelectableFlags_None, ImVec2(50, 0));
				ImGui::PopStyleVar();

				ImGui::EndMenuBar();
			}

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));

			if (selected) 
			{
				const auto size = static_cast<double>(selected->raw_data_len) / 1000;
				ImGui::Text(std::vformat(xorstr_("module: {}.dll"), std::make_format_args(image_get_name(selected))).c_str());

				const std::string_view base_dir = selected_asm->basedir ? selected_asm->basedir : xorstr_("none");

				ImGui::Text(utility::format(xorstr_("base dir: {}"), base_dir).c_str());
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(base_dir.data());

				ImGui::Text(utility::format(xorstr_("size: {:.2f}kb"), size).c_str());
				selected->is_module_handle ? ImGui::Text(xorstr_("is handle: true")) : ImGui::Text(xorstr_("is handle: false"));

				const std::string_view hash = selected_asm->aname.hash_value ? selected_asm->aname.hash_value : xorstr_("none");
				ImGui::Text(utility::format(xorstr_("hash: {}"), hash).c_str());

				if (ImGui::Button(xorstr_("export"), ImVec2(-1, 17)) && selected)
				{
					if (!dump())
					{
						logging::push(FOREGROUND_INTENSE_RED);
						logging::add_log(xorstr_("[error] failed to export module.\n"));
						logging::pop();
					}
					else
					{
						logging::push(FOREGROUND_INTENSE_GREEN);
						logging::add_log(xorstr_("[notice] exported module to %appdata%\\Void\\dumps\\\n"));
						logging::pop();
					}
				}
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(xorstr_("exports specified module to appdata\\Void\\dumps\\"));

			}
			else
				ImGui::Text(xorstr_("module: none"));

			ImGui::PopStyleVar();
			ImGui::EndChild();
		}

		ImGui::End();
	}
}

bool dumper_window::dump()
{
	const auto path = config::get_working_path();

	if (path.empty())
		return false;

	const auto directory = path / xorstr_("dumps");

	try 
	{
		// VMProtectBeginUltra("Dumper File Structure");

		if (!exists(directory))
		{
			if (!create_directory(directory))
				return false;
		}
		else
		{
			if (!is_directory(directory))
			{
				if (!remove(directory))
					return false;

				if (!create_directory(directory))
					return false;
			}
		}

		// VMProtectEnd();
	}
	catch (std::filesystem::filesystem_error& e)
	{
		logging::push(FOREGROUND_INTENSE_RED);
		logging::add_log(xorstr_("[error] failed to dump module: {}\n"), e.what());
		logging::pop();

		return false;
	}

	const auto exports_file = directory / (std::string(image_get_name(selected)) + xorstr_(".dll"));

	try
	{
		// VMProtectBeginUltra("Dumper Output");

		std::ofstream ofs_out_file(exports_file, std::ios::out | std::ios::trunc | std::ios::binary);

		ofs_out_file.write(selected->raw_data, selected->raw_data_len);

		if (!ofs_out_file.good())
			return false;

		ofs_out_file << std::string_view(selected->raw_data, selected->raw_data_len);
		ofs_out_file.close();

		// VMProtectEnd();
	}
	catch (std::wofstream::failure& e)
	{
		logging::push(FOREGROUND_INTENSE_RED);
		logging::add_log(xorstr_("[error] failed to dump module: {}\n"), e.what());
		logging::pop();

		return false;
	}

	return true;
}

#endif
#pragma endregion
