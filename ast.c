/* AST IMPLEMENTATION
 * Functions to create and manipulate Abstract Syntax Tree nodes
 * The AST is built during parsing and used for all subsequent phases
 */
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylineno;

/* Small helpers turn enum values into readable labels so diagnostics and the
 * AST pretty-printer stay useful even when new types are introduced. */
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
  }
  return "?";
}

static const char *unaryOpToString(UnaryOp op) {
  switch (op) {
  case UNOP_NOT:
    return "!";
  }
  return "?";
}

/* Central allocation helper that tags the node and records the lexer line so
 * every downstream diagnostic can point back to the originating token. */
static ASTNode *allocNode(NodeType type) {
  ASTNode *node = malloc(sizeof(ASTNode));
  if (!node) {
    fprintf(stderr, "Out of memory in AST allocation\n");
    exit(1);
  }
  node->type = type;
  node->line = yylineno;
  return node;
}

/* === Literal and identifier node builders === */

ASTNode *createNum(int value) {
  ASTNode *node = allocNode(NODE_NUM);
  node->data.num = value;
  return node;
}

ASTNode *createFloat(double value) {
  ASTNode *node = allocNode(NODE_FLOAT);
  node->data.fnum = value;
  return node;
}

ASTNode *createBoolLiteral(int value) {
  ASTNode *node = allocNode(NODE_BOOL);
  node->data.boolValue = value ? 1 : 0;
  return node;
}

ASTNode *createVar(char *name) {
  ASTNode *node = allocNode(NODE_VAR);
  node->data.name = strdup(name);
  return node;
}

ASTNode *createBinOp(BinaryOp op, ASTNode *left, ASTNode *right) {
  ASTNode *node = allocNode(NODE_BINOP);
  node->data.binop.op = op;
  node->data.binop.left = left;
  node->data.binop.right = right;
  return node;
}

ASTNode *createUnaryOp(UnaryOp op, ASTNode *expr) {
  ASTNode *node = allocNode(NODE_UNARY_OP);
  node->data.unary.op = op;
  node->data.unary.expr = expr;
  return node;
}

ASTNode *createDecl(char *name) {
  ASTNode *node = allocNode(NODE_DECL);
  node->data.name = strdup(name);
  return node;
}

ASTNode *createCharDecl(char *name) {
  ASTNode *node = allocNode(NODE_CHAR_DECL);
  node->data.name = strdup(name);
  return node;
}

ASTNode *createFloatDecl(char *name) {
  ASTNode *node = allocNode(NODE_FLOAT_DECL);
  node->data.name = strdup(name);
  return node;
}

ASTNode *createBoolDecl(char *name) {
  ASTNode *node = allocNode(NODE_BOOL_DECL);
  node->data.name = strdup(name);
  return node;
}

ASTNode *createAssign(char *var, ASTNode *value) {
  ASTNode *node = allocNode(NODE_ASSIGN);
  node->data.assign.var = strdup(var);
  node->data.assign.value = value;
  return node;
}

ASTNode *createPrint(ASTNode *expr) {
  ASTNode *node = allocNode(NODE_PRINT);
  node->data.expr = expr;
  return node;
}

ASTNode *createExprStmt(ASTNode *expr) {
  ASTNode *node = allocNode(NODE_EXPR_STMT);
  node->data.expr = expr;
  return node;
}

ASTNode *createStmtList(ASTNode *stmt1, ASTNode *stmt2) {
  ASTNode *node = allocNode(NODE_STMT_LIST);
  node->data.stmtlist.stmt = stmt1;
  node->data.stmtlist.next = stmt2;
  return node;
}

ASTNode *createBlock(ASTNode *stmts) {
  ASTNode *node = allocNode(NODE_BLOCK);
  node->data.block_items = stmts;
  return node;
}

/* === Composite type helpers: arrays and structs === */

ASTNode *createArrayDecl(char *name, int size, DataType dataType) {
  ASTNode *node = allocNode(NODE_ARRAY_DECL);
  node->data.array_decl.name = strdup(name);
  node->data.array_decl.size = size;
  node->data.array_decl.dataType = dataType;
  return node;
}

