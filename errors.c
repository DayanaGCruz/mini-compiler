#include "errors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Diagnostic bookkeeping. Instead of sprinkling fprintf calls throughout the
 * code base we track identifiers, struct types, keyword hints, and scope
 * markers here and expose helper functions that other phases can call. */

typedef struct {
  char *name;
  int line;
} IdentifierInfo;

static IdentifierInfo identifiers[512];
static int identifierCount = 0;

static IdentifierInfo structTypes[128];
static int structTypeCount = 0;

static int errorCount = 0;

/* We only need a tiny dictionary of keywords to spot probable typos. */
static const char *keywordList[] = {"int",   "char",   "float",  "bool",
                                    "print", "struct", "void",   "return",
                                    "if",    "else",   "switch", "case",
                                    "default","break", "true",  "false", "while",
                                    NULL};

#define MAX_SCOPE_DEPTH 128
static int scopeMarkers[MAX_SCOPE_DEPTH];
static int scopeDepth = 0;

typedef struct {
  char *identifier;
  const char *keyword;
  int line;
} KeywordSuggestion;

static KeywordSuggestion pendingKeyword = {NULL, NULL, 0};

static void resetPendingKeyword(void) {
  if (pendingKeyword.identifier) {
    free(pendingKeyword.identifier);
  }
  pendingKeyword.identifier = NULL;
  pendingKeyword.keyword = NULL;
  pendingKeyword.line = 0;
}

/* All reporting funnels through vreport so we can count errors and prefix the
 * category/line in a uniform fashion. */
static void vreport(ErrorCategory category, int line, const char *fmt,
                    va_list args) {
  const char *label = NULL;
  switch (category) {
  case ERROR_LEXICAL:
    label = "Lexical";
    break;
  case ERROR_SYNTAX:
    label = "Syntax";
    break;
  case ERROR_SEMANTIC:
    label = "Semantic";
    break;
  }

  fprintf(stderr, "%s Error (line %d): ", label, line);
  vfprintf(stderr, fmt, args);
  fprintf(stderr, "\n");

  errorCount++;
}

static void vwarn(int line, const char *fmt, va_list args) {
  if (line > 0) {
    fprintf(stderr, "Semantic Warning (line %d): ", line);
  } else {
    fprintf(stderr, "Semantic Warning: ");
  }

  vfprintf(stderr, fmt, args);
  fprintf(stderr, "\n");
}

static void reportSemanticWarning(int line, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vwarn(line, fmt, args);
  va_end(args);
}

void resetErrorState(void) {
  identifierCount = 0;
  structTypeCount = 0;
  errorCount = 0;
  scopeDepth = 0;
  resetPendingKeyword();
}

void reportLexicalError(int line, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vreport(ERROR_LEXICAL, line, fmt, args);
  va_end(args);
}

void reportSyntaxError(int line, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vreport(ERROR_SYNTAX, line, fmt, args);
  va_end(args);
}

void reportSemanticError(int line, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vreport(ERROR_SEMANTIC, line, fmt, args);
  va_end(args);
}

void reportTypeMismatchWarning(int line, const char *fromType,
                               const char *toType, const char *context) {
  if (!fromType)
    fromType = "unknown";
  if (!toType)
    toType = "unknown";

  if (context && *context) {
    reportSemanticWarning(line, "coercing %s to %s (%s)", fromType, toType,
                          context);
  } else {
    reportSemanticWarning(line, "coercing %s to %s", fromType, toType);
  }
}

int getErrorCount(void) { return errorCount; }

static int findIdentifierIndex(const char *name) {
  for (int i = 0; i < identifierCount; i++) {
    if (strcmp(identifiers[i].name, name) == 0) {
      return i;
    }
  }
  return -1;
}

static int findStructTypeIndex(const char *name) {
  for (int i = 0; i < structTypeCount; i++) {
    if (strcmp(structTypes[i].name, name) == 0) {
      return i;
    }
  }
  return -1;
}

