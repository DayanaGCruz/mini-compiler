/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

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

#line 92 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_LITERAL_NUM = 3,                /* LITERAL_NUM  */
  YYSYMBOL_LITERAL_CHAR = 4,               /* LITERAL_CHAR  */
  YYSYMBOL_LITERAL_FLOAT = 5,              /* LITERAL_FLOAT  */
  YYSYMBOL_ID = 6,                         /* ID  */
  YYSYMBOL_KW_INT = 7,                     /* KW_INT  */
  YYSYMBOL_KW_PRINT = 8,                   /* KW_PRINT  */
  YYSYMBOL_KW_CHAR = 9,                    /* KW_CHAR  */
  YYSYMBOL_KW_FLOAT = 10,                  /* KW_FLOAT  */
  YYSYMBOL_KW_BOOL = 11,                   /* KW_BOOL  */
  YYSYMBOL_KW_STRUCT = 12,                 /* KW_STRUCT  */
  YYSYMBOL_KW_VOID = 13,                   /* KW_VOID  */
  YYSYMBOL_KW_RETURN = 14,                 /* KW_RETURN  */
  YYSYMBOL_KW_IF = 15,                     /* KW_IF  */
  YYSYMBOL_KW_ELSE = 16,                   /* KW_ELSE  */
  YYSYMBOL_KW_SWITCH = 17,                 /* KW_SWITCH  */
  YYSYMBOL_KW_CASE = 18,                   /* KW_CASE  */
  YYSYMBOL_KW_DEFAULT = 19,                /* KW_DEFAULT  */
  YYSYMBOL_KW_BREAK = 20,                  /* KW_BREAK  */
  YYSYMBOL_KW_GOTO = 21,                   /* KW_GOTO  */
  YYSYMBOL_KW_CONTINUE = 22,               /* KW_CONTINUE  */
  YYSYMBOL_KW_WHILE = 23,                  /* KW_WHILE  */
  YYSYMBOL_KW_TRUE = 24,                   /* KW_TRUE  */
  YYSYMBOL_KW_FALSE = 25,                  /* KW_FALSE  */
  YYSYMBOL_AND = 26,                       /* AND  */
  YYSYMBOL_OR = 27,                        /* OR  */
  YYSYMBOL_NOT = 28,                       /* NOT  */
  YYSYMBOL_EQ = 29,                        /* EQ  */
  YYSYMBOL_NEQ = 30,                       /* NEQ  */
  YYSYMBOL_LEQ = 31,                       /* LEQ  */
  YYSYMBOL_GEQ = 32,                       /* GEQ  */
  YYSYMBOL_33_ = 33,                       /* '?'  */
  YYSYMBOL_34_ = 34,                       /* ':'  */
  YYSYMBOL_35_ = 35,                       /* '>'  */
  YYSYMBOL_36_ = 36,                       /* '<'  */
  YYSYMBOL_37_ = 37,                       /* '+'  */
  YYSYMBOL_38_ = 38,                       /* '-'  */
  YYSYMBOL_39_ = 39,                       /* '*'  */
  YYSYMBOL_40_ = 40,                       /* '/'  */
  YYSYMBOL_LOWER_THAN_ELSE = 41,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_42_ = 42,                       /* '('  */
  YYSYMBOL_43_ = 43,                       /* ')'  */
  YYSYMBOL_44_ = 44,                       /* '{'  */
  YYSYMBOL_45_ = 45,                       /* '}'  */
  YYSYMBOL_46_ = 46,                       /* ','  */
  YYSYMBOL_47_ = 47,                       /* '['  */
  YYSYMBOL_48_ = 48,                       /* ']'  */
  YYSYMBOL_49_ = 49,                       /* ';'  */
  YYSYMBOL_50_ = 50,                       /* '.'  */
  YYSYMBOL_51_ = 51,                       /* '='  */
  YYSYMBOL_YYACCEPT = 52,                  /* $accept  */
  YYSYMBOL_program = 53,                   /* program  */
  YYSYMBOL_func_list = 54,                 /* func_list  */
  YYSYMBOL_func_item = 55,                 /* func_item  */
  YYSYMBOL_func_decl = 56,                 /* func_decl  */
  YYSYMBOL_57_1 = 57,                      /* $@1  */
  YYSYMBOL_58_2 = 58,                      /* $@2  */
  YYSYMBOL_param_list = 59,                /* param_list  */
  YYSYMBOL_param = 60,                     /* param  */
  YYSYMBOL_stmt_list = 61,                 /* stmt_list  */
  YYSYMBOL_stmt = 62,                      /* stmt  */
  YYSYMBOL_block = 63,                     /* block  */
  YYSYMBOL_if_stmt = 64,                   /* if_stmt  */
  YYSYMBOL_switch_stmt = 65,               /* switch_stmt  */
  YYSYMBOL_switch_case_list = 66,          /* switch_case_list  */
  YYSYMBOL_switch_item = 67,               /* switch_item  */
  YYSYMBOL_case_stmt_body = 68,            /* case_stmt_body  */
  YYSYMBOL_while_stmt = 69,                /* while_stmt  */
  YYSYMBOL_expr_stmt = 70,                 /* expr_stmt  */
  YYSYMBOL_type = 71,                      /* type  */
  YYSYMBOL_decl = 72,                      /* decl  */
  YYSYMBOL_struct_decl = 73,               /* struct_decl  */
  YYSYMBOL_struct_field_list = 74,         /* struct_field_list  */
  YYSYMBOL_struct_field = 75,              /* struct_field  */
  YYSYMBOL_struct_var_decl = 76,           /* struct_var_decl  */
  YYSYMBOL_struct_assign = 77,             /* struct_assign  */
  YYSYMBOL_arg_list = 78,                  /* arg_list  */
  YYSYMBOL_assign = 79,                    /* assign  */
  YYSYMBOL_expr = 80,                      /* expr  */
  YYSYMBOL_return_stmt = 81,               /* return_stmt  */
  YYSYMBOL_print_stmt = 82                 /* print_stmt  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   559

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  92
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  189

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   288


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      42,    43,    39,    37,    46,    38,    50,    40,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    34,    49,
      36,    51,    35,    33,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    47,     2,    48,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    44,     2,    45,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    41
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    78,    78,    85,    86,    90,    91,    95,    95,    99,
      99,   106,   107,   108,   112,   117,   122,   127,   137,   141,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   165,   166,   170,   171,   172,   176,   179,
     193,   194,   198,   199,   203,   204,   208,   213,   219,   220,
     221,   222,   223,   228,   242,   250,   258,   259,   263,   270,
     280,   289,   290,   294,   300,   309,   310,   311,   312,   313,
     314,   319,   325,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     350,   351,   356
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "LITERAL_NUM",
  "LITERAL_CHAR", "LITERAL_FLOAT", "ID", "KW_INT", "KW_PRINT", "KW_CHAR",
  "KW_FLOAT", "KW_BOOL", "KW_STRUCT", "KW_VOID", "KW_RETURN", "KW_IF",
  "KW_ELSE", "KW_SWITCH", "KW_CASE", "KW_DEFAULT", "KW_BREAK", "KW_GOTO",
  "KW_CONTINUE", "KW_WHILE", "KW_TRUE", "KW_FALSE", "AND", "OR", "NOT",
  "EQ", "NEQ", "LEQ", "GEQ", "'?'", "':'", "'>'", "'<'", "'+'", "'-'",
  "'*'", "'/'", "LOWER_THAN_ELSE", "'('", "')'", "'{'", "'}'", "','",
  "'['", "']'", "';'", "'.'", "'='", "$accept", "program", "func_list",
  "func_item", "func_decl", "$@1", "$@2", "param_list", "param",
  "stmt_list", "stmt", "block", "if_stmt", "switch_stmt",
  "switch_case_list", "switch_item", "case_stmt_body", "while_stmt",
  "expr_stmt", "type", "decl", "struct_decl", "struct_field_list",
  "struct_field", "struct_var_decl", "struct_assign", "arg_list", "assign",
  "expr", "return_stmt", "print_stmt", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-77)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-53)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     254,   -77,   -77,   -77,   -77,    22,   -77,    32,   254,   -77,
     -77,    39,   -77,     3,   -77,   -77,    24,   -77,    34,     4,
     539,    36,    48,    75,   -77,    95,   103,    62,   -77,   105,
      71,   -77,    73,   113,    76,   546,    96,    79,   -77,   -77,
      79,   -77,    15,   -77,   -77,   -77,    25,   102,   140,    -1,
     109,   110,    98,   130,   -77,   -77,   234,   234,   125,   151,
     -77,   -77,   -77,   -77,   -77,   -77,   167,   -77,   -77,   -77,
     -77,   -77,   248,   -77,   -77,   177,   129,   -77,   229,   234,
     172,   234,   234,     0,   -21,   -77,   263,   234,   234,   -77,
     234,   -77,   363,   -77,   203,   -77,   -77,   -37,   234,   234,
     234,   234,   234,   234,   234,   234,   234,   234,   234,   234,
     234,   -77,   -77,   -77,   -77,    70,   468,   323,   147,   278,
     378,   150,   234,   197,   -77,   393,   408,   423,   -77,   -77,
     201,   -77,   495,   483,   505,   505,    31,    31,   438,    31,
      31,    78,    78,   -77,   -77,   -77,   234,   173,   234,   -77,
     176,   -77,   343,   -77,   185,   186,   185,   188,   234,   468,
     234,   293,   -77,   -77,   225,     1,   -77,   193,   468,   308,
     -77,    -8,   234,   209,   -77,    19,   -77,   -77,   -77,   -77,
     -77,   453,    79,   -77,   -77,    79,    79,   -77,   -77
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    48,    49,    50,    51,     0,    52,     0,     2,     3,
       5,     0,     6,     0,     1,     4,     0,    56,     7,     0,
       0,     0,     0,     0,    57,     0,    11,     0,    12,     0,
       0,    55,     0,     0,     0,     0,    14,     0,    58,    17,
       0,    13,     0,    65,    67,    66,    70,     0,     0,     0,
       0,     0,     0,     0,    68,    69,     0,     0,     0,     0,
      18,    30,    28,    29,    32,    27,     0,    20,    23,    24,
      25,    21,     0,    26,    22,     0,     0,    16,     0,     0,
       0,     0,     0,     0,    70,    91,     0,     0,     0,    31,
       0,    87,     0,    34,     0,    10,    19,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    47,     8,    15,    74,     0,    61,     0,    71,     0,
       0,     0,     0,     0,    90,     0,     0,     0,    89,    33,
       0,    53,    85,    86,    83,    84,    82,    81,     0,    79,
      80,    75,    76,    77,    78,    73,     0,    72,     0,    63,
       0,    59,     0,    71,     0,     0,     0,     0,     0,    62,
       0,     0,    92,    72,    35,     0,    46,     0,    88,     0,
      60,     0,     0,     0,    38,     0,    41,    54,    64,    36,
      37,     0,    45,    39,    40,    45,    44,    43,    42
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -77,   -77,   -77,   236,   -77,   -77,   -77,   -77,   211,   -15,
     -59,   -76,    80,   -77,   -77,    74,    67,   -77,   -77,   106,
     -77,    65,   -77,   -77,   -77,   -77,   -77,   -77,   -48,   -77,
     -77
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     7,     8,     9,    10,    20,    21,    27,    28,   186,
      60,    61,    62,    63,   175,   176,   187,    64,    65,    66,
      67,    68,    19,    24,    69,    70,   115,    71,    72,    73,
      74
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      96,    86,    43,    44,    45,    84,   121,    50,    91,    92,
     130,     1,   131,     2,     3,     4,    96,     6,    76,   172,
     173,    78,    59,    54,    55,    75,   122,    56,    13,   123,
     116,   117,    14,   119,   120,    96,    58,   172,   173,   125,
     126,    57,   127,    94,    17,    16,   174,    17,    85,    22,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,    77,   183,    12,    18,    78,   107,   108,
     109,   110,    79,    12,   152,    80,    81,    -9,   164,    30,
     166,    32,    43,    44,    45,    46,     1,    47,     2,     3,
       4,    48,     6,    49,    50,   179,    51,    31,   159,    52,
     161,    33,    53,    54,    55,    34,    11,    56,    35,   -52,
     168,    36,   169,   145,    11,    37,   146,   109,   110,    39,
      40,    57,    38,    58,   181,    23,    29,    96,    43,    44,
      45,    46,     1,    47,     2,     3,     4,    48,     6,    49,
      50,    29,    51,    42,    82,    52,    83,    89,    53,    54,
      55,    87,    88,    56,    43,    44,    45,    46,     1,    47,
       2,     3,     4,    48,     6,    49,    50,    57,    51,    58,
      93,    52,    90,    97,    53,    54,    55,   113,   118,    56,
      43,    44,    45,    46,     1,    47,     2,     3,     4,    48,
       6,    49,    50,    57,    51,    58,    95,    52,   148,   151,
      53,    54,    55,   153,   157,    56,    43,    44,    45,    46,
       1,    47,     2,     3,     4,    48,     6,    49,    50,    57,
      51,    58,   112,    52,   160,   162,    53,    54,    55,    58,
     165,    56,    43,    44,    45,    84,   167,    43,    44,    45,
      84,   171,   177,   182,    15,    57,    41,    58,   129,   184,
       0,   180,   188,    54,    55,     0,     0,    56,    54,    55,
       0,     1,    56,     2,     3,     4,     5,     6,     0,     0,
       0,    57,   114,     0,    98,    99,    57,   100,   101,   102,
     103,   104,     0,   105,   106,   107,   108,   109,   110,    98,
      99,     0,   100,   101,   102,   103,   104,   111,   105,   106,
     107,   108,   109,   110,    98,    99,     0,   100,   101,   102,
     103,   104,   124,   105,   106,   107,   108,   109,   110,    98,
      99,     0,   100,   101,   102,   103,   104,   149,   105,   106,
     107,   108,   109,   110,    98,    99,     0,   100,   101,   102,
     103,   104,   170,   105,   106,   107,   108,   109,   110,    98,
      99,     0,   100,   101,   102,   103,   104,   178,   105,   106,
     107,   108,   109,   110,     0,     0,     0,     0,     0,    98,
      99,   147,   100,   101,   102,   103,   104,     0,   105,   106,
     107,   108,   109,   110,     0,     0,     0,     0,     0,    98,
      99,   163,   100,   101,   102,   103,   104,     0,   105,   106,
     107,   108,   109,   110,    98,    99,   128,   100,   101,   102,
     103,   104,     0,   105,   106,   107,   108,   109,   110,    98,
      99,   150,   100,   101,   102,   103,   104,     0,   105,   106,
     107,   108,   109,   110,    98,    99,   154,   100,   101,   102,
     103,   104,     0,   105,   106,   107,   108,   109,   110,    98,
      99,   155,   100,   101,   102,   103,   104,     0,   105,   106,
     107,   108,   109,   110,    98,    99,   156,   100,   101,   102,
     103,   104,   158,   105,   106,   107,   108,   109,   110,    98,
      99,     0,   100,   101,   102,   103,   104,   185,   105,   106,
     107,   108,   109,   110,    98,    99,     0,   100,   101,   102,
     103,   104,     0,   105,   106,   107,   108,   109,   110,    98,
       0,     0,   100,   101,   102,   103,     0,     0,   105,   106,
     107,   108,   109,   110,   100,   101,   102,   103,     0,     0,
     105,   106,   107,   108,   109,   110,   102,   103,     0,     0,
     105,   106,   107,   108,   109,   110,     1,     0,     2,     3,
       4,    25,    26,     1,     0,     2,     3,     4,    25,     6
};

static const yytype_int16 yycheck[] =
{
      59,    49,     3,     4,     5,     6,     6,    15,    56,    57,
      47,     7,    49,     9,    10,    11,    75,    13,     3,    18,
      19,    42,    37,    24,    25,    40,    47,    28,     6,    50,
      78,    79,     0,    81,    82,    94,    44,    18,    19,    87,
      88,    42,    90,    58,    44,     6,    45,    44,    49,    45,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,    48,    45,     0,    42,    42,    37,    38,
      39,    40,    47,     8,   122,    50,    51,    43,   154,    43,
     156,     6,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,   171,    17,    49,   146,    20,
     148,     6,    23,    24,    25,    43,     0,    28,    46,     6,
     158,     6,   160,    43,     8,    44,    46,    39,    40,     6,
      44,    42,    49,    44,   172,    19,    20,   186,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    35,    17,    47,    42,    20,     6,    49,    23,    24,
      25,    42,    42,    28,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    42,    17,    44,
      45,    20,    42,     6,    23,    24,    25,    48,     6,    28,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    42,    17,    44,    45,    20,    51,    49,
      23,    24,    25,     6,     3,    28,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    42,
      17,    44,    45,    20,    51,    49,    23,    24,    25,    44,
      44,    28,     3,     4,     5,     6,    48,     3,     4,     5,
       6,    16,    49,    34,     8,    42,    35,    44,    45,   175,
      -1,   171,   185,    24,    25,    -1,    -1,    28,    24,    25,
      -1,     7,    28,     9,    10,    11,    12,    13,    -1,    -1,
      -1,    42,    43,    -1,    26,    27,    42,    29,    30,    31,
      32,    33,    -1,    35,    36,    37,    38,    39,    40,    26,
      27,    -1,    29,    30,    31,    32,    33,    49,    35,    36,
      37,    38,    39,    40,    26,    27,    -1,    29,    30,    31,
      32,    33,    49,    35,    36,    37,    38,    39,    40,    26,
      27,    -1,    29,    30,    31,    32,    33,    49,    35,    36,
      37,    38,    39,    40,    26,    27,    -1,    29,    30,    31,
      32,    33,    49,    35,    36,    37,    38,    39,    40,    26,
      27,    -1,    29,    30,    31,    32,    33,    49,    35,    36,
      37,    38,    39,    40,    -1,    -1,    -1,    -1,    -1,    26,
      27,    48,    29,    30,    31,    32,    33,    -1,    35,    36,
      37,    38,    39,    40,    -1,    -1,    -1,    -1,    -1,    26,
      27,    48,    29,    30,    31,    32,    33,    -1,    35,    36,
      37,    38,    39,    40,    26,    27,    43,    29,    30,    31,
      32,    33,    -1,    35,    36,    37,    38,    39,    40,    26,
      27,    43,    29,    30,    31,    32,    33,    -1,    35,    36,
      37,    38,    39,    40,    26,    27,    43,    29,    30,    31,
      32,    33,    -1,    35,    36,    37,    38,    39,    40,    26,
      27,    43,    29,    30,    31,    32,    33,    -1,    35,    36,
      37,    38,    39,    40,    26,    27,    43,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    26,
      27,    -1,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    26,    27,    -1,    29,    30,    31,
      32,    33,    -1,    35,    36,    37,    38,    39,    40,    26,
      -1,    -1,    29,    30,    31,    32,    -1,    -1,    35,    36,
      37,    38,    39,    40,    29,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    39,    40,    31,    32,    -1,    -1,
      35,    36,    37,    38,    39,    40,     7,    -1,     9,    10,
      11,    12,    13,     7,    -1,     9,    10,    11,    12,    13
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,     9,    10,    11,    12,    13,    53,    54,    55,
      56,    71,    73,     6,     0,    55,     6,    44,    42,    74,
      57,    58,    45,    71,    75,    12,    13,    59,    60,    71,
      43,    49,     6,     6,    43,    46,     6,    44,    49,     6,
      44,    60,    47,     3,     4,     5,     6,     8,    12,    14,
      15,    17,    20,    23,    24,    25,    28,    42,    44,    61,
      62,    63,    64,    65,    69,    70,    71,    72,    73,    76,
      77,    79,    80,    81,    82,    61,     3,    48,    42,    47,
      50,    51,    42,     6,     6,    49,    80,    42,    42,    49,
      42,    80,    80,    45,    61,    45,    62,     6,    26,    27,
      29,    30,    31,    32,    33,    35,    36,    37,    38,    39,
      40,    49,    45,    48,    43,    78,    80,    80,     6,    80,
      80,     6,    47,    50,    49,    80,    80,    80,    43,    45,
      47,    49,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    43,    46,    48,    51,    49,
      43,    49,    80,     6,    43,    43,    43,     3,    34,    80,
      51,    80,    49,    48,    63,    44,    63,    48,    80,    80,
      49,    16,    18,    19,    45,    66,    67,    49,    49,    63,
      64,    80,    34,    45,    67,    34,    61,    68,    68
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    52,    53,    54,    54,    55,    55,    57,    56,    58,
      56,    59,    59,    59,    60,    60,    60,    60,    61,    61,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    63,    63,    64,    64,    64,    65,    65,
      66,    66,    67,    67,    68,    68,    69,    70,    71,    71,
      71,    71,    71,    72,    72,    73,    74,    74,    75,    76,
      77,    78,    78,    79,    79,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      81,    81,    82
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     0,     9,     0,
       8,     1,     1,     3,     2,     5,     4,     3,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     3,     2,     5,     7,     7,     6,     7,
       2,     1,     4,     3,     1,     0,     5,     2,     1,     1,
       1,     1,     1,     3,     6,     6,     0,     2,     3,     4,
       6,     1,     3,     4,     7,     1,     1,     1,     1,     1,
       1,     3,     4,     4,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     5,     3,
       3,     2,     5
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: func_list  */
#line 78 "parser.y"
               { 
        root = (yyvsp[0].node);
        (yyval.node) = (yyvsp[0].node);     }
