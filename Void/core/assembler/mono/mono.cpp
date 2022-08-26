#include "mono.hpp"

assembler::mono::mono_domain* assembler::mono::get_root_domain()
{
	using func_t = mono_domain* (*)();
	static const auto func = reinterpret_cast<func_t>(memory::get_export_address(memory::mono_handle, xorstr_("mono_get_root_domain")));
	return func();
}

assembler::mono::mono_image* assembler::mono::assembly_get_image(mono_assembly* assembly)
{
	using func_t = mono_image*(*)(mono_assembly*);
	static const auto func = reinterpret_cast<func_t>(memory::get_export_address(memory::mono_handle, xorstr_("mono_assembly_get_image")));
	return func(assembly);
}

assembler::mono::mono_assembly* assembler::mono::image_get_assembly(mono_image* image)
{
	using func_t = mono_assembly * (*)(mono_image*);
	static const auto func = reinterpret_cast<func_t>(memory::get_export_address(memory::mono_handle, xorstr_("mono_image_get_assembly")));
	return func(image);
}

char* assembler::mono::image_get_name(mono_image* image)
{
	using func_t = char * (*)(mono_image*);
	static const auto func = reinterpret_cast<func_t>(memory::get_export_address(memory::mono_handle, xorstr_("mono_image_get_name")));
	return func(image);
}

std::vector<assembler::mono::mono_image*> assembler::mono::fetch_images()
{
	// VMProtectBeginUltra("Mono Fetch Images");

	if (!memory::mono_handle)
		return {};

	const auto domain = get_root_domain();
	std::vector<mono_image*> v{};

	gslist* glist;
	for (glist = domain->domain_assemblies; glist; glist = glist->next) {
		const auto assembly = static_cast<mono_assembly*>(glist->data);

		if (std::string_view(xorstr_("SerenityLoader")) == assembly->aname.name || std::string_view(xorstr_("Il2CppSystem.Runtime.Helpers")) == assembly->aname.name)
			continue;

		v.push_back(assembly_get_image(assembly));
	}

	// VMProtectEnd();
	return v;
}
