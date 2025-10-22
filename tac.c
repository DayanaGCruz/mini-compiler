#include "tac.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TACList tacList;
TACList optimizedList;

typedef struct {
  char *name;
  DataType type;
} NameTypeEntry;

typedef struct {
  char *varName;
  char *structType;
} StructVarEntry;

typedef struct {
  char *structName;
  char *fieldName;
  DataType type;
} StructFieldEntry;

typedef struct {
  char *name;
  DataType returnType;
} FunctionReturnEntry;

static NameTypeEntry typeTable[1024];
static int typeTableCount = 0;
static StructVarEntry structVarTable[256];
static int structVarCount = 0;
static StructFieldEntry structFieldTable[512];
static int structFieldCount = 0;
static FunctionReturnEntry functionReturnTable[256];
static int functionReturnCount = 0;

static void resetTypeTables(void) {
  for (int i = 0; i < typeTableCount; ++i) {
    free(typeTable[i].name);
    typeTable[i].name = NULL;
  }
  typeTableCount = 0;

  for (int i = 0; i < structVarCount; ++i) {
    free(structVarTable[i].varName);
    free(structVarTable[i].structType);
    structVarTable[i].varName = NULL;
    structVarTable[i].structType = NULL;
  }
  structVarCount = 0;

  for (int i = 0; i < structFieldCount; ++i) {
    free(structFieldTable[i].structName);
    free(structFieldTable[i].fieldName);
    structFieldTable[i].structName = NULL;
    structFieldTable[i].fieldName = NULL;
  }
  structFieldCount = 0;

  for (int i = 0; i < functionReturnCount; ++i) {
    free(functionReturnTable[i].name);
    functionReturnTable[i].name = NULL;
  }
  functionReturnCount = 0;
}

static int isLiteralName(const char *name) {
  if (!name)
    return 0;
  if (isdigit((unsigned char)name[0]) || name[0] == '-' || name[0] == '.')
    return 1;
  return 0;
}

static void recordNameType(const char *name, DataType type) {
  if (!name || isLiteralName(name))
    return;

  for (int i = 0; i < typeTableCount; ++i) {
    if (strcmp(typeTable[i].name, name) == 0) {
      typeTable[i].type = type;
      return;
    }
  }

  if (typeTableCount < (int)(sizeof(typeTable) / sizeof(typeTable[0]))) {
    typeTable[typeTableCount].name = strdup(name);
    typeTable[typeTableCount].type = type;
    typeTableCount++;
  }
}

static int hasRecordedType(const char *name) {
  if (!name || isLiteralName(name))
    return 0;

  for (int i = 0; i < typeTableCount; ++i) {
    if (strcmp(typeTable[i].name, name) == 0)
      return 1;
  }
  return 0;
}

static void recordStructVar(const char *varName, const char *structType) {
  if (!varName || !structType)
    return;

  for (int i = 0; i < structVarCount; ++i) {
    if (strcmp(structVarTable[i].varName, varName) == 0) {
      free(structVarTable[i].structType);
      structVarTable[i].structType = strdup(structType);
      return;
    }
  }

  if (structVarCount < (int)(sizeof(structVarTable) /
                             sizeof(structVarTable[0]))) {
    structVarTable[structVarCount].varName = strdup(varName);
    structVarTable[structVarCount].structType = strdup(structType);
    structVarCount++;
  }
}

static void recordStructField(const char *structName, const char *fieldName,
                              DataType type) {
  if (!structName || !fieldName)
    return;

  for (int i = 0; i < structFieldCount; ++i) {
    if (strcmp(structFieldTable[i].structName, structName) == 0 &&
        strcmp(structFieldTable[i].fieldName, fieldName) == 0) {
      structFieldTable[i].type = type;
      return;
    }
  }

  if (structFieldCount <
      (int)(sizeof(structFieldTable) / sizeof(structFieldTable[0]))) {
    structFieldTable[structFieldCount].structName = strdup(structName);
    structFieldTable[structFieldCount].fieldName = strdup(fieldName);
    structFieldTable[structFieldCount].type = type;
    structFieldCount++;
  }
}

static DataType lookupNameType(const char *name) {
  if (!name)
    return TYPE_INT;

  if (isLiteralName(name)) {
    for (const char *p = name; *p; ++p) {
      if (*p == '.' || *p == 'e' || *p == 'E')
        return TYPE_FLOAT;
    }
    return TYPE_INT;
  }

  for (int i = 0; i < typeTableCount; ++i) {
    if (strcmp(typeTable[i].name, name) == 0) {
      return typeTable[i].type;
    }
  }
  return TYPE_INT;
}

