#include "apiuser.hpp"

#if LVM_TESTING == 1
bool assembler::vrc::core::api_user::initialize_lvm(sol::state& lua)
{
	try
	{
		auto core_table = lua[std::string_view(xorstr_("vrc"))].get_or_create<sol::table>()[std::string_view(xorstr_("core"))].get_or_create<sol::table>();

		sol::usertype<api_user> apiuser_type = core_table.new_usertype<api_user>(xorstr_("api_user"), sol::factories(&api_user::ctor));

		// @note: static functions
		apiuser_type.set_function(VMProtectDecryptStringA("get_current"), &api_user::get_current);

		// @note: member functions
		apiuser_type[std::string_view(xorstr_("get_id"))] = &api_user::get_id;
		apiuser_type[std::string_view(xorstr_("get_vrca"))] = &api_user::get_vrca;
		apiuser_type[std::string_view(xorstr_("get_instance_id"))] = &api_user::get_instance_id;
		apiuser_type[std::string_view(xorstr_("get_world_id"))] = &api_user::get_world_id;
		apiuser_type[std::string_view(xorstr_("get_location"))] = &api_user::get_location;
		apiuser_type[std::string_view(xorstr_("get_icon_vrca"))] = &api_user::get_usericon;
		apiuser_type[std::string_view(xorstr_("get_status_description"))] = &api_user::get_status_description;
		apiuser_type[std::string_view(xorstr_("is_friends_with"))] = static_cast<bool(*)(std::string_view)>(&api_user::is_friends_with);
		apiuser_type[std::string_view(xorstr_("is_mobile"))] = &api_user::get_is_on_mobile;
		apiuser_type[std::string_view(xorstr_("get_displayname"))] = &api_user::display_name;
		apiuser_type[std::string_view(xorstr_("set_displayname"))] = &api_user::set_display_name;
	}
	catch (const sol::error& e)
	{
		logging::push(FOREGROUND_INTENSE_RED);
		logging::add_log(xorstr_("[critical] {}\n"), e.what());
		logging::pop();
		return false;
	}

	return true;
}
#endif

bool assembler::vrc::core::api_user::is_friends_with(il2cpp::il2cpp_string* user_id) // isFriendsWith
{
	using is_friends_func_t = bool(*)(il2cpp::il2cpp_string*);
	static const auto func = memory::get_method<is_friends_func_t>(ISFRIENDSWITH);
	return func(user_id);
}

bool assembler::vrc::core::api_user::has_tag(const std::string_view user_id) // hasTag(string tag)
{
	if (!this)
		return NULL;

	using has_tag_func_t = bool(*)(api_user*, il2cpp::il2cpp_string*);
	static const auto func = memory::get_method<has_tag_func_t>(HASTAG);
	return func(this, il2cpp::string_new(user_id));
}

assembler::vrc::core::api_user* assembler::vrc::core::api_user::get_current() // public static APIUser get_CurrentUser
{
	if (!global_class_)
		global_class_ = reinterpret_cast<vrc_core_apiuser_c*>(class_from_system_type(get_global_type()));

	return global_class_->static_fields->current_user;
}

assembler::il2cpp::il2cpp_array* assembler::vrc::core::api_user::get_past_displaynames() const
{
	if (!this)
		return nullptr;

	const auto list = this->fields.past_display_names;

	if (!list)
		return nullptr;

	return list->fields._items;
}

std::string assembler::vrc::core::api_user::get_usericon() const
{
	if (!this)
		return xorstr_("INVALID_STRING");

	return s_chars(this->fields.user_icon);
}

std::string assembler::vrc::core::api_user::get_status() const
{
	if (this == nullptr)
	{
		logging::push(FOREGROUND_INTENSE_BLUE);
		logging::print(xorstr_("[assembler] get_status passed nullptr.\n"));
		logging::pop();
		return xorstr_("INVALID_STRING");
	}
	return s_chars(this->fields.status); // <status>k__BackingField
}

