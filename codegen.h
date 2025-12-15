#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast.h"

/* High-level entry point that walks the optimized TAC stream generated from the
 * AST and emits MIPS assembly. The implementation is intentionally stateful so
 * it can buffer function bodies, manage global data segments, and stitch in
 * helper stubs only when the user program references them. */
void generateMIPS(ASTNode *root, const char *filename);

#endif
