/*
 *		assembler/assembly-csharp/system/buffer.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Window's System Buffer class replication, also contains a lot of random functions
 */
#ifndef BUFFER_HPP
#define BUFFER_HPP

#pragma once
#include "../../il2cpp/array_wrapper.hpp"
#include "../../common.hpp"
#include <string>

namespace assembler
{
    struct buffer : il2cpp::il2cpp_object
    {
        DELCONST(buffer);

        static void block_copy(il2cpp::il2cpp_array* src, std::int32_t src_offset, il2cpp::il2cpp_array* dst, std::int32_t dst_offset, std::int32_t cnt);
        static il2cpp::il2cpp_array* get_bytes(std::int32_t value);
        static bool deserialize(il2cpp::il2cpp_array* src, il2cpp_object** ref);
        static il2cpp::il2cpp_array_wrapper<il2cpp_object*>* serialize_parameters(il2cpp::il2cpp_array* bytes);
        static std::string to_base64_string(il2cpp::il2cpp_array* arr);
        static il2cpp::il2cpp_array* from_base64_string(std::string_view s);
    };
}

#endif