std::string assembler::vrc::core::api_user::get_status_description() const
// <statusDescription>k__BackingField
{
	if (!this)
	{
		logging::push(FOREGROUND_INTENSE_BLUE);
		logging::print(xorstr_("[assembler] get_status_description passed nullptr.\n"));
		logging::pop();
		return xorstr_("INVALID_STRING");
	}
	return s_chars(this->fields.status_description);
}

void assembler::vrc::core::api_user::set_status_description(const std::string_view argument)
// <statusDescription>k__BackingField
{
	if (!this)
	{
		logging::push(FOREGROUND_INTENSE_BLUE);
		logging::print(xorstr_("[assembler] set_status_description passed nullptr.\n"));
		logging::pop();
		return;
	}

	this->fields.status_description = il2cpp::string_new(argument);
}

bool assembler::vrc::core::api_user::is_friends_with(const std::string_view user_id) // isFriendsWith
{
	return is_friends_with(il2cpp::string_new(user_id));
}

assembler::il2cpp::il2cpp_array* assembler::vrc::core::api_user::get_tags() const
{
	if (!this)
	{
		logging::push(FOREGROUND_INTENSE_BLUE);
		logging::print(xorstr_("[assembler] get_tags passed nullptr.\n"));
		logging::pop();
		return nullptr;
	}
	return reinterpret_cast<il2cpp::il2cpp_array*>(this->fields.tags);
}

std::string assembler::vrc::core::api_user::display_name() const
{
	if (!this)
		return xorstr_("INVALID_STRING");

	return s_chars(this->fields.display_name);
}

void assembler::vrc::core::api_user::set_display_name(const std::string_view name)
{
	if (!this)
		return;

	this->fields.display_name = il2cpp::string_new(name);
}

std::string assembler::vrc::core::api_user::get_id() const
{
	if (!this)
		return xorstr_("INVALID_STRING");

	return s_chars(this->fields.id);
}

std::string assembler::vrc::core::api_user::get_vrca() const
{
	if (!this)
	{
		logging::push(FOREGROUND_INTENSE_BLUE);
		logging::print(xorstr_("[assembler] get_vrca passed nullptr.\n"));
		logging::pop();
		return xorstr_("INVALID_STRING");
	}
	return s_chars(this->fields.current_avatar_asset_url);
}

std::string assembler::vrc::core::api_user::get_location() const
{
	if (!this)
		return xorstr_("private");

	return s_chars(this->fields.location);
}

std::string assembler::vrc::core::api_user::get_world_id() const
{
	if (!this)
		return xorstr_("INVALID_STRING");

	return s_chars(this->fields.world_id);
}

std::string assembler::vrc::core::api_user::get_instance_id() const
{
	if (!this)
		return xorstr_("INVALID_STRING");

	return s_chars(this->fields.instance_id);
}

void assembler::vrc::core::api_user::send_friend_request(api_user* user)
{
	using func_t = void(*)(api_user*);
	static const auto func = memory::get_method<func_t>(SENDFRIENDREQUEST);
	func(user);
}

assembler::il2cpp::il2cpp_array* assembler::vrc::core::api_user::get_friends()
{
	const auto local_player = get_current();

	if (!local_player)
		return nullptr;

	const auto friends = local_player->fields.friend_i_ds;

	if (!friends)
		return nullptr;

	return friends->fields._items;
}

assembler::vrc::core::api_user* assembler::vrc::core::api_user::ctor()
{
	const auto ret = reinterpret_cast<api_user*>(new_object(get_global_type(), true));

	using func_t = void (*)(api_user*);
	static const auto func = memory::get_method<func_t>(APIUSERCTOR);
	func(ret);
	return ret;
}

assembler::il2cpp::il2cpp_type* assembler::vrc::core::api_user::get_global_type()
{
	if (!type_)
		type_ = il2cpp::get_type(xorstr_("VRC.Core.APIUser, VRCCore-Standalone"));

	return type_;
}

bool assembler::vrc::core::api_user::get_is_on_mobile() const
{
	if (!this)
		return false;

	return this->fields.supported_platforms == 2;
}
