#ifndef ERRORS_H
#define ERRORS_H

#include <stdarg.h>

typedef enum {
  ERROR_LEXICAL,
  ERROR_SYNTAX,
  ERROR_SEMANTIC
} ErrorCategory;

void resetErrorState(void);
void reportLexicalError(int line, const char *fmt, ...);
void reportSyntaxError(int line, const char *fmt, ...);
void reportSemanticError(int line, const char *fmt, ...);

int declareIdentifier(const char *name, int line);
int referenceIdentifier(const char *name, int line);
int declareStructType(const char *name, int line);
int referenceStructType(const char *name, int line);

void noteKeywordCandidate(const char *name, int line);
int fetchKeywordSuggestion(int line, const char **identifier,
                           const char **keyword);
void clearKeywordSuggestion(void);

void enterIdentifierScope(void);
void exitIdentifierScope(void);

int getErrorCount(void);

#endif
