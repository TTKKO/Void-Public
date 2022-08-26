#include "il2cpp.hpp"

void assembler::il2cpp::free(void* src)
{
	static const auto func = reinterpret_cast<decltype(&free)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_free")));
	return func(src);
}

const assembler::il2cpp::method_info* assembler::il2cpp::fetch_method_info(const il2cpp_class* klass, const std::string_view sz_text)
{
	const auto methods_size = klass->_2.method_count;
	const auto methods = klass->_1.methods;

	for (std::uint16_t i = 0; i < methods_size; ++i)
		if (sz_text == methods[i]->name)
			return methods[i];

	return nullptr;
}

const assembler::il2cpp::method_info* assembler::il2cpp::fetch_method_info(const il2cpp_class* klass, const std::uint16_t idx)
{
	const auto methods_size = klass->_2.method_count;
	const auto methods = klass->_1.methods;

	if (idx > methods_size)
		return nullptr;

	return methods[idx];
}

void assembler::il2cpp::dump_method_info(const il2cpp_class* klass)
{
	const auto methods_size = klass->_2.method_count;
	const auto methods = klass->_1.methods;

	for (std::uint16_t i = 0; i < methods_size; ++i)
		logging::print(xorstr_("[debug] method_info[{:d}]: {}\n"), i, methods[i]->name);
}

assembler::il2cpp::il2cpp_string* assembler::il2cpp::string_new(const std::wstring_view sz_text)
{
	using func_t = il2cpp_string * (*)(const il2cpp_char*, std::int32_t len);
	static const auto func = reinterpret_cast<func_t>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_string_new_utf16")));
	return func(sz_text.data(), static_cast<std::int32_t>(sz_text.length()));
}

assembler::il2cpp::il2cpp_string* assembler::il2cpp::string_new(const std::string_view sz_text)
{
	try
	{
		const auto utf16 = utility::ascii_encode(sz_text);

		using func_t = il2cpp_string * (*)(const il2cpp_char*, std::int32_t len);
		static const auto func = reinterpret_cast<func_t>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_string_new_utf16")));
		return func(utf16.c_str(), static_cast<std::int32_t>(utf16.length()));
	}
	catch (const std::range_error& e)
	{
		logging::push(FOREGROUND_INTENSE_RED);
		logging::print(xorstr_("[critical] {}\n"), e.what());
		logging::pop();
		return nullptr;
	}
}

std::string assembler::il2cpp::s_chars(const il2cpp_string* sz_text)
{
	if (!sz_text)
		return xorstr_("INVALID_STRING");

	// @note: possibility of throwing a runtime_error exception or bad_allocation exception
	try
	{
		return utility::unicode_ascii(sz_text->chars);
	}
	catch (const std::range_error& e)
	{
		logging::push(FOREGROUND_INTENSE_RED);
		logging::print(xorstr_("[critical] {}\n"), e.what());
		logging::pop();
		return xorstr_("INVALID_STRING");
	}
}

std::wstring assembler::il2cpp::ws_chars(il2cpp_string* sz_text)
{
	if (sz_text == nullptr)
		return xorstr_(L"INVALID_STRING");

	return sz_text->chars;
}

std::wstring_view assembler::il2cpp::wsv_chars(il2cpp_string* sz_text)
{
	if (sz_text == nullptr)
		return xorstr_(L"INVALID_STRING");

	return sz_text->chars;
}


void* assembler::il2cpp::resolve_icall(const char* sz_text)
{
	static const auto func = reinterpret_cast<decltype(&resolve_icall)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_resolve_icall")));
	return func(sz_text);
}

assembler::il2cpp::il2cpp_image* assembler::il2cpp::get_corlib()
{
	static const auto func = reinterpret_cast<decltype(&get_corlib)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_get_corlib")));
	return func();
}

assembler::il2cpp::il2cpp_assembly* assembler::il2cpp::image_get_assembly(il2cpp_image* img)
{
	static const auto func = reinterpret_cast<decltype(&image_get_assembly)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_image_get_assembly")));
	return func(img);
}

