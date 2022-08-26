#include "networking.hpp"

bool assembler::vrc::sdk_base::networking::go_to_room(const std::string_view room_id)
{
	const auto del = global_class()->static_fields->go_to_room;

    return il2cpp::call_vfunc<bool>(del->klass, 12, del, il2cpp::string_new(room_id));
}

assembler::unity_engine::game_object* assembler::vrc::sdk_base::networking::instantiate(const std::int32_t broadcast, const std::string_view prefab_path_or_dynamic_prefab_name, const sdk::vector& position, const sdk::quaternion& rotation)
{
    try
    {
    	const auto del = global_class()->static_fields->instantiate;

        return il2cpp::call_vfunc<unity_engine::game_object*>(del->klass, 12, del, broadcast, il2cpp::string_new(prefab_path_or_dynamic_prefab_name), position, rotation);
    }
    catch (const Il2CppExceptionWrapper& e)
    {
        logging::push(FOREGROUND_INTENSE_RED);
        logging::print(xorstr_("[critical] {}\n"), s_chars(e.ex->message));
        logging::pop();
        return nullptr;
    }
}

void assembler::vrc::sdk_base::networking::rpc(const std::int32_t target_clients, unity_engine::game_object* target_object, const std::string_view method_name, object_array* parameters)
{
	const auto del = global_class()->static_fields->rpc;

    il2cpp::call_vfunc<void>(del->klass, 12, del, target_clients, target_object, il2cpp::string_new(method_name), parameters);
}

std::int32_t assembler::vrc::sdk_base::networking::get_server_time_in_milliseconds()
{
	const auto del = global_class()->static_fields->get_server_time_in_milliseconds;

    return il2cpp::call_vfunc<std::int32_t>(del->klass, 12, del);
}

assembler::il2cpp::il2cpp_array* assembler::vrc::sdk_base::networking::decode_parameters(il2cpp::il2cpp_array* arr)
{
    const auto del = global_class()->static_fields->parameter_decoder;

    return il2cpp::call_vfunc<il2cpp::il2cpp_array*>(del->klass, 12, del, arr);
}

assembler::il2cpp::il2cpp_array* assembler::vrc::sdk_base::networking::encode_parameters(il2cpp::il2cpp_array* arr)
{
    const auto del = global_class()->static_fields->parameter_encoder;

    return il2cpp::call_vfunc<il2cpp::il2cpp_array*>(del->klass, 12, del, arr);
}

void assembler::vrc::sdk_base::networking::set_owner(vrc_player_api* player, unity_engine::game_object* object)
{
    const auto del = global_class()->static_fields->set_owner;

	il2cpp::call_vfunc<void>(del->klass, 12, del, player, object);
}

bool assembler::vrc::sdk_base::networking::is_owner(unity_engine::game_object* object)
{
    const auto del = global_class()->static_fields->is_owner;

    return il2cpp::call_vfunc<bool>(del->klass, 12, del, get_current(), object);
}

assembler::vrc::sdk_base::vrc_player_api* assembler::vrc::sdk_base::networking::get_current()
{
    const auto del = global_class()->static_fields->local_player;

    return il2cpp::call_vfunc<vrc_player_api*>(del->klass, 12, del);
}

assembler::vrc::sdk_base::vrc_sdkbase_networking_c* assembler::vrc::sdk_base::networking::global_class()
{
    if (!global_class_)
        global_class_ = reinterpret_cast<vrc_sdkbase_networking_c*>(class_from_system_type(il2cpp::get_type(xorstr_("VRC.SDKBase.Networking, VRCSDKBase"))));

    return global_class_;
}

//vrcarray<object*>* assembler::vrc::sdk_base::networking::decode_parameters(vrcarray<byte>* encoded_data)
//{
//	using func_t = vrcarray<object*>*(*)(vrcarray<byte>* bytes);
//	const auto func = memory::get_method<func_t>(0x24E5700); //public static object[] DecodeParameters(byte[] encodedData) { }
//	return func(encoded_data);
//}
//
//vrcarray<byte> assembler::vrc::sdk_base::networking::encode_parameters(const vrcarray<object*> parameters)
//{
//	using func_t = vrcarray<byte>(*)(vrcarray<object*> bytes);
//	const auto func = memory::get_method<func_t>(0x24E57C0); //public static byte[] EncodeParameters(object[] parameters) { }
//	return func(parameters);
//}
