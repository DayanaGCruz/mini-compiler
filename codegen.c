#include "codegen.h"
#include "symtab.h"
#include "tac.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOCAL_STACK_SIZE 400
#define RA_SAVE_OFFSET (LOCAL_STACK_SIZE - 4)

typedef struct {
  char name[64];
  DataType returnType;
  ASTNode *params;
} FunctionInfo;

static FILE *output = NULL;
static int tempReg = 0;
static int floatTempReg = 0;
static char currentReturnLabel[256];
static FunctionInfo functionTable[128];
static int functionCount = 0;
static FunctionInfo *currentFunction = NULL;
static int currentParamIndex = 0;
static int inFunction = 0;
static int boundsCheckLabelCounter = 0;
static int compareLabelCounter = 0;
static int needsInputStub = 0;
static int needsOutputStub = 0;

static void resetTempRegs(void);
static int getNextTemp(void);
static int getNextFloatTemp(void);
static int isLiteral(const char *operand);
static int isFloatLiteral(const char *operand);
static void ensureStorage(const char *name, DataType type);
static DataType parseTypeString(const char *typeStr);
static int loadRawIntValue(const char *operand, DataType operandType);
static int loadRawFloatValue(const char *operand);
static int materializeInt(const char *operand, DataType operandType);
static int materializeFloat(const char *operand, DataType operandType);
static void storeValue(const char *dest, DataType type, int reg, int isFloat);
static const char *formatFunctionLabel(const char *name, char *buffer,
                                       size_t size);
static FunctionInfo *lookupFunctionInfo(const char *name);
static FunctionInfo *registerFunctionInfo(const char *name, DataType returnType,
                                          ASTNode *params);
static void collectFunctionInfo(ASTNode *node);
static void processParameterSequence(ASTNode *params, int *paramIndex);
static void beginFunction(const char *name);
static void ensureFunctionContext(void);
static void finishFunction(void);
static void emitBinaryOp(TACInstr *instr);
static void emitAssign(TACInstr *instr);
static void emitPrint(TACInstr *instr);
static void emitArrayAssign(TACInstr *instr);
static void emitArrayAccess(TACInstr *instr);
static void emitComparison(TACInstr *instr);
static void emitLogical(TACInstr *instr);
static void emitNotInstr(TACInstr *instr);
static void emitStructAssign(TACInstr *instr);
static void emitStructAccess(TACInstr *instr);
static void emitArrayBoundsCheck(const char *arrayName, int indexReg);
static void emitParam(TACInstr *instr);
static void emitCall(TACInstr *instr);
static void emitReturn(TACInstr *instr);
static void emitGoto(TACInstr *instr);
static void emitConditionalBranch(TACInstr *instr);
static void handleDecl(TACInstr *instr);
static void handleArrayDecl(TACInstr *instr);
static void handleStructDecl(TACInstr *instr);
static void handleStructField(TACInstr *instr);
static void handleStructVarDecl(TACInstr *instr);
static void emitLabel(TACInstr *instr);
static const char *dataTypeToString(DataType type);
static int countFunctionParams(ASTNode *params);
static void printFunctionParams(ASTNode *params, int indent);
static void printFunctionTable(void);
static int materializeBoolean(const char *operand, DataType type);

static void resetTempRegs(void) {
  tempReg = 0;
  floatTempReg = 0;
}

static int getNextTemp(void) {
  int reg = tempReg++;
  if (tempReg > 7)
    tempReg = 0;
  return reg;
}

static int getNextFloatTemp(void) {
  int reg = floatTempReg++;
  if (floatTempReg > 9)
    floatTempReg = 0;
  return reg;
}

static int isLiteral(const char *operand) {
  if (!operand || !*operand)
    return 0;
  if (isdigit((unsigned char)operand[0]) || operand[0] == '-' ||
      operand[0] == '.')
    return 1;
  return 0;
}

static int isFloatLiteral(const char *operand) {
  if (!isLiteral(operand))
    return 0;
  for (const char *p = operand; *p; ++p) {
    if (*p == '.' || *p == 'e' || *p == 'E')
      return 1;
  }
  return 0;
}

static DataType parseTypeString(const char *typeStr) {
  if (!typeStr)
    return TYPE_INT;
  if (strcmp(typeStr, "float") == 0)
    return TYPE_FLOAT;
  if (strcmp(typeStr, "char") == 0)
    return TYPE_CHAR;
  if (strcmp(typeStr, "bool") == 0)
    return TYPE_BOOL;
  if (strcmp(typeStr, "void") == 0)
    return TYPE_VOID;
  return TYPE_INT;
}

static const char *dataTypeToString(DataType type) {
  switch (type) {
  case TYPE_INT:
    return "int";
  case TYPE_CHAR:
    return "char";
  case TYPE_FLOAT:
    return "float";
  case TYPE_BOOL:
    return "bool";
  case TYPE_VOID:
    return "void";
  default:
    return "unknown";
  }
}

static void ensureStorage(const char *name, DataType type) {
  if (!name || isLiteral(name))
    return;

  if (isVarDeclared((char *)name))
    return;

  int offset = -1;
  switch (type) {
  case TYPE_CHAR:
    offset = addCharVar((char *)name);
    break;
  case TYPE_FLOAT:
    offset = addFloatVar((char *)name);
    break;
  case TYPE_BOOL:
    offset = addBoolVar((char *)name);
    break;
  case TYPE_VOID:
    offset = addVar((char *)name);
    break;
  default:
    offset = addVar((char *)name);
    break;
  }
  if (offset < 0) {
    fprintf(stderr, "Error: Failed to allocate storage for %s\n", name);
    exit(1);
  }
}

