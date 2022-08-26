#include "transform.hpp"
#include "../../../utilities/ingame_logging.hpp"

assembler::il2cpp::il2cpp_type* assembler::unity_engine::transform::get_global_type()
{
    if (!type_)
        type_ = il2cpp::get_type(xorstr_("UnityEngine.Transform, UnityEngine.CoreModule"));

    return type_;
}

void assembler::unity_engine::transform::set_rotation(const sdk::quaternion& value)
{
    if (!set_rotation_func_) 
        set_rotation_func_ = static_cast<set_rotation_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Transform::set_rotation_Injected(UnityEngine.Quaternion&)")));

    set_rotation_func_(this, value);
}

sdk::quaternion assembler::unity_engine::transform::get_rotation()
{
    auto q = sdk::quaternion();

    if (!get_rotation_func_) 
        get_rotation_func_ = static_cast<get_rotation_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Transform::get_rotation_Injected(UnityEngine.Quaternion&)")));

    get_rotation_func_(this, &q);
    return q;
}

assembler::unity_engine::transform* assembler::unity_engine::transform::find(il2cpp::il2cpp_string* str)
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] find passed nullptr.\n"));
        logging::pop();
        return nullptr;
    }
    if (!find_func_) find_func_ = static_cast<find_t>(il2cpp::resolve_icall(xorstr_(
        "UnityEngine.Transform::FindRelativeTransformWithPath(UnityEngine.Transform,System.String,System.Boolean)")));
    return find_func_(this, str, false);
}

void assembler::unity_engine::transform::set_parent(transform* parent, const bool world_position_stays)
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] set_parent passed nullptr.\n"));
        logging::pop();
        return;
    }
    if (!set_parent_func_) set_parent_func_ = static_cast<set_parent_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.Transform::SetParent(UnityEngine.Transform,System.Boolean)")));
    set_parent_func_(this, parent, world_position_stays);
}

void assembler::unity_engine::transform::set_local_position(const sdk::vector& value)
{
    if (this == nullptr) return;
    if (!set_local_position_func_) set_local_position_func_ = static_cast<set_local_position_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.Transform::set_localPosition_Injected(UnityEngine.Vector3&)")));
    set_local_position_func_(this, value);
}

sdk::vector assembler::unity_engine::transform::get_local_position()
{
    auto v = sdk::vector(0, 0, 0);

    if (!get_local_position_func_) 
        get_local_position_func_ = static_cast<get_local_position_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Transform::get_localPosition_Injected(UnityEngine.Vector3&)")));

    get_local_position_func_(this, &v);
    return v;
}

void assembler::unity_engine::transform::set_local_scale(const sdk::vector& value)
{
    if (!set_local_scale_func_) 
        set_local_scale_func_ = static_cast<set_local_scale_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Transform::set_localScale_Injected(UnityEngine.Vector3&)")));

	set_local_scale_func_(this, value);
}

sdk::vector assembler::unity_engine::transform::get_local_scale()
{
    auto v = sdk::vector(0, 0, 0);

    if (!get_local_scale_func_) 
        get_local_scale_func_ = static_cast<get_local_scale_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Transform::get_localScale_Injected(UnityEngine.Vector3&)")));

    get_local_scale_func_(this, &v);
    return v;
}

void assembler::unity_engine::transform::set_local_rotation(const sdk::quaternion& q)
{
    if (!set_local_rotation_func_)
        set_local_rotation_func_ = static_cast<set_local_rotation_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Transform::set_localRotation_Injected(UnityEngine.Quaternion&)")));

    set_local_rotation_func_(this, q);
}

sdk::quaternion assembler::unity_engine::transform::get_local_rotation()
{
    auto q = sdk::quaternion{};

    if (!get_local_rotation_func_)
        get_local_rotation_func_ = static_cast<get_local_rotation_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Transform::get_localRotation_Injected(UnityEngine.Quaternion&)")));

    get_local_rotation_func_(this, &q);
    return q;
}

sdk::vector assembler::unity_engine::transform::inverse_transform_point(const sdk::vector& value)
{
    auto v = sdk::vector{};

    if (!inverse_transform_point_func_)
        inverse_transform_point_func_ = static_cast<inverse_transform_point_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Transform::InverseTransformPoint_Injected(UnityEngine.Vector3&,UnityEngine.Vector3&)")));

    inverse_transform_point_func_(this, value, &v);
    return v;
}

assembler::unity_engine::transform* assembler::unity_engine::transform::get_child(const int index)
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_child passed nullptr.\n"));
        logging::pop();
        return nullptr;
    }

    if (!get_child_func_) get_child_func_ = static_cast<get_child_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.Transform::GetChild(System.Int32)")));
    return get_child_func_(this, index);
}

