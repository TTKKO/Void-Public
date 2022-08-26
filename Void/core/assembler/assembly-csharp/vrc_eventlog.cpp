#include "vrc_eventlog.hpp"

assembler::il2cpp::field_info* assembler::vrc_eventlog::static_instance_ = nullptr;

std::int32_t assembler::vrc_eventlog::event_log_entry::get_sender_id()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_sender_id passed nullptr\n"));
        logging::pop();
        return NULL;
    }

    return *reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this) + 0x18);
}

assembler::vrc_event* assembler::vrc_eventlog::event_log_entry::get_vrc_event()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_vrc_event passed nullptr\n"));
        logging::pop();
        return nullptr;
    }

    return *reinterpret_cast<vrc_event**>(reinterpret_cast<std::uint8_t*>(this) + 0x20);
}

std::string assembler::vrc_eventlog::event_log_entry::get_name()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_name passed nullptr\n"));
        logging::pop();
        return xorstr_("INVALID_STRING");
    }

    return s_chars(*reinterpret_cast<il2cpp::il2cpp_string**>(reinterpret_cast<std::uint8_t*>(this) + 0x28));
}

void assembler::vrc_eventlog::should_process_events(const bool toggle)
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] should_process_events passed nullptr\n"));
        logging::pop();
        return;
    }
    *reinterpret_cast<bool*>(reinterpret_cast<std::uint8_t*>(this) + 0x54) = toggle;
}

assembler::vrc_eventreplicator* assembler::vrc_eventlog::get_eventreplicator()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_eventreplicator passed nullptr\n"));
        logging::pop();
        return nullptr;
    }
    return *reinterpret_cast<vrc_eventreplicator**>(reinterpret_cast<std::uint8_t*>(this) + 0x58);
}

assembler::vrc_eventlog* assembler::vrc_eventlog::instance()
{
    // @xref: private const float whatthefuck = 10;
    // @xref: private const int whatthefuck = 3;
    // @xref: public float whatthefuck; // 0x50
    // @xref: public bool whatthefuck; // 0x54
    // @xref: internal whatthefuck.whatthefuck whatthefuck; // 0x58
    // @xref: internal whatthefuck whatthefuck; // 0x60
    // @xref: internal List<ǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅ.ǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅ> ǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅǅ; // 0x68
    // @xref: internal static whatthefuck whatthefuck; // 0x0
    // @xref: private ProfilerMarker whatthefuck; // 0x78
    // @xref: private ProfilerMarker whatthefuck; // 0x80

    if (!static_instance_) 
        static_instance_ = get_field_by_index(class_from_system_type(il2cpp::get_type(xorstr_(L"ÎÏÌÌÍÌÏÍÏÏÏÎÎÎÏÎÌÍÍÎÌÏÍ, Assembly-CSharp.dll"))), 8);

    vrc_eventlog* instance;
    field_static_get_value(static_instance_, &instance);

    if (!instance) 
        return nullptr;

    return instance;
}
