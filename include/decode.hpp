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

struct Instr_ABC {uint8_t A; uint8_t B; uint8_t C; };

#define GET_OPCODE(i) (static_cast<OpCode>(((i)>>POS_OP) & MASK1(SIZE_OP, 0)))
#define SET_OPCODE(i, o) ((i) = (((i) & MASK0(SIZE_OP, POS_OP)) | ((static_cast<uint32_t>(o) << POS_OP) & MASK1(SIZE_OP, POS_OP))))

#define getarg(i, pos, size) (static_cast<int>(((i)>>(pos)) & MASK1(size, 0)))
#define setarg(i, v, pos, size) ((i) = (((i) & MASK0(size, pos)) | ((static_cast<uint32_t>(v) << pos) & MASK1(size, pos))))

#define GET_ARG_A(i)  to_u8(getarg(i, POS_A,SIZE_A ))
#define SETARG_A(i,v)   setarg(i, v, POS_A,SIZE_A )

#define GET_ARG_B(i)   to_u8(getarg(i, POS_B,SIZE_B ))
#define SETARG_B(i,v)   setarg(i, v, POS_B,SIZE_B )

#define GET_ARG_C(i)   to_u8(getarg(i, POS_C,POS_C ))
#define SETARG_C(i,v)   setarg(i, v, POS_C,SIZE_C )

#undef ARG_INFO

#define decode_op(instr) GET_OPCODE(instr)
#define decode_ABC(instr) Instr_ABC { GET_ARG_A(instr), GET_ARG_B(instr), GET_ARG_C(instr) }

#endif /* WALMART_LUA_DECODE */