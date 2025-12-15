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
#define SYMTAB_GROWTH_FACTOR 2
static int scopeCountStack[MAX_SCOPE_DEPTH];
static int scopeOffsetStack[MAX_SCOPE_DEPTH];
static int scopeDepth = 0;

/* Every scope push saves the number of variables declared so far and the stack
 * pointer offset. When we exit a scope we simply roll those counters back and
 * discard the associated symbols. */

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

  memset(sym, 0, sizeof(*sym));
}

static void releaseSymbolStorage(void) {
  if (!symtab.vars)
    return;

  for (int i = 0; i < symtab.count; ++i) {
    freeSymbol(&symtab.vars[i]);
  }

  free(symtab.vars);
  symtab.vars = NULL;
  symtab.capacity = 0;
  symtab.count = 0;
}

/* Table storage grows lazily. We keep old entries intact and zero-initialize
 * the new ones so callers can assume all fields start off cleared. */
static void ensureSymbolCapacity(void) {
  if (symtab.capacity == 0) {
    symtab.capacity = INITIAL_SYMTAB_CAPACITY;
    symtab.vars = calloc(symtab.capacity, sizeof(Symbol));
    if (!symtab.vars) {
      fprintf(stderr, "SYMBOL TABLE: Failed to allocate %d entries\n",
              symtab.capacity);
      exit(1);
    }
    return;
  }

  if (symtab.count < symtab.capacity)
    return;

  int newCapacity = symtab.capacity * SYMTAB_GROWTH_FACTOR;
  Symbol *resized =
      realloc(symtab.vars, (size_t)newCapacity * sizeof(Symbol));
  if (!resized) {
    fprintf(stderr, "SYMBOL TABLE: Failed to grow table to %d entries\n",
            newCapacity);
    exit(1);
  }

  memset(resized + symtab.capacity, 0,
         (size_t)(newCapacity - symtab.capacity) * sizeof(Symbol));
  symtab.vars = resized;
  symtab.capacity = newCapacity;
}

/* MIPS likes 4-byte alignment. Arrays and structs may request larger sizes, so
 * alignUp centralizes the padding computation. */
static int alignUp(int value, int alignment) {
  int remainder = value % alignment;
  return remainder == 0 ? value : value + alignment - remainder;
}

static void updateMaxOffset(void) {
  if (symtab.nextOffset > symtab.maxOffset) {
    symtab.maxOffset = symtab.nextOffset;
  }
}

