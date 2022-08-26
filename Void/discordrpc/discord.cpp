#include "discord.hpp"
#include "../core/assembler/assembly-csharp/roommanager.hpp"

discord_sdk::discord_sdk()
{
	eptime_ = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	try
	{
		Discord_Initialize(xorstr_("896581383558946847"), &handle_, 1, nullptr);
	}
	catch (const std::exception& e)
	{
		logging::push(FOREGROUND_INTENSE_RED);
		logging::print(xorstr_("[critical] discord_sdk -> {}\n"), e.what());
		logging::pop();
	}
}

bool discord_sdk::update() const
{
	const auto room_manager = assembler::room_manager::get_new();

	if (!room_manager)
		return false;

	const auto api_world = room_manager->klass->static_fields->world;
	const auto api_world_instance = room_manager->klass->static_fields->world_instance;

	assembler::unity_engine::object::destroy(reinterpret_cast<assembler::unity_engine::object*>(room_manager));

	if (!api_world || !api_world_instance)
		return true;

	const auto status = assembler::vrc::core::api_user::get_current()->get_status();
	
	std::string details;
	std::string state;

	if (status == xorstr_("ask me") || status == xorstr_("busy"))
	{
		details = xorstr_("World: Hidden");
		state = xorstr_("[Private] Players: Hidden");
	}
	else
	{
		details = utility::format(xorstr_("World: {}"), api_world->get_name());
		state = utility::format(xorstr_("[{}] Players: {:d}"), api_world_instance->get_access_type(), assembler::vrc::player_manager::get_players()->max_length);
	}

	const auto largetext = utility::format(xorstr_("Void Client: {}"), assembler::vrc::core::api_user::get_current()->display_name());

	try
	{
		DiscordRichPresence presence{};

		presence.state = state.c_str();
		presence.details = details.c_str();
		presence.largeImageText = largetext.c_str();
		presence.largeImageKey = xorstr_("voidbg2_2_");
		presence.smallImageText = xorstr_("VRChat");
		presence.smallImageKey = xorstr_("vrchat1024x1024");
		presence.partyId = xorstr_("");
		presence.startTimestamp = eptime_;
		presence.endTimestamp = NULL;

		Discord_UpdatePresence(&presence);
	}
	catch (const std::exception& e)
	{
		logging::push(FOREGROUND_INTENSE_RED);
		logging::print(xorstr_("[critical] discord_sdk -> {}\n"), e.what());
		logging::pop();
		return false;
	}

	if (handle_.errored)
		return false;

	return true;
}

discord_sdk::~discord_sdk()
{
	try
	{
		Discord_Shutdown();
	}
	catch (const std::exception& e)
	{
		logging::push(FOREGROUND_INTENSE_RED);
		logging::print(xorstr_("[critical] discord_sdk -> {}\n"), e.what());
		logging::pop();
	}
}
