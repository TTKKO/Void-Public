/*
 *		assembler/assembly-csharp/vrc_tracking_manager.hpp // @note: unused?
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's VRChat TrackingManager class replication
 */

#pragma once
#include "../unityengine/component.hpp"

namespace assembler
{
    struct vrc_tracking_manager : unity_engine::component
    {
    private:
        inline static il2cpp::il2cpp_type* global_type_ = nullptr;
        static il2cpp::il2cpp_type* get_global_type();
    public:
        static vrc_tracking_manager* instance();
    };
}
