#include "patches.hpp"
#include <future>

#pragma region patch_system
void patches::setup()
{
	patches_.emplace_back(
		SECSTR("AssetBundleLoad"),
		true,
		memory::get_method<void*>(ASSETBUNDLELOAD),
		&hk_ab_load
	);

	patches_.emplace_back(
		SECSTR("Transform::CountNodesDeep"),
		true,
		memory::get_method_unity<void*>(TRANSFORM_COUNTNODESDEEP),
		&hk_transform_countnodesdeep
	);

	patches_.emplace_back(
		SECSTR("DebugStringToFilePostprocessedStacktrace"),
		true,
		memory::get_method_unity<void*>(DEBUGPOSTPROCESSEDSTACKTRACE),
		&hk_debugstringtofilepostprocessedstacktrace
	);

	patches_.emplace_back(
		SECSTR("StringStorageDefault::reallocate"),
		true,
		memory::get_method_unity<void*>(REALLOCATESTRING),
		&hk_reallocatestring
	);

	patches_.emplace_back(
		SECSTR("CachedReader::OutOfBoundsError"),
		true,
		memory::get_method_unity<void*>(READEROOB),
		&hk_reader_outofbounds
	);

	patches_.emplace_back(
		SECSTR("SerializedFile::ReadObject"),
		true,
		memory::get_method_unity<void*>(READOBJECT),
		&hk_readobject
	);

	patches_.emplace_back(
		SECSTR("DownloadHandlerAssetBundle::GetAssetBundle"),
		true,
		memory::get_method_unity<void*>(DOWNLOADHANDLER_ASSETBUNDLE_GETASSETBUNDLE),
		&hk_downloadhandlerassetbundle_getassetbundle
	);

	patches_.emplace_back(
		SECSTR("AssetBundleLoadFromAsyncOperation::Perform"),
		true,
		memory::get_method_unity<void*>(ASSETBUNDLE_LOADFROMASYNCOP_PERFORM),
		&hk_assetbundleloadfromasyncop_perform
	);

	patches_.emplace_back(
		SECSTR("PersistentManager::ReadObjectThreaded"),
		true,
		memory::get_method_unity<void*>(PERSISTENTMANAGER_READOBJECTTHREADED),
		&hk_persistentmanager_readobjectthreated
	);

	patches_.emplace_back(
		SECSTR("PersistentManager::ReadAndActivateObjectThreaded"),
		true,
		memory::get_method_unity<void*>(PERSISTENTMANAGER_READANDACTIVEOBJECTTHREADED),
		&hk_persistentmanager_readandactiveobjectthreaded
	);

	patches_.emplace_back(
		SECSTR("AssetBundleLoadAssetOperation::GetLoadedAsset"),
		true,
		memory::get_method_unity<void*>(ASSETBUNDLE_LOADASSETOP_GETLOADEDASSET),
		&hk_assetbundleloadassetop_getloadedasset
	);

	patches_.emplace_back(
		SECSTR("AwakeFromLoadQueue::Add"),
		true,
		memory::get_method_unity<void*>(AWAKEFROMLOADQUEUE_ADD),
		&hk_awakefromloadqueue_add
	);

	patches_.emplace_back(
		SECSTR("PersistentManager::RegisterPartiallyLoadedObjectInternal"),
		true,
		memory::get_method_unity<void*>(PERSISTENTMANAGER_REGISTERPARTIALLYLOADEDOBJECTINTERNAL),
		&hk_persistentmanager_registerpartiallyloadedobjectinternal
	);

	patches_.emplace_back(
		SECSTR("ProduceHelper::Produce"),
		true,
		memory::get_method_unity<void*>(AUDIOMIXERPRODUCE),
		&hk_audiomixer_produce
	);

	patches_.emplace_back(
		SECSTR("GameObject::Transfer<StreamedBinaryRead>"),
		true,
		memory::get_method_unity<void*>(GAMEOBJECT_TRANSFER_STREAMEDBINARYREAD),
		&hk_gameobject_transfer
	);

	patches_.emplace_back(
		SECSTR("CachedReader::Read"),
		true,
		memory::get_method_unity<void*>(CACHEDREADERREAD),
		&hk_cachedreader_read
	);

	patches_.emplace_back(
		SECSTR("CachedReader::UpdateReadCache"),
		true,
		memory::get_method_unity<void*>(CACHEDREADERUPDATEREACHCACHE),
		&hk_cachedreader_updatereadcache
	);

	patches_.emplace_back(
		SECSTR("CachedReader::SetPosition"),
		true,
		memory::get_method_unity<void*>(CACHEDREADERSETPOSITION),
		&hk_cachedreader_setposition
	);

	patches_.emplace_back(
		SECSTR("CachedReader::End"),
		true,
		memory::get_method_unity<void*>(CACHEDREADEREND),
		&hk_cachedreader_end
	);

	//patches_.emplace_back(
	//	xorstr_("AssetBundleTransfer"),
	//	true,
	//	memory::get_method_unity<void*>(ASSETBUNDLETRANSFER),
	//	&hk_ab_transfer
	//);

	patches_.emplace_back(
		SECSTR("ArchiveStorageHeader::ReadHeaderSignature"),
		true,
		memory::get_method_unity<void*>(ACCESSOR_READHEADER),
		&hk_ash_readheadersignature
	);

	patches_.emplace_back(
		SECSTR("SceneLoaded"),
		true,
		memory::get_method<void*>(SCENELOADEDINTERNAL),
		&hk_sceneloadedinternal
	);

	patches_.emplace_back(
		SECSTR("SceneUnloaded"),
		true,
		memory::get_method<void*>(SCENEUNLOADEDINTERNAL),
		&hk_sceneunloadedinternal
	);

	patches_.emplace_back(
		SECSTR("SetLockState"),
		true,
		assembler::il2cpp::resolve_icall(SECSTR("UnityEngine.Cursor::set_lockState(UnityEngine.CursorLockMode)")),
		&hk_setlockstate
	);

	patches_.emplace_back(
		SECSTR("SerializeTraits::ResizeSTLStyleArray"),
		true,
		memory::get_method_unity<void*>(RESIZESTLSTYLEARRAY),
		&serializetraits_resizestlstylearray
	);

	patches_.emplace_back(
		SECSTR("NamedObject::VirtualRedirectTransfer"),
		true,
		memory::get_method_unity<void*>(NAMEDOBJECT_VIRTUALREDIRECTTRANSFER),
		&hk_virtualredirecttransfer
	);

	patches_.emplace_back(
		SECSTR("SerializeTraitsForStringTypes"),
		true,
		memory::get_method_unity<void*>(SERIALIZETRAITS_FORSTRINGTYPES),
		&hk_serialize_traits_for_string_types
	);

	patches_.emplace_back(
		SECSTR("SerializeTraits<dynamic_array<KeyframeTpl<float>,0>>::ResizeSTLStyleArray"),
		true,
		memory::get_method_unity<void*>(SERIALIZETRAITS_RESIZE_KEYFRAME),
		&hk_serializetraits_keyframe_resizestlarray
	);

	patches_.emplace_back(
		SECSTR("StreamedBinaryRead::ReadDirect"),
		true,
		memory::get_method_unity<void*>(STREAMEDBINARYREAD_READDIRECT),
		&hk_streamedbinaryread_readdirect
	);

	patches_.emplace_back(
		SECSTR("TransferField_Array<StreamedBinaryRead,Converter_String>"),
		true,
		memory::get_method_unity<void*>(TRANSFERFIELD_ARRAY_STREAMEDBINARYREAD_CONVERTERSTRING),
		&hk_transferfield_array_streamedbinaryread_converterstring
	);

	patches_.emplace_back(
		SECSTR("StreamedBinaryRead::TransferSTLStyleArray<ArrayOfManagedObjectsTransferer>"),
		true,
		memory::get_method_unity<void*>(STREAMEDBINARYREAD_TRANSFERSTLSTYLEARRAY_ARRAYOFMANAGEDOBJECTS),
		&hk_streamedbinaryread_transferarrayofmanagedobjects
	);

	//patches_.emplace_back(
	//	xorstr_("GetComponentsImplementationRecurse000"),
	//	true,
	//	memory::get_method_unity<void*>(0x8C12D0),
	//	&hk_get_components_implementation_recurse
	//);

	//patches_.emplace_back(
	//	xorstr_("Transform::Transfer<StreamedBinaryRead>"),
	//	true,
	//	memory::get_method_unity<void*>(0xDF13A0),
	//	&hk_transform_transfer
	//);
}

