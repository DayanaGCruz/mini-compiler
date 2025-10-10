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
    char* str;              /* For identifiers */
    struct ASTNode* node;   /* For AST nodes */
    DataType dataType;      /* For data type flag on identifiers and arrays */ 
}

/* TOKEN DECLARATIONS with their semantic value types */
%token <num> LITERAL_NUM LITERAL_CHAR

/* Number token carries an integer value */
%token <str> ID         /* Identifier token carries a string */
%token KW_INT KW_PRINT KW_CHAR KW_STRUCT        /* Keywords have no semantic value */

/* NON-TERMINAL TYPES - Define what type each grammar rule returns */
%type <node> program stmt_list stmt decl assign expr print_stmt struct_decl
              struct_field_list struct_field struct_var_decl struct_assign 
              arg_list return_stmt param param_list func_decl func_list
%type <dataType> type

/* OPERATOR PRECEDENCE AND ASSOCIATIVITY */
%left '+' '-'  /* Addition and subtraction are left-associative */

%%

/* GRAMMAR RULES - Define the structure of our language */

/* PROGRAM RULE - Entry point of our grammar */
program:
    func_list  { 
        $$ = $1;     }
    ;


func_list:  
    func_decl { $$ = $1;}
    | func_list func_decl { $$ = createFuncList($1, $2); }
    ;

func_decl: 
         type ID '(' param_list ')' '{' stmt_list '}' {
          $$ = createFuncDecl($1, $2, $4, $7);
        }
        | type ID '(' ')' '{' stmt_list '}' {
          $$ = createFuncDecl($1, $2, NULL, $6);
        }
        ;

param_list: 
    param { $$ = $1; }
    | param_list ',' param { $$ = createParamList($1, $3); }
    ;

param: 
     type ID { $$ = createParam($1, $2); }
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
    ;

/*Simple types */

type
    : KW_INT { $$ = TYPE_INT;  /* int */}
    | KW_CHAR { $$ = TYPE_CHAR; /* char */}
    | KW_VOID { $$ = TYPE_VOID; /* void */}
    ;

/* DECLARATION RULE - "int x;" */
decl
    : type ID ';' { 
      declareIdentifier($2, @2.first_line);
      if($1 == TYPE_INT) { /* int */
          $$ = createDecl($2);
      }  else {       /* char */
        $$ = createCharDecl($2);
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
    LITERAL_NUM { 
        /* Literal number */
        $$ = createNum($1);  /* Create leaf node with number value */
    }
    | LITERAL_CHAR {
        /* Literal char */
        $$ = createNum($1);
    }
    | ID { 
        referenceIdentifier($1, @1.first_line);
        /* Variable reference */
        $$ = createVar($1);  /* Create leaf node with variable name */
        free($1);            /* Free the identifier string */
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
    | ID '(' ')' { $$ = createFuncCall($1, NULL);}
    | expr '+' expr { 
        /* Addition operation - builds binary tree */
        $$ = createBinOp('+', $1, $3);  /* Left child, op, right child */
    }
    | expr '-' expr {
        /* Subtraction operation - builds binary tree */
        $$ = createBinOp('-', $1, $3);
    }
    | '(' expr ')' { $$ = $2; }
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
