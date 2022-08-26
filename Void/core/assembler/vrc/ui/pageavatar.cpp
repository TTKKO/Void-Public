#include "pageavatar.hpp"

assembler::il2cpp::il2cpp_type* assembler::vrc::ui::page_avatar::get_type()
{
    // @xref: private static ApiAvatar <whatthefuck>k__BackingField; // 0x0
    // @xref: private static ApiAvatar <whatthefuck>k__BackingField; // 0x8
    // @xref: private static whatthefuck.whatthefuck whatthefuck; // 0x10
    // @xref: private const string ǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅ = "VRChat User";

    if (!type_)
        type_ = il2cpp::get_type(xorstr_(L"ÎÏÍÍÏÏÌÍÏÍÎÌÎÍÌÎÍÎÎÌÌÎÎ, Assembly-CSharp.dll"));

    return type_;
}

assembler::vrc::ui::page_avatar* assembler::vrc::ui::page_avatar::ctor()
{
    const auto ret = reinterpret_cast<page_avatar*>(new_object(get_type(), true));

    using func_t = page_avatar * (*)(object*);
    static const auto func = memory::get_method<func_t>(PAGEAVATARCCTOR);
    func(ret);
    return ret;
}

void assembler::vrc::ui::page_avatar::force_change(core::api_avatar* a1, const std::string_view a2, core::api_avatar* a3)
{
    using func_t = void(*)(core::api_avatar*, il2cpp::il2cpp_string*, core::api_avatar*);
    static const auto func = memory::get_method<func_t>(FORCECHANGEAVATAR);
    func(a1, il2cpp::string_new(a2), a3);
}