assembler::il2cpp::il2cpp_image* assembler::il2cpp::assembly_get_image(il2cpp_assembly* assm)
{
	static const auto func = reinterpret_cast<decltype(&assembly_get_image)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_assembly_get_image")));
	return func(assm);
}

assembler::il2cpp::il2cpp_type* assembler::il2cpp::get_type(il2cpp_string* sz_text)
{
	using func_t = il2cpp_type * (*)(il2cpp_string*);
	static const auto func = memory::get_method<func_t>(GETTYPE);
	return func(sz_text);
}

assembler::il2cpp::il2cpp_type* assembler::il2cpp::get_type(const std::wstring_view sz_text)
{
	using func_t = il2cpp_type * (*)(il2cpp_string*);
	static const auto func = memory::get_method<func_t>(GETTYPE);
	const auto ret = func(string_new(sz_text));
	return ret;
}

assembler::il2cpp::il2cpp_type* assembler::il2cpp::get_type(const std::string_view sz_text)
{
	using func_t = il2cpp_type * (*)(il2cpp_string*);
	static const auto func = memory::get_method<func_t>(GETTYPE);
	return func(string_new(sz_text));
}

std::string assembler::il2cpp::type_to_string(il2cpp_type* t)
{
	using func_t = il2cpp_string * (*)(il2cpp_type*);
	static const auto func = memory::get_method<func_t>(TYPETOSTRING);
	return s_chars(func(t));
}

assembler::il2cpp::il2cpp_type* assembler::il2cpp::class_enum_basetype(il2cpp_class* klass)
{
	static const auto func = reinterpret_cast<decltype(&class_enum_basetype)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_class_enum_basetype")));
	return func(klass);
}

assembler::il2cpp::il2cpp_type* assembler::il2cpp::class_get_type(il2cpp_class* klass)
{
	static const auto func = reinterpret_cast<decltype(&class_get_type)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_class_get_type")));
	return func(klass);
}

std::size_t assembler::il2cpp::image_get_class_count(il2cpp_image* img)
{
	static const auto func = reinterpret_cast<decltype(&image_get_class_count)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_image_get_class_count")));
	return func(img);
}

assembler::il2cpp::il2cpp_class* assembler::il2cpp::image_get_class(il2cpp_image* img, const std::size_t idx)
{
	static const auto func = reinterpret_cast<decltype(&image_get_class)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_image_get_class")));
	return func(img, idx);
}

char* assembler::il2cpp::type_get_name(il2cpp_type* t)
{
	if (!t)
		return nullptr;

	static const auto func = reinterpret_cast<decltype(&type_get_name)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_type_get_name")));
	return func(t);
}

assembler::il2cpp::il2cpp_object* assembler::il2cpp::type_get_object(il2cpp_type* t)
{
	if (!t)
		return nullptr;

	static const auto func = reinterpret_cast<decltype(&type_get_object)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_type_get_object")));
	return func(t);
}

const char* assembler::il2cpp::image_get_name(il2cpp_image* img)
{
	static const auto func = reinterpret_cast<decltype(&image_get_name)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_image_get_name")));
	return func(img);
}

assembler::il2cpp::il2cpp_image* assembler::il2cpp::class_get_image(il2cpp_class* klass)
{
	static const auto func = reinterpret_cast<decltype(&class_get_image)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_class_get_image")));
	return func(klass);
}

assembler::il2cpp::il2cpp_domain* assembler::il2cpp::current_domain()
{
	static const auto func = reinterpret_cast<decltype(&current_domain)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_domain_get")));
	return func();
}

assembler::il2cpp::il2cpp_assembly** assembler::il2cpp::domain_get_assemblies(il2cpp_domain* dom, std::size_t* size)
{
	static const auto func = reinterpret_cast<decltype(&domain_get_assemblies)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_domain_get_assemblies")));
	return func(dom, size);
}

assembler::il2cpp::il2cpp_assembly* assembler::il2cpp::domain_assembly_open(il2cpp_domain* dom, const char* sz_text)
{
	static const auto func = reinterpret_cast<decltype(&domain_assembly_open)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_domain_assembly_open")));
	return func(dom, sz_text);
}