bool patches::init()
{
	for (auto& mode : patches_)
	{
		if (!mode.enabled)
		{
			logging::push(FOREGROUND_INTENSE_YELLOW);
			logging::print(xorstr_("[warn] {} is disabled.\n"), mode.name);
			logging::pop();

			continue;
		}

		try 
		{
			if (!mode.apply_patch())
				return false;
		}
		catch (const std::runtime_error& e)
		{
			logging::push(FOREGROUND_INTENSE_RED);
			logging::print(xorstr_("[critical] {}\n"), e.what());
			logging::print(xorstr_("[critical] this is likely caused by running an incompatible version of vrchat.\n"));
			logging::pop();

			return false;
		}
	}

	logging::push(FOREGROUND_INTENSE_CYAN);
	logging::print(xorstr_("[log] finished loading {:d} engine patches.\n"), patches_.size());
	logging::pop();

	return true;
}

void patches::restore()
{
	for (auto& [name, enabled, genuine_f, detour_f, detour] : patches_)
	{
		if (!enabled)
			continue;

		detour.restore();
	}
}

bool patches::mode::operator()(const mode& m) const
{
	return m.name == name;
}

bool patches::mode::apply_patch()
{
	if (!detour.create(genuine_f, detour_f))
		return false;
	return true;
}

patches::mode& patches::fetch_patch(const std::string& setting_name)
{
	if (const auto it = std::ranges::find_if(patches_, mode(setting_name)); it != patches_.end()) return *it;
	throw std::runtime_error(utility::format(xorstr_("failed to find patch [{}]"), setting_name));
}
#pragma endregion

