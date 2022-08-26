#include "properbitconverter.hpp"

std::int32_t assembler::vrc::udon::serialization::odin_serializer::proper_bit_converter::to_int32(const std::vector<std::uint8_t>& vec, const std::size_t pos, const bool big_endian) // public static uint ToInt32(byte[] buffer, int index)
{
	if (pos > vec.size() || pos + 4 > vec.size())
		return 1;

	std::int32_t i;
	if (memcpy_s(&i, sizeof std::int32_t, &vec[pos], sizeof std::uint8_t * 4) != 0)
		return 0;

	if (big_endian)
		i = static_cast<std::int32_t>(_byteswap_ulong(static_cast<DWORD>(i)));

	return i;
}

std::int32_t assembler::vrc::udon::serialization::odin_serializer::proper_bit_converter::to_int32(il2cpp::il2cpp_array_wrapper<std::uint8_t>* arr, const std::size_t pos, const bool big_endian)
{
	if (pos > arr->max_length || pos + 4 > arr->max_length)
		return 1;

	std::int32_t i;
	if (memcpy_s(&i, sizeof std::int32_t, &arr->at(pos), sizeof std::uint8_t * 4) != 0)
		return 0;

	if (big_endian)
		i = static_cast<std::int32_t>(_byteswap_ulong(static_cast<DWORD>(i)));

	return i;
}