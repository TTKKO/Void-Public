/*
 *		utilities/utilities.hpp
 *		Void
 *		
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Miscellaneous functions used throughout the source
 */


#ifndef UTILITIES_HPP
#define UTILITIES_HPP
#pragma once
#include "../core/sdk/hash/xorstr.hpp"
#include "../dependencies/imgui/imgui.h"
#include <json.hpp>
#include <iostream>
#include <fstream>
#include <format>
#include <codecvt>
#include <locale>
#include <mutex>
#include <regex>
#include <date/date.h>
#include <curl/curl.h>

#pragma region vmprotect_macros
#define SECSTR(x) (x)//(x)
#define SECSTRW(x) (x)//VMProtectDecryptStringW(x)
#pragma endregion

#pragma region logging_console_colors
#define FOREGROUND_WHITE		    (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN)
#define FOREGROUND_YELLOW       	(FOREGROUND_RED | FOREGROUND_GREEN)
#define FOREGROUND_CYAN		        (FOREGROUND_BLUE | FOREGROUND_GREEN)
#define FOREGROUND_MAGENTA	        (FOREGROUND_RED | FOREGROUND_BLUE)
#define FOREGROUND_BLACK		    0

#define FOREGROUND_INTENSE_RED		(FOREGROUND_RED | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_GREEN	(FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_BLUE		(FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_WHITE	(FOREGROUND_WHITE | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_YELLOW	(FOREGROUND_YELLOW | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_CYAN		(FOREGROUND_CYAN | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_MAGENTA	(FOREGROUND_MAGENTA | FOREGROUND_INTENSITY)
#pragma endregion

#pragma region logging_exception_handling
#ifdef _DEBUG
#define SEH_CATCH _RPT0(_CRT_ERROR, ex.what());
#else
#define SEH_CATCH std::abort();
#endif

#define SEH_START try {
#define SEH_END } catch (const std::exception& ex) {		\
	logging::push(FOREGROUND_INTENSE_RED);			\
	logging::print(xorstr_("[critical] {}\n"), ex.what());	\
	logging::pop();									\
	SEH_CATCH }
#pragma endregion

namespace utility
{
    template <typename ... ArgsT>
    constexpr std::string format(const std::string_view sz_text, ArgsT&& ... args_list)
    {
        return std::vformat(sz_text, std::make_format_args(std::forward<ArgsT>(args_list)...));
    }

    std::string get_date();
    std::string get_time();

    std::size_t write_data_callback(const void* ptr, std::size_t size, std::size_t nmemb, FILE* stream);

#pragma region string_manipulation
    std::string unicode_ascii(std::wstring_view wsz_unicode);
    std::wstring ascii_encode(std::string_view sz_ascii);
    void unicode_tolower(std::wstring& wsz_text);
    void unicode_toupper(std::wstring& wsz_text);
    void ascii_tolower(std::string& sz_text);
    void ascii_toupper(std::string& sz_text);
#pragma endregion

    std::string get_clipboard();
    void set_clipboard(std::string_view sz_text);

    std::wstring get_parent_path();
    std::vector<std::string> split(const std::string& str, const std::string& regex_str);
}

namespace logging
{
#pragma region vars
    inline ImGuiTextBuffer buf;
    inline ImGuiTextBuffer buf_times;
    inline ImVector<int> line_offsets;
    inline ImVector<int> buf_times_offsets;

    inline FILE* p_estream;
    inline FILE* p_ostream;
    inline FILE* p_istream;

    inline std::uint16_t w_console_color = FOREGROUND_INTENSE_WHITE;
    inline std::ofstream ofs_file;
    inline std::mutex m_log_mutex;
#pragma endregion

    void clear();

#pragma region output
    template <typename ... ArgsT>
    void print(const std::string_view sz_text, ArgsT&& ... args_list)
    {
        // @note: format time
        const std::string sz_time = std::vformat(xorstr_("[{:%m-%d-%Y %X}] "), std::make_format_args(std::chrono::system_clock::now()));

        // @note: print to console
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSE_CYAN);
        std::cout << sz_time;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSE_MAGENTA);
        std::cout << xorstr_("[void]: ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), w_console_color);

        if constexpr (sizeof...(args_list) > 0)
    	{
            // @note: prints to console
            const auto fmt_text = std::vformat(sz_text, std::make_format_args(std::forward<ArgsT>(args_list)...));
            std::cout << fmt_text << std::flush;

            // @note: prints to file
            if (ofs_file.is_open())
                ofs_file << sz_time << fmt_text << std::flush;
        }
        else 
        {
            // @note: prints to console
            std::cout << sz_text << std::flush;

            // @note: prints to file
            if (ofs_file.is_open())
                ofs_file << sz_time << sz_text << std::flush;
        }
    }

    template <typename ... ArgsT>
    void print_imgui(const std::string_view fmt, ArgsT&& ... args_list)
    {
        int old_size = buf.size();
    	std::lock_guard lock_guard(m_log_mutex);

        if constexpr (sizeof...(args_list) > 0)
            buf.append(std::vformat(fmt, std::make_format_args(std::forward<ArgsT>(args_list)...)).c_str());
        else
            buf.append(fmt.data());

        for (const std::int32_t new_size = buf.size(); old_size < new_size; old_size++)
            if (buf[old_size] == '\n')
                line_offsets.push_back(old_size + 1);

        buf_times.append(utility::get_time().c_str());
        buf_times_offsets.push_back(buf_times.size());
    }

    template <typename ... ArgsT>
    void add_log(const std::string_view fmt, ArgsT&& ... args_list)
    {
        const auto fmt_text = std::vformat(fmt, std::make_format_args(std::forward<ArgsT>(args_list)...));

        print(fmt_text);
        print_imgui(fmt_text);
    }
#pragma endregion

    void draw(const ImColor& rainbow, bool draw_rainbow);
    bool attach(const wchar_t* sz_console_title);
    void detach();

    inline void push(const std::uint16_t w_color)
    {
        w_console_color = w_color;
    }

    inline void pop()
    {
        w_console_color = FOREGROUND_INTENSE_WHITE;
    }
};
#endif