#pragma region patches
#pragma region assetbundle_processing
assembler::unity_engine::object* patches::hk_ab_load(assembler::unity_engine::object* obj, const bool b1, const bool b2, const bool b3)
{
	static auto genuine_f = get().fetch_patch(SECSTR("AssetBundleLoad")).detour.get_original<decltype(&hk_ab_load)>();

	auto obj_name = obj->get_ws_name();
	utility::unicode_tolower(obj_name);

	if (!obj_name.contains(xorstr_(L"avatar")) && !obj_name.contains(xorstr_(L"prefab-id-v1_avtr_")))
		return genuine_f(obj, b1, b2, b3);

	/* - CHECK ASSET BUNDLE - */
	const auto gameobj = reinterpret_cast<assembler::unity_engine::game_object*>(obj);
	const auto manager = reinterpret_cast<assembler::vrc::core::pipeline_manager*>(gameobj->get_component(xorstr_("PipelineManager")));
	const auto avatar_id = manager->get_blueprint_id();

	SEH_START
		if (!avatar_id.empty())
		{
			if (const auto wl_vec = &config::get<std::vector<std::string>>(g_context.avatar_whitelist); std::ranges::find(*wl_vec, avatar_id) != wl_vec->end())
			{
				logging::push(FOREGROUND_INTENSE_GREEN);
				logging::add_log(xorstr_("[anti-avatar crash] {} is whitelisted.\n"), avatar_id);
				logging::pop();
				return genuine_f(obj, b1, b2, b3);
			}

			if (const auto bl_vec = &config::get<std::vector<std::string>>(g_context.avatar_blacklist); config::get<bool>(g_context.anti_blacklisted_avatars) && std::ranges::find(*bl_vec, avatar_id) != bl_vec->end())
			{
				logging::push(FOREGROUND_INTENSE_RED);
				logging::add_log(xorstr_("[anti-blacklisted avatars] {} is blacklisted.\n"), avatar_id);
				logging::pop();
				return genuine_f(nullptr, b1, b2, b3);
			}
		}
	SEH_END

	{
		helpers::assetbundle_processor processor(gameobj);

		if (config::get<bool>(g_context.anti_avatar_crash))
		{
			processor.scan_transforms();
			processor.scan_rigidbodies();
			processor.scan_spherecolliders();
			processor.scan_boxcolliders();
			processor.scan_capsulecolliders();
			processor.scan_lights();
			processor.scan_cloths();
			processor.scan_skinnedmeshrenderers();
			processor.scan_meshrenderers();
			processor.scan_trailrenderers();
			processor.scan_linerenderers();
			processor.scan_particlesystems();
			processor.scan_animations();
			processor.scan_springjoints();
			processor.scan_aimiks();

			if (config::get<bool>(g_context.anti_avatar_audio))
				processor.remove_audiosources();
			else
				processor.scan_audiosources();

			processor.scan_shaders();
		}

		else if (config::get<bool>(g_context.anti_avatar_audio))
			processor.remove_audiosources();
	}

	if (config::get<bool>(g_context.anti_avatar_crash))
	{
		try
		{
			return genuine_f(obj, b1, b2, b3);
		}
		catch (const Il2CppExceptionWrapper& e)
		{
			logging::push(FOREGROUND_INTENSE_RED);
			logging::print(xorstr_("[critical] {}\n"), s_chars(e.ex->message));
			logging::pop();
			return nullptr;
		}
	}

	return genuine_f(obj, b1, b2, b3);
}

//0x180C65910

#pragma endregion

#pragma region engine_patches
//char patches::hk_get_components_implementation_recurse(std::uintptr_t* a1, const std::int64_t a2, const std::int64_t a3, void** a4, const std::int64_t a5)
//{
//	static auto& instance = get();
//	static auto genuine_f = instance.fetch_patch(SECSTR("GetComponentsImplementationRecurse000")).detour.get_original<decltype(&hk_get_components_implementation_recurse)>();
//
//	const std::intptr_t v2 = *(a1 + 6);
//
//	if (const auto aids = *reinterpret_cast<void**>(v2 + 8); !aids)
//	{
//		a1 = nullptr;
//		return 1;
//	}
//
//	return genuine_f(a1, a2, a3, a4, a5);
//}

void patches::hk_reallocatestring(native_string* a1, std::int64_t a2)
{
	static auto& instance = get();
	static auto genuine_f = instance.fetch_patch(SECSTR("StringStorageDefault::reallocate")).detour.get_original<decltype(&hk_reallocatestring)>();

	if (a1 != nullptr && a2 > 128 && a1->data != nullptr)
	{
		if (instance.last_reallocated_string_ != a1)
		{
			instance.last_reallocated_string_ = a1;
			instance.last_reallocation_count_ = 0;
		}
		else
		{
			instance.last_reallocation_count_++;
			if (instance.last_reallocation_count_ >= 8 && a2 <= a1->capacity + 16 && a1->capacity > 16)
				a2 = a1->capacity * 2;
		}
	}

	genuine_f(a1, a2);
}

std::uint32_t patches::impl_transform_countnodesdeep(node_container* _this, std::unordered_set<node_container*>& map)
{
	if (_this == nullptr)
		return 1;

	const auto direct_subs_count = _this->direct_sub_count;

	std::uint32_t total_nodes = 1;
	if (direct_subs_count <= 0)
		return total_nodes;

	map.insert(_this);

	const auto subs_base = _this->subs;
	if (subs_base == nullptr)
	{
		_this->direct_sub_count = 0;
		return total_nodes;
	}

	for (std::size_t i = 0; i < direct_subs_count; ++i)
	{
		const auto sub_node = subs_base[i];

		if (sub_node == nullptr)
		{
			// VMProtectBeginUltra("Node Overflow (1)");

			logging::push(FOREGROUND_INTENSE_RED);
			logging::add_log(SECSTR("[anti-node overflow] found duplicate transform in count\n"));
			logging::pop();
			ingame_logging::get().log(SECSTR("[<color=#a75cf6>anti-node overflow</color>] found duplicate transform in count"));

			if (config::get<bool>(g_context.xs_overlay_toggle))
			{
				if (!xs_overlay::get().send(SECSTR("[anti-node overflow] found duplicate transform in count"), SECSTR(""), SECSTR("warning"), 4))
				{
					logging::push(FOREGROUND_INTENSE_RED);
					logging::print(SECSTR("[critical] failed to talk to xs-overlay api [{}]\n"), xs_overlay::get().fetch_last_error());
					logging::pop();
				}
			}

			// VMProtectEnd();

			_this->direct_sub_count = 0;
			return total_nodes;
		}

		if (map.contains(sub_node))
		{
			// VMProtectBeginUltra("Node Overflow (2)");

			logging::push(FOREGROUND_INTENSE_RED);
			logging::add_log(SECSTR("[anti-node overflow] found duplicate transform in count\n"));
			logging::pop();
			ingame_logging::get().log(SECSTR("[<color=#a75cf6>anti-node overflow</color>] found duplicate transform in count"));

			if (config::get<bool>(g_context.xs_overlay_toggle))
			{
				if (!xs_overlay::get().send(SECSTR("[anti-node overflow] found duplicate transform in count"), SECSTR(""), SECSTR("warning"), 4))
				{
					logging::push(FOREGROUND_INTENSE_RED);
					logging::print(SECSTR("[critical] failed to talk to xs-overlay api [{}]\n"), xs_overlay::get().fetch_last_error());
					logging::pop();
				}
			}

			sub_node->direct_sub_count = _this->direct_sub_count = 0;

			// VMProtectEnd();
			return total_nodes;
		}

		total_nodes += impl_transform_countnodesdeep(sub_node, map);
	}

	return total_nodes;
}

