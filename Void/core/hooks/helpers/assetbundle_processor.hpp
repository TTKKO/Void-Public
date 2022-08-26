#ifndef ASSETBUNDLE_PROCESSOR_HPP
#define ASSETBUNDLE_PROCESSOR_HPP

#pragma once
#include <unordered_set>
#include "../../assembler/unityengine/transform.hpp"
#include "../../assembler/unityengine/skinnedmeshrenderer.hpp"
#include "../../assembler/unityengine/spherecollider.hpp"
#include "../../assembler/unityengine/boxcollider.hpp"
#include "../../assembler/unityengine/capsulecollider.hpp"
#include "../../assembler/unityengine/cloth.hpp"
#include "../../assembler/unityengine/meshfilter.hpp"
#include "../../assembler/unityengine/meshrenderer.hpp"
#include "../../assembler/unityengine/mesh.hpp"
#include "../../assembler/unityengine/trailrenderer.hpp"
#include "../../assembler/unityengine/linerenderer.hpp"
#include "../../assembler/unityengine/particle_system.hpp"
#include "../../assembler/unityengine/particlesystemrenderer.hpp"
#include "../../assembler/unityengine/animation.hpp"
#include "../../assembler/unityengine/springjoint.hpp"
#include "../../assembler/unityengine/shader.hpp"
#include "../../assembler/unityengine/material.hpp"

