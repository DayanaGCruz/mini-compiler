#define _GNU_SOURCE
#define _POSIX_C_SOURCE 200809L
/* MINIMAL C COMPILER - EDUCATIONAL VERSION
 * Demonstrates all phases of compilation with a simple language
 * Supports: int variables, addition, assignment, print
 */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include "ast.h"
#include "codegen.h"
#include "errors.h"
#include "tac.h"

extern int yyparse();
extern FILE* yyin;
extern ASTNode* root;

typedef struct {
    int enabled;
    const char* runtime;
} BenchmarkOptions;

/* ExecutionMetrics captures stats from the optional SPIM run so the CLI can
 * correlate compiler performance with the generated program's runtime. */
typedef struct {
    int ran;
    int success;
    int spawn_error;
    int exit_code;
    int signal;
    double wall_ms;
    double user_ms;
    double sys_ms;
    long max_rss_kb;
} ExecutionMetrics;

/* CompilationDiagnostics surfaces TAC counters and assembly size to the final
 * benchmark table. Keeping it in one struct keeps the call site clean. */
typedef struct {
    TACMetrics tac;
    off_t asmBytes;
} CompilationDiagnostics;

static void printUsage(const char* prog) {
    printf("Usage: %s [--benchmark|-b] [--runtime <spim>|--spim <spim>] \
<input.cm> <output.s>\n",
           prog);
    printf("Examples:\n");
    printf("  %s tests/array.cm output.s\n", prog);
    printf("  %s --benchmark tests/array.cm output.s\n", prog);
    printf("  %s --spim /usr/bin/spim tests/array.cm output.s\n", prog);
}

static off_t getFileSizeBytes(const char* path) {
    if (!path)
        return -1;
    struct stat st;
    if (stat(path, &st) != 0)
        return -1;
    return st.st_size;
}

static double elapsed_ms(struct timespec start, struct timespec end) {
    return (double)(end.tv_sec - start.tv_sec) * 1000.0 +
           (double)(end.tv_nsec - start.tv_nsec) / 1000000.0;
}

static double timeval_to_ms(struct timeval tv) {
    return (double)tv.tv_sec * 1000.0 + (double)tv.tv_usec / 1000.0;
}

static ExecutionMetrics runExecutionBenchmark(const char* runtime,
                                              const char* asmFile) {
    ExecutionMetrics metrics = {0};
    struct timespec start, end;
    if (clock_gettime(CLOCK_MONOTONIC, &start) != 0) {
        start.tv_sec = 0;
        start.tv_nsec = 0;
    }

    pid_t pid = fork();
    if (pid == 0) {
        execlp(runtime, runtime, "-file", asmFile, (char*)NULL);
        perror("spim");
        _exit(127);
    } else if (pid < 0) {
        metrics.spawn_error = errno;
        return metrics;
    }

    metrics.ran = 1;
    int status = 0;
    struct rusage usage;
    if (wait4(pid, &status, 0, &usage) == -1) {
        metrics.spawn_error = errno;
        metrics.ran = 0;
        return metrics;
    }

    if (clock_gettime(CLOCK_MONOTONIC, &end) == 0) {
        metrics.wall_ms = elapsed_ms(start, end);
    }
    metrics.user_ms = timeval_to_ms(usage.ru_utime);
    metrics.sys_ms = timeval_to_ms(usage.ru_stime);
    metrics.max_rss_kb = usage.ru_maxrss;

    if (WIFEXITED(status)) {
        metrics.exit_code = WEXITSTATUS(status);
        metrics.success = (metrics.exit_code == 0);
    } else if (WIFSIGNALED(status)) {
        metrics.signal = WTERMSIG(status);
    }

    return metrics;
}

