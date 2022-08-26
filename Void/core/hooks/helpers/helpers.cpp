#include "helpers.hpp"

bool helpers::is_oob(std::intptr_t* a1, const std::intptr_t a2, const std::intptr_t a3)
{
	if (!*(reinterpret_cast<std::uint8_t*>(a1) + 64))
	{
		const std::uintptr_t v5 = a2 + a3;
		if (a2 + a3 > (*reinterpret_cast<std::intptr_t(**)(std::uintptr_t)>(**(reinterpret_cast<std::uintptr_t**>(a1) + 3) + 48))(*(reinterpret_cast<std::uintptr_t*>(a1) + 3)))
		{
			return true;
		}
		if (v5 > *(reinterpret_cast<std::uintptr_t*>(a1) + 7))
		{
			return true;
		}
		if (a2 < *(reinterpret_cast<std::uintptr_t*>(a1) + 6))
		{
			return true;
		}
	}
	return false;
}

std::string helpers::fetch_oob(std::intptr_t* a1)
{
	char* buffer;
	(*reinterpret_cast<void(**)(std::intptr_t, char**)>(**(reinterpret_cast<std::intptr_t**>(a1) + 3) + 40))(*(a1 + 3), &buffer);

	std::string ret(buffer);

	*(reinterpret_cast<std::uint8_t*>(a1) + 64) = 1;

	return ret;
}

char helpers::fileaccessor_read(const std::intptr_t a1, const std::intptr_t a2, const std::intptr_t a3, const std::intptr_t a4, const std::int32_t a5)
{
	char result; // al

	if (const std::intptr_t v7 = *reinterpret_cast<std::uintptr_t*>(a1 + 1056))
		result = (*reinterpret_cast<std::intptr_t(**)(std::intptr_t, std::intptr_t, std::intptr_t, std::intptr_t, std::intptr_t, std::int32_t)>(*reinterpret_cast<std::intptr_t*>(v7) + 16))(
			v7,
			a1 + 8,
			a2,
			a3,
			a4,
			a5);
	else
		result = 0;
	return result;
}

char helpers::fileaccessor_seak(const std::intptr_t a1, const std::intptr_t a2, const std::uint32_t a3)
{
	char result; // al

	if (const std::intptr_t v5 = *reinterpret_cast<std::intptr_t*>(a1 + 1056))
		result = (*reinterpret_cast<std::intptr_t(**)(std::intptr_t, std::intptr_t, std::intptr_t, std::uintptr_t)>(*reinterpret_cast<std::uint64_t*>(v5) + 56))(v5, a1 + 8, a2, a3);
	else
		result = 0;
	return result;
}

std::int64_t helpers::fileaccessor_position(std::uint64_t* a1)
{
	std::int64_t result; // rax

	if (const int64_t v2 = *(a1 + 132))
		result = result = (*reinterpret_cast<std::int64_t(**)(std::int64_t, char*)>(*reinterpret_cast<std::uint64_t*>(v2) + 64))(v2, reinterpret_cast<char*>(a1) + 8);
	else
		result = 0;
	return result;
}

void helpers::unlock_persistentmanager(std::intptr_t* _this, const char a2)
{
	using unlock_t = void (*)(std::intptr_t*, char);
	static const auto unlock = memory::get_method_unity<unlock_t>(PERSISTENTMANAGER_UNLOCK);
	unlock(_this, a2);
}

void helpers::destroy_engineobject(std::intptr_t* _this, const char a2)
{
	using release_t = void (*)(std::intptr_t*, char);
	static const auto release = memory::get_method_unity<release_t>(DESTROYOBJECT_HIGHLEVEL);
	release(_this, a2);
}