static int loadRawIntValue(const char *operand, DataType operandType) {
  int reg = getNextTemp();
  if (!operand) {
    fprintf(output, "    move $t%d, $zero\n", reg);
    return reg;
  }

  if (isLiteral(operand)) {
    fprintf(output, "    li $t%d, %s\n", reg, operand);
    return reg;
  }

  int offset = getVarOffset((char *)operand);
  if (offset == -1) {
    fprintf(stderr, "Error: Variable %s not declared\n", operand);
    exit(1);
  }

  if (operandType == TYPE_CHAR || isCharVar((char *)operand)) {
    fprintf(output, "    lb $t%d, %d($sp)\n", reg, offset);
  } else {
    fprintf(output, "    lw $t%d, %d($sp)\n", reg, offset);
  }
  return reg;
}

static int loadRawFloatValue(const char *operand) {
  int freg = getNextFloatTemp();
  if (!operand) {
    fprintf(output, "    li.s $f%d, 0.0\n", freg);
    return freg;
  }

  if (isLiteral(operand)) {
    const char *value = operand;
    if (!isFloatLiteral(operand)) {
      /* Treat integer literal as float */
      static char buffer[64];
      snprintf(buffer, sizeof(buffer), "%s.0", operand);
      value = buffer;
    }
    fprintf(output, "    li.s $f%d, %s\n", freg, value);
    return freg;
  }

  int offset = getVarOffset((char *)operand);
  if (offset == -1) {
    fprintf(stderr, "Error: Variable %s not declared\n", operand);
    exit(1);
  }

  fprintf(output, "    lwc1 $f%d, %d($sp)\n", freg, offset);
  return freg;
}

static int materializeFloat(const char *operand, DataType operandType) {
  if (operandType == TYPE_FLOAT)
    return loadRawFloatValue(operand);

  int intReg = loadRawIntValue(operand, operandType);
  int freg = getNextFloatTemp();
  fprintf(output, "    mtc1 $t%d, $f%d\n", intReg, freg);
  fprintf(output, "    cvt.s.w $f%d, $f%d\n", freg, freg);
  return freg;
}

static int materializeInt(const char *operand, DataType operandType) {
  if (operandType == TYPE_FLOAT) {
    int freg = materializeFloat(operand, operandType);
    int reg = getNextTemp();
    fprintf(output, "    cvt.w.s $f%d, $f%d\n", freg, freg);
    fprintf(output, "    mfc1 $t%d, $f%d\n", reg, freg);
    return reg;
  }
  return loadRawIntValue(operand, operandType);
}

static int materializeBoolean(const char *operand, DataType operandType) {
  if (operandType == TYPE_FLOAT) {
    int freg = materializeFloat(operand, operandType);
    int zeroFReg = getNextFloatTemp();
    fprintf(output, "    li.s $f%d, 0.0\n", zeroFReg);
    int destReg = getNextTemp();
    int labelId = compareLabelCounter++;
    fprintf(output, "    c.eq.s $f%d, $f%d\n", freg, zeroFReg);
    fprintf(output, "    bc1t __bool_zero_%d\n", labelId);
    fprintf(output, "    li $t%d, 1\n", destReg);
    fprintf(output, "    j __bool_end_%d\n", labelId);
    fprintf(output, "__bool_zero_%d:\n", labelId);
    fprintf(output, "    li $t%d, 0\n", destReg);
    fprintf(output, "__bool_end_%d:\n", labelId);
    return destReg;
  }

  int valueReg = materializeInt(operand, operandType);
  int boolReg = getNextTemp();
  fprintf(output, "    sltu $t%d, $zero, $t%d\n", boolReg, valueReg);
  return boolReg;
}

static void storeValue(const char *dest, DataType type, int reg, int isFloat) {
  if (!dest || isLiteral(dest))
    return;

  int offset = getVarOffset((char *)dest);
  if (offset == -1) {
    fprintf(stderr, "Error: Destination %s not declared\n", dest);
    exit(1);
  }

  if (type == TYPE_FLOAT || isFloat) {
    fprintf(output, "    swc1 $f%d, %d($sp)\n", reg, offset);
  } else if (type == TYPE_CHAR || isCharVar((char *)dest)) {
    fprintf(output, "    sb $t%d, %d($sp)\n", reg, offset);
  } else {
    fprintf(output, "    sw $t%d, %d($sp)\n", reg, offset);
  }
}

static const char *formatFunctionLabel(const char *name, char *buffer,
                                        size_t size) {
  if (!name || strcmp(name, "main") == 0) {
    snprintf(buffer, size, "main");
  } else {
    snprintf(buffer, size, "fn_%s", name);
  }
  return buffer;
}

static FunctionInfo *lookupFunctionInfo(const char *name) {
  const char *key = name ? name : "main";
  for (int i = 0; i < functionCount; ++i) {
    if (strcmp(functionTable[i].name, key) == 0)
      return &functionTable[i];
  }
  return NULL;
}

static FunctionInfo *registerFunctionInfo(const char *name, DataType returnType,
                                          ASTNode *params) {
  const char *key = name ? name : "main";
  FunctionInfo *info = lookupFunctionInfo(key);
  if (info) {
    info->returnType = returnType;
    if (params)
      info->params = params;
    return info;
  }

  if (functionCount >= (int)(sizeof(functionTable) / sizeof(functionTable[0]))) {
    fprintf(stderr, "Error: Too many functions declared\n");
    exit(1);
  }

  FunctionInfo *slot = &functionTable[functionCount++];
  strncpy(slot->name, key, sizeof(slot->name) - 1);
  slot->name[sizeof(slot->name) - 1] = '\0';
  slot->returnType = returnType;
  slot->params = params;
  return slot;
}

