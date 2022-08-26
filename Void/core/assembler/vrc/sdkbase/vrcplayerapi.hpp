/*
 *		assembler/vrc/sdkbase/vrcplayerapi.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of VRChat's VRCPlayerApi class
 */
#ifndef VRCPLAYERAPI_HPP
#define VRCPLAYERAPI_HPP

#pragma once
#include "../player.hpp"
#include "../../../sdk/datatypes/color.h"
#include "networking.hpp"

namespace assembler::unity_engine
{
	enum class human_body_bones : std::int32_t
	{
		hips = 0,
		left_upper_leg = 1,
		right_upper_leg = 2,
		left_lower_leg = 3,
		right_lower_leg = 4,
		left_foot = 5,
		right_foot = 6,
		spine = 7,
		chest = 8,
		neck = 9,
		head = 10,
		left_shoulder = 11,
		right_shoulder = 12,
		left_upper_arm = 13,
		right_upper_arm = 14,
		left_lower_arm = 15,
		right_lower_arm = 16,
		left_hand = 17,
		right_hand = 18,
		left_toes = 19,
		right_toes = 20,
		left_eye = 21,
		right_eye = 22,
		jaw = 23,
		left_thumb_proximal = 24,
		left_thumb_intermediate = 25,
		left_thumb_distal = 26,
		left_index_proximal = 27,
		left_index_intermediate = 28,
		left_index_distal = 29,
		left_middle_proximal = 30,
		left_middle_intermediate = 31,
		left_middle_distal = 32,
		left_ring_proximal = 33,
		left_ring_intermediate = 34,
		left_ring_distal = 35,
		left_little_proximal = 36,
		left_little_intermediate = 37,
		left_little_distal = 38,
		right_thumb_proximal = 39,
		right_thumb_intermediate = 40,
		right_thumb_distal = 41,
		right_index_proximal = 42,
		right_index_intermediate = 43,
		right_index_distal = 44,
		right_middle_proximal = 45,
		right_middle_intermediate = 46,
		right_middle_distal = 47,
		right_ring_proximal = 48,
		right_ring_intermediate = 49,
		right_ring_distal = 50,
		right_little_proximal = 51,
		right_little_intermediate = 52,
		right_little_distal = 53,
		upper_chest = 54,
		last_bone = 55,
	};
}

namespace assembler::vrc::sdk_base
{
	struct __declspec(align(8)) vrc_sdk_base_vrc_player_api_fields
	{
		bool is_local;
		il2cpp::il2cpp_string* display_name;
		int32_t m_player_id;
		unity_engine::game_object* game_object;
		bool is_valid;
	};

	struct vrc_sdk_base_vrc_player_api_vtable
	{
		il2cpp::virtual_invoke_data _0_Equals;
		il2cpp::virtual_invoke_data _1_Finalize;
		il2cpp::virtual_invoke_data _2_GetHashCode;
		il2cpp::virtual_invoke_data _3_ToString;
		il2cpp::virtual_invoke_data _4_IsValid;
	};

	struct vrc_sdk_base_vrc_player_api_c
	{
		il2cpp::il2cpp_class_1 _1;
		struct vrc_sdk_base_vrc_player_api_static_fields* static_fields;
		struct VRC_SDKBase_VRCPlayerApi_RGCTXs* rgctx_data;
		il2cpp::il2cpp_class_2 _2;
		vrc_sdk_base_vrc_player_api_vtable vtable;
	};

	struct vrc_player_api
	{
		vrc_sdk_base_vrc_player_api_c* klass;
		void* monitor;
		vrc_sdk_base_vrc_player_api_fields fields;

		static vrc_player_api* get_current();
		std::int32_t player_id();
		sdk::vector get_position();
		sdk::quaternion get_rotation();
		static void teleport_to(vrc_player_api* who, vrc_player_api* to);
		void teleport_to(vrc_player_api* player);
		void teleport_to(const sdk::vector& position, const sdk::quaternion& rotation);
		void set_run_speed(float speed = 4);
		void set_walk_speed(float speed = 4);
		void set_jump_impulse(float impulse = 3);
		void set_name_plate_color(const sdk::color& col);
		bool is_vr();
		//void set_mute_status(bool can_speak, bool can_hear);
		bool get_is_master();
		sdk::vector get_bone_position(unity_engine::human_body_bones tt);
	};