std::uint32_t patches::hk_transform_countnodesdeep(node_container* _this)
{
	static auto genuine_f = get().fetch_patch(SECSTR("Transform::CountNodesDeep")).detour.get_original<decltype(&hk_transform_countnodesdeep)>();

	if (!config::get<bool>(g_context.anti_aa12))
		return genuine_f(_this);

	std::unordered_set<node_container*> v = {};
	return impl_transform_countnodesdeep(_this, v);
}

void patches::hk_debugstringtofilepostprocessedstacktrace(const char** data)
{
	static auto& instance = get();
	static auto genuine_f = instance.fetch_patch(SECSTR("DebugStringToFilePostprocessedStacktrace")).detour.get_original<decltype(&hk_debugstringtofilepostprocessedstacktrace)>();

	if (const auto sv_data = std::string_view(*data); instance.reader_depth_ > 0 || sv_data.contains(xorstr_("Size overflow in allocator")))
		*(reinterpret_cast<std::uint8_t*>(data) + 0x30) &= 0xEF;

	genuine_f(data);
}

void patches::hk_reader_outofbounds(std::uintptr_t* _this, const long a1, const long a2)
{
	static auto& instance = get();
	static auto genuine_f = instance.fetch_patch(SECSTR("CachedReader::OutOfBoundsError")).detour.get_original<decltype(&hk_reader_outofbounds)>();

	instance.reader_depth_++;
	try
	{
		genuine_f(_this, a1, a2);
		instance.reader_depth_--;
	}
	catch (const std::exception& e)
	{
		logging::push(FOREGROUND_INTENSE_RED);
		logging::print(xorstr_("[critical] {}\n"), e.what());
		logging::pop();
	}
}

std::uint64_t patches::serializetraits_resizestlstylearray(std::uintptr_t* a1, const std::int32_t a2)
{
	static auto& instance = get();
	static auto genuine_f = instance.fetch_patch(SECSTR("SerializeTraits::ResizeSTLStyleArray")).detour.get_original<decltype(&serializetraits_resizestlstylearray)>();

	if (a2 < 0 && config::get<bool>(g_context.anti_oob) && instance.read_object_depth_ > 0)
	{
		// VMProtectBeginUltra("SerializeTraits::ResizeSTLStyleArray OOB");

		instance.read_object_depth_--;
		RaiseException(STATUS_BAD_ALLOCATION, 0, 0, nullptr);

		// VMProtectEnd();
		return NULL;
	}

	const std::uintptr_t v3 = a1[2];
	std::uintptr_t result = a1[3] >> 1;
	const std::uintptr_t v5 = a2;

	if (a2 > result)
	{
		using usedinresize_t = std::intptr_t(*)(std::intptr_t, std::intptr_t, std::intptr_t);
		static auto usedinresize = memory::get_method_unity<usedinresize_t>(0xC6BF0);
		result = usedinresize(reinterpret_cast<std::intptr_t>(a1), a2, 1);
	}

	a1[2] = v5;

	if (v5 > v3)
	{
		result = *a1;
		auto v6 = reinterpret_cast<DWORD*>(*a1 + 4 * v3);

		if (v6 == nullptr && get().read_object_depth_ > 0 && config::get<bool>(g_context.anti_array_overflow))
		{
			// VMProtectBeginUltra("SerializeTraits::ResizeSTLStyleArray Overflow");

			instance.read_object_depth_--;
			RaiseException(STATUS_ARRAY_OVERFLOW, 0, 0, nullptr);

			// VMProtectEnd();
			return NULL;
		}

		if (const std::uintptr_t v7 = v5 - v3)
		{
			result = 0;
			for (std::uintptr_t i = v7; i; --i)
				*v6++ = 0;
		}
	}

	return result;
}

std::intptr_t patches::hk_readobject(std::intptr_t* a1, const std::intptr_t a2, char* a3, const bool a4, std::uintptr_t* a5, std::uint8_t* a6, std::uintptr_t* a7)
{
	static auto& instance = get();
	static auto genuine_f = instance.fetch_patch(SECSTR("SerializedFile::ReadObject")).detour.get_original<decltype(&hk_readobject)>();

	if (config::get<bool>(g_context.anti_ro_nulls) && instance.read_null_objects_)
	{
		const auto v11 = reinterpret_cast<char*>(a1[13]);
		const auto v12 = reinterpret_cast<char*>(a1[12]);

		const std::int64_t v14 = (v11 - v12) / 24;

		if (char* dummya3 = &v12[24 * (v14 >> 1)]; a2 == *reinterpret_cast<std::uintptr_t*>(dummya3) && a2 == 1 && v14 < 12)
		{
			if (v14 != 1 || g_context.instantiated)
			{
				logging::push(FOREGROUND_INTENSE_RED);
				logging::add_log(xorstr_("[anti-ro.nulls] possible bad bundle. [{:d}]\n"), v14);
				logging::pop();
				return NULL;
			}
		}
	}

	std::intptr_t ret;

	if (a1 == instance.cached_serialized_file_)
		return NULL;
	
	instance.cached_serialized_file_ = nullptr;

	try
	{
		get().read_object_depth_++;
		ret = patches_proxy::hk_readobject(genuine_f, a1, a2, a3, a4, a5, a6, a7);
		get().read_object_depth_--;
	}
	catch (const std::runtime_error& e)
	{
		if (config::get<bool>(g_context.anti_oob)) 
		{
			instance.crasher_depth_++;
			instance.cached_serialized_file_ = a1;
		}

		logging::push(FOREGROUND_INTENSE_RED);
		logging::add_log(xorstr_("[critical] {}\n"), e.what());
		logging::pop();
		ingame_logging::get().log(xorstr_("[<color=#a75cf6>critical</color>] {}"), e.what());

		if (config::get<bool>(g_context.xs_overlay_toggle))
		{
			if (!xs_overlay::get().send(utility::format(xorstr_("[critical] {}"), e.what()), xorstr_(""), xorstr_("warning"), 4))
			{
				logging::push(FOREGROUND_INTENSE_RED);
				logging::print(xorstr_("[critical] failed to talk to xs-overlay api [{}]\n"), xs_overlay::get().fetch_last_error());
				logging::pop();
			}
		}

		if (config::get<bool>(g_context.anti_oob))
			throw;

		return NULL;
	}
	
	return ret;
}

