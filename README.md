# Minimal Compiler for C-Minus

## Demonstration Link
- Demo video: https://drive.google.com/file/d/14jTo_8ed8iSOY1qkCV36vFBtIe04ao1F/view?usp=sharing 
- GitHub repository: https://github.com/DayanaGCruz/mini-compiler

## About
- Minimal C-Minus compiler for the C-Minus language specification in CST-405.
- Extended language coverage beyond the starter code: booleans, chars with escape sequences, arrays, structs, typed functions/recursion, `switch`/`while`, ternary/logical operators, and field or array access on simple identifiers.
- Compiler pipeline extras: AST/TAC visualisation, semantic tables, runtime array-bounds checks, built-in `input()`/`output()` helpers, a TAC optimizer (constant folding, copy propagation, loop unrolling, dead-code elimination), and benchmark-ready diagnostics.
- Adapted from course materials given at https://github.com/isac-artzi/CST-405.

## Quick Start
- Ensure `gcc`, `flex`, `bison`, and a MIPS runtime such as `spim` are installed.
- Spim is the command-line client for QtSpim from James Larus. Alternatively, run produced `output.s` MIPS file in QtSpim. 
- Build once with `make` from the project root; the binary `minicompiler` is produced.
- Benchmark the compiler and generated program with `./minicompiler --benchmark tests/array.cm output.s`. Use `--runtime /path/to/spim` (alias `--spim`) to point to a custom SPIM binary when it is not on your `PATH`.

## Benchmarking
The compiler now reports its own performance characteristics and can optionally run the generated assembly to capture runtime metrics.

- **Compilation metrics** – wall clock time, CPU time (user/sys), and peak resident set size are printed after every successful compile.
- **Intermediate metrics** – the summary lists TAC instruction counts before/after optimization, the number of temporaries allocated, and the size (bytes) of the emitted assembly for quick comparisons between runs.
- **Execution metrics** – pass `--benchmark` (or `-b`) to execute the emitted `.s` file with `spim -file <output>` and record wall/CPU time plus peak RSS for the child process. Combine with `--runtime /path/to/spim` (or `--spim`) if `spim` is not on your `PATH`.
- The SPIM/stdout output of the compiled program still streams directly to your terminal while benchmarks are collected. If SPIM fails to launch, the summary indicates the error code so you can fix your environment and rerun the benchmark.

## Language Features
- **Literals & tokens**: integer, floating-point (decimal & scientific), character literals (with escape sequences), `true`/`false` booleans, `void`, and both line/block comments. Tokens preserve line/column metadata so diagnostics can underline precise locations.
- **Types & declarations**: `int`, `float`, `char`, `bool`, and `void` types for globals or locals, compile-time-sized arrays, struct type definitions, and scalar/array declarations anywhere statements are allowed.
- **Composite data**: one-dimensional arrays for every scalar type (sized locally, optional `[]` form for parameters), `struct` definitions with typed fields, struct variables, struct assignment, and nested field or array-dereference chains.
- **Expressions**: arithmetic `+ - * /`, relational `< > <= >=`, equality `== !=`, logical `&& || !`, unary minus, ternary `?:`, parentheses, implicit int→float promotion, struct/array access, and function calls (including `input()`/`output()` built-ins).
- **Statements & control flow**: declarations, assignments, expression statements, `print(expr);`, `return` with or without values, nested blocks, `if`/`else`, `switch` with `case`/`default`/`break`, and `while` loops (with `break` support inside both `switch` and `while`).
- **Functions, scope & built-ins**: top-level functions with typed returns, up to four positional parameters (scalar, sized array, unsized array, or struct-by-value), `void` parameter lists for procedures, per-function identifier scopes, globals, and automatic linkage of `input()`/`output()` runtime helpers.
- **Diagnostics & semantic analysis**: lexer rejects malformed identifiers/characters, parser issues keyword suggestions, redeclarations or undefined identifiers/structs are flagged with source lines, semantic tables display identifier scopes and struct definitions, and TAC tracks inferred return types to validate function calls (includes arity checks during codegen).
- **Optimization, runtime & benchmarking**: AST → TAC lowering followed by constant folding, copy propagation, bounded loop unrolling, and dead-code elimination; generated MIPS uses stack-based allocation, enforces array bounds at runtime, and emits optional benchmarking summaries for compile/run phases.

## Tests
- Build once with `make` to produce `./minicompiler`, place `spim` on your `PATH`, then run `tests/run_tests.sh` to compile every sample, execute it in SPIM, and diff the output against each `.expected` file.
- `make test` is a convenience loop that emits the generated `.s` files and SPIM output for each sample; it does **not** compare against the baselines.
- Run a single program manually with `./minicompiler tests/<file>.cm out.s && spim out.s`.

### Positive samples with `.expected` baselines (`tests/`)
- `arithmetic.cm` – integer math pipeline sanity check.
- `array.cm` – scalar arrays, indexed writes/reads, and bounds tracking.
- `comprehensive_test.cm` – end-to-end coverage of globals, loops, arrays, recursion, builtin I/O, and precedence rules.
- `conditionals.cm` – nested `if`/`else` chains, boolean expressions, and ternary operators.
- `float.cm` / `float_array.cm` – floating-point locals plus aggregated storage.
- `functions.cm` – mutually recursive functions, argument passing, and typed returns.
- `function_scope.cm` / `scope.cm` – scope tracking and shadowing rules for locals vs. globals.
- `global_vars.cm` – global scalar/array lifetime across helper functions.
- `mixed.cm` – structs, chars, arrays, and function calls in one program.
- `order_of_ops.cm` – precedence/associativity plus parentheses regression.
- `struct.cm` – struct definitions, field assignments, and nested access.
- `swap_loop.cm` – array mutation within helper functions and `while` loops.
- `switch.cm` – multi-`case` switches, fall-through prevention, and `default` coverage.
- `test_functions_only.cm` – function-heavy workload with recursion, array parameters, and builtin `input`/`output` calls.
- `test_with_if_statements.cm` – stress test for conditional helpers and guard functions.
- `while-loop.cm` – relational expressions controlling loops with character output.
- `unroll_simple.cm` – tiny counted loop that fully exercises the loop-unrolling pass.
- `LQ16.cm` / `LQ27.cm` – reference implementations from the course exercises.

### Additional positive inputs (manual inspection)
- `function_loop_if.cm` – alternate formatting of the `LQ27` sample for quick manual runs (no `.expected`).

### Diagnostics & optimizer samples (`negative-tests/`)
- `array_and_struct_errors.cm` – reports array bound violations and struct field mismatches.
- `dead_code_elimination.cm` – compiles, but captures redundant assignments so you can inspect TAC/optimizer output.
- `function_argument_errors.cm` – mismatched call-site arity exercises the semantic checker and codegen arity validation.
- `identifier_errors.cm` – highlights undeclared identifiers and keyword/identifier typos.

Run any diagnostic sample with `./minicompiler negative-tests/<file>.cm` to view the emitted errors.

## GCU AI Policy Disclaimer
- ChatGPT Codex by OpenAI was utilized as an assistant in this project as allowed by the course-specific policy. 
