# Minimal Compiler for C-Minus

## Demonstration Link
- Demo video: https://drive.google.com/file/d/1NVpYBPGeRhmUV03PIhTDX4Cv3Z27W-Ii/view?usp=sharing 
- GitHub repository: https://github.com/DayanaGCruz/mini-compiler

## About
- Minimal C-Minus compiler for the C-Minus language specification in CST-405.
- Extended feature set beyond the course starter code: character literals, structured data (arrays and structs), function support, richer arithmetic, and detailed diagnostics.
- Adapted from course materials given at https://github.com/isac-artzi/CST-405.

## Quick Start
- Ensure `gcc`, `flex`, `bison`, and a MIPS runtime such as `spim` are installed.
- Spim is the command-line client for QtSpim from James Larus. Alternatively, run produced `output.s` MIPS file in QtSpim. 
- Build once with `make` from the project root; the binary `minicompiler` is produced.

## Language Features
- **Types**: `int`, `float`, `char`, and `void` (for function returns).
- **Expressions**: numeric and character literals, binary arithmetic `+ - * /`, nested subexpressions, implicit widening to `float` during evaluation.
- **Statements**: declarations, assignments, print statements, expression statements, and returns.
- **Functions**: function declarations with parameters, local scope handling, calls, and typed returns.
- **Arrays**: single-dimensional arrays of any primitive type with bounds checking during TAC generation.
- **Structs**: struct type definitions, struct variables, field assignment, and field access.
- **Characters**: character literals move through the scanner, parser, TAC, and MIPS code generation.
- **Optimization**: three-address code pass performs constant folding, copy propagation, and dead code elimination to remove unused temporaries and redundant assignments.
- **Diagnostics**: semantic checks emit detailed messages for undeclared identifiers, struct/array misuse, and type coercions.

## Tests
- `make test` or `tests/run_tests.sh` runs all positive samples, compares simulator output against the `.expected` baselines, and counts passes.
- `./minicompiler <input.cm> <output.s>` prints the full compilation trace and writes MIPS to `<output.s>`.

### Positive Samples (`tests/`)
- `arithmetic.cm` — integer arithmetic and subtraction sequences.
- `array.cm` — integer array declaration, stores, and loads.
- `float.cm` and `float_array.cm` — floating point locals and arrays.
- `functions.cm` — multi-function program with arguments and returns.
- `function_scope.cm` / `scope.cm` — nested scopes and shadowing.
- `mixed.cm` — combined structs, chars, arrays, and function calls.
- `order_of_ops.cm` — operator precedence and associativity coverage.
- `struct.cm` — struct declarations, assignments, and field access.
- `LQ16.cm` — regression exercise covering language basics.

### Negative Samples (`negative-tests/`)
- `array_and_struct_errors.cm` — demonstrates diagnostics for array bounds and missing struct fields.
- `dead_code_elimination.cm` — compiles successfully; serves as a reference for the optimizer removing unused assignments
- `identifer_errors.cm` - demonstrates diagnostics for identifier misuse and keyword/identifer typos. 

## GCU AI Policy Disclaimer
- ChatGPT Codex by OpenAI was utilized as an assistant in this project as allowed by the course-specific policy. 