static void collectFunctionInfo(ASTNode *node) {
  if (!node)
    return;

  switch (node->type) {
  case NODE_FUNC_DECL:
    registerFunctionInfo(node->data.func_decl.name,
                         node->data.func_decl.returnType,
                         node->data.func_decl.params);
    collectFunctionInfo(node->data.func_decl.body);
    break;
  case NODE_FUNC_LIST:
    collectFunctionInfo(node->data.list.item);
    collectFunctionInfo(node->data.list.next);
    break;
  case NODE_STMT_LIST:
    collectFunctionInfo(node->data.stmtlist.stmt);
    collectFunctionInfo(node->data.stmtlist.next);
    break;
  default:
    break;
  }
}

static void processParameterSequence(ASTNode *params, int *paramIndex) {
  if (!params)
    return;

  switch (params->type) {
  case NODE_PARAM: {
    DataType pType = params->data.param.type;
    int offset = -1;
    int storeAsPointer = 0;

    if (params->data.param.isStruct) {
      offset = addStructParam(params->data.param.name,
                              params->data.param.structType);
      storeAsPointer = 1;
    } else if (params->data.param.isArray) {
      offset = addArrayParam(params->data.param.name,
                             params->data.param.arraySize, pType);
      storeAsPointer = 1;
    } else if (pType == TYPE_CHAR) {
      offset = addCharVar(params->data.param.name);
    } else if (pType == TYPE_FLOAT) {
      offset = addFloatVar(params->data.param.name);
    } else {
      offset = addVar(params->data.param.name);
    }
    if (offset == -1) {
      fprintf(stderr, "Error: Parameter %s already declared\n",
              params->data.param.name);
      exit(1);
    } else if (offset == -2) {
      fprintf(stderr,
              "Error: Parameter %s uses undefined struct type %s\n",
              params->data.param.name, params->data.param.structType);
      exit(1);
    }

    if (*paramIndex < 4) {
      if (storeAsPointer) {
        fprintf(output, "    sw $a%d, %d($sp)\n", *paramIndex, offset);
      } else if (pType == TYPE_CHAR) {
        fprintf(output, "    sb $a%d, %d($sp)\n", *paramIndex, offset);
      } else if (pType == TYPE_FLOAT) {
        fprintf(output, "    sw $a%d, %d($sp)\n", *paramIndex, offset);
      } else {
        fprintf(output, "    sw $a%d, %d($sp)\n", *paramIndex, offset);
      }
    } else {
      fprintf(stderr,
              "Error: Code generation currently supports up to 4 parameters per "
              "function\n");
      exit(1);
    }

    (*paramIndex)++;
    break;
  }
  case NODE_PARAM_LIST:
  case NODE_ARG_LIST:
    processParameterSequence(params->data.list.item, paramIndex);
    processParameterSequence(params->data.list.next, paramIndex);
    break;
  default:
    break;
  }
}

static void beginFunction(const char *name) {
  if (inFunction)
    finishFunction();

  currentFunction = lookupFunctionInfo(name);
  if (!currentFunction)
    currentFunction = registerFunctionInfo(name, TYPE_INT, NULL);

  char label[128];
  formatFunctionLabel(currentFunction->name, label, sizeof(label));
  snprintf(currentReturnLabel, sizeof(currentReturnLabel), "__return_%s",
           label);

  enterScope();
  symtab.count = 0;
  symtab.nextOffset = 0;
  resetTempRegs();
  currentParamIndex = 0;
  inFunction = 1;

  fprintf(output, "%s:\n", label);
  fprintf(output, "    addi $sp, $sp, -%d\n", LOCAL_STACK_SIZE);
  if (strcmp(currentFunction->name, "main") != 0) {
    fprintf(output, "    sw $ra, %d($sp)\n", RA_SAVE_OFFSET);
  }

  if (currentFunction->params) {
    int paramIndex = 0;
    processParameterSequence(currentFunction->params, &paramIndex);
    fprintf(output, "\n");
  }
}

static void ensureFunctionContext(void) {
  if (!inFunction) {
    beginFunction("main");
  }
}

static void finishFunction(void) {
  if (!inFunction)
    return;

  fprintf(output, "%s:\n", currentReturnLabel);
  if (strcmp(currentFunction->name, "main") != 0) {
    fprintf(output, "    lw $ra, %d($sp)\n", RA_SAVE_OFFSET);
  }
  fprintf(output, "    addi $sp, $sp, %d\n", LOCAL_STACK_SIZE);
  if (strcmp(currentFunction->name, "main") == 0) {
    fprintf(output, "    li $v0, 10\n");
    fprintf(output, "    syscall\n");
  } else {
    fprintf(output, "    jr $ra\n");
  }
  fprintf(output, "\n");
  resetTempRegs();
  exitScope();
  currentFunction = NULL;
  currentParamIndex = 0;
  inFunction = 0;
}

static void emitBinaryOp(TACInstr *instr) {
  switch (instr->op) {
  case TAC_LT:
  case TAC_LE:
  case TAC_GT:
  case TAC_GE:
  case TAC_EQ:
  case TAC_NE:
    emitComparison(instr);
    return;
  case TAC_AND:
  case TAC_OR:
    emitLogical(instr);
    return;
  default:
    break;
  }

  ensureFunctionContext();
  ensureStorage(instr->result, instr->resultType);

  if (instr->resultType == TYPE_FLOAT) {
    int leftReg = materializeFloat(instr->arg1, instr->arg1Type);
    int rightReg = materializeFloat(instr->arg2, instr->arg2Type);

    switch (instr->op) {
    case TAC_ADD:
      fprintf(output, "    add.s $f%d, $f%d, $f%d\n", leftReg, leftReg,
              rightReg);
      break;
    case TAC_SUB:
      fprintf(output, "    sub.s $f%d, $f%d, $f%d\n", leftReg, leftReg,
              rightReg);
      break;
    case TAC_MUL:
      fprintf(output, "    mul.s $f%d, $f%d, $f%d\n", leftReg, leftReg,
              rightReg);
      break;
    case TAC_DIV:
      fprintf(output, "    div.s $f%d, $f%d, $f%d\n", leftReg, leftReg,
              rightReg);
      break;
    default:
      break;
    }

    storeValue(instr->result, instr->resultType, leftReg, 1);
  } else {
    int leftReg = materializeInt(instr->arg1, instr->arg1Type);
    int rightReg = materializeInt(instr->arg2, instr->arg2Type);

    switch (instr->op) {
    case TAC_ADD:
      fprintf(output, "    add $t%d, $t%d, $t%d\n", leftReg, leftReg,
              rightReg);
      break;
    case TAC_SUB:
      fprintf(output, "    sub $t%d, $t%d, $t%d\n", leftReg, leftReg,
              rightReg);
      break;
    case TAC_MUL:
      fprintf(output, "    mul $t%d, $t%d, $t%d\n", leftReg, leftReg,
              rightReg);
      break;
    case TAC_DIV:
      fprintf(output, "    div $t%d, $t%d\n", leftReg, rightReg);
      fprintf(output, "    mflo $t%d\n", leftReg);
      break;
    default:
      break;
    }

    storeValue(instr->result, instr->resultType, leftReg, 0);
  }

  resetTempRegs();
}