void assembler::il2cpp::raise_exception(il2cpp_exception* e)
{
	static const auto func = reinterpret_cast<decltype(&raise_exception)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_raise_exception")));
	func(e);
}

assembler::il2cpp::il2cpp_exception* assembler::il2cpp::exception_from_name_msg(il2cpp_image* img, const char* sz_namespace, const char* sz_name, const char* sz_message)
{
	static const auto func = reinterpret_cast<decltype(&exception_from_name_msg)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_exception_from_name_msg")));
	return func(img, sz_namespace, sz_name, sz_message);
}

assembler::il2cpp::il2cpp_exception* assembler::il2cpp::get_exception_argument_null(const char* sz_arg)
{
	static const auto func = reinterpret_cast<decltype(&get_exception_argument_null)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_get_exception_argument_null")));
	return func(sz_arg);
}

void assembler::il2cpp::gc_collect(const std::int32_t generations)
{
	static const auto func = reinterpret_cast<decltype(&gc_collect)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_gc_collect")));
	return func(generations);
}

std::int64_t assembler::il2cpp::gc_get_used_size()
{
	static const auto func = reinterpret_cast<decltype(&gc_get_used_size)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_gc_get_used_size")));
	return func();
}

std::int64_t assembler::il2cpp::gc_get_heap_size()
{
	static const auto func = reinterpret_cast<decltype(&gc_get_heap_size)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_gc_get_heap_size")));
	return func();
}

assembler::il2cpp::field_info* assembler::il2cpp::get_field_by_index(il2cpp_class* klass, const std::size_t idx)
{
	if (idx == 0)
		return nullptr;

	std::size_t i = 0;
	void* iter = nullptr;

	while (const auto field = get_fields(klass, &iter))
	{
		++i;

		if (i == idx)
			return field;
	}

	return nullptr;
}

void assembler::il2cpp::field_static_set_value(field_info* field, void* value)
{
	static const auto func = reinterpret_cast<decltype(&field_static_set_value)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_field_static_set_value")));
	func(field, value);
}

void assembler::il2cpp::field_static_get_value(field_info* field, void* value)
{
	static const auto func = reinterpret_cast<decltype(&field_static_get_value)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_field_static_get_value")));
	func(field, value);
}

assembler::il2cpp::field_info* assembler::il2cpp::class_get_field_from_name(il2cpp_object* obj, const char* sz_text)
{
	il2cpp_class* obj_class = object_get_class(obj);
	using func_t = field_info * (*)(il2cpp_class*, const char*);
	static const auto func = reinterpret_cast<func_t>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_class_get_field_from_name")));
	return func(obj_class, sz_text);
}

assembler::il2cpp::il2cpp_class* assembler::il2cpp::field_get_parent(field_info* field)
{
	static const auto func = reinterpret_cast<decltype(&field_get_parent)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_field_get_parent")));
	return func(field);
}

char* assembler::il2cpp::get_object_type_name(il2cpp_object* obj)
{
	if (obj == nullptr)
		return nullptr;

	return type_get_name(class_get_type(object_get_class(obj)));
}

assembler::il2cpp::il2cpp_type* assembler::il2cpp::get_object_type(il2cpp_object* obj)
{
	if (obj == nullptr)
		return nullptr;

	return class_get_type(object_get_class(obj));
}

assembler::il2cpp::il2cpp_object* assembler::il2cpp::object_new(il2cpp_class* klass)
{
	if (klass == nullptr)
		return nullptr;

	static const auto func = reinterpret_cast<decltype(&object_new)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_object_new")));
	return func(klass);
}

assembler::il2cpp::il2cpp_class* assembler::il2cpp::class_from_system_type(il2cpp_type* t)
{
	if (t == nullptr)
		return nullptr;

	static const auto func = reinterpret_cast<decltype(&class_from_system_type)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_class_from_system_type")));
	return func(t);
}