static void printBenchmarkSummary(double compileWallMs, double compileUserMs,
                                  double compileSysMs, long compileRssKb,
                                  int executionRequested,
                                  const ExecutionMetrics* execMetrics,
                                  const BenchmarkOptions* opts,
                                  const CompilationDiagnostics* diag) {
    printf("┌──────────────────────────────────────────────────────────┐\n");
    printf("│ BENCHMARK SUMMARY                                        │\n");
    printf("├──────────────────────────────────────────────────────────┤\n");
    printf("│ Compilation time (wall): %10.2f ms\n", compileWallMs);
    printf("│ Compilation CPU time   : user %8.2f ms | sys %8.2f ms\n",
           compileUserMs, compileSysMs);
    printf("│ Compilation peak RSS   : %8ld KB (%.2f MB)\n", compileRssKb,
           compileRssKb / 1024.0);

    if (diag) {
        printf("│ TAC instructions (raw->opt): %8zu -> %8zu\n",
               diag->tac.tacInstructions, diag->tac.optimizedTACInstructions);
        printf("│ TAC temporaries allocated  : %8zu\n", diag->tac.tempCount);
        if (diag->asmBytes >= 0) {
            printf("│ Assembly output size       : %8lld bytes\n",
                   (long long)diag->asmBytes);
        } else {
            printf("│ Assembly output size       :        unavailable\n");
        }
    }

    if (!executionRequested) {
        printf("│ Execution benchmarking : disabled (pass --benchmark)\n");
        printf("└──────────────────────────────────────────────────────────┘\n");
        return;
    }

    if (execMetrics->spawn_error) {
        printf("│ Execution benchmarking : failed to run '%s' (%s)\n",
               opts->runtime, strerror(execMetrics->spawn_error));
    } else if (!execMetrics->ran) {
        printf("│ Execution benchmarking : unable to collect metrics\n");
    } else if (!execMetrics->success) {
        if (execMetrics->signal != 0) {
            printf("│ Execution benchmarking : terminated by signal %d\n",
                   execMetrics->signal);
        } else {
            printf("│ Execution benchmarking : process exited with code %d\n",
                   execMetrics->exit_code);
        }
    } else {
        printf("│ Execution runtime (wall): %9.2f ms (runtime: %s)\n",
               execMetrics->wall_ms, opts->runtime);
        printf("│ Execution CPU time      : user %8.2f ms | sys %8.2f ms\n",
               execMetrics->user_ms, execMetrics->sys_ms);
        printf("│ Execution peak RSS      : %8ld KB (%.2f MB)\n",
               execMetrics->max_rss_kb,
               execMetrics->max_rss_kb / 1024.0);
    }
    printf("└──────────────────────────────────────────────────────────┘\n");
}

