#ifndef AST_H
#define AST_H

/* ABSTRACT SYNTAX TREE (AST)
 * The AST is an intermediate representation of the program structure
 * It represents the hierarchical syntax of the source code
 * Each node represents a construct in the language
 */

/* Primitive types for variables */
typedef enum DataType { TYPE_INT, TYPE_CHAR, TYPE_VOID } DataType;

/* NODE TYPES - Different kinds of AST nodes in our language */
typedef enum {
  NODE_NUM,       /* Numeric literal (e.g., 42) */
  NODE_VAR,       /* Variable reference (e.g., x) */
  NODE_BINOP,     /* Binary operation (e.g., x + y) */
  NODE_DECL,      /* Variable declaration (e.g., int x) */
  NODE_ASSIGN,    /* Assignment statement (e.g., x = 10) */
  NODE_PRINT,     /* Print statement (e.g., print(x)) */
  NODE_STMT_LIST, /* List of statements (program structure) */
  /* Array Node Types */
  NODE_ARRAY_DECL,   /* Array declration (e.g., int x[10]) */
  NODE_ARRAY_ASSIGN, /* Array assignment (e.g., x[5] = 10) */
  NODE_ARRAY_ACCESS, /* Array access (e.g., x[5]) */
  /* Char Node Types */
  NODE_CHAR_DECL,
  /* Struct Node Types */
  NODE_STRUCT_DEF,      /* Struct type definition */
  NODE_STRUCT_FIELD,    /* Field inside a struct definition */
  NODE_STRUCT_VAR_DECL, /* Variable declaration of a struct type */
  NODE_STRUCT_ASSIGN,   /* Assignment to a struct field */
  NODE_STRUCT_ACCESS,   /* Accessing a struct field */
  /* Function Node Types */
  NODE_FUNC_DECL,
  NODE_FUNC_CALL,
  NODE_PARAM,
  NODE_PARAM_LIST,
  NODE_ARG_LIST,
  NODE_RETURN,
  NODE_FUNC_LIST,
  NODE_BLOCK
} NodeType;

/* AST NODE STRUCTURE
 * Uses a union to efficiently store different node data
 * Only the relevant fields for each node type are used
 */
typedef struct ASTNode {
  NodeType type; /* Identifies what kind of node this is */

  /* Union allows same memory to store different data types */
  union {
    /* Literal number value (NODE_NUM) */
    int num;

    /* Variable or declaration name (NODE_VAR, NODE_DECL, NODE_CHAR_DECL) */
    char *name;
    /* int value; */ /* For potential future use in declarations with assignment
                      */

    /* Binary operation structure (NODE_BINOP) */
    struct {
      char op;               /* Operator character ('+', '-', ...) */
      struct ASTNode *left;  /* Left operand */
      struct ASTNode *right; /* Right operand */
    } binop;

    /* Assignment structure (NODE_ASSIGN) */
    struct {
      char *var;             /* Variable being assigned to */
      struct ASTNode *value; /* Expression being assigned */
    } assign;

    /* Print expression (NODE_PRINT) */
    struct ASTNode *expr;

    /* Statement list structure (NODE_STMT_LIST) */
    struct {
      struct ASTNode *stmt; /* Current statement */
      struct ASTNode *next; /* Rest of the list */
    } stmtlist;

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
      char *name;             /* Struct type name */
      struct ASTNode *fields; /* Linked list of field nodes */
    } struct_def;

    struct {
      char *fieldName;      /* Field identifier */
      DataType dataType;    /* Field primitive type */
      struct ASTNode *next; /* Next field in definition */
    } struct_field;

    struct {
      char *structName; /* Struct type name */
      char *varName;    /* Variable identifier */
    } struct_var_decl;

    struct {
      char *varName;         /* Struct variable name */
      char *fieldName;       /* Field being assigned */
      struct ASTNode *value; /* Value expression */
    } struct_assign;

    struct {
      char *varName;   /* Struct variable name */
      char *fieldName; /* Field being accessed */
    } struct_access;

    /* Function Node Types */
    struct {
      char *returnType;
      char *name;
      struct ASTNode *params;
      struct ASTNode *body;
    } func_decl;

    struct {
      char *name;
      struct ASTNode *args;
    } func_call;

    struct {
      char *type;
      char *name;
    } param;

    struct {
      struct ASTNode *item;
      struct ASTNode *next;
    } list;

    struct ASTNode *return_expr;

  } data;
} ASTNode;

/* AST CONSTRUCTION FUNCTIONS
 * These functions are called by the parser to build the tree
 */
ASTNode *createNum(int value);  /* Create number node */
ASTNode *createVar(char *name); /* Create variable node */
ASTNode *createBinOp(char op, ASTNode *left,
                     ASTNode *right); /* Create binary op node */
ASTNode *createDecl(char *name);
/* ASTNOde* createDeclWithAssgn(char* name, int value) */ /* Create
                                                             declaration node
                                                           */
ASTNode *createCharDecl(char *name);
ASTNode *createAssign(char *var, ASTNode *value); /* Create assignment node */
ASTNode *createPrint(ASTNode *expr);              /* Create print node */
ASTNode *createStmtList(ASTNode *stmt1,
                        ASTNode *stmt2); /* Create statement list */

ASTNode *createArrayDecl(char *name, int size, DataType dataType);
ASTNode *createArrayAssign(char *name, ASTNode *index, ASTNode *value);
ASTNode *createArrayAccess(char *name, ASTNode *index);
ASTNode *createStructDef(char *name, ASTNode *fields);
ASTNode *createStructField(char *name, DataType dataType);
ASTNode *appendStructField(ASTNode *list, ASTNode *field);
ASTNode *createStructVarDecl(char *structName, char *varName);
ASTNode *createStructAssign(char *varName, char *fieldName, ASTNode *value);
ASTNode *createStructAccess(char *varName, char *fieldName);

ASTNode *createFuncDecl(char *returnType, char *name, ASTNode *params,
                        ASTNode *body);
ASTNode *createFuncCall(char *name, ASTNode *args);
ASTNode *createParam(char *type, char *name);
ASTNode *createArgList(ASTNode *arg, ASTNode *next);
ASTNode *createReturn(ASTNode *expr);
ASTNode *createFuncList(ASTNode *func, ASTNode *next);
/* AST DISPLAY FUNCTION */
void printAST(ASTNode *node, int level); /* Pretty-print the AST */

#endif
