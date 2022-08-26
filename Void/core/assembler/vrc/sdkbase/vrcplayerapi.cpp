#include "vrcplayerapi.hpp"

assembler::vrc::sdk_base::vrc_player_api* assembler::vrc::sdk_base::vrc_player_api::get_current()
{
    return networking::get_current();
}

std::int32_t assembler::vrc::sdk_base::vrc_player_api::player_id()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] player_id passed nullptr\n"));
        logging::pop();
        return NULL;
    }

    const auto del = this->klass->static_fields->get_player_id;

    return il2cpp::call_vfunc<std::int32_t>(del->klass, 12, del, this);

    //using func_t = std::int32_t(*)(vrc_player_api*);
    //static const auto func = memory::get_method<func_t>(GETPLAYERID);
    //return func(this);
}

sdk::vector assembler::vrc::sdk_base::vrc_player_api::get_position()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_position passed nullptr\n"));
        logging::pop();
        return sdk::vector{};
    }

    const auto del = this->klass->static_fields->get_position;

    return il2cpp::call_vfunc<sdk::vector>(del->klass, 12, del, this);

    //using func_t = sdk::vector(*)(vrc_player_api*);
    //static const auto func = memory::get_method<func_t>(GETPLAYERPOSITION);
    //return func(this);
}

sdk::quaternion assembler::vrc::sdk_base::vrc_player_api::get_rotation()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_rotation passed nullptr\n"));
        logging::pop();
        return sdk::quaternion{};
    }

    const auto del = this->klass->static_fields->get_rotation;

    return il2cpp::call_vfunc<sdk::quaternion>(del->klass, 12, del, this);

    //using func_t = sdk::quaternion(*)(vrc_player_api*);
    //static const auto func = memory::get_method<func_t>(GETPLAYERROTATION);
    //return func(this);
}

void assembler::vrc::sdk_base::vrc_player_api::teleport_to(vrc_player_api* who, vrc_player_api* to)
{
    if (who == nullptr || to == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] teleport_to passed nullptr\n"));
        logging::pop();
        return;
    }

    const auto del = who->klass->static_fields->teleport_to;

    il2cpp::call_vfunc<void>(del->klass, 12, del, who, to->get_position(), to->get_rotation());

    //using teleport_fn = void(*)(vrc_player_api*, const sdk::vector&, const sdk::quaternion&);
    //static const auto function = memory::get_method<teleport_fn>(TELEPORTTO);
    //function(who, to->get_position(), to->get_rotation());
}

void assembler::vrc::sdk_base::vrc_player_api::teleport_to(vrc_player_api* player)
{
    if (this == nullptr || player == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] teleport_to passed nullptr\n"));
        logging::pop();
        return;
    }

    const auto del = this->klass->static_fields->teleport_to;

    il2cpp::call_vfunc<void>(del->klass, 12, del, this, player->get_position(), player->get_rotation());

    //using teleport_fn = void(*)(vrc_player_api*, const sdk::vector&, const sdk::quaternion&);
    //static const auto function = memory::get_method<teleport_fn>(TELEPORTTO);
    //function(this, player->get_position(), player->get_rotation());
}

void assembler::vrc::sdk_base::vrc_player_api::teleport_to(const sdk::vector& position, const sdk::quaternion& rotation)
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] teleport_to passed nullptr\n"));
        logging::pop();
        return;
    }

    const auto del = this->klass->static_fields->teleport_to;

    il2cpp::call_vfunc<void>(del->klass, 12, del, this, position, rotation);

    //using teleport_fn = void(*)(vrc_player_api*, const sdk::vector&, const sdk::quaternion&);
    //static const auto function = memory::get_method<teleport_fn>(TELEPORTTO);
    //function(this, position, rotation);
}


