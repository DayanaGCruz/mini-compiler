#include "codegen.h"
#include "symtab.h"
#include <stdio.h>
#include <stdlib.h>

FILE *output;
int tempReg = 0;

int getNextTemp() {
  int reg = tempReg++;
  if (tempReg > 7)
    tempReg = 0; // Reuse $t0-$t7
  return reg;
}

void genExpr(ASTNode *node) {
  if (!node)
    return;

  switch (node->type) {
  case NODE_NUM:
    fprintf(output, "    li $t%d, %d\n", getNextTemp(), node->data.num);
    break;

  case NODE_VAR: {
    /*if char type, use lb , else lw*/
    if (isCharVar(node->data.name)) {
      int offset = getVarOffset(node->data.name);
      if (offset == -1) {
        fprintf(stderr, "Error: Variable %s not declared\n", node->data.name);
        exit(1);
      }
      fprintf(output, "     lb $t%d, %d($sp)\n", getNextTemp(), offset);
    } else {
      int offset = getVarOffset(node->data.name);
      if (offset == -1) {
        fprintf(stderr, "Error: Variable %s not declared\n", node->data.name);
        exit(1);
      }
      fprintf(output, "    lw $t%d, %d($sp)\n", getNextTemp(), offset);
    }
    break;
  }

  case NODE_BINOP:
    genExpr(node->data.binop.left);
    int leftReg = tempReg - 1;
    genExpr(node->data.binop.right);
    int rightReg = tempReg - 1;
    if (node->data.binop.op == '+') {
      fprintf(output, "    add $t%d, $t%d, $t%d\n", leftReg, leftReg, rightReg);
    } else if (node->data.binop.op == '-') {
      fprintf(output, "    sub $t%d, $t%d, $t%d\n", leftReg, leftReg, rightReg);
    }
    tempReg = leftReg + 1;
    break;
  case NODE_ARRAY_ACCESS: {
    /* TODO: Generate code for array access */
    if (!isArrayVar(node->data.array_access.name)) {
      fprintf(stderr, "Error: %s is not an array\n",
              node->data.array_access.name);
      exit(1);
    }

    /* Generate code for index expression */
    genExpr(node->data.array_access.index);
    int indexReg = tempReg - 1;

    /* Calculate array element address and load value */
    int baseOffset = getVarOffset(node->data.array_access.name);
    int resultReg = getNextTemp();

    fprintf(output, "    # Array access: %s[index]\n",
            node->data.array_access.name);
    if (isCharVar(node->data.array_access.name)) {
      fprintf(output, "    addi $t%d, $sp, %d   # base address\n", resultReg,
              baseOffset);
      fprintf(output, "    add $t%d, $t%d, $t%d # element address\n", resultReg,
              resultReg, indexReg);
      fprintf(output, "    lb $t%d, 0($t%d)     # load byte\n", resultReg,
              resultReg);
    } else {
      fprintf(output, "    sll $t%d, $t%d, 2    # index * 4\n", indexReg,
              indexReg);
      fprintf(output, "    addi $t%d, $sp, %d   # base address\n", resultReg,
              baseOffset);
      fprintf(output, "    add $t%d, $t%d, $t%d # element address\n", resultReg,
              resultReg, indexReg);
      fprintf(output, "    lw $t%d, 0($t%d)     # load value\n", resultReg,
              resultReg);
    }
    break;
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
            node->data.struct_access.varName, node->data.struct_access.fieldName);
    if (fieldType == TYPE_CHAR) {
      fprintf(output, "    lb $t%d, %d($sp)\n", targetReg, totalOffset);
    } else {
      fprintf(output, "    lw $t%d, %d($sp)\n", targetReg, totalOffset);
    }
    break;
  }
  default:
    break;
  }
}
void genStmt(ASTNode *node) {
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

  case NODE_ASSIGN: {
    int offset = getVarOffset(node->data.assign.var);
    if (offset == -1) {
      fprintf(stderr, "Error: Variable %s not declared\n",
              node->data.assign.var);
      exit(1);
    }
    genExpr(node->data.assign.value);
    if (isCharVar(node->data.assign.var)) {
      fprintf(output, "    sb $t%d, %d($sp)\n", tempReg - 1, offset);
    } else {
      fprintf(output, "    sw $t%d, %d($sp)\n", tempReg - 1, offset);
    }
    tempReg = 0;
    break;
  }

  case NODE_PRINT:
    genExpr(node->data.expr);

    int useChar = 0;
    ASTNode *e = node->data.expr;
    if (((e->type == NODE_VAR) && isCharVar(e->data.name)) ||
        ((e->type == NODE_ARRAY_ACCESS) &&
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
      fprintf(output, "     # Print character\n");
      fprintf(output, "     li $v0, 11\n");
      fprintf(output, "     move $a0, $t%d\n", tempReg - 1);
      fprintf(output, "     syscall\n");
      fprintf(output, "    # Print newline\n");
      fprintf(output, "    li $v0, 11\n");
      fprintf(output, "    li $a0, 10\n");
      fprintf(output, "    syscall\n");
    } else {
      fprintf(output, "    # Print integer\n");
      fprintf(output, "    move $a0, $t%d\n", tempReg - 1);
      fprintf(output, "    li $v0, 1\n");
      fprintf(output, "    syscall\n");
      fprintf(output, "    # Print newline\n");
      fprintf(output, "    li $v0, 11\n");
      fprintf(output, "    li $a0, 10\n");
      fprintf(output, "    syscall\n");
    }
    tempReg = 0;
    break;

  case NODE_STMT_LIST:
    genStmt(node->data.stmtlist.stmt);
    genStmt(node->data.stmtlist.next);
    break;
  case NODE_ARRAY_DECL: {
    /* TODO: Generate code for array declaration */
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
    /* TODO: Generate code for array assignment */
    if (!isArrayVar(node->data.array_assign.name)) {
      fprintf(stderr, "Error: %s is not an array\n",
              node->data.array_assign.name);
      exit(1);
    }

    /* Generate code for index expression */
    genExpr(node->data.array_assign.index);
    int indexReg = tempReg - 1;

    /* Generate code for value expression */
    genExpr(node->data.array_assign.value);
    int valueReg = tempReg - 1;

    /* Calculate array element address */
    int baseOffset = getVarOffset(node->data.array_assign.name);
    int resultReg = getNextTemp();

    fprintf(output, "    # Array assignment: %s[index] = value\n",
            node->data.array_assign.name);
    if (isCharVar(node->data.array_assign.name)) {
      fprintf(output, "    addi $t%d, $sp, %d   # base address\n", resultReg,
              baseOffset);
      fprintf(output, "    add $t%d, $t%d, $t%d # element address\n", resultReg,
              resultReg, indexReg);
      fprintf(output, "    sb $t%d, 0($t%d)     # store byte\n", valueReg,
              resultReg);
    } else {
      fprintf(output, "    sll $t%d, $t%d, 2    # index * 4\n", indexReg,
              indexReg);
      fprintf(output, "    addi $t%d, $sp, %d   # base address\n", resultReg,
              baseOffset);
      fprintf(output, "    add $t%d, $t%d, $t%d # element address\n", resultReg,
              resultReg, indexReg);
      fprintf(output, "    sw $t%d, 0($t%d)     # store value\n", valueReg,
              resultReg);
    }
    tempReg = 0;
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

    genExpr(node->data.struct_assign.value);
    int valueReg = tempReg - 1;

    fprintf(output, "    # Struct assignment: %s.%s = ...\n",
            node->data.struct_assign.varName,
            node->data.struct_assign.fieldName);
    if (fieldType == TYPE_CHAR) {
      fprintf(output, "    sb $t%d, %d($sp)\n", valueReg, totalOffset);
    } else {
      fprintf(output, "    sw $t%d, %d($sp)\n", valueReg, totalOffset);
    }
    tempReg = 0;
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
  default:
    break;
  }
}

void generateMIPS(ASTNode *root, const char *filename) {
  output = fopen(filename, "w");
  if (!output) {
    fprintf(stderr, "Cannot open output file %s\n", filename);
    exit(1);
  }

  // Initialize symbol table
  initSymTab();

  // MIPS program header
  fprintf(output, ".data\n");
  fprintf(output, "\n.text\n");
  fprintf(output, ".globl main\n");
  fprintf(output, "main:\n");

  // Allocate stack space (max 100 variables * 4 bytes)
  fprintf(output, "    # Allocate stack space\n");
  fprintf(output, "    addi $sp, $sp, -400\n\n");

  // Generate code for statements
  genStmt(root);

  // Program exit
  fprintf(output, "\n    # Exit program\n");
  fprintf(output, "    addi $sp, $sp, 400\n");
  fprintf(output, "    li $v0, 10\n");
  fprintf(output, "    syscall\n");

  fclose(output);
}
