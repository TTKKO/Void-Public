/*
 *		assembler/assembly-csharp/moderationmanager.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's VRChat ModerationManager class replication
 */

#pragma once
#include "../unityengine/component.hpp"

namespace assembler
{
    struct moderation_manager : unity_engine::component
    {
		enum class moderation_type : std::int32_t
		{
			none = 0,
			block = 1,
			mute = 2,
			unmute = 3,
			hide_avatar = 4,
			show_avatar = 5
		};

        static moderation_manager* instance();
		bool check_moderation(il2cpp::il2cpp_string* user_id, moderation_type type);
		bool check_moderation(std::string_view user_id, moderation_type);
    };
}