ASTNode *createArrayAssign(char *name, ASTNode *index, ASTNode *value) {
  ASTNode *node = allocNode(NODE_ARRAY_ASSIGN);
  node->data.array_assign.name = strdup(name);
  node->data.array_assign.index = index;
  node->data.array_assign.value = value;
  return node;
}

ASTNode *createArrayAccess(char *name, ASTNode *index) {
  ASTNode *node = allocNode(NODE_ARRAY_ACCESS);
  node->data.array_access.name = strdup(name);
  node->data.array_access.index = index;
  return node;
}

ASTNode *createStructDef(char *name, ASTNode *fields) {
  ASTNode *node = allocNode(NODE_STRUCT_DEF);
  node->data.struct_def.name = strdup(name);
  node->data.struct_def.fields = fields;
  return node;
}

ASTNode *createStructField(char *name, DataType dataType) {
  ASTNode *node = allocNode(NODE_STRUCT_FIELD);
  node->data.struct_field.fieldName = strdup(name);
  node->data.struct_field.dataType = dataType;
  node->data.struct_field.next = NULL;
  return node;
}

ASTNode *appendStructField(ASTNode *list, ASTNode *field) {
  if (!list)
    return field;
  ASTNode *curr = list;
  while (curr->data.struct_field.next) {
    curr = curr->data.struct_field.next;
  }
  curr->data.struct_field.next = field;
  return list;
}

ASTNode *createStructVarDecl(char *structName, char *varName) {
  ASTNode *node = allocNode(NODE_STRUCT_VAR_DECL);
  node->data.struct_var_decl.structName = strdup(structName);
  node->data.struct_var_decl.varName = strdup(varName);
  return node;
}

ASTNode *createStructAssign(char *varName, char *fieldName, ASTNode *value) {
  ASTNode *node = allocNode(NODE_STRUCT_ASSIGN);
  node->data.struct_assign.varName = strdup(varName);
  node->data.struct_assign.fieldName = strdup(fieldName);
  node->data.struct_assign.value = value;
  return node;
}

ASTNode *createStructAccess(char *varName, char *fieldName) {
  ASTNode *node = allocNode(NODE_STRUCT_ACCESS);
  node->data.struct_access.varName = strdup(varName);
  node->data.struct_access.fieldName = strdup(fieldName);
  return node;
}

/* === Function and control-flow helpers === */

ASTNode *createFuncDecl(DataType returnType, char *name, ASTNode *params,
                        ASTNode *body) {
  ASTNode *node = allocNode(NODE_FUNC_DECL);
  node->data.func_decl.name = strdup(name);
  node->data.func_decl.returnType = returnType;
  node->data.func_decl.params = params;
  node->data.func_decl.body = body;
  return node;
}

ASTNode *createFuncCall(char *name, ASTNode *args) {
  ASTNode *node = allocNode(NODE_FUNC_CALL);
  node->data.func_call.name = name;
  node->data.func_call.args = args;
  return node;
}

ASTNode *createParam(DataType type, char *name) {
  ASTNode *node = allocNode(NODE_PARAM);
  node->data.param.type = type;
  node->data.param.name = strdup(name);
  node->data.param.isArray = 0;
  node->data.param.arraySize = 0;
  node->data.param.isStruct = 0;
  node->data.param.structType = NULL;
  return node;
}

ASTNode *createArrayParam(DataType type, char *name, int size) {
  ASTNode *node = createParam(type, name);
  node->data.param.isArray = 1;
  node->data.param.arraySize = size;
  return node;
}

ASTNode *createStructParam(char *structName, char *varName) {
  ASTNode *node = allocNode(NODE_PARAM);
  node->data.param.type = TYPE_VOID;
  node->data.param.name = strdup(varName);
  node->data.param.isArray = 0;
  node->data.param.arraySize = 0;
  node->data.param.isStruct = 1;
  node->data.param.structType = strdup(structName);
  return node;
}