static void emitComparison(TACInstr *instr) {
  ensureFunctionContext();
  ensureStorage(instr->result, instr->resultType);

  if (instr->arg1Type == TYPE_FLOAT || instr->arg2Type == TYPE_FLOAT) {
    int leftReg = materializeFloat(instr->arg1, instr->arg1Type);
    int rightReg = materializeFloat(instr->arg2, instr->arg2Type);
    int destReg = getNextTemp();
    int labelId = compareLabelCounter++;
    const char *cmpInstr = NULL;
    const char *branchInstr = "bc1t";
    int cmpLeft = leftReg;
    int cmpRight = rightReg;

    switch (instr->op) {
    case TAC_LT:
      cmpInstr = "c.lt.s";
      break;
    case TAC_LE:
      cmpInstr = "c.le.s";
      break;
    case TAC_GT:
      cmpInstr = "c.lt.s";
      cmpLeft = rightReg;
      cmpRight = leftReg;
      break;
    case TAC_GE:
      cmpInstr = "c.le.s";
      cmpLeft = rightReg;
      cmpRight = leftReg;
      break;
    case TAC_EQ:
      cmpInstr = "c.eq.s";
      break;
    case TAC_NE:
      cmpInstr = "c.eq.s";
      branchInstr = "bc1f";
      break;
    default:
      cmpInstr = "c.eq.s";
      break;
    }

    fprintf(output, "    %s $f%d, $f%d\n", cmpInstr, cmpLeft, cmpRight);
    fprintf(output, "    %s __cmp_true_%d\n", branchInstr, labelId);
    fprintf(output, "    li $t%d, 0\n", destReg);
    fprintf(output, "    j __cmp_end_%d\n", labelId);
    fprintf(output, "__cmp_true_%d:\n", labelId);
    fprintf(output, "    li $t%d, 1\n", destReg);
    fprintf(output, "__cmp_end_%d:\n", labelId);
    storeValue(instr->result, instr->resultType, destReg, 0);
    resetTempRegs();
    return;
  }

  int leftReg = materializeInt(instr->arg1, instr->arg1Type);
  int rightReg = materializeInt(instr->arg2, instr->arg2Type);
  int destReg = getNextTemp();

  switch (instr->op) {
  case TAC_LT:
    fprintf(output, "    slt $t%d, $t%d, $t%d\n", destReg, leftReg, rightReg);
    break;
  case TAC_LE:
    fprintf(output, "    slt $t%d, $t%d, $t%d\n", destReg, rightReg, leftReg);
    fprintf(output, "    xori $t%d, $t%d, 1\n", destReg, destReg);
    break;
  case TAC_GT:
    fprintf(output, "    slt $t%d, $t%d, $t%d\n", destReg, rightReg, leftReg);
    break;
  case TAC_GE:
    fprintf(output, "    slt $t%d, $t%d, $t%d\n", destReg, leftReg, rightReg);
    fprintf(output, "    xori $t%d, $t%d, 1\n", destReg, destReg);
    break;
  case TAC_EQ: {
    int tmpReg = getNextTemp();
    fprintf(output, "    xor $t%d, $t%d, $t%d\n", tmpReg, leftReg, rightReg);
    fprintf(output, "    sltiu $t%d, $t%d, 1\n", destReg, tmpReg);
    break;
  }
  case TAC_NE:
    fprintf(output, "    xor $t%d, $t%d, $t%d\n", destReg, leftReg, rightReg);
    fprintf(output, "    sltu $t%d, $zero, $t%d\n", destReg, destReg);
    break;
  default:
    fprintf(output, "    slt $t%d, $t%d, $t%d\n", destReg, leftReg, rightReg);
    break;
  }

  storeValue(instr->result, instr->resultType, destReg, 0);
  resetTempRegs();
}

static void emitLogical(TACInstr *instr) {
  ensureFunctionContext();
  ensureStorage(instr->result, instr->resultType);

  int leftReg = materializeBoolean(instr->arg1, instr->arg1Type);
  int rightReg = materializeBoolean(instr->arg2, instr->arg2Type);
  int destReg = getNextTemp();

  if (instr->op == TAC_AND) {
    fprintf(output, "    and $t%d, $t%d, $t%d\n", destReg, leftReg, rightReg);
  } else {
    fprintf(output, "    or $t%d, $t%d, $t%d\n", destReg, leftReg, rightReg);
  }

  fprintf(output, "    sltu $t%d, $zero, $t%d\n", destReg, destReg);
  storeValue(instr->result, instr->resultType, destReg, 0);
  resetTempRegs();
}