std::uintptr_t* patches::hk_persistentmanager_readobjectthreated(std::intptr_t* _this, const std::int32_t a2, const std::int32_t a3)
{
	static auto& instance = get();
	static auto genuine_f = instance.fetch_patch(SECSTR("PersistentManager::ReadObjectThreaded")).detour.get_original<decltype(&hk_persistentmanager_readobjectthreated)>();

	const auto ret = genuine_f(_this, a2, a3);

	if (instance.crasher_depth_ > 0 && instance.asyncoperations_depth_ > 0) 
	{
		helpers::unlock_persistentmanager(_this, 1);
		throw std::runtime_error(xorstr_("cleaning up"));
	}

	return ret;
}

std::uintptr_t* patches::hk_persistentmanager_readandactiveobjectthreaded(std::intptr_t* _this, std::uint32_t a2, std::uint32_t* a3, std::intptr_t* a4, std::uint8_t a5, std::intptr_t a6, std::int32_t a7)
{
	static auto& instance = get();
	static auto genuine_f = instance.fetch_patch(SECSTR("PersistentManager::ReadAndActivateObjectThreaded")).detour.get_original<decltype(&hk_persistentmanager_readandactiveobjectthreaded)>();

	try
	{
		return genuine_f(_this, a2, a3, a4, a5, a6, a7);
	}
	catch (const std::runtime_error&)
	{
		return nullptr;
	}
}

std::intptr_t* patches::hk_assetbundleloadassetop_getloadedasset(std::intptr_t* _this, std::intptr_t a2, std::intptr_t a3)
{
	static auto& instance = get();
	static auto genuine_f = instance.fetch_patch(SECSTR("AssetBundleLoadAssetOperation::GetLoadedAsset")).detour.get_original<decltype(&hk_assetbundleloadassetop_getloadedasset)>();

	const auto ret = genuine_f(_this, a2, a3);

	if (instance.crasher_depth_ > 0)
	{
		instance.crasher_depth_--;
		instance.cached_loadop_ = _this;

		return nullptr;
	}

	if (instance.cached_loadop_ == _this) 
	{
		helpers::destroy_engineobject(ret, 0);
		return nullptr;
	}

	instance.cached_loadop_ = nullptr;

	return ret;
}

std::intptr_t* patches::hk_downloadhandlerassetbundle_getassetbundle(std::intptr_t* _this)
{
	static auto& instance = get();
	static auto genuine_f = instance.fetch_patch(SECSTR("DownloadHandlerAssetBundle::GetAssetBundle")).detour.get_original<decltype(&hk_downloadhandlerassetbundle_getassetbundle)>();

	const auto ret = genuine_f(_this);

	if (instance.crasher_depth_ > 0)
	{
		instance.crasher_depth_--;
		instance.cached_asyncloadop_ = _this;

		return nullptr;
	}

	if (instance.cached_asyncloadop_ == _this) 
		return nullptr;

	instance.cached_asyncloadop_ = nullptr;

	return ret;
}

void patches::hk_assetbundleloadfromasyncop_perform(std::intptr_t* _this)
{
	static auto& instance = get();
	static auto genuine_f = instance.fetch_patch(SECSTR("AssetBundleLoadFromAsyncOperation::Perform")).detour.get_original<decltype(&hk_assetbundleloadfromasyncop_perform)>();

	try 
	{
		instance.asyncoperations_depth_++;
		genuine_f(_this);
		instance.asyncoperations_depth_--;
	}
	catch (const std::runtime_error&)
	{
		instance.asyncoperations_depth_--;
	}
}

std::intptr_t patches::hk_awakefromloadqueue_add(std::intptr_t* a1, std::intptr_t* a2)
{
	static auto& instance = get();
	static auto genuine_f = instance.fetch_patch(SECSTR("AwakeFromLoadQueue::Add")).detour.get_original<decltype(&hk_awakefromloadqueue_add)>();

	if (instance.crasher_depth_ > 0)
		return NULL;

	return genuine_f(a1, a2);
}

std::intptr_t* patches::hk_persistentmanager_registerpartiallyloadedobjectinternal(std::intptr_t* _this, const std::int32_t a2)
{
	static auto& instance = get();
	static auto genuine_f = instance.fetch_patch(SECSTR("PersistentManager::RegisterPartiallyLoadedObjectInternal")).detour.get_original<decltype(&hk_persistentmanager_registerpartiallyloadedobjectinternal)>();

	if (instance.crasher_depth_ > 0)
		return nullptr;

	return genuine_f(_this, a2);
}

std::intptr_t patches::hk_audiomixer_produce(const std::uint32_t a1, const std::uint32_t a2)
{
	static auto& instance = get();
	static auto genuine_f = instance.fetch_patch(SECSTR("ProduceHelper::Produce")).detour.get_original<decltype(&hk_audiomixer_produce)>();

	if (!instance.read_audio_mixers_ && config::get<bool>(g_context.anti_audio_mixers))
		return NULL;

	return genuine_f(a1, a2);
}

