/*
 *		assembler/il2cpp/array_wrapper.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's wrapper around il2cpp's arrays
 */
#pragma once
#include "structures/structures.h"

namespace assembler::il2cpp
{
	template <typename T>
	// ReSharper disable once CppInconsistentNaming
	struct il2cpp_array_wrapper : il2cpp_array
	{
		T* p_values = nullptr;

		std::uintptr_t get_data()
		{
			return reinterpret_cast<std::uintptr_t>(&p_values);
		}

		T& operator[](const il2cpp_array_size_t u_index)
		{
			return *reinterpret_cast<T*>(get_data() + sizeof(T) * u_index);
		}

		T& at(const il2cpp_array_size_t u_index)
		{
			return operator[](u_index);
		}

		void insert(T* p_array, il2cpp_array_size_t u_size, const std::uintptr_t u_index = 0)
		{
			if (u_size + u_index >= max_length)
			{
				if (u_index >= max_length)
					return;

				u_size = max_length - u_index;
			}

			for (std::uintptr_t u = 0; u_size > u; ++u)
				operator[](u + u_index) = p_array[u];
		}

		void fill(T t_value)
		{
			for (std::uintptr_t u = 0; max_length > u; ++u)
				operator[](u) = t_value;
		}

		void remove_at(const il2cpp_array_size_t u_index)
		{
			if (u_index >= max_length)
				return;

			if (max_length > u_index + 1)
			{
				for (il2cpp_array_size_t u = u_index; max_length - u_index > u; ++u)
					operator[](u) = operator[](u + 1);
			}

			--max_length;
		}

		void remove_range(const il2cpp_array_size_t u_index, std::uint32_t u_count)
		{
			if (u_index == 0)
				u_count = 1;

			const il2cpp_array_size_t u_total = u_index + u_count;
			if (u_total >= max_length)
				return;

			if (max_length > u_total + 1)
			{
				for (il2cpp_array_size_t u = u_index; max_length - u_total >= u; ++u)
					operator[](u) = operator[](u + u_count);
			}

			max_length -= u_count;
		}

		void clear()
		{
			if (max_length > 0)
			{
				memset(get_data(), 0, sizeof(T) * max_length);
				max_length = 0;
			}
		}
	};
}
