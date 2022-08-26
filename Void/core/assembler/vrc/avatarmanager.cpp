#include "avatarmanager.hpp"

// private readonly List<AudioSource>

assembler::vrc::core::api_avatar* assembler::vrc::avatarmanager::get_api_avatar()
{
    return *reinterpret_cast<core::api_avatar**>(reinterpret_cast<std::uint8_t*>(this) + 0x2D0);
}

assembler::vrc_player* assembler::vrc::avatarmanager::get_vrc_player()
{
    return *reinterpret_cast<vrc_player**>(reinterpret_cast<std::uint8_t*>(this) + 0xC0);
}