static const char *lookupStructVarType(const char *varName) {
  if (!varName)
    return NULL;

  for (int i = 0; i < structVarCount; ++i) {
    if (strcmp(structVarTable[i].varName, varName) == 0) {
      return structVarTable[i].structType;
    }
  }
  return NULL;
}

static DataType lookupStructFieldType(const char *structName,
                                      const char *fieldName) {
  if (!structName || !fieldName)
    return TYPE_INT;

  for (int i = 0; i < structFieldCount; ++i) {
    if (strcmp(structFieldTable[i].structName, structName) == 0 &&
        strcmp(structFieldTable[i].fieldName, fieldName) == 0) {
      return structFieldTable[i].type;
    }
  }
  return TYPE_INT;
}

static void recordFunctionReturnType(const char *name, DataType type) {
  if (!name)
    return;

  for (int i = 0; i < functionReturnCount; ++i) {
    if (strcmp(functionReturnTable[i].name, name) == 0) {
      functionReturnTable[i].returnType = type;
      return;
    }
  }

  if (functionReturnCount <
      (int)(sizeof(functionReturnTable) / sizeof(functionReturnTable[0]))) {
    functionReturnTable[functionReturnCount].name = strdup(name);
    functionReturnTable[functionReturnCount].returnType = type;
    functionReturnCount++;
  }
}

static DataType lookupFunctionReturn(const char *name) {
  if (!name)
    return TYPE_INT;

  for (int i = 0; i < functionReturnCount; ++i) {
    if (strcmp(functionReturnTable[i].name, name) == 0) {
      return functionReturnTable[i].returnType;
    }
  }
  return TYPE_INT;
}

static const char *typeToString(DataType type) {
  switch (type) {
  case TYPE_CHAR:
    return "char";
  case TYPE_FLOAT:
    return "float";
  case TYPE_INT:
    return "int";
  case TYPE_VOID:
    return "void";
  default:
    return "int";
  }
}

static void registerParamTypes(ASTNode *params) {
  if (!params)
    return;

  switch (params->type) {
  case NODE_PARAM:
    recordNameType(params->data.param.name, params->data.param.type);
    break;
  case NODE_PARAM_LIST:
  case NODE_ARG_LIST:
    registerParamTypes(params->data.list.item);
    registerParamTypes(params->data.list.next);
    break;
  default:
    break;
  }
}

static inline void copyTypeInfo(TACInstr *dest, const TACInstr *src) {
  if (!dest || !src)
    return;
  dest->resultType = src->resultType;
  dest->arg1Type = src->arg1Type;
  dest->arg2Type = src->arg2Type;
}

static DataType inferNodeType(ASTNode *node);

static DataType mergeTypes(DataType a, DataType b) {
  if (a == TYPE_FLOAT || b == TYPE_FLOAT)
    return TYPE_FLOAT;
  if (a == TYPE_INT || b == TYPE_INT) {
    if (a == TYPE_CHAR)
      return b;
    if (b == TYPE_CHAR)
      return a;
    return TYPE_INT;
  }
  if (a == TYPE_CHAR && b == TYPE_CHAR)
    return TYPE_CHAR;
  return a != TYPE_VOID ? a : b;
}

static DataType inferNodeType(ASTNode *node) {
  if (!node)
    return TYPE_INT;

  switch (node->type) {
  case NODE_FLOAT:
    return TYPE_FLOAT;
  case NODE_NUM:
    return TYPE_INT;
  case NODE_VAR:
  case NODE_DECL:
    return lookupNameType(node->data.name);
  case NODE_FLOAT_DECL:
    return TYPE_FLOAT;
  case NODE_CHAR_DECL:
    return TYPE_CHAR;
  case NODE_ARRAY_DECL:
    return node->data.array_decl.dataType;
  case NODE_BINOP: {
    DataType left = inferNodeType(node->data.binop.left);
    DataType right = inferNodeType(node->data.binop.right);
    return mergeTypes(left, right);
  }
  case NODE_ARRAY_ACCESS: {
    return lookupNameType(node->data.array_access.name);
  }
  case NODE_FUNC_CALL:
    return lookupFunctionReturn(node->data.func_call.name);
  case NODE_STRUCT_ACCESS: {
    const char *structType = lookupStructVarType(node->data.struct_access.varName);
    if (!structType)
      return TYPE_INT;
    return lookupStructFieldType(structType, node->data.struct_access.fieldName);
  }
  case NODE_ASSIGN:
    return inferNodeType(node->data.assign.value);
  case NODE_RETURN:
    if (node->data.return_expr)
      return inferNodeType(node->data.return_expr);
    return TYPE_INT;
  default:
    return TYPE_INT;
  }
}

