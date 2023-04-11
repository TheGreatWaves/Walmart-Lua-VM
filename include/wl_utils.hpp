#pragma once
#ifndef WALMART_LUA_UTILS
#define WALMART_LUA_UTILS

#include <sstream>
#include <bitset>

template<typename T>
static std::string toBinaryString(const T& x)
{
    std::stringstream ss;
    ss << std::bitset<sizeof(T) * 8>(x);
    return ss.str();
}

#endif /* WALMART_LUA_UTILS */