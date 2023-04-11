#include "opcodes.hpp"
#include "vm.hpp"
#include "decode.hpp"
#include <iostream>

int main() 
{
  // r[0] = 5
  // r[1] = 10
  // r[2] = 2
  // r[3] = 3

  // instr 1
  // r[4] = r[2] * r[3]
  //      = 2 * 3
  //      = 6
  //

  // instr 2
  // r[5] = r[0] + r[1]
  //      = 5 + 10
  //      = 15

  // instr 3
  // r[6] = r[5] - r[4]
  //      = 15 - 6
  //      = 9

  Instruction code[] = 
  {
    Instruction{static_cast<uint8_t>(OpCode::OP_MUL), 4, 2, 3},
    Instruction{static_cast<uint8_t>(OpCode::OP_ADD), 5, 0, 1},
    Instruction{static_cast<uint8_t>(OpCode::OP_SUB), 6, 5, 4},
    Instruction{static_cast<uint8_t>(OpCode::OP_HALT), 0, 0, 0}
  };

  VM vm(code);
  vm.registerFile.registers[0] = 5;
  vm.registerFile.registers[1] = 10;

  // Load two constants into registers 2 and 3
  vm.registerFile.registers[2] = 2;
  vm.registerFile.registers[3] = 3;

  vm.execute();

  // Print the final result
  std::cout << "Mul result: " << vm.registerFile.registers[4] << '\n';
  std::cout << "Add result: " << vm.registerFile.registers[5] << '\n';
  std::cout << "Sub result: " << vm.registerFile.registers[6] << '\n';

  return 0;
}
