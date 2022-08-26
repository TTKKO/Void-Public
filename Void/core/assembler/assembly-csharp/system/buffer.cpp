#include "buffer.hpp"

void assembler::buffer::block_copy(il2cpp::il2cpp_array* src, const std::int32_t src_offset, il2cpp::il2cpp_array* dst, const std::int32_t dst_offset, const std::int32_t cnt)
{
	static const auto func = memory::get_method<decltype(&block_copy)>(BLOCKCOPY);
    func(src, src_offset, dst, dst_offset, cnt);
}

assembler::il2cpp::il2cpp_array* assembler::buffer::get_bytes(const std::int32_t value)
{
    static auto integer_type = il2cpp::class_from_system_type(il2cpp::get_type(xorstr_("System.Int32")));
    const auto arr = array_new<std::uint8_t>(integer_type, sizeof std::int32_t);
    memcpy_s(&arr->at(0), sizeof std::int32_t, &value, sizeof std::int32_t);
    return arr;
}

bool assembler::buffer::deserialize(il2cpp::il2cpp_array* src, il2cpp_object** ref)
{
    static const auto func = memory::get_method<decltype(&deserialize)>(DESERIALIZEARRAY);
    return func(src, ref);
}

assembler::il2cpp::il2cpp_array_wrapper<assembler::il2cpp::il2cpp_object*>* assembler::buffer::serialize_parameters(il2cpp::il2cpp_array* bytes)
{
    static const auto func = memory::get_method<decltype(&serialize_parameters)> (SERIALIZEPARAMETERS);
    return func(bytes);
}

std::string assembler::buffer::to_base64_string(il2cpp::il2cpp_array* arr)
{
    using func_t = il2cpp::il2cpp_string* (*)(il2cpp::il2cpp_array*);
    static const auto func = memory::get_method<func_t>(TOBASE64STRING);
    return s_chars(func(arr));
}

assembler::il2cpp::il2cpp_array* assembler::buffer::from_base64_string(const std::string_view s)
{
    using func_t = il2cpp::il2cpp_array* (*)(il2cpp::il2cpp_string*);
    static const auto func = memory::get_method<func_t>(FROMBASE64STRING);
    return func(il2cpp::string_new(s));
}