void patches::hk_safebinaryread_transfer(std::uintptr_t* a1, float* a2, const char* a3)
{
	static auto genuine_f = get().fetch_patch(SECSTR("FloatTransfer")).detour.get_original<decltype(&hk_safebinaryread_transfer)>();
	genuine_f(a1, a2, a3);

	if (get().read_bad_floats_ || *a2 > -3.402823E+7f && *a2 < 3.402823E+7f)
		return;

	if (!std::isnan(*a2) && a3 != nullptr)
		if (std::ranges::find(allowed_fields, a3) != allowed_fields.end())
			return;

	*a2 = 0;
}

void patches::hk_gameobject_transfer(std::uintptr_t* a1, const std::uintptr_t* a2)
{
	static auto& instance = get();
	static auto genuine_f = instance.fetch_patch(SECSTR("GameObject::Transfer<StreamedBinaryRead>")).detour.get_original<decltype(&hk_gameobject_transfer)>();

	const auto p_size = *reinterpret_cast<std::int32_t*>(a2[5]);
	if (!p_size && config::get<bool>(g_context.anti_oob) && instance.read_object_depth_ > 0)
	{
		// VMProtectBeginUltra("GameObject::Transfer OOB");

		instance.read_object_depth_--;
		RaiseException(STATUS_BAD_ALLOCATION, 0, 0, nullptr);

		// VMProtectEnd();
		return;
	}

	return genuine_f(a1, a2);
}

void patches::hk_cachedreader_read(std::intptr_t* _this, void* a2, const std::size_t size)
{
	static auto& instance = get();
	static auto genuine_f = instance.fetch_patch(SECSTR("CachedReader::Read")).detour.get_original<decltype(&hk_cachedreader_read)>();

	const auto current = reinterpret_cast<std::uintptr_t>(a2);
	const auto last = current + size;

	if (last < current && config::get<bool>(g_context.anti_oob) && instance.read_object_depth_ > 0)
	{
		// VMProtectBeginUltra("CachedReader::Read OOB 1");

		*(reinterpret_cast<std::uint8_t*>(_this) + 64) = 1;

		instance.read_object_depth_--;
		RaiseException(STATUS_BAD_ALLOCATION, 0, 0, nullptr);

		// VMProtectEnd();
	}

	if (const auto v5 = *reinterpret_cast<char**>(_this); reinterpret_cast<std::uint64_t>(&v5[size]) > *(reinterpret_cast<std::uint64_t*>(_this) + 2))
	{
		if (const auto v7 = reinterpret_cast<std::uint64_t>(&v5[*(reinterpret_cast<std::uint64_t*>(_this) + 5) * *(reinterpret_cast<std::int32_t*>(_this) + 8) - *(reinterpret_cast<std::uint64_t*>(_this) + 1)]); helpers::is_oob(_this, v7, size))
		{
			if (config::get<bool>(g_context.anti_oob) && instance.read_object_depth_ > 0)
			{
				// VMProtectBeginUltra("CachedReader::Read OOB 2");

				*(reinterpret_cast<std::uint8_t*>(_this) + 64) = 1;

				instance.read_object_depth_--;
				RaiseException(STATUS_OUT_OF_BOUNDS, 0, 0, nullptr);

				// VMProtectEnd();
			}
		}
	}

	else
	{
		if (config::get<bool>(g_context.anti_oob) && instance.read_object_depth_ > 0)
		{
			if (memmove_s(a2, size, v5, size) != 0)
			{
				// VMProtectBeginUltra("CachedReader::Read OOB 3");

				instance.read_object_depth_--;
				RaiseException(STATUS_BAD_ALLOCATION, 0, 0, nullptr);

				// VMProtectEnd();
			}
		}
		else memmove_s(a2, size, v5, size);

		*reinterpret_cast<std::uint64_t*>(_this) += size;
		return;
	}

	genuine_f(_this, a2, size);
}

void patches::hk_cachedreader_updatereadcache(std::intptr_t* _this, void* a2, const std::size_t size)
{
	static auto& instance = get();
	static auto genuine_f = instance.fetch_patch(SECSTR("CachedReader::UpdateReadCache")).detour.get_original<decltype(&hk_cachedreader_updatereadcache)>();

	if (const std::uint64_t v6 = *_this + *(_this + 5) * *(reinterpret_cast<std::int32_t*>(_this) + 8) - *(_this + 1); helpers::is_oob(_this, v6, size))
	{
		if (config::get<bool>(g_context.anti_oob) && instance.read_object_depth_ > 0) 
		{
			// VMProtectBeginUltra("CachedReader::UpdateReadCache OOB");

			*(reinterpret_cast<std::uint8_t*>(_this) + 64) = 1;

			instance.read_object_depth_--;
			RaiseException(STATUS_OUT_OF_BOUNDS, 0, 0, nullptr);

			// VMProtectEnd();
		}
	}

	return genuine_f(_this, a2, size);
}

void patches::hk_cachedreader_setposition(std::intptr_t* _this, const std::uintptr_t a2)
{
	static auto& instance = get();
	static auto genuine_f = instance.fetch_patch(SECSTR("CachedReader::SetPosition")).detour.get_original<decltype(&hk_cachedreader_setposition)>();

	if (helpers::is_oob(_this, a2, 0))
	{
		if (config::get<bool>(g_context.anti_oob) && instance.read_object_depth_ > 0)
		{
			// VMProtectBeginUltra("CachedReader::SetPosition OOB");

			*(reinterpret_cast<std::uint8_t*>(_this) + 64) = 1;

			instance.read_object_depth_--;
			RaiseException(STATUS_OUT_OF_BOUNDS, 0, 0, nullptr);

			// VMProtectEnd();
		}
	}

	return genuine_f(_this, a2);
}

