# Table of Contents
1. [Addressing Modes](#%20Addressing%20Modes)
2. [General Implementation](#%20General%20Implementation)
3. [Stack-based Model](#%20Stack%20Based%20Virtual%20Machines)

# Addressing Modes
In any assembly language numbers server multiple uses.

- Register numbers
- Immediate (scalar) values
- Memory addresses

# General Implementation
- Data structures to contain instructions and operands
- Call stack for function call operations
- Instruction Pointer
- A virtual CPU, which handles instruction dispatch

# Stack Based Virtual Machines
As the name suggests, the internal memory structure of a stack-based virtual machine is a stack. The stack data structure only allows two basic operations, which is pop and push (LIFO). Thanks to this simplicity, the stack-based virtual machine is quite simple, intuituve and easy to implement and maintain. However, as all things, this does come at a cost, the one downside of this design is that push and pop may be used extensively in many cases which could introduce performance related issues.

Take this example of what adding two numbers might look like:
```
POP 20
POP 7
ADD 20, 7, result
push result
```
As you can see, just two get our first two operands we require two different `POP` instructions, followed by the actual computation via `ADD` then finally recording the result via a final `PUSH`. Just for a mere adding operation we required 4 instructions.

An advantage of the stack-based model actually derives from its simplicity as well. Thanks to the fact that the operands have to be addressed by the stack pointer, this means that we never have to know or worry about any operand's address explicitly.