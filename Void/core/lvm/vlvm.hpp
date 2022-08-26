// ReSharper disable CppInconsistentNaming
#pragma once
#ifndef VLVM_HPP
#define VLVM_HPP

#include "env.hpp"

#if LVM_TESTING == 1

namespace vlvm
{
	inline std::string queued_script{};

	bool initialize();
	void do_script(std::string_view sz);
}

#endif

#endif