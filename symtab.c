/* SYMBOL TABLE IMPLEMENTATION
 * Manages variable declarations and lookups
 * Essential for semantic analysis (checking if variables are declared)
 * Provides memory layout information for code generation
 */
#include "symtab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SymbolTable symtab;
StructTable structTable;

#define MAX_SCOPE_DEPTH 128
static int scopeCountStack[MAX_SCOPE_DEPTH];
static int scopeOffsetStack[MAX_SCOPE_DEPTH];
static int scopeDepth = 0;

static void freeSymbol(Symbol *sym) {
  if (!sym)
    return;

  if (sym->name) {
    free(sym->name);
    sym->name = NULL;
  }

  if (sym->structType) {
    free(sym->structType);
    sym->structType = NULL;
  }

  if (sym->paramTypes) {
    for (int i = 0; i < sym->paramCount; i++) {
      free(sym->paramTypes[i]);
    }
    free(sym->paramTypes);
    sym->paramTypes = NULL;
  }

  sym->paramCount = 0;
  sym->isArray = 0;
  sym->arraySize = 0;
  sym->isChar = 0;
  sym->isFloat = 0;
  sym->isStruct = 0;
}

static int alignUp(int value, int alignment) {
  int remainder = value % alignment;
  return remainder == 0 ? value : value + alignment - remainder;
}

static const char *dataTypeToString(DataType type) {
  switch (type) {
  case TYPE_CHAR:
    return "char";
  case TYPE_INT:
    return "int";
  case TYPE_FLOAT:
    return "float";
  default:
    return "unknown";
  }
}

void initStructTable() {
  structTable.count = 0;
  printf("STRUCT TABLE: Initialized\n");
  printStructTable();
}

void initSymTab() {
  symtab.count = 0;
  symtab.nextOffset = 0;
  scopeDepth = 0;
  initStructTable();
  printf("SYMBOL TABLE: Initialized\n");
  printSymTab();
}

int addVar(char *name) {
  if (isVarDeclared(name)) {
    printf("SYMBOL TABLE: Failed to add '%s' - already declared\n", name);
    return -1;
  }

  symtab.nextOffset = alignUp(symtab.nextOffset, 4);

  symtab.vars[symtab.count].name = strdup(name);
  symtab.vars[symtab.count].offset = symtab.nextOffset;
  symtab.vars[symtab.count].isArray = 0;
  symtab.vars[symtab.count].arraySize = 0;
  symtab.vars[symtab.count].isChar = 0;
  symtab.vars[symtab.count].isFloat = 0;
  symtab.vars[symtab.count].isStruct = 0;
  symtab.vars[symtab.count].structType = NULL;

  symtab.nextOffset += 4;
  symtab.count++;

  printf("SYMBOL TABLE: Added variable '%s' at offset %d\n", name,
         symtab.vars[symtab.count - 1].offset);
  printSymTab();

  return symtab.vars[symtab.count - 1].offset;
}

int getVarOffset(char *name) {
  for (int i = 0; i < symtab.count; i++) {
    if (strcmp(symtab.vars[i].name, name) == 0) {
      printf("SYMBOL TABLE: Found variable '%s' at offset %d\n", name,
             symtab.vars[i].offset);
      return symtab.vars[i].offset;
    }
  }
  printf("SYMBOL TABLE: Variable '%s' not found\n", name);
  return -1;
}

int isVarDeclared(char *name) { return getVarOffset(name) != -1; }

int addCharVar(char *name) {
  if (isVarDeclared(name)) {
    printf("SYMBOL TABLE: Failed to add char '%s' - already declared\n", name);
    return -1;
  }

  symtab.vars[symtab.count].name = strdup(name);
  symtab.vars[symtab.count].offset = symtab.nextOffset;
  symtab.vars[symtab.count].isArray = 0;
  symtab.vars[symtab.count].arraySize = 0;
  symtab.vars[symtab.count].isChar = 1;
  symtab.vars[symtab.count].isFloat = 0;
  symtab.vars[symtab.count].isStruct = 0;
  symtab.vars[symtab.count].structType = NULL;

  symtab.nextOffset += 1;
  symtab.count++;

  printf("SYMBOL TABLE: Added char '%s' at offset %d\n", name,
         symtab.vars[symtab.count - 1].offset);
  printSymTab();

  return symtab.vars[symtab.count - 1].offset;
}

