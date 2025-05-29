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
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/parser.y"

#include <stdio.h>
#include <stdlib.h>
#include "../inc/ast.h"
#include "../inc/types.h"

ASTNode* root;

#line 80 "build/parser.tab.c"

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
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_IDENTIFIER = 4,                 /* IDENTIFIER  */
  YYSYMBOL_CHARACTER = 5,                  /* CHARACTER  */
  YYSYMBOL_FLOAT = 6,                      /* FLOAT  */
  YYSYMBOL_DOUBLE = 7,                     /* DOUBLE  */
  YYSYMBOL_LONG = 8,                       /* LONG  */
  YYSYMBOL_RETURN = 9,                     /* RETURN  */
  YYSYMBOL_WHILE = 10,                     /* WHILE  */
  YYSYMBOL_FOR = 11,                       /* FOR  */
  YYSYMBOL_IF = 12,                        /* IF  */
  YYSYMBOL_ELSE = 13,                      /* ELSE  */
  YYSYMBOL_TRUE = 14,                      /* TRUE  */
  YYSYMBOL_FALSE = 15,                     /* FALSE  */
  YYSYMBOL_LOGIC_AND = 16,                 /* LOGIC_AND  */
  YYSYMBOL_LOGIC_OR = 17,                  /* LOGIC_OR  */
  YYSYMBOL_ASSIGNMENT_ADD_EQUALS = 18,     /* ASSIGNMENT_ADD_EQUALS  */
  YYSYMBOL_ASSIGNMENT_SUB_EQUALS = 19,     /* ASSIGNMENT_SUB_EQUALS  */
  YYSYMBOL_ASSIGNMENT_MUL_EQUALS = 20,     /* ASSIGNMENT_MUL_EQUALS  */
  YYSYMBOL_ASSIGNMENT_DIV_EQUALS = 21,     /* ASSIGNMENT_DIV_EQUALS  */
  YYSYMBOL_INCREMENT = 22,                 /* INCREMENT  */
  YYSYMBOL_DECREMENT = 23,                 /* DECREMENT  */
  YYSYMBOL_NULLTOK = 24,                   /* NULLTOK  */
  YYSYMBOL_COMPARE = 25,                   /* COMPARE  */
  YYSYMBOL_BASE_TYPE = 26,                 /* BASE_TYPE  */
  YYSYMBOL_STRING = 27,                    /* STRING  */
  YYSYMBOL_28_ = 28,                       /* '+'  */
  YYSYMBOL_29_ = 29,                       /* '-'  */
  YYSYMBOL_30_ = 30,                       /* '*'  */
  YYSYMBOL_31_ = 31,                       /* '/'  */
  YYSYMBOL_32_ = 32,                       /* ';'  */
  YYSYMBOL_33_ = 33,                       /* '('  */
  YYSYMBOL_34_ = 34,                       /* ')'  */
  YYSYMBOL_35_ = 35,                       /* '{'  */
  YYSYMBOL_36_ = 36,                       /* '}'  */
  YYSYMBOL_37_ = 37,                       /* '='  */
  YYSYMBOL_38_ = 38,                       /* ','  */
  YYSYMBOL_39_ = 39,                       /* '%'  */
  YYSYMBOL_40_ = 40,                       /* '&'  */
  YYSYMBOL_41_ = 41,                       /* '['  */
  YYSYMBOL_42_ = 42,                       /* ']'  */
  YYSYMBOL_YYACCEPT = 43,                  /* $accept  */
  YYSYMBOL_program = 44,                   /* program  */
  YYSYMBOL_input = 45,                     /* input  */
  YYSYMBOL_statement = 46,                 /* statement  */
  YYSYMBOL_47_1 = 47,                      /* $@1  */
  YYSYMBOL_48_2 = 48,                      /* $@2  */
  YYSYMBOL_else_clause = 49,               /* else_clause  */
  YYSYMBOL_block = 50,                     /* block  */
  YYSYMBOL_51_3 = 51,                      /* $@3  */
  YYSYMBOL_declare = 52,                   /* declare  */
  YYSYMBOL_argument_list = 53,             /* argument_list  */
  YYSYMBOL_parameter_list = 54,            /* parameter_list  */
  YYSYMBOL_type = 55,                      /* type  */
  YYSYMBOL_none_or_more_pointers = 56,     /* none_or_more_pointers  */
  YYSYMBOL_declare_or_expr_opt = 57,       /* declare_or_expr_opt  */
  YYSYMBOL_expr_opt = 58,                  /* expr_opt  */
  YYSYMBOL_expr = 59,                      /* expr  */
  YYSYMBOL_logic_or = 60,                  /* logic_or  */
  YYSYMBOL_logic_and = 61,                 /* logic_and  */
  YYSYMBOL_rvalue = 62,                    /* rvalue  */
  YYSYMBOL_mag = 63,                       /* mag  */
  YYSYMBOL_term = 64,                      /* term  */
  YYSYMBOL_factor = 65,                    /* factor  */
  YYSYMBOL_postfix = 66,                   /* postfix  */
  YYSYMBOL_primary = 67                    /* primary  */
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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   242

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  140

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   282


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
       2,     2,     2,     2,     2,     2,     2,    39,    40,     2,
      33,    34,    30,    28,    38,    29,     2,    31,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    32,
       2,    37,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    41,     2,    42,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    35,     2,    36,     2,     2,     2,     2,
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
      25,    26,    27
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    64,    64,    68,    69,    73,    74,    75,    76,    77,
      77,    84,    85,    85,    86,    90,    91,    92,    96,    96,
     100,   101,   105,   106,   107,   111,   112,   113,   116,   120,
     121,   125,   126,   127,   131,   132,   136,   137,   138,   139,
     140,   141,   145,   146,   150,   151,   155,   156,   160,   161,
     162,   166,   167,   168,   169,   173,   174,   175,   176,   177,
     178,   179,   183,   184,   185,   186,   187,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201
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
  "\"end of file\"", "error", "\"invalid token\"", "INT", "IDENTIFIER",
  "CHARACTER", "FLOAT", "DOUBLE", "LONG", "RETURN", "WHILE", "FOR", "IF",
  "ELSE", "TRUE", "FALSE", "LOGIC_AND", "LOGIC_OR",
  "ASSIGNMENT_ADD_EQUALS", "ASSIGNMENT_SUB_EQUALS",
  "ASSIGNMENT_MUL_EQUALS", "ASSIGNMENT_DIV_EQUALS", "INCREMENT",
  "DECREMENT", "NULLTOK", "COMPARE", "BASE_TYPE", "STRING", "'+'", "'-'",
  "'*'", "'/'", "';'", "'('", "')'", "'{'", "'}'", "'='", "','", "'%'",
  "'&'", "'['", "']'", "$accept", "program", "input", "statement", "$@1",
  "$@2", "else_clause", "block", "$@3", "declare", "argument_list",
  "parameter_list", "type", "none_or_more_pointers", "declare_or_expr_opt",
  "expr_opt", "expr", "logic_or", "logic_and", "rvalue", "mag", "term",
  "factor", "postfix", "primary", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-102)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-22)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -102,    11,   140,  -102,  -102,    -6,  -102,  -102,  -102,  -102,
     202,    -4,    -2,     8,  -102,  -102,   202,   202,  -102,  -102,
    -102,   202,   202,  -102,   171,    13,  -102,     7,    46,    29,
      43,    47,    37,     6,    28,     3,   -16,  -102,   202,    34,
     202,  -102,   202,  -102,  -102,    38,  -102,  -102,    36,    39,
    -102,  -102,   -24,  -102,   202,   202,   202,   202,   202,   202,
     202,   202,   202,   202,   202,   202,   202,  -102,  -102,   202,
     -22,  -102,  -102,    40,   171,    41,  -102,   202,  -102,   202,
      44,    47,  -102,    37,     6,    28,    28,  -102,  -102,  -102,
    -102,  -102,  -102,  -102,  -102,    30,  -102,   202,    45,  -102,
      67,    49,  -102,    45,  -102,  -102,    50,  -102,  -102,  -102,
    -102,    42,   202,    65,   -19,    78,  -102,    52,  -102,    -9,
    -102,    45,    50,  -102,   102,   202,    53,  -102,  -102,    81,
    -102,    54,   202,  -102,    45,    55,  -102,    45,    65,  -102
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     2,     1,    68,    67,    70,    72,    73,    69,
       0,     0,     0,     0,    74,    75,     0,     0,    76,    29,
      71,     0,     0,    14,     0,     0,     4,     0,     0,     0,
      41,    43,    45,    47,    50,    54,    61,    62,    25,     0,
       0,     9,     0,    59,    60,    28,    56,    57,     0,     0,
      58,     5,    12,     6,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    65,    66,     0,
       0,    26,     7,     0,    33,     0,    30,     0,    77,     0,
       0,    42,    54,    44,    46,    48,    49,    51,    52,    53,
      37,    38,    39,    40,    36,     0,    64,     0,     0,    31,
       0,     0,    32,     0,    55,    20,    22,    63,    27,    18,
       8,    21,    35,    15,     0,     0,     3,     0,    34,     0,
      11,     0,     0,    23,     0,    35,     0,    16,    13,     0,
      19,     0,     0,    24,     0,     0,    10,     0,    15,    17
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -102,  -102,   -26,  -102,  -102,  -102,   -47,  -101,  -102,    18,
    -102,  -102,   -23,  -102,  -102,   -32,   -10,  -102,    64,    48,
      63,   -20,   -12,  -102,  -102
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,    26,    74,    80,   120,   110,   116,    27,
     114,    70,    28,    45,   101,   117,    29,    30,    31,    32,
      33,    34,    35,    36,    37
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      39,    48,   113,   126,    43,    44,    67,    68,   -21,    46,
      47,     3,    96,    79,    49,   121,    97,    50,   127,   122,
     128,    62,    63,    64,    65,    69,   109,    38,    71,    40,
      73,    41,    75,   136,    57,    58,   138,    85,    86,    51,
      66,    42,    82,    82,    82,    82,    82,    87,    88,    89,
      52,   100,    90,    91,    92,    93,    94,    95,    59,    60,
      54,    53,    56,    55,   102,   104,    72,    61,    76,   105,
      77,   111,   107,    78,    98,   103,    19,   106,   119,    79,
     109,   112,   123,   115,   125,   133,   132,   108,   134,   137,
     124,   139,    99,   131,     0,     0,     0,     0,     0,   129,
       0,     0,   118,    83,     0,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,   118,    14,    15,    81,    84,
       0,     0,   135,     0,    16,    17,    18,     0,    19,    20,
       0,    21,    22,     0,    23,    24,     0,     0,   130,     0,
       0,     0,    25,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,     0,    14,    15,     0,     0,     0,     0,
       0,     0,    16,    17,    18,     0,    19,    20,     0,    21,
      22,     0,    23,    24,     4,     5,     6,     7,     8,     9,
      25,     0,     0,     0,     0,    14,    15,     0,     0,     0,
       0,     0,     0,    16,    17,    18,     0,    19,    20,     0,
      21,    22,     0,     0,    24,     4,     5,     6,     7,     8,
       9,    25,     0,     0,     0,     0,    14,    15,     0,     0,
       0,     0,     0,     0,    16,    17,    18,     0,     0,    20,
       0,    21,    22,     0,     0,    24,     0,     0,     0,     0,
       0,     0,    25
};

