# Minimal Compiler Test Guide

## About
 - Minimal C-Minus compiler for the C-Minus language specification in CST-405. Four new features have been added: support for char literals, structs, subtraction operations, and improved lexical and syntax error reporting. Adapted from course materials given at:
 https://github.com/isac-artzi/CST-405

## Quick Start
- Ensure `gcc`, `flex`, `bison`, and a MIPS runtime such as `spim` are installed.
- Spim is the command-line client for QtSpim from James Larus. Alternatively, run produced `output.s` MIPS file in QtSpim. 
- Build once with `make` from the project root; the binary `minicompiler` is produced.

## Run the Tests
- Execute `make test` to compile `source.cm`, print the generated MIPS, and run it in `spim`.
- To target individual samples (e.g., structs, chars, subtraction), run `./minicompiler tests/<file>.cm output.s` then feed `output.s` to your MIPS runtime. The available tests are arithemtic.cm, structs.cm, array.cm, arithmetic.cm.
- Alter the tests to produce lexical error like typos in keywords, declared identifiers, illegal identifiers, and more to see detailed error messages with line number and suggestions. 

## Feature Highlights
- `char` literals and assignments are accepted end-to-end through parsing, TAC, and codegen.
- `struct` definitions and member access compile into correct symbol-table entries and field offsets which are assignable and accessible.

## Demonstration Link
- Demo video: https://drive.google.com/file/d/1hbsZdQrqea_QTi1SuDYx91Z5wz8J-Mia/view?usp=sharing
- GitHub repository: https://github.com/DayanaGCruz/mini-compiler
