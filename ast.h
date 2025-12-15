#ifndef AST_H
#define AST_H

/* ABSTRACT SYNTAX TREE (AST)
 * The AST is an intermediate representation of the program structure. Each
 * node is a typed record that describes one construct in the C-Minus language
 * (expressions, statements, declarations, etc.). The parser is responsible for
 * instantiating these nodes and downstream stages simply consume this data
 * structure, so consolidating everything in one header clarifies how the
 * compiler communicates between phases.
 */

typedef enum DataType {
  TYPE_INT,
  TYPE_CHAR,
  TYPE_FLOAT,
  TYPE_BOOL,
  TYPE_VOID
} DataType;

/* NodeType enumerates every concrete AST variant we know how to build. The
 * order is not semantically relevant, but grouping similar concepts keeps the
 * tree printer compact. */
typedef enum {
  OP_ADD,
  OP_SUB,
  OP_MUL,
  OP_DIV,
  OP_LT,
  OP_LE,
  OP_GT,
  OP_GE,
  OP_EQ,
  OP_NEQ,
  OP_AND,
  OP_OR
} BinaryOp;

typedef enum {
  UNOP_NOT
} UnaryOp;

typedef enum {
  NODE_NUM,
  NODE_FLOAT,
  NODE_BOOL,
  NODE_VAR,
  NODE_BINOP,
  NODE_UNARY_OP,
  NODE_DECL,
  NODE_CHAR_DECL,
  NODE_FLOAT_DECL,
  NODE_BOOL_DECL,
  NODE_ASSIGN,
  NODE_PRINT,
  NODE_EXPR_STMT,
  NODE_STMT_LIST,
  NODE_BLOCK,
  NODE_IF,
  NODE_SWITCH,
  NODE_CASE,
  NODE_BREAK,
  NODE_CONDITIONAL,
  NODE_ARRAY_DECL,
  NODE_ARRAY_ASSIGN,
  NODE_ARRAY_ACCESS,
  NODE_STRUCT_DEF,
  NODE_STRUCT_FIELD,
  NODE_STRUCT_VAR_DECL,
  NODE_STRUCT_ASSIGN,
  NODE_STRUCT_ACCESS,
  NODE_FUNC_DECL,
  NODE_FUNC_CALL,
  NODE_PARAM,
  NODE_PARAM_LIST,
  NODE_ARG_LIST,
  NODE_RETURN,
  NODE_FUNC_LIST,
  NODE_WHILE
} NodeType;

/* ASTNode is the single representation used everywhere in the compiler. The
 * `type` tag tells consumers which union member inside `data` is valid, and the
 * `line` allows every phase to keep source locations attached to diagnostics. */
typedef struct ASTNode {
  NodeType type;
  int line;

  union {
    int num;
    double fnum;
    int boolValue;
    char *name;

    struct {
      BinaryOp op;
      struct ASTNode *left;
      struct ASTNode *right;
    } binop;

    struct {
      UnaryOp op;
      struct ASTNode *expr;
    } unary;

    struct {
      char *var;
      struct ASTNode *value;
    } assign;

    struct ASTNode *expr;

    struct {
      struct ASTNode *stmt;
      struct ASTNode *next;
    } stmtlist;

    struct ASTNode *block_items;

    struct {
      char *name;
      int size;
      DataType dataType;
    } array_decl;

    struct {
      char *name;
      struct ASTNode *index;
      struct ASTNode *value;
    } array_assign;

    struct {
      char *name;
      struct ASTNode *index;
    } array_access;

    struct {
      char *name;
      struct ASTNode *fields;
    } struct_def;

    struct {
      char *fieldName;
      DataType dataType;
      struct ASTNode *next;
    } struct_field;

    struct {
      char *structName;
      char *varName;
    } struct_var_decl;

    struct {
      char *varName;
      char *fieldName;
      struct ASTNode *value;
    } struct_assign;

    struct {
      char *varName;
      char *fieldName;
    } struct_access;

    struct {
      DataType returnType;
      char *name;
      struct ASTNode *params;
      struct ASTNode *body;
    } func_decl;

    struct {
      char *name;
      struct ASTNode *args;
    } func_call;

    struct {
      DataType type;
      char *name;
      int isArray;
      int arraySize;
      int isStruct;
      char *structType;
    } param;

    struct {
      struct ASTNode *item;
      struct ASTNode *next;
    } list;

    struct ASTNode *return_expr;

    struct {
      struct ASTNode *condition;
      struct ASTNode *thenBranch;
      struct ASTNode *elseBranch;
    } if_stmt;

    struct {
      struct ASTNode *condition;
      struct ASTNode *trueExpr;
      struct ASTNode *falseExpr;
    } conditional;

    struct {
      struct ASTNode *expr;
      struct ASTNode *cases;
      struct ASTNode *defaultCase;
    } switch_stmt;

    struct {
      int isDefault;
      struct ASTNode *valueExpr;
      struct ASTNode *statements;
      struct ASTNode *next;
      char *label;
    } case_stmt;

    struct {
      struct ASTNode *condition;
      struct ASTNode *body;
    } while_stmt;

  } data;
} ASTNode;