namespace helpers
{
	class assetbundle_processor
	{
		inline static const std::wregex poiyomi_regex = std::wregex(xorstr_(LR"((?:hidden\/(locked\/|))?(\.|)poiyomi(\/poiyomi [.0-9]+)?\/(\s|•|★|\?|)+poiyomi (pro|toon|outline)(\s|•|★|\?|)+(?:\/[a-z0-9\s\.\d-_\+\!\@\#\$\%\,\^\&\*\(\)=\]\[]+)?)"));
		inline static const std::unordered_set<std::wstring> shader_whitelist = {
			xorstr_(L"doppels shaders/dope toon shader"),
			xorstr_(L"magic3000/vertexmove"),
			xorstr_(L"mochie/mochie's screen fx"),
			xorstr_(L"doppels shaders/screenfx/dope shader 2.19"),
			xorstr_(L"mobile/unlit (supports lightmap)"),
			xorstr_(L".poiyomi/toon/cutout"),
			xorstr_(L"xiexe/toon2.0/xstoon2.0"),
			xorstr_(L"unitychantoonshader/mobile/toon_shadinggrademap"),
			xorstr_(L".poiyomi/toon/opaque"),
			xorstr_(L".poiyomi/master/opaque"),
			xorstr_(L"unitychantoonshader/toon_doubleshadewithfeather"),
			xorstr_(L"mms3/mnmrshader3"),
			xorstr_(L".poiyomi/slim/basic opaque"),
			xorstr_(L"noenoe/noenoe toon shader/noenoe toon opaque"),
			xorstr_(L"sprites/glitch3"),
			xorstr_(L"snail/marker"),
			xorstr_(L"doppels shaders/metallicfx v5.0"),
			xorstr_(L"ysht shaders/pbtshader"),
			xorstr_(L"shader forge/doublesidedspec"),
			xorstr_(L"silent's cel shading/opaque"),
			xorstr_(L"liltoon"),
			xorstr_(L"unitychantoonshader/toon_shadinggrademap"),
			xorstr_(L"unitychantoonshader/toon_doubleshadewithfeather_transclipping"),
			xorstr_(L"shader forge/crystal shader"),
			xorstr_(L"cubedparadox/flat lit toon"),
			xorstr_(L"unlitwf/wf_gem_opaque"),
			xorstr_(L"hidden/liltoontransparent"),
			xorstr_(L"unlitwf/wf_fakefur_transparent"),
			xorstr_(L"magic3000/screenspace"),
			xorstr_(L"raliv/penetrator"),
			xorstr_(L"hidden/internalerrorshader"),
			xorstr_(L".poiyomi/toon/advanced/cutout"),
			xorstr_(L"silent's cel shading/opaque"),
			xorstr_(L"raliv/penetrator"),
			xorstr_(L"kriptofx/rfx4/lava"),
			xorstr_(L".poiyomi/toon/advanced/outlines cutout"),
			xorstr_(L"arktoon/opaque"),
			xorstr_(L"silent's cel shading/lightramp (outline)"),
			xorstr_(L"silent's cel shading/lightramp"),
			xorstr_(L"leviant's shaders/ubershader v2.9"),
			xorstr_(L"kyuubical/hfhd"),
			xorstr_(L"arktoon/alphacutout"),
			xorstr_(L".poiyomi/pro/cutout"),
			xorstr_(L"skuld/skuld's marker"),
			xorstr_(L"custom/avatar shaders/poiyomi's shader/toon/cutout"),
			xorstr_(L".poiyomi/toon/default/cutout"),
			xorstr_(L"_shaders/rainbow"),
			xorstr_(L"ciconia studio/double sided/emissive/diffuse"),
			xorstr_(L"hidden/liltoontransparentoutline"),
			xorstr_(L"hidden/liltoonoutline"),
			xorstr_(L"custom/cottonfoxhsv"),
			xorstr_(L"unitychantoonshader/toon_shadinggrademap_transclipping"),
			xorstr_(L"unitychantoonshader/toon_doubleshadewithfeather_clipping"),
			xorstr_(L".poiyomi/pro/opaque"),
			xorstr_(L"custom/invisible"),
			xorstr_(L"karekitsune/karekitsune_effect"),
			xorstr_(L"kriptofx/rfx4/particle"),
			xorstr_(L"sine vfx/startspherev5"),
			xorstr_(L"kriptofx/rfx4/distortion"),
			xorstr_(L"kriptofx/me/particle"),
			xorstr_(L"arktoon/faderefracted"),
			xorstr_(L"arktoon/faderefracted"),
			xorstr_(L".poiyomi/toon/outlines cutout"),
			xorstr_(L".loli_explorer.exe/eye shader"),
			xorstr_(L"gap/additivemobiledistortionscroll"),
			xorstr_(L"doppels shaders/toon/dope toon cutout 1.31"),
			xorstr_(L"doppels shaders/metallicfx v5.11"),
			xorstr_(L"doppels shaders/toon/dope toon 1.4.0"),
			xorstr_(L"doppels shaders/rainbow rim"),
			xorstr_(L"doppels shaders/models shaders/metallicfx 6.0.0"),
			xorstr_(L"doppels shaders/distortion wave 3d v 1.1"),
			xorstr_(L"particles/particles rfx4"),
			xorstr_(L"doppels shaders/cross texture"),
			xorstr_(L"particles/additive intensify"),
			xorstr_(L"sine vfx/startspherev5"),
			xorstr_(L"rollthered/fire"),
			xorstr_(L"glass-ish_shader"),
			xorstr_(L"raliv/processing"),
			xorstr_(L"unlitwf/wf_fakefur_mix"),
			xorstr_(L"doppels shaders/metallicfx cutout v5.11"),
			xorstr_(L"hirabiki/vrclens/depthoffield cutout"),
			xorstr_(L"hirabiki/vrclens/screenspace aux cutout"),
			xorstr_(L"hirabiki/vrclens/mesh preview"),
			xorstr_(L"hirabiki/vrclens/screenspace auxfocus cutout"),
			xorstr_(L"hirabiki/vrclens/pivot indicator"),
			xorstr_(L"leviant's shaders/viewspacerender unlit alpha"),
			xorstr_(L"doppels shaders/screenfx/dope shader 2.2.2"),
			xorstr_(L"arktoon+t/opaque"),
			xorstr_(L"pidi shaders collection/xfur system/standard/high quality/twenty four samples"),
			xorstr_(L"doppels shaders/metallicfx v5.0"),
			xorstr_(L"zfs shaders/zfs_3d_pro"),
			xorstr_(L"vrlabs/particle shader"),
			xorstr_(L".rero/particle/litprojectivedissolve(particle)"),
			xorstr_(L".rero/rero standard/rero standard (metallic setup)"),
			xorstr_(L".poiyomi/toon/transparent"),
			xorstr_(L"leviant's shaders/viewspacerender unlit alpha overrender"),
			xorstr_(L"doppels shaders/screenfx/screen space texture 1.01"),
			xorstr_(L"!mai lofi!/mai glass!"),
			xorstr_(L"custom/object shaders/moving gems shader"),
			xorstr_(L"custom/multi-shader/screenspacepub + stencil"),
			xorstr_(L"custom/object shaders/wireframe shader - ztest"),
			xorstr_(L"custom/misc/point particles"),
			xorstr_(L"custom/screen/neon shader"),
			xorstr_(L"custom/text shader emotes"),
			xorstr_(L"corpse/uber particle v1.5"),
			xorstr_(L"quantum/gpu particles/simulator"),
			xorstr_(L"arktoon/fade"),
			xorstr_(L"xiexe/xsfur"),
			xorstr_(L".poiyomi/toon/advanced/opaque"),
			xorstr_(L"xiexe/toon2.0/xstoon2.0_penetrator"),
			xorstr_(L"raliv/orifice"),
			xorstr_(L"raivo/particles/mesh_glow"),
			xorstr_(L"raivo/particles/animated rimlight"),
			xorstr_(L"amibeingtouched"),
			xorstr_(L"yukio's shaders/fur shader [low]"),
			xorstr_(L"shaderboy/invisible shader v2"),
			xorstr_(L"fx/flare"),
			xorstr_(L"silent's cel shading/crosstone"),
			xorstr_(L"unlit/fallback"),
			xorstr_(L".poiyomi/toon/advanced/transparent"),
			xorstr_(L"unitychantoonshader/angelring/toon_shadinggrademap_transclipping"),
			xorstr_(L".rero/rero standard/rero standard (specular setup)"),
			xorstr_(L"noenoe/noenoe toon shader/noenoe toon outline"),
			xorstr_(L"particles/additive"),
			xorstr_(L".poiyomi/toon/simple/cutout"),
			xorstr_(L"doppels shaders/models shaders/metallicfx 6.0.1"),
			xorstr_(L"unlit/transparent cutout"),
			xorstr_(L".poiyomi/toon/advanced/outlines transparent"),
			xorstr_(L"noenoe/noenoe toon shader/noenoe toon outline outer only"),
			xorstr_(L".poiyomi/toon/simple/transparent"),
			xorstr_(L"custom/runes"),
			xorstr_(L"ega/particles/firesphere"),
			xorstr_(L"raivo/particles/alphablend particle"),
			xorstr_(L".sendo/toon/test sendols toon beta v1.1"),
			xorstr_(L"corpse/connecting loop v1.2"),
			xorstr_(L"hotate/himo/memory_reset"),
			xorstr_(L"hotate/himo/memory_hider"),
			xorstr_(L"hotate/himo/vpass"),
			xorstr_(L"xiexe/toon3/xstoon3_fur"),
			xorstr_(L"unlit/color"),
			xorstr_(L"!jaygamer/pack-o-punch shader"),
			xorstr_(L"hidden/liltoonfur"),
			xorstr_(L"unitychantoonshader/nooutline/tooncolor_shadinggrademap"),
			xorstr_(L".poiyomi/toon/outlines transparent"),
			xorstr_(L"cubedparadox/unit shadowed"),
			xorstr_(L"doppels shaders/fx/screenspace hud 1.1"),
			xorstr_(L"doppels shaders/models shaders/burning glasses 1.11"),
			xorstr_(L"doppels shaders/toon/dope toon 1.4.2"),
			xorstr_(L"doppels shaders/fx/screenspace hud 1.1"),
			xorstr_(L"doppels shaders/models shaders/anime stylized eyes"),
			xorstr_(L"temmie/toon"),
			xorstr_(L"doppels shaders/models shaders/cross eye shader"),
			xorstr_(L"vrlabs/ragdoll system/invisible"),
			xorstr_(L"unitychantoonshader/angelring/toon_shadinggrademap"),
			xorstr_(L"mochie/particles"),
			xorstr_(L".poiyomi/patreon/particle2/cutout"),
			xorstr_(L"sunao shader/opaque"),
			xorstr_(L"sunao shader/[stencil outline]/opaque"),
			xorstr_(L".rero/rero standard/rero standard"),
			xorstr_(L"fur/furrimcolorshader"),
			xorstr_(L"!m.o.o.n/marker"),
			xorstr_(L"kriptofx/rfx4/decal/distortmaskmobile"),
			xorstr_(L"kriptofx/rfx4/distortionparticlesadditive"),
			xorstr_(L"tearstop"),
			xorstr_(L"tearsbottom"),
			xorstr_(L"sine vfx/v3dlasers/blackholecore"),
			xorstr_(L"sine vfx/v3dlasers/flarecustom"),
			xorstr_(L".meritaa/alpha blended"),
			xorstr_(L"custom/advancedgemshader/metallic"),
			xorstr_(L"shader forge/double lighted"),
			xorstr_(L"silent's cel shading/crosstone (outline)"),
			xorstr_(L".poiyomi/toon/default/opaque"),
			xorstr_(L"sunao shader/opaque"),
			xorstr_(L"arktoon/_extra/emissivefreak/opaque"),
			xorstr_(L"raivo/particles/watershader"),
			xorstr_(L"magic3000/screenspacepub"),
			xorstr_(L"riot/fur/furshaderedit (low)"),
			xorstr_(L"autodesk interactive"),
			xorstr_(L"realtoon/version 5/lite/default"),
			xorstr_(L"doppels shaders/toon/dope toon opaque 1.31"),
			xorstr_(L"doppels shaders/toon/dope toon transparent 1.31"),
			xorstr_(L"unlit/hologram logo"),
			xorstr_(L"ui/timer hologram"),
			xorstr_(L"doppels shaders/models shaders/flame heart eye shader"),
			xorstr_(L"sunao shader/transparent"),
			xorstr_(L"decal/particle decal"),
			xorstr_(L"kriptofx/me/distortion"),
			xorstr_(L"mochie/particle shader"),
			xorstr_(L"unitychantoonshader/nooutline/tooncolor_doubleshadewithfeather"),
			xorstr_(L"sunao shader/transparent"),
			xorstr_(L"sunao shader/cutout"),
			xorstr_(L"unitychantoonshader/toon_shadinggrademap_stencilout"),
			xorstr_(L"poiyomi/shatterwave"),
			xorstr_(L"unitychantoonshader/toon_shadinggrademap_transclipping_stencilmask"),
			xorstr_(L"unitychantoonshader/mobile/toon_shadinggrademap_stencilout"),
			xorstr_(L"_lil/liltoonmulti"),
			xorstr_(L"unlit/kf_vrchatavatartextshader"),
			xorstr_(L"hidden/liltoonfurtwopass"),
			xorstr_(L"unlit/rainbowtrail")
		};

