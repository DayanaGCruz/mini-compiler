/* AST IMPLEMENTATION
 * Functions to create and manipulate Abstract Syntax Tree nodes
 * The AST is built during parsing and used for all subsequent phases
 */
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Create a number literal node */
ASTNode *createNum(int value) {
  ASTNode *node = malloc(sizeof(ASTNode));
  node->type = NODE_NUM;
  node->data.num = value; /* Store the integer value */
  return node;
}

/* Create a variable reference node */
ASTNode *createVar(char *name) {
  ASTNode *node = malloc(sizeof(ASTNode));
  node->type = NODE_VAR;
  node->data.name = strdup(name); /* Copy the variable name */
  return node;
}

/* Create a binary operation node (e.g., + or -) */
ASTNode *createBinOp(char op, ASTNode *left, ASTNode *right) {
  ASTNode *node = malloc(sizeof(ASTNode));
  node->type = NODE_BINOP;
  node->data.binop.op = op;       /* Store operator (+, -, ...) */
  node->data.binop.left = left;   /* Left subtree */
  node->data.binop.right = right; /* Right subtree */
  return node;
}

/* Create a variable declaration node */
ASTNode *createDecl(char *name) {
  ASTNode *node = malloc(sizeof(ASTNode));
  node->type = NODE_DECL;
  node->data.name = strdup(name); /* Store variable name */
  return node;
}

ASTNode *createCharDecl(char *name) {
  ASTNode *node = malloc(sizeof(ASTNode));
  node->type = NODE_CHAR_DECL;
  node->data.name = strdup(name);
  return node;
}

/*
ASTNode* createDeclWithAssgn(char* name, int value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_DECL;
    node->data.name = strdup(name);
    node->data.value = value;
    return node;
}

*/

/* Create an assignment statement node */
ASTNode *createAssign(char *var, ASTNode *value) {
  ASTNode *node = malloc(sizeof(ASTNode));
  node->type = NODE_ASSIGN;
  node->data.assign.var = strdup(var); /* Variable name */
  node->data.assign.value = value;     /* Expression tree */
  return node;
}

/* Create a print statement node */
ASTNode *createPrint(ASTNode *expr) {
  ASTNode *node = malloc(sizeof(ASTNode));
  node->type = NODE_PRINT;
  node->data.expr = expr; /* Expression to print */
  return node;
}

/* Create a statement list node (links statements together) */
ASTNode *createStmtList(ASTNode *stmt1, ASTNode *stmt2) {
  ASTNode *node = malloc(sizeof(ASTNode));
  node->type = NODE_STMT_LIST;
  node->data.stmtlist.stmt = stmt1; /* First statement */
  node->data.stmtlist.next = stmt2; /* Rest of list */
  return node;
}
/* TODO: Implement array declaration creation */
ASTNode *createArrayDecl(char *name, int size, DataType dataType) {
  ASTNode *node = malloc(sizeof(ASTNode));
  node->type = NODE_ARRAY_DECL;
  node->data.array_decl.name = strdup(name);
  node->data.array_decl.size = size;
  node->data.array_decl.dataType = dataType;
  return node;
}

/* TODO: Implement array assignment creation */
ASTNode *createArrayAssign(char *name, ASTNode *index, ASTNode *value) {
  ASTNode *node = malloc(sizeof(ASTNode));
  node->type = NODE_ARRAY_ASSIGN;
  node->data.array_assign.name = strdup(name);
  node->data.array_assign.index = index;
  node->data.array_assign.value = value;
  return node;
}

/* TODO: Implement array access creation */
ASTNode *createArrayAccess(char *name, ASTNode *index) {
  ASTNode *node = malloc(sizeof(ASTNode));
  node->type = NODE_ARRAY_ACCESS;
  node->data.array_access.name = strdup(name);
  node->data.array_access.index = index;
  return node;
}

ASTNode *createStructDef(char *name, ASTNode *fields) {
  ASTNode *node = malloc(sizeof(ASTNode));
  node->type = NODE_STRUCT_DEF;
  node->data.struct_def.name = strdup(name);
  node->data.struct_def.fields = fields;
  return node;
}

ASTNode *createStructField(char *name, DataType dataType) {
  ASTNode *node = malloc(sizeof(ASTNode));
  node->type = NODE_STRUCT_FIELD;
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
  ASTNode *node = malloc(sizeof(ASTNode));
  node->type = NODE_STRUCT_VAR_DECL;
  node->data.struct_var_decl.structName = strdup(structName);
  node->data.struct_var_decl.varName = strdup(varName);
  return node;
}

ASTNode *createStructAssign(char *varName, char *fieldName, ASTNode *value) {
  ASTNode *node = malloc(sizeof(ASTNode));
  node->type = NODE_STRUCT_ASSIGN;
  node->data.struct_assign.varName = strdup(varName);
  node->data.struct_assign.fieldName = strdup(fieldName);
  node->data.struct_assign.value = value;
  return node;
}

ASTNode *createStructAccess(char *varName, char *fieldName) {
  ASTNode *node = malloc(sizeof(ASTNode));
  node->type = NODE_STRUCT_ACCESS;
  node->data.struct_access.varName = strdup(varName);
  node->data.struct_access.fieldName = strdup(fieldName);
  return node;
}

