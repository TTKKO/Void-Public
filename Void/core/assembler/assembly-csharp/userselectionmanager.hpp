/*
 *		assembler/assembly-csharp/userselectionmanager.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's UserSelectionManager class replication
 */

#pragma once
#include "../unityengine/behaviour.hpp"
#include "../vrc/core/apiuser.hpp"

namespace assembler
{
    struct user_selection_manager_fields {
        vrc::core::api_user* apiuser1;
        vrc::core::api_user* apiuser2;
    };
    
    struct user_selection_manager : unity_engine::behaviour
    {
    private:
        inline static il2cpp::il2cpp_class* global_klass_ = nullptr;
    public:
        user_selection_manager_fields fields;

        static user_selection_manager* instance();
        static il2cpp::il2cpp_class* get_global_klass();
    };

    struct user_selection_manager_staticfields {
        user_selection_manager* instance;
    };
}
