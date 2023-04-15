#pragma once
#ifndef WALMART_LUA_INSTRUCTION
#define WALMART_LUA_INSTRUCTION

#include "wl_utils.hpp"
// This file mostly mirrors lua's source, namely lopcodes.h

/* Lua assume that instructions are unsigned numbers.
 * An opcode can be identified by the first 6 bits.
 * Instructions are as follows:
 *   'A'   : 8 bits
 *   'B'   : 9 bits
 *   'C'   : 9 bits
 *   'Bx'  : ('B' and 'C')
 *   'sBx' : signed Bx
 */

enum class OpMode {iABC,iABx};

/*
 * Size of opcode arguments (referenced from lua source)
 */
#define SIZE_OP    7
#define SIZE_A     8
#define SIZE_B     8
#define SIZE_C     8
#define SIZE_Bx    (SIZE_B+SIZE_C+1)


/*
 * Position of opcode arguments (referenced from lua source)
 */
#define POS_OP  0
#define POS_A   (POS_OP+SIZE_OP)
#define POS_k   (POS_A+SIZE_A)
#define POS_B   (POS_k+1)
#define POS_C   (POS_B+SIZE_B)
#define POS_Bx  POS_k


/*
 * Macro util
 */
// Creates a mask of 'n' 1s followed by p 0s (rhs)
#define MASK1(n,p)   ((~((~(static_cast<uint32_t>(0)))<<n))<<p)

// Creates a mask of 'n' 0s followed by p 1s (rhs)
#define MASK0(n,p)   (~MASK1(n,p))

/*
 * An instruction is 32 bits long.
 * Standard ABC
 */
struct Instruction 
{
  uint8_t opcode;
  uint8_t a;
  uint8_t b;
  uint8_t c;
};

[[nodiscard]] auto encode_instruction(const Instruction& instruction) -> uint32_t {
  uint32_t encoded = 0;
  encoded |= static_cast<uint32_t>(instruction.opcode);
  encoded |= static_cast<uint32_t>(instruction.a) << POS_A;
  encoded |= static_cast<uint32_t>(instruction.b) << POS_B;
  encoded |= static_cast<uint32_t>(instruction.c) << POS_C;

  return encoded;
}

#endif /* WALMART_LUA_INSTRUCTION */