int addCharArrayVar(char *name, int size) {
  if (isVarDeclared(name)) {
    printf("SYMBOL TABLE: Failed to add array '%s' - already declared\n", name);
    return -1;
  }

  symtab.vars[symtab.count].name = strdup(name);
  symtab.vars[symtab.count].arraySize = size;
  symtab.vars[symtab.count].isArray = 1;
  symtab.vars[symtab.count].offset = symtab.nextOffset;
  symtab.vars[symtab.count].isChar = 1;
  symtab.vars[symtab.count].isFloat = 0;
  symtab.vars[symtab.count].isStruct = 0;
  symtab.vars[symtab.count].structType = NULL;

  symtab.nextOffset += size;
  symtab.count++;

  printf("SYMBOL TABLE: Added char array '%s[%d]' at offset %d\n", name, size,
         symtab.vars[symtab.count - 1].offset);
  printSymTab();

  return symtab.vars[symtab.count - 1].offset;
}

int addFloatVar(char *name) {
  if (isVarDeclared(name)) {
    printf("SYMBOL TABLE: Failed to add float '%s' - already declared\n", name);
    return -1;
  }

  symtab.nextOffset = alignUp(symtab.nextOffset, 4);

  symtab.vars[symtab.count].name = strdup(name);
  symtab.vars[symtab.count].offset = symtab.nextOffset;
  symtab.vars[symtab.count].isArray = 0;
  symtab.vars[symtab.count].arraySize = 0;
  symtab.vars[symtab.count].isChar = 0;
  symtab.vars[symtab.count].isFloat = 1;
  symtab.vars[symtab.count].isStruct = 0;
  symtab.vars[symtab.count].structType = NULL;

  symtab.nextOffset += 4;
  symtab.count++;

  printf("SYMBOL TABLE: Added float '%s' at offset %d\n", name,
         symtab.vars[symtab.count - 1].offset);
  printSymTab();

  return symtab.vars[symtab.count - 1].offset;
}

int addArrayVar(char *name, int size) {
  if (isVarDeclared(name)) {
    printf("SYMBOL TABLE: Failed to add array '%s' - already declared\n", name);
    return -1;
  }

  symtab.nextOffset = alignUp(symtab.nextOffset, 4);

  symtab.vars[symtab.count].name = strdup(name);
  symtab.vars[symtab.count].arraySize = size;
  symtab.vars[symtab.count].isArray = 1;
  symtab.vars[symtab.count].offset = symtab.nextOffset;
  symtab.vars[symtab.count].isChar = 0;
  symtab.vars[symtab.count].isFloat = 0;
  symtab.vars[symtab.count].isStruct = 0;
  symtab.vars[symtab.count].structType = NULL;

  symtab.nextOffset += size * 4;
  symtab.count++;

  printf("SYMBOL TABLE: Added array '%s[%d]' at offset %d\n", name, size,
         symtab.vars[symtab.count - 1].offset);
  printSymTab();

  return symtab.vars[symtab.count - 1].offset;
}

int addFloatArrayVar(char *name, int size) {
  if (isVarDeclared(name)) {
    printf("SYMBOL TABLE: Failed to add float array '%s' - already declared\n",
           name);
    return -1;
  }

  symtab.nextOffset = alignUp(symtab.nextOffset, 4);

  symtab.vars[symtab.count].name = strdup(name);
  symtab.vars[symtab.count].arraySize = size;
  symtab.vars[symtab.count].isArray = 1;
  symtab.vars[symtab.count].offset = symtab.nextOffset;
  symtab.vars[symtab.count].isChar = 0;
  symtab.vars[symtab.count].isFloat = 1;
  symtab.vars[symtab.count].isStruct = 0;
  symtab.vars[symtab.count].structType = NULL;

  symtab.nextOffset += size * 4;
  symtab.count++;

  printf("SYMBOL TABLE: Added float array '%s[%d]' at offset %d\n", name, size,
         symtab.vars[symtab.count - 1].offset);
  printSymTab();

  return symtab.vars[symtab.count - 1].offset;
}

int isArrayVar(char *name) {
  for (int i = 0; i < symtab.count; i++) {
    if (strcmp(symtab.vars[i].name, name) == 0) {
      return symtab.vars[i].isArray;
    }
  }
  return 0; /* Not found or not an array */
}

int isCharVar(char *name) {
  for (int i = 0; i < symtab.count; i++) {
    if (strcmp(symtab.vars[i].name, name) == 0) {
      return symtab.vars[i].isChar;
    }
  }
  return 0; /* Not found or not a char */
}

