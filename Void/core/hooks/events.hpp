/*
 *		hooks/events.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		VRChat hooks
 */

#pragma once
#include "eventmap.hpp"
#include <random>
#include "../assembler/assembly-csharp/system/collections/dictionary.hpp"
#include "../assembler/assembly-csharp/vrc_eventlog.hpp"
#include "../assembler/assembly-csharp/eventdata.hpp"
#include "../assembler/assembly-csharp/highlightsfx.hpp"
#include "../assembler/vrc/udon/serialization/odinserializer/properbitconverter.hpp"
#include "../assembler/vrc/sdkbase/networking.hpp"
#include "../assembler/vrc/sdkbase/vrc_pickup.hpp"
#include "../assembler/assembly-csharp/system/buffer.hpp"
#include "../assembler/assembly-csharp/photon_player.hpp"
#include "../assembler/unityengine/xrdevice.hpp"
#include "../assembler/unityengine/xrsettings.hpp"
#include "../assembler/unityengine/material.hpp"
#include "../assembler/vrc/vrcquickmenu.hpp"
#include "../assembler/assembly-csharp/vrcuipage.hpp"
#include "../assembler/assembly-csharp/vrc_tracking_manager.hpp"
#include "../assembler/vrc/vrcsocialmenu.hpp"
#include "../assembler/vrc/modules/lovense_modules.hpp"
#include "../../detours/cdetourhook.hpp"
#include "helpers/nameplates.hpp"
#include "helpers/game_manager.hpp"
#include "helpers/camera_handler.hpp"
#include "../sdk/input_system.hpp"

class detours : public c_singleton<detours>
{
public:
    void setup();
    bool init();
    void restore();
    void setup_ratelimter();
private:
    struct mode
    {
        std::string name;
        bool enabled{};
        void* genuine_f{};
        void* detour_f{};

        c_detour_hook detour{};
        bool operator()(const mode& m) const;
        bool apply_hook();
    };

    static inline std::unordered_set<std::string> userlist_ = std::unordered_set<std::string>();
    static inline nlohmann::json userplates_ = nlohmann::json();

    struct photon_network
    {
        std::uintptr_t* photon_network_ptr = nullptr;
        assembler::il2cpp::il2cpp_object* raise_options = nullptr;
        std::uintptr_t* send_options = nullptr;
    } pn_;

    std::mutex g_mutex_{};
    std::mutex bot_mutex_{};
    std::mutex blocked_users_mutex_{};
    std::unordered_set<std::int32_t> blocked_users_{};
    std::unordered_set<std::int32_t> invisible_users_{};
    std::unordered_map<std::int32_t, bool> bot_users_{};

    std::vector<mode> detours_ = std::vector<mode>();
    event_map event_map_ = event_map();

    std::string cached_hwid_{};

    std::int32_t e7_exploit_servertime_ = 0;
    std::uint64_t tickcount_ = 0;

    float avatar_rotation_z_ = 0.f;
    float update_delay_ = 1.f;

    bool should_skip_update_ = true;
    bool initialized_menu_ = false;
    bool right_trigger_ready_ = true;

    bool deserialize_safety_check_ = false;
	bool quickmenu_safety_check_ = false;

    bool is_quickmenu_open_ = false;

    mode& fetch_hook(const std::string& setting_name);
    void clean();

    static bool hk_opraiseevent(std::uintptr_t* _this, std::uint8_t code, assembler::il2cpp::il2cpp_object* custom_content, assembler::il2cpp::il2cpp_object* raise_options, std::uintptr_t* send_options);
    static void hk_playerupdate(assembler::vrc_player* _this, float f, float f_2);
    static void* hk_processaudio(void* _this, assembler::il2cpp::il2cpp_object* a1, assembler::il2cpp::il2cpp_array_wrapper<std::uint8_t>* buffer, int length);
    static void hk_videoaddurl(void* _this, assembler::il2cpp::il2cpp_string* url);
    static void hk_loadurl(void* _this, assembler::il2cpp::il2cpp_string* vrcurl);
    static void hk_setfixeddeltatime(float value);
    static std::uintptr_t* hk_onavatardownload(std::uintptr_t* callback, assembler::vrc::core::api_avatar* avatar, assembler::il2cpp::il2cpp_object* a3, bool a4 = false);
    static void hk_onevent(assembler::il2cpp::il2cpp_object* _this, assembler::event_data* event_data);
    static void hk_ontriggerenter(assembler::il2cpp::il2cpp_object* _this, assembler::unity_engine::collider* collider);
    static std::int32_t hk_getroundtriptime(void* _this);
    static void hk_onupdate(assembler::il2cpp::il2cpp_object* _this);
    static assembler::il2cpp::il2cpp_string* hk_getdeviceuniqueidentifier();
    static float hk_getsmoothdeltatime();
    static assembler::il2cpp::il2cpp_object* hk_switchavatarrpc(assembler::il2cpp::il2cpp_object* callback, assembler::vrc::avatarmanager* _this, assembler::vrc::core::api_avatar* apiavatar, float fl);
    static void hk_onphotonplayerjoined(void* _this, assembler::photon_player* photon_player);
    static void hk_onphotonplayerleft(void* _this, assembler::photon_player* photon_player);
    static void hk_onplayerjoin(assembler::il2cpp::il2cpp_object* _this, assembler::vrc::player* player);
    static void hk_onplayerleft(assembler::il2cpp::il2cpp_object* _this, assembler::vrc::player* player);
    static void hk_onleftroom(void* _this);
    static void hk_sendputrequest(assembler::il2cpp::il2cpp_string* target, assembler::il2cpp::il2cpp_object* res, assembler::il2cpp::il2cpp_object* req, assembler::il2cpp::il2cpp_object* cr);
    static bool hk_vrcuipage_awake(assembler::unity_engine::component* _this);
    static void hk_udonbehaviour_runprogramstr(assembler::unity_engine::component* _this, assembler::il2cpp::il2cpp_string* event_name);
    static void hk_udonsync_runprogramasrpc(assembler::unity_engine::component* _this, assembler::il2cpp::il2cpp_string* a2, assembler::vrc::player* player);
    static void hk_customscenes_ctor(assembler::il2cpp::il2cpp_object* _this, assembler::vrc::core::api_world* a2);
    static assembler::il2cpp::il2cpp_object* hk_assetbundle_loadworld(assembler::il2cpp::il2cpp_object* callback, assembler::vrc::core::api_world* a2, assembler::il2cpp::il2cpp_object* a3, bool a4 = false);
    static void hk_onmenuclose(assembler::ui_manager_impl* _this, bool a2);
    static void hk_onmenuopen(assembler::ui_manager_impl* _this, bool a2);
    static void hk_onflowpage(assembler::il2cpp::il2cpp_object* _this, bool a2);
    static void hk_onvrcuimanager_place(assembler::unity_engine::component* _this, bool a2 = false, bool a3 = false);
};