static const yytype_int16 yycheck[] =
{
      10,    24,   103,    12,    16,    17,    22,    23,    32,    21,
      22,     0,    34,    37,    24,    34,    38,     4,   119,    38,
     121,    18,    19,    20,    21,    41,    35,    33,    38,    33,
      40,    33,    42,   134,    28,    29,   137,    57,    58,    32,
      37,    33,    54,    55,    56,    57,    58,    59,    60,    61,
       4,    74,    62,    63,    64,    65,    66,    69,    30,    31,
      17,    32,    25,    16,    74,    77,    32,    39,    30,    79,
      34,     4,    42,    34,    34,    34,    26,    33,    13,    37,
      35,    32,     4,   106,    32,     4,    33,    97,    34,    34,
     116,   138,    74,   125,    -1,    -1,    -1,    -1,    -1,   122,
      -1,    -1,   112,    55,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,   125,    14,    15,    54,    56,
      -1,    -1,   132,    -1,    22,    23,    24,    -1,    26,    27,
      -1,    29,    30,    -1,    32,    33,    -1,    -1,    36,    -1,
      -1,    -1,    40,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    -1,    14,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    22,    23,    24,    -1,    26,    27,    -1,    29,
      30,    -1,    32,    33,     3,     4,     5,     6,     7,     8,
      40,    -1,    -1,    -1,    -1,    14,    15,    -1,    -1,    -1,
      -1,    -1,    -1,    22,    23,    24,    -1,    26,    27,    -1,
      29,    30,    -1,    -1,    33,     3,     4,     5,     6,     7,
       8,    40,    -1,    -1,    -1,    -1,    14,    15,    -1,    -1,
      -1,    -1,    -1,    -1,    22,    23,    24,    -1,    -1,    27,
      -1,    29,    30,    -1,    -1,    33,    -1,    -1,    -1,    -1,
      -1,    -1,    40
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    44,    45,     0,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    14,    15,    22,    23,    24,    26,
      27,    29,    30,    32,    33,    40,    46,    52,    55,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    33,    59,
      33,    33,    33,    65,    65,    56,    65,    65,    55,    59,
       4,    32,     4,    32,    17,    16,    25,    28,    29,    30,
      31,    39,    18,    19,    20,    21,    37,    22,    23,    41,
      54,    59,    32,    59,    47,    59,    30,    34,    34,    37,
      48,    61,    65,    62,    63,    64,    64,    65,    65,    65,
      59,    59,    59,    59,    59,    65,    34,    38,    34,    52,
      55,    57,    59,    34,    65,    59,    33,    42,    59,    35,
      50,     4,    32,    50,    53,    55,    51,    58,    59,    13,
      49,    34,    38,     4,    45,    32,    12,    50,    50,    55,
      36,    58,    33,     4,    34,    59,    50,    34,    50,    49
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    43,    44,    45,    45,    46,    46,    46,    46,    47,
      46,    46,    48,    46,    46,    49,    49,    49,    51,    50,
      52,    52,    53,    53,    53,    54,    54,    54,    55,    56,
      56,    57,    57,    57,    58,    58,    59,    59,    59,    59,
      59,    59,    60,    60,    61,    61,    62,    62,    63,    63,
      63,    64,    64,    64,    64,    65,    65,    65,    65,    65,
      65,    65,    66,    66,    66,    66,    66,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     2,     2,     3,     5,     0,
      10,     6,     0,     7,     1,     0,     2,     7,     0,     4,
       4,     2,     0,     2,     4,     0,     1,     3,     2,     0,
       2,     1,     1,     0,     1,     0,     3,     3,     3,     3,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     3,
       1,     3,     3,     3,     1,     4,     2,     2,     2,     2,
       2,     1,     1,     4,     4,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3
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
        yyerror (&yylloc, YY_("syntax error: cannot back up")); \
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






/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

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
      yychar = yylex (&yylval, &yylloc);
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
  case 2: /* program: input  */
#line 64 "src/parser.y"
                { root = (yyvsp[0].node); }
#line 1640 "build/parser.tab.c"
    break;

  case 3: /* input: %empty  */
#line 68 "src/parser.y"
                        { (yyval.node) = make_program((yyloc)); }
#line 1646 "build/parser.tab.c"
    break;

  case 4: /* input: input statement  */
#line 69 "src/parser.y"
                                { append_statement((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 1652 "build/parser.tab.c"
    break;

  case 5: /* statement: declare ';'  */
#line 73 "src/parser.y"
                        { (yyval.node) = (yyvsp[-1].node); }
#line 1658 "build/parser.tab.c"
    break;

  case 6: /* statement: expr ';'  */
#line 74 "src/parser.y"
                        { (yyval.node) = (yyvsp[-1].node); }
#line 1664 "build/parser.tab.c"
    break;

  case 7: /* statement: RETURN expr ';'  */
#line 75 "src/parser.y"
                                { (yyval.node) = make_return((yyvsp[-1].node), (yyloc)); }
#line 1670 "build/parser.tab.c"
    break;

  case 8: /* statement: WHILE '(' expr ')' block  */
#line 76 "src/parser.y"
                                        { (yyval.node) = make_while((yyvsp[-2].node), (yyvsp[0].node), (yyloc)); }
#line 1676 "build/parser.tab.c"
    break;

  case 9: /* $@1: %empty  */
#line 77 "src/parser.y"
                  { sem_enter_scope(); }
#line 1682 "build/parser.tab.c"
    break;

  case 10: /* statement: FOR '(' $@1 declare_or_expr_opt ';' expr_opt ';' expr_opt ')' block  */
#line 77 "src/parser.y"
                                                                                                        {
		(yyval.node) = make_program((yyloc));
		append_statement((yyval.node), (yyvsp[-6].node));
		ASTNode* while_body = (yyvsp[0].node);
		append_statement(while_body, (yyvsp[-2].node));
		append_statement((yyval.node), make_while((yyvsp[-4].node), while_body, (yyloc)));
		sem_exit_scope(); }
#line 1694 "build/parser.tab.c"
    break;

  case 11: /* statement: IF '(' expr ')' block else_clause  */
#line 84 "src/parser.y"
                                                { (yyval.node) = make_if((yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node), (yyloc)); }
#line 1700 "build/parser.tab.c"
    break;

  case 12: /* $@2: %empty  */
#line 85 "src/parser.y"
                          { sem_enter_scope(); }
#line 1706 "build/parser.tab.c"
    break;

  case 13: /* statement: type IDENTIFIER $@2 '(' argument_list ')' block  */
#line 85 "src/parser.y"
                                                                                { sem_exit_scope(); (yyval.node) = make_function((yyvsp[-6].type), (yyvsp[-5].sval), (yyvsp[-2].argument), (yyvsp[0].node), (yyloc)); }
#line 1712 "build/parser.tab.c"
    break;

  case 14: /* statement: ';'  */
#line 86 "src/parser.y"
                        { (yyval.node) = make_empty((yyloc)); }
#line 1718 "build/parser.tab.c"
    break;

  case 15: /* else_clause: %empty  */
#line 90 "src/parser.y"
                        { (yyval.node) = NULL; }
#line 1724 "build/parser.tab.c"
    break;

  case 16: /* else_clause: ELSE block  */
#line 91 "src/parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 1730 "build/parser.tab.c"
    break;

  case 17: /* else_clause: ELSE IF '(' expr ')' block else_clause  */
#line 92 "src/parser.y"
                                                        { (yyval.node) = make_if((yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node), (yyloc)); }
#line 1736 "build/parser.tab.c"
    break;

  case 18: /* $@3: %empty  */
#line 96 "src/parser.y"
            { sem_enter_scope(); }
#line 1742 "build/parser.tab.c"
    break;

  case 19: /* block: '{' $@3 input '}'  */
#line 96 "src/parser.y"
                                             { sem_exit_scope(); (yyval.node) = (yyvsp[-1].node); }
#line 1748 "build/parser.tab.c"
    break;

  case 20: /* declare: type IDENTIFIER '=' expr  */
#line 100 "src/parser.y"
                                        { (yyval.node) = make_declare((yyvsp[-3].type), (yyvsp[-2].sval), (yyvsp[0].node), (yyloc)); }
#line 1754 "build/parser.tab.c"
    break;

  case 21: /* declare: type IDENTIFIER  */
#line 101 "src/parser.y"
                                        { (yyval.node) = make_declare((yyvsp[-1].type), (yyvsp[0].sval), NULL, (yyloc)); }
#line 1760 "build/parser.tab.c"
    break;

  case 22: /* argument_list: %empty  */
#line 105 "src/parser.y"
        { (yyval.argument) = NULL; }
#line 1766 "build/parser.tab.c"
    break;

  case 23: /* argument_list: type IDENTIFIER  */
#line 106 "src/parser.y"
                                        { (yyval.argument) = make_argument((yyvsp[-1].type), (yyvsp[0].sval), (yyloc)); }
#line 1772 "build/parser.tab.c"
    break;

  case 24: /* argument_list: argument_list ',' type IDENTIFIER  */
#line 107 "src/parser.y"
                                                { append_argument((yyvsp[-3].argument), make_argument((yyvsp[-1].type), (yyvsp[0].sval), (yyloc)), (yyloc)); (yyval.argument) = (yyvsp[-3].argument); }
#line 1778 "build/parser.tab.c"
    break;

  case 25: /* parameter_list: %empty  */
#line 111 "src/parser.y"
        { (yyval.parameter) = NULL; }
#line 1784 "build/parser.tab.c"
    break;

  case 26: /* parameter_list: expr  */
#line 112 "src/parser.y"
                                        { (yyval.parameter) = make_parameter((yyvsp[0].node), (yyloc)); }
#line 1790 "build/parser.tab.c"
    break;

  case 27: /* parameter_list: parameter_list ',' expr  */
#line 113 "src/parser.y"
                                        { append_parameter((yyvsp[-2].parameter), make_parameter((yyvsp[0].node), (yyloc)), (yyloc)); (yyval.parameter) = (yyvsp[-2].parameter); }
#line 1796 "build/parser.tab.c"
    break;

  case 28: /* type: BASE_TYPE none_or_more_pointers  */
#line 116 "src/parser.y"
                                        { (yyval.type) = make_type(get_base_type((yyvsp[-1].sval)), (yyvsp[0].ival)); }
#line 1802 "build/parser.tab.c"
    break;

  case 29: /* none_or_more_pointers: %empty  */
#line 120 "src/parser.y"
        { (yyval.ival) = 0; }
#line 1808 "build/parser.tab.c"
    break;

  case 30: /* none_or_more_pointers: none_or_more_pointers '*'  */
#line 121 "src/parser.y"
                                        { (yyval.ival) = (yyvsp[-1].ival) + 1; }
#line 1814 "build/parser.tab.c"
    break;

  case 31: /* declare_or_expr_opt: declare  */
#line 125 "src/parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 1820 "build/parser.tab.c"
    break;

  case 32: /* declare_or_expr_opt: expr  */
#line 126 "src/parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 1826 "build/parser.tab.c"
    break;

  case 33: /* declare_or_expr_opt: %empty  */
#line 127 "src/parser.y"
                { (yyval.node) = make_empty((yyloc)); }
#line 1832 "build/parser.tab.c"
    break;

  case 34: /* expr_opt: expr  */
#line 131 "src/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 1838 "build/parser.tab.c"
    break;

  case 35: /* expr_opt: %empty  */
#line 132 "src/parser.y"
                { (yyval.node) = make_empty((yyloc)); }
#line 1844 "build/parser.tab.c"
    break;

  case 36: /* expr: factor '=' expr  */
#line 136 "src/parser.y"
                                { (yyval.node) = make_assign((yyvsp[-2].node), (yyvsp[0].node), (yyloc)); }
#line 1850 "build/parser.tab.c"
    break;

  case 37: /* expr: factor ASSIGNMENT_ADD_EQUALS expr  */
#line 137 "src/parser.y"
                                                { (yyval.node) = make_assign((yyvsp[-2].node), make_binary("+", (yyvsp[-2].node), (yyvsp[0].node), (yyloc)), (yyloc)); }
#line 1856 "build/parser.tab.c"
    break;

  case 38: /* expr: factor ASSIGNMENT_SUB_EQUALS expr  */
#line 138 "src/parser.y"
                                                { (yyval.node) = make_assign((yyvsp[-2].node), make_binary("-", (yyvsp[-2].node), (yyvsp[0].node), (yyloc)), (yyloc)); }
#line 1862 "build/parser.tab.c"
    break;

  case 39: /* expr: factor ASSIGNMENT_MUL_EQUALS expr  */
#line 139 "src/parser.y"
                                                { (yyval.node) = make_assign((yyvsp[-2].node), make_binary("*", (yyvsp[-2].node), (yyvsp[0].node), (yyloc)), (yyloc)); }
#line 1868 "build/parser.tab.c"
    break;

  case 40: /* expr: factor ASSIGNMENT_DIV_EQUALS expr  */
#line 140 "src/parser.y"
                                                { (yyval.node) = make_assign((yyvsp[-2].node), make_binary("/", (yyvsp[-2].node), (yyvsp[0].node), (yyloc)), (yyloc)); }
#line 1874 "build/parser.tab.c"
    break;

  case 41: /* expr: logic_or  */
#line 141 "src/parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 1880 "build/parser.tab.c"
    break;

  case 42: /* logic_or: logic_or LOGIC_OR logic_and  */
#line 145 "src/parser.y"
                                      { (yyval.node) = make_binary("||", (yyvsp[-2].node), (yyvsp[0].node), (yyloc)); }
#line 1886 "build/parser.tab.c"
    break;

  case 43: /* logic_or: logic_and  */
#line 146 "src/parser.y"
                                 { (yyval.node) = (yyvsp[0].node); }
#line 1892 "build/parser.tab.c"
    break;

  case 44: /* logic_and: logic_and LOGIC_AND rvalue  */
#line 150 "src/parser.y"
                                      { (yyval.node) = make_binary("&&", (yyvsp[-2].node), (yyvsp[0].node), (yyloc)); }
#line 1898 "build/parser.tab.c"
    break;

  case 45: /* logic_and: rvalue  */
#line 151 "src/parser.y"
                                 { (yyval.node) = (yyvsp[0].node); }
#line 1904 "build/parser.tab.c"
    break;

  case 46: /* rvalue: rvalue COMPARE mag  */
#line 155 "src/parser.y"
                                { (yyval.node) = make_binary((yyvsp[-1].sval), (yyvsp[-2].node), (yyvsp[0].node), (yyloc)); }
#line 1910 "build/parser.tab.c"
    break;

  case 47: /* rvalue: mag  */
#line 156 "src/parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 1916 "build/parser.tab.c"
    break;

  case 48: /* mag: mag '+' term  */
#line 160 "src/parser.y"
                        { (yyval.node) = make_binary("+", (yyvsp[-2].node), (yyvsp[0].node), (yyloc)); }
#line 1922 "build/parser.tab.c"
    break;

  case 49: /* mag: mag '-' term  */
#line 161 "src/parser.y"
                        { (yyval.node) = make_binary("-", (yyvsp[-2].node), (yyvsp[0].node), (yyloc)); }
#line 1928 "build/parser.tab.c"
    break;

  case 50: /* mag: term  */
#line 162 "src/parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 1934 "build/parser.tab.c"
    break;

  case 51: /* term: term '*' factor  */
#line 166 "src/parser.y"
                        { (yyval.node) = make_binary("*", (yyvsp[-2].node), (yyvsp[0].node), (yyloc)); }
#line 1940 "build/parser.tab.c"
    break;

  case 52: /* term: term '/' factor  */
#line 167 "src/parser.y"
                                { (yyval.node) = make_binary("/", (yyvsp[-2].node), (yyvsp[0].node), (yyloc)); }
#line 1946 "build/parser.tab.c"
    break;

  case 53: /* term: term '%' factor  */
#line 168 "src/parser.y"
                                { (yyval.node) = make_binary("%", (yyvsp[-2].node), (yyvsp[0].node), (yyloc)); }
#line 1952 "build/parser.tab.c"
    break;

  case 54: /* term: factor  */
#line 169 "src/parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 1958 "build/parser.tab.c"
    break;

  case 55: /* factor: '(' type ')' factor  */
#line 173 "src/parser.y"
                                { (yyval.node) = make_cast((yyvsp[-2].type), (yyvsp[0].node), (yyloc)); }
#line 1964 "build/parser.tab.c"
    break;

  case 56: /* factor: '-' factor  */
#line 174 "src/parser.y"
                        { (yyval.node) = make_unary("-", (yyvsp[0].node), (yyloc)); }
#line 1970 "build/parser.tab.c"
    break;

  case 57: /* factor: '*' factor  */
#line 175 "src/parser.y"
                        { (yyval.node) = make_unary("*", (yyvsp[0].node), (yyloc)); }
#line 1976 "build/parser.tab.c"
    break;

  case 58: /* factor: '&' IDENTIFIER  */
#line 176 "src/parser.y"
                                { (yyval.node) = make_unary("&", make_identifier((yyvsp[0].sval), (yyloc)), (yyloc)); }
#line 1982 "build/parser.tab.c"
    break;

  case 59: /* factor: INCREMENT factor  */
#line 177 "src/parser.y"
                           { (yyval.node) = make_assign((yyvsp[0].node), make_binary("+", (yyvsp[0].node), make_int(1, (yyloc)), (yyloc)), (yyloc)); }
#line 1988 "build/parser.tab.c"
    break;

  case 60: /* factor: DECREMENT factor  */
#line 178 "src/parser.y"
                           { (yyval.node) = make_assign((yyvsp[0].node), make_binary("-", (yyvsp[0].node), make_int(1, (yyloc)), (yyloc)), (yyloc)); }
#line 1994 "build/parser.tab.c"
    break;

  case 61: /* factor: postfix  */
#line 179 "src/parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 2000 "build/parser.tab.c"
    break;

  case 62: /* postfix: primary  */
#line 183 "src/parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 2006 "build/parser.tab.c"
    break;

  case 63: /* postfix: postfix '[' factor ']'  */
#line 184 "src/parser.y"
                                        { (yyval.node) = make_unary("*", make_binary("+", (yyvsp[-3].node), (yyvsp[-1].node), (yyloc)), (yyloc)); }
#line 2012 "build/parser.tab.c"
    break;

  case 64: /* postfix: IDENTIFIER '(' parameter_list ')'  */
#line 185 "src/parser.y"
                                                { (yyval.node) = make_function_call((yyvsp[-3].sval), (yyvsp[-1].parameter), (yyloc)); }
#line 2018 "build/parser.tab.c"
    break;

  case 65: /* postfix: postfix INCREMENT  */
#line 186 "src/parser.y"
                                { (yyval.node) = make_binary("-", make_assign((yyvsp[-1].node), make_binary("+", (yyvsp[-1].node), make_int(1, (yyloc)), (yyloc)), (yyloc)), make_int(1, (yyloc)), (yyloc)); }
#line 2024 "build/parser.tab.c"
    break;

  case 66: /* postfix: postfix DECREMENT  */
#line 187 "src/parser.y"
                                { (yyval.node) = make_binary("+", make_assign((yyvsp[-1].node), make_binary("-", (yyvsp[-1].node), make_int(1, (yyloc)), (yyloc)), (yyloc)), make_int(1, (yyloc)), (yyloc)); }
#line 2030 "build/parser.tab.c"
    break;

  case 67: /* primary: IDENTIFIER  */
#line 191 "src/parser.y"
                        { (yyval.node) = make_identifier((yyvsp[0].sval), (yyloc)); }
#line 2036 "build/parser.tab.c"
    break;

  case 68: /* primary: INT  */
#line 192 "src/parser.y"
                        { (yyval.node) = make_int((yyvsp[0].ival), (yyloc)); }
#line 2042 "build/parser.tab.c"
    break;

  case 69: /* primary: LONG  */
#line 193 "src/parser.y"
                        { (yyval.node) = make_long((yyvsp[0].lval), (yyloc)); }
#line 2048 "build/parser.tab.c"
    break;

  case 70: /* primary: CHARACTER  */
#line 194 "src/parser.y"
                        { (yyval.node) = make_character((yyvsp[0].cval), (yyloc)); }
#line 2054 "build/parser.tab.c"
    break;

  case 71: /* primary: STRING  */
#line 195 "src/parser.y"
                        { (yyval.node) = make_string((yyvsp[0].sval), (yyloc)); }
#line 2060 "build/parser.tab.c"
    break;

  case 72: /* primary: FLOAT  */
#line 196 "src/parser.y"
                        { (yyval.node) = make_float((yyvsp[0].fval), (yyloc)); }
#line 2066 "build/parser.tab.c"
    break;

  case 73: /* primary: DOUBLE  */
#line 197 "src/parser.y"
                        { (yyval.node) = make_double((yyvsp[0].dval), (yyloc)); }
#line 2072 "build/parser.tab.c"
    break;

  case 74: /* primary: TRUE  */
#line 198 "src/parser.y"
                                { (yyval.node) = make_true((yyloc)); }
#line 2078 "build/parser.tab.c"
    break;

  case 75: /* primary: FALSE  */
#line 199 "src/parser.y"
                                { (yyval.node) = make_false((yyloc)); }
#line 2084 "build/parser.tab.c"
    break;

  case 76: /* primary: NULLTOK  */
#line 200 "src/parser.y"
                                { (yyval.node) = make_null((yyloc)); }
#line 2090 "build/parser.tab.c"
    break;

  case 77: /* primary: '(' expr ')'  */
#line 201 "src/parser.y"
                        { (yyval.node) = (yyvsp[-1].node); }
#line 2096 "build/parser.tab.c"
    break;


#line 2100 "build/parser.tab.c"

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
        yyerror (&yylloc, yymsgp);
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
  yyerror (&yylloc, YY_("memory exhausted"));
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

#line 204 "src/parser.y"



int yyerror(YYLTYPE* yylloc, const char *msg) {
	fprintf(stderr, "Parse error at line %d, column %d: %s\n",
		yylloc->first_line, yylloc->first_column, msg);
	exit(1);
	return 1;
}
