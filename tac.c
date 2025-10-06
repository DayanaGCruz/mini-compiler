#include "tac.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TACList tacList;
TACList optimizedList;

static int isNumericLiteral(const char *s) {
  if (!s || !*s)
    return 0;
  if (isdigit((unsigned char)s[0]))
    return 1;
  return (s[0] == '-' && isdigit((unsigned char)s[1]));
}

void initTAC() {
  tacList.head = NULL;
  tacList.tail = NULL;
  tacList.tempCount = 0;
  optimizedList.head = NULL;
  optimizedList.tail = NULL;
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

char *generateTACExpr(ASTNode *node) {
  if (!node)
    return NULL;

  switch (node->type) {
  case NODE_NUM: {
    char *temp = malloc(20);
    sprintf(temp, "%d", node->data.num);
    return temp;
  }

  case NODE_VAR:
    return strdup(node->data.name);

  case NODE_BINOP: {
    char *left = generateTACExpr(node->data.binop.left);
    char *right = generateTACExpr(node->data.binop.right);
    char *temp = newTemp();

    if (node->data.binop.op == '+') {
      appendTAC(createTAC(TAC_ADD, left, right, temp));
    } else if (node->data.binop.op == '-') {
      appendTAC(createTAC(TAC_SUB, left, right, temp));
    }

    return temp;
  }
  case NODE_ARRAY_ACCESS: {
    /* TODO: Generate TAC for array access */
    char *indexExpr = generateTACExpr(node->data.array_access.index);
    char *temp = newTemp();

    appendTAC(createTAC(TAC_ARRAY_ACCESS, indexExpr,
                        node->data.array_access.name, temp));
    return temp;
  }
  case NODE_STRUCT_ACCESS: {
    char *temp = newTemp();
    appendTAC(createTAC(TAC_STRUCT_ACCESS, node->data.struct_access.varName,
                        node->data.struct_access.fieldName, temp));
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
  case NODE_DECL:
    appendTAC(createTAC(TAC_DECL, NULL, NULL, node->data.name));
    break;

  case NODE_ASSIGN: {
    char *expr = generateTACExpr(node->data.assign.value);
    appendTAC(createTAC(TAC_ASSIGN, expr, NULL, node->data.assign.var));
    break;
  }

  case NODE_PRINT: {
    char *expr = generateTACExpr(node->data.expr);
    appendTAC(createTAC(TAC_PRINT, expr, NULL, NULL));
    break;
  }

  case NODE_STMT_LIST:
    generateTAC(node->data.stmtlist.stmt);
    generateTAC(node->data.stmtlist.next);
    break;
  case NODE_ARRAY_DECL:
    appendTAC(
        createTAC(TAC_ARRAY_DECL, NULL, NULL, node->data.array_decl.name));
    break;
  case NODE_ARRAY_ASSIGN: {
    char *indexExpr = generateTACExpr(node->data.array_assign.index);
    char *valueExpr = generateTACExpr(node->data.array_assign.index);
    appendTAC(createTAC(TAC_ARRAY_ASSIGN, indexExpr, valueExpr,
                        node->data.array_assign.name));
    break;
  }

  case NODE_STRUCT_DEF: {
    appendTAC(createTAC(TAC_STRUCT_DECL, NULL, NULL,
                        node->data.struct_def.name));
    ASTNode *field = node->data.struct_def.fields;
    while (field) {
      const char *typeStr =
          field->data.struct_field.dataType == TYPE_CHAR ? "char" : "int";
      appendTAC(createTAC(TAC_STRUCT_FIELD, field->data.struct_field.fieldName,
                          (char *)typeStr, node->data.struct_def.name));
      field = field->data.struct_field.next;
    }
    break;
  }

  case NODE_STRUCT_VAR_DECL:
    appendTAC(createTAC(TAC_STRUCT_VAR_DECL,
                        node->data.struct_var_decl.structName, NULL,
                        node->data.struct_var_decl.varName));
    break;

  case NODE_STRUCT_ASSIGN: {
    char *valueExpr = generateTACExpr(node->data.struct_assign.value);
    appendTAC(createTAC(TAC_STRUCT_ASSIGN, valueExpr,
                        node->data.struct_assign.fieldName,
                        node->data.struct_assign.varName));
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

    case TAC_ADD:
      printf("%s = %s + %s", curr->result, curr->arg1, curr->arg2);
      printf("     // Add: store result in %s\n", curr->result);
      break;
    case TAC_SUB:
      printf("%s = %s - %s", curr->result, curr->arg1, curr->arg2);
      printf("     // Subtract: store result in %s\n", curr->result);
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
  } VarValue;

  VarValue values[100];
  int valueCount = 0;

  while (curr) {
    TACInstr *newInstr = NULL;

    switch (curr->op) {
    case TAC_DECL:
      newInstr = createTAC(TAC_DECL, NULL, NULL, curr->result);
      break;

    case TAC_ADD:
    case TAC_SUB: {
      // Check if both operands are constants
      char *left = curr->arg1;
      char *right = curr->arg2;

      // Look up values in propagation table (search from most recent)
      for (int i = valueCount - 1; i >= 0; i--) {
        if (strcmp(values[i].var, left) == 0) {
          left = values[i].value;
          break;
        }
      }
      for (int i = valueCount - 1; i >= 0; i--) {
        if (strcmp(values[i].var, right) == 0) {
          right = values[i].value;
          break;
        }
      }

      // Constant folding
      if (isNumericLiteral(left) && isNumericLiteral(right)) {
        int result = (curr->op == TAC_ADD) ? atoi(left) + atoi(right)
                                           : atoi(left) - atoi(right);
        char *resultStr = malloc(20);
        sprintf(resultStr, "%d", result);

        // Store for propagation
        values[valueCount].var = strdup(curr->result);
        values[valueCount].value = resultStr;
        valueCount++;

        newInstr = createTAC(TAC_ASSIGN, resultStr, NULL, curr->result);
      } else {
        newInstr = createTAC(curr->op, left, right, curr->result);
      }
      break;
    }

    case TAC_ASSIGN: {
      char *value = curr->arg1;

      // Look up value in propagation table (search from most recent)
      for (int i = valueCount - 1; i >= 0; i--) {
        if (strcmp(values[i].var, value) == 0) {
          value = values[i].value;
          break;
        }
      }

      // Store for propagation
      values[valueCount].var = strdup(curr->result);
      values[valueCount].value = strdup(value);
      valueCount++;

      newInstr = createTAC(TAC_ASSIGN, value, NULL, curr->result);
      break;
    }

    case TAC_PRINT: {
      char *value = curr->arg1;

      // Look up value in propagation table
      for (int i = valueCount - 1; i >= 0; i--) { // Search from most recent
        if (strcmp(values[i].var, value) == 0) {
          value = values[i].value;
          break;
        }
      }

      newInstr = createTAC(TAC_PRINT, value, NULL, NULL);
      break;
    }

    case TAC_ARRAY_DECL:
        /* TODO: Arrays declarations don't need optimization */
        newInstr = createTAC(TAC_ARRAY_DECL, NULL, NULL, curr->result);
        break;

    case TAC_ARRAY_ASSIGN: {
        /* TODO: Optimize array assignments */
        char* index = curr->arg1;
        char* value = curr->arg2;

        /* Look up values in propagation table */
        for (int i = valueCount - 1; i >= 0; i--) {
        if (strcmp(values[i].var, index) == 0) {
    index = values[i].value;
    break;
}
        }
        for (int i = valueCount - 1; i >= 0; i--) {
if (strcmp(values[i].var, value) == 0) {
    value = values[i].value;
    break;
}
        }

        newInstr = createTAC(TAC_ARRAY_ASSIGN, index, value, curr->result);
        break;
    }

    case TAC_ARRAY_ACCESS: {
        /* TODO: Optimize array access */
        char* index = curr->arg1;

        /* Look up index in propagation table */
        for (int i = valueCount - 1; i >= 0; i--) {
        if (strcmp(values[i].var, index) == 0) {
    index = values[i].value;
    break;
}
        }

        newInstr = createTAC(TAC_ARRAY_ACCESS, index, curr->arg2, curr->result);
        break;
    }

    case TAC_STRUCT_DECL:
        newInstr = createTAC(TAC_STRUCT_DECL, curr->arg1, curr->arg2, curr->result);
        break;

    case TAC_STRUCT_FIELD:
        newInstr = createTAC(TAC_STRUCT_FIELD, curr->arg1, curr->arg2, curr->result);
        break;

    case TAC_STRUCT_VAR_DECL:
        newInstr = createTAC(TAC_STRUCT_VAR_DECL, curr->arg1, curr->arg2, curr->result);
        break;

    case TAC_STRUCT_ASSIGN: {
      char *value = curr->arg1;

      /* Propagate the assigned value if it is a known copy */
      for (int i = valueCount - 1; i >= 0; i--) {
        if (strcmp(values[i].var, value) == 0) {
          value = values[i].value;
          break;
        }
      }

      /* Track struct field value for later accesses */
      size_t keyLen = strlen(curr->result) + 1 + strlen(curr->arg2) + 1;
      char *fieldKey = malloc(keyLen);
      sprintf(fieldKey, "%s.%s", curr->result, curr->arg2);

      values[valueCount].var = fieldKey;
      values[valueCount].value = strdup(value);
      valueCount++;

      newInstr =
          createTAC(TAC_STRUCT_ASSIGN, value, curr->arg2, curr->result);
      break;
    }

    case TAC_STRUCT_ACCESS: {
      size_t keyLen = strlen(curr->arg1) + 1 + strlen(curr->arg2) + 1;
      char *fieldKey = malloc(keyLen);
      sprintf(fieldKey, "%s.%s", curr->arg1, curr->arg2);

      char *fieldValue = NULL;
      for (int i = valueCount - 1; i >= 0; i--) {
        if (strcmp(values[i].var, fieldKey) == 0) {
          fieldValue = values[i].value;
          break;
        }
      }

      if (fieldValue) {
        /* Replace access with direct assignment and propagate */
        newInstr = createTAC(TAC_ASSIGN, fieldValue, NULL, curr->result);
        values[valueCount].var = strdup(curr->result);
        values[valueCount].value = strdup(fieldValue);
        valueCount++;
      } else {
        newInstr = createTAC(TAC_STRUCT_ACCESS, curr->arg1, curr->arg2,
                             curr->result);
      }

      free(fieldKey);
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
      printf("%s = %s.%s   // Struct field access\n", curr->result,
             curr->arg1, curr->arg2);
      break;
    default:
      break;
    }
    curr = curr->next;
  }
}