	struct vrc_sdk_base_vrc_player_api_static_fields
	{
		il2cpp::il2cpp_object* is_master_delegate;
		il2cpp::il2cpp_object* is_instance_owner_delegate;
		il2cpp::il2cpp_object* is_moderator_delegate;
		il2cpp::il2cpp_object* is_super_delegate;
		il2cpp::il2cpp_object* set_animator_bool;
		il2cpp::il2cpp_object* claim_network_control;
		il2cpp::il2cpp_object* get_look_ray;
		il2cpp::il2cpp_object* is_grounded;
		il2cpp::il2cpp_object* s_players;
		il2cpp::il2cpp_object* get_player_id;
		il2cpp::il2cpp_object* get_player_by_game_object;
		il2cpp::il2cpp_object* get_player_by_id;
		il2cpp::il2cpp_object* is_owner;
		il2cpp::il2cpp_object* take_ownership;
		il2cpp::il2cpp_object* get_tracking_data;
		il2cpp::il2cpp_object* get_bone_transform;
		il2cpp::il2cpp_object* get_bone_position;
		il2cpp::il2cpp_object* get_bone_rotation;
		il2cpp::il2cpp_object* get_pickup_in_hand;
		il2cpp::il2cpp_object* play_haptic_event_in_hand;
		il2cpp::il2cpp_object* teleport_to;
		il2cpp::il2cpp_object* teleport_to_orientation;
		il2cpp::il2cpp_object* teleport_to_orientation_lerp;
		il2cpp::il2cpp_object* respawn;
		il2cpp::il2cpp_object* respawn_with_index;
		il2cpp::il2cpp_object* enable_pickups;
		il2cpp::il2cpp_object* set_name_plate_color;
		il2cpp::il2cpp_object* restore_name_plate_color;
		il2cpp::il2cpp_object* set_name_plate_visibility;
		il2cpp::il2cpp_object* restore_name_plate_visibility;
		il2cpp::il2cpp_object* set_player_tag;
		il2cpp::il2cpp_object* get_player_tag;
		il2cpp::il2cpp_object* get_players_with_tag;
		il2cpp::il2cpp_object* clear_player_tags;
		il2cpp::il2cpp_object* set_invisible_to_tagged;
		il2cpp::il2cpp_object* set_invisible_to_untagged;
		il2cpp::il2cpp_object* set_silenced_to_tagged;
		il2cpp::il2cpp_object* set_silenced_to_untagged;
		il2cpp::il2cpp_object* clear_invisible;
		il2cpp::il2cpp_object* clear_silence;
		il2cpp::il2cpp_object* set_run_speed;
		il2cpp::il2cpp_object* set_walk_speed;
		il2cpp::il2cpp_object* set_strafe_speed;
		il2cpp::il2cpp_object* set_jump_impulse;
		il2cpp::il2cpp_object* set_gravity_strength;
		il2cpp::il2cpp_object* get_run_speed;
		il2cpp::il2cpp_object* get_walk_speed;
		il2cpp::il2cpp_object* get_strafe_speed;
		il2cpp::il2cpp_object* get_jump_impulse;
		il2cpp::il2cpp_object* get_gravity_strength;
		il2cpp::il2cpp_object* set_voice_gain;
		il2cpp::il2cpp_object* set_voice_distance_near;
		il2cpp::il2cpp_object* set_voice_distance_far;
		il2cpp::il2cpp_object* set_voice_volumetric_radius;
		il2cpp::il2cpp_object* set_voice_lowpass;
		il2cpp::il2cpp_object* set_avatar_audio_gain;
		il2cpp::il2cpp_object* set_avatar_audio_far_radius;
		il2cpp::il2cpp_object* set_avatar_audio_near_radius;
		il2cpp::il2cpp_object* set_avatar_audio_volumetric_radius;
		il2cpp::il2cpp_object* set_avatar_audio_force_spatial;
		il2cpp::il2cpp_object* set_avatar_audio_custom_curve;
		il2cpp::il2cpp_object* combat_setup;
		il2cpp::il2cpp_object* combat_set_max_hitpoints;
		il2cpp::il2cpp_object* combat_set_current_hitpoints;
		il2cpp::il2cpp_object* combat_get_current_hitpoints;
		il2cpp::il2cpp_object* combat_set_respawn;
		il2cpp::il2cpp_object* combat_set_damage_graphic;
		il2cpp::il2cpp_object* combat_get_destructible;
		il2cpp::il2cpp_object* is_user_in_vr;
		il2cpp::il2cpp_object* use_legacy_locomotion;
		il2cpp::il2cpp_object* use_attached_station;
		il2cpp::il2cpp_object* push_animations;
		il2cpp::il2cpp_object* pop_animations;
		il2cpp::il2cpp_object* immobilize;
		il2cpp::il2cpp_object* set_velocity;
		il2cpp::il2cpp_object* get_velocity;
		il2cpp::il2cpp_object* get_position;
		il2cpp::il2cpp_object* get_rotation;
	};
}

#endif
