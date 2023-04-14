#pragma once
#ifndef WALMART_LUA_VM
#define WALMART_LUA_VM

#include <vector>
#include "decode.hpp"

#define THREADED_CODE

#ifdef THREADED_CODE
  #define DISPATCH(opcode) goto *jumpTable[ opcode ];
  #define INSTR(opcode) lbl_##opcode
  #define NEXT continue
#else
  #define DISPATCH(opcode) switch( opcode )
  #define INSTR(opcode) case static_cast<int>( OpCode::opcode )
  #define NEXT break
#endif 

/* Maximum size of the stack */
constexpr size_t MAX_STACK_SIZE{1000};

/* Maximum number of registers */
constexpr uint8_t MAX_REGISTERS{255};

/* Max number of instructions */
constexpr size_t MAX_INSTRUCTIONS{10000};

/* Max number of constants */
constexpr uint8_t MAX_CONSTANTS{255};

/*
 * An instruction is 32 bits long.
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
  encoded |= static_cast<uint32_t>(instruction.opcode) << 26;
  encoded |= static_cast<uint32_t>(instruction.a) << 18;
  encoded |= static_cast<uint32_t>(instruction.b) << 9;
  encoded |= static_cast<uint32_t>(instruction.c);
  return encoded;
}

struct RegisterFile 
{
  int registers[MAX_REGISTERS];
};

struct Stack 
{
  std::vector<int> values;
  int *top; // Pointer to the top of the stack.

  Stack() 
  {
    values.reserve(MAX_STACK_SIZE);
    top = nullptr;
  }

  void push(int value) 
  {
    if (values.size() < MAX_STACK_SIZE) 
    {
      values.push_back(value);
      top = &values.back(); // Update the pointer to the last element
    } 
    else 
    {
      // Stack overflow error
      throw std::overflow_error("Stack overflow");
    }
  }

  [[nodiscard]] int pop() 
  {
    if (values.size() > 0) 
    {
      int value = values.back();
      values.pop_back();

      if (values.size() > 0) 
      {
        top = &values.back();
      } 
      else 
      {
        top = nullptr;
      }
      return value;
    } 
    else 
    {
      // Stack underflow error
      throw std::underflow_error("Stack underflow)");
    }
  }

  [[nodiscard]] auto peek() -> int 
  {
    if (values.size() > 0) {
      return values.back();
    } else {
      // Empty stack error
      throw std::runtime_error("Stack is empty");
    }
  }

  [[nodiscard]] bool empty() noexcept { return values.empty(); };

  [[nodiscard]] bool full() noexcept { return values.size() == MAX_STACK_SIZE; };
};

struct VM 
{
  Instruction *instructions;
  RegisterFile registerFile;
  Stack stack;

  uint8_t instructionPointer;
  uint8_t stackPointer;

  int constants[MAX_CONSTANTS];

  VM(Instruction *instructions)
      : instructions(instructions), instructionPointer(0), stackPointer(0) {}

  void execute() 
  {
    #ifdef THREADED_CODE
    #define LABEL(opcode) &&lbl_##opcode,
    static const void *jumpTable[] = 
    {
      OPCODE(LABEL)
    };
    #undef LABEL
    #endif

    auto &r = registerFile.registers;

    while (instructionPointer < MAX_INSTRUCTIONS) 
    {
      // Fetch instruction
      auto &instruction = instructions[instructionPointer];
      auto instr = encode_instruction(instruction);
      auto opcode = decode_op(instr);
      auto [a, b, c] = decode_ABC(instr);

      // Move to next instruction
      instructionPointer++;


      DISPATCH(static_cast<int>(opcode))
      {

        INSTR(OP_ADD): 
        {
          r[a] = r[b] + r[c];
          NEXT;
        }

        INSTR(OP_MUL): 
        {
          r[a] = r[b] * r[c];
          NEXT;
        }

        INSTR(OP_SUB): 
        {
          r[a] = r[b] - r[c];
          NEXT;
        }

        INSTR(OP_DIV): 
        {
          r[a] = r[b] / r[c];
          NEXT;
        }

        INSTR(OP_HALT): { return; }
        INSTR(OP_LOADK): { NEXT; }
        INSTR(OP_GETGLOBAL): { NEXT; }
        INSTR(OP_SETGLOBAL): { NEXT; }

      }
    }
  }
};

#endif /* WALMART_LUA_VM */
