/*
 *		assembler/assembly-csharp/vrcuipage.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's VRChat VRCUiPage class replication
 */

#pragma once
#include "../unityengine/component.hpp"

namespace assembler
{
    struct vrc_ui_page : unity_engine::component
    {
    private:
        static inline il2cpp::il2cpp_type* type_ = nullptr;
    public:
        static il2cpp::il2cpp_type* get_type();
        static vrc_ui_page* get_page(std::string_view path);
        void set_name(std::string_view name);
    };
}