static const char *dataTypeToString(DataType type) {
  switch (type) {
  case TYPE_CHAR:
    return "char";
  case TYPE_INT:
    return "int";
  case TYPE_FLOAT:
    return "float";
  case TYPE_BOOL:
    return "bool";
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
  releaseSymbolStorage();
  symtab.nextOffset = 0;
  symtab.maxOffset = 0;
  scopeDepth = 0;
  ensureSymbolCapacity();
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
  ensureSymbolCapacity();
  Symbol *sym = &symtab.vars[symtab.count];
  memset(sym, 0, sizeof(*sym));
  sym->name = strdup(name);
  sym->offset = symtab.nextOffset;

  symtab.nextOffset += 4;
  updateMaxOffset();
  symtab.count++;

  printf("SYMBOL TABLE: Added variable '%s' at offset %d\n", name,
         sym->offset);
  printSymTab();

  return sym->offset;
}

int addBoolVar(char *name) {
  if (isVarDeclared(name)) {
    printf("SYMBOL TABLE: Failed to add bool '%s' - already declared\n", name);
    return -1;
  }

  symtab.nextOffset = alignUp(symtab.nextOffset, 4);
  ensureSymbolCapacity();
  Symbol *sym = &symtab.vars[symtab.count];
  memset(sym, 0, sizeof(*sym));
  sym->name = strdup(name);
  sym->offset = symtab.nextOffset;
  sym->isBool = 1;

  symtab.nextOffset += 4;
  updateMaxOffset();
  symtab.count++;

  printf("SYMBOL TABLE: Added bool '%s' at offset %d\n", name, sym->offset);
  printSymTab();

  return sym->offset;
}

int getVarOffset(char *name) {
  if (!symtab.vars) {
    printf("SYMBOL TABLE: Variable '%s' not found\n", name);
    return -1;
  }
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

  ensureSymbolCapacity();
  Symbol *sym = &symtab.vars[symtab.count];
  memset(sym, 0, sizeof(*sym));
  sym->name = strdup(name);
  sym->offset = symtab.nextOffset;
  sym->isChar = 1;

  symtab.nextOffset += 1;
  updateMaxOffset();
  symtab.count++;

  printf("SYMBOL TABLE: Added char '%s' at offset %d\n", name, sym->offset);
  printSymTab();

  return sym->offset;
}

int addCharArrayVar(char *name, int size) {
  if (isVarDeclared(name)) {
    printf("SYMBOL TABLE: Failed to add array '%s' - already declared\n", name);
    return -1;
  }

  ensureSymbolCapacity();
  Symbol *sym = &symtab.vars[symtab.count];
  memset(sym, 0, sizeof(*sym));
  sym->name = strdup(name);
  sym->arraySize = size;
  sym->isArray = 1;
  sym->offset = symtab.nextOffset;
  sym->isChar = 1;

  symtab.nextOffset += size;
  updateMaxOffset();
  symtab.count++;

  printf("SYMBOL TABLE: Added char array '%s[%d]' at offset %d\n", name, size,
         sym->offset);
  printSymTab();

  return sym->offset;
}

int addFloatVar(char *name) {
  if (isVarDeclared(name)) {
    printf("SYMBOL TABLE: Failed to add float '%s' - already declared\n", name);
    return -1;
  }

  symtab.nextOffset = alignUp(symtab.nextOffset, 4);
  ensureSymbolCapacity();
  Symbol *sym = &symtab.vars[symtab.count];
  memset(sym, 0, sizeof(*sym));
  sym->name = strdup(name);
  sym->offset = symtab.nextOffset;
  sym->isFloat = 1;

  symtab.nextOffset += 4;
  updateMaxOffset();
  symtab.count++;

  printf("SYMBOL TABLE: Added float '%s' at offset %d\n", name, sym->offset);
  printSymTab();

  return sym->offset;
}

int addArrayVar(char *name, int size) {
  if (isVarDeclared(name)) {
    printf("SYMBOL TABLE: Failed to add array '%s' - already declared\n", name);
    return -1;
  }

  symtab.nextOffset = alignUp(symtab.nextOffset, 4);
  ensureSymbolCapacity();
  Symbol *sym = &symtab.vars[symtab.count];
  memset(sym, 0, sizeof(*sym));
  sym->name = strdup(name);
  sym->arraySize = size;
  sym->isArray = 1;
  sym->offset = symtab.nextOffset;

  symtab.nextOffset += size * 4;
  updateMaxOffset();
  symtab.count++;

  printf("SYMBOL TABLE: Added array '%s[%d]' at offset %d\n", name, size,
         sym->offset);
  printSymTab();

  return sym->offset;
}

int addBoolArrayVar(char *name, int size) {
  if (isVarDeclared(name)) {
    printf("SYMBOL TABLE: Failed to add bool array '%s' - already declared\n",
           name);
    return -1;
  }

  symtab.nextOffset = alignUp(symtab.nextOffset, 4);
  ensureSymbolCapacity();
  Symbol *sym = &symtab.vars[symtab.count];
  memset(sym, 0, sizeof(*sym));
  sym->name = strdup(name);
  sym->arraySize = size;
  sym->isArray = 1;
  sym->offset = symtab.nextOffset;
  sym->isBool = 1;

  symtab.nextOffset += size * 4;
  updateMaxOffset();
  symtab.count++;

  printf("SYMBOL TABLE: Added bool array '%s[%d]' at offset %d\n", name, size,
         sym->offset);
  printSymTab();

  return sym->offset;
}

int addFloatArrayVar(char *name, int size) {
  if (isVarDeclared(name)) {
    printf("SYMBOL TABLE: Failed to add float array '%s' - already declared\n",
           name);
    return -1;
  }

  symtab.nextOffset = alignUp(symtab.nextOffset, 4);
  ensureSymbolCapacity();
  Symbol *sym = &symtab.vars[symtab.count];
  memset(sym, 0, sizeof(*sym));
  sym->name = strdup(name);
  sym->arraySize = size;
  sym->isArray = 1;
  sym->offset = symtab.nextOffset;
  sym->isFloat = 1;

  symtab.nextOffset += size * 4;
  updateMaxOffset();
  symtab.count++;

  printf("SYMBOL TABLE: Added float array '%s[%d]' at offset %d\n", name, size,
         sym->offset);
  printSymTab();

  return sym->offset;
}

int addArrayParam(char *name, int size, DataType elemType) {
  if (isVarDeclared(name)) {
    printf("SYMBOL TABLE: Failed to add array parameter '%s' - already declared\n",
           name);
    return -1;
  }

  symtab.nextOffset = alignUp(symtab.nextOffset, 4);
  ensureSymbolCapacity();
  Symbol *sym = &symtab.vars[symtab.count];
  memset(sym, 0, sizeof(*sym));
  sym->name = strdup(name);
  sym->offset = symtab.nextOffset;
  sym->isArray = 1;
  sym->arraySize = size;
  sym->isChar = (elemType == TYPE_CHAR);
  sym->isFloat = (elemType == TYPE_FLOAT);
  sym->isBool = (elemType == TYPE_BOOL);
  sym->isPointer = 1;
  sym->isParam = 1;

  symtab.nextOffset += 4;
  updateMaxOffset();
  symtab.count++;

  printf("SYMBOL TABLE: Added array parameter '%s[%d]' (elem %s) at offset %d\n",
         name, size, dataTypeToString(elemType), sym->offset);
  printSymTab();

  return sym->offset;
}

int isArrayVar(char *name) {
  if (!symtab.vars)
    return 0;
  for (int i = 0; i < symtab.count; i++) {
    if (strcmp(symtab.vars[i].name, name) == 0) {
      return symtab.vars[i].isArray;
    }
  }
  return 0; /* Not found or not an array */
}

int isCharVar(char *name) {
  if (!symtab.vars)
    return 0;
  for (int i = 0; i < symtab.count; i++) {
    if (strcmp(symtab.vars[i].name, name) == 0) {
      return symtab.vars[i].isChar;
    }
  }
  return 0; /* Not found or not a char */
}

int isFloatVar(char *name) {
  if (!symtab.vars)
    return 0;
  for (int i = 0; i < symtab.count; i++) {
    if (strcmp(symtab.vars[i].name, name) == 0) {
      return symtab.vars[i].isFloat;
    }
  }
  return 0;
}

DataType getVarType(const char *name) {
  if (!symtab.vars)
    return TYPE_INT;
  for (int i = 0; i < symtab.count; i++) {
    if (strcmp(symtab.vars[i].name, name) == 0) {
      if (symtab.vars[i].isChar)
        return TYPE_CHAR;
      if (symtab.vars[i].isFloat)
        return TYPE_FLOAT;
      if (symtab.vars[i].isBool)
        return TYPE_BOOL;
      if (symtab.vars[i].isStruct)
        return TYPE_VOID;
      return TYPE_INT;
    }
  }
  return TYPE_INT;
}

int getArraySize(char *name) {
  if (!symtab.vars)
    return 0;
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
  ensureSymbolCapacity();
  Symbol *sym = &symtab.vars[symtab.count];
  memset(sym, 0, sizeof(*sym));
  sym->name = strdup(varName);
  sym->offset = symtab.nextOffset;
  sym->isStruct = 1;
  sym->structType = strdup(structName);

  int paddedSize = alignUp(def->size, 4);
  symtab.nextOffset += paddedSize;
  updateMaxOffset();
  symtab.count++;

  printf("SYMBOL TABLE: Added struct var '%s' (type %s) at offset %d\n",
         varName, structName, sym->offset);
  printSymTab();
  return sym->offset;
}

int addStructParam(char *varName, const char *structName) {
  StructDef *def = getStructDef(structName);
  if (!def) {
    printf("SYMBOL TABLE: Failed to add struct parameter '%s' - struct '%s' undefined\n",
           varName, structName);
    return -2;
  }

  if (isVarDeclared(varName)) {
    printf("SYMBOL TABLE: Failed to add '%s' - already declared\n", varName);
    return -1;
  }

  symtab.nextOffset = alignUp(symtab.nextOffset, 4);
  ensureSymbolCapacity();
  Symbol *sym = &symtab.vars[symtab.count];
  memset(sym, 0, sizeof(*sym));
  sym->name = strdup(varName);
  sym->offset = symtab.nextOffset;
  sym->isStruct = 1;
  sym->structType = strdup(structName);
  sym->isPointer = 1;
  sym->isParam = 1;

  symtab.nextOffset += 4;
  updateMaxOffset();
  symtab.count++;

  printf("SYMBOL TABLE: Added struct parameter '%s' (type %s) at offset %d\n",
         varName, structName, sym->offset);
  printSymTab();
  return sym->offset;
}

int isStructVar(const char *varName) {
  if (!symtab.vars)
    return 0;
  for (int i = 0; i < symtab.count; i++) {
    if (strcmp(symtab.vars[i].name, varName) == 0) {
      return symtab.vars[i].isStruct;
    }
  }
  return 0;
}

const char *getStructTypeName(const char *varName) {
  if (!symtab.vars)
    return NULL;
  for (int i = 0; i < symtab.count; i++) {
    if (strcmp(symtab.vars[i].name, varName) == 0) {
      return symtab.vars[i].structType;
    }
  }
  return NULL;
}

int isPointerVar(const char *name) {
  if (!symtab.vars)
    return 0;
  for (int i = 0; i < symtab.count; i++) {
    if (strcmp(symtab.vars[i].name, name) == 0) {
      return symtab.vars[i].isPointer;
    }
  }
  return 0;
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
  if (!name || !symtab.vars)
    return NULL;

  for (int i = symtab.count - 1; i >= 0; --i) {
    Symbol *sym = &symtab.vars[i];
    if (sym->name && strcmp(sym->name, name) == 0) {
      return sym;
    }
  }
  return NULL;
}

void printSymTab() {
  printf("\n=== SYMBOL TABLE STATE ===\n");
  printf("Count: %d, Next Offset: %d\n", symtab.count, symtab.nextOffset);
  if (!symtab.vars) {
    printf("(uninitialized)\n");
    printf("==========================\n\n");
    return;
  }
  if (symtab.count == 0) {
    printf("(empty)\n");
  } else {
    printf("Variables:\n");
    for (int i = 0; i < symtab.count; i++) {
      Symbol *sym = &symtab.vars[i];
      if (sym->isPointer) {
        const char *paramTag = sym->isParam ? ", param" : "";
        if (sym->isStruct) {
          printf(" [%d] %s -> offset %d (struct %s pointer%s)\n", i,
                 sym->name, sym->offset,
                 sym->structType ? sym->structType : "<unnamed>", paramTag);
        } else if (sym->isArray) {
          printf(" [%d] %s -> offset %d (array pointer%s, size %d)\n", i,
                 sym->name, sym->offset, paramTag, sym->arraySize);
        } else {
          printf(" [%d] %s -> offset %d (pointer%s)\n", i, sym->name,
                 sym->offset, paramTag);
        }
      } else if (sym->isArray) {
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
