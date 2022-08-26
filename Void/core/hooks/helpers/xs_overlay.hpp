#pragma once

#ifndef XS_OVERLAY_HPP
#define XS_OVERLAY_HPP

#include <Ws2tcpip.h>
#include <json.hpp>
#include "../../../utilities/memory.hpp"

class xs_overlay : public c_singleton<xs_overlay>
{
public:
    struct xso_message
    {
        std::int32_t message_type{};
        std::int32_t idx{};
        float volume{};
        std::string_view audio_path;
        float timeout{};
        std::string_view title;
        std::string_view content;
        std::string_view icon;
        float height{};
        float opacity{};
        bool use_base64_icon{};
        std::string_view source_app;

        void to_json(nlohmann::json& j) const;
    };

private:
    std::string last_error_ = xorstr_("none");
    sockaddr_in serv_addr_ = {};
    std::int32_t socket_ = 0;
    static constexpr std::int32_t port = 42069;

public:
    _NODISCARD std::string_view fetch_last_error() const;
    bool initialize();
    _NODISCARD bool is_connected() const;
    bool send(std::string_view title, std::string_view content, std::string_view type = xorstr_("default"), float timeout = 6);
    bool shutdown();
};

#endif