#line 1748 "parser.tab.c"
    break;

  case 3: /* func_list: func_item  */
#line 85 "parser.y"
              { (yyval.node) = (yyvsp[0].node);}
#line 1754 "parser.tab.c"
    break;

  case 4: /* func_list: func_list func_item  */
#line 86 "parser.y"
                          { (yyval.node) = createFuncList((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1760 "parser.tab.c"
    break;

  case 5: /* func_item: func_decl  */
#line 90 "parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 1766 "parser.tab.c"
    break;

  case 6: /* func_item: struct_decl  */
#line 91 "parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 1772 "parser.tab.c"
    break;

  case 7: /* $@1: %empty  */
#line 95 "parser.y"
                     { enterIdentifierScope(); }
#line 1778 "parser.tab.c"
    break;

  case 8: /* func_decl: type ID '(' $@1 param_list ')' '{' stmt_list '}'  */
#line 95 "parser.y"
                                                                                  {
          exitIdentifierScope();
          (yyval.node) = createFuncDecl((yyvsp[-8].dataType), (yyvsp[-7].str), (yyvsp[-4].node), (yyvsp[-1].node));
        }
#line 1787 "parser.tab.c"
    break;

  case 9: /* $@2: %empty  */
#line 99 "parser.y"
                      { enterIdentifierScope(); }
#line 1793 "parser.tab.c"
    break;

  case 10: /* func_decl: type ID '(' $@2 ')' '{' stmt_list '}'  */
#line 99 "parser.y"
                                                                        {
          exitIdentifierScope();
          (yyval.node) = createFuncDecl((yyvsp[-7].dataType), (yyvsp[-6].str), NULL, (yyvsp[-1].node));
        }
#line 1802 "parser.tab.c"
    break;

  case 11: /* param_list: KW_VOID  */
#line 106 "parser.y"
            { (yyval.node) = NULL; }
#line 1808 "parser.tab.c"
    break;

  case 12: /* param_list: param  */
#line 107 "parser.y"
            { (yyval.node) = (yyvsp[0].node); }
#line 1814 "parser.tab.c"
    break;

  case 13: /* param_list: param_list ',' param  */
#line 108 "parser.y"
                           { (yyval.node) = createParamList((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1820 "parser.tab.c"
    break;

  case 14: /* param: type ID  */
#line 112 "parser.y"
             {
       declareIdentifier((yyvsp[0].str), (yylsp[0]).first_line);
       (yyval.node) = createParam((yyvsp[-1].dataType), (yyvsp[0].str));
       free((yyvsp[0].str));
     }
#line 1830 "parser.tab.c"
    break;

  case 15: /* param: type ID '[' LITERAL_NUM ']'  */
#line 117 "parser.y"
                                   {
       declareIdentifier((yyvsp[-3].str), (yylsp[-3]).first_line);
       (yyval.node) = createArrayParam((yyvsp[-4].dataType), (yyvsp[-3].str), (yyvsp[-1].num));
       free((yyvsp[-3].str));
     }
#line 1840 "parser.tab.c"
    break;

  case 16: /* param: type ID '[' ']'  */
#line 122 "parser.y"
                       {
       declareIdentifier((yyvsp[-2].str), (yylsp[-2]).first_line);
       (yyval.node) = createArrayParam((yyvsp[-3].dataType), (yyvsp[-2].str), 0);
       free((yyvsp[-2].str));
     }
#line 1850 "parser.tab.c"
    break;

  case 17: /* param: KW_STRUCT ID ID  */
#line 127 "parser.y"
                       {
       referenceStructType((yyvsp[-1].str), (yylsp[-1]).first_line);
       declareIdentifier((yyvsp[0].str), (yylsp[0]).first_line);
       (yyval.node) = createStructParam((yyvsp[-1].str), (yyvsp[0].str));
       free((yyvsp[-1].str));
       free((yyvsp[0].str));
     }
#line 1862 "parser.tab.c"
    break;

  case 18: /* stmt_list: stmt  */
#line 137 "parser.y"
         { 
        /* Base case: single statement */
        (yyval.node) = (yyvsp[0].node);  /* Pass the statement up as-is */
    }
#line 1871 "parser.tab.c"
    break;

  case 19: /* stmt_list: stmt_list stmt  */
#line 141 "parser.y"
                     { 
        /* Recursive case: list followed by another statement */
        (yyval.node) = createStmtList((yyvsp[-1].node), (yyvsp[0].node));  /* Build linked list of statements */
    }
#line 1880 "parser.tab.c"
    break;

  case 31: /* stmt: KW_BREAK ';'  */
#line 160 "parser.y"
                   { (yyval.node) = createBreak(); }
#line 1886 "parser.tab.c"
    break;

  case 33: /* block: '{' stmt_list '}'  */
#line 165 "parser.y"
                      { (yyval.node) = createBlock((yyvsp[-1].node)); }
#line 1892 "parser.tab.c"
    break;

  case 34: /* block: '{' '}'  */
#line 166 "parser.y"
              { (yyval.node) = createBlock(NULL); }
#line 1898 "parser.tab.c"
    break;

  case 35: /* if_stmt: KW_IF '(' expr ')' block  */
#line 170 "parser.y"
                                                   { (yyval.node) = createIf((yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 1904 "parser.tab.c"
    break;

  case 36: /* if_stmt: KW_IF '(' expr ')' block KW_ELSE block  */
#line 171 "parser.y"
                                             { (yyval.node) = createIf((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1910 "parser.tab.c"
    break;

  case 37: /* if_stmt: KW_IF '(' expr ')' block KW_ELSE if_stmt  */
#line 172 "parser.y"
                                               { (yyval.node) = createIf((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1916 "parser.tab.c"
    break;

  case 38: /* switch_stmt: KW_SWITCH '(' expr ')' '{' '}'  */
#line 176 "parser.y"
                                   {
      (yyval.node) = createSwitch((yyvsp[-3].node), NULL, NULL);
    }
#line 1924 "parser.tab.c"
    break;

  case 39: /* switch_stmt: KW_SWITCH '(' expr ')' '{' switch_case_list '}'  */
#line 179 "parser.y"
                                                      {
      ASTNode *cases = (yyvsp[-1].node);
      ASTNode *defaultNode = NULL;
      for (ASTNode *curr = cases; curr; curr = curr->data.case_stmt.next) {
        if (curr->data.case_stmt.isDefault) {
          defaultNode = curr;
          break;
        }
      }
      (yyval.node) = createSwitch((yyvsp[-4].node), cases, defaultNode);
    }
#line 1940 "parser.tab.c"
    break;

  case 40: /* switch_case_list: switch_case_list switch_item  */
#line 193 "parser.y"
                                 { (yyval.node) = appendCase((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1946 "parser.tab.c"
    break;

  case 41: /* switch_case_list: switch_item  */
#line 194 "parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 1952 "parser.tab.c"
    break;

  case 42: /* switch_item: KW_CASE expr ':' case_stmt_body  */
#line 198 "parser.y"
                                    { (yyval.node) = createCase((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1958 "parser.tab.c"
    break;

  case 43: /* switch_item: KW_DEFAULT ':' case_stmt_body  */
#line 199 "parser.y"
                                    { (yyval.node) = createDefaultCase((yyvsp[0].node)); }
#line 1964 "parser.tab.c"
    break;

  case 44: /* case_stmt_body: stmt_list  */
#line 203 "parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 1970 "parser.tab.c"
    break;

  case 45: /* case_stmt_body: %empty  */
#line 204 "parser.y"
                  { (yyval.node) = NULL; }
#line 1976 "parser.tab.c"
    break;

  case 46: /* while_stmt: KW_WHILE '(' expr ')' block  */
#line 208 "parser.y"
                                {
      (yyval.node) = createWhile((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1984 "parser.tab.c"
    break;

  case 47: /* expr_stmt: expr ';'  */
#line 213 "parser.y"
             { (yyval.node) = createExprStmt((yyvsp[-1].node)); }
#line 1990 "parser.tab.c"
    break;

  case 48: /* type: KW_INT  */
#line 219 "parser.y"
             { (yyval.dataType) = TYPE_INT;  /* int */}
#line 1996 "parser.tab.c"
    break;

  case 49: /* type: KW_CHAR  */
#line 220 "parser.y"
              { (yyval.dataType) = TYPE_CHAR; /* char */}
#line 2002 "parser.tab.c"
    break;

  case 50: /* type: KW_FLOAT  */
#line 221 "parser.y"
               { (yyval.dataType) = TYPE_FLOAT; /* float */}
#line 2008 "parser.tab.c"
    break;

  case 51: /* type: KW_BOOL  */
#line 222 "parser.y"
              { (yyval.dataType) = TYPE_BOOL; /* bool */}
#line 2014 "parser.tab.c"
    break;

  case 52: /* type: KW_VOID  */
#line 223 "parser.y"
              { (yyval.dataType) = TYPE_VOID; /* void */}
#line 2020 "parser.tab.c"
    break;

  case 53: /* decl: type ID ';'  */
#line 228 "parser.y"
                  { 
      declareIdentifier((yyvsp[-1].str), (yylsp[-1]).first_line);
      if ((yyvsp[-2].dataType) == TYPE_INT) {
        (yyval.node) = createDecl((yyvsp[-1].str));
      } else if ((yyvsp[-2].dataType) == TYPE_CHAR) {
        (yyval.node) = createCharDecl((yyvsp[-1].str));
      } else if ((yyvsp[-2].dataType) == TYPE_FLOAT) {
        (yyval.node) = createFloatDecl((yyvsp[-1].str));
      } else if ((yyvsp[-2].dataType) == TYPE_BOOL) {
        (yyval.node) = createBoolDecl((yyvsp[-1].str));
      } else {
        (yyval.node) = createDecl((yyvsp[-1].str));
      }
    }
#line 2039 "parser.tab.c"
    break;

  case 54: /* decl: type ID '[' LITERAL_NUM ']' ';'  */
#line 242 "parser.y"
                                      {
      declareIdentifier((yyvsp[-4].str), (yylsp[-4]).first_line);
      (yyval.node) = createArrayDecl((yyvsp[-4].str), (yyvsp[-2].num), (yyvsp[-5].dataType));
      free((yyvsp[-4].str));
    }
#line 2049 "parser.tab.c"
    break;

  case 55: /* struct_decl: KW_STRUCT ID '{' struct_field_list '}' ';'  */
#line 250 "parser.y"
                                                 {
        declareStructType((yyvsp[-4].str), (yylsp[-4]).first_line);
        (yyval.node) = createStructDef((yyvsp[-4].str), (yyvsp[-2].node));
        free((yyvsp[-4].str));
    }
#line 2059 "parser.tab.c"
    break;

  case 56: /* struct_field_list: %empty  */
#line 258 "parser.y"
                  { (yyval.node) = NULL; }
#line 2065 "parser.tab.c"
    break;

  case 57: /* struct_field_list: struct_field_list struct_field  */
#line 259 "parser.y"
                                     { (yyval.node) = appendStructField((yyvsp[-1].node), (yyvsp[0].node)); }
#line 2071 "parser.tab.c"
    break;

  case 58: /* struct_field: type ID ';'  */
#line 263 "parser.y"
                  {
        (yyval.node) = createStructField((yyvsp[-1].str), (yyvsp[-2].dataType));
        free((yyvsp[-1].str));
    }
#line 2080 "parser.tab.c"
    break;

  case 59: /* struct_var_decl: KW_STRUCT ID ID ';'  */
#line 270 "parser.y"
                          {
        referenceStructType((yyvsp[-2].str), (yylsp[-2]).first_line);
        declareIdentifier((yyvsp[-1].str), (yylsp[-1]).first_line);
        (yyval.node) = createStructVarDecl((yyvsp[-2].str), (yyvsp[-1].str));
        free((yyvsp[-2].str));
        free((yyvsp[-1].str));
    }
#line 2092 "parser.tab.c"
    break;

  case 60: /* struct_assign: ID '.' ID '=' expr ';'  */
#line 280 "parser.y"
                             {
        referenceIdentifier((yyvsp[-5].str), (yylsp[-5]).first_line);
        (yyval.node) = createStructAssign((yyvsp[-5].str), (yyvsp[-3].str), (yyvsp[-1].node));
        free((yyvsp[-5].str));
        free((yyvsp[-3].str));
    }
#line 2103 "parser.tab.c"
    break;

  case 61: /* arg_list: expr  */
#line 289 "parser.y"
         { (yyval.node) = (yyvsp[0].node);}
#line 2109 "parser.tab.c"
    break;

  case 62: /* arg_list: arg_list ',' expr  */
#line 290 "parser.y"
                        { (yyval.node) = createArgList((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2115 "parser.tab.c"
    break;

  case 63: /* assign: ID '=' expr ';'  */
#line 294 "parser.y"
                    { 
        referenceIdentifier((yyvsp[-3].str), (yylsp[-3]).first_line);
        /* Create assignment node with variable name and expression */
        (yyval.node) = createAssign((yyvsp[-3].str), (yyvsp[-1].node));  /* $1 = ID, $3 = expr */
        free((yyvsp[-3].str));                   /* Free the identifier string */
    }
#line 2126 "parser.tab.c"
    break;

  case 64: /* assign: ID '[' expr ']' '=' expr ';'  */
#line 300 "parser.y"
                                   {
      referenceIdentifier((yyvsp[-6].str), (yylsp[-6]).first_line);
      (yyval.node) = createArrayAssign((yyvsp[-6].str), (yyvsp[-4].node), (yyvsp[-1].node));
      free((yyvsp[-6].str));
    }
#line 2136 "parser.tab.c"
    break;

  case 65: /* expr: LITERAL_NUM  */
#line 309 "parser.y"
                { (yyval.node) = createNum((yyvsp[0].num)); }
#line 2142 "parser.tab.c"
    break;

  case 66: /* expr: LITERAL_FLOAT  */
#line 310 "parser.y"
                    { (yyval.node) = createFloat((yyvsp[0].fnum)); }
#line 2148 "parser.tab.c"
    break;

  case 67: /* expr: LITERAL_CHAR  */
#line 311 "parser.y"
                   { (yyval.node) = createNum((yyvsp[0].num)); }
#line 2154 "parser.tab.c"
    break;

  case 68: /* expr: KW_TRUE  */
#line 312 "parser.y"
              { (yyval.node) = createBoolLiteral(1); }
#line 2160 "parser.tab.c"
    break;

  case 69: /* expr: KW_FALSE  */
#line 313 "parser.y"
               { (yyval.node) = createBoolLiteral(0); }
#line 2166 "parser.tab.c"
    break;

  case 70: /* expr: ID  */
#line 314 "parser.y"
         {
        referenceIdentifier((yyvsp[0].str), (yylsp[0]).first_line);
        (yyval.node) = createVar((yyvsp[0].str));
        free((yyvsp[0].str));
    }
#line 2176 "parser.tab.c"
    break;

  case 71: /* expr: ID '.' ID  */
#line 319 "parser.y"
                {
        referenceIdentifier((yyvsp[-2].str), (yylsp[-2]).first_line);
        (yyval.node) = createStructAccess((yyvsp[-2].str), (yyvsp[0].str));
        free((yyvsp[-2].str));
        free((yyvsp[0].str));
    }
#line 2187 "parser.tab.c"
    break;

  case 72: /* expr: ID '[' expr ']'  */
#line 325 "parser.y"
                      {
        referenceIdentifier((yyvsp[-3].str), (yylsp[-3]).first_line);
        (yyval.node) = createArrayAccess((yyvsp[-3].str), (yyvsp[-1].node));
        free((yyvsp[-3].str));
    }
#line 2197 "parser.tab.c"
    break;

  case 73: /* expr: ID '(' arg_list ')'  */
#line 330 "parser.y"
                          { (yyval.node) = createFuncCall((yyvsp[-3].str), (yyvsp[-1].node)); }
#line 2203 "parser.tab.c"
    break;

  case 74: /* expr: ID '(' ')'  */
#line 331 "parser.y"
                 { (yyval.node) = createFuncCall((yyvsp[-2].str), NULL); }
#line 2209 "parser.tab.c"
    break;

  case 75: /* expr: expr '+' expr  */
#line 332 "parser.y"
                    { (yyval.node) = createBinOp(OP_ADD, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2215 "parser.tab.c"
    break;

  case 76: /* expr: expr '-' expr  */
#line 333 "parser.y"
                    { (yyval.node) = createBinOp(OP_SUB, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2221 "parser.tab.c"
    break;

  case 77: /* expr: expr '*' expr  */
#line 334 "parser.y"
                    { (yyval.node) = createBinOp(OP_MUL, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2227 "parser.tab.c"
    break;

  case 78: /* expr: expr '/' expr  */
#line 335 "parser.y"
                    { (yyval.node) = createBinOp(OP_DIV, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2233 "parser.tab.c"
    break;

  case 79: /* expr: expr '>' expr  */
#line 336 "parser.y"
                    { (yyval.node) = createBinOp(OP_GT, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2239 "parser.tab.c"
    break;

  case 80: /* expr: expr '<' expr  */
#line 337 "parser.y"
                    { (yyval.node) = createBinOp(OP_LT, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2245 "parser.tab.c"
    break;

  case 81: /* expr: expr GEQ expr  */
#line 338 "parser.y"
                    { (yyval.node) = createBinOp(OP_GE, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2251 "parser.tab.c"
    break;

  case 82: /* expr: expr LEQ expr  */
#line 339 "parser.y"
                    { (yyval.node) = createBinOp(OP_LE, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2257 "parser.tab.c"
    break;

  case 83: /* expr: expr EQ expr  */
#line 340 "parser.y"
                   { (yyval.node) = createBinOp(OP_EQ, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2263 "parser.tab.c"
    break;

  case 84: /* expr: expr NEQ expr  */
#line 341 "parser.y"
                    { (yyval.node) = createBinOp(OP_NEQ, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2269 "parser.tab.c"
    break;

  case 85: /* expr: expr AND expr  */
#line 342 "parser.y"
                    { (yyval.node) = createBinOp(OP_AND, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2275 "parser.tab.c"
    break;

  case 86: /* expr: expr OR expr  */
#line 343 "parser.y"
                   { (yyval.node) = createBinOp(OP_OR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2281 "parser.tab.c"
    break;

  case 87: /* expr: NOT expr  */
#line 344 "parser.y"
               { (yyval.node) = createUnaryOp(UNOP_NOT, (yyvsp[0].node)); }
#line 2287 "parser.tab.c"
    break;

  case 88: /* expr: expr '?' expr ':' expr  */
#line 345 "parser.y"
                             { (yyval.node) = createConditionalExpr((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2293 "parser.tab.c"
    break;

  case 89: /* expr: '(' expr ')'  */
#line 346 "parser.y"
                   { (yyval.node) = (yyvsp[-1].node); }
#line 2299 "parser.tab.c"
    break;

  case 90: /* return_stmt: KW_RETURN expr ';'  */
#line 350 "parser.y"
                       { (yyval.node) = createReturn((yyvsp[-1].node)); }
#line 2305 "parser.tab.c"
    break;

  case 91: /* return_stmt: KW_RETURN ';'  */
#line 351 "parser.y"
                    { (yyval.node) = createReturn(NULL);}
#line 2311 "parser.tab.c"
    break;

  case 92: /* print_stmt: KW_PRINT '(' expr ')' ';'  */
#line 356 "parser.y"
                              { 
        /* Create print node with expression to print */
        (yyval.node) = createPrint((yyvsp[-2].node));  /* $3 is the expression inside parens */
    }
#line 2320 "parser.tab.c"
    break;


#line 2324 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 362 "parser.y"


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
