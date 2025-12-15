#include "tac.h"
#include "errors.h"
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* TAC GENERATION & OPTIMIZATION
 * The parser produces an AST, but later compilation phases want a flat list of
 * instructions. This file manages the translation into TAC, tracks enough type
 * metadata to catch misuse, and applies lightweight optimizations (folding,
 * propagation, loop unrolling, etc.). */

TACList tacList;
TACList optimizedList;
static int labelCounter = 0;
static int inGlobalContext = 1;

#define LOOP_UNROLL_LIMIT 8 /* Maximum fully-unrolled iterations */

#define MAX_BREAK_DEPTH 128
static const char *breakLabelStack[MAX_BREAK_DEPTH];
static int breakDepth = 0;

/* The following lookup tables keep track of inferred type information while we
 * build TAC. They allow us to validate struct/array usage and emit better
 * instructions without constantly consulting the symbol table. */
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
  int size;
} ArrayInfoEntry;

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
static ArrayInfoEntry arrayInfoTable[512];
static int arrayInfoCount = 0;
static FunctionReturnEntry functionReturnTable[256];
static int functionReturnCount = 0;

typedef struct {
  char *funcName;
  char **paramNames;
  int paramCount;
  char **constValues;
  signed char *constStatus; /* -1: not constant, 0: unknown, 1: literal */
} FunctionParamInfo;

static FunctionParamInfo functionParamTable[256];
static int functionParamCount = 0;

static const char *currentFunctionContext = NULL;

static int isLiteralName(const char *name);

typedef enum {
  LOOP_COND_LT,
  LOOP_COND_LE,
  LOOP_COND_GT,
  LOOP_COND_GE
} LoopCondType;

typedef struct {
  const char *varName;
  int initValue;
  int boundValue;
  int stepValue;
  int tripCount;
  LoopCondType condType;
} LoopAnalysis;

/* These reset helpers are called before each compilation to avoid leaking
 * per-run state when the CLI rebuilds multiple programs. */
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

  for (int i = 0; i < arrayInfoCount; ++i) {
    free(arrayInfoTable[i].name);
    arrayInfoTable[i].name = NULL;
    arrayInfoTable[i].size = 0;
  }
  arrayInfoCount = 0;

  for (int i = 0; i < functionReturnCount; ++i) {
    free(functionReturnTable[i].name);
    functionReturnTable[i].name = NULL;
  }
  functionReturnCount = 0;
}

static void freeFunctionParamInfo(FunctionParamInfo *info) {
  if (!info)
    return;
  free(info->funcName);
  info->funcName = NULL;
  if (info->paramNames) {
    for (int i = 0; i < info->paramCount; ++i) {
      free(info->paramNames[i]);
    }
    free(info->paramNames);
    info->paramNames = NULL;
  }
  if (info->constValues) {
    for (int i = 0; i < info->paramCount; ++i) {
      free(info->constValues[i]);
    }
    free(info->constValues);
    info->constValues = NULL;
  }
  free(info->constStatus);
  info->constStatus = NULL;
  info->paramCount = 0;
}

static void resetFunctionParamTable(void) {
  for (int i = 0; i < functionParamCount; ++i) {
    freeFunctionParamInfo(&functionParamTable[i]);
  }
  functionParamCount = 0;
}

static FunctionParamInfo *findFunctionParamInfo(const char *name) {
  if (!name)
    return NULL;
  for (int i = 0; i < functionParamCount; ++i) {
    if (functionParamTable[i].funcName &&
        strcmp(functionParamTable[i].funcName, name) == 0) {
      return &functionParamTable[i];
    }
  }
  return NULL;
}

static int countFunctionParams(ASTNode *params) {
  if (!params)
    return 0;
  switch (params->type) {
  case NODE_PARAM:
    return 1;
  case NODE_PARAM_LIST:
  case NODE_ARG_LIST:
    return countFunctionParams(params->data.list.item) +
           countFunctionParams(params->data.list.next);
  default:
    return 0;
  }
}

static void fillParamNames(FunctionParamInfo *info, ASTNode *params,
                           int *index) {
  if (!info || !params || !index)
    return;
  switch (params->type) {
  case NODE_PARAM:
    if (*index < info->paramCount) {
      const char *name = params->data.param.name;
      info->paramNames[*index] = name ? strdup(name) : NULL;
      info->constValues[*index] = NULL;
      info->constStatus[*index] = 0;
      (*index)++;
    }
    break;
  case NODE_PARAM_LIST:
  case NODE_ARG_LIST:
    fillParamNames(info, params->data.list.item, index);
    fillParamNames(info, params->data.list.next, index);
    break;
  default:
    break;
  }
}

static void recordFunctionParams(const char *funcName, ASTNode *params) {
  const char *name = funcName ? funcName : "main";
  FunctionParamInfo *info = findFunctionParamInfo(name);
  if (!info) {
    if (functionParamCount >= (int)(sizeof(functionParamTable) /
                                    sizeof(functionParamTable[0]))) {
      return;
    }
    info = &functionParamTable[functionParamCount++];
    memset(info, 0, sizeof(*info));
    info->funcName = strdup(name);
  } else {
    freeFunctionParamInfo(info);
    info->funcName = strdup(name);
  }

  int paramCount = countFunctionParams(params);
  info->paramCount = paramCount;
  if (paramCount > 0) {
    info->paramNames = calloc(paramCount, sizeof(char *));
    info->constValues = calloc(paramCount, sizeof(char *));
    info->constStatus = calloc(paramCount, sizeof(signed char));
    int index = 0;
    fillParamNames(info, params, &index);
  }
}

static void resetParamConstantStates(void) {
  for (int i = 0; i < functionParamCount; ++i) {
    FunctionParamInfo *info = &functionParamTable[i];
    if (!info->constValues || !info->constStatus)
      continue;
    for (int j = 0; j < info->paramCount; ++j) {
      free(info->constValues[j]);
      info->constValues[j] = NULL;
      info->constStatus[j] = 0;
    }
  }
}

static void markParamNonConstant(FunctionParamInfo *info, int index) {
  if (!info || index < 0 || index >= info->paramCount)
    return;
  if (info->constStatus && info->constStatus[index] != -1) {
    free(info->constValues[index]);
    info->constValues[index] = NULL;
    info->constStatus[index] = -1;
  }
}

static void considerParamLiteral(FunctionParamInfo *info, int index,
                                 const char *value) {
  if (!info || index < 0 || index >= info->paramCount)
    return;
  if (!value || !isLiteralName(value)) {
    markParamNonConstant(info, index);
    return;
  }
  if (!info->constStatus)
    return;
  if (info->constStatus[index] == -1)
    return;
  if (info->constStatus[index] == 0) {
    info->constValues[index] = strdup(value);
    info->constStatus[index] = 1;
  } else if (info->constStatus[index] == 1 &&
             strcmp(info->constValues[index], value) != 0) {
    markParamNonConstant(info, index);
  }
}

