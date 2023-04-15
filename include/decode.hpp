#pragma once
#ifndef WALMART_LUA_DECODE
#define WALMART_LUA_DECODE

#include "instruction.hpp"

#define GET(ARG) (instruction>>POS_##ARG) & MASK1(SIZE_##ARG, 0)

#define ARGS(x) \
  x(OP) \
  x(A) \
  x(B) \
  x(C) 

namespace walmart_lua
{
  [[nodiscard]] auto get_op(uint8_t opcode) -> OpCode 
  {
    return static_cast<OpCode>(opcode);
  }

  #define MAKE_DECODE_FN(arg) [[nodiscard]] auto decode_##arg(uint32_t instruction) -> uint8_t { return GET(arg); }
  ARGS(MAKE_DECODE_FN)
  #undef MAKE_DECODE_FN
}

struct Instr_ABC {uint8_t A; uint8_t B; uint8_t C; };

#define decode_op(instr) walmart_lua::get_op(walmart_lua::decode_OP(instr))
#define decode_ABC(instr) Instr_ABC { walmart_lua::decode_A(instr), walmart_lua::decode_B(instr), walmart_lua::decode_C(instr) }

#endif /* WALMART_LUA_DECODE */