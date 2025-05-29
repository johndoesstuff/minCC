# minCC – A Minimal C Compiler

minCC is a lightweight C compiler designed to support a significant subset of the C language. Built from scratch in C using Flex/Bison and using the LLVM api to deepen understanding of compiler design, parsing, and code generation.

## Features

### Language Constructs

- **Control Flow**: `if`, `else`, `while`, `for`, `return` statements
- **Functions**: Declaration, definition, and invocation
- **Variable Operations**:
  - Declarations and assignments
  - Compound assignments: `=`, `+=`, `-=`, `*=`, `/=`
  - Increment (`++`) and decrement (`--`) operators
- **Pointers**:
  - Dereferencing and pointer arithmetic
  - Arbitrary pointer depth
  - Pass-by-reference semantics
- **Types Supported**:
  - Primitive types: `int`, `bool`, `char`, `float`, `double`, `short`, `long`
  - Strings as `char*` with escape sequences (`\n`, `\t`, `\0`)
- **Type Coercion**:
  - Implicit conversions
  - Variadic function promotion
- **Operators**:
  - Arithmatic operators: `+`, `-`, `*`, `/`, `%`
  - Comparison operators: `==`, `!=`, `<`, `>`, `<=`, `>=`
  - Logical operators: `&&`, `||`
- **Scopes**: Proper variable scoping and shadowing
- **Error Handling**: Descriptive error messages for easier debugging
- (UNDER CONSTRUCTION) **Standard Library Integration**: Supports native functions like `printf`

### Compilation Details

- **Input**: C-like source code
- **Output**: LLVM Intermediate Representation (IR) for further compilation or execution

## Installation

1. **Clone the repository**:

```bash
git clone https://github.com/johndoesstuff/minCC.git
cd minCC
```

2. **Build the compiler**:

```bash
make
```

This will generate the minCC executable in the project directory.

## Usage

To compile a source file:

```bash
./minCC path/to/source.c
```

This will produce an output.ll file containing the LLVM IR.

To compile the LLVM IR to an executable:

```bash
llc output.ll -o output.s
clang output.s -o output
```

Then, run your program:

```bash
./output
```

## Testing

To ensure the compiler is working properly test programs are provided under the `test/` and can be found in `unit_tests.c`