static void emitNotInstr(TACInstr *instr) {
  ensureFunctionContext();
  ensureStorage(instr->result, instr->resultType);

  int valueReg = materializeBoolean(instr->arg1, instr->arg1Type);
  int destReg = getNextTemp();
  fprintf(output, "    xori $t%d, $t%d, 1\n", destReg, valueReg);
  storeValue(instr->result, instr->resultType, destReg, 0);
  resetTempRegs();
}

static void emitAssign(TACInstr *instr) {
  ensureFunctionContext();
  ensureStorage(instr->result, instr->resultType);

  if (instr->resultType == TYPE_FLOAT) {
    int freg = materializeFloat(instr->arg1, instr->arg1Type);
    storeValue(instr->result, instr->resultType, freg, 1);
  } else {
    int reg = materializeInt(instr->arg1, instr->arg1Type);
    storeValue(instr->result, instr->resultType, reg, 0);
  }

  resetTempRegs();
}

static void emitPrint(TACInstr *instr) {
  ensureFunctionContext();

  if (instr->arg1Type == TYPE_FLOAT) {
    int freg = materializeFloat(instr->arg1, instr->arg1Type);
    fprintf(output, "    mov.s $f12, $f%d\n", freg);
    fprintf(output, "    li $v0, 2\n");
    fprintf(output, "    syscall\n");
  } else if (instr->arg1Type == TYPE_CHAR) {
    int reg = materializeInt(instr->arg1, instr->arg1Type);
    fprintf(output, "    li $v0, 11\n");
    fprintf(output, "    move $a0, $t%d\n", reg);
    fprintf(output, "    syscall\n");
  } else {
    int reg = materializeInt(instr->arg1, instr->arg1Type);
    fprintf(output, "    move $a0, $t%d\n", reg);
    fprintf(output, "    li $v0, 1\n");
    fprintf(output, "    syscall\n");
  }

  fprintf(output, "    li $v0, 11\n");
  fprintf(output, "    li $a0, 10\n");
  fprintf(output, "    syscall\n");

  resetTempRegs();
}

static void handleDecl(TACInstr *instr) {
  ensureFunctionContext();
  DataType declType = instr->resultType;
  if (instr->arg1)
    declType = parseTypeString(instr->arg1);
  ensureStorage(instr->result, declType);
}

static void handleArrayDecl(TACInstr *instr) {
  ensureFunctionContext();
  DataType elemType = instr->resultType;
  if (instr->arg1)
    elemType = parseTypeString(instr->arg1);
  int size = instr->arg2 ? atoi(instr->arg2) : 0;
  int offset = -1;
  if (elemType == TYPE_CHAR) {
    offset = addCharArrayVar(instr->result, size);
  } else if (elemType == TYPE_FLOAT) {
    offset = addFloatArrayVar(instr->result, size);
  } else if (elemType == TYPE_BOOL) {
    offset = addBoolArrayVar(instr->result, size);
  } else {
    offset = addArrayVar(instr->result, size);
  }
  if (offset < 0) {
    fprintf(stderr, "Error: Failed to declare array %s\n", instr->result);
    exit(1);
  }
  fprintf(output, "    # Declared array %s[%d]\n", instr->result, size);
}

static void handleStructDecl(TACInstr *instr) {
  if (addStructType(instr->result) == -1) {
    fprintf(stderr, "Error: Struct %s already defined\n", instr->result);
    exit(1);
  }
  fprintf(output, "    # Struct %s defined\n", instr->result);
}

static void handleStructField(TACInstr *instr) {
  DataType fieldType = parseTypeString(instr->arg2);
  if (addStructField(instr->result, instr->arg1, fieldType) == -1) {
    fprintf(stderr, "Error: Struct field %s.%s redeclared\n", instr->result,
            instr->arg1);
    exit(1);
  }
}

static void handleStructVarDecl(TACInstr *instr) {
  ensureFunctionContext();
  int offset = addStructVar(instr->result, instr->arg1);
  if (offset < 0) {
    fprintf(stderr, "Error: Failed to declare struct var %s\n", instr->result);
    exit(1);
  }
  fprintf(output, "    # Declared struct %s %s\n", instr->arg1, instr->result);
}

static void emitArrayBoundsCheck(const char *arrayName, int indexReg) {
  if (!arrayName)
    return;

  int arraySize = getArraySize((char *)arrayName);
  if (arraySize <= 0)
    return;

  int limitReg = getNextTemp();
  int labelId = boundsCheckLabelCounter++;

  fprintf(output, "    # Bounds check for array %s\n", arrayName);
  fprintf(output, "    bltz $t%d, __bounds_error_%d\n", indexReg, labelId);
  fprintf(output, "    li $t%d, %d\n", limitReg, arraySize);
  fprintf(output, "    bge $t%d, $t%d, __bounds_error_%d\n", indexReg, limitReg,
          labelId);
  fprintf(output, "    j __bounds_ok_%d\n", labelId);
  fprintf(output, "__bounds_error_%d:\n", labelId);
  fprintf(output, "    li $v0, 4\n");
  fprintf(output, "    la $a0, __array_oob_msg\n");
  fprintf(output, "    syscall\n");
  fprintf(output, "    li $v0, 10\n");
  fprintf(output, "    syscall\n");
  fprintf(output, "__bounds_ok_%d:\n", labelId);
}

