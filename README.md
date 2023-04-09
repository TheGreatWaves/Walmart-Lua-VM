# Walmart Lua VM
Walmart-Lua-VM is a personal hobby project exploring the realm of register-based virtual machines. Inspired by Lua's VM implementation, the project aims to implement a basic register-based virtual machine that follows Lua's design principles.

# Brief 
A virtual machine (VM) is a software construct which emulates a physical computer. While physical computers execute machine code, virtual machines execute bytecode, a more abstract form of machine code. In addition to allowing for the execution of bytecode, virtual machines have another important advantage: they allow programs to be run on different platforms without having to recompile the code for each platform. Because the virtual machine provides a layer of abstraction between the program and the physical hardware, the same bytecode can be executed on any platform that has a compatible virtual machine.

# Motivation
The vast majority of virtual machines used in programming languages are stack-based, including popular examples like the JVM, .NET CLR, and Python. However, this architecture has some limitations, such as difficulties in register allocation, increased memory usage due to the use of a stack, and slower performance for certain operations. The register-based virtual machine was developed to address these concerns.

In a register-based virtual machine, data is stored in registers rather than on a stack. This can reduce the number of memory operations required and lead to better performance. Additionally, register-based virtual machines provide more control over register allocation, which can lead to more efficient use of resources. The bytecode instructions used in a register-based virtual machine also tend to be simpler, which can make it easier to write and optimize a compiler for the virtual machine.

# References
[1] Ierusalimschy, R., et al. "The Implementation of Lua 5.0." Journal of Universal Computer Science, vol. 11, no. 7, 2005, pp. 1159-1176. [Online]. Available: https://www.lua.org/doc/jucs05.pdf
