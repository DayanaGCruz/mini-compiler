#include "codegen.h"
#include "symtab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOCAL_STACK_SIZE 400
#define RA_SAVE_OFFSET LOCAL_STACK_SIZE

static FILE *output = NULL;
static int tempReg = 0;
static char currentReturnLabel[128];

static int getNextTemp(void);
static void resetTempRegs(void);
static void genStmt(ASTNode *node);
static int genExpr(ASTNode *node);
static void genFunctionList(ASTNode *node);
static void genFunctionDecl(ASTNode *funcDecl);
static void genFunctionBody(const char *name, ASTNode *params, ASTNode *body,
                            int isMainEntry);
static void processParameterSequence(ASTNode *params, int *paramIndex);
static void processArgumentSequence(ASTNode *args, int *argIndex);
static int paramIsChar(ASTNode *paramNode);
static int countParams(ASTNode *node);

static void formatFunctionLabel(const char *name, char *buffer, size_t size) {
  if (!name || strcmp(name, "main") == 0) {
    snprintf(buffer, size, "main");
  } else {
    snprintf(buffer, size, "fn_%s", name);
  }
}

static int getNextTemp(void) {
  int reg = tempReg++;
  if (tempReg > 7)
    tempReg = 0;
  return reg;
}

static void resetTempRegs(void) { tempReg = 0; }

static int paramIsChar(ASTNode *paramNode) {
  if (!paramNode || paramNode->type != NODE_PARAM)
    return 0;

  return paramNode->data.param.type == TYPE_CHAR;
}

static int countParams(ASTNode *node) {
  if (!node)
    return 0;

  switch (node->type) {
  case NODE_PARAM:
    return 1;
  case NODE_PARAM_LIST:
  case NODE_ARG_LIST:
    return countParams(node->data.list.item) + countParams(node->data.list.next);
  default:
    return 0;
  }
}

