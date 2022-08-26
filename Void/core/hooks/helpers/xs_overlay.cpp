#include "xs_overlay.hpp"

void xs_overlay::xso_message::to_json(nlohmann::json& j) const
{
    j[xorstr_("messageType")] = this->message_type;
    j[xorstr_("index")] = this->idx;
    j[xorstr_("volume")] = this->volume;
    j[xorstr_("audioPath")] = this->audio_path;
    j[xorstr_("timeout")] = this->timeout;
    j[xorstr_("title")] = this->title;
    j[xorstr_("content")] = this->content;
    j[xorstr_("icon")] = this->icon;
    j[xorstr_("height")] = this->height;
    j[xorstr_("opacity")] = this->opacity;
    j[xorstr_("useBase64Icon")] = this->use_base64_icon;
    j[xorstr_("sourceApp")] = this->source_app;
}

std::string_view xs_overlay::fetch_last_error() const
{
    return std::string_view(last_error_);
}

bool xs_overlay::initialize()
{
    if (!socket_)
    {
        // VMProtectBeginMutation("Windows Socket");

        if ((socket_ = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        {
            last_error_ = SECSTR("failed to initialize native socket");
            return false;
        }

        serv_addr_.sin_family = AF_INET;
        serv_addr_.sin_port = htons(port);

        if (inet_pton(AF_INET, SECSTR("127.0.0.1"), &serv_addr_.sin_addr) <= 0)
        {
            last_error_ = SECSTR("failed to open socket on port 42069");
            return false;
        }

        if (const auto res = connect(socket_, reinterpret_cast<sockaddr*>(&serv_addr_), sizeof serv_addr_); res == -1)
        {
            last_error_ = SECSTR("failed to initialize socket connection");
            return false;
        }

        // VMProtectEnd();

        return true;
    }

    last_error_ = SECSTR("socket already opened");
    return false;
}

bool xs_overlay::is_connected() const
{
    return socket_;
}

bool xs_overlay::send(const std::string_view title, const std::string_view content, const std::string_view type, const float timeout)
{
    if (socket_)
    {
        //xso_message message;
        xso_message message{ 1 };
        message.message_type = 1;
        message.title = title;
        message.content = content;
        message.height = 120.f;
        message.source_app = xorstr_("VRChat");
        message.timeout = timeout;
        message.audio_path = type;
        message.use_base64_icon = false;
        message.icon = type;
        message.opacity = 0.9f;

        nlohmann::json j{};
        char parsed_json[1000] = { 0 };

        try 
        {
            message.to_json(j);
            auto str = j.dump();
            std::ranges::copy(str, parsed_json);
        }
    	catch (const nlohmann::json::exception& e)
        {
            last_error_ = xorstr_("failed to parse message.");

            logging::push(FOREGROUND_INTENSE_RED);
            logging::print(xorstr_("[critical] {}\n"), e.what());
            logging::pop();

            return false;
        }

        if (const auto res = sendto(socket_, parsed_json, strlen(parsed_json), 0, reinterpret_cast<sockaddr*>(&serv_addr_), sizeof serv_addr_); res == -1)
        {
            last_error_ = xorstr_("failed to send message over socket");
            return false;
        }

        return true;
    }

    last_error_ = xorstr_("socket connection not opened");
    return false;
}

bool xs_overlay::shutdown()
{
    if (socket_)
    {
        // VMProtectBeginMutation("Windows Socket Shutdown");

        closesocket(socket_);
        socket_ = 0;

        // VMProtectEnd();
        return true;
    }
    return false;
}