int main(int argc, char* argv[]) {
    BenchmarkOptions benchmark = {.enabled = 0, .runtime = "spim"};
    const char* inputPath = NULL;
    const char* outputPath = NULL;

    for (int i = 1; i < argc; ++i) {
        const char* arg = argv[i];
        if (strcmp(arg, "--benchmark") == 0 || strcmp(arg, "-b") == 0) {
            benchmark.enabled = 1;
            continue;
        }
        if (strcmp(arg, "--runtime") == 0 || strcmp(arg, "--spim") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr,
                        "Error: %s requires a path to the SPIM binary.\n",
                        arg);
                printUsage(argv[0]);
                return 1;
            }
            benchmark.enabled = 1;
            benchmark.runtime = argv[++i];
            continue;
        }
        if (arg[0] == '-' && arg[1] != '\0') {
            fprintf(stderr, "Error: Unknown option '%s'\n", arg);
            printUsage(argv[0]);
            return 1;
        }
        if (!inputPath) {
            inputPath = arg;
        } else if (!outputPath) {
            outputPath = arg;
        } else {
            fprintf(stderr, "Error: Unexpected extra argument '%s'\n", arg);
            printUsage(argv[0]);
            return 1;
        }
    }

    if (!inputPath || !outputPath) {
        printUsage(argv[0]);
        return 1;
    }

    yyin = fopen(inputPath, "r");
    if (!yyin) {
        fprintf(stderr, "Error: Cannot open input file '%s'\n", inputPath);
        return 1;
    }

    struct timespec compileStart, compileEnd;
    if (clock_gettime(CLOCK_MONOTONIC, &compileStart) != 0) {
        compileStart.tv_sec = 0;
        compileStart.tv_nsec = 0;
    }

    printf("\n");
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║          MINIMAL C COMPILER - EDUCATIONAL VERSION          ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    
    /* PHASE 1: Lexical and Syntax Analysis */
    printf("┌──────────────────────────────────────────────────────────┐\n");
    printf("│ PHASE 1: LEXICAL & SYNTAX ANALYSIS                       │\n");
    printf("├──────────────────────────────────────────────────────────┤\n");
    printf("│ • Reading source file: %s\n", inputPath);
    printf("│ • Tokenizing input (scanner.l)\n");
    printf("│ • Parsing grammar rules (parser.y)\n");
    printf("│ • Building Abstract Syntax Tree\n");
    printf("└──────────────────────────────────────────────────────────┘\n");
    
    resetErrorState();
    int parseResult = yyparse();

    if (parseResult == 0 && getErrorCount() == 0) {
        printf("✓ Parse successful - program is syntactically correct!\n\n");
        
        /* PHASE 2: AST Display */
        printf("┌──────────────────────────────────────────────────────────┐\n");
        printf("│ PHASE 2: ABSTRACT SYNTAX TREE (AST)                      │\n");
        printf("├──────────────────────────────────────────────────────────┤\n");
        printf("│ Tree structure representing the program hierarchy:        │\n");
        printf("└──────────────────────────────────────────────────────────┘\n");
        printAST(root, 0);
        printf("\n");

        printf("┌──────────────────────────────────────────────────────────┐\n");
        printf("│ IDENTIFIER TABLES & SCOPES                               │\n");
        printf("├──────────────────────────────────────────────────────────┤\n");
        printf("│ Declarations recorded during parsing and active scopes    │\n");
        printf("└──────────────────────────────────────────────────────────┘\n");
        printIdentifierTable();
        printIdentifierScopes();
        printStructTypeTable();

        /* PHASE 3: Intermediate Code */
        printf("┌──────────────────────────────────────────────────────────┐\n");
        printf("│ PHASE 3: INTERMEDIATE CODE GENERATION                    │\n");
        printf("├──────────────────────────────────────────────────────────┤\n");
        printf("│ Three-Address Code (TAC) - simplified instructions:       │\n");
        printf("│ • Each instruction has at most 3 operands                │\n");
        printf("│ • Temporary variables (t0, t1, ...) for expressions      │\n");
        printf("└──────────────────────────────────────────────────────────┘\n");
        initTAC();
        generateTAC(root);
        if (getErrorCount() > 0) {
            goto fail;
        }
        printTAC();
        printf("\n");
        
        /* PHASE 4: Optimization */
        printf("┌──────────────────────────────────────────────────────────┐\n");
        printf("│ PHASE 4: CODE OPTIMIZATION                               │\n");
        printf("├──────────────────────────────────────────────────────────┤\n");
        printf("│ Applying optimizations:                                  │\n");
        printf("│ • Constant folding (evaluate compile-time expressions)   │\n");
        printf("│ • Copy propagation (replace variables with values)       │\n");
        printf("│ • Loop unrolling (replicate loop body)                   │\n");
        printf("│ • Dead code elimination                                  │\n");
        printf("└──────────────────────────────────────────────────────────┘\n");
        optimizeTAC();
        printOptimizedTAC();
        printf("\n");

        printf("┌──────────────────────────────────────────────────────────┐\n");
        printf("│ FUNCTION RETURN TABLE (TAC)                              │\n");
        printf("├──────────────────────────────────────────────────────────┤\n");
        printf("│ Records the return type inferred for each function        │\n");
        printf("└──────────────────────────────────────────────────────────┘\n");
        printFunctionReturnTable();
        printf("\n");

        TACMetrics tacMetrics = {0};
        getTACMetrics(&tacMetrics);

        /* PHASE 5: Code Generation */
        printf("┌──────────────────────────────────────────────────────────┐\n");
        printf("│ PHASE 5: MIPS CODE GENERATION                            │\n");
        printf("├──────────────────────────────────────────────────────────┤\n");
        printf("│ Translating to MIPS assembly:                            │\n");
        printf("│ • Variables stored on stack                              │\n");
        printf("│ • Using $t0-$t7 for temporary values                     │\n");
        printf("│ • System calls for print operations                      │\n");
        printf("└──────────────────────────────────────────────────────────┘\n");
        generateMIPS(root, outputPath);
        printf("✓ MIPS assembly code generated to: %s\n", outputPath);
        printf("\n");

        if (clock_gettime(CLOCK_MONOTONIC, &compileEnd) != 0) {
            compileEnd = compileStart;
        }
        struct rusage compileUsage;
        getrusage(RUSAGE_SELF, &compileUsage);
        double compileWall = elapsed_ms(compileStart, compileEnd);
        double compileUser = timeval_to_ms(compileUsage.ru_utime);
        double compileSys = timeval_to_ms(compileUsage.ru_stime);
        long compileRss = compileUsage.ru_maxrss;

        ExecutionMetrics execMetrics = {0};
        if (benchmark.enabled) {
            printf("Running execution benchmark with '%s'...\n",
                   benchmark.runtime);
            execMetrics = runExecutionBenchmark(benchmark.runtime, outputPath);
        }

        CompilationDiagnostics diagnostics = {
            .tac = tacMetrics,
            .asmBytes = getFileSizeBytes(outputPath)};

        printBenchmarkSummary(compileWall, compileUser, compileSys,
                              compileRss, benchmark.enabled, &execMetrics,
                              &benchmark, &diagnostics);
        
        printf("╔════════════════════════════════════════════════════════════╗\n");
        printf("║                  COMPILATION SUCCESSFUL!                   ║\n");
        printf("║         Run the output file in a MIPS simulator            ║\n");
        printf("╚════════════════════════════════════════════════════════════╝\n");
        fclose(yyin);
        return 0;
    }

fail:
    {
        int errors = getErrorCount();
        printf("✗ Compilation halted due to %d error%s.\n", errors,
               errors == 1 ? "" : "s");
        printf("Common issues to investigate:\n");
        printf("  • Missing semicolons or mismatched braces\n");
        printf("  • Undeclared or misspelled identifiers\n");
        printf("  • Illegal characters in the source file\n");
        if (yyin)
            fclose(yyin);
        return 1;
    }
}
