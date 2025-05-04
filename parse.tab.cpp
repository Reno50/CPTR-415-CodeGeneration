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
#line 1 "rustish_parser_file.y"

// Code for the bison file
// #include "lex.yy.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "ASTtree.h"

extern int yylineno;

void yyerror(const char *msg);
//void custom_error(SemanticError *error);
int yylex(void);
/* Our parser does not support:
a = [1, 2, 3, 4] // This array assignment syntax
*/


#line 91 "parse.tab.cpp"

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

#include "parse.tab.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_MAIN = 3,                       /* MAIN  */
  YYSYMBOL_LCURLY = 4,                     /* LCURLY  */
  YYSYMBOL_RCURLY = 5,                     /* RCURLY  */
  YYSYMBOL_IDENTIFIER = 6,                 /* IDENTIFIER  */
  YYSYMBOL_SEMICOLON = 7,                  /* SEMICOLON  */
  YYSYMBOL_NUMBER = 8,                     /* NUMBER  */
  YYSYMBOL_ASSIGN = 9,                     /* ASSIGN  */
  YYSYMBOL_PRINT = 10,                     /* PRINT  */
  YYSYMBOL_READ = 11,                      /* READ  */
  YYSYMBOL_COMMA = 12,                     /* COMMA  */
  YYSYMBOL_PRINTLN = 13,                   /* PRINTLN  */
  YYSYMBOL_ARROW = 14,                     /* ARROW  */
  YYSYMBOL_COLON = 15,                     /* COLON  */
  YYSYMBOL_FN = 16,                        /* FN  */
  YYSYMBOL_I32 = 17,                       /* I32  */
  YYSYMBOL_LET = 18,                       /* LET  */
  YYSYMBOL_MUT = 19,                       /* MUT  */
  YYSYMBOL_BOOL = 20,                      /* BOOL  */
  YYSYMBOL_FALSE = 21,                     /* FALSE  */
  YYSYMBOL_TRUE = 22,                      /* TRUE  */
  YYSYMBOL_INT_ARR = 23,                   /* INT_ARR  */
  YYSYMBOL_BOOL_ARR = 24,                  /* BOOL_ARR  */
  YYSYMBOL_LPAREN = 25,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 26,                    /* RPAREN  */
  YYSYMBOL_PLUS = 27,                      /* PLUS  */
  YYSYMBOL_MINUS = 28,                     /* MINUS  */
  YYSYMBOL_TIMES = 29,                     /* TIMES  */
  YYSYMBOL_DIV = 30,                       /* DIV  */
  YYSYMBOL_MOD = 31,                       /* MOD  */
  YYSYMBOL_AND = 32,                       /* AND  */
  YYSYMBOL_OR = 33,                        /* OR  */
  YYSYMBOL_NOT = 34,                       /* NOT  */
  YYSYMBOL_IF = 35,                        /* IF  */
  YYSYMBOL_ELSE = 36,                      /* ELSE  */
  YYSYMBOL_WHILE = 37,                     /* WHILE  */
  YYSYMBOL_RETURN = 38,                    /* RETURN  */
  YYSYMBOL_LSQUARE = 39,                   /* LSQUARE  */
  YYSYMBOL_RSQUARE = 40,                   /* RSQUARE  */
  YYSYMBOL_NE = 41,                        /* NE  */
  YYSYMBOL_EQ = 42,                        /* EQ  */
  YYSYMBOL_LT = 43,                        /* LT  */
  YYSYMBOL_GT = 44,                        /* GT  */
  YYSYMBOL_LE = 45,                        /* LE  */
  YYSYMBOL_GE = 46,                        /* GE  */
  YYSYMBOL_DOT = 47,                       /* DOT  */
  YYSYMBOL_LEN = 48,                       /* LEN  */
  YYSYMBOL_YYACCEPT = 49,                  /* $accept  */
  YYSYMBOL_program = 50,                   /* program  */
  YYSYMBOL_funcDefList = 51,               /* funcDefList  */
  YYSYMBOL_mainDef = 52,                   /* mainDef  */
  YYSYMBOL_funcDef = 53,                   /* funcDef  */
  YYSYMBOL_paramsList = 54,                /* paramsList  */
  YYSYMBOL_varDec = 55,                    /* varDec  */
  YYSYMBOL_type = 56,                      /* type  */
  YYSYMBOL_funcBody = 57,                  /* funcBody  */
  YYSYMBOL_localVarDecList = 58,           /* localVarDecList  */
  YYSYMBOL_statementList = 59,             /* statementList  */
  YYSYMBOL_statement = 60,                 /* statement  */
  YYSYMBOL_funcCallExp = 61,               /* funcCallExp  */
  YYSYMBOL_usedArgs = 62,                  /* usedArgs  */
  YYSYMBOL_expression = 63,                /* expression  */
  YYSYMBOL_identifier = 64,                /* identifier  */
  YYSYMBOL_number = 65                     /* number  */
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
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   504

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  167

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   303


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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    90,    90,   103,   109,   113,   117,   125,   133,   136,
     140,   145,   151,   161,   165,   169,   173,   177,   181,   186,
     191,   197,   201,   205,   209,   212,   215,   218,   221,   224,
     227,   230,   233,   236,   239,   242,   245,   248,   251,   254,
     258,   262,   266,   270,   274,   277,   280,   283,   286,   289,
     292,   295,   298,   301,   307,   310,   313,   316,   319,   322,
     325,   328,   331,   334,   337,   340,   343,   346,   350,   355
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
  "\"end of file\"", "error", "\"invalid token\"", "MAIN", "LCURLY",
  "RCURLY", "IDENTIFIER", "SEMICOLON", "NUMBER", "ASSIGN", "PRINT", "READ",
  "COMMA", "PRINTLN", "ARROW", "COLON", "FN", "I32", "LET", "MUT", "BOOL",
  "FALSE", "TRUE", "INT_ARR", "BOOL_ARR", "LPAREN", "RPAREN", "PLUS",
  "MINUS", "TIMES", "DIV", "MOD", "AND", "OR", "NOT", "IF", "ELSE",
  "WHILE", "RETURN", "LSQUARE", "RSQUARE", "NE", "EQ", "LT", "GT", "LE",
  "GE", "DOT", "LEN", "$accept", "program", "funcDefList", "mainDef",
  "funcDef", "paramsList", "varDec", "type", "funcBody", "localVarDecList",
  "statementList", "statement", "funcCallExp", "usedArgs", "expression",
  "identifier", "number", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-84)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -84,    26,    20,   -84,    38,   -84,   -84,    24,   -84,    80,
      19,     3,    75,    90,    11,   -84,    94,   -84,   -84,     8,
     -84,    82,    92,     8,   103,   -84,   -84,    73,    75,   -84,
       8,   -84,   -84,    89,     5,    -1,     6,   -84,    75,    82,
     -84,   -84,    85,   102,   422,   422,   414,   -84,   121,    56,
     122,   -84,   122,   -84,   -84,   124,   422,   422,   -84,   104,
     -84,   -84,   422,   422,   422,   -84,    70,   -20,   -84,   113,
     -84,   140,   -84,   422,   422,   125,   126,   128,   129,   130,
     422,   108,   109,   -84,    22,   322,    52,   107,   431,    93,
     -84,   -84,   422,   422,   422,   422,   422,   422,   422,   422,
     422,   422,   422,   422,   422,   422,   105,   -84,   -84,   167,
      63,   422,   422,   422,   422,   422,   438,   -84,   -84,   422,
     143,   144,   -84,   -84,   371,    93,    93,   -84,   -84,   -84,
     -84,    93,   160,   160,   160,   160,   160,   160,   458,   -84,
     380,   -84,   -84,   194,   221,   248,   275,   302,   151,   322,
     -84,   -84,   116,   -84,   -84,   -84,   -84,   -84,   -84,   -84,
     422,   158,   329,   -84,   -84,   389,   -84
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,     1,     0,     2,     3,     0,    68,     0,
       0,     0,     0,     0,     0,    11,     0,    21,     5,     0,
       9,     0,     0,     0,    23,    13,    14,     0,     0,    10,
       0,     7,    12,     0,     0,     0,     0,     8,     0,     0,
      19,    24,     0,     0,     0,     0,     0,    22,     0,     0,
       0,    17,     0,    18,     6,     0,    43,    43,    69,     0,
      56,    57,     0,     0,     0,    44,     0,    49,    48,     0,
      39,     0,    37,     0,    43,     0,     0,     0,     0,     0,
       0,     0,     0,    20,     0,    41,     0,     0,     0,    67,
      66,    23,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    23,    38,     0,
       0,     0,     0,     0,     0,     0,     0,    15,    16,     0,
       0,     0,    55,    45,     0,    50,    51,    52,    53,    54,
      58,    59,    61,    60,    65,    64,    62,    63,     0,    46,
       0,    25,    40,     0,     0,     0,     0,     0,     0,    42,
      32,    33,    34,    47,    36,    26,    27,    28,    29,    30,
       0,     0,     0,    23,    31,     0,    35
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -84,   -84,   -84,   -84,   -84,   -84,    -7,    96,    54,   -84,
     -83,   -84,   -33,   -41,   -42,    -4,    16
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,     5,     6,    14,    15,    28,    18,    24,
      34,    47,    65,    84,    85,    67,    68
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
       9,    48,    66,    69,    71,    74,    50,    16,   124,     8,
      40,     8,    41,    52,    29,    42,    86,    16,    43,   105,
      88,    89,    90,    21,   140,    25,     3,   106,    26,    13,
      49,   109,    55,   110,   119,    16,     4,    22,   116,    51,
      44,     7,    45,    46,     8,    12,    53,    27,   120,    10,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   119,    73,    81,    20,    82,   143,
     144,   145,   146,   147,    91,   119,    31,   149,   121,    17,
     165,    74,    37,    75,    76,    77,    78,    79,     8,   142,
      35,    48,    54,    36,    17,    80,    17,    92,    93,    94,
      95,    96,    97,    98,    19,    11,    30,    48,    39,    23,
      56,    99,   100,   101,   102,   103,   104,   107,   162,    32,
      49,    33,    94,    95,    96,    97,    38,    57,    72,    87,
      58,    83,    48,   122,   111,   112,    49,   113,   114,   115,
      92,    93,    94,    95,    96,    97,    98,   108,   117,   118,
     150,   151,   161,   139,    99,   100,   101,   102,   103,   104,
     160,    49,   163,     0,     0,     0,     0,    92,    93,    94,
      95,    96,    97,    98,   141,     0,     0,     0,     0,     0,
       0,    99,   100,   101,   102,   103,   104,    92,    93,    94,
      95,    96,    97,    98,    92,    93,    94,    95,    96,    97,
      98,   155,     0,     0,     0,     0,     0,     0,    99,   100,
     101,   102,   103,   104,     0,     0,     0,     0,     0,     0,
       0,    92,    93,    94,    95,    96,    97,    98,   156,     0,
       0,     0,     0,     0,     0,    99,   100,   101,   102,   103,
     104,     0,     0,     0,     0,     0,     0,     0,    92,    93,
      94,    95,    96,    97,    98,   157,     0,     0,     0,     0,
       0,     0,    99,   100,   101,   102,   103,   104,     0,     0,
       0,     0,     0,     0,     0,    92,    93,    94,    95,    96,
      97,    98,   158,     0,     0,     0,     0,     0,     0,    99,
     100,   101,   102,   103,   104,     0,     0,     0,     0,     0,
       0,     0,    92,    93,    94,    95,    96,    97,    98,   159,
       0,     0,     0,     0,     0,     0,    99,   100,   101,   102,
     103,   104,     0,     0,     0,     0,     0,     0,     0,    92,
      93,    94,    95,    96,    97,    98,   164,     0,     0,     0,
       0,     0,     0,    99,   100,   101,   102,   103,   104,    92,
      93,    94,    95,    96,    97,    98,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,     0,
      99,   100,   101,   102,   103,   104,   152,     8,    41,     0,
       0,    42,     0,     0,    43,   154,     8,    41,     0,     0,
      42,     0,     0,    43,   166,     8,    41,     0,     0,    42,
       0,     0,    43,     0,     0,     0,    44,     0,    45,    46,
       0,     0,     0,     0,     0,    44,     0,    45,    46,     0,
       8,    70,    58,     0,    44,    59,    45,    46,     8,     0,
      58,     0,     0,    59,     0,    60,    61,     0,     0,    62,
       0,     0,    63,    60,    61,     0,     0,    62,    64,     0,
      63,     0,     0,     0,     0,     0,    64,   123,    92,    93,
      94,    95,    96,    97,    98,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   148,    99,
     100,   101,   102,   103,   104,    92,    93,    94,    95,    96,
      97,    98,     0,     0,     0,     0,     0,     0,   153,    99,
     100,   101,   102,   103,   104
};

