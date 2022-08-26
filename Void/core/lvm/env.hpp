#pragma once
#ifndef VENV_HPP
#define VENV_HPP

#include "../hooks/events.hpp"

#if LVM_TESTING == 1

#include "sol2/sol.hpp"

namespace vlvm::env
{
	inline sol::state lua{};

	void print(const sol::variadic_args& va);
	void warn(const sol::variadic_args& va);
	void error(const sol::variadic_args& va);

	bool register_globals(sol::state& lua);
	bool register_vector3(sol::state& lua);
	bool register_quaternion(sol::state& lua);
	bool register_color(sol::state& lua);

}

#endif

#endif