#include "playermanager.hpp"
#include "player.hpp"

assembler::vrc::player* assembler::vrc::player_manager::get_player(il2cpp::il2cpp_string* user_id)
{
    using func_t = player * (*)(il2cpp::il2cpp_string*);
    static const auto func = memory::get_method<func_t>(PLAYERGETPLAYER);
    return func(user_id);
}

assembler::il2cpp::il2cpp_array* assembler::vrc::player_manager::get_players()
{
    try 
    {
        using func_t = il2cpp::il2cpp_array* (*)();
        static const auto func = memory::get_method<func_t>(GETALLPLAYERS);
        return func();
    }
	catch (const Il2CppExceptionWrapper& e)
    {
        logging::push(FOREGROUND_INTENSE_RED);
        logging::print(xorstr_("[critical] {}\n"), s_chars(e.ex->message));
        logging::pop();

        return nullptr;
    }
}

float assembler::vrc::player_manager::get_distance_between(player* from, player* to)
{
	if (!from || !to)
        return 0.f;

    const auto from_transform = from->get_transform();
    const auto to_transform = to->get_transform();

    if (!from_transform || !to_transform)
        return 0.f;

    return from_transform->get_position().dist_to(to_transform->get_position());
}

assembler::vrc::player* assembler::vrc::player_manager::get_player(const std::int32_t photon_id)
{
    using func_t = player * (*)(std::int32_t);
    static const auto func = memory::get_method<func_t>(GETPLAYERBYPHOTON);
    return func(photon_id);
}

assembler::vrc::player* assembler::vrc::player_manager::get_player(const std::string_view user_id)
{
    using func_t = player * (*)(il2cpp::il2cpp_string*);
    static const auto func = memory::get_method<func_t>(PLAYERGETPLAYER);
    return func(il2cpp::string_new(user_id));
}
