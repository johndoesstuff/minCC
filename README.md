# minCC – A Minimal C Compiler

minCC is a lightweight C compiler designed to support a significant subset of the C language. Built from scratch in C using Flex/Bison and using the LLVM api to deepen understanding of compiler design, parsing, and code generation.

## See it in action

Compile test raymarcher under `test/`

```
./minCC test/raymarcher.c -o test/raymarcher.ll
llc -relocation-model=pic test/raymarcher.ll -o test/raymarcher.s
clang test/raymarcher.s -o test/raymarcher -fPIE -lm
./test/raymarcher

Basic Raymarcher with Sphere SDF:

qkkkkkkkkkkqqqqqqwwS tttt1 FF|||(7    k bbUUUUUUUUUUUUUUUUUbb k    7(|||FF 1tttt Swwqqqqqqkkkkkkkkkk
kkkkkkkkkkkkkkqqqqwwS  FFFFFFFF||(   kPPP666  bbbbbbbbb  666PPPk   (||FFFFFFFF  Swwqqqqkkkkkkkkkkkkk
kkkkkkkkkkkkkkkqqqqwwS FFFFFFFFF||( qkPP6666666hhhhhhh6666666PPkq (||FFFFFFFFF Swwqqqqkkkkkkkkkkkkkk
kkkkkkkkkkkkkkkkqqqwwS |FFFFFFF||(7 kkPP666666hhhhhhhhh666666PPkk 7(||FFFFFFF| Swwqqqkkkkkkkkkkkkkkk
kkkkkkkkkkkkkkkkqqqqww  ||FFF||||(  qkPP666666hhhhhhhhh666666PPkq  (||||FFF||  wwqqqqkkkkkkkkkkkkkkk
kkkkkkkkkkkkkkkkqqqqwS   (||||((7    kPPP666666hhhhhhh666666PPPk    7((||||(   Swqqqqkkkkkkkkkkkkkkk
qkkkkkkkkkkkkkkqqqqwwS ooen    ///** kkPP66666666hhh66666666PPkk **///    neoo Swwqqqqkkkkkkkkkkkkkk
qqqqkkkkkkkkkqqqqqwwS ZZZZoo  ////**c kkPPP666666666666666PPPkk c**////  ooZZZZ Swwqqqqqkkkkkkkkkqqq
qqqqqqqqqqqqqqqqqwwS 555ZZZooe ****cr  qkPPPP66666666666PPPPkq  rc**** eooZZZ555 Swwqqqqqqqqqqqqqqqq
wwwwqqqqqqqqqqwwwwS555555ZZZoo  ccr      kkPPPPPPPPPPPPPPPkk      rcc  ooZZZ555555Swwwwqqqqqqqqqqwww
 ESSwwwwwwwwwwSS 555555555ZZZoe   ::::   5  kkkPPPPPPPkkk  5   ::::   eoZZZ555555555 SSwwwwwwwwwwSSE
t  |         ZZZ5555555555ZZoonC{   '    Z5YYY         YYY5Z    '   {CnooZZ5555555555ZZZ         |
t FFFFF||| eooZZZ5555555ZZZZoe CC{        5               5        {CC eoZZZZ5555555ZZZooe |||FFFFF
 FFFFFFFF|| nooZZZZZZZZZZZooe }}CC{      HHHHHHmmmmmmmHHHHHH      {CC}} eooZZZZZZZZZZZoon ||FFFFFFFF
FFFFFFFFF||(   eooooZZooooe }}}}CC   HHHmmmmmmmmmmmmmmmmmmmmmHHH   CC}}}} eooooZZooooe   (||FFFFFFFF
|FFFFFFF||(7 //*    een  }}}}}}C  HHHmmmmmmmm88888888888mmmmmmmmHHH  C}}}}}}  nee    *// 7(||FFFFFFF
(||||||||(7 ////**c   {CCCCCCC  HHmmmmmm888888888888888888888mmmmmmHH  CCCCCCC{   c**//// 7(||||||||
   (((7    ******cr :    {{{  HHmmmmm888888888888888888888888888mmmmmHH  {{{    : rc******    7(((
   qqkkkqq    ccr  :::'      HHmmmm8888888888888888888888888888888mmmmHH      ':::  rcc    qqkkkqq
kkPPPPPPPPPPkkk             Hmmmmm88888888888RRRRRRRRRRR88888888888mmmmmH             kkkPPPPPPPPPPk
bPPP666666PPPPPPkk         Hmmmm8888888888RRRRRRRRRRRRRRRRR8888888888mmmmH         kkPPPPPP666666PPP
Ub666666666666PPPPkq 5555 HHmmm888888888RRRRRRRRRRRRRRRRRRRRR888888888mmmHH 5555 qkPPPP666666666666b
UU 6666666666666PPPkk YY HHmmmm88888888RRRRRRRRRRRRRRRRRRRRRRR88888888mmmmHH YY kkPPP6666666666666 U
UUb66hhhhh66666666PPkk Y HHmmm88888888RRRRRRRRRRRRRRRRRRRRRRRRR88888888mmmHH Y kkPP66666666hhhhh66bU
UUb hhhhhhhh666666PPPk   Hmmmm88888888RRRRRRRRRRRRRRRRRRRRRRRRR88888888mmmmH   kPPP666666hhhhhhhh bU
UUb hhhhhhhhh66666PPPk   Hmmmm8888888RRRRRRRRRRRRRRRRRRRRRRRRRRR8888888mmmmH   kPPP66666hhhhhhhhh bU
UUb hhhhhhhh666666PPPk   Hmmmm88888888RRRRRRRRRRRRRRRRRRRRRRRRR88888888mmmmH   kPPP666666hhhhhhhh bU
UUb66hhhhh66666666PPkk Y HHmmm88888888RRRRRRRRRRRRRRRRRRRRRRRRR88888888mmmHH Y kkPP66666666hhhhh66bU
UU 6666666666666PPPkk YY HHmmmm88888888RRRRRRRRRRRRRRRRRRRRRRR88888888mmmmHH YY kkPPP6666666666666 U
Ub666666666666PPPPkq 5555 HHmmm888888888RRRRRRRRRRRRRRRRRRRRR888888888mmmHH 5555 qkPPPP666666666666b
bPPP666666PPPPPPkk         Hmmmm8888888888RRRRRRRRRRRRRRRRR8888888888mmmmH         kkPPPPPP666666PPP
kkPPPPPPPPPPkkk             Hmmmmm88888888888RRRRRRRRRRR88888888888mmmmmH             kkkPPPPPPPPPPk
   qqkkkqq    ccr  :::'      HHmmmm8888888888888888888888888888888mmmmHH      ':::  rcc    qqkkkqq
   (((7    ******cr :    {{{  HHmmmmm888888888888888888888888888mmmmmHH  {{{    : rc******    7(((
(||||||||(7 ////**c   {CCCCCCC  HHmmmmmm888888888888888888888mmmmmmHH  CCCCCCC{   c**//// 7(||||||||
|FFFFFFF||(7 //*    een  }}}}}}C  HHHmmmmmmmm88888888888mmmmmmmmHHH  C}}}}}}  nee    *// 7(||FFFFFFF
FFFFFFFFF||(   eooooZZooooe }}}}CC   HHHmmmmmmmmmmmmmmmmmmmmmHHH   CC}}}} eooooZZooooe   (||FFFFFFFF
 FFFFFFFF|| nooZZZZZZZZZZZooe }}CC{      HHHHHHmmmmmmmHHHHHH      {CC}} eooZZZZZZZZZZZoon ||FFFFFFFF
t FFFFF||| eooZZZ5555555ZZZZoe CC{        5               5        {CC eoZZZZ5555555ZZZooe |||FFFFF
t  |         ZZZ5555555555ZZoonC{   '    Z5YYY         YYY5Z    '   {CnooZZ5555555555ZZZ         |
 ESSwwwwwwwwwwSS 555555555ZZZoe   ::::   5  kkkPPPPPPPkkk  5   ::::   eoZZZ555555555 SSwwwwwwwwwwSSE
wwwwqqqqqqqqqqwwwwS555555ZZZoo  ccr      kkPPPPPPPPPPPPPPPkk      rcc  ooZZZ555555Swwwwqqqqqqqqqqwww
qqqqqqqqqqqqqqqqqwwS 555ZZZooe ****cr  qkPPPP66666666666PPPPkq  rc**** eooZZZ555 Swwqqqqqqqqqqqqqqqq
qqqqkkkkkkkkkqqqqqwwS ZZZZoo  ////**c kkPPP666666666666666PPPkk c**////  ooZZZZ Swwqqqqqkkkkkkkkkqqq
qkkkkkkkkkkkkkkqqqqwwS ooen    ///** kkPP66666666hhh66666666PPkk **///    neoo Swwqqqqkkkkkkkkkkkkkk
kkkkkkkkkkkkkkkkqqqqwS   (||||((7    kPPP666666hhhhhhh666666PPPk    7((||||(   Swqqqqkkkkkkkkkkkkkkk
kkkkkkkkkkkkkkkkqqqqww  ||FFF||||(  qkPP666666hhhhhhhhh666666PPkq  (||||FFF||  wwqqqqkkkkkkkkkkkkkkk
kkkkkkkkkkkkkkkkqqqwwS |FFFFFFF||(7 kkPP666666hhhhhhhhh666666PPkk 7(||FFFFFFF| Swwqqqkkkkkkkkkkkkkkk
kkkkkkkkkkkkkkkqqqqwwS FFFFFFFFF||( qkPP6666666hhhhhhh6666666PPkq (||FFFFFFFFF Swwqqqqkkkkkkkkkkkkkk
kkkkkkkkkkkkkkqqqqwwS  FFFFFFFF||(   kPPP666  bbbbbbbbb  666PPPk   (||FFFFFFFF  Swwqqqqkkkkkkkkkkkkk
```


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
./minCC [-o output.ll] <input file>
```

This will produce an output.ll file containing the LLVM IR.

To compile the LLVM IR to an executable:

```bash
llc -relocation-model=pic output.ll -o output.s
clang output.s -o output -fPIE -lm
```

Then, run your program:

```bash
./output
```

## Testing

To ensure the compiler is working properly test programs are provided under the `test/` and can be found in `unit_tests.c`
