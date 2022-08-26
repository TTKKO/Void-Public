#include "player.hpp"

#include "sdkbase/vrcplayerapi.hpp"

std::string assembler::vrc::player::to_string() // public override string ToString()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] to_string passed nullptr.\n"));
        logging::pop();
        return xorstr_("INVALID_STRING");
    }

    using to_string_func_t = il2cpp::il2cpp_string* (*)(player*);
    static const auto to_string_func = memory::get_method<to_string_func_t>(PLAYERTOSTRING);
    return s_chars(to_string_func(this));
}

assembler::vrc::player* assembler::vrc::player::get_current()
{
    using func_t = player * (*)();
    static const auto func = memory::get_method<func_t>(PLAYERCURRENTUSER);
    return func();
}

std::int32_t assembler::vrc::player::get_photon_id()
{
    if (this == nullptr) 
        return NULL;

    const auto photonplayer = *reinterpret_cast<std::uint64_t*>(reinterpret_cast<std::uint8_t*>(this) + 0x40);

    if (!photonplayer) 
        return NULL;

    return *reinterpret_cast<std::int32_t*>(photonplayer + 0x18);
}

assembler::vrc::core::api_user* assembler::vrc::player::get_api_user()
{
    if (this == nullptr) 
        return nullptr;

    return *reinterpret_cast<core::api_user**>(reinterpret_cast<std::uint8_t*>(this) + 0x18);
}

assembler::vrc_player* assembler::vrc::player::get_vrc_player()
{
    if (this == nullptr) 
        return nullptr;

    return *reinterpret_cast<vrc_player**>(reinterpret_cast<std::uint8_t*>(this) + 0x20);
}

assembler::vrc::sdk_base::vrc_player_api* assembler::vrc::player::get_vrc_player_api()
{
    if (this == nullptr) return nullptr;
    return *reinterpret_cast<sdk_base::vrc_player_api**>(reinterpret_cast<std::uint8_t*>(this) + 0x50);
}
