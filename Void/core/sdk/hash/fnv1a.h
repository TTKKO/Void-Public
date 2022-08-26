// ReSharper disable CppInconsistentNaming
#pragma once

/*
 * 32-BIT FNV1A HASH
 * much proper to use fnv1a instead crc32 with randomly access ~1kb
 * @credits: underscorediscovery
 */

namespace sdk::hash
{
    using fnv1a_t = std::uint32_t;

    namespace fnv1a
    {

        /* fnv1a constants */
    	constexpr std::uint32_t u_basis = 0x811c9dc5u;
    	constexpr std::uint32_t u_prime = 0x1000193u;

        /* create compile time hash */
        consteval fnv1a_t hash_const(const char* sz_string, const fnv1a_t u_value = u_basis) noexcept
        {
            return sz_string[0] == '\0' ? u_value : hash_const(&sz_string[1], (u_value ^ static_cast<fnv1a_t>(sz_string[0])) * u_prime);
        }

        /* create runtime hash */
        inline fnv1a_t hash(const char* sz_string, fnv1a_t u_value = u_basis)
        {
            for (std::size_t i = 0U; i < strlen(sz_string); ++i)
            {
                u_value ^= sz_string[i];
                u_value *= u_prime;
            }

            return u_value;
        }
    }
}