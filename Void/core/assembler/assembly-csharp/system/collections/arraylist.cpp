#include "arraylist.hpp"

assembler::system_replication::collections::array_list* assembler::system_replication::collections::array_list::ctor()
{
    const auto ret = reinterpret_cast<array_list*>(il2cpp::new_object(xorstr_("System.Collections.ArrayList")));
    using func_t = void (*)(array_list*);
    static const auto func = memory::get_method<func_t>(ARRAYLIST_CTOR);
    func(ret);
    return ret;
}

std::int32_t assembler::system_replication::collections::array_list::add(il2cpp_object* value)
{
    return il2cpp::call_vfunc<std::int32_t>(this->klass, 29, this, value);
}

object_array* assembler::system_replication::collections::array_list::to_array()
{
    return il2cpp::call_vfunc<object_array*>(this->klass, 48, this);
}