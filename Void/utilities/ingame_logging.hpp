/*
 *		utilities/ingame_logging.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		awful implementation of logging to void's quickmenu
 */

#ifndef INGAME_LOGGING_HPP
#define INGAME_LOGGING_HPP

#pragma once
#include <regex>
#include "../core/assembler/vrc/vrcquickmenu.hpp"
#include "../core/assembler/assembly-csharp/ui_manager_impl.hpp"

namespace assembler::vrc_quick_menu
{
    bool vr_debug_update();
}

class ingame_logging : public c_singleton<ingame_logging>
{
    std::mutex m_lock_{};
    std::vector<std::string> log_list_{};
    std::int32_t log_list_index_ = 0;
    std::int32_t max_debug_lines_ = 26;
public:
    bool update();
    bool update_shadow();

    template <typename ... ArgsT>
    void log(const std::string_view sv_text, ArgsT&& ... args_list)
    {
        if constexpr (sizeof...(args_list) > 0)
        {
            std::lock_guard log_lock(m_lock_);
            log_list_.emplace_back(std::vformat(sv_text, std::make_format_args(std::forward<ArgsT>(args_list)...)));
        }
        else
        {
            std::lock_guard log_lock(m_lock_);
            log_list_.emplace_back(sv_text);
        }

        if (!assembler::vrc_quick_menu::vr_debug_update())
        {
            logging::push(FOREGROUND_INTENSE_RED);
            logging::print(xorstr_("[critical] failed to update vr debug menu, likely that the text is missing.\n"));
            logging::pop();
        }
    }
};

//inline std::vector<ConsoleUtils::Line> ConsoleUtils::LogList;
#endif
