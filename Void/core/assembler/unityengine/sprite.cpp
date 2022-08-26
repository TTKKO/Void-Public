#include "sprite.hpp"

assembler::unity_engine::ui::sprite* assembler::unity_engine::ui::sprite::create(texture_2d* texture, const rect& rect, const sdk::vector_2d& pivot, const float thing, const std::uint32_t wtf, const sprite_mesh_type type, const sdk::vector_4d& box, const bool aids)
{
	if (!create_func_)
		create_func_ = static_cast<create_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Sprite::CreateSprite_Injected(UnityEngine.Texture2D,UnityEngine.Rect&,UnityEngine.Vector2&,System.Single,System.UInt32,UnityEngine.SpriteMeshType,UnityEngine.Vector4&,System.Boolean)")));

	return create_func_(texture, rect, pivot, thing, wtf, type, box, aids);
}

assembler::unity_engine::ui::sprite* assembler::unity_engine::ui::sprite::create_custom(const std::int32_t width, const std::int32_t height, ID3D11ShaderResourceView* dx_texture)
{
	const auto tex = texture_2d::create_external_texture(width, height, texture_2d::texture_format::argb32, true, false, dx_texture);

	const auto rect = unity_engine::rect(0.f, 0.f, static_cast<float>(width), static_cast<float>(height));

	const static auto pivot = sdk::vector_2d();
	const static auto border = sdk::vector_4d();

	return create(tex, rect, pivot, 100.f, 0, tight, border, false);
}
