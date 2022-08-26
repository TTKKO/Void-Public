#pragma once

#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <cstdint>
#include "../../../globals.hpp"

#define STATUS_OUT_OF_BOUNDS       (0xe0000000ul)
#define STATUS_ARRAY_OVERFLOW      (0xe0000001ul)
#define STATUS_BAD_ALLOCATION      (0xe0000002ul)
#define STATUS_BAD_POINTER         (0xe0000003ul)
#define STATUS_CLEANUP             (0xe0000004ul)

namespace helpers
{
	bool is_oob(std::intptr_t* a1, std::intptr_t a2, std::intptr_t a3);
    std::string fetch_oob(std::intptr_t* a1);
    char fileaccessor_read(std::intptr_t a1, std::intptr_t a2, std::intptr_t a3, std::intptr_t a4, std::int32_t a5);
    char fileaccessor_seak(std::intptr_t a1, std::intptr_t a2, std::uint32_t a3);
    std::int64_t fileaccessor_position(std::uintptr_t* a1);
    void unlock_persistentmanager(std::intptr_t* _this, char a2);
    void destroy_engineobject(std::intptr_t* _this, char a2);


}

#endif