int isFloatVar(char *name) {
  for (int i = 0; i < symtab.count; i++) {
    if (strcmp(symtab.vars[i].name, name) == 0) {
      return symtab.vars[i].isFloat;
    }
  }
  return 0;
}

DataType getVarType(const char *name) {
  for (int i = 0; i < symtab.count; i++) {
    if (strcmp(symtab.vars[i].name, name) == 0) {
      if (symtab.vars[i].isChar)
        return TYPE_CHAR;
      if (symtab.vars[i].isFloat)
        return TYPE_FLOAT;
      if (symtab.vars[i].isStruct)
        return TYPE_VOID;
      return TYPE_INT;
    }
  }
  return TYPE_INT;
}

int getArraySize(char *name) {
  for (int i = 0; i < symtab.count; i++) {
    if (strcmp(symtab.vars[i].name, name) == 0) {
      return symtab.vars[i].arraySize;
    }
  }
  return 0; /* Not found */
}

StructDef *getStructDef(const char *name) {
  for (int i = 0; i < structTable.count; i++) {
    if (strcmp(structTable.defs[i].name, name) == 0) {
      return &structTable.defs[i];
    }
  }
  return NULL;
}

int isStructTypeDefined(const char *name) { return getStructDef(name) != NULL; }

int addStructType(char *name) {
  if (isStructTypeDefined(name)) {
    printf("STRUCT TABLE: Failed to add struct '%s' - already defined\n", name);
    return -1;
  }

  if (structTable.count >= MAX_STRUCTS) {
    printf("STRUCT TABLE: Cannot add struct '%s' - table full\n", name);
    return -1;
  }

  StructDef *def = &structTable.defs[structTable.count];
  def->name = strdup(name);
  def->fieldCount = 0;
  def->size = 0;
  structTable.count++;

  printf("STRUCT TABLE: Added struct '%s'\n", name);
  printStructTable();
  return 0;
}

int addStructField(char *structName, char *fieldName, DataType type) {
  StructDef *def = getStructDef(structName);
  if (!def) {
    printf("STRUCT TABLE: Struct '%s' not defined\n", structName);
    return -1;
  }

  for (int i = 0; i < def->fieldCount; i++) {
    if (strcmp(def->fields[i].name, fieldName) == 0) {
      printf("STRUCT TABLE: Field '%s' already exists on struct '%s'\n",
             fieldName, structName);
      return -1;
    }
  }

  if (def->fieldCount >= MAX_STRUCT_FIELDS) {
    printf("STRUCT TABLE: Struct '%s' has too many fields\n", structName);
    return -1;
  }

  StructField *field = &def->fields[def->fieldCount];
  field->name = strdup(fieldName);
  field->type = type;
  if (type == TYPE_INT || type == TYPE_FLOAT) {
    def->size = alignUp(def->size, 4);
  }
  field->offset = def->size;
  def->fieldCount++;
  def->size += (type == TYPE_CHAR) ? 1 : 4;

  printf("STRUCT TABLE: Added field '%s' (%s) to struct '%s' at offset %d\n",
         fieldName, dataTypeToString(type), structName, field->offset);
  printStructTable();
  return field->offset;
}

int addStructVar(char *varName, const char *structName) {
  StructDef *def = getStructDef(structName);
  if (!def) {
    printf(
        "SYMBOL TABLE: Failed to add struct var '%s' - struct '%s' undefined\n",
        varName, structName);
    return -2;
  }

  if (isVarDeclared(varName)) {
    printf("SYMBOL TABLE: Failed to add '%s' - already declared\n", varName);
    return -1;
  }

  symtab.nextOffset = alignUp(symtab.nextOffset, 4);

  symtab.vars[symtab.count].name = strdup(varName);
  symtab.vars[symtab.count].offset = symtab.nextOffset;
  symtab.vars[symtab.count].isArray = 0;
  symtab.vars[symtab.count].arraySize = 0;
  symtab.vars[symtab.count].isChar = 0;
  symtab.vars[symtab.count].isFloat = 0;
  symtab.vars[symtab.count].isStruct = 1;
  symtab.vars[symtab.count].structType = strdup(structName);

  int paddedSize = alignUp(def->size, 4);
  symtab.nextOffset += paddedSize;
  symtab.count++;

  printf("SYMBOL TABLE: Added struct var '%s' (type %s) at offset %d\n",
         varName, structName, symtab.vars[symtab.count - 1].offset);
  printSymTab();
  return symtab.vars[symtab.count - 1].offset;
}

