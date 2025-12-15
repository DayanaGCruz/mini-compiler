#ifndef SYMTAB_H
#define SYMTAB_H

/* SYMBOL TABLE
 * Tracks all declared variables during compilation
 * Maps variable names to their memory locations (stack offsets)
 * Used for semantic checking and code generation
 */

#include "ast.h"

#define INITIAL_SYMTAB_CAPACITY 128 /* Starting size for dynamic table */
#define SCOPE_MAX_VARS 100          /* Per-scope identifier snapshot */
#define MAX_STRUCTS 50
#define MAX_STRUCT_FIELDS 32

/* SYMBOL ENTRY - Information about each variable */
typedef struct {
  char *name; /* Variable identifier */
  int offset; /* Stack offset in bytes (for MIPS stack frame) */
  int isArray;
  int arraySize;
  int isChar;        /* 1 if char, else 0 (int)*/
  int isFloat;       /* 1 if float */
  int isBool;        /* 1 if bool */
  int isStruct;      /* 1 if struct variable */
  char *structType;  /* Struct type name if applicable */
  int isPointer;     /* 1 if symbol stores an address */
  int isParam;       /* 1 if symbol declared as function parameter */
  int isFunction;    /* 1 if function, 0 if variable */
  int paramCount;    /* Number of parameters (if function) */
  char **paramTypes; /* Array of parameter types */
} Symbol;

typedef struct {
  char *name;
  DataType type;
  int offset;
} StructField;

typedef struct {
  char *name;
  StructField fields[MAX_STRUCT_FIELDS];
  int fieldCount;
  int size;
} StructDef;

typedef struct {
  StructDef defs[MAX_STRUCTS];
  int count;
} StructTable;

/* Struct metadata mirrors the runtime layout (field order and offsets). The
 * code generator queries these helpers to compute addresses without needing to
 * know how the parser declared each type. */

/* SYMBOL TABLE STRUCTURE */
typedef struct {
  Symbol *vars;   /* Dynamic array of all symbols */
  int count;      /* Number of variables declared */
  int capacity;   /* Current allocation size */
  int nextOffset; /* Next available stack offset */
  int maxOffset;  /* Peak stack usage within current function */
} SymbolTable;

/* SYMBOL TABLE OPERATIONS */
void initSymTab(); /* Initialize empty symbol table */
void initStructTable();
int addVar(
    char *name); /* Add new variable, returns offset or -1 if duplicate */
int addBoolVar(char *name);
int addCharVar(char *name);
int addFloatVar(char *name);
int getVarOffset(
    char *name); /* Get stack offset for variable, -1 if not found */
int isCharVar(char *name);
int isFloatVar(char *name);
DataType getVarType(const char *name);
int isVarDeclared(char *name); /* Check if variable exists (1=yes, 0=no) */
int addCharArrayVar(char *name, int size);
int addArrayVar(char *name, int size); /*Add array to symbol table*/
int addFloatArrayVar(char *name, int size);
int addBoolArrayVar(char *name, int size);
int addArrayParam(char *name, int size, DataType elemType);
int isArrayVar(char *name);            /* Check if variable is an array*/
int getArraySize(char *name);
int addStructType(char *name);
int addStructField(char *structName, char *fieldName, DataType type);
StructDef *getStructDef(const char *name);
int isStructTypeDefined(const char *name);
int addStructVar(char *varName, const char *structName);
int addStructParam(char *varName, const char *structName);
int isStructVar(const char *varName);
const char *getStructTypeName(const char *varName);
int getStructFieldOffset(const char *structName, const char *fieldName);
DataType getStructFieldType(const char *structName, const char *fieldName);
void printSymTab(); /* Print current symbol table contents for tracing */

void enterScope();
void exitScope();
Symbol *lookupSymbol(char *name); /*Check current & global scope */
int isPointerVar(const char *name);

extern SymbolTable symtab;
extern StructTable structTable;

void printStructTable();

#endif