assembler::il2cpp::il2cpp_class* assembler::il2cpp::class_from_type(il2cpp_type* t)
{
	if (t == nullptr)
		return nullptr;

	static const auto func = reinterpret_cast<decltype(&class_from_type)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_class_from_il2cpp_type")));
	return func(t);
}

assembler::il2cpp::il2cpp_object* assembler::il2cpp::new_object(const std::string_view sz_text)
{
	il2cpp_type* type = get_type(sz_text);

	if (type == nullptr)
		return nullptr;

	il2cpp_class* klass = class_from_system_type(type);
	return object_new(klass);
}

assembler::il2cpp::il2cpp_object* assembler::il2cpp::new_object(il2cpp_type* type, const bool is_system_object)
{
	il2cpp_class* klass;

	if (!type)
		return nullptr;

	if (is_system_object)
		klass = class_from_system_type(type);
	else
		klass = class_from_type(type);

	if (!klass)
		return nullptr;

	return object_new(klass);
}

assembler::il2cpp::il2cpp_object* assembler::il2cpp::new_object_from_object(il2cpp_object* obj, const bool is_system_type /*= false*/)
{
	return new_object(get_object_type(obj), is_system_type);
}

assembler::il2cpp::il2cpp_object* assembler::il2cpp::new_object_from_class(il2cpp_class* obj, const bool system_type)
{
	return new_object(class_get_type(obj), system_type);
}

void* assembler::il2cpp::object_unbox(il2cpp_object* obj)
{
	static const auto func = reinterpret_cast<decltype(&object_unbox)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_object_unbox")));
	return func(obj);
}

assembler::il2cpp::il2cpp_object* assembler::il2cpp::value_box(const std::string_view sz_type, void* data)
{
	const auto klass = class_from_system_type(get_type(sz_type));

	if (klass == nullptr)
		return nullptr;

	using func_t = il2cpp_object*(*)(il2cpp_class*, void*);
	static const auto func = reinterpret_cast<func_t>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_value_box")));
	return func(klass, data);
}

assembler::il2cpp::il2cpp_object* assembler::il2cpp::value_box_not_system(const std::string_view sz_type, void* data)
{
	const auto klass = class_from_type(get_type(sz_type));

	if (klass == nullptr)
		return nullptr;

	using func_t = il2cpp_object*(*)(il2cpp_class*, void*);
	const auto func = reinterpret_cast<func_t>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_value_box")));
	return func(klass, data);
}

assembler::il2cpp::il2cpp_object* assembler::il2cpp::get_field(il2cpp_object* obj, const char* sz_text)
{
	if (obj == nullptr)
		return nullptr;

	il2cpp_class* obj_class = object_get_class(obj);
	void* iter = nullptr;

	while (const auto field = get_fields(obj_class, &iter))
	{
		const char* field_name = field_get_name(field);
		il2cpp_type* field_type = field_get_type(field);

		if (char* field_type_name = type_get_name(field_type); std::string_view(field_name) == sz_text || std::string_view(field_type_name) == sz_text)
			return field_get_value_object(field, obj);
	}

	return nullptr;
}

assembler::il2cpp::field_info* assembler::il2cpp::get_fields(il2cpp_class* klass, void** iter)
{
	using func_t = field_info * (*)(il2cpp_class*, void**);
	static const auto func = reinterpret_cast<func_t>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_class_get_fields")));
	return func(klass, iter);
}

assembler::il2cpp::il2cpp_type* assembler::il2cpp::field_get_type(field_info* field)
{
	if (field == nullptr)
		return nullptr;

	static const auto func = reinterpret_cast<decltype(&field_get_type)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_field_get_type")));
	return func(field);
}

const char* assembler::il2cpp::field_get_name(field_info* field)
{
	if (field == nullptr)
		return nullptr;

	static const auto func = reinterpret_cast<decltype(&field_get_name)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_field_get_name")));
	return func(field);
}

assembler::il2cpp::il2cpp_class* assembler::il2cpp::object_get_class(il2cpp_object* obj)
{
	if (obj == nullptr)
		return nullptr;

	static const auto func = reinterpret_cast<decltype(&object_get_class)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_object_get_class")));
	return func(obj);
}