assembler::unity_engine::transform* assembler::unity_engine::transform::get_root()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_root passed nullptr.\n"));
        logging::pop();
        return nullptr;
    }

    if (!get_root_func_) get_root_func_ = static_cast<get_root_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.Transform::GetRoot()")));
    return get_root_func_(this);
}

int assembler::unity_engine::transform::child_count()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] child_count passed nullptr.\n"));
        logging::pop();
        return NULL;
    }

    if (!child_count_func_) 
        child_count_func_ = static_cast<child_count_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Transform::get_childCount()")));

    return child_count_func_(this);
}

void assembler::unity_engine::transform::get_all_children()
{
    const std::size_t child_count = this->child_count();

    std::string text;

    for (std::size_t i = 0; i < child_count; i++)
        text += xorstr_("-");

    std::cout << text << xorstr_(" ") << this->get_name() << std::endl;

    for (size_t i = 0; i < child_count; i++)
    {
        get_all_children(this->get_child(static_cast<int>(i)));
    }
}

void assembler::unity_engine::transform::get_all_children(transform* transform)
{
    int i = 0;
    transform->get_all_children();
}

assembler::unity_engine::object* assembler::unity_engine::transform::get_component_in_children_z(const std::string_view type)
{
    const int child_count = this->child_count();


    if (get_component(type) != nullptr)
    {
        return get_component(type);
    }
    std::string text;

    for (std::size_t i = 0; i < child_count; i++)
        text += xorstr_("-");

    std::cout << text << " " << this->get_name() << std::endl;

    for (std::size_t i = 0; i < child_count; i++)
    {
        this->get_child(static_cast<std::int32_t>(i))->get_component_in_children_z(type);
    }
    return nullptr;
}


sdk::vector assembler::unity_engine::transform::get_forward()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_forward passed nullptr.\n"));
        logging::pop();
        return sdk::vector{};
    }

    using func_t = sdk::vector(*)(transform*);
    const auto func = memory::get_method<func_t>(GET_FORWARD);
    return func(this);
}

sdk::vector assembler::unity_engine::transform::get_right()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_right passed nullptr.\n"));
        logging::pop();
        return sdk::vector{};
    }

    using func_t = sdk::vector(*)(transform*);
    const auto func = memory::get_method<func_t>(GET_RIGHT);
    return func(this);
}

sdk::vector assembler::unity_engine::transform::get_up()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_up passed nullptr.\n"));
        logging::pop();
        return sdk::vector{};
    }

    using func_t = sdk::vector(*)(transform*);
    const auto func = memory::get_method<func_t>(GET_UP);
    return func(this);
}

sdk::vector assembler::unity_engine::transform::get_position()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_position passed nullptr.\n"));
        logging::pop();
        return sdk::vector{};
    }

    if (!get_position_func_) get_position_func_ = static_cast<get_position_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.Transform::get_position_Injected(UnityEngine.Vector3&)")));

    sdk::vector v;
    get_position_func_(this, &v);
    return v;
}

void assembler::unity_engine::transform::set_position(const sdk::vector& value)
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] set_position passed nullptr.\n"));
        logging::pop();
        return;
    }

    if (!set_position_func_) set_position_func_ = static_cast<set_position_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.Transform::set_position_Injected(UnityEngine.Vector3&)")));
    set_position_func_(this, value);
}

void assembler::unity_engine::transform::rotate(const sdk::vector& eulers, const std::int32_t relative_to)
{
	auto q = sdk::quaternion::from_eulerangles(eulers);

    if (relative_to == 1) 
    {
        q *= this->get_local_rotation();
        this->set_local_rotation(q);
    }

    else
    {
        logging::push(FOREGROUND_INTENSE_RED);
        logging::print(xorstr_("[assembler] relative not supported.\n"));
        logging::pop();
    }
}

void assembler::unity_engine::transform::set_parent(transform* to)
{
    if (!set_parent_func_) set_parent_func_ = static_cast<set_parent_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.Transform::SetParent(UnityEngine.Transform,System.Boolean)")));
    set_parent_func_(this, to, false);
}

assembler::unity_engine::transform* assembler::unity_engine::transform::get_parent()
{
    if (!get_parent_func_) get_parent_func_ = static_cast<get_parent_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.Transform::GetParent()")));
    return get_parent_func_(this);
}

assembler::unity_engine::transform* assembler::unity_engine::transform::find(const std::string_view str)
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] find passed nullptr.\n"));
        logging::pop();
        return nullptr;
    }
    if (!find_func_) 
        find_func_ = static_cast<find_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Transform::FindRelativeTransformWithPath(UnityEngine.Transform,System.String,System.Boolean)")));

    return find_func_(this, il2cpp::string_new(str), false);
}