static void analyzeParamConstants(void) {
  resetParamConstantStates();

  TACInstr **paramStack = NULL;
  int stackSize = 0;
  int stackCapacity = 0;

  for (TACInstr *curr = tacList.head; curr; curr = curr->next) {
    if (curr->op == TAC_PARAM) {
      if (stackSize >= stackCapacity) {
        int newCap = stackCapacity == 0 ? 8 : stackCapacity * 2;
        TACInstr **newStack = realloc(paramStack, newCap * sizeof(*newStack));
        if (!newStack)
          break;
        paramStack = newStack;
        stackCapacity = newCap;
      }
      paramStack[stackSize++] = curr;
    } else if (curr->op == TAC_CALL) {
      int needed = curr->paramCount;
      if (needed > stackSize)
        needed = stackSize;
      FunctionParamInfo *info = findFunctionParamInfo(curr->arg1);
      if (info && needed > 0 && info->paramNames && info->constStatus) {
        int usable = info->paramCount < needed ? info->paramCount : needed;
        int start = stackSize - needed;
        for (int i = 0; i < usable; ++i) {
          TACInstr *paramInstr = paramStack[start + i];
          considerParamLiteral(info, i, paramInstr ? paramInstr->arg1 : NULL);
        }
        if (info->paramCount > usable) {
          for (int i = usable; i < info->paramCount; ++i) {
            markParamNonConstant(info, i);
          }
        }
      }
      stackSize -= curr->paramCount;
      if (stackSize < 0)
        stackSize = 0;
    }
  }

  free(paramStack);
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

  if (structVarCount <
      (int)(sizeof(structVarTable) / sizeof(structVarTable[0]))) {
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

static void recordArrayInfo(const char *name, int size) {
  if (!name)
    return;

  for (int i = 0; i < arrayInfoCount; ++i) {
    if (strcmp(arrayInfoTable[i].name, name) == 0) {
      arrayInfoTable[i].size = size;
      return;
    }
  }

  if (arrayInfoCount <
      (int)(sizeof(arrayInfoTable) / sizeof(arrayInfoTable[0]))) {
    arrayInfoTable[arrayInfoCount].name = strdup(name);
    arrayInfoTable[arrayInfoCount].size = size;
    arrayInfoCount++;
  }
}

static int lookupArraySize(const char *name) {
  if (!name)
    return -1;

  for (int i = 0; i < arrayInfoCount; ++i) {
    if (strcmp(arrayInfoTable[i].name, name) == 0) {
      return arrayInfoTable[i].size;
    }
  }
  return -1;
}

static int evalConstInt(ASTNode *node, int *value) {
  if (!node)
    return 0;

  switch (node->type) {
  case NODE_NUM:
    if (value)
      *value = node->data.num;
    return 1;
  case NODE_BOOL:
    if (value)
      *value = node->data.boolValue;
    return 1;
  case NODE_UNARY_OP: {
    int inner = 0;
    if (!evalConstInt(node->data.unary.expr, &inner))
      return 0;
    if (node->data.unary.op == UNOP_NOT) {
      if (value)
        *value = !inner;
      return 1;
    }
    return 0;
  }
  case NODE_BINOP: {
    int leftVal = 0;
    int rightVal = 0;
    if (!evalConstInt(node->data.binop.left, &leftVal) ||
        !evalConstInt(node->data.binop.right, &rightVal))
      return 0;
    int result = 0;
    switch (node->data.binop.op) {
    case OP_ADD:
      result = leftVal + rightVal;
      break;
    case OP_SUB:
      result = leftVal - rightVal;
      break;
    case OP_MUL:
      result = leftVal * rightVal;
      break;
    case OP_DIV:
      if (rightVal == 0)
        return 0;
      result = leftVal / rightVal;
      break;
    case OP_LT:
      result = leftVal < rightVal;
      break;
    case OP_LE:
      result = leftVal <= rightVal;
      break;
    case OP_GT:
      result = leftVal > rightVal;
      break;
    case OP_GE:
      result = leftVal >= rightVal;
      break;
    case OP_EQ:
      result = leftVal == rightVal;
      break;
    case OP_NEQ:
      result = leftVal != rightVal;
      break;
    case OP_AND:
      result = (leftVal != 0) && (rightVal != 0);
      break;
    case OP_OR:
      result = (leftVal != 0) || (rightVal != 0);
      break;
    default:
      return 0;
    }
    if (value)
      *value = result;
    return 1;
  }
  default:
    return 0;
  }
}

static void validateArrayIndex(const char *arrayName, ASTNode *indexNode,
                               int line) {
  if (!arrayName || !indexNode)
    return;

  int size = lookupArraySize(arrayName);
  if (size <= 0)
    return;

  int indexValue = 0;
  if (evalConstInt(indexNode, &indexValue)) {
    if (indexValue < 0 || indexValue >= size) {
      reportSemanticError(line,
                          "array index %d out of bounds for '%s' (size %d)",
                          indexValue, arrayName, size);
    }
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

static int structFieldExists(const char *structName, const char *fieldName,
                             DataType *typeOut) {
  if (!structName || !fieldName)
    return 0;

  for (int i = 0; i < structFieldCount; ++i) {
    if (strcmp(structFieldTable[i].structName, structName) == 0 &&
        strcmp(structFieldTable[i].fieldName, fieldName) == 0) {
      if (typeOut)
        *typeOut = structFieldTable[i].type;
      return 1;
    }
  }
  return 0;
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
  case TYPE_BOOL:
    return "bool";
  case TYPE_INT:
    return "int";
  case TYPE_VOID:
    return "void";
  default:
    return "int";
  }
}

static const char *binaryOpToString(BinaryOp op) {
  switch (op) {
  case OP_ADD:
    return "+";
  case OP_SUB:
    return "-";
  case OP_MUL:
    return "*";
  case OP_DIV:
    return "/";
  case OP_LT:
    return "<";
  case OP_LE:
    return "<=";
  case OP_GT:
    return ">";
  case OP_GE:
    return ">=";
  case OP_EQ:
    return "==";
  case OP_NEQ:
    return "!=";
  case OP_AND:
    return "&&";
  case OP_OR:
    return "||";
  default:
    return "?";
  }
}

static void warnTypeCoercion(DataType fromType, DataType toType,
                             const char *context) {
  if (fromType == toType)
    return;

  reportTypeMismatchWarning(0, typeToString(fromType), typeToString(toType),
                            context);
}

static void registerParamTypes(ASTNode *params) {
  if (!params)
    return;

  switch (params->type) {
  case NODE_PARAM:
    if (params->data.param.isStruct) {
      if (params->data.param.structType) {
        recordStructVar(params->data.param.name, params->data.param.structType);
      }
      recordNameType(params->data.param.name, TYPE_VOID);
    } else {
      recordNameType(params->data.param.name, params->data.param.type);
      if (params->data.param.isArray) {
        recordArrayInfo(params->data.param.name, params->data.param.arraySize);
      }
    }
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

static char *newLabel(const char *prefix) {
  char buffer[64];
  snprintf(buffer, sizeof(buffer), "__%s_%d", prefix ? prefix : "label",
           labelCounter++);
  return strdup(buffer);
}

static void pushBreakLabel(const char *label) {
  if (breakDepth >= MAX_BREAK_DEPTH)
    return;
  breakLabelStack[breakDepth++] = label;
}

static void popBreakLabel(void) {
  if (breakDepth <= 0)
    return;
  breakDepth--;
}

static const char *currentBreakLabel(void) {
  if (breakDepth <= 0)
    return NULL;
  return breakLabelStack[breakDepth - 1];
}

static inline void copyTypeInfo(TACInstr *dest, const TACInstr *src) {
  if (!dest || !src)
    return;
  dest->resultType = src->resultType;
  dest->arg1Type = src->arg1Type;
  dest->arg2Type = src->arg2Type;
  dest->line = src->line;
}

static TACInstr *cloneInstruction(const TACInstr *instr) {
  if (!instr)
    return NULL;
  TACInstr *copy = createTAC(instr->op, instr->arg1, instr->arg2, instr->result);
  copyTypeInfo(copy, instr);
  copy->paramCount = instr->paramCount;
  return copy;
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

static int isComparisonOp(BinaryOp op) {
  switch (op) {
  case OP_LT:
  case OP_LE:
  case OP_GT:
  case OP_GE:
  case OP_EQ:
  case OP_NEQ:
    return 1;
  default:
    return 0;
  }
}

static int isLogicalOp(BinaryOp op) { return op == OP_AND || op == OP_OR; }

static DataType inferNodeType(ASTNode *node) {
  if (!node)
    return TYPE_INT;

  switch (node->type) {
  case NODE_FLOAT:
    return TYPE_FLOAT;
  case NODE_NUM:
    return TYPE_INT;
  case NODE_BOOL:
    return TYPE_BOOL;
  case NODE_VAR:
  case NODE_DECL:
    return lookupNameType(node->data.name);
  case NODE_FLOAT_DECL:
    return TYPE_FLOAT;
  case NODE_CHAR_DECL:
    return TYPE_CHAR;
  case NODE_BOOL_DECL:
    return TYPE_BOOL;
  case NODE_ARRAY_DECL:
    return node->data.array_decl.dataType;
  case NODE_BINOP: {
    DataType left = inferNodeType(node->data.binop.left);
    DataType right = inferNodeType(node->data.binop.right);
    if (isComparisonOp(node->data.binop.op) ||
        isLogicalOp(node->data.binop.op)) {
      return TYPE_BOOL;
    }
    DataType result = mergeTypes(left, right);
    return result == TYPE_BOOL ? TYPE_INT : result;
  }
  case NODE_UNARY_OP:
    if (node->data.unary.op == UNOP_NOT)
      return TYPE_BOOL;
    return TYPE_INT;
  case NODE_ARRAY_ACCESS: {
    return lookupNameType(node->data.array_access.name);
  }
  case NODE_FUNC_CALL:
    return lookupFunctionReturn(node->data.func_call.name);
  case NODE_STRUCT_ACCESS: {
    const char *structType =
        lookupStructVarType(node->data.struct_access.varName);
    if (!structType)
      return TYPE_INT;
    return lookupStructFieldType(structType,
                                 node->data.struct_access.fieldName);
  }
  case NODE_EXPR_STMT:
    return inferNodeType(node->data.expr);
  case NODE_ASSIGN:
    return inferNodeType(node->data.assign.value);
  case NODE_RETURN:
    if (node->data.return_expr)
      return inferNodeType(node->data.return_expr);
    return TYPE_INT;
  case NODE_CONDITIONAL: {
    DataType trueType = inferNodeType(node->data.conditional.trueExpr);
    DataType falseType = inferNodeType(node->data.conditional.falseExpr);
    return mergeTypes(trueType, falseType);
  }
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

static int parseIntLiteral(const char *literal, int *out) {
  if (!literal || !out)
    return 0;
  char *end = NULL;
  long value = strtol(literal, &end, 10);
  if (!end || *end != '\0')
    return 0;
  if (value > INT_MAX || value < INT_MIN)
    return 0;
  *out = (int)value;
  return 1;
}

static int resolveOperandIntValue(const char *operand, int *out) {
  if (!operand || !out)
    return 0;
  if (parseIntLiteral(operand, out))
    return 1;
  if (!currentFunctionContext)
    return 0;
  FunctionParamInfo *info = findFunctionParamInfo(currentFunctionContext);
  if (!info || !info->paramNames || !info->constStatus)
    return 0;
  for (int i = 0; i < info->paramCount; ++i) {
    if (info->paramNames[i] && strcmp(info->paramNames[i], operand) == 0) {
      if (info->constStatus[i] == 1 && info->constValues[i]) {
        return parseIntLiteral(info->constValues[i], out);
      }
      return 0;
    }
  }
  return 0;
}

static int mapTACOpToLoopCond(TACOp op, LoopCondType *type) {
  if (!type)
    return 0;
  switch (op) {
  case TAC_LT:
    *type = LOOP_COND_LT;
    return 1;
  case TAC_LE:
    *type = LOOP_COND_LE;
    return 1;
  case TAC_GT:
    *type = LOOP_COND_GT;
    return 1;
  case TAC_GE:
    *type = LOOP_COND_GE;
    return 1;
  default:
    return 0;
  }
}

static int invertLoopCondType(LoopCondType input, LoopCondType *out) {
  if (!out)
    return 0;
  switch (input) {
  case LOOP_COND_LT:
    *out = LOOP_COND_GT;
    return 1;
  case LOOP_COND_LE:
    *out = LOOP_COND_GE;
    return 1;
  case LOOP_COND_GT:
    *out = LOOP_COND_LT;
    return 1;
  case LOOP_COND_GE:
    *out = LOOP_COND_LE;
    return 1;
  default:
    return 0;
  }
}

static int deriveLoopCondition(TACInstr *condInstr, TACInstr *ifzInstr,
                               LoopAnalysis *analysis) {
  if (!condInstr || !ifzInstr || !analysis)
    return 0;
  if (!condInstr->result || !ifzInstr->arg1 ||
      strcmp(condInstr->result, ifzInstr->arg1) != 0)
    return 0;

  LoopCondType baseType;
  if (!mapTACOpToLoopCond(condInstr->op, &baseType))
    return 0;

  int value1 = 0;
  int value2 = 0;
  int arg1Literal = resolveOperandIntValue(condInstr->arg1, &value1);
  int arg2Literal = resolveOperandIntValue(condInstr->arg2, &value2);
  if (arg1Literal == arg2Literal)
    return 0;

  const char *varName = NULL;
  LoopCondType normalized = baseType;
  int boundValue = 0;

  if (!arg1Literal && arg2Literal) {
    boundValue = value2;
    varName = condInstr->arg1;
  } else if (arg1Literal && !arg2Literal) {
    boundValue = value1;
    if (!invertLoopCondType(baseType, &normalized))
      return 0;
    varName = condInstr->arg2;
  } else {
    return 0;
  }

  if (!varName)
    return 0;

  analysis->varName = varName;
  analysis->boundValue = boundValue;
  analysis->condType = normalized;
  return 1;
}

static int findLiteralInitBefore(const TACInstr *boundary, const char *varName,
                                 int *value) {
  if (!boundary || !varName || !value)
    return 0;
  TACInstr *curr = tacList.head;
  int found = 0;
  while (curr && curr != boundary) {
    if (curr->op == TAC_ASSIGN && curr->result &&
        strcmp(curr->result, varName) == 0 && curr->arg1 &&
        isLiteralName(curr->arg1)) {
      int parsed = 0;
      if (parseIntLiteral(curr->arg1, &parsed)) {
        *value = parsed;
        found = 1;
      }
    }
    curr = curr->next;
  }
  return found;
}

static int detectLoopIncrement(TACInstr *bodyStart, TACInstr *bodyEnd,
                               const char *varName, int *stepValue) {
  if (!bodyStart || !varName || !stepValue)
    return 0;

  TACInstr *curr = bodyStart;
  TACInstr *prev = NULL;
  int found = 0;

  while (curr && curr != bodyEnd) {
    if (curr->op == TAC_ASSIGN && curr->result &&
        strcmp(curr->result, varName) == 0 && curr->arg1 && prev &&
        prev->result && strcmp(prev->result, curr->arg1) == 0 &&
        (prev->op == TAC_ADD || prev->op == TAC_SUB)) {

      int literal = 0;
      int delta = 0;
      if (prev->arg1 && strcmp(prev->arg1, varName) == 0 && prev->arg2 &&
          parseIntLiteral(prev->arg2, &literal)) {
        delta = (prev->op == TAC_ADD) ? literal : -literal;
      } else if (prev->arg2 && strcmp(prev->arg2, varName) == 0 &&
                 prev->arg1 && parseIntLiteral(prev->arg1, &literal)) {
        if (prev->op == TAC_ADD) {
          delta = literal;
        } else {
          delta = 0;
        }
      }

      if (delta != 0) {
        *stepValue = delta;
        found = 1;
      }
    }
    prev = curr;
    curr = curr->next;
  }

  return found;
}

static int computeTripCount(LoopAnalysis *analysis) {
  if (!analysis)
    return 0;
  int step = analysis->stepValue;
  int init = analysis->initValue;
  int bound = analysis->boundValue;
  if (step == 0)
    return 0;

  long diff = 0;
  long absStep = step > 0 ? (long)step : -(long)step;
  int trips = 0;

  switch (analysis->condType) {
  case LOOP_COND_LT:
    if (step <= 0)
      return 0;
    diff = (long)bound - (long)init;
    if (diff <= 0) {
      trips = 0;
      break;
    }
    trips = (int)((diff + (long)step - 1) / (long)step);
    break;
  case LOOP_COND_LE:
    if (step <= 0)
      return 0;
    diff = (long)bound - (long)init;
    if (diff < 0) {
      trips = 0;
      break;
    }
    trips = (int)(diff / (long)step + 1);
    break;
  case LOOP_COND_GT:
    if (step >= 0)
      return 0;
    diff = (long)init - (long)bound;
    if (diff <= 0) {
      trips = 0;
      break;
    }
    trips = (int)((diff + absStep - 1) / absStep);
    break;
  case LOOP_COND_GE:
    if (step >= 0)
      return 0;
    diff = (long)init - (long)bound;
    if (diff < 0) {
      trips = 0;
      break;
    }
    trips = (int)(diff / absStep + 1);
    break;
  default:
    return 0;
  }

  analysis->tripCount = trips;
  return 1;
}

void initTAC() {
  tacList.head = NULL;
  tacList.tail = NULL;
  tacList.tempCount = 0;
  optimizedList.head = NULL;
  optimizedList.tail = NULL;
  labelCounter = 0;
  breakDepth = 0;
  inGlobalContext = 1;
  resetTypeTables();
  resetFunctionParamTable();
  currentFunctionContext = NULL;
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
  instr->line = 0;
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

typedef struct {
  char **items;
  int count;
  int capacity;
} LiveSet;

static void liveSetInit(LiveSet *set) {
  set->items = NULL;
  set->count = 0;
  set->capacity = 0;
}

static void liveSetFree(LiveSet *set) {
  if (!set)
    return;
  for (int i = 0; i < set->count; ++i) {
    free(set->items[i]);
  }
  free(set->items);
  set->items = NULL;
  set->count = 0;
  set->capacity = 0;
}

static void liveSetEnsureCapacity(LiveSet *set) {
  if (set->count < set->capacity)
    return;
  int newCapacity = set->capacity ? set->capacity * 2 : 16;
  char **newItems = realloc(set->items, sizeof(char *) * newCapacity);
  if (!newItems) {
    fprintf(stderr, "Error: Out of memory in liveSetEnsureCapacity\n");
    exit(1);
  }
  set->items = newItems;
  set->capacity = newCapacity;
}

static int isVarCandidate(const char *name) {
  return name && *name && !isLiteralName(name);
}

static int liveSetContains(const LiveSet *set, const char *name) {
  if (!set || !isVarCandidate(name))
    return 0;
  for (int i = 0; i < set->count; ++i) {
    if (strcmp(set->items[i], name) == 0)
      return 1;
  }
  return 0;
}

static void liveSetAdd(LiveSet *set, const char *name) {
  if (!set || !isVarCandidate(name))
    return;
  if (liveSetContains(set, name))
    return;
  liveSetEnsureCapacity(set);
  set->items[set->count++] = strdup(name);
}

static void liveSetRemove(LiveSet *set, const char *name) {
  if (!set || !isVarCandidate(name))
    return;
  for (int i = 0; i < set->count; ++i) {
    if (strcmp(set->items[i], name) == 0) {
      free(set->items[i]);
      set->items[i] = set->items[set->count - 1];
      set->count--;
      return;
    }
  }
}

static void freeTACInstr(TACInstr *instr) {
  if (!instr)
    return;
  free(instr->arg1);
  free(instr->arg2);
  free(instr->result);
  free(instr);
}

static const char *getDefinedVariable(const TACInstr *instr) {
  if (!instr)
    return NULL;

  switch (instr->op) {
  case TAC_ADD:
  case TAC_SUB:
  case TAC_MUL:
  case TAC_DIV:
  case TAC_LT:
  case TAC_LE:
  case TAC_GT:
  case TAC_GE:
  case TAC_EQ:
  case TAC_NE:
  case TAC_AND:
  case TAC_OR:
  case TAC_NOT:
  case TAC_ASSIGN:
  case TAC_ARRAY_ACCESS:
  case TAC_STRUCT_ACCESS:
  case TAC_CALL:
    return instr->result;
  default:
    return NULL;
  }
}

static int isRemovableForDCE(const TACInstr *instr) {
  if (!instr)
    return 0;

  switch (instr->op) {
  case TAC_ADD:
  case TAC_SUB:
  case TAC_MUL:
  case TAC_DIV:
  case TAC_LT:
  case TAC_LE:
  case TAC_GT:
  case TAC_GE:
  case TAC_EQ:
  case TAC_NE:
  case TAC_AND:
  case TAC_OR:
  case TAC_NOT:
  case TAC_ASSIGN:
  case TAC_ARRAY_ACCESS:
  case TAC_STRUCT_ACCESS:
    return 1;
  default:
    return 0;
  }
}

static void addInstructionUses(const TACInstr *instr, LiveSet *live) {
  if (!instr || !live)
    return;

  switch (instr->op) {
  case TAC_ADD:
  case TAC_SUB:
  case TAC_MUL:
  case TAC_DIV:
  case TAC_LT:
  case TAC_LE:
  case TAC_GT:
  case TAC_GE:
  case TAC_EQ:
  case TAC_NE:
  case TAC_AND:
  case TAC_OR:
    liveSetAdd(live, instr->arg1);
    liveSetAdd(live, instr->arg2);
    break;
  case TAC_NOT:
  case TAC_ASSIGN:
    liveSetAdd(live, instr->arg1);
    break;
  case TAC_PRINT:
    liveSetAdd(live, instr->arg1);
    break;
  case TAC_PARAM:
    liveSetAdd(live, instr->arg1);
    break;
  case TAC_RETURN:
    liveSetAdd(live, instr->arg1);
    break;
  case TAC_ARRAY_ASSIGN:
    liveSetAdd(live, instr->arg1);
    liveSetAdd(live, instr->arg2);
    liveSetAdd(live, instr->result);
    break;
  case TAC_ARRAY_ACCESS:
    liveSetAdd(live, instr->arg1);
    liveSetAdd(live, instr->arg2);
    break;
  case TAC_STRUCT_ASSIGN:
    liveSetAdd(live, instr->arg1);
    liveSetAdd(live, instr->result);
    break;
  case TAC_STRUCT_ACCESS:
    liveSetAdd(live, instr->arg1);
    break;
  case TAC_IFZ:
  case TAC_IFNZ:
    liveSetAdd(live, instr->arg1);
    break;
  case TAC_CALL:
  case TAC_DECL:
  case TAC_ARRAY_DECL:
  case TAC_STRUCT_DECL:
  case TAC_STRUCT_FIELD:
  case TAC_STRUCT_VAR_DECL:
  case TAC_LABEL:
  case TAC_FUNC_BEGIN:
  case TAC_FUNC_END:
    break;
  default:
    break;
  }
}

static void performDeadCodeElimination(void) {
  TACInstr *curr = optimizedList.head;
  int count = 0;
  int hasControlFlow = 0;
  while (curr) {
    if (curr->op == TAC_GOTO || curr->op == TAC_IFZ || curr->op == TAC_IFNZ)
      hasControlFlow = 1;
    count++;
    curr = curr->next;
  }

  if (count == 0 || hasControlFlow)
    return;

  TACInstr **instructions = malloc(sizeof(TACInstr *) * count);
  if (!instructions) {
    fprintf(stderr, "Error: Out of memory in performDeadCodeElimination\n");
    exit(1);
  }

  LiveSet live;
  liveSetInit(&live);

  curr = optimizedList.head;
  for (int i = 0; i < count; ++i) {
    instructions[i] = curr;
    curr = curr->next;
  }

  int *removeFlags = calloc(count, sizeof(int));
  if (!removeFlags) {
    fprintf(stderr, "Error: Out of memory in performDeadCodeElimination\n");
    exit(1);
  }

  for (int i = count - 1; i >= 0; --i) {
    TACInstr *instr = instructions[i];
    const char *definedVar = getDefinedVariable(instr);
    int definesVar = isVarCandidate(definedVar);

    if (isRemovableForDCE(instr) && definesVar &&
        !liveSetContains(&live, definedVar)) {
      removeFlags[i] = 1;
      continue;
    }

    if (definesVar)
      liveSetRemove(&live, definedVar);

    addInstructionUses(instr, &live);
  }

  TACInstr *newHead = NULL;
  TACInstr *newTail = NULL;

  for (int i = 0; i < count; ++i) {
    TACInstr *instr = instructions[i];
    if (removeFlags[i]) {
      freeTACInstr(instr);
      continue;
    }

    instr->next = NULL;
    if (!newHead) {
      newHead = newTail = instr;
    } else {
      newTail->next = instr;
      newTail = instr;
    }
  }

  optimizedList.head = newHead;
  optimizedList.tail = newTail;

  liveSetFree(&live);
  free(removeFlags);
  free(instructions);
}

/* Clone a half-open range of TAC instructions into the optimized list. */
static void appendInstructionRange(TACInstr *start, TACInstr *end) {
  TACInstr *curr = start;
  while (curr && curr != end) {
    TACInstr *copy = cloneInstruction(curr);
    appendOptimizedTAC(copy);
    curr = curr->next;
  }
}

/* Attempt to fully unroll a simple counted while-loop starting at *currPtr. */
static int tryUnrollLoop(TACInstr **currPtr) {
  if (!currPtr || !*currPtr)
    return 0;

  TACInstr *startLabel = *currPtr;
  if (startLabel->op != TAC_LABEL || !startLabel->result)
    return 0;

  TACInstr *condInstr = startLabel->next;
  if (!condInstr || !condInstr->next || condInstr->next->op != TAC_IFZ)
    return 0;

  TACInstr *ifzInstr = condInstr->next;
  if (!ifzInstr->result)
    return 0;

  LoopAnalysis analysis = {0};
  if (!deriveLoopCondition(condInstr, ifzInstr, &analysis))
    return 0;

  if (!findLiteralInitBefore(startLabel, analysis.varName, &analysis.initValue))
    return 0;

  TACInstr *bodyStart = ifzInstr->next;
  if (!bodyStart)
    return 0;

  TACInstr *closingGoto = bodyStart;
  while (closingGoto) {
    if (closingGoto->op == TAC_GOTO && closingGoto->result &&
        strcmp(closingGoto->result, startLabel->result) == 0) {
      break;
    }
    if (closingGoto->op == TAC_LABEL && closingGoto->result &&
        strcmp(closingGoto->result, ifzInstr->result) == 0) {
      return 0;
    }
    closingGoto = closingGoto->next;
  }

  if (!closingGoto || !closingGoto->next ||
      closingGoto->next->op != TAC_LABEL ||
      strcmp(closingGoto->next->result, ifzInstr->result) != 0)
    return 0;

  TACInstr *endLabel = closingGoto->next;

  for (TACInstr *scan = bodyStart; scan && scan != closingGoto;
       scan = scan->next) {
    if (scan->op == TAC_LABEL)
      return 0;
  }

  if (!detectLoopIncrement(bodyStart, closingGoto, analysis.varName,
                           &analysis.stepValue))
    return 0;

  if (!computeTripCount(&analysis))
    return 0;

  if (analysis.tripCount <= 0 || analysis.tripCount > LOOP_UNROLL_LIMIT)
    return 0;

  appendOptimizedTAC(cloneInstruction(startLabel));
  for (int iter = 0; iter < analysis.tripCount; ++iter) {
    appendInstructionRange(bodyStart, closingGoto);
  }
  appendOptimizedTAC(cloneInstruction(endLabel));

  *currPtr = endLabel->next;
  return 1;
}

static void copyWithLoopUnrolling(void) {
  TACInstr *curr = tacList.head;
  currentFunctionContext = NULL;
  while (curr) {
    if (curr->op == TAC_FUNC_BEGIN) {
      currentFunctionContext = curr->result;
    } else if (curr->op == TAC_FUNC_END) {
      currentFunctionContext = NULL;
    }
    if (curr->op == TAC_LABEL && tryUnrollLoop(&curr)) {
      continue;
    }
    TACInstr *copy = cloneInstruction(curr);
    appendOptimizedTAC(copy);
    curr = curr->next;
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
    param->line = args->line;
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

  case NODE_BOOL: {
    char *temp = malloc(4);
    sprintf(temp, "%d", node->data.boolValue ? 1 : 0);
    return temp;
  }

  case NODE_VAR: {
    recordNameType(node->data.name, lookupNameType(node->data.name));
    return strdup(node->data.name);
  }

  case NODE_UNARY_OP: {
    char *operand = generateTACExpr(node->data.unary.expr);
    char *temp = newTemp();
    recordNameType(temp, TYPE_BOOL);
    TACInstr *instr = createTAC(TAC_NOT, operand, NULL, temp);
    instr->arg1Type = inferNodeType(node->data.unary.expr);
    instr->resultType = TYPE_BOOL;
    instr->line = node->line;
    appendTAC(instr);
    return temp;
  }

  case NODE_BINOP: {
    if (node->data.binop.op == OP_DIV) {
      ASTNode *rightLit = node->data.binop.right;
      if (rightLit) {
        int zeroInt = rightLit->type == NODE_NUM && rightLit->data.num == 0;
        int zeroFloat = rightLit->type == NODE_FLOAT && rightLit->data.fnum == 0.0;
        if (zeroInt || zeroFloat) {
          reportSemanticError(node->line,
                              "division by zero in constant expression");
        }
      }
    }
    char *left = generateTACExpr(node->data.binop.left);
    char *right = generateTACExpr(node->data.binop.right);
    DataType leftType = inferNodeType(node->data.binop.left);
    DataType rightType = inferNodeType(node->data.binop.right);
    BinaryOp op = node->data.binop.op;

    if (isComparisonOp(op) || isLogicalOp(op)) {
      char *temp = newTemp();
      recordNameType(temp, TYPE_BOOL);
      TACOp tacOp = TAC_EQ;
      switch (op) {
      case OP_LT:
        tacOp = TAC_LT;
        break;
      case OP_LE:
        tacOp = TAC_LE;
        break;
      case OP_GT:
        tacOp = TAC_GT;
        break;
      case OP_GE:
        tacOp = TAC_GE;
        break;
      case OP_EQ:
        tacOp = TAC_EQ;
        break;
      case OP_NEQ:
        tacOp = TAC_NE;
        break;
      case OP_AND:
        tacOp = TAC_AND;
        break;
      case OP_OR:
        tacOp = TAC_OR;
        break;
      default:
        break;
      }

      TACInstr *instr = createTAC(tacOp, left, right, temp);
      instr->arg1Type = leftType;
      instr->arg2Type = rightType;
      instr->resultType = TYPE_BOOL;
      instr->line = node->line;
      appendTAC(instr);
      return temp;
    }

    char *temp = newTemp();
    recordNameType(temp, exprType);

    if (leftType != exprType) {
      char detail[128];
      snprintf(detail, sizeof(detail), "in '%s' expression (left operand)",
               binaryOpToString(op));
      warnTypeCoercion(leftType, exprType, detail);
    }
    if (rightType != exprType) {
      char detail[128];
      snprintf(detail, sizeof(detail), "in '%s' expression (right operand)",
               binaryOpToString(op));
      warnTypeCoercion(rightType, exprType, detail);
    }

    TACOp tacOp = TAC_ADD;
    switch (op) {
    case OP_ADD:
      tacOp = TAC_ADD;
      break;
    case OP_SUB:
      tacOp = TAC_SUB;
      break;
    case OP_MUL:
      tacOp = TAC_MUL;
      break;
    case OP_DIV:
      tacOp = TAC_DIV;
      break;
    default:
      break;
    }

    TACInstr *instr = createTAC(tacOp, left, right, temp);
    instr->arg1Type = leftType;
    instr->arg2Type = rightType;
    instr->resultType = exprType;
    instr->line = node->line;
    appendTAC(instr);
    return temp;
  }

  case NODE_ARRAY_ACCESS: {
    validateArrayIndex(node->data.array_access.name,
                       node->data.array_access.index, node->line);
    char *indexExpr = generateTACExpr(node->data.array_access.index);
    char *temp = newTemp();
    recordNameType(temp, exprType);

    TACInstr *instr = createTAC(TAC_ARRAY_ACCESS, indexExpr,
                                node->data.array_access.name, temp);
    instr->arg1Type = inferNodeType(node->data.array_access.index);
    instr->arg2Type = lookupNameType(node->data.array_access.name);
    instr->resultType = exprType;
    instr->line = node->line;
    appendTAC(instr);
    return temp;
  }

  case NODE_CONDITIONAL: {
    char *condValue = generateTACExpr(node->data.conditional.condition);
    DataType condType = inferNodeType(node->data.conditional.condition);
    char *falseLabel = newLabel("cond_false");
    char *endLabel = newLabel("cond_end");
    char *resultTemp = newTemp();
    DataType trueType = inferNodeType(node->data.conditional.trueExpr);
    DataType falseType = inferNodeType(node->data.conditional.falseExpr);
    DataType resultType = mergeTypes(trueType, falseType);
    recordNameType(resultTemp, resultType);

    TACInstr *branch = createTAC(TAC_IFZ, condValue, NULL, falseLabel);
    branch->arg1Type = condType;
    branch->line = node->line;
    appendTAC(branch);

    char *trueValue = generateTACExpr(node->data.conditional.trueExpr);
    TACInstr *assignTrue = createTAC(TAC_ASSIGN, trueValue, NULL, resultTemp);
    assignTrue->arg1Type = trueType;
    assignTrue->resultType = resultType;
    assignTrue->line = node->line;
    appendTAC(assignTrue);

    appendTAC(createTAC(TAC_GOTO, NULL, NULL, endLabel));
    appendTAC(createTAC(TAC_LABEL, NULL, NULL, falseLabel));

    char *falseValue = generateTACExpr(node->data.conditional.falseExpr);
    TACInstr *assignFalse = createTAC(TAC_ASSIGN, falseValue, NULL, resultTemp);
    assignFalse->arg1Type = falseType;
    assignFalse->resultType = resultType;
    assignFalse->line = node->line;
    appendTAC(assignFalse);

    appendTAC(createTAC(TAC_LABEL, NULL, NULL, endLabel));
    return resultTemp;
  }

  case NODE_STRUCT_ACCESS: {
    const char *structType =
        lookupStructVarType(node->data.struct_access.varName);
    if (!structType) {
      reportSemanticError(node->line, "variable '%s' is not a struct",
                          node->data.struct_access.varName);
      char *temp = newTemp();
      recordNameType(temp, TYPE_INT);
      return temp;
    }

    DataType fieldType = TYPE_INT;
    if (!structFieldExists(structType, node->data.struct_access.fieldName,
                           &fieldType)) {
      reportSemanticError(node->line, "struct '%s' has no field '%s'",
                          structType, node->data.struct_access.fieldName);
      char *temp = newTemp();
      recordNameType(temp, TYPE_INT);
      return temp;
    }

    exprType = fieldType;
    char *temp = newTemp();
    recordNameType(temp, exprType);

    TACInstr *instr =
        createTAC(TAC_STRUCT_ACCESS, node->data.struct_access.varName,
                  node->data.struct_access.fieldName, temp);
    instr->arg2Type = fieldType;
    instr->resultType = exprType;
    instr->line = node->line;
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
    call->line = node->line;
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
    TACOp op = inGlobalContext ? TAC_GLOBAL_DECL : TAC_DECL;
    TACInstr *instr =
        createTAC(op, "int", NULL, node->data.name);
    instr->resultType = TYPE_INT;
    appendTAC(instr);
    break;
  }

  case NODE_CHAR_DECL: {
    recordNameType(node->data.name, TYPE_CHAR);
    TACOp op = inGlobalContext ? TAC_GLOBAL_DECL : TAC_DECL;
    TACInstr *instr =
        createTAC(op, "char", NULL, node->data.name);
    instr->resultType = TYPE_CHAR;
    appendTAC(instr);
    break;
  }

  case NODE_FLOAT_DECL: {
    recordNameType(node->data.name, TYPE_FLOAT);
    TACOp op = inGlobalContext ? TAC_GLOBAL_DECL : TAC_DECL;
    TACInstr *instr =
        createTAC(op, "float", NULL, node->data.name);
    instr->resultType = TYPE_FLOAT;
    appendTAC(instr);
    break;
  }

  case NODE_BOOL_DECL: {
    recordNameType(node->data.name, TYPE_BOOL);
    TACOp op = inGlobalContext ? TAC_GLOBAL_DECL : TAC_DECL;
    TACInstr *instr =
        createTAC(op, "bool", NULL, node->data.name);
    instr->resultType = TYPE_BOOL;
    appendTAC(instr);
    break;
  }

  case NODE_ASSIGN: {
    char *expr = generateTACExpr(node->data.assign.value);
    DataType valueType = inferNodeType(node->data.assign.value);
    DataType targetType = lookupNameType(node->data.assign.var);
    int targetKnown = hasRecordedType(node->data.assign.var);
    if (!targetKnown)
      targetType = valueType;
    else if (valueType != targetType) {
      char detail[128];
      snprintf(detail, sizeof(detail), "while assigning to '%s'",
               node->data.assign.var);
      warnTypeCoercion(valueType, targetType, detail);
    }
    recordNameType(node->data.assign.var, targetType);

    TACInstr *instr = createTAC(TAC_ASSIGN, expr, NULL, node->data.assign.var);
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
  case NODE_EXPR_STMT:
    (void)generateTACExpr(node->data.expr);
    break;

  case NODE_STMT_LIST:
    generateTAC(node->data.stmtlist.stmt);
    generateTAC(node->data.stmtlist.next);
    break;
  case NODE_BLOCK:
    generateTAC(node->data.block_items);
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
    recordArrayInfo(node->data.array_decl.name, node->data.array_decl.size);
    TACOp op = inGlobalContext ? TAC_GLOBAL_ARRAY_DECL : TAC_ARRAY_DECL;
    TACInstr *instr = createTAC(op, (char *)typeStr, sizeBuf,
                                node->data.array_decl.name);
    instr->resultType = elemType;
    instr->line = node->line;
    appendTAC(instr);
    break;
  }
  case NODE_ARRAY_ASSIGN: {
    validateArrayIndex(node->data.array_assign.name,
                       node->data.array_assign.index, node->line);
    char *indexExpr = generateTACExpr(node->data.array_assign.index);
    char *valueExpr = generateTACExpr(node->data.array_assign.value);
    DataType indexType = inferNodeType(node->data.array_assign.index);
    DataType valueType = inferNodeType(node->data.array_assign.value);
    DataType elemType = lookupNameType(node->data.array_assign.name);
    if (indexType != TYPE_INT) {
      char detail[128];
      snprintf(detail, sizeof(detail), "for index of array '%s'",
               node->data.array_assign.name);
      warnTypeCoercion(indexType, TYPE_INT, detail);
    }
    if (valueType != elemType) {
      char detail[128];
      snprintf(detail, sizeof(detail), "for element of array '%s'",
               node->data.array_assign.name);
      warnTypeCoercion(valueType, elemType, detail);
    }
    TACInstr *instr = createTAC(TAC_ARRAY_ASSIGN, indexExpr, valueExpr,
                                node->data.array_assign.name);
    instr->arg1Type = indexType;
    instr->arg2Type = valueType;
    instr->resultType = elemType;
    instr->line = node->line;
    appendTAC(instr);
    break;
  }

  case NODE_IF: {
    char *condValue = generateTACExpr(node->data.if_stmt.condition);
    DataType condType = inferNodeType(node->data.if_stmt.condition);
    ASTNode *elseBranch = node->data.if_stmt.elseBranch;
    char *elseLabel = elseBranch ? newLabel("if_else") : NULL;
    char *endLabel = newLabel("if_end");

    TACInstr *branch =
        createTAC(TAC_IFZ, condValue, NULL, elseBranch ? elseLabel : endLabel);
    branch->arg1Type = condType;
    appendTAC(branch);

    generateTAC(node->data.if_stmt.thenBranch);

    if (elseBranch) {
      appendTAC(createTAC(TAC_GOTO, NULL, NULL, endLabel));
      appendTAC(createTAC(TAC_LABEL, NULL, NULL, elseLabel));
      generateTAC(elseBranch);
    }

    appendTAC(createTAC(TAC_LABEL, NULL, NULL, endLabel));
    break;
  }

  case NODE_SWITCH: {
    char *switchValue = generateTACExpr(node->data.switch_stmt.expr);
    DataType switchType = inferNodeType(node->data.switch_stmt.expr);
    char *endLabel = newLabel("switch_end");
    pushBreakLabel(endLabel);

    for (ASTNode *curr = node->data.switch_stmt.cases; curr;
         curr = curr->data.case_stmt.next) {
      if (!curr->data.case_stmt.label) {
        curr->data.case_stmt.label = curr->data.case_stmt.isDefault
                                         ? newLabel("switch_default")
                                         : newLabel("switch_case");
      }
    }

    ASTNode *defaultNode = node->data.switch_stmt.defaultCase;
    if (defaultNode && !defaultNode->data.case_stmt.label) {
      defaultNode->data.case_stmt.label = newLabel("switch_default");
    }

    for (ASTNode *curr = node->data.switch_stmt.cases; curr;
         curr = curr->data.case_stmt.next) {
      if (curr->data.case_stmt.isDefault)
        continue;

      if (!curr->data.case_stmt.valueExpr) {
        reportSemanticError(curr->line,
                            "case label requires a constant expression");
        continue;
      }

      int caseValue = 0;
      if (!evalConstInt(curr->data.case_stmt.valueExpr, &caseValue)) {
        reportSemanticError(curr->line,
                            "case label must be a compile-time constant");
        continue;
      }

      char literal[32];
      snprintf(literal, sizeof(literal), "%d", caseValue);

      char *cmpTemp = newTemp();
      recordNameType(cmpTemp, TYPE_BOOL);
      TACInstr *cmp = createTAC(TAC_EQ, switchValue, literal, cmpTemp);
      cmp->arg1Type = switchType;
      cmp->arg2Type = inferNodeType(curr->data.case_stmt.valueExpr);
      cmp->resultType = TYPE_BOOL;
      cmp->line = curr->line;
      appendTAC(cmp);

      TACInstr *branch =
          createTAC(TAC_IFNZ, cmpTemp, NULL, curr->data.case_stmt.label);
      branch->arg1Type = TYPE_BOOL;
      branch->line = curr->line;
      appendTAC(branch);
    }

    const char *fallthroughTarget =
        (defaultNode && defaultNode->data.case_stmt.label)
            ? defaultNode->data.case_stmt.label
            : endLabel;
    appendTAC(createTAC(TAC_GOTO, NULL, NULL, (char *)fallthroughTarget));

    for (ASTNode *curr = node->data.switch_stmt.cases; curr;
         curr = curr->data.case_stmt.next) {
      appendTAC(createTAC(TAC_LABEL, NULL, NULL, curr->data.case_stmt.label));
      generateTAC(curr->data.case_stmt.statements);
    }

    appendTAC(createTAC(TAC_LABEL, NULL, NULL, endLabel));
    popBreakLabel();
    break;
  }

  case NODE_BREAK: {
    const char *label = currentBreakLabel();
    if (!label) {
      reportSemanticError(node->line, "'break' used outside of switch");
    } else {
      appendTAC(createTAC(TAC_GOTO, NULL, NULL, (char *)label));
    }
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
    TACOp op =
        inGlobalContext ? TAC_GLOBAL_STRUCT_VAR_DECL : TAC_STRUCT_VAR_DECL;
    TACInstr *instr =
        createTAC(op, node->data.struct_var_decl.structName, NULL,
                  node->data.struct_var_decl.varName);
    instr->resultType = TYPE_VOID;
    appendTAC(instr);
    break;
  }

  case NODE_STRUCT_ASSIGN: {
    const char *structType =
        lookupStructVarType(node->data.struct_assign.varName);
    if (!structType) {
      reportSemanticError(node->line, "variable '%s' is not a struct",
                          node->data.struct_assign.varName);
      break;
    }

    DataType fieldType = TYPE_INT;
    if (!structFieldExists(structType, node->data.struct_assign.fieldName,
                           &fieldType)) {
      reportSemanticError(node->line, "struct '%s' has no field '%s'",
                          structType, node->data.struct_assign.fieldName);
      break;
    }

    char *valueExpr = generateTACExpr(node->data.struct_assign.value);
    DataType valueType = inferNodeType(node->data.struct_assign.value);
    if (valueType != fieldType) {
      char detail[128];
      snprintf(detail, sizeof(detail), "while assigning to field '%s.%s'",
               node->data.struct_assign.varName,
               node->data.struct_assign.fieldName);
      warnTypeCoercion(valueType, fieldType, detail);
    }
    TACInstr *instr = createTAC(TAC_STRUCT_ASSIGN, valueExpr,
                                node->data.struct_assign.fieldName,
                                node->data.struct_assign.varName);
    instr->arg1Type = valueType;
    instr->resultType = fieldType;
    instr->line = node->line;
    appendTAC(instr);
    break;
  }

  case NODE_FUNC_DECL: {
    const char *name = node->data.func_decl.name;
    if (!name)
      name = "main";
    recordFunctionReturnType(name, node->data.func_decl.returnType);
    registerParamTypes(node->data.func_decl.params);
    recordFunctionParams(name, node->data.func_decl.params);

    TACInstr *begin = createTAC(
        TAC_FUNC_BEGIN, (char *)typeToString(node->data.func_decl.returnType),
        NULL, (char *)name);
    begin->resultType = node->data.func_decl.returnType;
    appendTAC(begin);

    appendTAC(createTAC(TAC_LABEL, NULL, NULL, (char *)name));

    int previousGlobal = inGlobalContext;
    inGlobalContext = 0;
    generateTAC(node->data.func_decl.body);
    inGlobalContext = previousGlobal;

    TACInstr *end = createTAC(TAC_FUNC_END, NULL, NULL, (char *)name);
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
  case NODE_WHILE: {
    char *startLabel = newLabel("while_start");
    char *endLabel = newLabel("while_end");

    appendTAC(createTAC(TAC_LABEL, NULL, NULL, startLabel));

    char *condTemp = generateTACExpr(node->data.while_stmt.condition);
    TACInstr *exitBranch = createTAC(TAC_IFZ, condTemp, NULL, endLabel);
    exitBranch->arg1Type = inferNodeType(node->data.while_stmt.condition);
    appendTAC(exitBranch);

    pushBreakLabel(endLabel);
    generateTAC(node->data.while_stmt.body);
    popBreakLabel();

    appendTAC(createTAC(TAC_GOTO, NULL, NULL, startLabel));
    appendTAC(createTAC(TAC_LABEL, NULL, NULL, endLabel));

    break;
  }
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
    case TAC_GLOBAL_DECL:
      printf("GLOBAL DECL %s", curr->result);
      printf("    // Global declaration of '%s'\n", curr->result);
      break;
    case TAC_GLOBAL_ARRAY_DECL:
      printf("GLOBAL ARRAY %s[%s]", curr->result, curr->arg2);
      printf("    // Global array declaration\n");
      break;
    case TAC_GLOBAL_STRUCT_VAR_DECL:
      printf("GLOBAL STRUCT %s %s\n", curr->arg1, curr->result);
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
    case TAC_LT:
      printf("%s = %s < %s", curr->result, curr->arg1, curr->arg2);
      printf("     // Comparison (LT)\n");
      break;
    case TAC_LE:
      printf("%s = %s <= %s", curr->result, curr->arg1, curr->arg2);
      printf("    // Comparison (LE)\n");
      break;
    case TAC_GT:
      printf("%s = %s > %s", curr->result, curr->arg1, curr->arg2);
      printf("     // Comparison (GT)\n");
      break;
    case TAC_GE:
      printf("%s = %s >= %s", curr->result, curr->arg1, curr->arg2);
      printf("    // Comparison (GE)\n");
      break;
    case TAC_EQ:
      printf("%s = %s == %s", curr->result, curr->arg1, curr->arg2);
      printf("    // Equality\n");
      break;
    case TAC_NE:
      printf("%s = %s != %s", curr->result, curr->arg1, curr->arg2);
      printf("    // Inequality\n");
      break;
    case TAC_AND:
      printf("%s = %s && %s", curr->result, curr->arg1, curr->arg2);
      printf("   // Logical AND\n");
      break;
    case TAC_OR:
      printf("%s = %s || %s", curr->result, curr->arg1, curr->arg2);
      printf("   // Logical OR\n");
      break;
    case TAC_NOT:
      printf("%s = !%s", curr->result, curr->arg1);
      printf("        // Logical NOT\n");
      break;
    case TAC_ASSIGN:
      printf("%s = %s", curr->result, curr->arg1);
      printf("           // Assign value to %s\n", curr->result);
      break;
    case TAC_PRINT:
      printf("PRINT %s", curr->arg1);
      printf("          // Output value of %s\n", curr->arg1);
      break;
    case TAC_GOTO:
      printf("GOTO %s\n", curr->result);
      break;
    case TAC_IFZ:
      printf("IFZ %s GOTO %s\n", curr->arg1, curr->result);
      break;
    case TAC_IFNZ:
      printf("IFNZ %s GOTO %s\n", curr->arg1, curr->result);
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
    case TAC_LABEL:
      printf("LABEL %s\n", curr->result ? curr->result : "<anon>");
      break;
    case TAC_PARAM:
      printf("PARAM %s", curr->arg1 ? curr->arg1 : "<null>");
      printf("        // Function argument\n");
      break;
    case TAC_CALL:
      if (curr->result) {
        printf("%s = CALL %s (%d args)", curr->result,
               curr->arg1 ? curr->arg1 : "<func>", curr->paramCount);
      } else {
        printf("CALL %s (%d args)", curr->arg1 ? curr->arg1 : "<func>",
               curr->paramCount);
      }
      printf("\n");
      break;
    case TAC_RETURN:
      if (curr->arg1)
        printf("RETURN %s\n", curr->arg1);
      else
        printf("RETURN\n");
      break;
    case TAC_FUNC_BEGIN:
      printf("FUNC BEGIN %s : %s\n",
             curr->result ? curr->result : "<anon>",
             curr->arg1 ? curr->arg1 : "<type>");
      break;
    case TAC_FUNC_END:
      printf("FUNC END %s\n", curr->result ? curr->result : "<anon>");
      break;
    default:
      printf("// Unhandled TAC opcode %d\n", curr->op);
      break;
    }
    curr = curr->next;
  }
}

// Simple optimization: constant folding and copy propagation
void optimizeTAC() {
  analyzeParamConstants();
  TACInstr *curr = tacList.head;

  int hasControlFlow = 0;
  for (TACInstr *scan = tacList.head; scan; scan = scan->next) {
    if (scan->op == TAC_GOTO || scan->op == TAC_IFZ || scan->op == TAC_IFNZ) {
      hasControlFlow = 1;
      break;
    }
  }

  if (hasControlFlow) {
    copyWithLoopUnrolling();
    return;
  }

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
    case TAC_GLOBAL_DECL:
    case TAC_GLOBAL_ARRAY_DECL:
    case TAC_GLOBAL_STRUCT_VAR_DECL:
      newInstr = createTAC(curr->op, curr->arg1, curr->arg2, curr->result);
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

    case TAC_LT:
    case TAC_LE:
    case TAC_GT:
    case TAC_GE:
    case TAC_EQ:
    case TAC_NE:
    case TAC_AND:
    case TAC_OR: {
      newInstr = createTAC(curr->op, curr->arg1, curr->arg2, curr->result);
      copyTypeInfo(newInstr, curr);
      break;
    }

    case TAC_NOT: {
      newInstr = createTAC(TAC_NOT, curr->arg1, NULL, curr->result);
      copyTypeInfo(newInstr, curr);
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
      newInstr =
          createTAC(TAC_ARRAY_DECL, curr->arg1, curr->arg2, curr->result);
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
    case TAC_GOTO:
    case TAC_IFZ:
    case TAC_IFNZ:
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
      newInstr->line = curr->line;
      appendOptimizedTAC(newInstr);
    }

    curr = curr->next;
  }

  performDeadCodeElimination();
}

static void printOptimizedInstruction(TACInstr *curr, int *lineNumPtr) {
  if (!curr || !lineNumPtr)
    return;

  int lineNum = *lineNumPtr;
  switch (curr->op) {
  case TAC_DECL:
    printf("%2d: DECL %s\n", lineNum, curr->result);
    lineNum++;
    break;
  case TAC_GLOBAL_DECL:
    printf("%2d: GLOBAL DECL %s\n", lineNum, curr->result);
    lineNum++;
    break;
  case TAC_GLOBAL_ARRAY_DECL:
    printf("%2d: GLOBAL ARRAY %s[%s]\n", lineNum, curr->result, curr->arg2);
    lineNum++;
    break;
  case TAC_GLOBAL_STRUCT_VAR_DECL:
    printf("%2d: GLOBAL STRUCT %s %s\n", lineNum, curr->arg1, curr->result);
    lineNum++;
    break;
  case TAC_ADD:
    printf("%2d: %s = %s + %s", lineNum, curr->result, curr->arg1,
           curr->arg2);
    printf("     // Runtime addition needed\n");
    lineNum++;
    break;
  case TAC_SUB:
    printf("%2d: %s = %s - %s", lineNum, curr->result, curr->arg1,
           curr->arg2);
    printf("     // Runtime subtraction needed\n");
    lineNum++;
    break;
  case TAC_MUL:
    printf("%2d: %s = %s * %s", lineNum, curr->result, curr->arg1,
           curr->arg2);
    printf("     // Runtime multiplication needed\n");
    lineNum++;
    break;
  case TAC_DIV:
    printf("%2d: %s = %s / %s", lineNum, curr->result, curr->arg1,
           curr->arg2);
    printf("     // Runtime division needed\n");
    lineNum++;
    break;
  case TAC_LT:
    printf("%2d: %s = %s < %s\n", lineNum++, curr->result, curr->arg1,
           curr->arg2);
    break;
  case TAC_LE:
    printf("%2d: %s = %s <= %s\n", lineNum++, curr->result, curr->arg1,
           curr->arg2);
    break;
  case TAC_GT:
    printf("%2d: %s = %s > %s\n", lineNum++, curr->result, curr->arg1,
           curr->arg2);
    break;
  case TAC_GE:
    printf("%2d: %s = %s >= %s\n", lineNum++, curr->result, curr->arg1,
           curr->arg2);
    break;
  case TAC_EQ:
    printf("%2d: %s = %s == %s\n", lineNum++, curr->result, curr->arg1,
           curr->arg2);
    break;
  case TAC_NE:
    printf("%2d: %s = %s != %s\n", lineNum++, curr->result, curr->arg1,
           curr->arg2);
    break;
  case TAC_AND:
    printf("%2d: %s = %s && %s\n", lineNum++, curr->result, curr->arg1,
           curr->arg2);
    break;
  case TAC_OR:
    printf("%2d: %s = %s || %s\n", lineNum++, curr->result, curr->arg1,
           curr->arg2);
    break;
  case TAC_NOT:
    printf("%2d: %s = !%s\n", lineNum++, curr->result, curr->arg1);
    break;
  case TAC_ASSIGN:
    printf("%2d: %s = %s", lineNum, curr->result, curr->arg1);
    if (isNumericLiteral(curr->arg1)) {
      printf("           // Constant value: %s\n", curr->arg1);
    } else {
      printf("           // Copy value\n");
    }
    lineNum++;
    break;
  case TAC_PRINT:
    printf("%2d: PRINT %s", lineNum, curr->arg1);
    if (isNumericLiteral(curr->arg1)) {
      printf("          // Print constant: %s\n", curr->arg1);
    } else {
      printf("          // Print variable\n");
    }
    lineNum++;
    break;
  case TAC_GOTO:
    printf("%2d: GOTO %s\n", lineNum++, curr->result);
    break;
  case TAC_IFZ:
    printf("%2d: IFZ %s GOTO %s\n", lineNum++, curr->arg1, curr->result);
    break;
  case TAC_IFNZ:
    printf("%2d: IFNZ %s GOTO %s\n", lineNum++, curr->arg1, curr->result);
    break;
  case TAC_ARRAY_DECL:
    printf("%2d: ARRAY DECL %s\n", lineNum++, curr->result);
    break;
  case TAC_ARRAY_ASSIGN:
    printf("%2d: %s[%s] = %s   // Array assignment\n", lineNum++, curr->result,
           curr->arg1, curr->arg2);
    break;
  case TAC_ARRAY_ACCESS:
    printf("%2d: %s = %s[%s]   // Array access\n", lineNum++, curr->result,
           curr->arg2, curr->arg1);
    break;
  case TAC_STRUCT_DECL:
    printf("%2d: STRUCT %s   // Struct definition\n", lineNum++, curr->result);
    break;
  case TAC_STRUCT_FIELD:
    printf("%2d: FIELD %s.%s (%s)\n", lineNum++, curr->result, curr->arg1,
           curr->arg2);
    break;
  case TAC_STRUCT_VAR_DECL:
    printf("%2d: STRUCT VAR %s : %s\n", lineNum++, curr->result, curr->arg1);
    break;
  case TAC_STRUCT_ASSIGN:
    printf("%2d: %s.%s = %s   // Struct assignment\n", lineNum++, curr->result,
           curr->arg2, curr->arg1);
    break;
  case TAC_STRUCT_ACCESS:
    printf("%2d: %s = %s.%s   // Struct field access\n", lineNum++, curr->result,
           curr->arg1, curr->arg2);
    break;
  case TAC_LABEL:
    printf("%2d: LABEL %s\n", lineNum++, curr->result ? curr->result : "<anon>");
    break;
  case TAC_PARAM:
    printf("%2d: PARAM %s\n", lineNum++, curr->arg1 ? curr->arg1 : "<null>");
    break;
  case TAC_CALL:
    if (curr->result) {
      printf("%2d: %s = CALL %s (%d args)\n", lineNum++, curr->result,
             curr->arg1 ? curr->arg1 : "<func>", curr->paramCount);
    } else {
      printf("%2d: CALL %s (%d args)\n", lineNum++,
             curr->arg1 ? curr->arg1 : "<func>", curr->paramCount);
    }
    break;
  case TAC_RETURN:
    if (curr->arg1) {
      printf("%2d: RETURN %s\n", lineNum++, curr->arg1);
    } else {
      printf("%2d: RETURN\n", lineNum++);
    }
    break;
  case TAC_FUNC_BEGIN:
    printf("%2d: FUNC BEGIN %s : %s\n", lineNum++,
           curr->result ? curr->result : "<anon>",
           curr->arg1 ? curr->arg1 : "<type>");
    break;
  case TAC_FUNC_END:
    printf("%2d: FUNC END %s\n", lineNum++, curr->result ? curr->result : "<anon>");
    break;
  default:
    return;
  }

  *lineNumPtr = lineNum;
}

void printOptimizedTAC() {
  printf("Optimized TAC Instructions:\n");
  printf("─────────────────────────────\n");
  TACInstr *curr = optimizedList.head;
  int lineNum = 1;
  while (curr) {
    printOptimizedInstruction(curr, &lineNum);
    curr = curr->next;
  }
}

void printFunctionReturnTable() {
  printf("\n=== FUNCTION RETURN TABLE ===\n");
  printf("Count: %d\n", functionReturnCount);
  if (functionReturnCount == 0) {
    printf("(empty)\n");
  } else {
    for (int i = 0; i < functionReturnCount; ++i) {
      const char *name = functionReturnTable[i].name
                             ? functionReturnTable[i].name
                             : "<unnamed>";
      printf(" [%d] %s -> %s\n", i, name,
             typeToString(functionReturnTable[i].returnType));
    }
  }
  printf("============================="
         "\n\n");
}

TACList *getTACList(void) { return &tacList; }

TACList *getOptimizedTACList(void) { return &optimizedList; }

static size_t countInstructions(const TACList *list) {
  size_t count = 0;
  if (!list)
    return 0;
  for (TACInstr *curr = list->head; curr; curr = curr->next)
    ++count;
  return count;
}

void getTACMetrics(TACMetrics *metrics) {
  if (!metrics)
    return;
  metrics->tacInstructions = countInstructions(&tacList);
  metrics->optimizedTACInstructions = countInstructions(&optimizedList);
  metrics->tempCount = (size_t)tacList.tempCount;
}
