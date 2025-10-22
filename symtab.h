#ifndef SYMTAB_H
#define SYMTAB_H

/* SYMBOL TABLE
 * Tracks all declared variables during compilation
 * Maps variable names to their memory locations (stack offsets)
 * Used for semantic checking and code generation
 */

#include "ast.h"

#define MAX_VARS 100 /* Maximum number of variables supported */
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
  int isStruct;      /* 1 if struct variable */
  char *structType;  /* Struct type name if applicable */
  int isFunction;    /* 1 if function, 0 if variable */
  int paramCount;    /* Number of parameters (if function) */
  char **paramTypes; /* Array of parameter types */
} Symbol;

typedef struct Scope {
  Symbol vars[MAX_VARS];
  int count;
  int nextOffset;
  struct Scope *parent;
} Scope;

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

/* SYMBOL TABLE STRUCTURE */
typedef struct {
  Symbol vars[MAX_VARS]; /* Array of all variables */
  int count;             /* Number of variables declared */
  int nextOffset;        /* Next available stack offset */
  Scope *currentScope;
  Scope *globalScope;
} SymbolTable;

/* SYMBOL TABLE OPERATIONS */
void initSymTab(); /* Initialize empty symbol table */
void initStructTable();
int addVar(
    char *name); /* Add new variable, returns offset or -1 if duplicate */
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
int isArrayVar(char *name);            /* Check if variable is an array*/
int getArraySize(char *name);
int addStructType(char *name);
int addStructField(char *structName, char *fieldName, DataType type);
StructDef *getStructDef(const char *name);
int isStructTypeDefined(const char *name);
int addStructVar(char *varName, const char *structName);
int isStructVar(const char *varName);
const char *getStructTypeName(const char *varName);
int getStructFieldOffset(const char *structName, const char *fieldName);
DataType getStructFieldType(const char *structName, const char *fieldName);
void printSymTab(); /* Print current symbol table contents for tracing */

void enterScope();
void exitScope();
int addFunction(char *name, char *returnType, char **paramTypes,
                int paramCount);
int addParameter(char *name, char *type);
Symbol *lookupSymbol(char *name); /*Check current & global scope */
int isInCurrentScope(char *name); /* Check current scope */

extern SymbolTable symtab;
extern StructTable structTable;

void printStructTable();

#endif