static int min3(int a, int b, int c) {
  int m = a < b ? a : b;
  return m < c ? m : c;
}

/* Lightweight Levenshtein distance implementation for identifier suggestions.
 * It runs on tiny strings so the O(n*m) DP table is perfectly adequate. */
static int levenshtein(const char *a, const char *b) {
  size_t lenA = strlen(a);
  size_t lenB = strlen(b);

  int *prev = malloc((lenB + 1) * sizeof(int));
  int *curr = malloc((lenB + 1) * sizeof(int));

  if (!prev || !curr) {
    free(prev);
    free(curr);
    return 0;
  }

  for (size_t j = 0; j <= lenB; j++) {
    prev[j] = (int)j;
  }

  for (size_t i = 1; i <= lenA; i++) {
    curr[0] = (int)i;
    for (size_t j = 1; j <= lenB; j++) {
      if (a[i - 1] == b[j - 1]) {
        curr[j] = prev[j - 1];
      } else {
        curr[j] = min3(prev[j] + 1,     /* deletion */
                       curr[j - 1] + 1, /* insertion */
                       prev[j - 1] + 1  /* substitution */
        );
      }
    }

    int *tmp = prev;
    prev = curr;
    curr = tmp;
  }

  int distance = prev[lenB];
  free(prev);
  free(curr);
  return distance;
}

static const char *suggestIdentifier(const char *name) {
  const char *best = NULL;
  int bestScore = 4; /* only suggest when reasonably close */

  for (int i = 0; i < identifierCount; i++) {
    int score = levenshtein(name, identifiers[i].name);
    if (score < bestScore) {
      bestScore = score;
      best = identifiers[i].name;
    }
  }

  return best;
}

static const char *suggestKeyword(const char *name, int *scoreOut) {
  const char *best = NULL;
  int bestScore = scoreOut ? *scoreOut : 4;

  if (!scoreOut) {
    bestScore = 4;
  }

  for (int i = 0; keywordList[i]; i++) {
    int score = levenshtein(name, keywordList[i]);
    if (score < bestScore) {
      bestScore = score;
      best = keywordList[i];
    }
  }

  if (scoreOut)
    *scoreOut = bestScore;

  return best;
}

int declareIdentifier(const char *name, int line) {
  if (!name)
    return 0;

  int idx = findIdentifierIndex(name);
  if (idx != -1) {
    reportSemanticError(line,
                        "identifier '%s' already declared (previous at line %d)",
                        name, identifiers[idx].line);
    return 0;
  }

  if (identifierCount >= (int)(sizeof(identifiers) / sizeof(identifiers[0]))) {
    reportSemanticError(line, "too many identifiers declared");
    return 0;
  }

  identifiers[identifierCount].name = strdup(name);
  identifiers[identifierCount].line = line;
  identifierCount++;
  return 1;
}

int referenceIdentifier(const char *name, int line) {
  if (!name)
    return 0;

  if (findIdentifierIndex(name) != -1)
    return 1;

  const char *hint = suggestIdentifier(name);
  if (hint) {
    reportSemanticError(line, "identifier '%s' is undefined. Did you mean '%s'?",
                        name, hint);
  } else {
    reportSemanticError(line, "identifier '%s' is undefined", name);
  }
  return 0;
}

int declareStructType(const char *name, int line) {
  if (!name)
    return 0;

  int idx = findStructTypeIndex(name);
  if (idx != -1) {
    reportSemanticError(line,
                        "struct '%s' already declared (previous at line %d)",
                        name, structTypes[idx].line);
    return 0;
  }

  if (structTypeCount >=
      (int)(sizeof(structTypes) / sizeof(structTypes[0]))) {
    reportSemanticError(line, "too many struct types declared");
    return 0;
  }

  structTypes[structTypeCount].name = strdup(name);
  structTypes[structTypeCount].line = line;
  structTypeCount++;
  return 1;
}

int referenceStructType(const char *name, int line) {
  if (!name)
    return 0;

  if (findStructTypeIndex(name) != -1)
    return 1;

  reportSemanticError(line, "struct type '%s' is undefined", name);
  return 0;
}