void assembler::vrc::sdk_base::vrc_player_api::set_run_speed(const float speed)
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] set_run_speed passed nullptr\n"));
        logging::pop();
        return;
    }

    const auto del = this->klass->static_fields->set_run_speed;

    il2cpp::call_vfunc<void>(del->klass, 12, del, this, speed);

    //using func_t = void(*)(vrc_player_api*, float);
    //static const auto func = memory::get_method<func_t>(SETRUNSPEED);
    //func(this, speed);
}

void assembler::vrc::sdk_base::vrc_player_api::set_walk_speed(const float speed)
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] set_walk_speed passed nullptr\n"));
        logging::pop();
        return;
    }

    const auto del = this->klass->static_fields->set_walk_speed;

    il2cpp::call_vfunc<void>(del->klass, 12, del, this, speed);

    //using func_t = void(*)(vrc_player_api*, float);
    //static const auto func = memory::get_method<func_t>(SETWALKSPEED);
    //func(this, speed);
}

void assembler::vrc::sdk_base::vrc_player_api::set_jump_impulse(const float impulse)
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] set_jump_impulse passed nullptr\n"));
        logging::pop();
        return;
    }

    const auto del = this->klass->static_fields->set_jump_impulse;

    il2cpp::call_vfunc<void>(del->klass, 12, del, this, impulse);

    //using func_t = void(*)(vrc_player_api*, float);
    //static const auto func = memory::get_method<func_t>(SETJUMPIMPULSE);
    //func(this, impulse);
}

void assembler::vrc::sdk_base::vrc_player_api::set_name_plate_color(const sdk::color& col)
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] set_name_plate_color passed nullptr\n"));
        logging::pop();
        return;
    }

    const auto del = this->klass->static_fields->set_name_plate_color;

    il2cpp::call_vfunc<void>(del->klass, 12, del, this, col.base_alpha());

    //using func_t = void(*)(vrc_player_api*, std::array<float, 4U>);
    //static const auto func = memory::get_method<func_t>(SETNAMEPLATECOLOR);
    //func(this, col.base_alpha());
}

bool assembler::vrc::sdk_base::vrc_player_api::is_vr()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] is_vr passed nullptr\n"));
        logging::pop();
        return false;
    }

    const auto del = this->klass->static_fields->is_user_in_vr;

    return il2cpp::call_vfunc<bool>(del->klass, 12, del, this);
}

//void assembler::vrc::sdk_base::vrc_player_api::set_mute_status(const bool can_speak, const bool can_hear)
//{
//    if (this == nullptr)
//    {
//        logging::push(FOREGROUND_INTENSE_BLUE);
//        logging::print(xorstr_("[assembler] set_mute_status passed nullptr\n"));
//        logging::pop();
//        return;
//    }
//
//
//
//    using func_t = void(*)(vrc_player_api*, bool, bool);
//    static const auto func = memory::get_method<func_t>(SETMUTESTATUS);
//    func(this, can_speak, can_hear);
//}

bool assembler::vrc::sdk_base::vrc_player_api::get_is_master()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_is_master passed nullptr\n"));
        logging::pop();
        return NULL;
    }

    const auto del = this->klass->static_fields->is_master_delegate;

    return il2cpp::call_vfunc<bool>(del->klass, 12, del, this);

    //using func_t = bool(*)(vrc_player_api*);
    //static const auto func = memory::get_method<func_t>(GETISMASTERDELEGATE);
    //return func(this);
}

sdk::vector assembler::vrc::sdk_base::vrc_player_api::get_bone_position(const unity_engine::human_body_bones tt)
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_bone_position passed nullptr\n"));
        logging::pop();
        return sdk::vector{};
    }

    const auto del = this->klass->static_fields->get_bone_position;

    return il2cpp::call_vfunc<sdk::vector>(del->klass, 12, del, this, tt);

    //using func_t = sdk::vector(*)(vrc_player_api*, unity_engine::human_body_bones);
    //static const auto func = memory::get_method<func_t>(GETBONEPOSITION);
    //return func(this, tt);
}
