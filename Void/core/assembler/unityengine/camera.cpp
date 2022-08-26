#include "camera.hpp"
#include "../common.hpp"
#include "../../../offsets.hpp"

assembler::unity_engine::camera* assembler::unity_engine::camera::get_main()
{
    if (!get_main_func_) 
        get_main_func_ = static_cast<get_main_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Camera::get_main()")));

    return get_main_func_();
}

sdk::vector assembler::unity_engine::camera::world_to_screen_point(const sdk::vector& position)
{
    if (!world_to_screen_point_func_) 
        world_to_screen_point_func_ = static_cast<world_to_screen_point_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Camera::WorldToScreenPoint_Injected(UnityEngine.Vector3&,UnityEngine.Camera/MonoOrStereoscopicEye,UnityEngine.Vector3&)")));

    auto v = sdk::vector(0, 0, 0);
    world_to_screen_point_func_(this, position, 2, &v);
    return v;
}

void assembler::unity_engine::camera::set_field_of_view(const float fov)
{
    if (!set_field_of_view_func_)
        set_field_of_view_func_ = static_cast<set_field_of_view_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Camera::set_fieldOfView(System.Single)")));

    set_field_of_view_func_(this, fov);
}

float assembler::unity_engine::camera::get_near_clip_plane()
{
    if (!get_near_clip_plane_func_)
        get_near_clip_plane_func_ = static_cast<get_near_clip_plane_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Camera::get_nearClipPlane()")));

    return get_near_clip_plane_func_(this);
}

void assembler::unity_engine::camera::set_near_clip_plane(const float val)
{
    if (!set_near_clip_plane_func_)
        set_near_clip_plane_func_ = static_cast<set_near_clip_plane_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Camera::set_nearClipPlane(System.Single)")));

    set_near_clip_plane_func_(this, val);
}
