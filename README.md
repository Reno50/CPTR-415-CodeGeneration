## CPTR-415: Compiler Construction - Compiler, now with code generation!

This project is a compiler for a subset of the Rust language, and compiles into mips code.
It is not complete, and it is missing some features. Still, when finished, it will have:
* Basic Arithmetic
* Boolean and 32-bit integer types
* Boolean and 32-bit integer array types, although support may be limited
* Support for functions, with allowed return types of integers and booleans
* While loops

## Building and running the compiler:
Included in the project is a makefile, and you can build the compiler with make installed by running the command:

> make all

To run the compiler, you can use the following command on a .ri source code file:

> ./rustish filename.ri