static int isNumericLiteral(const char *s) {
  if (!s || !*s)
    return 0;
  if (isdigit((unsigned char)s[0]) || s[0] == '.')
    return 1;
  return (s[0] == '-' && (isdigit((unsigned char)s[1]) || s[1] == '.'));
}

void initTAC() {
  tacList.head = NULL;
  tacList.tail = NULL;
  tacList.tempCount = 0;
  optimizedList.head = NULL;
  optimizedList.tail = NULL;
  resetTypeTables();
}

char *newTemp() {
  char *temp = malloc(10);
  sprintf(temp, "t%d", tacList.tempCount++);
  return temp;
}

TACInstr *createTAC(TACOp op, char *arg1, char *arg2, char *result) {
  TACInstr *instr = malloc(sizeof(TACInstr));
  instr->op = op;
  instr->arg1 = arg1 ? strdup(arg1) : NULL;
  instr->arg2 = arg2 ? strdup(arg2) : NULL;
  instr->result = result ? strdup(result) : NULL;
  instr->resultType = TYPE_INT;
  instr->arg1Type = TYPE_INT;
  instr->arg2Type = TYPE_INT;
  instr->paramCount = 0;
  instr->next = NULL;
  return instr;
}

void appendTAC(TACInstr *instr) {
  if (!tacList.head) {
    tacList.head = tacList.tail = instr;
  } else {
    tacList.tail->next = instr;
    tacList.tail = instr;
  }
}

void appendOptimizedTAC(TACInstr *instr) {
  if (!optimizedList.head) {
    optimizedList.head = optimizedList.tail = instr;
  } else {
    optimizedList.tail->next = instr;
    optimizedList.tail = instr;
  }
}

static int emitCallArguments(ASTNode *args) {
  if (!args)
    return 0;

  if (args->type == NODE_ARG_LIST || args->type == NODE_PARAM_LIST) {
    int leftCount = emitCallArguments(args->data.list.item);
    int rightCount = emitCallArguments(args->data.list.next);
    return leftCount + rightCount;
  }

  DataType argType = inferNodeType(args);
  char *argVal = generateTACExpr(args);
  if (argVal) {
    TACInstr *param = createTAC(TAC_PARAM, argVal, NULL, NULL);
    param->arg1Type = argType;
    appendTAC(param);
  }
  return 1;
}

char *generateTACExpr(ASTNode *node) {
  if (!node)
    return NULL;

  DataType exprType = inferNodeType(node);

  switch (node->type) {
  case NODE_NUM: {
    char *temp = malloc(20);
    sprintf(temp, "%d", node->data.num);
    return temp;
  }

  case NODE_FLOAT: {
    char *temp = malloc(32);
    sprintf(temp, "%f", node->data.fnum);
    return temp;
  }

  case NODE_VAR: {
    recordNameType(node->data.name, lookupNameType(node->data.name));
    return strdup(node->data.name);
  }

  case NODE_BINOP: {
    char *left = generateTACExpr(node->data.binop.left);
    char *right = generateTACExpr(node->data.binop.right);
    DataType leftType = inferNodeType(node->data.binop.left);
    DataType rightType = inferNodeType(node->data.binop.right);
    char *temp = newTemp();
    recordNameType(temp, exprType);

    TACOp op = TAC_ADD;
    switch (node->data.binop.op) {
    case '+':
      op = TAC_ADD;
      break;
    case '-':
      op = TAC_SUB;
      break;
    case '*':
      op = TAC_MUL;
      break;
    case '/':
      op = TAC_DIV;
      break;
    default:
      break;
    }

    TACInstr *instr = createTAC(op, left, right, temp);
    instr->arg1Type = leftType;
    instr->arg2Type = rightType;
    instr->resultType = exprType;
    appendTAC(instr);
    return temp;
  }

  case NODE_ARRAY_ACCESS: {
    char *indexExpr = generateTACExpr(node->data.array_access.index);
    char *temp = newTemp();
    recordNameType(temp, exprType);

    TACInstr *instr = createTAC(
        TAC_ARRAY_ACCESS, indexExpr, node->data.array_access.name, temp);
    instr->arg1Type = inferNodeType(node->data.array_access.index);
    instr->arg2Type = lookupNameType(node->data.array_access.name);
    instr->resultType = exprType;
    appendTAC(instr);
    return temp;
  }

  case NODE_STRUCT_ACCESS: {
    char *temp = newTemp();
    recordNameType(temp, exprType);

    TACInstr *instr = createTAC(TAC_STRUCT_ACCESS,
                                node->data.struct_access.varName,
                                node->data.struct_access.fieldName, temp);
    const char *structType =
        lookupStructVarType(node->data.struct_access.varName);
    instr->arg2Type = lookupStructFieldType(structType,
                                            node->data.struct_access.fieldName);
    instr->resultType = exprType;
    appendTAC(instr);
    return temp;
  }

  case NODE_FUNC_CALL: {
    int argCount = emitCallArguments(node->data.func_call.args);
    char *temp = newTemp();
    recordNameType(temp, exprType);
    TACInstr *call = createTAC(TAC_CALL, node->data.func_call.name, NULL, temp);
    call->paramCount = argCount;
    call->resultType = exprType;
    appendTAC(call);
    return temp;
  }

  default:
    return NULL;
  }
}

