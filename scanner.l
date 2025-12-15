%{
/* LEXICAL ANALYZER (SCANNER)
 * This is the first phase of compilation - breaking input into tokens
 * Flex generates a scanner from these rules that reads character by character
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"  /* Token definitions from Bison */
#include "errors.h"

extern YYLTYPE yylloc;

#define YY_USER_ACTION                                                        \
  do {                                                                       \
    yylloc.first_line = yylineno;                                            \
    yylloc.last_line = yylineno;                                             \
    yylloc.first_column = 0;                                                 \
    yylloc.last_column = 0;                                                  \
  } while (0);
%}

/* Flex options to suppress warnings for unused functions */
%option nounput
%option noinput
%option yylineno

/* Dedicated start condition to skip multi-line comment bodies without
 * polluting the main DFA. */
%x COMMENT

%%

"int"           { return KW_INT; }
"print"         { return KW_PRINT; }

"char"          { return KW_CHAR; }
"float"         { return KW_FLOAT; }
"bool"          { return KW_BOOL; }

"struct"        { return KW_STRUCT; }

"return"        { return KW_RETURN; }
"void"          { return KW_VOID; }

"if"            { return KW_IF; }
"else"          { return KW_ELSE; }
"switch"        { return KW_SWITCH; }
"case"          { return KW_CASE; }
"default"       { return KW_DEFAULT; }
"break"         { return KW_BREAK; }
"goto"          { return KW_GOTO; }
"continue"      { return KW_CONTINUE; }
"true"          { return KW_TRUE; }
"false"         { return KW_FALSE; }

"while"         { return KW_WHILE; }

[a-zA-Z_][a-zA-Z0-9_]* { 
    yylval.str = strdup(yytext);
    noteKeywordCandidate(yytext, yylineno);
    return ID; 
}

[0-9][a-zA-Z_][a-zA-Z0-9_]* {
    reportLexicalError(yylineno,
                       "illegal identifier '%s' (identifiers must start with a letter or underscore)",
                       yytext);
}

[0-9]+\.[0-9]*([eE][+-]?[0-9]+)? { 
    yylval.fnum = atof(yytext);
    return LITERAL_FLOAT;
}

[0-9]*\.[0-9]+([eE][+-]?[0-9]+)? {
    yylval.fnum = atof(yytext);
    return LITERAL_FLOAT;
}

[0-9]+          { 
    yylval.num = atoi(yytext);
    return LITERAL_NUM; 
}

\'(\\.|[^\\'\n])\' {
  /* Character literal: 
    supports '\n', '\r', '\t', '\0', '\\', '\'', and printable chars.
  */

  int c;
  if (yytext[1] == '\\') {
    switch (yytext[2]) {
      case 'n': c = '\n'; break;
      case 'r': c = '\r'; break;
      case 't': c = '\t'; break;
      case '0': c = '\0'; break;
      case '\\': c = '\\'; break;
      case '\'': c = '\''; break;
      default: c = yytext[2]; break; /* Fall back for other escape characters*/
    }
    } else { c = yytext[1];}
  yylval.num = c;
  return LITERAL_CHAR;
  }

"+"             { return '+'; }
"-"             { return '-'; }
"*"             { return '*'; }
"//"[^\n]*     { /* skip single-line comment */ }
"/*"            { BEGIN(COMMENT); }

<COMMENT>"*/"   { BEGIN(INITIAL); }
<COMMENT>\n     { }
<COMMENT>.      { }

"/"             { return '/'; }
"="             { return '='; }
";"             { return ';'; }
"("             { return '('; }
")"             { return ')'; }
"["             { return '['; }
"]"             { return ']'; }
"{"             { return '{'; }
"}"             { return '}'; }
"."             { return '.'; }
","             { return ','; }
"?"             { return '?'; }
":"             { return ':'; }

">"             { return '>'; }
"<"             { return '<'; }
">="            { return GEQ; }
"<="            { return LEQ; }
"=="            { return EQ; }
"!="            { return NEQ; }
"&&"            { return AND; }
"||"            { return OR; }
"!"             { return NOT; }

[ \t\r]+       { }

\n              { }

.               { reportLexicalError(yylineno,
                                   "unknown character '%c'", *yytext); }

%%

/* Required by Flex - signals end of input */
int yywrap() {
    return 1;  /* 1 means no more input files */
}
