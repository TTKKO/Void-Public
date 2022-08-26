#include "vrcplayer.hpp"
#include "../vrc/sdkbase/networking.hpp"
#include "system/collections/arraylist.hpp"

assembler::vrc_player* assembler::vrc_player::get_current()
{
    return vrc::player::get_current()->get_vrc_player();
}

assembler::vrc::player* assembler::vrc_player::get_player()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_player passed nullptr\n"));
        logging::pop();
        return nullptr;
    }
    return *reinterpret_cast<vrc::player**>(reinterpret_cast<std::uint8_t*>(this) + 0x50); //_player;
}

std::uint64_t assembler::vrc_player::get_steam_id()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_steam_id passed nullptr\n"));
        logging::pop();
        return NULL;
    }
    return *reinterpret_cast<std::uint64_t*>(reinterpret_cast<std::uint8_t*>(this) + 0x190); //private ulong
}

short assembler::vrc_player::get_ping()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_ping passed nullptr\n"));
        logging::pop();
        return NULL;
    }
    const auto playernet = *reinterpret_cast<std::uint64_t*>(reinterpret_cast<std::uint8_t*>(this) + 0x58); //_playerNet;

    if (!playernet) 
        return NULL;

    return *reinterpret_cast<short*>(playernet + 0x58);
}

int assembler::vrc_player::get_fps() //inherited from playernet class
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_fps passed nullptr\n"));
        logging::pop();
        return NULL;
    }

    const auto playernet = *reinterpret_cast<std::uint64_t*>(reinterpret_cast<std::uint8_t*>(this) + 0x58);

    if (!playernet)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] playernet passed nullptr\n"));
        logging::pop();
        return NULL;
    }
    const auto premath = *reinterpret_cast<std::uint8_t*>(playernet + 0x5C);

    if (premath <= 0) 
        return NULL;

    return static_cast<int>(1000.f / static_cast<float>(premath));
}

assembler::vrc::core::api_avatar* assembler::vrc_player::get_api_avatar()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_api_avatar passed nullptr\n"));
        logging::pop();
        return nullptr;
    }
    return *reinterpret_cast<vrc::core::api_avatar**>(reinterpret_cast<std::uint8_t*>(this) + 0x178);
}

assembler::player_nameplate* assembler::vrc_player::get_name_plate()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_name_plate passed nullptr\n"));
        logging::pop();
        return nullptr;
    }
    return *reinterpret_cast<player_nameplate**>(reinterpret_cast<std::uint8_t*>(this) + 0x68);
}

assembler::vrc::avatarmanager* assembler::vrc_player::get_avatarmanager()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_avatarmanager passed nullptr\n"));
        logging::pop();
        return nullptr;
    }
    return *reinterpret_cast<vrc::avatarmanager**>(reinterpret_cast<std::uint8_t*>(this) + 0xD8); // OBFUSCATIONMESSk__BackingField
}

assembler::uspeaker* assembler::vrc_player::get_uspeaker()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_uspeaker passed nullptr\n"));
        logging::pop();
        return nullptr;
    }
    return *reinterpret_cast<uspeaker**>(reinterpret_cast<std::uint8_t*>(this) + 0xB0);
}

assembler::unity_engine::animator* assembler::vrc_player::get_animator()
{
    if (!this)
        return nullptr;

    return *reinterpret_cast<unity_engine::animator**>(reinterpret_cast<std::uint8_t*>(this) + 0x130);
}

void assembler::vrc_player::spawn_emoji(emojis index)
{
    if (!this)
        return;

    vrc::sdk_base::networking::rpc(
        0,
        this->get_game_object(),
        xorstr_("SpawnEmojiRPC"),
        system_replication::collections::create_object_array(il2cpp::value_box(xorstr_("System.Int32"), &index))
    );
}

void assembler::vrc_player::load_avatar(const bool force)
{
    if (!this)
        return;

    using func_t = void (*)(vrc_player*, bool);
    static const auto func = memory::get_method<func_t>(VRCPLAYER_LOADAVATAR);
	func(this, force);
}

void assembler::vrc_player::load_all_avatars(const bool self)
{
    if (!this)
        return;

    using func_t = void (*)(vrc_player*, bool);
    static const auto func = memory::get_method<func_t>(VRCPLAYER_LOADALLAVATARS);
    func(this, self);
}
