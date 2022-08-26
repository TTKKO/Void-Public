/*
 *		DiscordRPC/discord.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's Discord integration
 */
#ifndef DISCORD_HPP
#define DISCORD_HPP

#pragma once
#include "../core/assembler/vrc/core/apiuser.hpp"
#include "../core/assembler/vrc/core/apiworld.hpp"
#include "../core/assembler/vrc/core/apiworldinstance.hpp"
#include "../core/assembler/vrc/player.hpp"
#include "../core/assembler/vrc/playermanager.hpp"
#include <discord_rpc.h>

class discord_sdk
{
public:
    discord_sdk();
    _NODISCARD bool update() const;
    ~discord_sdk();

private:
    DiscordEventHandlers handle_{};
    std::int64_t eptime_;
};

#endif
