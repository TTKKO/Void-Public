#include "vrcuipage.hpp"
#include "../il2cpp/il2cpp.hpp"
#include "../assembly-csharp/vrcuimanager.hpp"

assembler::il2cpp::il2cpp_type* assembler::vrc_ui_page::get_type()
{
    // @xref: public string whatthefuck; // 0x18
    // @xref: public bool whatthefuck; // 0x20
    // @xref: public bool whatthefuck; // 0x21
    // @xref: private List<whatthefuck> whatthefuck; // 0x30
    // @xref: private bool whatthefuck; // 0x38
    // @xref: private whatthefuck whatthefuck; // 0x40
    // @xref: private bool whatthefuck; // 0x48
    // @xref: protected whatthefuck whatthefuck; // 0x50
    // @xref: public static float whatthefuck; // 0x0
    // @xref: public static Ease whatthefuck; // 0x4
    // @xref: public static Ease whatthefuck; // 0x8
    // @xref: protected Sequence ǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅ; // 0x58

    if (!type_)
        type_ = il2cpp::get_type(xorstr_(L"ÏÎÏÏÍÍÌÌÏÍÌÌÏÍÏÌÍÌÎÌÎÏÏ, VRC.UI.Elements.dll"));
        //type_ = reinterpret_cast<il2cpp::il2cpp_type*>(type_get_object(il2cpp::locate_type(xorstr_("VRC.UI.Elements.dll"), 58)));

    return type_;
}

assembler::vrc_ui_page* assembler::vrc_ui_page::get_page(const std::string_view path)
{
    using func_t = vrc_ui_page * (*)(vrc_ui_manager*, il2cpp::il2cpp_string*);
    static const auto func = memory::get_method<func_t>(GETVRCUIPAGE);
    return func(vrc_ui_manager::instance(), il2cpp::string_new(path));
}

void assembler::vrc_ui_page::set_name(const std::string_view name)
{
    *reinterpret_cast<il2cpp::il2cpp_string**>(reinterpret_cast<std::uint8_t*>(this) + 0x18) = il2cpp::string_new(name);
}
