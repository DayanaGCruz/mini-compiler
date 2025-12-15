%{
/* SYNTAX ANALYZER (PARSER)
 * This is the second phase of compilation - checking grammar rules
 * Bison generates a parser that builds an Abstract Syntax Tree (AST)
 * The parser uses tokens from the scanner to verify syntax is correct
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "errors.h"

/* External declarations for lexer interface */
extern int yylex();      /* Get next token from scanner */
extern int yyparse();    /* Parse the entire input */
extern FILE* yyin;       /* Input file handle */

void yyerror(const char* s);  /* Error handling function */
ASTNode* root = NULL;          /* Root of the Abstract Syntax Tree */
%}

%code requires {
#include "ast.h"
}

%define parse.error verbose
%locations

/* SEMANTIC VALUES UNION
 * Defines possible types for tokens and grammar symbols
 * This allows different grammar rules to return different data types
 */
%union {
    int num;                /* For integer literals & char literal codepoints */
    double fnum;            /* For floating-point literals */
    char* str;              /* For identifiers */
    struct ASTNode* node;   /* For AST nodes */
    DataType dataType;      /* For data type flag on identifiers and arrays */ 
}

/* TOKEN DECLARATIONS with their semantic value types */
%token <num> LITERAL_NUM LITERAL_CHAR
%token <fnum> LITERAL_FLOAT

/* Number token carries an integer value */
%token <str> ID         /* Identifier token carries a string */
%token KW_INT KW_PRINT KW_CHAR KW_FLOAT KW_BOOL KW_STRUCT KW_VOID KW_RETURN
%token KW_IF KW_ELSE KW_SWITCH KW_CASE KW_DEFAULT KW_BREAK KW_GOTO KW_CONTINUE KW_WHILE
%token KW_TRUE KW_FALSE
%token AND OR NOT EQ NEQ LEQ GEQ   /* Multi-character operators */

/* NON-TERMINAL TYPES - Define what type each grammar rule returns */
%type <node> program stmt_list stmt decl assign expr print_stmt struct_decl
              struct_field_list struct_field struct_var_decl struct_assign 
              arg_list return_stmt expr_stmt param param_list func_decl
              block if_stmt switch_stmt switch_case_list switch_item
              case_stmt_body while_stmt top_level_list top_level_item
%type <dataType> type

/* OPERATOR PRECEDENCE AND ASSOCIATIVITY */
%right '?' ':'
%left OR
%left AND
%left EQ NEQ
%left '>' '<' GEQ LEQ
%left '+' '-'
%left '*' '/'
%right NOT
%right UMINUS
%nonassoc LOWER_THAN_ELSE
%nonassoc KW_ELSE

%%

/* GRAMMAR RULES - Define the structure of our language */

/* PROGRAM RULE - Entry point of our grammar */
program:
    top_level_list  { 
        root = $1;
        $$ = $1;     }
    ;

/* top_level_list folds function and struct definitions into one list so the
 * entire translation unit appears as a single AST node downstream. */
top_level_list:  
    top_level_item { $$ = $1;}
    | top_level_list top_level_item { $$ = createFuncList($1, $2); }
    ;

top_level_item:
    func_decl { $$ = $1; }
    | struct_decl { $$ = $1; }
    | decl { $$ = $1; }
    | struct_var_decl { $$ = $1; }
    ;

/* Function declarations push a new identifier scope for parameters plus local
 * declarations and pop it once the body has been parsed. */
func_decl: 
         type ID '(' { enterIdentifierScope(); } param_list ')' '{' stmt_list '}' {
          exitIdentifierScope();
          $$ = createFuncDecl($1, $2, $5, $8);
        }
        | type ID '(' { enterIdentifierScope(); } ')' '{' stmt_list '}' {
          exitIdentifierScope();
          $$ = createFuncDecl($1, $2, NULL, $7);
        }
        ;

param_list: 
    KW_VOID { $$ = NULL; }
    | param { $$ = $1; }
    | param_list ',' param { $$ = createParamList($1, $3); }
    ;

param: 
     type ID {
       declareIdentifier($2, @2.first_line);
       $$ = createParam($1, $2);
       free($2);
     }
     | type ID '[' LITERAL_NUM ']' {
       declareIdentifier($2, @2.first_line);
       $$ = createArrayParam($1, $2, $4);
       free($2);
     }
     | type ID '[' ']' {
       declareIdentifier($2, @2.first_line);
       $$ = createArrayParam($1, $2, 0);
       free($2);
     }
     | KW_STRUCT ID ID {
       referenceStructType($2, @2.first_line);
       declareIdentifier($3, @3.first_line);
       $$ = createStructParam($2, $3);
       free($2);
       free($3);
     }
     ;
