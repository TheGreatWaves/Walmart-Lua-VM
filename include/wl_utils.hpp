#pragma once
#ifndef WALMART_LUA_UTILS
#define WALMART_LUA_UTILS

#include <sstream>
#include <bitset>

// https://stackoverflow.com/questions/7349689/how-to-print-using-cout-a-number-in-binary-form
template<typename T>
std::string toBinaryString(const T& x)
{
    std::stringstream ss;
    ss << std::bitset<sizeof(T) * 8>(x);
    return ss.str();
}

/*
 * Casts
 */

[[ nodiscard ]] constexpr uint8_t to_u8(auto i) { return static_cast<uint8_t>(i); }

#endif /* WALMART_LUA_UTILS */