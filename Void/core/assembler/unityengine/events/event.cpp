#include "event.hpp"

#include <iostream>

#include "../../common.hpp"

void assembler::unity_engine::events::unity_event::add_listener(unity_action* call)
{
    using func_t = void (*)(unity_event*, unity_action*);
    static const auto func = memory::get_method<func_t>(ADDLISTENER);
    func(this, call);
}