static void emitArrayAssign(TACInstr *instr) {
  ensureFunctionContext();
  int indexReg = materializeInt(instr->arg1, instr->arg1Type);
  emitArrayBoundsCheck(instr->result, indexReg);
  DataType elemType = instr->resultType;
  DataType valueType = instr->arg2Type;
  int baseOffset = getVarOffset(instr->result);
  if (baseOffset == -1) {
    fprintf(stderr, "Error: Array %s not declared\n", instr->result);
    exit(1);
  }

  int pointerBased = isPointerVar(instr->result);
  int addrReg = getNextTemp();
  if (pointerBased) {
    fprintf(output, "    lw $t%d, %d($sp)\n", addrReg, baseOffset);
  } else {
    fprintf(output, "    addi $t%d, $sp, %d\n", addrReg, baseOffset);
  }

  if (elemType == TYPE_CHAR) {
    fprintf(output, "    add $t%d, $t%d, $t%d\n", addrReg, addrReg, indexReg);
    int valueReg = materializeInt(instr->arg2, valueType);
    fprintf(output, "    sb $t%d, 0($t%d)\n", valueReg, addrReg);
  } else {
    fprintf(output, "    sll $t%d, $t%d, 2\n", indexReg, indexReg);
    fprintf(output, "    add $t%d, $t%d, $t%d\n", addrReg, addrReg, indexReg);
    if (elemType == TYPE_FLOAT) {
      int freg = materializeFloat(instr->arg2, valueType);
      fprintf(output, "    swc1 $f%d, 0($t%d)\n", freg, addrReg);
    } else {
      int valueReg = materializeInt(instr->arg2, valueType);
      fprintf(output, "    sw $t%d, 0($t%d)\n", valueReg, addrReg);
    }
  }

  resetTempRegs();
}

static void emitArrayAccess(TACInstr *instr) {
  ensureFunctionContext();
  ensureStorage(instr->result, instr->resultType);

  int indexReg = materializeInt(instr->arg1, instr->arg1Type);
  emitArrayBoundsCheck(instr->arg2, indexReg);
  int baseOffset = getVarOffset(instr->arg2);
  if (baseOffset == -1) {
    fprintf(stderr, "Error: Array %s not declared\n", instr->arg2);
    exit(1);
  }

  int pointerBased = isPointerVar(instr->arg2);
  int addrReg = getNextTemp();
  if (pointerBased) {
    fprintf(output, "    lw $t%d, %d($sp)\n", addrReg, baseOffset);
  } else {
    fprintf(output, "    addi $t%d, $sp, %d\n", addrReg, baseOffset);
  }

  if (instr->resultType == TYPE_CHAR) {
    fprintf(output, "    add $t%d, $t%d, $t%d\n", addrReg, addrReg, indexReg);
    fprintf(output, "    lb $t%d, 0($t%d)\n", addrReg, addrReg);
    storeValue(instr->result, instr->resultType, addrReg, 0);
  } else {
    fprintf(output, "    sll $t%d, $t%d, 2\n", indexReg, indexReg);
    fprintf(output, "    add $t%d, $t%d, $t%d\n", addrReg, addrReg, indexReg);
    if (instr->resultType == TYPE_FLOAT) {
      int freg = getNextFloatTemp();
      fprintf(output, "    lwc1 $f%d, 0($t%d)\n", freg, addrReg);
      storeValue(instr->result, instr->resultType, freg, 1);
    } else {
      fprintf(output, "    lw $t%d, 0($t%d)\n", addrReg, addrReg);
      storeValue(instr->result, instr->resultType, addrReg, 0);
    }
  }

  resetTempRegs();
}

static void emitStructAssign(TACInstr *instr) {
  ensureFunctionContext();
  const char *structType = getStructTypeName(instr->result);
  if (!structType) {
    fprintf(stderr, "Error: %s is not a struct variable\n", instr->result);
    exit(1);
  }
  int baseOffset = getVarOffset((char *)instr->result);
  int fieldOffset = getStructFieldOffset(structType, instr->arg2);
  DataType fieldType = getStructFieldType(structType, instr->arg2);

  if (fieldOffset < 0) {
    fprintf(stderr, "Error: Field %s not found on struct %s\n", instr->arg2,
            structType);
    exit(1);
  }

  if (isPointerVar(instr->result)) {
    int baseReg = getNextTemp();
    fprintf(output, "    lw $t%d, %d($sp)\n", baseReg, baseOffset);
    fprintf(output, "    addi $t%d, $t%d, %d\n", baseReg, baseReg, fieldOffset);
    if (fieldType == TYPE_FLOAT) {
      int freg = materializeFloat(instr->arg1, instr->arg1Type);
      fprintf(output, "    swc1 $f%d, 0($t%d)\n", freg, baseReg);
    } else {
      int reg = materializeInt(instr->arg1, instr->arg1Type);
      if (fieldType == TYPE_CHAR) {
        fprintf(output, "    sb $t%d, 0($t%d)\n", reg, baseReg);
      } else {
        fprintf(output, "    sw $t%d, 0($t%d)\n", reg, baseReg);
      }
    }
  } else {
    int totalOffset = baseOffset + fieldOffset;
    if (fieldType == TYPE_FLOAT) {
      int freg = materializeFloat(instr->arg1, instr->arg1Type);
      fprintf(output, "    swc1 $f%d, %d($sp)\n", freg, totalOffset);
    } else {
      int reg = materializeInt(instr->arg1, instr->arg1Type);
      if (fieldType == TYPE_CHAR) {
        fprintf(output, "    sb $t%d, %d($sp)\n", reg, totalOffset);
      } else {
        fprintf(output, "    sw $t%d, %d($sp)\n", reg, totalOffset);
      }
    }
  }

  resetTempRegs();
}

