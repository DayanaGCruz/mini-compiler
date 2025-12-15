#ifndef ERRORS_H
#define ERRORS_H

#include <stdarg.h>

/* Centralized diagnostics helper. The parser, lexer, and semantic analysis
 * stages do not print directly; instead they call into this module so we can
 * count errors, attach suggestions, and expose scope/identifier dumps in one
 * place. */

typedef enum {
  ERROR_LEXICAL,
  ERROR_SYNTAX,
  ERROR_SEMANTIC
} ErrorCategory;

void resetErrorState(void);
void reportLexicalError(int line, const char *fmt, ...);
void reportSyntaxError(int line, const char *fmt, ...);
void reportSemanticError(int line, const char *fmt, ...);
void reportTypeMismatchWarning(int line, const char *fromType,
                               const char *toType,
                               const char *context);

int declareIdentifier(const char *name, int line);
int referenceIdentifier(const char *name, int line);
int declareStructType(const char *name, int line);
int referenceStructType(const char *name, int line);

/* Keyword suggestions are queued when the lexer spots an identifier that looks
 * suspiciously similar to a keyword (e.g., `fi` vs `if`). The parser can then
 * surface a targeted message on the exact line that triggered the error. */
void noteKeywordCandidate(const char *name, int line);
int fetchKeywordSuggestion(int line, const char **identifier,
                           const char **keyword);
void clearKeywordSuggestion(void);

void enterIdentifierScope(void);
void exitIdentifierScope(void);

void printIdentifierTable(void);
void printStructTypeTable(void);
void printIdentifierScopes(void);

int getErrorCount(void);

#endif