static void processParameterSequence(ASTNode *params, int *paramIndex) {
  if (!params)
    return;

  switch (params->type) {
  case NODE_PARAM: {
    int isChar = paramIsChar(params);
    int offset =
        isChar ? addCharVar(params->data.param.name) : addVar(params->data.param.name);
    if (offset == -1) {
      fprintf(stderr, "Error: Parameter %s already declared\n",
              params->data.param.name);
      exit(1);
    }

    if (*paramIndex < 4) {
      if (isChar) {
        fprintf(output, "    sb $a%d, %d($sp)\n", *paramIndex, offset);
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
    if (params->data.list.item)
      processParameterSequence(params->data.list.item, paramIndex);
    if (params->data.list.next)
      processParameterSequence(params->data.list.next, paramIndex);
    break;
  default:
    break;
  }
}

static void processArgumentSequence(ASTNode *args, int *argIndex) {
  if (!args)
    return;

  switch (args->type) {
  case NODE_ARG_LIST:
  case NODE_PARAM_LIST:
    if (args->data.list.item)
      processArgumentSequence(args->data.list.item, argIndex);
    if (args->data.list.next)
      processArgumentSequence(args->data.list.next, argIndex);
    break;

  default: {
    int reg = genExpr(args);
    if (*argIndex < 4) {
      fprintf(output, "    move $a%d, $t%d\n", *argIndex, reg);
    } else {
      fprintf(stderr,
              "Error: Code generation currently supports up to 4 arguments per "
              "call\n");
      exit(1);
    }
    (*argIndex)++;
    resetTempRegs();
    break;
  }
  }
}

static int genExpr(ASTNode *node) {
  if (!node)
    return -1;

  switch (node->type) {
  case NODE_NUM: {
    int reg = getNextTemp();
    fprintf(output, "    li $t%d, %d\n", reg, node->data.num);
    return reg;
  }

  case NODE_VAR: {
    int offset = getVarOffset(node->data.name);
    if (offset == -1) {
      fprintf(stderr, "Error: Variable %s not declared\n", node->data.name);
      exit(1);
    }

    int reg = getNextTemp();
    if (isCharVar(node->data.name)) {
      fprintf(output, "    lb $t%d, %d($sp)\n", reg, offset);
    } else {
      fprintf(output, "    lw $t%d, %d($sp)\n", reg, offset);
    }
    return reg;
  }

  case NODE_BINOP: {
    int leftReg = genExpr(node->data.binop.left);
    int rightReg = genExpr(node->data.binop.right);

    if (node->data.binop.op == '+') {
      fprintf(output, "    add $t%d, $t%d, $t%d\n", leftReg, leftReg, rightReg);
    } else if (node->data.binop.op == '-') {
      fprintf(output, "    sub $t%d, $t%d, $t%d\n", leftReg, leftReg, rightReg);
    } else {
      fprintf(stderr, "Error: Unsupported binary operator %c\n",
              node->data.binop.op);
      exit(1);
    }

    tempReg = leftReg + 1;
    if (tempReg > 7)
      tempReg = 0;
    return leftReg;
  }

  case NODE_ARRAY_ACCESS: {
    if (!isArrayVar(node->data.array_access.name)) {
      fprintf(stderr, "Error: %s is not an array\n",
              node->data.array_access.name);
      exit(1);
    }

    int indexReg = genExpr(node->data.array_access.index);
    int baseOffset = getVarOffset(node->data.array_access.name);
    if (baseOffset == -1) {
      fprintf(stderr, "Error: Array %s offset lookup failed\n",
              node->data.array_access.name);
      exit(1);
    }

    int addrReg = getNextTemp();
    fprintf(output, "    # Array access: %s[index]\n",
            node->data.array_access.name);
    if (isCharVar(node->data.array_access.name)) {
      fprintf(output, "    addi $t%d, $sp, %d\n", addrReg, baseOffset);
      fprintf(output, "    add $t%d, $t%d, $t%d\n", addrReg, addrReg, indexReg);
      fprintf(output, "    lb $t%d, 0($t%d)\n", addrReg, addrReg);
    } else {
      fprintf(output, "    sll $t%d, $t%d, 2\n", indexReg, indexReg);
      fprintf(output, "    addi $t%d, $sp, %d\n", addrReg, baseOffset);
      fprintf(output, "    add $t%d, $t%d, $t%d\n", addrReg, addrReg, indexReg);
      fprintf(output, "    lw $t%d, 0($t%d)\n", addrReg, addrReg);
    }

    tempReg = addrReg + 1;
    if (tempReg > 7)
      tempReg = 0;
    return addrReg;
  }

  case NODE_STRUCT_ACCESS: {
    if (!isStructVar(node->data.struct_access.varName)) {
      fprintf(stderr, "Error: %s is not a struct variable\n",
              node->data.struct_access.varName);
      exit(1);
    }

    const char *structType =
        getStructTypeName(node->data.struct_access.varName);
    if (!structType) {
      fprintf(stderr, "Error: Struct type for %s not found\n",
              node->data.struct_access.varName);
      exit(1);
    }

    int baseOffset = getVarOffset(node->data.struct_access.varName);
    int fieldOffset =
        getStructFieldOffset(structType, node->data.struct_access.fieldName);
    if (fieldOffset < 0) {
      fprintf(stderr, "Error: Field %s not found in struct %s\n",
              node->data.struct_access.fieldName, structType);
      exit(1);
    }

    DataType fieldType =
        getStructFieldType(structType, node->data.struct_access.fieldName);
    int totalOffset = baseOffset + fieldOffset;
    int targetReg = getNextTemp();

    fprintf(output, "    # Struct access: %s.%s\n",
            node->data.struct_access.varName,
            node->data.struct_access.fieldName);
    if (fieldType == TYPE_CHAR) {
      fprintf(output, "    lb $t%d, %d($sp)\n", targetReg, totalOffset);
    } else {
      fprintf(output, "    lw $t%d, %d($sp)\n", targetReg, totalOffset);
    }
    return targetReg;
  }

  case NODE_FUNC_CALL: {
    int argIndex = 0;
    processArgumentSequence(node->data.func_call.args, &argIndex);
    char targetLabel[128];
    formatFunctionLabel(node->data.func_call.name, targetLabel,
                        sizeof(targetLabel));
    fprintf(output, "    jal %s\n", targetLabel);
    int destReg = getNextTemp();
    fprintf(output, "    move $t%d, $v0\n", destReg);

    tempReg = destReg + 1;
    if (tempReg > 7)
      tempReg = 0;
    return destReg;
  }

  default:
    return -1;
  }
}

static void genStmt(ASTNode *node) {
  if (!node)
    return;

  switch (node->type) {
  case NODE_DECL: {
    int offset = addVar(node->data.name);
    if (offset == -1) {
      fprintf(stderr, "Error: Variable %s already declared\n", node->data.name);
      exit(1);
    }
    fprintf(output, "    # Declared %s at offset %d\n", node->data.name,
            offset);
    break;
  }

  case NODE_CHAR_DECL: {
    int offset = addCharVar(node->data.name);
    if (offset == -1) {
      fprintf(stderr, "Error: Variable %s already declared\n", node->data.name);
      exit(1);
    }
    fprintf(output, "    # Declared %s at offset %d\n", node->data.name,
            offset);
    break;
  }

  case NODE_ASSIGN: {
    int offset = getVarOffset(node->data.assign.var);
    if (offset == -1) {
      fprintf(stderr, "Error: Variable %s not declared\n",
              node->data.assign.var);
      exit(1);
    }

    int valueReg = genExpr(node->data.assign.value);
    if (isCharVar(node->data.assign.var)) {
      fprintf(output, "    sb $t%d, %d($sp)\n", valueReg, offset);
    } else {
      fprintf(output, "    sw $t%d, %d($sp)\n", valueReg, offset);
    }
    resetTempRegs();
    break;
  }

  case NODE_PRINT: {
    int reg = genExpr(node->data.expr);

    int useChar = 0;
    ASTNode *e = node->data.expr;
    if ((e->type == NODE_VAR && isCharVar(e->data.name)) ||
        (e->type == NODE_ARRAY_ACCESS &&
         isCharVar(e->data.array_access.name))) {
      useChar = 1;
    } else if (e->type == NODE_STRUCT_ACCESS) {
      const char *structType = getStructTypeName(e->data.struct_access.varName);
      if (structType) {
        if (getStructFieldType(structType, e->data.struct_access.fieldName) ==
            TYPE_CHAR) {
          useChar = 1;
        }
      }
    }

    if (useChar) {
      fprintf(output, "    # Print character\n");
      fprintf(output, "    li $v0, 11\n");
      fprintf(output, "    move $a0, $t%d\n", reg);
      fprintf(output, "    syscall\n");
      fprintf(output, "    # Print newline\n");
      fprintf(output, "    li $v0, 11\n");
      fprintf(output, "    li $a0, 10\n");
      fprintf(output, "    syscall\n");
    } else {
      fprintf(output, "    # Print integer\n");
      fprintf(output, "    move $a0, $t%d\n", reg);
      fprintf(output, "    li $v0, 1\n");
      fprintf(output, "    syscall\n");
      fprintf(output, "    # Print newline\n");
      fprintf(output, "    li $v0, 11\n");
      fprintf(output, "    li $a0, 10\n");
      fprintf(output, "    syscall\n");
    }

    resetTempRegs();
    break;
  }

  case NODE_STMT_LIST:
    genStmt(node->data.stmtlist.stmt);
    genStmt(node->data.stmtlist.next);
    break;

  case NODE_ARRAY_DECL: {
    int offset = (node->data.array_decl.dataType == TYPE_CHAR)
                     ? addCharArrayVar(node->data.array_decl.name,
                                       node->data.array_decl.size)
                     : addArrayVar(node->data.array_decl.name,
                                   node->data.array_decl.size);
    if (offset == -1) {
      fprintf(stderr, "Error: Array %s already declared\n",
              node->data.array_decl.name);
      exit(1);
    }
    fprintf(output, "    # Declared array %s[%d] at offset %d\n",
            node->data.array_decl.name, node->data.array_decl.size, offset);
    break;
  }
  case NODE_ARRAY_ASSIGN: {
    if (!isArrayVar(node->data.array_assign.name)) {
      fprintf(stderr, "Error: %s is not an array\n",
              node->data.array_assign.name);
      exit(1);
    }

    int indexReg = genExpr(node->data.array_assign.index);
    int valueReg = genExpr(node->data.array_assign.value);
    int baseOffset = getVarOffset(node->data.array_assign.name);
    int addrReg = getNextTemp();

    fprintf(output, "    # Array assignment: %s[index] = value\n",
            node->data.array_assign.name);
    if (isCharVar(node->data.array_assign.name)) {
      fprintf(output, "    addi $t%d, $sp, %d\n", addrReg, baseOffset);
      fprintf(output, "    add $t%d, $t%d, $t%d\n", addrReg, addrReg, indexReg);
      fprintf(output, "    sb $t%d, 0($t%d)\n", valueReg, addrReg);
    } else {
      fprintf(output, "    sll $t%d, $t%d, 2\n", indexReg, indexReg);
      fprintf(output, "    addi $t%d, $sp, %d\n", addrReg, baseOffset);
      fprintf(output, "    add $t%d, $t%d, $t%d\n", addrReg, addrReg, indexReg);
      fprintf(output, "    sw $t%d, 0($t%d)\n", valueReg, addrReg);
    }
    resetTempRegs();
    break;
  }
  case NODE_STRUCT_DEF: {
    if (addStructType(node->data.struct_def.name) == -1) {
      fprintf(stderr, "Error: Struct %s already defined\n",
              node->data.struct_def.name);
      exit(1);
    }

    ASTNode *field = node->data.struct_def.fields;
    while (field) {
      if (addStructField(node->data.struct_def.name,
                         field->data.struct_field.fieldName,
                         field->data.struct_field.dataType) == -1) {
        fprintf(stderr,
                "Error: Field %s duplicate or struct undefined during %s\n",
                field->data.struct_field.fieldName,
                node->data.struct_def.name);
        exit(1);
      }
      field = field->data.struct_field.next;
    }

    fprintf(output, "    # Struct %s defined\n", node->data.struct_def.name);
    break;
  }
  case NODE_STRUCT_VAR_DECL: {
    int offset = addStructVar(node->data.struct_var_decl.varName,
                              node->data.struct_var_decl.structName);
    if (offset < 0) {
      if (offset == -2) {
        fprintf(stderr, "Error: Struct type %s not defined\n",
                node->data.struct_var_decl.structName);
      } else {
        fprintf(stderr, "Error: Struct variable %s already declared\n",
                node->data.struct_var_decl.varName);
      }
      exit(1);
    }

    fprintf(output, "    # Declared struct %s %s at offset %d\n",
            node->data.struct_var_decl.structName,
            node->data.struct_var_decl.varName, offset);
    break;
  }
  case NODE_STRUCT_ASSIGN: {
    if (!isStructVar(node->data.struct_assign.varName)) {
      fprintf(stderr, "Error: %s is not a struct variable\n",
              node->data.struct_assign.varName);
      exit(1);
    }

    const char *structType =
        getStructTypeName(node->data.struct_assign.varName);
    if (!structType) {
      fprintf(stderr, "Error: Struct type for %s not found\n",
              node->data.struct_assign.varName);
      exit(1);
    }

    int baseOffset = getVarOffset(node->data.struct_assign.varName);
    int fieldOffset =
        getStructFieldOffset(structType, node->data.struct_assign.fieldName);
    if (fieldOffset < 0) {
      fprintf(stderr, "Error: Field %s not found in struct %s\n",
              node->data.struct_assign.fieldName, structType);
      exit(1);
    }

    DataType fieldType =
        getStructFieldType(structType, node->data.struct_assign.fieldName);
    int totalOffset = baseOffset + fieldOffset;

    int valueReg = genExpr(node->data.struct_assign.value);

    fprintf(output, "    # Struct assignment: %s.%s = ...\n",
            node->data.struct_assign.varName,
            node->data.struct_assign.fieldName);
    if (fieldType == TYPE_CHAR) {
      fprintf(output, "    sb $t%d, %d($sp)\n", valueReg, totalOffset);
    } else {
      fprintf(output, "    sw $t%d, %d($sp)\n", valueReg, totalOffset);
    }
    resetTempRegs();
    break;
  }

  case NODE_FUNC_CALL:
    genExpr(node);
    resetTempRegs();
    break;

  case NODE_RETURN:
    if (node->data.return_expr) {
      int retReg = genExpr(node->data.return_expr);
      fprintf(output, "    move $v0, $t%d\n", retReg);
      resetTempRegs();
    } else {
      fprintf(output, "    li $v0, 0\n");
    }
    fprintf(output, "    j %s\n", currentReturnLabel);
    break;

  default:
    break;
  }
}

static void genFunctionBody(const char *name, ASTNode *params, ASTNode *body,
                            int isMainEntry) {
  if (!name)
    return;

  char funcLabel[64];
  formatFunctionLabel(name, funcLabel, sizeof(funcLabel));

  enterScope();
  symtab.count = 0;
  symtab.nextOffset = 0;
  resetTempRegs();

  snprintf(currentReturnLabel, sizeof(currentReturnLabel), "__return_%s",
           funcLabel);
  int frameSize = LOCAL_STACK_SIZE + (isMainEntry ? 0 : 4);

  fprintf(output, "%s:\n", funcLabel);
  fprintf(output, "    addi $sp, $sp, -%d\n", frameSize);
  if (!isMainEntry) {
    fprintf(output, "    sw $ra, %d($sp)\n", RA_SAVE_OFFSET);
  }

  int paramIndex = 0;
  processParameterSequence(params, &paramIndex);
  if (paramIndex > 0)
    fprintf(output, "\n");

  if (body)
    genStmt(body);

  fprintf(output, "%s:\n", currentReturnLabel);
  if (!isMainEntry) {
    fprintf(output, "    lw $ra, %d($sp)\n", RA_SAVE_OFFSET);
  }
  fprintf(output, "    addi $sp, $sp, %d\n", frameSize);
  if (isMainEntry) {
    fprintf(output, "    li $v0, 10\n");
    fprintf(output, "    syscall\n");
  } else {
    fprintf(output, "    jr $ra\n");
  }
  fprintf(output, "\n");
  exitScope();
}

static void genFunctionDecl(ASTNode *funcDecl) {
  if (!funcDecl)
    return;

  const char *name = funcDecl->data.func_decl.name;
  ASTNode *params = funcDecl->data.func_decl.params;
  ASTNode *body = funcDecl->data.func_decl.body;

  int paramTotal = countParams(params);
  if (paramTotal > 4) {
    fprintf(stderr,
            "Error: Function %s has %d parameters; this compiler supports up to 4.\n",
            name ? name : "<anonymous>", paramTotal);
    exit(1);
  }

  int isMainEntry = (name && strcmp(name, "main") == 0);
  genFunctionBody(name, params, body, isMainEntry);
}

static void genFunctionList(ASTNode *node) {
  if (!node)
    return;

  switch (node->type) {
  case NODE_FUNC_LIST:
    if (node->data.list.item)
      genFunctionList(node->data.list.item);
    if (node->data.list.next)
      genFunctionList(node->data.list.next);
    break;

  case NODE_FUNC_DECL:
    genFunctionDecl(node);
    break;

  default:
    genFunctionBody("main", NULL, node, 1);
    break;
  }
}

void generateMIPS(ASTNode *root, const char *filename) {
  output = fopen(filename, "w");
  if (!output) {
    fprintf(stderr, "Cannot open output file %s\n", filename);
    exit(1);
  }

  initSymTab();

  fprintf(output, ".data\n\n");
  fprintf(output, ".text\n");
  fprintf(output, ".globl main\n\n");

  if (!root) {
    genFunctionBody("main", NULL, NULL, 1);
  } else if (root->type == NODE_FUNC_DECL || root->type == NODE_FUNC_LIST) {
    genFunctionList(root);
  } else {
    genFunctionBody("main", NULL, root, 1);
  }

  fclose(output);
}
