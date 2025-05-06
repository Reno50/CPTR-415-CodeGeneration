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

This makes a file called

> test.asm

You can assemble this file in a MIPS assembler such as Mars, and it will compile up to level 3 complexity rustish, as defined by Dr. Halterman externally.

## Limitations

Typechecking:
* If/Else statement error line is garbage value
* Array typechecking is iffy
* Array literals don't work yet
* When checking for return statements, while statements will not have their statements checked - doing a comprehensive data flow analysis is the only way of truly implementing this feature

For the code generation step, I quieted (commented) all of the standard output error messages.
The limitations of our code, in accordance to level 3 rustish, is as follows:
* No arrays - don't even try - unless Caleb commited his changes, and they may work
* Functions CAN work, but are not GUARENTEED to work - some scenarios work, but multiple function calls in one expression seems to cause issues
* read() may or may not have issues, I haven't done enough testing - it isn't part of any specific stage though