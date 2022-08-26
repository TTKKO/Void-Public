/*
 *		assembler/vrc/ui/pageavatar.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of VRChat's PageAvatar class
 */
#ifndef PAGEAVATAR_HPP
#define PAGEAVATAR_HPP

#pragma once
#include "../../il2cpp/il2cpp.hpp"
#include "../../unityengine/component.hpp"

namespace assembler::vrc::core
{
    struct api_avatar;
}

namespace assembler::vrc::ui
{
    struct page_avatar : unity_engine::component
    {
    private:
        static inline il2cpp::il2cpp_type* type_ = nullptr;
    public:
        static il2cpp::il2cpp_type* get_type();
        static page_avatar* ctor();
        static void force_change(core::api_avatar* a1, std::string_view a2, core::api_avatar* a3);
    };
}

#endif