ASTNode *createFuncDecl(char *returnType, char *name, ASTNode *params,
                        ASTNode *body) {
  ASTNode *node = malloc(sizeof(ASTNode));
  node->type = NODE_FUNC_DECL;
  node->data.func_decl.name = strdup(name);
  node->data.func_decl.returnType = strdup(returnType);
  node->data.func_decl.params = params;
  node->data.func_decl.body = body;
  return node;
}
ASTNode *createFuncCall(char *name, ASTNode *args) {
  ASTNode *node = malloc(sizeof(ASTNode));
  node->type = NODE_FUNC_CALL;
  node->data.func_call.name = name;
  node->data.func_call.args = args;
  return node;
}
ASTNode *createParam(char *type, char *name) {
  ASTNode *node = malloc(sizeof(ASTNode));
  node->type = NODE_PARAM;
  node->data.param.type = type;
  node->data.param.name = name;
  return node;
}
:qASTNode *createArgList(ASTNode *arg, ASTNode *next) {
  ASTNode *node = malloc(sizeof(ASTNode));
  node->type = NODE_ARG_LIST;
  node->data.list.item = arg;
  node->data.list.next = next;
  return node;
}
ASTNode *createReturn(ASTNode *expr) {
  ASTNode *node = malloc(sizeof(ASTNode));
  node->type = NODE_RETURN;
  node->data.return_expr = expr;
  return node;
}
ASTNode *createFuncList(ASTNode *func, ASTNode *next) {
  ASTNode* node  = malloc(sizeof(ASTNode));
  node->type = NODE_FUNC_LIST;
  node->data.list.item = func;
  node->data.list.next = next;
  return node;
}

/* Display the AST structure (for debugging and education) */
void printAST(ASTNode *node, int level) {
  if (!node)
    return;

  /* Indent based on tree depth */
  for (int i = 0; i < level; i++)
    printf("  ");

  /* Print node based on its type */
  switch (node->type) {
  case NODE_NUM:
    printf("NUM: %d\n", node->data.num);
    break;
  case NODE_VAR:
    printf("VAR: %s\n", node->data.name);
    break;
  case NODE_BINOP:
    printf("BINOP: %c\n", node->data.binop.op);
    printAST(node->data.binop.left, level + 1);
    printAST(node->data.binop.right, level + 1);
    break;
  case NODE_DECL:
    printf("DECL: %s\n", node->data.name);
    break;
  case NODE_CHAR_DECL:
    printf("CHAR DECL: %s\n", node->data.name);
    break;
  case NODE_ASSIGN:
    printf("ASSIGN: %s\n", node->data.assign.var);
    printAST(node->data.assign.value, level + 1);
    break;
  case NODE_PRINT:
    printf("PRINT\n");
    printAST(node->data.expr, level + 1);
    break;
  case NODE_STMT_LIST:
    /* Print statements in sequence at same level */
    printAST(node->data.stmtlist.stmt, level);
    printAST(node->data.stmtlist.next, level);
    break;
  case NODE_ARRAY_DECL:
    printf("%*sARRAY_DECL: %s[%d]\n", level * 2, "", node->data.array_decl.name,
           node->data.array_decl.size);
    break;
  case NODE_ARRAY_ASSIGN:
    printf("%*sARRAY_ASSIGN: %s[] =\n", level * 2, "",
           node->data.array_assign.name);
    printf("%*sIndex:\n", level * 2, "");
    printAST(node->data.array_assign.index, level + 1);
    printf("%*sValue:\n", level * 2, "");
    printAST(node->data.array_assign.value, level + 1);
    break;
  case NODE_ARRAY_ACCESS:
    printf("%*sIndex:\n", level * 2, "");
    printAST(node->data.array_access.index, level + 1);
    break;
  case NODE_STRUCT_DEF:
    printf("STRUCT: %s\n", node->data.struct_def.name);
    printAST(node->data.struct_def.fields, level + 1);
    break;
  case NODE_STRUCT_FIELD:
    printf("%*sFIELD (%s): %s\n", level * 2, "",
           node->data.struct_field.dataType == TYPE_CHAR ? "char" : "int",
           node->data.struct_field.fieldName);
    printAST(node->data.struct_field.next, level);
    break;
  case NODE_STRUCT_VAR_DECL:
    printf("STRUCT VAR: %s %s\n", node->data.struct_var_decl.structName,
           node->data.struct_var_decl.varName);
    break;
  case NODE_STRUCT_ASSIGN:
    printf("STRUCT ASSIGN: %s.%s\n", node->data.struct_assign.varName,
           node->data.struct_assign.fieldName);
    printAST(node->data.struct_assign.value, level + 1);
    break;
  case NODE_STRUCT_ACCESS:
    printf("STRUCT ACCESS: %s.%s\n", node->data.struct_access.varName,
           node->data.struct_access.fieldName);
    break;
    case NODE_FUNC_DECL: 


    printf("FUNCTION DECLARATION: %s"
  default:
    break;
  }
}
