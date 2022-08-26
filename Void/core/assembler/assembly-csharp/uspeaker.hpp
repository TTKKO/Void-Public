/*
 *		assembler/assembly-csharp/uspeaker.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's VRChat USpeaker class replication
 */

#pragma once
#include "../common.hpp"
#include "../il2cpp/il2cpp.hpp"

enum class bit_rate : int
{
    bit_rate_8k,
    bit_rate_10k,
    bit_rate_16k,
    bit_rate_18k,
    bit_rate_20k,
    bit_rate_24k,
    bit_rate_32k,
    bit_rate_48k,
    bit_rate_64k,
    bit_rate_96k,
    bit_rate_128k,
    bit_rate_256k,
    bit_rate_384k,
    bit_rate_512k,
};

namespace assembler
{
	struct uspeaker_fields : unity_engine::unity_engine_object_fields {
		std::int32_t _10_;
		std::int32_t _11_;
		bit_rate bitrate;
		std::int32_t _13_;
		float _14_;
		std::int32_t _15_;
		bool _16_;
		std::int32_t _17_;
		bool _18_;
		bool _19_;
		bool _20_;
		float _21_;
		float _23_;
		float _24_;
		bool _27_;
		struct _793_o* _30_;
		struct UnityEngine_AudioSource_o* _31_;
		struct ONSPAudioSource_o* _32_;
		struct _474_o* _33_;
		struct OVRLipSyncContext_o* _34_;
		struct OVRLipSyncContextMorphTarget_o* _35_;
		struct _630_o* _36_;
		struct _622_o* _37_;
		struct UnityEngine_AudioClip_o* _38_;
		struct _717_o* _39_;
		struct _1414_o* _40_;
		std::int32_t _41_;
		std::int32_t _42_;
		std::int32_t _43_;
		float _44_;
		float _45_;
		struct System_Collections_Generic_List_o* _46_;
		System_Collections_Generic_List_o* _47_;
		struct System_Byte_array* _48_;
		struct _1407_o* _49_;
		struct _1408_o* _50_;
		std::int32_t _51_;
		struct _1412_o* _52_;
		struct System_String_o* _53_;
		float _54_;
		float _55_;
		float _56_;
		float _57_;
		std::int32_t _58_;
		std::int32_t _59_;
		std::int32_t _60_;
		std::int32_t _61_;
		bool _62_;
		std::int32_t _63_;
		std::int32_t _65_;
		std::int32_t _66_;
		std::int32_t _67_;
		std::int32_t _68_;
		std::int32_t _69_;
		float _70_;
		std::uint32_t _71_;
		float _72_;
		std::uint32_t _73_;
		float _78_;
		std::int32_t _79_;
		bool _80_;
		struct System_Single_array* _81_;
		struct _1743_o* _82_;
		std::uint32_t _83_;
		float _84_;
		float _85_;
		float _86_;
		float _87_;
		float _88_;
		float _89_;
		float _90_;
		float _91_;
		float _92_;
		float _93_;
		float _94_;
		float _95_;
		bool _96_;
		float _97_;
		float _98_;
		bool _99_;
		float _100_;
		float _101_;
		std::int32_t _105_;
		float _106_;
		float _107_;
		float _108_;
		float _109_;
		double _110_;
		float _113_;
		float _114_;
		float _115_;
		std::int32_t _116_;
		std::int32_t _117_;
		struct _98_array* _119_;
		std::int32_t _120_;
		float _139_;
		float _140_;
		float _141_;
		float _142_;
		std::int32_t _143_;
		std::int32_t _144_;
		std::int32_t _145_;
		std::int32_t _146_;
		std::int32_t _147_;
	};
	struct uspeaker_rgctxs {
	};
	struct uspeaker_vtable {
		il2cpp::virtual_invoke_data _0_Equals;
		il2cpp::virtual_invoke_data _1_Finalize;
		il2cpp::virtual_invoke_data _2_GetHashCode;
		il2cpp::virtual_invoke_data _3_ToString;
	};
	struct uspeaker_c {
		il2cpp::il2cpp_class_1 _1;
		struct uspeaker_static_fields* static_fields;
		uspeaker_rgctxs* rgctx_data;
		il2cpp::il2cpp_class_2 _2;
		uspeaker_vtable vtable;
	};

	struct uspeaker
	{
		uspeaker_c* klass;
		void* monitor;
		uspeaker_fields fields;

		void set_bitrate(bit_rate bitrate);
		void set_remotegain(float db);
	};

	struct uspeaker_static_fields {
		bool _;
		bool _1_;
		float _2_;
		float remotegain;
		bool _4_;
		System_Collections_Generic_List_o* _5_;
		int32_t _6_;
		System_String_o* _7_;
		struct System_Collections_Generic_List_ValueTuple_float_o* _9_;
		struct System_String_array* _28_;
		float _75_;
		struct System_Collections_Generic_Dictionary_Nullable_int_o* _102_;
	};

}