ASTNode *createNum(int value);
ASTNode *createFloat(double value);
ASTNode *createBoolLiteral(int value);
ASTNode *createVar(char *name);
ASTNode *createBinOp(BinaryOp op, ASTNode *left, ASTNode *right);
ASTNode *createUnaryOp(UnaryOp op, ASTNode *expr);
ASTNode *createDecl(char *name);
ASTNode *createCharDecl(char *name);
ASTNode *createFloatDecl(char *name);
ASTNode *createBoolDecl(char *name);
ASTNode *createAssign(char *var, ASTNode *value);
ASTNode *createPrint(ASTNode *expr);
ASTNode *createExprStmt(ASTNode *expr);
ASTNode *createStmtList(ASTNode *stmt1, ASTNode *stmt2);
ASTNode *createBlock(ASTNode *stmts);

ASTNode *createArrayDecl(char *name, int size, DataType dataType);
ASTNode *createArrayAssign(char *name, ASTNode *index, ASTNode *value);
ASTNode *createArrayAccess(char *name, ASTNode *index);
ASTNode *createStructDef(char *name, ASTNode *fields);
ASTNode *createStructField(char *name, DataType dataType);
ASTNode *appendStructField(ASTNode *list, ASTNode *field);
ASTNode *createStructVarDecl(char *structName, char *varName);
ASTNode *createStructAssign(char *varName, char *fieldName, ASTNode *value);
ASTNode *createStructAccess(char *varName, char *fieldName);

ASTNode *createFuncDecl(DataType returnType, char *name, ASTNode *params,
                        ASTNode *body);
ASTNode *createFuncCall(char *name, ASTNode *args);
ASTNode *createParam(DataType type, char *name);
ASTNode *createArrayParam(DataType type, char *name, int size);
ASTNode *createStructParam(char *structName, char *varName);
ASTNode *createParamList(ASTNode *param, ASTNode *next);
ASTNode *createArgList(ASTNode *arg, ASTNode *next);
ASTNode *createReturn(ASTNode *expr);
ASTNode *createFuncList(ASTNode *func, ASTNode *next);

ASTNode *createIf(ASTNode *cond, ASTNode *thenBranch, ASTNode *elseBranch);
ASTNode *createSwitch(ASTNode *expr, ASTNode *cases, ASTNode *defaultCase);
ASTNode *createCase(ASTNode *valueExpr, ASTNode *statements);
ASTNode *createDefaultCase(ASTNode *statements);
ASTNode *appendCase(ASTNode *cases, ASTNode *newCase);
ASTNode *createBreak(void);
ASTNode *createConditionalExpr(ASTNode *cond, ASTNode *trueExpr,
                               ASTNode *falseExpr);

ASTNode *createWhile(ASTNode *cond, ASTNode *body);

void printAST(ASTNode *node, int level);

#endif
