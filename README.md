# Minimal Compiler for C-Minus

## Demonstration Link
- Demo video: https://drive.google.com/file/d/1NVpYBPGeRhmUV03PIhTDX4Cv3Z27W-Ii/view?usp=sharing 
- GitHub repository: https://github.com/DayanaGCruz/mini-compiler

## About
- Minimal C-Minus compiler for the C-Minus language specification in CST-405.
- Extended feature set beyond the course starter code: character literals, structured data (arrays and structs), function support, richer arithmetic, conditional control flow, and detailed diagnostics.
- Adapted from course materials given at https://github.com/isac-artzi/CST-405.

## Quick Start
- Ensure `gcc`, `flex`, `bison`, and a MIPS runtime such as `spim` are installed.
- Spim is the command-line client for QtSpim from James Larus. Alternatively, run produced `output.s` MIPS file in QtSpim. 
- Build once with `make` from the project root; the binary `minicompiler` is produced.

## Language Features
- **Scalar types & literals**: `int`, `float` (supports decimal/scientific input), `char` with standard escape sequences, `bool` via `true`/`false`, and `void` for procedures.
- **Aggregates**: single-dimensional arrays for any scalar type plus `struct` definitions, struct variables, field assignment, and nested field access.
- **Expressions**: arithmetic `+ - * /`, relational `< > <= >=`, equality `== !=`, logical `&& || !`, ternary `?:`, implicit int→float promotion, array/struct access, and function calls.
- **Statements & control flow**: variable and array declarations, assignments, expression statements, `print`, `return` (with or without a value), blocks, `if`/`else`, and `switch` with `case`, `default`, and `break` handling.
- **Functions & scope**: top-level function declarations with typed parameters (scalars, arrays, or structs), local scope creation, and typed returns.
- **Comments & tokens**: line (`//`) and block (`/* ... */`) comments, full keyword/token coverage for the grammar, and column-aware location tracking.
- **Diagnostics & optimization**: lexer/parser errors highlight line numbers and suggest keywords, semantic checks catch undeclared identifiers and type misuse, and the TAC optimizer performs constant folding, copy propagation, and dead-code elimination before MIPS generation.

## Tests
- Build once with `make` to produce `./minicompiler`, place `spim` on your `PATH`, then run `tests/run_tests.sh` to compile every sample, execute it in SPIM, and diff the output against each `.expected` file.
- `make test` is a convenience loop that emits the generated `.s` files and SPIM output for each sample; it does **not** compare against the baselines.
- Run a single program manually with `./minicompiler tests/<file>.cm out.s && spim out.s`.

### Positive samples with `.expected` baselines (`tests/`)
- `arithmetic.cm` – integer math pipeline sanity check.
- `array.cm` – scalar arrays, indexed writes/reads, and bounds tracking.
- `conditionals.cm` – nested `if`/`else` chains and boolean expressions.
- `float.cm` / `float_array.cm` – floating-point locals plus aggregated storage.
- `functions.cm` – mutually recursive functions, argument passing, and typed returns.
- `function_scope.cm` / `scope.cm` – lexical scoping, shadowing, and block-local lifetimes.
- `mixed.cm` – structs, chars, arrays, and function calls in one program.
- `order_of_ops.cm` – precedence/associativity plus parentheses regression.
- `struct.cm` – struct definitions, field assignments, and nested access.
- `switch.cm` – multi-`case` switches, fall-through prevention, and `default` coverage.
- `LQ16.cm` – reference implementation from the course exercise.

### Additional positive inputs (manual inspection)
- `test_functions_only.cm` – stress test for chained function calls (no `.expected`, run via `make test`).
- `test_with_if_statements.cm` – ad-hoc conditional stress test for manual inspection.

### Diagnostics & optimizer samples (`negative-tests/`)
- `array_and_struct_errors.cm` – reports array bound violations and struct field mismatches.
- `dead_code_elimination.cm` – compiles, but captures redundant assignments so you can inspect TAC/optimizer output.
- `identifier_errors.cm` – highlights undeclared identifiers and keyword/identifier typos.

Run any diagnostic sample with `./minicompiler negative-tests/<file>.cm` to view the emitted errors.

## GCU AI Policy Disclaimer
- ChatGPT Codex by OpenAI was utilized as an assistant in this project as allowed by the course-specific policy. 
