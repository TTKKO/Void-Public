/*
 *		assembler/vrc/udon/serialization/odinserializer/properbitconverter.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		custom implementation of vrchat's bitconverter class
 */

#pragma once
#include "../../../../il2cpp/il2cpp.hpp"

namespace assembler::vrc::udon::serialization::odin_serializer
{
    struct proper_bit_converter
    {
        static std::int32_t to_int32(const std::vector<std::uint8_t>& vec, std::size_t pos, bool big_endian = false);
        static std::int32_t to_int32(il2cpp::il2cpp_array_wrapper<std::uint8_t>* arr, std::size_t pos, bool big_endian = false);
    };
}
