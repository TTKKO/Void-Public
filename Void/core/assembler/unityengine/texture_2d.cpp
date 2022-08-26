#include "texture_2d.hpp"

void assembler::unity_engine::texture_2d::set_pixel(const int32_t x, const int32_t y, const sdk::color& c)
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] set_pixel passed nullptr.\n"));
        logging::pop();
        return;
    }
    if (!set_pixel_func_) 
        set_pixel_func_ = static_cast<set_pixel_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Texture2D::SetPixelImpl_Injected(System.Int32,System.Int32,System.Int32,UnityEngine.Color&)")));
    set_pixel_func_(this, 0, x, y, c.base_alpha());
}

void assembler::unity_engine::texture_2d::apply()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] apply passed nullptr.\n"));
        logging::pop();
        return;
    }
    if (!apply_func_) apply_func_ = static_cast<apply_t>(il2cpp::resolve_icall(
        xorstr_("UnityEngine.Texture2D::ApplyImpl(System.Boolean,System.Boolean)")));
    apply_func_(this, true, false);
}

bool assembler::unity_engine::texture_2d::load_image(il2cpp::il2cpp_array* arr)
{
    if (!load_image_func_) 
        load_image_func_ = static_cast<load_image_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.ImageConversion::LoadImage(UnityEngine.Texture2D,System.Byte[],System.Boolean)")));

    return load_image_func_(this, arr, false);
}

assembler::il2cpp::il2cpp_type* assembler::unity_engine::texture_2d::get_global_type()
{
    if (!type_)
        type_ = il2cpp::get_type(xorstr_("UnityEngine.Texture2D, UnityEngine.CoreModule"));

    return type_;
}

assembler::unity_engine::texture_2d* assembler::unity_engine::texture_2d::create_external_texture(const std::int32_t width, const std::int32_t height, const texture_format format, const bool mip_chain, const bool linear, ID3D11ShaderResourceView* texture)
{
    using func_t = texture_2d * (*)(std::int32_t, std::int32_t, texture_format, bool, bool, ID3D11ShaderResourceView*);
    static const auto func = memory::get_method<func_t>(CREATEEXTERNALTEXTURE);
    return func(width, height, format, mip_chain, linear, texture);
}