assembler::il2cpp::property_info* assembler::il2cpp::class_get_property_from_name(il2cpp_class* klass, const char* sz_text)
{
	if (klass == nullptr)
		return nullptr;

	static const auto func = reinterpret_cast<decltype(&class_get_property_from_name)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_class_get_property_from_name")));
	return func(klass, sz_text);
}

void assembler::il2cpp::field_set_value(il2cpp_object* obj, field_info* field, void* value)
{
	if (obj == nullptr)
		return;

	static const auto func = reinterpret_cast<decltype(&field_set_value)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_field_set_value")));
	func(obj, field, value);
}

void assembler::il2cpp::field_get_value(il2cpp_object* obj, field_info* field, void* value)
{
	if (obj == nullptr)
		return;

	static const auto func = reinterpret_cast<decltype(&field_get_value)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_field_get_value")));
	func(obj, field, value);
}

assembler::il2cpp::il2cpp_object* assembler::il2cpp::field_get_value_object(field_info* field, il2cpp_object* obj)
{
	if (obj == nullptr)
		return nullptr;

	static const auto func = reinterpret_cast<decltype(&field_get_value_object)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_field_get_value_object")));
	return func(field, obj);
}

uint32_t assembler::il2cpp::object_get_size(il2cpp_object* obj)
{
	if (obj == nullptr)
		return NULL;

	static const auto func = reinterpret_cast<decltype(&object_get_size)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_object_get_size")));
	return func(obj);
}

std::uint32_t assembler::il2cpp::array_get_byte_length(il2cpp_array* arr)
{
	if (arr == nullptr)
		return NULL;

	static const auto func = reinterpret_cast<decltype(&array_get_byte_length)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_array_get_byte_length")));
	return func(arr);
}

void assembler::il2cpp::array_clear(il2cpp_array* arr, const std::size_t idx, const std::size_t len)
{
	if (!arr->max_length)
		return;

	if (idx < 0 || idx > arr->max_length || idx + len > arr->max_length)
		return;

	const auto arr_length = arr->max_length;
	const auto arr_size = array_get_byte_length(arr);
	const auto arr_elem_size = arr_length ? arr_size / arr_length : 0;
	const auto arr_obj_size = object_get_size(arr) - arr_size;

	std::memset(reinterpret_cast<std::uint8_t*>(arr) + arr_obj_size + arr_elem_size * idx, 0, arr_elem_size * len);
	arr->max_length = 0;
}

std::uint32_t assembler::il2cpp::array_length(const il2cpp_array* arr)
{
	if (arr == nullptr)
		return NULL;

	return static_cast<std::uint32_t>(arr->max_length);
}

assembler::il2cpp::il2cpp_thread* assembler::il2cpp::thread_attach(il2cpp_domain* dom)
{
	static const auto func = reinterpret_cast<decltype(&thread_attach)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_thread_attach")));
	return func(dom);
}

void assembler::il2cpp::thread_detach(il2cpp_thread* t)
{
	static const auto func = reinterpret_cast<decltype(&thread_detach)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_thread_detach")));
	return func(t);
}

void assembler::il2cpp::monitor_enter(il2cpp_object* obj)
{
	static const auto func = reinterpret_cast<decltype(&monitor_enter)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_monitor_enter")));
	func(obj);
}

void assembler::il2cpp::monitor_exit(il2cpp_object* obj)
{
	static const auto func = reinterpret_cast<decltype(&monitor_exit)>(memory::get_export_address(memory::game_assembly_handle, xorstr_("il2cpp_monitor_exit")));
	func(obj);
}

assembler::il2cpp::il2cpp_type* assembler::il2cpp::locate_type(const char* sz_text, const std::size_t idx)
{
	const auto domain = current_domain();
	const auto assem = domain_assembly_open(domain, sz_text);
	const auto core = assembly_get_image(assem);
	const auto klass = image_get_class(core, idx);
	return class_get_type(klass);
}
