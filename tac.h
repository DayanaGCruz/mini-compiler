#ifndef TAC_H
#define TAC_H

#include "ast.h"
#include <stddef.h>

/* THREE-ADDRESS CODE (TAC)
 * Intermediate representation between AST and machine code
 * Each instruction has at most 3 operands (result = arg1 op arg2)
 * Makes optimization and code generation easier
 */

/* TAC INSTRUCTION TYPES */
typedef enum {
  TAC_ADD,    /* Addition: result = arg1 + arg2 */
  TAC_SUB,    /* Subtraction: result = arg1 - arg2 */
  TAC_MUL,    /* Multiplication: result = arg1 * arg2 */
  TAC_DIV,    /* Division: result = arg1 / arg2 */
  TAC_LT,
  TAC_LE,
  TAC_GT,
  TAC_GE,
  TAC_EQ,
  TAC_NE,
  TAC_AND,
  TAC_OR,
  TAC_NOT,
  TAC_ASSIGN, /* Assignment: result = arg1 */
  TAC_PRINT,  /* Print: print(arg1) */
  TAC_DECL,   /* Declaration: declare result */
  TAC_GLOBAL_DECL,       /* Global scalar declaration */
  TAC_GLOBAL_ARRAY_DECL, /* Global array declaration */
  TAC_GLOBAL_STRUCT_VAR_DECL, /* Global struct variable */
  TAC_GOTO,
  TAC_IFZ,
  TAC_IFNZ,

  TAC_ARRAY_DECL,
  TAC_ARRAY_ASSIGN,
  TAC_ARRAY_ACCESS,
  TAC_STRUCT_DECL,
  TAC_STRUCT_FIELD,
  TAC_STRUCT_VAR_DECL,
  TAC_STRUCT_ASSIGN,
  TAC_STRUCT_ACCESS,

  TAC_LABEL, /* Function entry pointL LABEL func_name */
  TAC_PARAM, 
  TAC_CALL, 
  TAC_RETURN, 
  TAC_FUNC_BEGIN,
  TAC_FUNC_END
} TACOp;

/* TAC INSTRUCTION STRUCTURE */
typedef struct TACInstr {
  TACOp op;              /* Operation type */
  char *arg1;            /* First operand (if needed) */
  char *arg2;            /* Second operand (for binary ops) */
  char *result;          /* Result/destination */
  DataType resultType;   /* Type of the result operand */
  DataType arg1Type;     /* Type info for arg1 */
  DataType arg2Type;     /* Type info for arg2 */
  int line;              /* Source line for diagnostics */
  int paramCount; /* For CALL Instr */
  struct TACInstr *next; /* Linked list pointer */
} TACInstr;

/* TAC LIST MANAGEMENT */
typedef struct {
  TACInstr *head; /* First instruction */
  TACInstr *tail; /* Last instruction (for efficient append) */
  int tempCount;  /* Counter for temporary variables (t0, t1, ...) */
} TACList;

typedef struct {
  size_t tacInstructions;
  size_t optimizedTACInstructions;
  size_t tempCount;
} TACMetrics;

/* TACMetrics is surfaced to the CLI benchmarking summary so the user can see
 * how aggressive the optimizer was (instruction count before vs. after) and
 * how many temporaries were allocated while lowering expressions. */

/* TAC GENERATION FUNCTIONS */
void initTAC();  /* Initialize TAC lists */
char *newTemp(); /* Generate new temp variable */
TACInstr *createTAC(TACOp op, char *arg1, char *arg2,
                    char *result);    /* Create TAC instruction */
void appendTAC(TACInstr *instr);      /* Add instruction to list */
void generateTAC(ASTNode *node);      /* Convert AST to TAC */
char *generateTACExpr(ASTNode *node); /* Generate TAC for expression */

/* TAC OPTIMIZATION AND OUTPUT */
void printTAC();          /* Display unoptimized TAC */
void optimizeTAC();       /* Apply optimizations */
void printOptimizedTAC(); /* Display optimized TAC */
void printFunctionReturnTable();
void getTACMetrics(TACMetrics *metrics);

TACList *getTACList();
TACList *getOptimizedTACList();

#endif
