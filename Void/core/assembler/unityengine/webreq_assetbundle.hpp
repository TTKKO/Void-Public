/*
 *		assembler/unityengine/webreq_assetbundle.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Unity's WebRequestAssetBundle class
 */

#pragma once
#include "../il2cpp/il2cpp.hpp"

namespace assembler::unity_engine
{
    struct web_request
    {
        il2cpp::il2cpp_object* send_web_request();

    private:
        using send_web_request_t = il2cpp::il2cpp_object* (*)(web_request*);
        inline static send_web_request_t send_web_request_func_ = nullptr;
    };

    struct webreq_assetbundle
    {
        static web_request* get_asset_bundle(std::string_view url);
    };
}