		std::vector<assembler::unity_engine::material*> materials_{};
		std::vector<assembler::unity_engine::object*> audiosources_{};

		assembler::unity_engine::game_object* assetbundle_ = nullptr;

		std::uint64_t particle_count_ = 0;
		bool has_constructed_audiosources_ = false;

		static inline assembler::il2cpp::il2cpp_type* rigidbody_type_ = nullptr;
		static inline assembler::il2cpp::il2cpp_type* lights_type_ = nullptr;
		static inline assembler::il2cpp::il2cpp_type* trailrenderer_type_ = nullptr;
		static inline assembler::il2cpp::il2cpp_type* aimiks_type_ = nullptr;
		static inline assembler::il2cpp::il2cpp_type* audiosources_type_ = nullptr;

		static bool confirm_material(assembler::unity_engine::material* m, std::uint64_t count);

	public:
		explicit assetbundle_processor(assembler::unity_engine::game_object* bundle) : assetbundle_(bundle)
		{
			assetbundle_->set_active(false);
		}
		~assetbundle_processor()
		{
			assetbundle_->set_active(true);
		}

		void scan_transforms() const;
		void scan_rigidbodies() const;
		void scan_spherecolliders() const;
		void scan_boxcolliders() const;
		void scan_capsulecolliders() const;
		void scan_lights() const;
		void scan_cloths() const;
		void scan_trailrenderers();
		void scan_linerenderers();
		void scan_particlesystems();
		void scan_animations() const;
		void scan_springjoints() const;
		void scan_aimiks() const;
		void scan_skinnedmeshrenderers();
		void scan_meshrenderers();
		void scan_audiosources();
		void scan_shaders();
		//void postprocess_skinnedmeshrenderers() const;

		void remove_audiosources();
	};
}

#endif