void patches::hk_cachedreader_end(std::intptr_t* _this)
{
	static auto& instance = get();
	static auto genuine_f = instance.fetch_patch(SECSTR("CachedReader::End")).detour.get_original<decltype(&hk_cachedreader_end)>();

	if (const std::uint64_t v2 = *_this + *(reinterpret_cast<std::int32_t*>(_this) + 8) * *(_this + 5) - *(_this + 1); helpers::is_oob(_this, v2, 0))
	{
		if (config::get<bool>(g_context.anti_oob) && instance.read_object_depth_ > 0)
		{
			// VMProtectBeginUltra("CachedReader::End OOB");

			*(reinterpret_cast<std::uint8_t*>(_this) + 64) = 1;

			instance.read_object_depth_--;
			RaiseException(STATUS_OUT_OF_BOUNDS, 0, 0, nullptr);

			// VMProtectEnd();
		}
	}

	return genuine_f(_this);
}

void patches::hk_streamedbinaryread_readdirect(std::uintptr_t* _this, void* a2, const std::int32_t size)
{
	static auto& instance = get();
	static auto genuine_f = instance.fetch_patch(SECSTR("StreamedBinaryRead::ReadDirect")).detour.get_original<decltype(&hk_streamedbinaryread_readdirect)>();

	// @note: should not be negative
	if (size < 0 && config::get<bool>(g_context.anti_oob) && instance.read_object_depth_ > 0)
	{
		// VMProtectBeginUltra("SBR::ReadDirect OOB");

		instance.read_object_depth_--;
		RaiseException(STATUS_BAD_ALLOCATION, 0, 0, nullptr);

		// VMProtectEnd();
	}

	genuine_f(_this, a2, size);
}

std::intptr_t patches::hk_transferfield_array_streamedbinaryread_converterstring(const std::intptr_t a1, const std::intptr_t a2)
{
	static auto& instance = get();
	static auto genuine_f = instance.fetch_patch(SECSTR("TransferField_Array<StreamedBinaryRead,Converter_String>")).detour.get_original<decltype(&hk_transferfield_array_streamedbinaryread_converterstring)>();

	if (config::get<bool>(g_context.anti_oob) && instance.read_object_depth_ > 0) 
	{
		try
		{
			return genuine_f(a1, a2);
		}
		catch (const std::length_error&)
		{
			// VMProtectBeginUltra("TF::Array<SBR, ConverterString> Bad Allocation");

			instance.read_object_depth_--;
			RaiseException(STATUS_BAD_ALLOCATION, 0, 0, nullptr);

			// VMProtectEnd();

			return NULL;
		}
	}

	return genuine_f(a1, a2);
}

std::intptr_t patches::hk_streamedbinaryread_transferarrayofmanagedobjects(const std::intptr_t a1, std::uintptr_t* a2)
{
	static auto& instance = get();
	static auto genuine_f = instance.fetch_patch(SECSTR("StreamedBinaryRead::TransferSTLStyleArray<ArrayOfManagedObjectsTransferer>")).detour.get_original<decltype(&hk_streamedbinaryread_transferarrayofmanagedobjects)>();

	if (instance.read_object_depth_ > 0) 
	{
		try
		{
			return genuine_f(a1, a2);
		}
		catch (const Il2CppExceptionWrapper&)
		{
			// VMProtectBeginUltra("SBR::TransferSTLStyleArray<ArrayOfManagedObjectsTransferer> Bad Allocation");

			instance.read_object_depth_--;
			RaiseException(STATUS_BAD_ALLOCATION, 0, 0, nullptr);

			// VMProtectEnd();

			return NULL;
		}
	}

	return genuine_f(a1, a2);
}

void patches::hk_virtualredirecttransfer(std::uintptr_t* _this, streamed_binary_read* a2, const std::uintptr_t a3, const DWORD a4)
{
	static auto& instance = get();
	static auto genuine_f = get().fetch_patch(SECSTR("NamedObject::VirtualRedirectTransfer")).detour.get_original<decltype(&hk_virtualredirecttransfer)>();

	const auto v6 = reinterpret_cast<std::int32_t*>(*(reinterpret_cast<std::uintptr_t*>(a2) + 5));

	if (const std::uint64_t v10 = *v6; v10 + reinterpret_cast<std::uintptr_t>(a2) < v10)
	{
		if (config::get<bool>(g_context.anti_oob) && instance.read_object_depth_ > 0)
		{
			// VMProtectBeginUltra("VirtualRedirectTransfer OOB");

			instance.read_object_depth_--;
			RaiseException(STATUS_BAD_ALLOCATION, 0, 0, nullptr);

			// VMProtectEnd();
		}
	}

	genuine_f(_this, a2, a3, a4);
}

std::uintptr_t* patches::hk_serialize_traits_for_string_types(native_string* a1, const std::int32_t a2)
{
	static auto& instance = get();
	static auto genuine_f = get().fetch_patch(SECSTR("SerializeTraitsForStringTypes")).detour.get_original<decltype(&hk_serialize_traits_for_string_types)>();

	if (const std::int64_t v4 = a2; instance.read_object_depth_ > 0 && v4 < 0 && config::get<bool>(g_context.anti_oob))
	{
		// VMProtectBeginUltra("SerializeTraitsForStringTypes OOB");

		instance.read_object_depth_--;
		RaiseException(STATUS_BAD_POINTER, 0, 0, nullptr);

		// VMProtectEnd();
	}

	return genuine_f(a1, a2);
}

std::uintptr_t patches::hk_serializetraits_keyframe_resizestlarray(std::uintptr_t* a1, const std::int32_t a2)
{
	static auto& instance = get();
	static auto genuine_f = get().fetch_patch(SECSTR("SerializeTraits<dynamic_array<KeyframeTpl<float>,0>>::ResizeSTLStyleArray")).detour.get_original<decltype(&hk_serializetraits_keyframe_resizestlarray)>();

	if (a2 < 0 && config::get<bool>(g_context.anti_oob) && instance.read_object_depth_ > 0)
	{
		// VMProtectBeginUltra("SerializeTraits OOB");

		instance.read_object_depth_--;
		RaiseException(STATUS_BAD_POINTER, 0, 0, nullptr);

		// VMProtectEnd();
	}

	return genuine_f(a1, a2);
}

