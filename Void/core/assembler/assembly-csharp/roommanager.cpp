#include "roommanager.hpp"
#include "../il2cpp/il2cpp.hpp"

assembler::room_manager_c* assembler::room_manager::get_class()
{
    return reinterpret_cast<room_manager_c*>(class_from_system_type(get_type()));
}

assembler::il2cpp::il2cpp_type* assembler::room_manager::get_type()
{
    // @xref: private static bool whatthefuck; // 0x0
    // @xref: internal static ApiWorld whatthefuck; // 0x8
    // @xref: internal static ApiWorldInstance ǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅ; // 0x10
    // @xref: internal static bool whatthefuck; // 0x18

    if (!type_)
        type_ = il2cpp::get_type(xorstr_(L"ÌÍÎÌÎÎÏÏÎÌÌÏÌÏÏÍÍÍÍÌÍÎÍ, Assembly-CSharp.dll"));
        //type_ = reinterpret_cast<il2cpp::il2cpp_type*>(type_get_object(il2cpp::locate_type(xorstr_("Assembly-CSharp.dll"), 775)));

    return type_;
}

assembler::room_manager* assembler::room_manager::get_new()
{
    return reinterpret_cast<room_manager*>(new_object(get_type(), true));
}

std::string assembler::room_manager::get_room_id()
{
    using func_t = il2cpp::il2cpp_string* (*)();
    static const auto func = memory::get_method<func_t>(GETROOMID);
    return s_chars(func());
}