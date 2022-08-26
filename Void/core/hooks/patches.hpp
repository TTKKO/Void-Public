/*
 *		hooks/patches.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		UnityPlayer hooks
 */
#ifndef PATCHES_HPP
#define PATCHES_HPP

#pragma once
#include "../assembler/unityengine/scene.hpp"
#include "../assembler/unityengine/cursor.hpp"
#include "../assembler/vrc/core/pipeline_manager.hpp"
#include "helpers/helpers.hpp"
#include "helpers/assetbundle_processor.hpp"
#include "../menu.hpp"

class patches : public c_singleton<patches>
{
public:
    void setup();
    bool init();
    void restore();
private:
    struct mode
    {
        std::string name{};
        bool enabled{};
        void* genuine_f{};
        void* detour_f{};
        c_detour_hook detour{};

        bool operator()(const mode& m) const;
        bool apply_patch();
    };

    static const inline std::array<const char*, 6ull> allowed_fields = {
        xorstr_("m_BreakForce"),
        xorstr_("m_BreakTorque"),
        xorstr_("collisionSphereDistance"),
        xorstr_("maxDistance"),
        xorstr_("inSlope"),
        xorstr_("outSlope")
    };

    struct node_container
    {
        std::uint8_t padding_1[0x70];
        node_container** subs;
        std::uint8_t padding_2[0x8];
        std::int64_t direct_sub_count;
    };

    struct native_string
    {
        std::uintptr_t* data;    // 8
        std::int64_t capacity; // 16
        std::int64_t unknown;  // 24
        std::int64_t length;   // 32
    };

    bool set_readobject_patches_ = false;
    bool set_nop_inst_ = false;
    bool read_audio_mixers_ = true;
    bool read_bad_floats_ = true;
    bool read_null_objects_ = false;

    std::vector<mode> patches_ = std::vector<mode>();
    native_string* last_reallocated_string_ = nullptr;

    std::intptr_t* cached_serialized_file_ = nullptr;
    std::intptr_t* cached_loadop_ = nullptr;
    std::intptr_t* cached_asyncloadop_ = nullptr;

    std::int32_t crasher_depth_ = 0;
    std::int32_t asyncoperations_depth_ = 0;
    std::int32_t read_object_depth_ = 0;
    std::int32_t cached_reader_update_depth_ = 0;
    std::int32_t reader_depth_ = 0;
    std::int32_t last_reallocation_count_ = 0;

    mode& fetch_patch(const std::string& setting_name);

    static assembler::unity_engine::object* hk_ab_load(assembler::unity_engine::object* obj, bool b1, bool b2, bool b3);
    //static char hk_get_components_implementation_recurse(std::uintptr_t* a1, std::int64_t a2, std::int64_t a3, void** a4, std::int64_t a5);

    static void hk_reallocatestring(native_string* a1, std::int64_t a2);
    static std::uint32_t impl_transform_countnodesdeep(node_container* _this, std::unordered_set<node_container*>& map);
    static std::uint32_t hk_transform_countnodesdeep(node_container* _this);
    static void hk_debugstringtofilepostprocessedstacktrace(const char** data);
    static void hk_reader_outofbounds(std::uintptr_t* _this, long a1, long a2);
    static std::uint64_t serializetraits_resizestlstylearray(std::uintptr_t* a1, std::int32_t a2);

    static std::intptr_t hk_readobject(std::intptr_t* a1, std::intptr_t a2, char* a3, bool a4, std::uintptr_t* a5, std::uint8_t* a6, std::uintptr_t* a7);

