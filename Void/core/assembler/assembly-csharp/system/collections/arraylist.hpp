/*
 *		assembler/assembly-csharp/system/collections/arraylist.hpp
 *		Void
 *
 *		Copyright � 2021 Azurilex. All rights reserved.
 *		Void's arraylist class replication
 */

#pragma once
#include "../../../common.hpp"

namespace assembler::system_replication::collections
{
    struct array_list : il2cpp::il2cpp_object
    {
        static array_list* ctor();
        std::int32_t add(il2cpp_object* value);
        object_array* to_array();
    };

    template <typename... TArgs>
    object_array* create_object_array(TArgs&&... args)
    {
        const auto arraylist = array_list::ctor();

        using expand = int[];
        (void)expand
        {
            0, (arraylist->add(reinterpret_cast<il2cpp::il2cpp_object*>(args)), 0)...
        };

        return arraylist->to_array();
    }
}