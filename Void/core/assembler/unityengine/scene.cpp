#include "scene.hpp"

int32_t assembler::unity_engine::scene::get_buildindex()
{
    if (!get_buildindex_func_) 
        get_buildindex_func_ = static_cast<get_buildindex_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.SceneManagement.Scene::GetBuildIndexInternal(System.Int32)")));
    return get_buildindex_func_(this->m_handle);
}

int32_t assembler::unity_engine::scene::get_handle()
{
    if (this == nullptr)
    {
        logging::push(FOREGROUND_INTENSE_BLUE);
        logging::print(xorstr_("[assembler] get_handle passed nullptr.\n"));
        logging::pop();
        return NULL;
    }

    return *reinterpret_cast<int32_t*>(reinterpret_cast<std::uint8_t*>(this));
}

bool assembler::unity_engine::scene_manager::set_active_scene(scene scenee)
{
	auto v4 = scenee.m_handle;

    if (!set_active_scene_func_) 
        set_active_scene_func_ = static_cast<set_active_scene_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.SceneManagement.SceneManager::SetActiveScene_Injected(UnityEngine.SceneManagement.Scene&)")));

    return set_active_scene_func_(&v4);
}

assembler::unity_engine::scene assembler::unity_engine::scene_manager::get_scene_by_name(const std::string_view name)
{
    scene v3;
    v3.m_handle = 0;

    if (!get_scene_by_name_func_)
        get_scene_by_name_func_ = static_cast<get_scene_by_name_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.SceneManagement.SceneManager::GetSceneByName_Injected(System.String,UnityEngine.SceneManagement.Scene&)")));

	get_scene_by_name_func_(il2cpp::string_new(name), &v3);
    return v3;
}

assembler::unity_engine::scene assembler::unity_engine::scene_manager::get_active_scene()
{
    scene v3;
    v3.m_handle = 0;

    if (!get_active_scene_func_)
        get_active_scene_func_ = static_cast<get_active_scene_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.SceneManagement.SceneManager::GetActiveScene_Injected(UnityEngine.SceneManagement.Scene&)")));

    get_active_scene_func_(&v3);
    return v3;
}