/* STATEMENT LIST - Handles multiple statements */
stmt_list:
    stmt { 
        /* Base case: single statement */
        $$ = $1;  /* Pass the statement up as-is */
    }
    | stmt_list stmt { 
        /* Recursive case: list followed by another statement */
        $$ = createStmtList($1, $2);  /* Build linked list of statements */
    }
    ;

/* STATEMENT TYPES - The three kinds of statements we support */
stmt:
    decl        /* Variable declaration */
    | assign    /* Assignment statement */
    | print_stmt /* Print statement */
    | struct_decl /* Struct type definition */
    | struct_var_decl /* Struct variable declaration */
    | struct_assign /* Struct field assignment */
    | return_stmt
    | expr_stmt
    | if_stmt
    | switch_stmt
    | block
    | KW_BREAK ';' { $$ = createBreak(); }
    | while_stmt
    ;

block:
    '{' stmt_list '}' { $$ = createBlock($2); }
    | '{' '}' { $$ = createBlock(NULL); }
    ;

if_stmt:
    KW_IF '(' expr ')' block %prec LOWER_THAN_ELSE { $$ = createIf($3, $5, NULL); }
    | KW_IF '(' expr ')' block KW_ELSE block { $$ = createIf($3, $5, $7); }
    | KW_IF '(' expr ')' block KW_ELSE if_stmt { $$ = createIf($3, $5, $7); }
    ;

switch_stmt:
    KW_SWITCH '(' expr ')' '{' '}' {
      $$ = createSwitch($3, NULL, NULL);
    }
    | KW_SWITCH '(' expr ')' '{' switch_case_list '}' {
      ASTNode *cases = $6;
      ASTNode *defaultNode = NULL;
      for (ASTNode *curr = cases; curr; curr = curr->data.case_stmt.next) {
        if (curr->data.case_stmt.isDefault) {
          defaultNode = curr;
          break;
        }
      }
      $$ = createSwitch($3, cases, defaultNode);
    }
    ;

switch_case_list:
    switch_case_list switch_item { $$ = appendCase($1, $2); }
    | switch_item { $$ = $1; }
    ;

switch_item:
    KW_CASE expr ':' case_stmt_body { $$ = createCase($2, $4); }
    | KW_DEFAULT ':' case_stmt_body { $$ = createDefaultCase($3); }
    ;

case_stmt_body:
    stmt_list { $$ = $1; }
    | /* empty */ { $$ = NULL; }
    ;

while_stmt:
    KW_WHILE '(' expr ')' block {
      $$ = createWhile($3, $5);
    }
    ;
expr_stmt:
    expr ';' { $$ = createExprStmt($1); }
    ;

/*Simple types */

type
    : KW_INT { $$ = TYPE_INT;  /* int */}
    | KW_CHAR { $$ = TYPE_CHAR; /* char */}
    | KW_FLOAT { $$ = TYPE_FLOAT; /* float */}
    | KW_BOOL { $$ = TYPE_BOOL; /* bool */}
    | KW_VOID { $$ = TYPE_VOID; /* void */}
    ;

/* DECLARATION RULE - "int x;" */
decl
    : type ID ';' { 
      declareIdentifier($2, @2.first_line);
      if ($1 == TYPE_INT) {
        $$ = createDecl($2);
      } else if ($1 == TYPE_CHAR) {
        $$ = createCharDecl($2);
      } else if ($1 == TYPE_FLOAT) {
        $$ = createFloatDecl($2);
      } else if ($1 == TYPE_BOOL) {
        $$ = createBoolDecl($2);
      } else {
        $$ = createDecl($2);
      }
    }
    | type ID '[' LITERAL_NUM ']' ';' {
      declareIdentifier($2, @2.first_line);
      $$ = createArrayDecl($2, $4, $1);
      free($2);
    }
   ;

struct_decl
    : KW_STRUCT ID '{' struct_field_list '}' ';' {
        declareStructType($2, @2.first_line);
        $$ = createStructDef($2, $4);
        free($2);
    }
    ;

struct_field_list
    : /* empty */ { $$ = NULL; }
    | struct_field_list struct_field { $$ = appendStructField($1, $2); }
    ;

struct_field
    : type ID ';' {
        $$ = createStructField($2, $1);
        free($2);
    }
    ;

