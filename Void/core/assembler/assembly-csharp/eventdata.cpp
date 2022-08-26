#include "eventdata.hpp"
#include "../il2cpp/il2cpp.hpp"

// Namespace: ExitGames.Client.Photon
// public class EventData

assembler::il2cpp::il2cpp_object* assembler::event_data::get_custom_data()
{
	using func_t = il2cpp::il2cpp_object*(*)(event_data*);
	static const auto func = memory::get_method<func_t>(GETCUSTOMDATA);
	return func(this);
}

assembler::il2cpp::il2cpp_object* assembler::event_data::get_item(const std::uint8_t key)
{
	using func_t = il2cpp::il2cpp_object* (*)(event_data*, std::uint8_t);
	static const auto func = memory::get_method<func_t>(GETITEM);
	return func(this, key);
}