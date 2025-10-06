# Minimal Compiler Test Guide

## Quick Start
- Ensure `gcc`, `flex`, `bison`, and a MIPS runtime such as `spim` are installed.
- Build once with `make` from the project root; the binary `minicompiler` is produced.

## Run the Tests
- Execute `make test` to compile `source.cm`, print the generated MIPS, and run it in `spim`.
- To target individual samples (e.g., structs, chars, subtraction), run `./minicompiler tests/<file>.cm output.s` then feed `output.s` to your MIPS runtime.
- Expect clear diagnostics when the compiler encounters lexical, syntax, or semantic errors; the `errors.c` subsystem reports location-aware messages.

## Feature Highlights
- `char` literals and assignments are accepted end-to-end through parsing, TAC, and codegen.
- `struct` definitions and member access compile into correct symbol-table entries and field offsets.
- Arithmetic covers subtraction alongside other expressions, both standalone and inside structs.
- Error identification is first-class: malformed tokens, redefinitions, and type mismatches all halt compilation with context.

## Share Your Project
- Demo video: _link coming soon_
- GitHub repository: _link coming soon_