static void emitStructAccess(TACInstr *instr) {
  ensureFunctionContext();
  ensureStorage(instr->result, instr->resultType);

  const char *structType = getStructTypeName(instr->arg1);
  if (!structType) {
    fprintf(stderr, "Error: %s is not a struct variable\n", instr->arg1);
    exit(1);
  }

  int baseOffset = getVarOffset((char *)instr->arg1);
  int fieldOffset = getStructFieldOffset(structType, instr->arg2);
  DataType fieldType = getStructFieldType(structType, instr->arg2);

  if (fieldOffset < 0) {
    fprintf(stderr, "Error: Field %s not found on struct %s\n", instr->arg2,
            structType);
    exit(1);
  }

  if (isPointerVar(instr->arg1)) {
    int baseReg = getNextTemp();
    fprintf(output, "    lw $t%d, %d($sp)\n", baseReg, baseOffset);
    fprintf(output, "    addi $t%d, $t%d, %d\n", baseReg, baseReg, fieldOffset);
    if (fieldType == TYPE_FLOAT) {
      int freg = getNextFloatTemp();
      fprintf(output, "    lwc1 $f%d, 0($t%d)\n", freg, baseReg);
      storeValue(instr->result, instr->resultType, freg, 1);
    } else {
      int reg = getNextTemp();
      if (fieldType == TYPE_CHAR) {
        fprintf(output, "    lb $t%d, 0($t%d)\n", reg, baseReg);
      } else {
        fprintf(output, "    lw $t%d, 0($t%d)\n", reg, baseReg);
      }
      storeValue(instr->result, instr->resultType, reg, 0);
    }
  } else {
    int totalOffset = baseOffset + fieldOffset;
    if (fieldType == TYPE_FLOAT) {
      int freg = getNextFloatTemp();
      fprintf(output, "    lwc1 $f%d, %d($sp)\n", freg, totalOffset);
      storeValue(instr->result, instr->resultType, freg, 1);
    } else {
      int reg = getNextTemp();
      if (fieldType == TYPE_CHAR) {
        fprintf(output, "    lb $t%d, %d($sp)\n", reg, totalOffset);
      } else {
        fprintf(output, "    lw $t%d, %d($sp)\n", reg, totalOffset);
      }
      storeValue(instr->result, instr->resultType, reg, 0);
    }
  }

  resetTempRegs();
}

static void emitParam(TACInstr *instr) {
  ensureFunctionContext();
  if (currentParamIndex >= 4) {
    fprintf(stderr,
            "Error: Code generation currently supports up to 4 arguments per "
            "call\n");
    exit(1);
  }

  const char *argName = instr->arg1;
  if (argName && !isLiteral(argName) && isPointerVar(argName)) {
    int offset = getVarOffset((char *)argName);
    if (offset == -1) {
      fprintf(stderr, "Error: Pointer argument %s not declared\n", argName);
      exit(1);
    }
    int reg = getNextTemp();
    fprintf(output, "    lw $t%d, %d($sp)\n", reg, offset);
    fprintf(output, "    move $a%d, $t%d\n", currentParamIndex, reg);
  } else if (argName && !isLiteral(argName) && isStructVar(argName)) {
    int offset = getVarOffset((char *)argName);
    if (offset == -1) {
      fprintf(stderr, "Error: Struct argument %s not declared\n", argName);
      exit(1);
    }
    int reg = getNextTemp();
    fprintf(output, "    addi $t%d, $sp, %d\n", reg, offset);
    fprintf(output, "    move $a%d, $t%d\n", currentParamIndex, reg);
  } else if (argName && !isLiteral(argName) && isArrayVar((char *)argName)) {
    int offset = getVarOffset((char *)argName);
    if (offset == -1) {
      fprintf(stderr, "Error: Array argument %s not declared\n", argName);
      exit(1);
    }
    int reg = getNextTemp();
    fprintf(output, "    addi $t%d, $sp, %d\n", reg, offset);
    fprintf(output, "    move $a%d, $t%d\n", currentParamIndex, reg);
  } else if (instr->arg1Type == TYPE_FLOAT) {
    int freg = materializeFloat(instr->arg1, instr->arg1Type);
    int reg = getNextTemp();
    fprintf(output, "    mfc1 $t%d, $f%d\n", reg, freg);
    fprintf(output, "    move $a%d, $t%d\n", currentParamIndex, reg);
  } else {
    int reg = materializeInt(instr->arg1, instr->arg1Type);
    fprintf(output, "    move $a%d, $t%d\n", currentParamIndex, reg);
  }

  currentParamIndex++;
  resetTempRegs();
}

static void emitCall(TACInstr *instr) {
  ensureFunctionContext();
  char label[128];
  if (instr->arg1) {
    if (strcmp(instr->arg1, "input") == 0)
      needsInputStub = 1;
    else if (strcmp(instr->arg1, "output") == 0)
      needsOutputStub = 1;
  }
  formatFunctionLabel(instr->arg1, label, sizeof(label));
  fprintf(output, "    jal %s\n", label);

  if (instr->result) {
    ensureStorage(instr->result, instr->resultType);
    int offset = getVarOffset(instr->result);
    if (offset == -1) {
      fprintf(stderr, "Error: Failed to locate storage for call result %s\n",
              instr->result);
      exit(1);
    }

    if (instr->resultType == TYPE_FLOAT) {
      fprintf(output, "    swc1 $f0, %d($sp)\n", offset);
    } else if (instr->resultType == TYPE_CHAR) {
      fprintf(output, "    sb $v0, %d($sp)\n", offset);
    } else {
      fprintf(output, "    sw $v0, %d($sp)\n", offset);
    }
  }

  currentParamIndex = 0;
  resetTempRegs();
}

static void emitReturn(TACInstr *instr) {
  ensureFunctionContext();
  DataType retType = currentFunction ? currentFunction->returnType : TYPE_INT;

  if (instr->arg1) {
    if (retType == TYPE_FLOAT) {
      int freg = materializeFloat(instr->arg1, instr->arg1Type);
      fprintf(output, "    mov.s $f0, $f%d\n", freg);
      fprintf(output, "    mfc1 $v0, $f%d\n", freg);
    } else {
      int reg = materializeInt(instr->arg1, instr->arg1Type);
      fprintf(output, "    move $v0, $t%d\n", reg);
    }
  } else {
    fprintf(output, "    move $v0, $zero\n");
  }

  fprintf(output, "    j %s\n", currentReturnLabel);
  resetTempRegs();
}

static void emitGoto(TACInstr *instr) {
  ensureFunctionContext();
  if (instr->result)
    fprintf(output, "    j %s\n", instr->result);
}