void generateTAC(ASTNode *node) {
  if (!node)
    return;

  switch (node->type) {
  case NODE_DECL: {
    recordNameType(node->data.name, TYPE_INT);
    TACInstr *instr = createTAC(TAC_DECL, "int", NULL, node->data.name);
    instr->resultType = TYPE_INT;
    appendTAC(instr);
    break;
  }

  case NODE_CHAR_DECL: {
    recordNameType(node->data.name, TYPE_CHAR);
    TACInstr *instr = createTAC(TAC_DECL, "char", NULL, node->data.name);
    instr->resultType = TYPE_CHAR;
    appendTAC(instr);
    break;
  }

  case NODE_FLOAT_DECL: {
    recordNameType(node->data.name, TYPE_FLOAT);
    TACInstr *instr = createTAC(TAC_DECL, "float", NULL, node->data.name);
    instr->resultType = TYPE_FLOAT;
    appendTAC(instr);
    break;
  }

  case NODE_ASSIGN: {
    char *expr = generateTACExpr(node->data.assign.value);
    DataType valueType = inferNodeType(node->data.assign.value);
    DataType targetType = lookupNameType(node->data.assign.var);
    if (!hasRecordedType(node->data.assign.var))
      targetType = valueType;
    recordNameType(node->data.assign.var, targetType);

    TACInstr *instr = createTAC(TAC_ASSIGN, expr, NULL,
                                node->data.assign.var);
    instr->arg1Type = valueType;
    instr->resultType = targetType;
    appendTAC(instr);
    break;
  }

  case NODE_PRINT: {
    char *expr = generateTACExpr(node->data.expr);
    TACInstr *instr = createTAC(TAC_PRINT, expr, NULL, NULL);
    instr->arg1Type = inferNodeType(node->data.expr);
    appendTAC(instr);
    break;
  }

  case NODE_STMT_LIST:
    generateTAC(node->data.stmtlist.stmt);
    generateTAC(node->data.stmtlist.next);
    break;
  case NODE_BLOCK:
    generateTAC(node->data.list.item);
    break;
  case NODE_FUNC_LIST:
    generateTAC(node->data.list.item);
    generateTAC(node->data.list.next);
    break;
  case NODE_ARRAY_DECL: {
    DataType elemType = node->data.array_decl.dataType;
    const char *typeStr = typeToString(elemType);
    char sizeBuf[32];
    sprintf(sizeBuf, "%d", node->data.array_decl.size);
    recordNameType(node->data.array_decl.name, elemType);
    TACInstr *instr =
        createTAC(TAC_ARRAY_DECL, typeStr, sizeBuf, node->data.array_decl.name);
    instr->resultType = elemType;
    appendTAC(instr);
    break;
  }
  case NODE_ARRAY_ASSIGN: {
    char *indexExpr = generateTACExpr(node->data.array_assign.index);
    char *valueExpr = generateTACExpr(node->data.array_assign.value);
    DataType indexType = inferNodeType(node->data.array_assign.index);
    DataType valueType = inferNodeType(node->data.array_assign.value);
    DataType elemType = lookupNameType(node->data.array_assign.name);
    TACInstr *instr = createTAC(TAC_ARRAY_ASSIGN, indexExpr, valueExpr,
                                node->data.array_assign.name);
    instr->arg1Type = indexType;
    instr->arg2Type = valueType;
    instr->resultType = elemType;
    appendTAC(instr);
    break;
  }

  case NODE_STRUCT_DEF: {
    appendTAC(
        createTAC(TAC_STRUCT_DECL, NULL, NULL, node->data.struct_def.name));
    ASTNode *field = node->data.struct_def.fields;
    while (field) {
      const char *typeStr = typeToString(field->data.struct_field.dataType);
      recordStructField(node->data.struct_def.name,
                        field->data.struct_field.fieldName,
                        field->data.struct_field.dataType);
      TACInstr *fieldInstr =
          createTAC(TAC_STRUCT_FIELD, field->data.struct_field.fieldName,
                    (char *)typeStr, node->data.struct_def.name);
      fieldInstr->arg2Type = field->data.struct_field.dataType;
      appendTAC(fieldInstr);
      field = field->data.struct_field.next;
    }
    break;
  }

  case NODE_STRUCT_VAR_DECL: {
    recordStructVar(node->data.struct_var_decl.varName,
                    node->data.struct_var_decl.structName);
    recordNameType(node->data.struct_var_decl.varName, TYPE_VOID);
    TACInstr *instr = createTAC(TAC_STRUCT_VAR_DECL,
                                node->data.struct_var_decl.structName, NULL,
                                node->data.struct_var_decl.varName);
    instr->resultType = TYPE_VOID;
    appendTAC(instr);
    break;
  }

  case NODE_STRUCT_ASSIGN: {
    char *valueExpr = generateTACExpr(node->data.struct_assign.value);
    const char *structType =
        lookupStructVarType(node->data.struct_assign.varName);
    DataType fieldType = lookupStructFieldType(structType,
                                              node->data.struct_assign.fieldName);
    TACInstr *instr = createTAC(TAC_STRUCT_ASSIGN, valueExpr,
                                node->data.struct_assign.fieldName,
                                node->data.struct_assign.varName);
    instr->arg1Type = inferNodeType(node->data.struct_assign.value);
    instr->resultType = fieldType;
    appendTAC(instr);
    break;
  }

  case NODE_FUNC_DECL: {
    const char *name = node->data.func_decl.name;
    if (!name)
      name = "main";
    recordFunctionReturnType(name, node->data.func_decl.returnType);
    registerParamTypes(node->data.func_decl.params);

    TACInstr *begin =
        createTAC(TAC_FUNC_BEGIN, (char *)typeToString(node->data.func_decl.returnType),
                  NULL, name);
    begin->resultType = node->data.func_decl.returnType;
    appendTAC(begin);

    appendTAC(createTAC(TAC_LABEL, NULL, NULL, name));

    generateTAC(node->data.func_decl.body);

    TACInstr *end = createTAC(TAC_FUNC_END, NULL, NULL, name);
    end->resultType = node->data.func_decl.returnType;
    appendTAC(end);
    break;
  }
  case NODE_FUNC_CALL:
    (void)generateTACExpr(node);
    break;

  case NODE_RETURN:
    if (node->data.return_expr) {
      char *retVal = generateTACExpr(node->data.return_expr);
      TACInstr *instr = createTAC(TAC_RETURN, retVal, NULL, NULL);
      instr->arg1Type = inferNodeType(node->data.return_expr);
      appendTAC(instr);
    } else {
      TACInstr *instr = createTAC(TAC_RETURN, NULL, NULL, NULL);
      instr->resultType = TYPE_VOID;
      appendTAC(instr);
    }
    break;
  default:
    break;
  }
}