//void patches::hk_transform_transfer(std::uintptr_t* _this, streamed_binary_read* a2)
//{
//	static auto& instance = get();
//	static auto genuine_f = instance.fetch_patch(SECSTR("Transform::Transfer<StreamedBinaryRead>")).detour.get_original<decltype(&hk_transform_transfer)>();
//
//	if ((*reinterpret_cast<DWORD*>(a2) & 0x4000) == 0) 
//	{
//		const auto v11 = reinterpret_cast<std::int32_t*>(*(reinterpret_cast<std::uintptr_t*>(a2) + 5));
//		const std::uint64_t v14 = *(_this + 16);
//		const std::uint64_t v15 = *v11;
//
//		if (v15 > v14 && v15 + reinterpret_cast<std::uintptr_t>(a2) < v15)
//		{
//			if (config::get<bool>(g_context.anti_oob) && instance.read_object_depth_ > 0)
//			{
//				// VMProtectBeginUltra("SerializeTraits OOB");
//
//				instance.read_object_depth_--;
//				RaiseException(STATUS_BAD_POINTER, 0, 0, nullptr);
//
//				// VMProtectEnd();
//			}
//		}
//	}
//
//	return genuine_f(_this, a2);
//}

std::intptr_t patches::hk_ash_readheadersignature(std::uintptr_t* a1, const std::intptr_t a2)
{
	static auto genuine_f = get().fetch_patch(SECSTR("ArchiveStorageHeader::ReadHeaderSignature")).detour.get_original<decltype(&hk_ash_readheadersignature)>();

	if (!config::get<bool>(g_context.anti_ro_nulls))
		return genuine_f(a1, a2);

	const auto position = helpers::fileaccessor_position(a1);

	auto data = new char[131072];
	std::uintptr_t data_read2 = 0;
	if (helpers::fileaccessor_read(reinterpret_cast<std::intptr_t>(a1), 131072, reinterpret_cast<std::intptr_t>(data), reinterpret_cast<std::intptr_t>(&data_read2), 0))
	{
		const auto sv_data = std::string_view(data, 131071);
		try
		{
			if (sv_data.empty() || sv_data.at(7) != 0 && sv_data.starts_with(xorstr_("UnityFS")))
				throw std::runtime_error(xorstr_("anti-ro.nulls: found bad signature"));

			if (sv_data.contains(xorstr_("_0048_PaleGoldenrodS")))
				throw std::runtime_error(xorstr_("anti-ro.nulls: found bad signature"));
		}
		catch (const std::runtime_error& e)
		{
			logging::push(FOREGROUND_INTENSE_RED);
			logging::add_log(xorstr_("[critical] {}\n"), e.what());
			logging::pop();
			ingame_logging::get().log(xorstr_("[<color=#a75cf6>critical</color>] {}"), e.what());

			if (config::get<bool>(g_context.xs_overlay_toggle))
			{
				if (!xs_overlay::get().send(utility::format(xorstr_("[critical] {}"), e.what()), xorstr_(""), xorstr_("warning"), 4))
				{
					logging::push(FOREGROUND_INTENSE_RED);
					logging::print(xorstr_("[critical] failed to talk to xs-overlay api [{}]\n"), xs_overlay::get().fetch_last_error());
					logging::pop();
				}
			}

			delete[] data;
			return NULL;
		}
	}

	delete[] data;
	helpers::fileaccessor_seak(reinterpret_cast<std::intptr_t>(a1), position, 1);
	return genuine_f(a1, a2);
}
#pragma endregion

#pragma region utility_patches
void patches::hk_sceneloadedinternal(assembler::unity_engine::scene scene, const std::int32_t mode)
{
	static auto& instance = get();
	static auto genuine_f = instance.fetch_patch(SECSTR("SceneLoaded")).detour.get_original<decltype(&hk_sceneloadedinternal)>();

	if (scene.get_buildindex() == -1)
	{
		instance.read_audio_mixers_ = false;
		instance.read_bad_floats_ = false;
		instance.read_null_objects_ = true;
	}

	return genuine_f(scene, mode);
}

void patches::hk_sceneunloadedinternal(assembler::unity_engine::scene scene)
{
	static auto& instance = get();
	static auto genuine_f = instance.fetch_patch(SECSTR("SceneUnloaded")).detour.get_original<decltype(&hk_sceneunloadedinternal)>();

	if (scene.get_buildindex() == -1)
	{
		instance.read_audio_mixers_ = true;
		instance.read_bad_floats_ = true;
		instance.read_null_objects_ = false;
	}

	return genuine_f(scene);
}

void patches::hk_setlockstate(assembler::unity_engine::cursor_lock_mode value)
{
	static auto genuine_f = get().fetch_patch(SECSTR("SetLockState")).detour.get_original<decltype(&hk_setlockstate)>();

	if (menu_window::mainmenu_opened)
		value = assembler::unity_engine::cursor_lock_mode::none;

	genuine_f(value);
}
#pragma endregion
#pragma endregion

#pragma region seh_chain
std::int32_t patches_proxy::evaluate_exception(const DWORD code)
{
	switch (code)
	{
	case STATUS_ARRAY_OVERFLOW:
	case STATUS_OUT_OF_BOUNDS:
	case STATUS_BAD_ALLOCATION:
	case STATUS_BAD_POINTER:
	case STATUS_CLEANUP:
		return EXCEPTION_EXECUTE_HANDLER;

	default:
		return EXCEPTION_CONTINUE_SEARCH;
	}
}
#pragma endregion