int isStructVar(const char *varName) {
  for (int i = 0; i < symtab.count; i++) {
    if (strcmp(symtab.vars[i].name, varName) == 0) {
      return symtab.vars[i].isStruct;
    }
  }
  return 0;
}

const char *getStructTypeName(const char *varName) {
  for (int i = 0; i < symtab.count; i++) {
    if (strcmp(symtab.vars[i].name, varName) == 0) {
      return symtab.vars[i].structType;
    }
  }
  return NULL;
}

int getStructFieldOffset(const char *structName, const char *fieldName) {
  StructDef *def = getStructDef(structName);
  if (!def) {
    printf("STRUCT TABLE: Struct '%s' not defined\n", structName);
    return -1;
  }

  for (int i = 0; i < def->fieldCount; i++) {
    if (strcmp(def->fields[i].name, fieldName) == 0) {
      return def->fields[i].offset;
    }
  }

  printf("STRUCT TABLE: Field '%s' not found in struct '%s'\n", fieldName,
         structName);
  return -1;
}

DataType getStructFieldType(const char *structName, const char *fieldName) {
  StructDef *def = getStructDef(structName);
  if (!def) {
    printf("STRUCT TABLE: Struct '%s' not defined\n", structName);
    return TYPE_INT;
  }

  for (int i = 0; i < def->fieldCount; i++) {
    if (strcmp(def->fields[i].name, fieldName) == 0) {
      return def->fields[i].type;
    }
  }

  printf("STRUCT TABLE: Field '%s' not found in struct '%s'\n", fieldName,
         structName);
  return TYPE_INT;
}

Symbol *lookupSymbol(char *name) {
  Scope *scope = symtab.currentScope;

  while (scope != NULL) {
    for (int i = 0; i < scope->count; i++) {
      if (strcmp(scope->vars[i].name, name) == 0) {
        return &scope->vars[i]; // Found it
      }
    }
    scope = scope->parent; // Try parent scope
  }
  return NULL; // Not found in any scope
}

void printSymTab() {
  printf("\n=== SYMBOL TABLE STATE ===\n");
  printf("Count: %d, Next Offset: %d\n", symtab.count, symtab.nextOffset);
  if (symtab.count == 0) {
    printf("(empty)\n");
  } else {
    printf("Variables:\n");
    for (int i = 0; i < symtab.count; i++) {
      Symbol *sym = &symtab.vars[i];
      if (sym->isArray) {
        const char *label = "int";
        if (sym->isChar)
          label = "char";
        else if (sym->isFloat)
          label = "float";
        printf(" [%d] %s[%d] -> offset %d (%s array)\n", i, sym->name,
               sym->arraySize, sym->offset, label);
      } else if (sym->isStruct) {
        printf(" [%d] %s -> offset %d (struct %s)\n", i, sym->name, sym->offset,
               sym->structType);
      } else {
        const char *label = "int";
        if (sym->isChar)
          label = "char";
        else if (sym->isFloat)
          label = "float";
        printf(" [%d] %s -> offset %d (%s)\n", i, sym->name, sym->offset,
               label);
      }
    }
  }
  printf("==========================\n\n");
}

void printStructTable() {
  printf("\n=== STRUCT TABLE STATE ===\n");
  printf("Count: %d\n", structTable.count);
  if (structTable.count == 0) {
    printf("(empty)\n");
  } else {
    for (int i = 0; i < structTable.count; i++) {
      StructDef *def = &structTable.defs[i];
      printf(" [%d] struct %s (size %d)\n", i, def->name, def->size);
      for (int j = 0; j < def->fieldCount; j++) {
        StructField *field = &def->fields[j];
        printf("      .%s @ %d (%s)\n", field->name, field->offset,
               dataTypeToString(field->type));
      }
    }
  }
  printf("==========================\n\n");
}

void enterScope() {
  if (scopeDepth >= MAX_SCOPE_DEPTH) {
    fprintf(stderr, "SYMBOL TABLE: Scope depth limit reached\n");
    exit(1);
  }

  scopeCountStack[scopeDepth] = symtab.count;
  scopeOffsetStack[scopeDepth] = symtab.nextOffset;
  scopeDepth++;
}

void exitScope() {
  if (scopeDepth == 0)
    return;

  scopeDepth--;
  int targetCount = scopeCountStack[scopeDepth];
  int targetOffset = scopeOffsetStack[scopeDepth];

  while (symtab.count > targetCount) {
    symtab.count--;
    freeSymbol(&symtab.vars[symtab.count]);
  }

  symtab.nextOffset = targetOffset;
}