void printTAC() {
  printf("Unoptimized TAC Instructions:\n");
  printf("─────────────────────────────\n");
  TACInstr *curr = tacList.head;
  int lineNum = 1;
  while (curr) {
    printf("%2d: ", lineNum++);
    switch (curr->op) {
    case TAC_DECL:
      printf("DECL %s", curr->result);
      printf("          // Declare variable '%s'\n", curr->result);
      break;

    case TAC_ADD:
      printf("%s = %s + %s", curr->result, curr->arg1, curr->arg2);
      printf("     // Add: store result in %s\n", curr->result);
      break;
    case TAC_SUB:
      printf("%s = %s - %s", curr->result, curr->arg1, curr->arg2);
      printf("     // Subtract: store result in %s\n", curr->result);
      break;
    case TAC_MUL:
      printf("%s = %s * %s", curr->result, curr->arg1, curr->arg2);
      printf("     // Multiply: store result in %s\n", curr->result);
      break;
    case TAC_DIV:
      printf("%s = %s / %s", curr->result, curr->arg1, curr->arg2);
      printf("     // Divide: store result in %s\n", curr->result);
      break;
    case TAC_ASSIGN:
      printf("%s = %s", curr->result, curr->arg1);
      printf("           // Assign value to %s\n", curr->result);
      break;
    case TAC_PRINT:
      printf("PRINT %s", curr->arg1);
      printf("          // Output value of %s\n", curr->arg1);
      break;
    case TAC_ARRAY_DECL:
      printf("ARRAY DECL %s", curr->result);
      printf("      // Declare array '%s'\n", curr->result);
      break;
    case TAC_ARRAY_ASSIGN:
      printf("%s[%s] = %s", curr->result, curr->arg1, curr->arg2);
      printf("   // Array assignment\n");
      break;
    case TAC_ARRAY_ACCESS:
      printf("%s = %s[%s]", curr->result, curr->arg2, curr->arg1);
      printf("   // Array access\n");
      break;
    case TAC_STRUCT_DECL:
      printf("STRUCT %s", curr->result);
      printf("         // Struct definition begins\n");
      break;
    case TAC_STRUCT_FIELD:
      printf("FIELD %s.%s (%s)", curr->result, curr->arg1, curr->arg2);
      printf(" // Struct field\n");
      break;
    case TAC_STRUCT_VAR_DECL:
      printf("STRUCT VAR %s : %s", curr->result, curr->arg1);
      printf(" // Struct variable declaration\n");
      break;
    case TAC_STRUCT_ASSIGN:
      printf("%s.%s = %s", curr->result, curr->arg2, curr->arg1);
      printf("   // Struct field assignment\n");
      break;
    case TAC_STRUCT_ACCESS:
      printf("%s = %s.%s", curr->result, curr->arg1, curr->arg2);
      printf("   // Struct field access\n");
      break;
    default:
      break;
    }
    curr = curr->next;
  }
}