ASTNode *createParamList(ASTNode *param, ASTNode *next) {
  ASTNode *node = allocNode(NODE_PARAM_LIST);
  node->data.list.item = param;
  node->data.list.next = next;
  return node;
}

ASTNode *createArgList(ASTNode *arg, ASTNode *next) {
  ASTNode *node = allocNode(NODE_ARG_LIST);
  node->data.list.item = arg;
  node->data.list.next = next;
  return node;
}

ASTNode *createReturn(ASTNode *expr) {
  ASTNode *node = allocNode(NODE_RETURN);
  node->data.return_expr = expr;
  return node;
}

ASTNode *createFuncList(ASTNode *func, ASTNode *next) {
  ASTNode *node = allocNode(NODE_FUNC_LIST);
  node->data.list.item = func;
  node->data.list.next = next;
  return node;
}

ASTNode *createIf(ASTNode *cond, ASTNode *thenBranch, ASTNode *elseBranch) {
  ASTNode *node = allocNode(NODE_IF);
  node->data.if_stmt.condition = cond;
  node->data.if_stmt.thenBranch = thenBranch;
  node->data.if_stmt.elseBranch = elseBranch;
  return node;
}

ASTNode *createSwitch(ASTNode *expr, ASTNode *cases, ASTNode *defaultCase) {
  ASTNode *node = allocNode(NODE_SWITCH);
  node->data.switch_stmt.expr = expr;
  node->data.switch_stmt.cases = cases;
  node->data.switch_stmt.defaultCase = defaultCase;
  return node;
}

ASTNode *createCase(ASTNode *valueExpr, ASTNode *statements) {
  ASTNode *node = allocNode(NODE_CASE);
  node->data.case_stmt.isDefault = 0;
  node->data.case_stmt.valueExpr = valueExpr;
  node->data.case_stmt.statements = statements;
  node->data.case_stmt.next = NULL;
  node->data.case_stmt.label = NULL;
  return node;
}

ASTNode *createDefaultCase(ASTNode *statements) {
  ASTNode *node = allocNode(NODE_CASE);
  node->data.case_stmt.isDefault = 1;
  node->data.case_stmt.valueExpr = NULL;
  node->data.case_stmt.statements = statements;
  node->data.case_stmt.next = NULL;
  node->data.case_stmt.label = NULL;
  return node;
}

ASTNode *appendCase(ASTNode *cases, ASTNode *newCase) {
  if (!cases)
    return newCase;
  ASTNode *curr = cases;
  while (curr->data.case_stmt.next) {
    curr = curr->data.case_stmt.next;
  }
  curr->data.case_stmt.next = newCase;
  return cases;
}

ASTNode *createBreak(void) {
  return allocNode(NODE_BREAK);
}

ASTNode *createConditionalExpr(ASTNode *cond, ASTNode *trueExpr,
                               ASTNode *falseExpr) {
  ASTNode *node = allocNode(NODE_CONDITIONAL);
  node->data.conditional.condition = cond;
  node->data.conditional.trueExpr = trueExpr;
  node->data.conditional.falseExpr = falseExpr;
  return node;
}

ASTNode *createWhile(ASTNode *cond, ASTNode *body) {
  ASTNode *node = allocNode(NODE_WHILE);
  node->data.while_stmt.condition = cond;
  node->data.while_stmt.body = body;
  return node;
}


/* === Debug printer ===
 * Walking the tree recursively gives the user a readable outline of how the
 * parser understood the source code. Indentation mirrors node depth. */
static void printIndent(int level) {
  for (int i = 0; i < level; i++)
    printf("  ");
}

/* printAST mirrors the node type dispatch table so adding a new variant
 * requires touching a single location and guarantees the dump stays useful
 * during debugging sessions. */