void noteKeywordCandidate(const char *name, int line) {
  if (!name)
    return;

  int score = 4;
  const char *keyword = suggestKeyword(name, &score);

  if (keyword && score <= 2) {
    resetPendingKeyword();
    pendingKeyword.identifier = strdup(name);
    pendingKeyword.keyword = keyword;
    pendingKeyword.line = line;
  }
}

int fetchKeywordSuggestion(int line, const char **identifier,
                           const char **keyword) {
  if (pendingKeyword.keyword && pendingKeyword.line == line) {
    if (identifier)
      *identifier = pendingKeyword.identifier;
    if (keyword)
      *keyword = pendingKeyword.keyword;
    return 1;
  }
  return 0;
}

void clearKeywordSuggestion(void) { resetPendingKeyword(); }

void enterIdentifierScope(void) {
  if (scopeDepth >= MAX_SCOPE_DEPTH) {
    return;
  }
  scopeMarkers[scopeDepth++] = identifierCount;
}

void exitIdentifierScope(void) {
  if (scopeDepth == 0)
    return;

  int marker = scopeMarkers[--scopeDepth];
  while (identifierCount > marker) {
    identifierCount--;
    free(identifiers[identifierCount].name);
    identifiers[identifierCount].name = NULL;
    identifiers[identifierCount].line = 0;
  }
}

void printIdentifierTable(void) {
  printf("\n=== IDENTIFIER TABLE STATE ===\n");
  printf("Count: %d\n", identifierCount);
  if (identifierCount == 0) {
    printf("(empty)\n");
  } else {
    for (int i = 0; i < identifierCount; ++i) {
      const char *name = identifiers[i].name ? identifiers[i].name : "<unnamed>";
      printf(" [%d] %s (declared at line %d)\n", i, name, identifiers[i].line);
    }
  }
  printf("==============================\n\n");
}

void printStructTypeTable(void) {
  printf("\n=== STRUCT TYPE TABLE STATE ===\n");
  printf("Count: %d\n", structTypeCount);
  if (structTypeCount == 0) {
    printf("(empty)\n");
  } else {
    for (int i = 0; i < structTypeCount; ++i) {
      const char *name =
          structTypes[i].name ? structTypes[i].name : "<unnamed-struct>";
      printf(" [%d] struct %s (declared at line %d)\n", i, name,
             structTypes[i].line);
    }
  }
  printf("================================\n\n");
}

void printIdentifierScopes(void) {
  printf("\n=== IDENTIFIER SCOPES ===\n");
  printf("Active Scopes: %d\n", scopeDepth);

  int boundaries[MAX_SCOPE_DEPTH + 2];
  int segmentCount = 0;

  boundaries[segmentCount++] = 0;
  for (int i = 0; i < scopeDepth && segmentCount < MAX_SCOPE_DEPTH + 1; ++i) {
    boundaries[segmentCount++] = scopeMarkers[i];
  }

  if (segmentCount < MAX_SCOPE_DEPTH + 2) {
    boundaries[segmentCount++] = identifierCount;
  }

  for (int segment = 0; segment < segmentCount - 1; ++segment) {
    int start = boundaries[segment];
    int end = boundaries[segment + 1];
    int count = end - start;

    if (segment == 0) {
      printf(" Global identifiers (%d)\n", count);
    } else {
      printf(" Scope depth %d identifiers (%d)\n", segment - 1, count);
    }

    if (count == 0) {
      printf("   (empty)\n");
      continue;
    }

    for (int i = start; i < end; ++i) {
      const char *name = identifiers[i].name ? identifiers[i].name : "<unnamed>";
      printf("   - %s (line %d)\n", name, identifiers[i].line);
    }
  }

  if (segmentCount <= 1) {
    printf(" Global identifiers (0)\n");
    if (identifierCount == 0)
      printf("   (empty)\n");
  }

  printf("===========================\n\n");
}