struct_var_decl
    : KW_STRUCT ID ID ';' {
        referenceStructType($2, @2.first_line);
        declareIdentifier($3, @3.first_line);
        $$ = createStructVarDecl($2, $3);
        free($2);
        free($3);
    }
    ;

struct_assign
    : ID '.' ID '=' expr ';' {
        referenceIdentifier($1, @1.first_line);
        $$ = createStructAssign($1, $3, $5);
        free($1);
        free($3);
    }
    ;

arg_list: 
    expr { $$ = $1;}
    | arg_list ',' expr { $$ = createArgList($1, $3); }
    ;
/* ASSIGNMENT RULE - "x = expr;" */
assign:
    ID '=' expr ';' { 
        referenceIdentifier($1, @1.first_line);
        /* Create assignment node with variable name and expression */
        $$ = createAssign($1, $3);  /* $1 = ID, $3 = expr */
        free($1);                   /* Free the identifier string */
    }
    | ID '[' expr ']' '=' expr ';' {
      referenceIdentifier($1, @1.first_line);
      $$ = createArrayAssign($1, $3, $6);
      free($1);
    }
    ;

/* EXPRESSION RULES - Build expression trees */
expr:
    LITERAL_NUM { $$ = createNum($1); }
    | LITERAL_FLOAT { $$ = createFloat($1); }
    | LITERAL_CHAR { $$ = createNum($1); }
    | KW_TRUE { $$ = createBoolLiteral(1); }
    | KW_FALSE { $$ = createBoolLiteral(0); }
    | ID {
        referenceIdentifier($1, @1.first_line);
        $$ = createVar($1);
        free($1);
    }
    | ID '.' ID {
        referenceIdentifier($1, @1.first_line);
        $$ = createStructAccess($1, $3);
        free($1);
        free($3);
    }
    | ID '[' expr ']' {
        referenceIdentifier($1, @1.first_line);
        $$ = createArrayAccess($1, $3);
        free($1);
    }
    | ID '(' arg_list ')' { $$ = createFuncCall($1, $3); }
    | ID '(' ')' { $$ = createFuncCall($1, NULL); }
    | expr '+' expr { $$ = createBinOp(OP_ADD, $1, $3); }
    | expr '-' expr { $$ = createBinOp(OP_SUB, $1, $3); }
    | expr '*' expr { $$ = createBinOp(OP_MUL, $1, $3); }
    | expr '/' expr { $$ = createBinOp(OP_DIV, $1, $3); }
    | expr '>' expr { $$ = createBinOp(OP_GT, $1, $3); }
    | expr '<' expr { $$ = createBinOp(OP_LT, $1, $3); }
    | expr GEQ expr { $$ = createBinOp(OP_GE, $1, $3); }
    | expr LEQ expr { $$ = createBinOp(OP_LE, $1, $3); }
    | expr EQ expr { $$ = createBinOp(OP_EQ, $1, $3); }
    | expr NEQ expr { $$ = createBinOp(OP_NEQ, $1, $3); }
    | expr AND expr { $$ = createBinOp(OP_AND, $1, $3); }
    | expr OR expr { $$ = createBinOp(OP_OR, $1, $3); }
    | NOT expr { $$ = createUnaryOp(UNOP_NOT, $2); }
    | expr '?' expr ':' expr { $$ = createConditionalExpr($1, $3, $5); }
    | '(' expr ')' { $$ = $2; }
    | '-' expr %prec UMINUS { $$ = createBinOp(OP_SUB, createNum(0), $2); }
    ;

return_stmt: 
    KW_RETURN expr ';' { $$ = createReturn($2); }
    | KW_RETURN ';' { $$ = createReturn(NULL);}
    ;

/* PRINT STATEMENT - "print(expr);" */
print_stmt:
    KW_PRINT '(' expr ')' ';' { 
        /* Create print node with expression to print */
        $$ = createPrint($3);  /* $3 is the expression inside parens */
    }
    ;

%%

/* ERROR HANDLING - Called by Bison when syntax error detected */
void yyerror(const char* s) {
    extern YYLTYPE yylloc;
    int line = yylloc.first_line;
    const char *identifier = NULL;
    const char *keyword = NULL;

    if (fetchKeywordSuggestion(line, &identifier, &keyword)) {
        reportSyntaxError(line,
                          "identifier '%s' used where keyword expected. Did you mean '%s'?",
                          identifier, keyword);
        clearKeywordSuggestion();
        return;
    }

    clearKeywordSuggestion();

    if (line <= 0) {
        reportSyntaxError(0, "%s", s);
    } else {
        reportSyntaxError(line, "%s", s);
    }
}