void printAST(ASTNode *node, int level) {
  if (!node)
    return;

  switch (node->type) {
  case NODE_NUM:
    printIndent(level);
    printf("NUM: %d\n", node->data.num);
    break;
  case NODE_FLOAT:
    printIndent(level);
    printf("FLOAT: %f\n", node->data.fnum);
    break;
  case NODE_BOOL:
    printIndent(level);
    printf("BOOL: %s\n", node->data.boolValue ? "true" : "false");
    break;
  case NODE_VAR:
    printIndent(level);
    printf("VAR: %s\n", node->data.name);
    break;
  case NODE_BINOP:
    printIndent(level);
    printf("BINOP: %s\n", binaryOpToString(node->data.binop.op));
    printAST(node->data.binop.left, level + 1);
    printAST(node->data.binop.right, level + 1);
    break;
  case NODE_UNARY_OP:
    printIndent(level);
    printf("UNARY: %s\n", unaryOpToString(node->data.unary.op));
    printAST(node->data.unary.expr, level + 1);
    break;
  case NODE_DECL:
    printIndent(level);
    printf("DECL (int): %s\n", node->data.name);
    break;
  case NODE_CHAR_DECL:
    printIndent(level);
    printf("DECL (char): %s\n", node->data.name);
    break;
  case NODE_FLOAT_DECL:
    printIndent(level);
    printf("DECL (float): %s\n", node->data.name);
    break;
  case NODE_BOOL_DECL:
    printIndent(level);
    printf("DECL (bool): %s\n", node->data.name);
    break;
  case NODE_ASSIGN:
    printIndent(level);
    printf("ASSIGN: %s\n", node->data.assign.var);
    printAST(node->data.assign.value, level + 1);
    break;
  case NODE_PRINT:
    printIndent(level);
    printf("PRINT\n");
    printAST(node->data.expr, level + 1);
    break;
  case NODE_EXPR_STMT:
    printIndent(level);
    printf("EXPR_STMT\n");
    printAST(node->data.expr, level + 1);
    break;
  case NODE_STMT_LIST:
    printAST(node->data.stmtlist.stmt, level);
    printAST(node->data.stmtlist.next, level);
    break;
  case NODE_BLOCK:
    printIndent(level);
    printf("BLOCK\n");
    printAST(node->data.block_items, level + 1);
    break;
  case NODE_IF:
    printIndent(level);
    printf("IF\n");
    printIndent(level + 1);
    printf("COND:\n");
    printAST(node->data.if_stmt.condition, level + 2);
    printIndent(level + 1);
    printf("THEN:\n");
    printAST(node->data.if_stmt.thenBranch, level + 2);
    if (node->data.if_stmt.elseBranch) {
      printIndent(level + 1);
      printf("ELSE:\n");
      printAST(node->data.if_stmt.elseBranch, level + 2);
    }
    break;
  case NODE_SWITCH:
    printIndent(level);
    printf("SWITCH\n");
    printIndent(level + 1);
    printf("EXPR:\n");
    printAST(node->data.switch_stmt.expr, level + 2);
    printIndent(level + 1);
    printf("CASES:\n");
    printAST(node->data.switch_stmt.cases, level + 2);
    if (node->data.switch_stmt.defaultCase) {
      printIndent(level + 1);
      printf("DEFAULT:\n");
      printAST(node->data.switch_stmt.defaultCase, level + 2);
    }
    break;
  case NODE_CASE:
    printIndent(level);
    if (node->data.case_stmt.isDefault) {
      printf("CASE <default>\n");
    } else {
      printf("CASE\n");
      printAST(node->data.case_stmt.valueExpr, level + 1);
    }
    printAST(node->data.case_stmt.statements, level + 1);
    printAST(node->data.case_stmt.next, level);
    break;
  case NODE_BREAK:
    printIndent(level);
    printf("BREAK\n");
    break;
  case NODE_CONDITIONAL:
    printIndent(level);
    printf("CONDITIONAL\n");
    printIndent(level + 1);
    printf("COND:\n");
    printAST(node->data.conditional.condition, level + 2);
    printIndent(level + 1);
    printf("TRUE:\n");
    printAST(node->data.conditional.trueExpr, level + 2);
    printIndent(level + 1);
    printf("FALSE:\n");
    printAST(node->data.conditional.falseExpr, level + 2);
    break;
  case NODE_ARRAY_DECL:
    printIndent(level);
    printf("ARRAY_DECL: %s[%d] (%s)\n", node->data.array_decl.name,
           node->data.array_decl.size,
           dataTypeToString(node->data.array_decl.dataType));
    break;
  case NODE_ARRAY_ASSIGN:
    printIndent(level);
    printf("ARRAY_ASSIGN: %s[]\n", node->data.array_assign.name);
    printIndent(level + 1);
    printf("Index:\n");
    printAST(node->data.array_assign.index, level + 2);
    printIndent(level + 1);
    printf("Value:\n");
    printAST(node->data.array_assign.value, level + 2);
    break;
  case NODE_ARRAY_ACCESS:
    printIndent(level);
    printf("ARRAY_ACCESS: %s\n", node->data.array_access.name);
    printAST(node->data.array_access.index, level + 1);
    break;
  case NODE_STRUCT_DEF:
    printIndent(level);
    printf("STRUCT: %s\n", node->data.struct_def.name);
    printAST(node->data.struct_def.fields, level + 1);
    break;
  case NODE_STRUCT_FIELD:
    printIndent(level);
    printf("FIELD (%s): %s\n",
           dataTypeToString(node->data.struct_field.dataType),
           node->data.struct_field.fieldName);
    printAST(node->data.struct_field.next, level);
    break;
  case NODE_STRUCT_VAR_DECL:
    printIndent(level);
    printf("STRUCT VAR: %s %s\n", node->data.struct_var_decl.structName,
           node->data.struct_var_decl.varName);
    break;
  case NODE_STRUCT_ASSIGN:
    printIndent(level);
    printf("STRUCT ASSIGN: %s.%s\n", node->data.struct_assign.varName,
           node->data.struct_assign.fieldName);
    printAST(node->data.struct_assign.value, level + 1);
    break;
  case NODE_STRUCT_ACCESS:
    printIndent(level);
    printf("STRUCT ACCESS: %s.%s\n", node->data.struct_access.varName,
           node->data.struct_access.fieldName);
    break;
  case NODE_FUNC_DECL:
    printIndent(level);
    printf("FUNC DECL: %s RETURN: %s\n", node->data.func_decl.name,
           dataTypeToString(node->data.func_decl.returnType));
    printAST(node->data.func_decl.params, level + 1);
    printAST(node->data.func_decl.body, level + 1);
    break;
  case NODE_FUNC_CALL:
    printIndent(level);
    printf("FUNC_CALL: %s\n", node->data.func_call.name);
    printAST(node->data.func_call.args, level + 1);
    break;
  case NODE_FUNC_LIST:
    printAST(node->data.list.item, level);
    printAST(node->data.list.next, level);
    break;
  case NODE_PARAM_LIST:
  case NODE_ARG_LIST:
    printAST(node->data.list.item, level);
    printAST(node->data.list.next, level);
    break;
  case NODE_PARAM:
    printIndent(level);
    if (node->data.param.isStruct) {
      printf("FUNCTION PARAMETER: struct %s %s\n",
             node->data.param.structType ? node->data.param.structType :
                                            "<anon>",
             node->data.param.name);
    } else if (node->data.param.isArray) {
      printf("FUNCTION PARAMETER: %s %s[%d]\n",
             dataTypeToString(node->data.param.type),
             node->data.param.name, node->data.param.arraySize);
    } else {
      printf("FUNCTION PARAMETER: %s %s\n",
             dataTypeToString(node->data.param.type),
             node->data.param.name);
    }
    break;
  case NODE_RETURN:
    printIndent(level);
    printf("RETURN\n");
    printAST(node->data.return_expr, level + 1);
    break;
  case NODE_WHILE:
      printIndent(level);
      printf("WHILE\n");
      printAST(node->data.while_stmt.condition, level + 1);
      printAST(node->data.while_stmt.body, level + 1);
    break;
  default:
    break;
  }
}