    static std::uintptr_t* hk_persistentmanager_readobjectthreated(std::intptr_t* _this, std::int32_t a2, std::int32_t a3);
    static std::uintptr_t* hk_persistentmanager_readandactiveobjectthreaded(std::intptr_t* _this, std::uint32_t a2, std::uint32_t* a3, std::intptr_t* a4, std::uint8_t a5, std::intptr_t a6, std::int32_t a7);
    static std::intptr_t* hk_assetbundleloadassetop_getloadedasset(std::intptr_t* _this, std::intptr_t a2, std::intptr_t a3);
    static std::intptr_t* hk_downloadhandlerassetbundle_getassetbundle(std::intptr_t* _this);
    static void hk_assetbundleloadfromasyncop_perform(std::intptr_t* _this);

    static std::intptr_t hk_awakefromloadqueue_add(std::intptr_t* a1, std::intptr_t* a2);

    static std::intptr_t* hk_persistentmanager_registerpartiallyloadedobjectinternal(std::intptr_t* _this, std::int32_t);

    static std::intptr_t hk_audiomixer_produce(std::uint32_t a1, std::uint32_t a2);
    static void hk_safebinaryread_transfer(std::uintptr_t* a1, float* a2, const char* a3);
    static void hk_gameobject_transfer(std::uintptr_t* a1, const std::uintptr_t* a2);

    static void hk_sceneloadedinternal(assembler::unity_engine::scene scene, std::int32_t mode);
    static void hk_sceneunloadedinternal(assembler::unity_engine::scene scene);
    static void hk_setlockstate(assembler::unity_engine::cursor_lock_mode value);

    static void hk_cachedreader_read(std::intptr_t* _this, void* a2, std::size_t size);
    static void hk_cachedreader_updatereadcache(std::intptr_t* _this, void* a2, std::size_t size);
    static void hk_cachedreader_setposition(std::intptr_t* _this, std::uintptr_t a2);
    static void hk_cachedreader_end(std::intptr_t* _this);

    static void hk_streamedbinaryread_readdirect(std::uintptr_t* _this, void* a2, std::int32_t size);
    static std::intptr_t hk_transferfield_array_streamedbinaryread_converterstring(std::intptr_t a1, std::intptr_t a2);
    static std::intptr_t hk_streamedbinaryread_transferarrayofmanagedobjects(std::intptr_t a1, std::uintptr_t* a2);
    static void hk_virtualredirecttransfer(std::uintptr_t* _this, struct streamed_binary_read* a2, std::uintptr_t a3, DWORD a4);
    static std::uintptr_t* hk_serialize_traits_for_string_types(native_string* a1, std::int32_t a2);
    static std::uintptr_t hk_serializetraits_keyframe_resizestlarray(std::uintptr_t* a1, std::int32_t a2);
    static std::intptr_t hk_ash_readheadersignature(std::uintptr_t* a1, std::intptr_t a2);
};

namespace patches_proxy
{
	std::int32_t evaluate_exception(DWORD code);

    using hk_readobject_func = std::intptr_t (*)(std::intptr_t*, std::intptr_t, char*, bool, std::uintptr_t*, std::uint8_t*, std::uintptr_t*);
    inline std::intptr_t hk_readobject(const hk_readobject_func f, std::intptr_t* a1, const std::intptr_t a2, char* a3, const bool a4, std::uintptr_t* a5, std::uint8_t* a6, std::uintptr_t* a7)
    {
        __try
        {
        	return f(a1, a2, a3, a4, a5, a6, a7);
        }
        __except (evaluate_exception(exception_code()))
        {
	        switch(exception_code())
            {
            case STATUS_OUT_OF_BOUNDS:
                throw std::runtime_error(SECSTR("anti-oob: encountered out of bounds asset."));
            case STATUS_ARRAY_OVERFLOW:
                throw std::runtime_error(SECSTR("anti-array overflow: encountered bad bundle."));
            case STATUS_BAD_ALLOCATION:
                throw std::runtime_error(SECSTR("anti-oob: bad allocation."));
	        case STATUS_BAD_POINTER:
                throw std::runtime_error(SECSTR("anti-oob: attempt to write invalid memory."));
            default: throw std::runtime_error(SECSTR("an unknown error occurred"));
            }
        }
    }
}

#endif