static const yytype_int16 yycheck[] =
{
       4,    34,    44,    45,    46,    25,     7,    11,    91,     6,
       5,     6,     7,     7,    21,    10,    57,    21,    13,    39,
      62,    63,    64,    12,   107,    17,     0,    47,    20,    26,
      34,    73,    39,    74,    12,    39,    16,    26,    80,    40,
      35,     3,    37,    38,     6,    26,    40,    39,    26,    25,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,    12,     9,    50,    13,    52,   111,
     112,   113,   114,   115,     4,    12,    22,   119,    26,     4,
     163,    25,    28,    27,    28,    29,    30,    31,     6,    26,
      17,   124,    38,    20,     4,    39,     4,    27,    28,    29,
      30,    31,    32,    33,    14,    25,    14,   140,    19,    15,
      25,    41,    42,    43,    44,    45,    46,     4,   160,    23,
     124,    18,    29,    30,    31,    32,    30,    25,     7,    25,
       8,     7,   165,    26,     9,     9,   140,     9,     9,     9,
      27,    28,    29,    30,    31,    32,    33,     7,    40,    40,
       7,     7,    36,    48,    41,    42,    43,    44,    45,    46,
       9,   165,     4,    -1,    -1,    -1,    -1,    27,    28,    29,
      30,    31,    32,    33,     7,    -1,    -1,    -1,    -1,    -1,
      -1,    41,    42,    43,    44,    45,    46,    27,    28,    29,
      30,    31,    32,    33,    27,    28,    29,    30,    31,    32,
      33,     7,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,
      43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    27,    28,    29,    30,    31,    32,    33,     7,    -1,
      -1,    -1,    -1,    -1,    -1,    41,    42,    43,    44,    45,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,    28,
      29,    30,    31,    32,    33,     7,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    42,    43,    44,    45,    46,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    27,    28,    29,    30,    31,
      32,    33,     7,    -1,    -1,    -1,    -1,    -1,    -1,    41,
      42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    27,    28,    29,    30,    31,    32,    33,     7,
      -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    43,    44,
      45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,
      28,    29,    30,    31,    32,    33,     7,    -1,    -1,    -1,
      -1,    -1,    -1,    41,    42,    43,    44,    45,    46,    27,
      28,    29,    30,    31,    32,    33,    27,    28,    29,    30,
      31,    32,    33,    41,    42,    43,    44,    45,    46,    -1,
      41,    42,    43,    44,    45,    46,     5,     6,     7,    -1,
      -1,    10,    -1,    -1,    13,     5,     6,     7,    -1,    -1,
      10,    -1,    -1,    13,     5,     6,     7,    -1,    -1,    10,
      -1,    -1,    13,    -1,    -1,    -1,    35,    -1,    37,    38,
      -1,    -1,    -1,    -1,    -1,    35,    -1,    37,    38,    -1,
       6,     7,     8,    -1,    35,    11,    37,    38,     6,    -1,
       8,    -1,    -1,    11,    -1,    21,    22,    -1,    -1,    25,
      -1,    -1,    28,    21,    22,    -1,    -1,    25,    34,    -1,
      28,    -1,    -1,    -1,    -1,    -1,    34,    26,    27,    28,
      29,    30,    31,    32,    33,    27,    28,    29,    30,    31,
      32,    33,    41,    42,    43,    44,    45,    46,    40,    41,
      42,    43,    44,    45,    46,    27,    28,    29,    30,    31,
      32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    40,    41,
      42,    43,    44,    45,    46
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    50,    51,     0,    16,    52,    53,     3,     6,    64,
      25,    25,    26,    26,    54,    55,    64,     4,    57,    14,
      57,    12,    26,    15,    58,    17,    20,    39,    56,    55,
      14,    57,    56,    18,    59,    17,    20,    57,    56,    19,
       5,     7,    10,    13,    35,    37,    38,    60,    61,    64,
       7,    40,     7,    40,    57,    55,    25,    25,     8,    11,
      21,    22,    25,    28,    34,    61,    63,    64,    65,    63,
       7,    63,     7,     9,    25,    27,    28,    29,    30,    31,
      39,    65,    65,     7,    62,    63,    62,    25,    63,    63,
      63,     4,    27,    28,    29,    30,    31,    32,    33,    41,
      42,    43,    44,    45,    46,    39,    47,     4,     7,    63,
      62,     9,     9,     9,     9,     9,    63,    40,    40,    12,
      26,    26,    26,    26,    59,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    48,
      59,     7,    26,    63,    63,    63,    63,    63,    40,    63,
       7,     7,     5,    40,     5,     7,     7,     7,     7,     7,
       9,    36,    63,     4,     7,    59,     5
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    49,    50,    51,    51,    52,    53,    53,    53,    53,
      54,    54,    55,    56,    56,    56,    56,    56,    56,    57,
      58,    58,    59,    59,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      61,    62,    62,    62,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    64,    65
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     0,     5,     8,     6,     7,     5,
       3,     1,     3,     1,     1,     5,     5,     3,     3,     4,
       5,     0,     2,     0,     1,     4,     5,     5,     5,     5,
       5,     7,     5,     5,     5,     9,     5,     2,     3,     2,
       4,     1,     3,     0,     1,     3,     3,     4,     1,     1,
       3,     3,     3,     3,     3,     3,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     1,     1
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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
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

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: funcDefList mainDef  */
#line 90 "rustish_parser_file.y"
                                     {
                  (yyval.program_node) = new ProgramNode((yyvsp[0].main_def_node), (yyvsp[-1].func_def_list_node)); // Main first, then func_def_list
                  //abstract_syntax_tree = $$;
                  // No need to check functions, as all the code should be valid, but we do need to trickle up type info
                  (yyval.program_node)->check_funcs();
                  std::cout << "Checked!\n";
                  std::ofstream context;
                  context.open("test.asm", std::ios::out); // Write output only and append it
                  (yyval.program_node)->emit_code(context);

                  std::cout << "Done!\n";
               }
#line 1591 "parse.tab.cpp"
    break;

  case 3: /* funcDefList: funcDefList funcDef  */
#line 103 "rustish_parser_file.y"
                                     {
                     // Append the funcDef to funcDefList's list of function definitions
                     (yyvsp[-1].func_def_list_node)->push_back((yyvsp[0].func_def_node));
                     (yyval.func_def_list_node) = (yyvsp[-1].func_def_list_node);
                     // Adds funcDef to funcDefList at the back
               }
#line 1602 "parse.tab.cpp"
    break;

  case 4: /* funcDefList: %empty  */
#line 109 "rustish_parser_file.y"
                             { // There are no functions (or no more functions?)
                  (yyval.func_def_list_node) = new std::vector<FuncDefNode *>;
               }
#line 1610 "parse.tab.cpp"
    break;

  case 5: /* mainDef: FN MAIN LPAREN RPAREN funcBody  */
#line 113 "rustish_parser_file.y"
                                                { // Just the funcBody this time, since name, return type, and param list are known
                  (yyval.main_def_node) = new MainDefNode((yyvsp[0].func_body_node));
               }
#line 1618 "parse.tab.cpp"
    break;

  case 6: /* funcDef: FN identifier LPAREN paramsList RPAREN ARROW type funcBody  */
#line 117 "rustish_parser_file.y"
                                                                            { // As with each of these funcDefs, create an instance of the function class with identifier, param list, type, and funcBody child
                  // Construct parameter table from parameter list
                  VarSymbolTable *var_table = new VarSymbolTable("var_table");
                  for (int i = 0; i < (yyvsp[-4].params_list_node)->size(); i++) {
                     var_table->insert((yyvsp[-4].params_list_node)->at(i)->name, (yyvsp[-4].params_list_node)->at(i));
                  }
                  (yyval.func_def_node) = new FuncDefNode((yyvsp[-6].indentifier_node), var_table, (yyvsp[-4].params_list_node), (yyvsp[-1].type_node), (yyvsp[0].func_body_node)); // identifier, parameter table, parameter vector, return type, body
               }
#line 1631 "parse.tab.cpp"
    break;

  case 7: /* funcDef: FN identifier LPAREN paramsList RPAREN funcBody  */
#line 125 "rustish_parser_file.y"
                                                                 {
                  // Construct parameter table from parameter list
                  VarSymbolTable *var_table = new VarSymbolTable("var_table");
                  for (int i = 0; i < (yyvsp[-2].params_list_node)->size(); i++) {
                     var_table->insert((yyvsp[-2].params_list_node)->at(i)->name, (yyvsp[-2].params_list_node)->at(i));
                  }
                  (yyval.func_def_node) = new FuncDefNode((yyvsp[-4].indentifier_node), var_table, (yyvsp[-2].params_list_node), NULL, (yyvsp[0].func_body_node)); // Null for an empty return type i guess??
               }
#line 1644 "parse.tab.cpp"
    break;

  case 8: /* funcDef: FN identifier LPAREN RPAREN ARROW type funcBody  */
#line 133 "rustish_parser_file.y"
                                                                 {
                  (yyval.func_def_node) = new FuncDefNode((yyvsp[-5].indentifier_node), NULL, NULL, (yyvsp[-1].type_node), (yyvsp[0].func_body_node)); // Null for an empty param list
               }
#line 1652 "parse.tab.cpp"
    break;

  case 9: /* funcDef: FN identifier LPAREN RPAREN funcBody  */
#line 136 "rustish_parser_file.y"
                                                      {
                  (yyval.func_def_node) = new FuncDefNode((yyvsp[-3].indentifier_node), NULL, NULL, NULL, (yyvsp[0].func_body_node));
               }
#line 1660 "parse.tab.cpp"
    break;

  case 10: /* paramsList: paramsList COMMA varDec  */
#line 140 "rustish_parser_file.y"
                                         {// Add varDec to the param list of the paramlist class
                  (yyvsp[0].var_dec_node)->initialized = true;
                  (yyvsp[-2].params_list_node)->push_back((yyvsp[0].var_dec_node));
                  (yyval.params_list_node) = (yyvsp[-2].params_list_node);
               }
#line 1670 "parse.tab.cpp"
    break;

  case 11: /* paramsList: varDec  */
#line 145 "rustish_parser_file.y"
                        { // Create the ParamList out of the varDec
                  (yyval.params_list_node) = new std::vector<VariableInfo *>;
                  (yyvsp[0].var_dec_node)->initialized = true;
                  (yyval.params_list_node)->push_back((yyvsp[0].var_dec_node));
               }
#line 1680 "parse.tab.cpp"
    break;

  case 12: /* varDec: identifier COLON type  */
#line 151 "rustish_parser_file.y"
                                       { // Just a variable class with an identifier and type
                  VariableInfo *var_info = new VariableInfo;
                  var_info->name = *((yyvsp[-2].indentifier_node)->identifier);
                  var_info->type = (yyvsp[0].type_node)->type;
                  var_info->initialized = false;
                  var_info->line_num = yylineno;
                  var_info->size = (yyvsp[0].type_node)->size;
                  (yyval.var_dec_node) = var_info;
               }
#line 1694 "parse.tab.cpp"
    break;

  case 13: /* type: I32  */
#line 161 "rustish_parser_file.y"
                     {// For each of these, just make a type class with the type and maybe array size if we choose to modify this to include that in the grammar
                  (yyval.type_node) = new TypeNode(RustishType::i32_t); // Not entirely sure if this is the best convention??
                  (yyval.type_node)->size = 4;
               }
#line 1703 "parse.tab.cpp"
    break;

  case 14: /* type: BOOL  */
#line 165 "rustish_parser_file.y"
                      {
                  (yyval.type_node) = new TypeNode(RustishType::bool_t);
                  (yyval.type_node)->size = 4;
               }
#line 1712 "parse.tab.cpp"
    break;

  case 15: /* type: LSQUARE I32 SEMICOLON number RSQUARE  */
#line 169 "rustish_parser_file.y"
                                                      {
                  (yyval.type_node) = new TypeNode(RustishType::i32array_t); // Length of number
                  (yyval.type_node)->size = atoi(((yyvsp[-1].number_node)->number)->c_str());
               }
#line 1721 "parse.tab.cpp"
    break;

  case 16: /* type: LSQUARE BOOL SEMICOLON number RSQUARE  */
#line 173 "rustish_parser_file.y"
                                                       {
                  (yyval.type_node) = new TypeNode(RustishType::boolarray_t); // Length of number
                  (yyval.type_node)->size = atoi(((yyvsp[-1].number_node)->number)->c_str());
               }
#line 1730 "parse.tab.cpp"
    break;

  case 17: /* type: LSQUARE I32 RSQUARE  */
#line 177 "rustish_parser_file.y"
                                     {
                  (yyval.type_node) = new TypeNode(RustishType::i32array_t); // Length of 4 by default
                  (yyval.type_node)->size = 4;
               }
#line 1739 "parse.tab.cpp"
    break;

  case 18: /* type: LSQUARE BOOL RSQUARE  */
#line 181 "rustish_parser_file.y"
                                      {
                  (yyval.type_node) = new TypeNode(RustishType::boolarray_t); // Length of 4 by default
                  (yyval.type_node)->size = 4;
               }
#line 1748 "parse.tab.cpp"
    break;

  case 19: /* funcBody: LCURLY localVarDecList statementList RCURLY  */
#line 186 "rustish_parser_file.y"
                                                             { 
                  // Note that this doesn't leave room for variables mixed in with statements
                  (yyval.func_body_node) = new FuncBodyNode((yyvsp[-2].decl_list_node), (yyvsp[-1].statement_list_node), yylineno); // Vector of varDec, statements
               }
#line 1757 "parse.tab.cpp"
    break;

  case 20: /* localVarDecList: localVarDecList LET MUT varDec SEMICOLON  */
#line 191 "rustish_parser_file.y"
                                                          {
                  // Contains all local variable declarations in a function
                  (yyvsp[-1].var_dec_node)->initialized = false;
                  (yyvsp[-4].decl_list_node)->insert((yyvsp[-1].var_dec_node)->name, (yyvsp[-1].var_dec_node)); // Insert at beginning
                  (yyval.decl_list_node) = (yyvsp[-4].decl_list_node);
               }
#line 1768 "parse.tab.cpp"
    break;

  case 21: /* localVarDecList: %empty  */
#line 197 "rustish_parser_file.y"
                              {
                  (yyval.decl_list_node) = new VarSymbolTable("localVarDecList");
               }
#line 1776 "parse.tab.cpp"
    break;

  case 22: /* statementList: statementList statement  */
#line 201 "rustish_parser_file.y"
                                         {// Contains all the statements in a function 
                  (yyvsp[-1].statement_list_node)->push_back((yyvsp[0].statement_node));
                  (yyval.statement_list_node) = (yyvsp[-1].statement_list_node);
               }
#line 1785 "parse.tab.cpp"
    break;

  case 23: /* statementList: %empty  */
#line 205 "rustish_parser_file.y"
                               {// To start the statement list
                  (yyval.statement_list_node) = new std::vector<StatementNode *>;
               }
#line 1793 "parse.tab.cpp"
    break;

  case 24: /* statement: SEMICOLON  */
#line 209 "rustish_parser_file.y"
                           {
                  (yyval.statement_node) = new StatementNode();
               }
#line 1801 "parse.tab.cpp"
    break;

  case 25: /* statement: identifier ASSIGN expression SEMICOLON  */
#line 212 "rustish_parser_file.y"
                                                        {
                  (yyval.statement_node) = new AssignmentStatementNode((yyvsp[-3].indentifier_node), (yyvsp[-1].expression_node));
               }
#line 1809 "parse.tab.cpp"
    break;

  case 26: /* statement: identifier PLUS ASSIGN expression SEMICOLON  */
#line 215 "rustish_parser_file.y"
                                                             {
                  (yyval.statement_node) = new OtherOpStatementNode((yyvsp[-4].indentifier_node), (yyvsp[-1].expression_node), OtherOperators::PLUS_OP);
               }
#line 1817 "parse.tab.cpp"
    break;

  case 27: /* statement: identifier MINUS ASSIGN expression SEMICOLON  */
#line 218 "rustish_parser_file.y"
                                                              {
                  (yyval.statement_node) = new OtherOpStatementNode((yyvsp[-4].indentifier_node), (yyvsp[-1].expression_node), OtherOperators::MINUS_OP);
               }
#line 1825 "parse.tab.cpp"
    break;

  case 28: /* statement: identifier TIMES ASSIGN expression SEMICOLON  */
#line 221 "rustish_parser_file.y"
                                                              {
                  (yyval.statement_node) = new OtherOpStatementNode((yyvsp[-4].indentifier_node), (yyvsp[-1].expression_node), OtherOperators::TIMES_OP);
               }
#line 1833 "parse.tab.cpp"
    break;

  case 29: /* statement: identifier DIV ASSIGN expression SEMICOLON  */
#line 224 "rustish_parser_file.y"
                                                            {
                  (yyval.statement_node) = new OtherOpStatementNode((yyvsp[-4].indentifier_node), (yyvsp[-1].expression_node), OtherOperators::DIV_OP);
               }
#line 1841 "parse.tab.cpp"
    break;

  case 30: /* statement: identifier MOD ASSIGN expression SEMICOLON  */
#line 227 "rustish_parser_file.y"
                                                            {
                  (yyval.statement_node) = new OtherOpStatementNode((yyvsp[-4].indentifier_node), (yyvsp[-1].expression_node), OtherOperators::MOD_OP);
               }
#line 1849 "parse.tab.cpp"
    break;

  case 31: /* statement: identifier LSQUARE expression RSQUARE ASSIGN expression SEMICOLON  */
#line 230 "rustish_parser_file.y"
                                                                                   {// array[0] = 1
                  (yyval.statement_node) = new ArrayAssignmentStatementNode((yyvsp[-6].indentifier_node), (yyvsp[-4].expression_node), (yyvsp[-1].expression_node));
               }
#line 1857 "parse.tab.cpp"
    break;

  case 32: /* statement: PRINT LPAREN usedArgs RPAREN SEMICOLON  */
#line 233 "rustish_parser_file.y"
                                                        {
                  (yyval.statement_node) = new PrintStatementNode((yyvsp[-2].used_args_node));
               }
#line 1865 "parse.tab.cpp"
    break;

  case 33: /* statement: PRINTLN LPAREN usedArgs RPAREN SEMICOLON  */
#line 236 "rustish_parser_file.y"
                                                          {
                  (yyval.statement_node) = new PrintlnStatementNode((yyvsp[-2].used_args_node));
               }
#line 1873 "parse.tab.cpp"
    break;

  case 34: /* statement: IF expression LCURLY statementList RCURLY  */
#line 239 "rustish_parser_file.y"
                                                           {
                  (yyval.statement_node) = new IfStatementNode((yyvsp[-3].expression_node), (yyvsp[-1].statement_list_node));
               }
#line 1881 "parse.tab.cpp"
    break;

  case 35: /* statement: IF expression LCURLY statementList RCURLY ELSE LCURLY statementList RCURLY  */
#line 242 "rustish_parser_file.y"
                                                                                            {
                  (yyval.statement_node) = new IfElseStatementNode((yyvsp[-7].expression_node), (yyvsp[-5].statement_list_node), (yyvsp[-1].statement_list_node));
               }
#line 1889 "parse.tab.cpp"
    break;

  case 36: /* statement: WHILE expression LCURLY statementList RCURLY  */
#line 245 "rustish_parser_file.y"
                                                              {
                  (yyval.statement_node) = new WhileStatementNode((yyvsp[-3].expression_node), (yyvsp[-1].statement_list_node));
               }
#line 1897 "parse.tab.cpp"
    break;

  case 37: /* statement: funcCallExp SEMICOLON  */
#line 248 "rustish_parser_file.y"
                                       {
                  (yyval.statement_node) = new FuncCallStatementNode((yyvsp[-1].func_call_exp_node));
               }
#line 1905 "parse.tab.cpp"
    break;

  case 38: /* statement: RETURN expression SEMICOLON  */
#line 251 "rustish_parser_file.y"
                                             {
                  (yyval.statement_node) = new ReturnStatementNode((yyvsp[-1].expression_node));
               }
#line 1913 "parse.tab.cpp"
    break;

  case 39: /* statement: RETURN SEMICOLON  */
#line 254 "rustish_parser_file.y"
                                  {
                  (yyval.statement_node) = new ReturnStatementNode(new ExpressionNode());
               }
#line 1921 "parse.tab.cpp"
    break;

  case 40: /* funcCallExp: identifier LPAREN usedArgs RPAREN  */
#line 258 "rustish_parser_file.y"
                                                   {
                  (yyval.func_call_exp_node) = new FuncCallExpressionNode((yyvsp[-3].indentifier_node), (yyvsp[-1].used_args_node), yylineno);
               }
#line 1929 "parse.tab.cpp"
    break;

  case 41: /* usedArgs: expression  */
#line 262 "rustish_parser_file.y"
                            {
                  (yyval.used_args_node) = new std::vector<ExpressionNode *>;
                  (yyval.used_args_node)->push_back((yyvsp[0].expression_node));
               }
#line 1938 "parse.tab.cpp"
    break;

  case 42: /* usedArgs: usedArgs COMMA expression  */
#line 266 "rustish_parser_file.y"
                                           {
                  (yyvsp[-2].used_args_node)->push_back((yyvsp[0].expression_node));
                  (yyval.used_args_node) = (yyvsp[-2].used_args_node);
               }
#line 1947 "parse.tab.cpp"
    break;

  case 43: /* usedArgs: %empty  */
#line 270 "rustish_parser_file.y"
                               {
                  (yyval.used_args_node) = nullptr;
               }
#line 1955 "parse.tab.cpp"
    break;

  case 44: /* expression: funcCallExp  */
#line 274 "rustish_parser_file.y"
                             {
                  (yyval.expression_node) = (yyvsp[0].func_call_exp_node);
               }
#line 1963 "parse.tab.cpp"
    break;

  case 45: /* expression: LPAREN expression RPAREN  */
#line 277 "rustish_parser_file.y"
                                          {
                  (yyval.expression_node) = (yyvsp[-1].expression_node);
               }
#line 1971 "parse.tab.cpp"
    break;

  case 46: /* expression: identifier DOT LEN  */
#line 280 "rustish_parser_file.y"
                                    {
                  (yyval.expression_node) = new ArrayLengthExpressionNode((yyvsp[-2].indentifier_node), yylineno);
               }
#line 1979 "parse.tab.cpp"
    break;

  case 47: /* expression: identifier LSQUARE expression RSQUARE  */
#line 283 "rustish_parser_file.y"
                                                       {
                  (yyval.expression_node) = new ArrayAccessExpressionNode((yyvsp[-3].indentifier_node), (yyvsp[-1].expression_node), yylineno);
               }
#line 1987 "parse.tab.cpp"
    break;

  case 48: /* expression: number  */
#line 286 "rustish_parser_file.y"
                        { 
                  (yyval.expression_node) = new NumberExpressionNode((yyvsp[0].number_node), yylineno);
               }
#line 1995 "parse.tab.cpp"
    break;

  case 49: /* expression: identifier  */
#line 289 "rustish_parser_file.y"
                            {
                  (yyval.expression_node) = new IdentifierExpressionNode((yyvsp[0].indentifier_node), yylineno);
               }
#line 2003 "parse.tab.cpp"
    break;

  case 50: /* expression: expression PLUS expression  */
#line 292 "rustish_parser_file.y"
                                            {
                  (yyval.expression_node) = new BinaryExpressionNode((yyvsp[-2].expression_node), (yyvsp[0].expression_node), BinaryOperator::PLUS_OP, yylineno);
               }
#line 2011 "parse.tab.cpp"
    break;

  case 51: /* expression: expression MINUS expression  */
#line 295 "rustish_parser_file.y"
                                             {
                  (yyval.expression_node) = new BinaryExpressionNode((yyvsp[-2].expression_node), (yyvsp[0].expression_node), BinaryOperator::MINUS_OP, yylineno);
               }
#line 2019 "parse.tab.cpp"
    break;

  case 52: /* expression: expression TIMES expression  */
#line 298 "rustish_parser_file.y"
                                             {
                  (yyval.expression_node) = new BinaryExpressionNode((yyvsp[-2].expression_node), (yyvsp[0].expression_node), BinaryOperator::TIMES_OP, yylineno);
               }
#line 2027 "parse.tab.cpp"
    break;

  case 53: /* expression: expression DIV expression  */
#line 301 "rustish_parser_file.y"
                                           {
                  if ((yyvsp[0].expression_node) == 0) {
                     yyerror("Division by zero error!\n");
                  }
                  (yyval.expression_node) = new BinaryExpressionNode((yyvsp[-2].expression_node), (yyvsp[0].expression_node), BinaryOperator::DIV_OP, yylineno);
               }
#line 2038 "parse.tab.cpp"
    break;

  case 54: /* expression: expression MOD expression  */
#line 307 "rustish_parser_file.y"
                                           {
                  (yyval.expression_node) = new BinaryExpressionNode((yyvsp[-2].expression_node), (yyvsp[0].expression_node), BinaryOperator::MOD_OP, yylineno);
               }
#line 2046 "parse.tab.cpp"
    break;

  case 55: /* expression: READ LPAREN RPAREN  */
#line 310 "rustish_parser_file.y"
                                    {
                  (yyval.expression_node) = new ReadExpressionNode(yylineno);
               }
#line 2054 "parse.tab.cpp"
    break;

  case 56: /* expression: FALSE  */
#line 313 "rustish_parser_file.y"
                       {
                  (yyval.expression_node) = new FalseExpressionNode(yylineno);
               }
#line 2062 "parse.tab.cpp"
    break;

  case 57: /* expression: TRUE  */
#line 316 "rustish_parser_file.y"
                      { 
                  (yyval.expression_node) = new TrueExpressionNode(yylineno);
               }
#line 2070 "parse.tab.cpp"
    break;

  case 58: /* expression: expression AND expression  */
#line 319 "rustish_parser_file.y"
                                           {
                  (yyval.expression_node) = new BinaryExpressionNode((yyvsp[-2].expression_node), (yyvsp[0].expression_node), BinaryOperator::AND_OP, yylineno);
               }
#line 2078 "parse.tab.cpp"
    break;

  case 59: /* expression: expression OR expression  */
#line 322 "rustish_parser_file.y"
                                          {
                  (yyval.expression_node) = new BinaryExpressionNode((yyvsp[-2].expression_node), (yyvsp[0].expression_node), BinaryOperator::OR_OP, yylineno);
               }
#line 2086 "parse.tab.cpp"
    break;

  case 60: /* expression: expression EQ expression  */
#line 325 "rustish_parser_file.y"
                                          {
                  (yyval.expression_node) = new BinaryExpressionNode((yyvsp[-2].expression_node), (yyvsp[0].expression_node), BinaryOperator::EQ_OP, yylineno);
               }
#line 2094 "parse.tab.cpp"
    break;

  case 61: /* expression: expression NE expression  */
#line 328 "rustish_parser_file.y"
                                          {
                  (yyval.expression_node) = new BinaryExpressionNode((yyvsp[-2].expression_node), (yyvsp[0].expression_node), BinaryOperator::NE_OP, yylineno);
               }
#line 2102 "parse.tab.cpp"
    break;

  case 62: /* expression: expression LE expression  */
#line 331 "rustish_parser_file.y"
                                          {
                  (yyval.expression_node) = new BinaryExpressionNode((yyvsp[-2].expression_node), (yyvsp[0].expression_node), BinaryOperator::LE_OP, yylineno);
               }
#line 2110 "parse.tab.cpp"
    break;

  case 63: /* expression: expression GE expression  */
#line 334 "rustish_parser_file.y"
                                          {
                  (yyval.expression_node) = new BinaryExpressionNode((yyvsp[-2].expression_node), (yyvsp[0].expression_node), BinaryOperator::GE_OP, yylineno);
               }
#line 2118 "parse.tab.cpp"
    break;

  case 64: /* expression: expression GT expression  */
#line 337 "rustish_parser_file.y"
                                          {
                  (yyval.expression_node) = new BinaryExpressionNode((yyvsp[-2].expression_node), (yyvsp[0].expression_node), BinaryOperator::GT_OP, yylineno);
               }
#line 2126 "parse.tab.cpp"
    break;

  case 65: /* expression: expression LT expression  */
#line 340 "rustish_parser_file.y"
                                          {
                  (yyval.expression_node) = new BinaryExpressionNode((yyvsp[-2].expression_node), (yyvsp[0].expression_node), BinaryOperator::LT_OP, yylineno);
               }
#line 2134 "parse.tab.cpp"
    break;

  case 66: /* expression: NOT expression  */
#line 343 "rustish_parser_file.y"
                                {
                  (yyval.expression_node) = new NotExpressionNode((yyvsp[0].expression_node), yylineno);
               }
#line 2142 "parse.tab.cpp"
    break;

  case 67: /* expression: MINUS expression  */
#line 346 "rustish_parser_file.y"
                                  {
                  (yyval.expression_node) = new UnaryMinusExpressionNode((yyvsp[0].expression_node), yylineno);
               }
#line 2150 "parse.tab.cpp"
    break;

  case 68: /* identifier: IDENTIFIER  */
#line 350 "rustish_parser_file.y"
                            {
                  std::string *value = new std::string(yyval.token->value);
                  (yyval.indentifier_node) = new IdentifierNode(value, yylineno);
               }
#line 2159 "parse.tab.cpp"
    break;

  case 69: /* number: NUMBER  */
#line 355 "rustish_parser_file.y"
                        {
                  std::string *value = new std::string(yyval.token->value);
                  (yyval.number_node) = new NumberNode(value, yylineno);
               }
#line 2168 "parse.tab.cpp"
    break;


#line 2172 "parse.tab.cpp"

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
          = {yyssp, yytoken};
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
                      yytoken, &yylval);
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


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
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

#line 360 "rustish_parser_file.y"


extern FILE *yyin;

int yyparse();

int main(int argc, char **argv) {
   if (argc == 2) {
      yyin = fopen(argv[1], "r");
      if (yyin == NULL){
         printf("syntax: %s filename\n", argv[0]);
      }
   } else {
      printf("syntax: %s filename\n", argv[0]);
   }
   yyparse(); // Calls yylex() for tokens.

   return 0;
}

void yyerror(const char *msg) {
   printf("** Line %d: %s\n", yylineno, msg);
}
