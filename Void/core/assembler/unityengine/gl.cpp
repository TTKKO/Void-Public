#include "gl.hpp"

void assembler::unity_engine::gl::vertex3(const sdk::vector& vec)
{
    if (!vertex3_func_) vertex3_func_ = static_cast<vertex3_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.GL::Vertex3(System.Single,System.Single,System.Single)")));
    vertex3_func_(vec.x, vec.y, vec.z);
}

void assembler::unity_engine::gl::push_matrix()
{
    if (!push_matrix_func_) push_matrix_func_ = static_cast<push_matrix_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.GL::PushMatrix()")));
    push_matrix_func_();
}

void assembler::unity_engine::gl::pop_matrix()
{
    if (!pop_matrix_func_) pop_matrix_func_ = static_cast<pop_matrix_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.GL::PopMatrix()")));
    pop_matrix_func_();
}

void assembler::unity_engine::gl::load_ortho()
{
    if (!load_ortho_func_) load_ortho_func_ = static_cast<load_ortho_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.GL::LoadOrtho()")));
    load_ortho_func_();
}

void assembler::unity_engine::gl::begin(const int32_t mode)
{
    if (!begin_func_) begin_func_ = static_cast<begin_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.GL::Begin(System.Int32)")));
    begin_func_(mode);
}

void assembler::unity_engine::gl::color(const sdk::color& c)
{
    if (!color_func_) color_func_ = static_cast<color_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.GL::ImmediateColor(System.Single,System.Single,System.Single,System.Single)")));
    color_func_(c.base_alpha());
}

void assembler::unity_engine::gl::end()
{
    if (!end_func_) end_func_ = static_cast<end_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.GL::End()")));
    end_func_();
}
