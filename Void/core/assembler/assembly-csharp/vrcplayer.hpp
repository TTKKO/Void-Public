/*
 *		assembler/assembly-csharp/vrcplayer.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's VRChat VRCPlayer class replication
 */

#pragma once
#include "../vrc/avatarmanager.hpp"
#include "player_nameplate.hpp"
#include "../unityengine/transform.hpp"
#include "../unityengine/animator.hpp"
#include "../vrc/player.hpp"
#include "uspeaker.hpp"

namespace assembler
{
    enum class emojis : std::int32_t
    {
        angry,
        flushed,
        crying,
        frown,
        wave,
        brah,
        heart_eyes,
        pumpkin,
        kiss,
        laughing,
        skull,
        smile,
        ghost,
        neutral,
        cool,
        think,
        thumbs_down,
        thumbs_up,
        silly,
        mouth_open,
        bat,
        cloud,
        flames,
        snowflake,
        snowball,
        splash,
        cobweb,
        beer,
        candy,
        candycane,
        candycorn,
        cheers,
        coconut,
        gingebread,
        icecream,
        pineapple,
        pizza,
        tomato,
        beach_ball,
        coal,
        party,
        gift,
        presents,
        safety_tube,
        mistletoe,
        money,
        sunscreen,
        cheap_glasses,
        boo,
        broken_heart,
        alert,
        go,
        heart,
        music,
        question_mark,
        no_entry,
        zzz
    };

    struct vrc_player : unity_engine::component
    {
        static vrc_player* get_current();

        vrc::player* get_player();
        std::uint64_t get_steam_id();
        short get_ping();
        int get_fps();
        vrc::core::api_avatar* get_api_avatar();
        player_nameplate* get_name_plate();
        vrc::avatarmanager* get_avatarmanager();
        uspeaker* get_uspeaker();
        unity_engine::animator* get_animator();
        void spawn_emoji(emojis index);
        void load_avatar(bool force = false);
        void load_all_avatars(bool self = false);
    };
}