static void emitConditionalBranch(TACInstr *instr) {
  ensureFunctionContext();
  int condReg = materializeBoolean(instr->arg1, instr->arg1Type);
  if (instr->op == TAC_IFZ) {
    fprintf(output, "    beq $t%d, $zero, %s\n", condReg, instr->result);
  } else {
    fprintf(output, "    bne $t%d, $zero, %s\n", condReg, instr->result);
  }
  resetTempRegs();
}

static void emitLabel(TACInstr *instr) {
  ensureFunctionContext();
  if (!instr->result)
    return;

  if (currentFunction && strcmp(instr->result, currentFunction->name) == 0)
    return;

  fprintf(output, "%s:\n", instr->result);
}

static int countFunctionParams(ASTNode *params) {
  if (!params)
    return 0;

  switch (params->type) {
  case NODE_PARAM:
    return 1;
  case NODE_PARAM_LIST:
    return countFunctionParams(params->data.list.item) +
           countFunctionParams(params->data.list.next);
  default:
    return 0;
  }
}

static void printFunctionParams(ASTNode *params, int indent) {
  if (!params)
    return;

  switch (params->type) {
  case NODE_PARAM:
    printf("%*s- %s %s\n", indent, "",
           dataTypeToString(params->data.param.type),
           params->data.param.name);
    break;
  case NODE_PARAM_LIST:
    printFunctionParams(params->data.list.item, indent);
    printFunctionParams(params->data.list.next, indent);
    break;
  default:
    break;
  }
}

static void printFunctionTable(void) {
  printf("\n=== FUNCTION TABLE STATE ===\n");
  printf("Count: %d\n", functionCount);
  if (functionCount == 0) {
    printf("(empty)\n");
  } else {
    for (int i = 0; i < functionCount; ++i) {
      FunctionInfo *info = &functionTable[i];
      int paramCount = countFunctionParams(info->params);
      printf(" [%d] %s -> return %s (params: %d)\n", i, info->name,
             dataTypeToString(info->returnType), paramCount);
      if (paramCount == 0) {
        printf("      (none)\n");
      } else {
        printFunctionParams(info->params, 8);
      }
    }
  }
  printf("===========================\n\n");
}

void generateMIPS(ASTNode *root, const char *filename) {
  output = fopen(filename, "w");
  if (!output) {
    fprintf(stderr, "Cannot open output file %s\n", filename);
    exit(1);
  }

  initSymTab();
  functionCount = 0;
  boundsCheckLabelCounter = 0;
  needsInputStub = 0;
  needsOutputStub = 0;
  collectFunctionInfo(root);
  if (lookupFunctionInfo("main") == NULL)
    registerFunctionInfo("main", TYPE_INT, NULL);

  printf("┌──────────────────────────────────────────────────────────┐\n");
  printf("│ FUNCTION TABLE (CODE GENERATION)                        │\n");
  printf("├──────────────────────────────────────────────────────────┤\n");
  printf("│ Functions prepared for stack frame allocation           │\n");
  printf("└──────────────────────────────────────────────────────────┘\n");
  printFunctionTable();

  fprintf(output, ".data\n\n");
  fprintf(output, "__array_oob_msg: .asciiz \"Runtime error: array index out of bounds\\n\"\n\n");
  fprintf(output, ".text\n");
  fprintf(output, ".globl main\n\n");

  TACList *optList = getOptimizedTACList();
  TACInstr *instr = optList ? optList->head : NULL;

  while (instr) {
    switch (instr->op) {
    case TAC_FUNC_BEGIN:
      beginFunction(instr->result);
      break;
    case TAC_FUNC_END:
      finishFunction();
      break;
    case TAC_LABEL:
      emitLabel(instr);
      break;
    case TAC_DECL:
      handleDecl(instr);
      break;
    case TAC_ASSIGN:
      emitAssign(instr);
      break;
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
      emitBinaryOp(instr);
      break;
    case TAC_NOT:
      emitNotInstr(instr);
      break;
    case TAC_PRINT:
      emitPrint(instr);
      break;
    case TAC_ARRAY_DECL:
      handleArrayDecl(instr);
      break;
    case TAC_ARRAY_ASSIGN:
      emitArrayAssign(instr);
      break;
    case TAC_ARRAY_ACCESS:
      emitArrayAccess(instr);
      break;
    case TAC_STRUCT_DECL:
      handleStructDecl(instr);
      break;
    case TAC_STRUCT_FIELD:
      handleStructField(instr);
      break;
    case TAC_STRUCT_VAR_DECL:
      handleStructVarDecl(instr);
      break;
    case TAC_STRUCT_ASSIGN:
      emitStructAssign(instr);
      break;
    case TAC_STRUCT_ACCESS:
      emitStructAccess(instr);
      break;
    case TAC_PARAM:
      emitParam(instr);
      break;
    case TAC_CALL:
      emitCall(instr);
      break;
    case TAC_RETURN:
      emitReturn(instr);
      break;
    case TAC_GOTO:
      emitGoto(instr);
      break;
    case TAC_IFZ:
    case TAC_IFNZ:
      emitConditionalBranch(instr);
      break;
    default:
      break;
    }
    instr = instr->next;
  }

  if (needsInputStub) {
    fprintf(output, "\nfn_input:\n");
    fprintf(output, "    li $v0, 5\n");
    fprintf(output, "    syscall\n");
    fprintf(output, "    jr $ra\n");
  }

  if (needsOutputStub) {
    fprintf(output, "\nfn_output:\n");
    fprintf(output, "    li $v0, 1\n");
    fprintf(output, "    syscall\n");
    fprintf(output, "    li $v0, 11\n");
    fprintf(output, "    li $a0, 10\n");
    fprintf(output, "    syscall\n");
    fprintf(output, "    jr $ra\n");
  }

  finishFunction();
  fclose(output);
}
