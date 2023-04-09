/*
 * This header file defines the opcodes used by the Walmart Lua VM.
 * The opcodes are defined as an enum class called OpCode, and also
 * provides functions for converting between the enum values and
 * string representations.
 */




#pragma once
#ifndef WALMART_LUA_OPCODES
#define WALMART_LUA_OPCODES

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
  x(OP_DIV)       /*  A B C   R(A) := RK(B) / RK(C)                       */

// define the enum class for opcodes
#define ENUM(opcode) opcode,
enum class OpCode
{
    OPCODE( ENUM )
};
#undef ENUM

// define a macro to convert an opcode to a string
#define OPCODE_STR(opcode) case OpCode::opcode: return #opcode;
[[ nodiscard ]] inline std::string_view nameof(OpCode opcode)
{
  switch (opcode)
  {
    OPCODE( OPCODE_STR )
    default: throw std::invalid_argument("Unexpected Opcode");
  }
}
#undef OPCODE_STR

inline std::ostream& operator<<(std::ostream &os, OpCode opcode)
{
  os << nameof(opcode);
  return os;
}

#endif /* WALMART_LUA_OPCODES */