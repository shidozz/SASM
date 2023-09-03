# Sasm Programming Language

## Introduction
Sasm (Shidozz Assembler) is a low-level programming language designed for system programming and low-level access to computer resources. This project contains the assembler for the Sasm language.

## Features
1) Hexadecimal notation: `(0x000000) to (0xFFFFFF)`
2) Registers: `A0-A9`, `B0-B4`, `ST`, `PR`, `CR`, `NX`
3) Keywords: `ret`, `add`, `rem`, `set`, `jmp`, `ver`, `jie`, `jin`, `jis`, `jii`, `global`, `extern`
## Getting Started
### Prerequisites
```
GCC Compiler
Make
```
## Compilation
### To compile the Sasm compiler:
```
make
```
This will produce an executable named `sasm.exe`.

### To assemble and run a Sasm program:

```bash
./sasm.exe your_program.sasm
```
## Examples
### Basic operation with registers:
```
global _start
    add A0 1
    ret
```
### Jump operations:
```
global _start
    add A0 5
    jmp A1
```
## Bytecode
For detailed on Bytecode, please refor to the [Bytecode](docs/Bytecode.md).

## Documentation
For detailed language specifications and advanced topics, please refer to the [Wiki](#) (coming soon).

## Contributing
Contributions are welcome! Please read the contributing guidelines before making a PR.

## License
This project is licensed under the MIT License. See [LICENSE.md](LICENSE.md) for details.