// Simple optimization: constant folding and copy propagation
void optimizeTAC() {
  TACInstr *curr = tacList.head;

  // Copy propagation table
  typedef struct {
    char *var;
    char *value;
    DataType type;
  } VarValue;

  VarValue values[100];
  int valueCount = 0;

  while (curr) {
    TACInstr *newInstr = NULL;

    switch (curr->op) {
    case TAC_DECL:
      newInstr = createTAC(TAC_DECL, curr->arg1, curr->arg2, curr->result);
      copyTypeInfo(newInstr, curr);
      break;

    case TAC_ADD:
    case TAC_SUB:
    case TAC_MUL:
    case TAC_DIV: {
      // Check if both operands are constants
      char *left = curr->arg1;
      char *right = curr->arg2;
      DataType leftType = curr->arg1Type;
      DataType rightType = curr->arg2Type;

      // Look up values in propagation table (search from most recent)
      for (int i = valueCount - 1; i >= 0; i--) {
        if (strcmp(values[i].var, left) == 0) {
          left = values[i].value;
          leftType = values[i].type;
          break;
        }
      }
      for (int i = valueCount - 1; i >= 0; i--) {
        if (strcmp(values[i].var, right) == 0) {
          right = values[i].value;
          rightType = values[i].type;
          break;
        }
      }

      // Constant folding
      if (isNumericLiteral(left) && isNumericLiteral(right)) {
        double resultVal = 0.0;
        switch (curr->op) {
        case TAC_ADD:
          resultVal = atof(left) + atof(right);
          break;
        case TAC_SUB:
          resultVal = atof(left) - atof(right);
          break;
        case TAC_MUL:
          resultVal = atof(left) * atof(right);
          break;
        case TAC_DIV:
          resultVal = atof(left) / atof(right);
          break;
        default:
          break;
        }
        char *resultStr = malloc(64);
        if (curr->resultType == TYPE_FLOAT) {
          sprintf(resultStr, "%f", resultVal);
        } else {
          sprintf(resultStr, "%d", (int)resultVal);
        }

        // Store for propagation
        values[valueCount].var = strdup(curr->result);
        values[valueCount].value = resultStr;
        values[valueCount].type = curr->resultType;
        valueCount++;

        newInstr = createTAC(TAC_ASSIGN, resultStr, NULL, curr->result);
        newInstr->arg1Type = curr->resultType;
        newInstr->resultType = curr->resultType;
      } else {
        newInstr = createTAC(curr->op, left, right, curr->result);
        newInstr->arg1Type = leftType;
        newInstr->arg2Type = rightType;
        newInstr->resultType = curr->resultType;
      }
      break;
    }

    case TAC_ASSIGN: {
      char *value = curr->arg1;
      DataType valueType = curr->arg1Type;

      // Look up value in propagation table (search from most recent)
      for (int i = valueCount - 1; i >= 0; i--) {
        if (strcmp(values[i].var, value) == 0) {
          value = values[i].value;
          valueType = values[i].type;
          break;
        }
      }

      // Store for propagation
      values[valueCount].var = strdup(curr->result);
      values[valueCount].value = strdup(value);
      values[valueCount].type = curr->resultType;
      valueCount++;

      newInstr = createTAC(TAC_ASSIGN, value, NULL, curr->result);
      newInstr->arg1Type = valueType;
      newInstr->resultType = curr->resultType;
      break;
    }

    case TAC_PRINT: {
      char *value = curr->arg1;
      DataType valueType = curr->arg1Type;

      // Look up value in propagation table
      for (int i = valueCount - 1; i >= 0; i--) { // Search from most recent
        if (strcmp(values[i].var, value) == 0) {
          value = values[i].value;
          valueType = values[i].type;
          break;
        }
      }

      newInstr = createTAC(TAC_PRINT, value, NULL, NULL);
      newInstr->arg1Type = valueType;
      break;
    }

    case TAC_ARRAY_DECL:
      /* TODO: Arrays declarations don't need optimization */
      newInstr = createTAC(TAC_ARRAY_DECL, curr->arg1, curr->arg2, curr->result);
      copyTypeInfo(newInstr, curr);
      break;

    case TAC_ARRAY_ASSIGN: {
      /* TODO: Optimize array assignments */
      char *index = curr->arg1;
      char *value = curr->arg2;
      DataType indexType = curr->arg1Type;
      DataType valueType = curr->arg2Type;

      /* Look up values in propagation table */
      for (int i = valueCount - 1; i >= 0; i--) {
        if (strcmp(values[i].var, index) == 0) {
          index = values[i].value;
          indexType = values[i].type;
          break;
        }
      }
      for (int i = valueCount - 1; i >= 0; i--) {
        if (strcmp(values[i].var, value) == 0) {
          value = values[i].value;
          valueType = values[i].type;
          break;
        }
      }

      newInstr = createTAC(TAC_ARRAY_ASSIGN, index, value, curr->result);
      newInstr->arg1Type = indexType;
      newInstr->arg2Type = valueType;
      newInstr->resultType = curr->resultType;
      break;
    }

    case TAC_ARRAY_ACCESS: {
      /* TODO: Optimize array access */
      char *index = curr->arg1;
      DataType indexType = curr->arg1Type;

      /* Look up index in propagation table */
      for (int i = valueCount - 1; i >= 0; i--) {
        if (strcmp(values[i].var, index) == 0) {
          index = values[i].value;
          indexType = values[i].type;
          break;
        }
      }

      newInstr = createTAC(TAC_ARRAY_ACCESS, index, curr->arg2, curr->result);
      newInstr->arg1Type = indexType;
      newInstr->arg2Type = curr->arg2Type;
      newInstr->resultType = curr->resultType;
      break;
    }

    case TAC_STRUCT_DECL:
      newInstr =
          createTAC(TAC_STRUCT_DECL, curr->arg1, curr->arg2, curr->result);
      copyTypeInfo(newInstr, curr);
      break;

    case TAC_STRUCT_FIELD:
      newInstr =
          createTAC(TAC_STRUCT_FIELD, curr->arg1, curr->arg2, curr->result);
      copyTypeInfo(newInstr, curr);
      break;

    case TAC_STRUCT_VAR_DECL:
      newInstr =
          createTAC(TAC_STRUCT_VAR_DECL, curr->arg1, curr->arg2, curr->result);
      copyTypeInfo(newInstr, curr);
      break;

    case TAC_STRUCT_ASSIGN: {
      char *value = curr->arg1;
      DataType valueType = curr->arg1Type;

      /* Propagate the assigned value if it is a known copy */
      for (int i = valueCount - 1; i >= 0; i--) {
        if (strcmp(values[i].var, value) == 0) {
          value = values[i].value;
          valueType = values[i].type;
          break;
        }
      }

      /* Track struct field value for later accesses */
      size_t keyLen = strlen(curr->result) + 1 + strlen(curr->arg2) + 1;
      char *fieldKey = malloc(keyLen);
      sprintf(fieldKey, "%s.%s", curr->result, curr->arg2);

      values[valueCount].var = fieldKey;
      values[valueCount].value = strdup(value);
      values[valueCount].type = curr->resultType;
      valueCount++;

      newInstr = createTAC(TAC_STRUCT_ASSIGN, value, curr->arg2, curr->result);
      newInstr->arg1Type = valueType;
      newInstr->resultType = curr->resultType;
      break;
    }

    case TAC_STRUCT_ACCESS: {
      size_t keyLen = strlen(curr->arg1) + 1 + strlen(curr->arg2) + 1;
      char *fieldKey = malloc(keyLen);
      sprintf(fieldKey, "%s.%s", curr->arg1, curr->arg2);

      char *fieldValue = NULL;
      DataType fieldValueType = curr->resultType;
      for (int i = valueCount - 1; i >= 0; i--) {
        if (strcmp(values[i].var, fieldKey) == 0) {
          fieldValue = values[i].value;
          fieldValueType = values[i].type;
          break;
        }
      }

      if (fieldValue) {
        /* Replace access with direct assignment and propagate */
        newInstr = createTAC(TAC_ASSIGN, fieldValue, NULL, curr->result);
        values[valueCount].var = strdup(curr->result);
        values[valueCount].value = strdup(fieldValue);
        values[valueCount].type = fieldValueType;
        valueCount++;
        newInstr->arg1Type = fieldValueType;
        newInstr->resultType = fieldValueType;
      } else {
        newInstr =
            createTAC(TAC_STRUCT_ACCESS, curr->arg1, curr->arg2, curr->result);
        copyTypeInfo(newInstr, curr);
      }

      free(fieldKey);
      break;
    }

    case TAC_LABEL:
    case TAC_PARAM:
    case TAC_RETURN:
    case TAC_FUNC_BEGIN:
    case TAC_FUNC_END:
      newInstr = createTAC(curr->op, curr->arg1, curr->arg2, curr->result);
      copyTypeInfo(newInstr, curr);
      break;

    case TAC_CALL: {
      newInstr = createTAC(TAC_CALL, curr->arg1, curr->arg2, curr->result);
      newInstr->paramCount = curr->paramCount;
      copyTypeInfo(newInstr, curr);
      break;
    }
    }

    if (newInstr) {
      appendOptimizedTAC(newInstr);
    }

    curr = curr->next;
  }
}

