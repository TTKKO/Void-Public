#include "texture.hpp"

void assembler::unity_engine::texture::set_wrap_mode(const int32_t value)
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] set_wrap_mode passed nullptr.\n"));
        logging::pop();
        return;
    }
    if (!set_wrap_mode_func_) set_wrap_mode_func_ = static_cast<set_wrap_mode_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.Texture::set_wrapMode(UnityEngine.TextureWrapMode)")));
    set_wrap_mode_func_(this, value);
}

int32_t assembler::unity_engine::texture::get_width()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_width passed nullptr.\n"));
        logging::pop();
        return NULL;
    }
    if (!get_width_func_) get_width_func_ = static_cast<get_width_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.Texture::GetDataWidth()")));
    return get_width_func_(this);
}

int32_t assembler::unity_engine::texture::get_height()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_height passed nullptr.\n"));
        logging::pop();
        return NULL;
    }
    if (!get_height_func_) get_height_func_ = static_cast<get_height_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.Texture::GetDataHeight()")));
    return get_height_func_(this);
}
