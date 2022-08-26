#include "queue.hpp"

void assembler::system_replication::collections::queue::clear()
{
	il2cpp::call_mifunc<void>(this->klass, 5, this);
}

std::int32_t assembler::system_replication::collections::queue::get_count()
{
    return il2cpp::call_mifunc<std::int32_t>(this->klass, 2, this);
}

assembler::il2cpp::il2cpp_object* assembler::system_replication::collections::queue::dequeue()
{
    return il2cpp::call_mifunc<il2cpp::il2cpp_object*>(this->klass, 11, this);
}

void assembler::system_replication::collections::queue::enqueue(il2cpp::il2cpp_object* obj)
{
	il2cpp::call_mifunc<void>(this->klass, 7, this, obj);
}