void printOptimizedTAC() {
  printf("Optimized TAC Instructions:\n");
  printf("─────────────────────────────\n");
  TACInstr *curr = optimizedList.head;
  int lineNum = 1;
  while (curr) {
    printf("%2d: ", lineNum++);
    switch (curr->op) {
    case TAC_DECL:
      printf("DECL %s\n", curr->result);
      break;
    case TAC_ADD:
      printf("%s = %s + %s", curr->result, curr->arg1, curr->arg2);
      printf("     // Runtime addition needed\n");
      break;
    case TAC_SUB:
      printf("%s = %s - %s", curr->result, curr->arg1, curr->arg2);
      printf("     // Runtime subtraction needed\n");
      break;
    case TAC_MUL:
      printf("%s = %s * %s", curr->result, curr->arg1, curr->arg2);
      printf("     // Runtime multiplication needed\n");
      break;
    case TAC_DIV:
      printf("%s = %s / %s", curr->result, curr->arg1, curr->arg2);
      printf("     // Runtime division needed\n");
      break;
    case TAC_ASSIGN:
      printf("%s = %s", curr->result, curr->arg1);
      // Check if it's a constant
      if (isNumericLiteral(curr->arg1)) {
        printf("           // Constant value: %s\n", curr->arg1);
      } else {
        printf("           // Copy value\n");
      }
      break;
    case TAC_PRINT:
      printf("PRINT %s", curr->arg1);
      // Check if it's a constant
      if (isNumericLiteral(curr->arg1)) {
        printf("          // Print constant: %s\n", curr->arg1);
      } else {
        printf("          // Print variable\n");
      }
      break;
    case TAC_ARRAY_DECL:
      printf("ARRAY DECL %s\n", curr->result);
      break;
    case TAC_ARRAY_ASSIGN:
      printf("%s[%s] = %s   // Array assignment\n", curr->result, curr->arg1,
             curr->arg2);
      break;
    case TAC_ARRAY_ACCESS:
      printf("%s = %s[%s]   // Array access\n", curr->result, curr->arg2,
             curr->arg1);
      break;
    case TAC_STRUCT_DECL:
      printf("STRUCT %s   // Struct definition\n", curr->result);
      break;
    case TAC_STRUCT_FIELD:
      printf("FIELD %s.%s (%s)\n", curr->result, curr->arg1, curr->arg2);
      break;
    case TAC_STRUCT_VAR_DECL:
      printf("STRUCT VAR %s : %s\n", curr->result, curr->arg1);
      break;
    case TAC_STRUCT_ASSIGN:
      printf("%s.%s = %s   // Struct assignment\n", curr->result, curr->arg2,
             curr->arg1);
      break;
    case TAC_STRUCT_ACCESS:
      printf("%s = %s.%s   // Struct field access\n", curr->result, curr->arg1,
             curr->arg2);
      break;
    default:
      break;
    }
    curr = curr->next;
  }
}

TACList *getTACList(void) { return &tacList; }

TACList *getOptimizedTACList(void) { return &optimizedList; }
