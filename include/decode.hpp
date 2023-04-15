#pragma once
#ifndef WALMART_LUA_DECODE
#define WALMART_LUA_DECODE

#include "instruction.hpp"

namespace walmart_lua
{
  [[nodiscard]] auto get_op(uint8_t opcode) -> OpCode 
  {
    return static_cast<OpCode>(opcode);
  }

  [[nodiscard]] auto decode_opcode(uint32_t instruction) -> uint8_t 
  {
    return (instruction >> POS_OP) & MASK1(SIZE_OP, 0);
  }

  [[nodiscard]] auto decode_A(uint32_t instruction) -> uint8_t
  {

    return ((instruction >> POS_A) & MASK1(SIZE_A, 0));
  }
  
  [[nodiscard]] auto decode_B(uint32_t instruction) -> uint8_t
  {
    return (instruction >> POS_B) & MASK1(SIZE_B, 0);
  }

  [[nodiscard]] auto decode_C(uint32_t instruction) -> uint8_t
  {
    return (instruction >> POS_C) & MASK1(SIZE_C, 0);
  }
}

struct Instr_ABC {uint8_t A; uint8_t B; uint8_t C; };

#define decode_op(instr) walmart_lua::get_op(walmart_lua::decode_opcode(instr))
#define decode_ABC(instr) Instr_ABC { walmart_lua::decode_A(instr), walmart_lua::decode_B(instr), walmart_lua::decode_C(instr) }

#endif /* WALMART_LUA_DECODE */