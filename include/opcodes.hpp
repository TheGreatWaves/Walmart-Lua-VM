/*
 * This header file defines the opcodes used by the Walmart Lua VM.
 * The opcodes are defined as an enum class called OpCode, and also
 * provides functions for converting between the enum values and
 * string representations.
 */

#pragma once
#ifndef WALMART_LUA_OPCODES
#define WALMART_LUA_OPCODES

#include <cstdint>
#include <stdexcept>
#include <string_view>

#define OPCODE(x)                                                            \
  /*----------------------------------------------------------------------   \
  name                args    description                                    \
  ------------------------------------------------------------------------*/ \
  x(OP_LOADK)     /*  A B     R(A) := Kst(Bx)                             */ \
  x(OP_GETGLOBAL) /*  A Bx    R(A) := Gbl[Kst(Bx)]                        */ \
  x(OP_SETGLOBAL) /*  A Bx    Gbl[Kst(Bx)] := R(A)                        */ \
  x(OP_ADD)       /*  A B C   R(A) := RK(B) + RK(C)                       */ \
  x(OP_SUB)       /*  A B C   R(A) := RK(B) - RK(C)                       */ \
  x(OP_MUL)       /*  A B C   R(A) := RK(B) * RK(C)                       */ \
  x(OP_DIV)       /*  A B C   R(A) := RK(B) / RK(C)                       */ \
  x(OP_HALT)

// define the enum class for opcodes
#define ENUM(opcode) opcode,
enum class OpCode : uint8_t { OPCODE(ENUM) OP_COUNT };
#undef ENUM

#define NUM_OPCODES static_cast<int>(OpCode::OP_COUNT)

// define a macro to convert an opcode to a string
#define STR_HELPER(X) std::string_view(#X)
#define OPCODE_STR(opcode) case OpCode::opcode: return STR_HELPER(opcode);

[[nodiscard]] inline auto nameof(OpCode opcode) -> std::string_view 
{
  switch (opcode) 
  {
    OPCODE(OPCODE_STR)
    default: throw std::invalid_argument("Unexpected Opcode");
  }
}

#undef OPCODE_STR
#undef STR_HELPER

inline std::ostream &operator<<(std::ostream &os, OpCode opcode) 
{
  os << nameof(opcode);
  return os;
}

[[nodiscard]] auto decode(uint8_t opcode) -> OpCode 
{
  return static_cast<OpCode>(opcode);
}

#endif /* WALMART_LUA_OPCODES */