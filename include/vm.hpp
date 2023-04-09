#pragma once
#ifndef WALMART_LUA_VM
#define WALMART_LUA_VM

#include <vector>

/* Maximum size of the stack */
constexpr uint MAX_STACK_SIZE{1000};

/* Maximum number of registers */
constexpr uint8_t MAX_REGISTERS{255};

/* Max number of instructions */
constexpr uint MAX_INSTRUCTIONS{10000};

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

  VM(Instruction *instructions)
      : instructions(instructions), instructionPointer(0), stackPointer(0) {}

  void execute() 
  {
    #define LABEL(opcode) &&opcode,
    static const void *jumpTable[] = 
    {
        &&OP_ADD,
        &&OP_MUL,
        &&OP_HALT,
        &&OP_SUB,
    };
    #undef LABEL

    auto &r = registerFile.registers;

    while (instructionPointer < MAX_INSTRUCTIONS) 
    {
      // Fetch instruction
      auto &instruction = instructions[instructionPointer];
      auto opcode = decode(instruction.opcode);
      auto [_, a, b, c] = instruction;

      // Move to next instruction
      instructionPointer++;

      // TODO: REMOVE THIS
      auto opcode_idx = 0;

      switch (opcode) {
        break;
      case OpCode::OP_ADD:
        opcode_idx = 0;
        break;
      case OpCode::OP_MUL:
        opcode_idx = 1;
        break;
      case OpCode::OP_HALT:
        opcode_idx = 2;
        break;
      case OpCode::OP_SUB:
        opcode_idx = 3;
      }

      // Jump to the opcode handler
      goto *jumpTable[opcode_idx];

    OP_ADD : 
    {
      r[a] = r[b] + r[c];
      continue;
    }

    OP_MUL : 
    {
      r[a] = r[b] * r[c];
      continue;
    }

    OP_SUB : 
    {
      r[a] = r[b] - r[c];
      continue;
    }

    OP_HALT : { break; }
    }
  }
};

#endif /* WALMART_LUA_VM */
