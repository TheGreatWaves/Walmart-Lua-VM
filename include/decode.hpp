#pragma once
#ifndef WALMART_LUA_DECODE
#define WALMART_LUA_DECODE

#include "opcodes.hpp"

/*
 * Size and position of opcode arguments. (Straight from lua)
 */
#define SIZE_C          9
#define SIZE_B          9
#define SIZE_Bx         (SIZE_C + SIZE_B)
#define SIZE_A          8

#define SIZE_OP         6

#define POS_OP          0
#define POS_A           (POS_OP + SIZE_OP)
#define POS_C           (POS_A + SIZE_A)
#define POS_B           (POS_C + SIZE_C)
#define POS_Bx          POS_C

namespace walmart_lua
{
  [[nodiscard]] auto get_op(uint8_t opcode) -> OpCode 
  {
    return static_cast<OpCode>(opcode);
  }

  [[nodiscard]] auto decode_opcode(uint32_t instruction) -> uint8_t 
  {
    return (instruction >> 26) & 0x3F; 
  }

  [[nodiscard]] auto decode_A(uint32_t instruction) -> uint8_t
  {

    return ((instruction >> 18) & 0xFF);
  }
  
  [[nodiscard]] auto decode_B(uint32_t instruction) -> uint8_t
  {
    return (instruction >> 9) & 0x1FF;
  }

  [[nodiscard]] auto decode_C(uint32_t instruction) -> uint8_t
  {
    return (instruction & 0x1FF);
  }
}

struct Instr_ABC {uint8_t A; uint8_t B; uint8_t C; };

#define decode_op(instr) walmart_lua::get_op(walmart_lua::decode_opcode(instr))
#define decode_ABC(instr) Instr_ABC { walmart_lua::decode_A(instr), walmart_lua::decode_B(instr), walmart_lua::decode_C(instr) }

#endif /* WALMART_LUA_DECODE */