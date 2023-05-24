/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 4 "compiler.y"

    #include "compiler_common.h" //Extern variables that communicate with lex
    // #define YYDEBUG 1
    // int yydebug = 1; 
    # define Fu 0 // function
    # define P 1 // parameter
    # define I 2 // id
    # define Fo 3 // foreach


    extern int yylineno;
    extern int yylex();
    extern FILE *yyin;

    int yylex_destroy ();
    void yyerror (char const *s)
    {
        printf("error:%d: %s\n", yylineno, s);
    }

    extern int yylineno;
    extern int yylex();
    extern FILE *yyin;

    /* Symbol table function - you can add new functions if needed. */
    /* parameters and return type can be changed */
    static void create_symbol();
    static void insert_symbol(char*, char*, char*, int, bool);
    static char *lookup_symbol(char*, int);
    static void dump_symbol();
    static void build_func_para(char *);

    struct table{
        int scope;
        struct table *prev;
        struct symbol *head;
    };
    struct symbol{
        int index;
        char* name;
        int mut;
        char* type;
        int addr;
        int lineno;
        char* func_sig;
        struct symbol *next;
    };
    struct table *current_table = NULL;
    
    /* Global variables */
    bool HAS_ERROR = false;
    int global_scope = -1;
    int addr = 0;
    bool casting = false;
    char func_para[100] = "(";
    bool has_return = false;
    char return_type = 'v';

#line 129 "y.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    LET = 258,
    MUT = 259,
    NEWLINE = 260,
    INT = 261,
    FLOAT = 262,
    BOOL = 263,
    STR = 264,
    TRUE = 265,
    FALSE = 266,
    GEQ = 267,
    LEQ = 268,
    EQL = 269,
    NEQ = 270,
    LOR = 271,
    LAND = 272,
    ADD_ASSIGN = 273,
    SUB_ASSIGN = 274,
    MUL_ASSIGN = 275,
    DIV_ASSIGN = 276,
    REM_ASSIGN = 277,
    IF = 278,
    ELSE = 279,
    FOR = 280,
    WHILE = 281,
    LOOP = 282,
    PRINT = 283,
    PRINTLN = 284,
    FUNC = 285,
    RETURN = 286,
    BREAK = 287,
    ID = 288,
    ARROW = 289,
    AS = 290,
    IN = 291,
    DOTDOT = 292,
    RSHIFT = 293,
    LSHIFT = 294,
    INT_LIT = 295,
    FLOAT_LIT = 296,
    STRING_LIT = 297
  };
#endif
/* Tokens.  */
#define LET 258
#define MUT 259
#define NEWLINE 260
#define INT 261
#define FLOAT 262
#define BOOL 263
#define STR 264
#define TRUE 265
#define FALSE 266
#define GEQ 267
#define LEQ 268
#define EQL 269
#define NEQ 270
#define LOR 271
#define LAND 272
#define ADD_ASSIGN 273
#define SUB_ASSIGN 274
#define MUL_ASSIGN 275
#define DIV_ASSIGN 276
#define REM_ASSIGN 277
#define IF 278
#define ELSE 279
#define FOR 280
#define WHILE 281
#define LOOP 282
#define PRINT 283
#define PRINTLN 284
#define FUNC 285
#define RETURN 286
#define BREAK 287
#define ID 288
#define ARROW 289
#define AS 290
#define IN 291
#define DOTDOT 292
#define RSHIFT 293
#define LSHIFT 294
#define INT_LIT 295
#define FLOAT_LIT 296
#define STRING_LIT 297

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 69 "compiler.y"

    int i_val;
    float f_val;
    char *s_val;

#line 271 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */



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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


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
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   324

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  63
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  52
/* YYNRULES -- Number of rules.  */
#define YYNRULES  124
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  238

#define YYUNDEFTOK  2
#define YYMAXUTOK   297


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    62,    54,     2,     2,    61,    53,     2,
      43,    44,    59,    57,    45,    58,     2,    60,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    46,    49,
      55,    50,    56,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    51,     2,    52,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    47,     2,    48,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   102,   102,   106,   107,   111,   112,   117,   124,   116,
     131,   129,   139,   147,   153,   161,   172,   173,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   188,   194,
     201,   202,   206,   206,   209,   210,   211,   212,   213,   214,
     215,   216,   219,   226,   227,   228,   232,   235,   236,   237,
     241,   244,   244,   244,   247,   250,   251,   254,   257,   262,
     265,   270,   273,   281,   284,   290,   295,   299,   305,   313,
     316,   317,   318,   321,   322,   323,   324,   324,   327,   327,
     328,   329,   329,   332,   334,   335,   335,   336,   337,   338,
     340,   339,   345,   355,   356,   357,   358,   359,   360,   364,
     365,   366,   367,   368,   369,   373,   374,   375,   376,   377,
     378,   382,   383,   387,   388,   389,   393,   394,   398,   399,
     400,   403,   411,   419,   420
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "LET", "MUT", "NEWLINE", "INT", "FLOAT",
  "BOOL", "STR", "TRUE", "FALSE", "GEQ", "LEQ", "EQL", "NEQ", "LOR",
  "LAND", "ADD_ASSIGN", "SUB_ASSIGN", "MUL_ASSIGN", "DIV_ASSIGN",
  "REM_ASSIGN", "IF", "ELSE", "FOR", "WHILE", "LOOP", "PRINT", "PRINTLN",
  "FUNC", "RETURN", "BREAK", "ID", "ARROW", "AS", "IN", "DOTDOT", "RSHIFT",
  "LSHIFT", "INT_LIT", "FLOAT_LIT", "STRING_LIT", "'('", "')'", "','",
  "':'", "'{'", "'}'", "';'", "'='", "'['", "']'", "'&'", "'\"'", "'<'",
  "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "'!'", "$accept", "Program",
  "GlobalStatementList", "GlobalStatement", "FunctionDeclStmt", "$@1",
  "$@2", "$@3", "FuncOpen", "ParameterList", "FuncBlock", "StatementList",
  "Statement", "CallFunction", "Block", "StartBlock", "$@4",
  "DeclarationStmt", "AssignmentStmt", "IFStmt", "IFOpen", "PrintStmt",
  "WhileStmt", "ForStmt", "$@5", "$@6", "LoopStmt", "DeclareArrayStmt",
  "ExpressionStmt", "LogicalORExpr", "LogicalANDExpr", "ComparisonExpr",
  "AdditionExpr", "MultiplicationExpr", "UnaryExpr", "ArrayExpr", "$@7",
  "DotExpr", "$@8", "$@9", "DOtOpen", "Operand", "$@10", "$@11", "Literal",
  "assign_op", "cmp_op", "add_op", "mul_op", "shift_op", "unary_op",
  "Type", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,    40,    41,    44,    58,   123,   125,    59,
      61,    91,    93,    38,    34,    60,    62,    43,    45,    42,
      47,    37,    33
};
# endif

#define YYPACT_NINF (-127)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-81)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      22,  -127,   -13,    35,    22,  -127,  -127,   -14,  -127,  -127,
    -127,    -6,  -127,    11,     6,    20,    29,    65,  -127,     4,
      41,    44,   208,  -127,  -127,  -127,    74,  -127,     4,    46,
      17,  -127,  -127,  -127,    91,    62,    91,    54,    56,   158,
    -127,  -127,    91,  -127,     8,    70,   -20,  -127,  -127,  -127,
      57,   208,   107,   109,    53,    67,    69,  -127,    12,    71,
     120,   122,  -127,  -127,   114,   106,   266,    32,   244,  -127,
    -127,   -22,    91,  -127,  -127,     4,   100,    -9,    37,    88,
     101,    88,   234,    91,  -127,  -127,  -127,  -127,  -127,  -127,
      -5,  -127,    96,    91,    94,   134,    95,  -127,    89,  -127,
    -127,  -127,  -127,  -127,     8,     8,    98,   142,   149,   137,
      88,   157,  -127,  -127,    91,    91,  -127,  -127,  -127,  -127,
    -127,  -127,  -127,  -127,    91,    91,    91,  -127,  -127,  -127,
    -127,  -127,    91,    91,  -127,   118,  -127,  -127,     6,  -127,
      -3,    18,     8,   130,  -127,   131,  -127,    91,   121,   123,
       4,   125,   133,   143,  -127,  -127,  -127,   118,   146,  -127,
     136,   145,  -127,  -127,  -127,    88,  -127,  -127,  -127,  -127,
      32,  -127,  -127,  -127,  -127,     4,  -127,   -12,  -127,     4,
      91,    18,   148,    59,  -127,  -127,   194,  -127,  -127,  -127,
     167,  -127,  -127,  -127,     5,   197,   200,  -127,  -127,   162,
    -127,   155,   166,    91,     8,   163,    88,   178,   179,  -127,
     172,   174,   190,   180,   181,    91,  -127,  -127,  -127,    88,
    -127,  -127,  -127,  -127,  -127,     8,  -127,     8,  -127,  -127,
    -127,  -127,  -127,   208,  -127,  -127,   182,  -127
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     6,     0,     0,     2,     4,     5,     0,    12,     1,
       3,     7,    10,     0,     0,     0,     0,     0,    11,     0,
       0,     0,     0,   121,   122,   124,     0,    14,     0,     0,
       0,    27,    97,    98,     0,     0,     0,     0,     0,    87,
      93,    94,     0,    32,     0,     0,     0,   118,   119,   120,
       0,    16,     0,     0,     0,     0,     0,    22,     0,     0,
       0,     0,    20,    57,    59,    61,    63,    66,    69,    71,
      72,    84,     0,   123,     8,     0,     0,     0,    87,     0,
       0,     0,     0,     0,   100,   101,   102,   103,   104,    90,
       0,    99,     0,     0,     0,     0,     0,    76,     0,    96,
      15,    17,    26,    18,     0,     0,     0,     0,     0,    43,
       0,     0,    24,    25,     0,     0,   110,   108,   105,   106,
     107,   109,   111,   112,     0,     0,     0,   117,   116,   113,
     114,   115,     0,     0,    85,     0,    75,    70,     0,    13,
       0,     0,     0,     0,    46,     0,    50,     0,     0,     0,
       0,     0,     0,     0,    42,    88,    33,     0,     0,    95,
       0,     0,    30,    19,    21,     0,    45,    23,    58,    60,
      62,    65,    64,    67,    68,     0,    73,     0,     9,     0,
       0,     0,     0,     0,    40,    51,     0,    48,    49,    91,
       0,    28,    89,    74,     0,     0,     0,    44,    86,    35,
      39,     0,     0,     0,     0,     0,     0,     0,     0,    78,
       0,    81,     0,     0,     0,     0,    55,    38,    56,     0,
      36,    41,    52,    47,    92,     0,    77,     0,    83,    29,
      31,    37,    54,     0,    79,    82,     0,    53
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -127,  -127,  -127,   228,  -127,  -127,  -127,  -127,  -127,  -127,
      97,   -49,  -127,  -127,   -78,    34,  -127,  -127,  -127,  -127,
    -127,  -127,  -127,  -127,  -127,  -127,  -127,    61,   -28,  -127,
     124,   128,   126,    -4,   -65,  -126,  -127,  -127,  -127,  -127,
    -127,  -127,  -127,  -127,   -44,  -127,  -127,   185,  -127,  -127,
    -127,   -24
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     5,     6,    13,   138,    14,     7,    16,
      18,    50,    51,    52,    53,    54,    95,    55,    56,    57,
      58,    59,    60,    61,   206,   233,   221,   182,    62,    63,
      64,    65,    66,    67,    68,    69,   158,   210,   225,   227,
     211,    70,   175,   150,    71,    93,   124,   125,   132,   133,
      72,    27
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      96,   144,   101,   146,    74,   106,    79,   137,    81,   176,
      23,    24,    25,   134,    94,    32,    33,   109,    32,    33,
       8,    76,    98,   135,    23,    24,    25,     1,   151,    11,
     136,   193,   166,   135,    99,     9,   110,   141,    12,   152,
     136,   142,   209,   179,    15,    40,    41,   180,    40,    41,
      77,   139,     2,    17,   148,   149,    30,    26,    31,    46,
     160,   161,    46,    32,    33,   154,    19,   173,   174,   181,
      22,    26,    89,    20,    21,    28,    34,    29,    35,    36,
     143,    37,    38,    73,   104,   105,    39,   197,    92,   122,
     123,   177,    75,    40,    41,    80,    42,    82,   184,    83,
      43,    32,    33,    97,    44,   100,    45,    46,   204,   205,
      47,    48,   102,   177,   103,    49,   107,   183,   108,   186,
     111,   171,   172,   115,    78,   112,   189,   113,    32,    33,
     114,    40,    41,   140,    42,    43,   153,   145,   155,   156,
     157,   232,    44,   159,    45,    46,   162,   163,    47,    48,
     212,   198,   200,    49,   164,   199,   220,   202,    40,    41,
     218,   165,   167,   151,   185,   187,    30,   188,    31,    44,
     190,    45,    46,    32,    33,   217,    84,    85,    86,    87,
      88,   234,   191,   235,   236,   195,    34,   231,    35,    36,
     219,    37,    38,    89,   196,   192,    39,   194,   203,   207,
     208,    90,   213,    40,    41,   214,    42,   216,    91,    92,
      43,    30,   215,    31,    44,   204,    45,    46,    32,    33,
      47,    48,   223,   224,   226,    49,   -80,   228,   229,   230,
     237,    34,    10,    35,    36,   178,    37,    38,   168,   147,
     222,    39,   201,   169,    32,    33,     0,     0,    40,    41,
     170,    42,   126,     0,     0,    43,     0,     0,     0,    44,
       0,    45,    46,     0,     0,    47,    48,    78,     0,     0,
      49,     0,     0,     0,    40,    41,     0,    42,   116,   117,
     118,   119,   127,   128,     0,    44,     0,    45,    46,     0,
       0,    47,    48,     0,     0,     0,    49,     0,     0,     0,
       0,     0,     0,   129,   130,   131,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   120,   121,   122,   123
};

static const yytype_int16 yycheck[] =
{
      44,    79,    51,    81,    28,    54,    34,    72,    36,   135,
       6,     7,     8,    35,    42,    10,    11,     5,    10,    11,
      33,     4,    42,    45,     6,     7,     8,     5,    33,    43,
      52,   157,   110,    45,    54,     0,    24,    46,    44,    44,
      52,    50,    37,    46,    33,    40,    41,    50,    40,    41,
      33,    75,    30,    47,    82,    83,     3,    53,     5,    54,
     104,   105,    54,    10,    11,    93,    46,   132,   133,    51,
       5,    53,    35,    44,    45,    34,    23,    33,    25,    26,
      43,    28,    29,     9,    31,    32,    33,   165,    51,    57,
      58,   135,    46,    40,    41,    33,    43,    43,   142,    43,
      47,    10,    11,    33,    51,    48,    53,    54,    49,    50,
      57,    58,     5,   157,     5,    62,    49,   141,    49,   147,
      49,   125,   126,    17,    33,     5,   150,     5,    10,    11,
      16,    40,    41,    33,    43,    47,    40,    36,    44,     5,
      45,   219,    51,    54,    53,    54,    48,     5,    57,    58,
     194,   175,   180,    62,     5,   179,   205,   181,    40,    41,
     204,    24,     5,    33,    33,    44,     3,    44,     5,    51,
      45,    53,    54,    10,    11,   203,    18,    19,    20,    21,
      22,   225,    49,   227,   233,    49,    23,   215,    25,    26,
      27,    28,    29,    35,    49,    52,    33,    51,    50,     5,
      33,    43,     5,    40,    41,     5,    43,    52,    50,    51,
      47,     3,    50,     5,    51,    49,    53,    54,    10,    11,
      57,    58,    44,    44,    52,    62,    52,    37,    48,    48,
      48,    23,     4,    25,    26,   138,    28,    29,   114,     5,
     206,    33,   181,   115,    10,    11,    -1,    -1,    40,    41,
     124,    43,    67,    -1,    -1,    47,    -1,    -1,    -1,    51,
      -1,    53,    54,    -1,    -1,    57,    58,    33,    -1,    -1,
      62,    -1,    -1,    -1,    40,    41,    -1,    43,    12,    13,
      14,    15,    38,    39,    -1,    51,    -1,    53,    54,    -1,
      -1,    57,    58,    -1,    -1,    -1,    62,    -1,    -1,    -1,
      -1,    -1,    -1,    59,    60,    61,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    55,    56,    57,    58
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     5,    30,    64,    65,    66,    67,    71,    33,     0,
      66,    43,    44,    68,    70,    33,    72,    47,    73,    46,
      44,    45,     5,     6,     7,     8,    53,   114,    34,    33,
       3,     5,    10,    11,    23,    25,    26,    28,    29,    33,
      40,    41,    43,    47,    51,    53,    54,    57,    58,    62,
      74,    75,    76,    77,    78,    80,    81,    82,    83,    84,
      85,    86,    91,    92,    93,    94,    95,    96,    97,    98,
     104,   107,   113,     9,   114,    46,     4,    33,    33,    91,
      33,    91,    43,    43,    18,    19,    20,    21,    22,    35,
      43,    50,    51,   108,    91,    79,   107,    33,    42,    54,
      48,    74,     5,     5,    31,    32,    74,    49,    49,     5,
      24,    49,     5,     5,    16,    17,    12,    13,    14,    15,
      55,    56,    57,    58,   109,   110,   110,    38,    39,    59,
      60,    61,   111,   112,    35,    45,    52,    97,    69,   114,
      33,    46,    50,    43,    77,    36,    77,     5,    91,    91,
     106,    33,    44,    40,    91,    44,     5,    45,    99,    54,
     107,   107,    48,     5,     5,    24,    77,     5,    93,    94,
      95,    96,    96,    97,    97,   105,    98,   107,    73,    46,
      50,    51,    90,   114,   107,    33,    91,    44,    44,   114,
      45,    49,    52,    98,    51,    49,    49,    77,   114,   114,
      91,    90,   114,    50,    49,    50,    87,     5,    33,    37,
     100,   103,   107,     5,     5,    50,    52,    91,   107,    27,
      74,    89,    78,    44,    44,   101,    52,   102,    37,    48,
      48,    91,    77,    88,   107,   107,    74,    48
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    63,    64,    65,    65,    66,    66,    68,    69,    67,
      70,    67,    71,    72,    72,    73,    74,    74,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    76,    77,
      77,    77,    79,    78,    80,    80,    80,    80,    80,    80,
      80,    80,    81,    82,    82,    82,    83,    84,    84,    84,
      85,    87,    88,    86,    89,    90,    90,    91,    92,    92,
      93,    93,    94,    94,    95,    95,    95,    96,    96,    96,
      97,    97,    97,    98,    98,    98,    99,    98,   101,   100,
     100,   102,   100,   103,   104,   105,   104,   104,   104,   104,
     106,   104,   104,   107,   107,   107,   107,   107,   107,   108,
     108,   108,   108,   108,   108,   109,   109,   109,   109,   109,
     109,   110,   110,   111,   111,   111,   112,   112,   113,   113,
     113,   114,   114,   114,   114
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     0,     0,     9,
       0,     5,     2,     5,     3,     4,     1,     2,     2,     3,
       1,     3,     1,     3,     2,     2,     2,     1,     4,     6,
       3,     6,     0,     3,     4,     5,     6,     7,     6,     5,
       4,     6,     3,     2,     4,     3,     3,     6,     4,     4,
       3,     0,     0,     9,     2,     3,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     3,     1,     3,     3,     1,
       2,     1,     1,     3,     4,     2,     0,     6,     0,     3,
       1,     0,     3,     2,     1,     0,     4,     1,     3,     4,
       0,     4,     6,     1,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
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
#  endif
# endif

# ifndef yytnamerr
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
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
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
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
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
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
  case 7:
#line 117 "compiler.y"
    {
        insert_symbol("func", (yyvsp[0].s_val), func_para, Fu, false);
        printf("> Insert `%s` (addr: -1) to scope level %d\n", (yyvsp[0].s_val), 0);
        create_symbol();
        has_return = true;
    }
#line 1643 "y.tab.c"
    break;

  case 8:
#line 124 "compiler.y"
    {
        if(strcmp((yyvsp[-1].s_val), "bool")==0)
            return_type = 'b';
    }
#line 1652 "y.tab.c"
    break;

  case 9:
#line 128 "compiler.y"
             {has_return = false;}
#line 1658 "y.tab.c"
    break;

  case 10:
#line 131 "compiler.y"
    {   
        insert_symbol("func", (yyvsp[-1].s_val), "(V)V", Fu, false);
        printf("> Insert `%s` (addr: -1) to scope level %d\n", (yyvsp[-1].s_val), 0);
        create_symbol();
    }
#line 1668 "y.tab.c"
    break;

  case 12:
#line 140 "compiler.y"
    {
        printf("func: %s\n", (yyvsp[0].s_val));
        (yyval.s_val) = (yyvsp[0].s_val);
    }
#line 1677 "y.tab.c"
    break;

  case 13:
#line 148 "compiler.y"
    {
        insert_symbol((yyvsp[0].s_val), (yyvsp[-2].s_val), "-", P, false);
        printf("> Insert `%s` (addr: %d) to scope level %d\n", (yyvsp[-2].s_val), addr-1, global_scope);
        build_func_para((yyvsp[0].s_val));
    }
#line 1687 "y.tab.c"
    break;

  case 14:
#line 154 "compiler.y"
    {
        insert_symbol((yyvsp[0].s_val), (yyvsp[-2].s_val), "-", P, false);
        printf("> Insert `%s` (addr: %d) to scope level %d\n", (yyvsp[-2].s_val), addr-1, global_scope);
        build_func_para((yyvsp[0].s_val));
    }
#line 1697 "y.tab.c"
    break;

  case 15:
#line 162 "compiler.y"
    { 
        if(has_return){
            printf("%creturn\n", return_type);
            has_return = false;
        }
        dump_symbol(); 
        
    }
#line 1710 "y.tab.c"
    break;

  case 28:
#line 189 "compiler.y"
    { 
        addr = 0;
        lookup_symbol((yyvsp[-3].s_val), Fu); // function
    }
#line 1719 "y.tab.c"
    break;

  case 29:
#line 195 "compiler.y"
    {
        return_type = 'b';
        printf("%creturn\n" , return_type);
        dump_symbol();
        
    }
#line 1730 "y.tab.c"
    break;

  case 30:
#line 201 "compiler.y"
                                   { dump_symbol(); }
#line 1736 "y.tab.c"
    break;

  case 31:
#line 202 "compiler.y"
                                               { dump_symbol();}
#line 1742 "y.tab.c"
    break;

  case 32:
#line 206 "compiler.y"
          { create_symbol(); }
#line 1748 "y.tab.c"
    break;

  case 34:
#line 209 "compiler.y"
                      { insert_symbol((yyvsp[0].s_val), (yyvsp[-2].s_val), "-", I, false ); }
#line 1754 "y.tab.c"
    break;

  case 35:
#line 210 "compiler.y"
                          { insert_symbol((yyvsp[0].s_val), (yyvsp[-2].s_val), "-", I, true ); }
#line 1760 "y.tab.c"
    break;

  case 36:
#line 211 "compiler.y"
                                        { insert_symbol((yyvsp[-2].s_val), (yyvsp[-4].s_val), "-", I, false ); }
#line 1766 "y.tab.c"
    break;

  case 37:
#line 212 "compiler.y"
                                             { insert_symbol((yyvsp[-2].s_val), (yyvsp[-4].s_val), "-", I, true ); }
#line 1772 "y.tab.c"
    break;

  case 38:
#line 213 "compiler.y"
                                                     { insert_symbol("array", (yyvsp[-4].s_val), "-", I, false ); }
#line 1778 "y.tab.c"
    break;

  case 39:
#line 214 "compiler.y"
                                    { insert_symbol("i32", (yyvsp[-2].s_val), "-", I, true ); }
#line 1784 "y.tab.c"
    break;

  case 40:
#line 215 "compiler.y"
                         { insert_symbol((yyvsp[0].s_val), (yyvsp[-2].s_val), "-", I, false); }
#line 1790 "y.tab.c"
    break;

  case 41:
#line 216 "compiler.y"
                                   { insert_symbol((yyvsp[-2].s_val), (yyvsp[-4].s_val), "-", I, false); }
#line 1796 "y.tab.c"
    break;

  case 42:
#line 220 "compiler.y"
    { 
        if(strcmp(lookup_symbol((yyvsp[-2].s_val), 3), "undefined")!=0)
            printf("%s\n", (yyvsp[-1].s_val)); 
    }
#line 1805 "y.tab.c"
    break;

  case 47:
#line 235 "compiler.y"
                                                  {printf("PRINT %s\n", (yyvsp[-2].s_val));}
#line 1811 "y.tab.c"
    break;

  case 48:
#line 236 "compiler.y"
                                    {printf("PRINT %s\n", (yyvsp[-1].s_val));}
#line 1817 "y.tab.c"
    break;

  case 49:
#line 237 "compiler.y"
                                      {printf("PRINTLN %s\n", (yyvsp[-1].s_val));}
#line 1823 "y.tab.c"
    break;

  case 51:
#line 244 "compiler.y"
                   { lookup_symbol((yyvsp[0].s_val), I); }
#line 1829 "y.tab.c"
    break;

  case 52:
#line 244 "compiler.y"
                                                               { insert_symbol("i32", (yyvsp[-4].s_val), "-", Fo, false); }
#line 1835 "y.tab.c"
    break;

  case 53:
#line 244 "compiler.y"
                                                                                                                                       { dump_symbol() ;}
#line 1841 "y.tab.c"
    break;

  case 57:
#line 254 "compiler.y"
                    {(yyval.s_val) = (yyvsp[0].s_val);}
#line 1847 "y.tab.c"
    break;

  case 58:
#line 258 "compiler.y"
    {
        (yyval.s_val) = "bool";
        printf("LOR\n");
    }
#line 1856 "y.tab.c"
    break;

  case 59:
#line 262 "compiler.y"
                     { (yyval.s_val) = (yyvsp[0].s_val); }
#line 1862 "y.tab.c"
    break;

  case 60:
#line 266 "compiler.y"
    {
        (yyval.s_val) = "bool"; 
        printf("LAND\n");
    }
#line 1871 "y.tab.c"
    break;

  case 61:
#line 270 "compiler.y"
                     { (yyval.s_val) = (yyvsp[0].s_val); }
#line 1877 "y.tab.c"
    break;

  case 62:
#line 274 "compiler.y"
    {
        if(strcmp((yyvsp[-2].s_val), (yyvsp[0].s_val)) != 0){
            printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n", yylineno+1, (yyvsp[-1].s_val), (yyvsp[-2].s_val), (yyvsp[0].s_val));
        }
        (yyval.s_val) = "bool";
        printf("%s\n", (yyvsp[-1].s_val));
    }
#line 1889 "y.tab.c"
    break;

  case 63:
#line 281 "compiler.y"
                   { (yyval.s_val) = (yyvsp[0].s_val); }
#line 1895 "y.tab.c"
    break;

  case 64:
#line 285 "compiler.y"
    {
        
        printf("%s\n", (yyvsp[-1].s_val));
        (yyval.s_val) = (yyvsp[-2].s_val); 
    }
#line 1905 "y.tab.c"
    break;

  case 65:
#line 291 "compiler.y"
    {
        printf("%s\n", (yyvsp[-1].s_val));
        (yyval.s_val) = (yyvsp[-2].s_val); 
    }
#line 1914 "y.tab.c"
    break;

  case 66:
#line 295 "compiler.y"
                         { (yyval.s_val) = (yyvsp[0].s_val); }
#line 1920 "y.tab.c"
    break;

  case 67:
#line 300 "compiler.y"
    {
        (yyval.s_val) = (yyvsp[-2].s_val);
        printf("%s\n", (yyvsp[-1].s_val));

    }
#line 1930 "y.tab.c"
    break;

  case 68:
#line 306 "compiler.y"
    {
        if(strcmp((yyvsp[-2].s_val), (yyvsp[0].s_val)) != 0){
            printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n", yylineno+1, (yyvsp[-1].s_val), (yyvsp[-2].s_val), (yyvsp[0].s_val));
        }
        (yyval.s_val) = (yyvsp[-2].s_val);
        printf("%s\n", (yyvsp[-1].s_val));
    }
#line 1942 "y.tab.c"
    break;

  case 69:
#line 313 "compiler.y"
                { (yyval.s_val) = (yyvsp[0].s_val); }
#line 1948 "y.tab.c"
    break;

  case 70:
#line 316 "compiler.y"
                         { (yyval.s_val) = (yyvsp[0].s_val); printf("%s\n", (yyvsp[-1].s_val)); }
#line 1954 "y.tab.c"
    break;

  case 71:
#line 317 "compiler.y"
                {(yyval.s_val) = (yyvsp[0].s_val);}
#line 1960 "y.tab.c"
    break;

  case 72:
#line 318 "compiler.y"
              { (yyval.s_val) = (yyvsp[0].s_val); }
#line 1966 "y.tab.c"
    break;

  case 76:
#line 324 "compiler.y"
              { lookup_symbol((yyvsp[0].s_val), I); }
#line 1972 "y.tab.c"
    break;

  case 78:
#line 327 "compiler.y"
             { printf("DOTDOT\n"); }
#line 1978 "y.tab.c"
    break;

  case 80:
#line 328 "compiler.y"
              { printf("DOTDOT\n"); }
#line 1984 "y.tab.c"
    break;

  case 81:
#line 329 "compiler.y"
               { printf("DOTDOT\n"); }
#line 1990 "y.tab.c"
    break;

  case 84:
#line 334 "compiler.y"
              { (yyval.s_val) = (yyvsp[0].s_val); }
#line 1996 "y.tab.c"
    break;

  case 85:
#line 335 "compiler.y"
                 { casting = true; }
#line 2002 "y.tab.c"
    break;

  case 87:
#line 336 "compiler.y"
         { (yyval.s_val) = lookup_symbol((yyvsp[0].s_val), I) ;}
#line 2008 "y.tab.c"
    break;

  case 88:
#line 337 "compiler.y"
                             { (yyval.s_val) = (yyvsp[-1].s_val); }
#line 2014 "y.tab.c"
    break;

  case 89:
#line 338 "compiler.y"
                         { (yyval.s_val) = lookup_symbol((yyvsp[-3].s_val), I); printf("INT_LIT %d\n", (yyvsp[-1].i_val));}
#line 2020 "y.tab.c"
    break;

  case 90:
#line 340 "compiler.y"
    {
        casting = true;
        lookup_symbol((yyvsp[-1].s_val), 1) ;
    }
#line 2029 "y.tab.c"
    break;

  case 92:
#line 346 "compiler.y"
    {
        lookup_symbol((yyvsp[-3].s_val), P); // parameter
        lookup_symbol((yyvsp[-1].s_val), P); // parameter
        has_return = true;
        return_type = 'b';
        lookup_symbol((yyvsp[-5].s_val), Fu); // function name
    }
#line 2041 "y.tab.c"
    break;

  case 93:
#line 355 "compiler.y"
              { (yyval.s_val) = "i32"; printf("INT_LIT %d\n", (yyvsp[0].i_val));}
#line 2047 "y.tab.c"
    break;

  case 94:
#line 356 "compiler.y"
                { (yyval.s_val) = "f32"; printf("FLOAT_LIT %f\n", (yyvsp[0].f_val));}
#line 2053 "y.tab.c"
    break;

  case 95:
#line 357 "compiler.y"
                         { (yyval.s_val) = "str"; printf("STRING_LIT \"%s\"\n", (yyvsp[-1].s_val));}
#line 2059 "y.tab.c"
    break;

  case 96:
#line 358 "compiler.y"
             { (yyval.s_val) = "str"; printf("STRING_LIT \"\"\n");}
#line 2065 "y.tab.c"
    break;

  case 97:
#line 359 "compiler.y"
           { (yyval.s_val) = "bool"; printf("bool TRUE\n");}
#line 2071 "y.tab.c"
    break;

  case 98:
#line 360 "compiler.y"
            { (yyval.s_val) = "bool"; printf("bool FALSE\n");}
#line 2077 "y.tab.c"
    break;

  case 99:
#line 364 "compiler.y"
          {(yyval.s_val) = "ASSIGN";}
#line 2083 "y.tab.c"
    break;

  case 100:
#line 365 "compiler.y"
                 {(yyval.s_val) = "ADD_ASSIGN";}
#line 2089 "y.tab.c"
    break;

  case 101:
#line 366 "compiler.y"
                 {(yyval.s_val) = "SUB_ASSIGN";}
#line 2095 "y.tab.c"
    break;

  case 102:
#line 367 "compiler.y"
                 {(yyval.s_val) = "MUL_ASSIGN";}
#line 2101 "y.tab.c"
    break;

  case 103:
#line 368 "compiler.y"
                 {(yyval.s_val) = "DIV_ASSIGN";}
#line 2107 "y.tab.c"
    break;

  case 104:
#line 369 "compiler.y"
                 {(yyval.s_val) = "REM_ASSIGN";}
#line 2113 "y.tab.c"
    break;

  case 105:
#line 373 "compiler.y"
          { (yyval.s_val) = "EQL"; }
#line 2119 "y.tab.c"
    break;

  case 106:
#line 374 "compiler.y"
          { (yyval.s_val) = "NEQ"; }
#line 2125 "y.tab.c"
    break;

  case 107:
#line 375 "compiler.y"
          { (yyval.s_val) = "LSS"; }
#line 2131 "y.tab.c"
    break;

  case 108:
#line 376 "compiler.y"
          { (yyval.s_val) = "LEQ"; }
#line 2137 "y.tab.c"
    break;

  case 109:
#line 377 "compiler.y"
          { (yyval.s_val) = "GTR"; }
#line 2143 "y.tab.c"
    break;

  case 110:
#line 378 "compiler.y"
          { (yyval.s_val) = "GEQ"; }
#line 2149 "y.tab.c"
    break;

  case 111:
#line 382 "compiler.y"
          { (yyval.s_val) = "ADD"; }
#line 2155 "y.tab.c"
    break;

  case 112:
#line 383 "compiler.y"
          { (yyval.s_val) = "SUB"; }
#line 2161 "y.tab.c"
    break;

  case 113:
#line 387 "compiler.y"
          { (yyval.s_val) = "MUL"; }
#line 2167 "y.tab.c"
    break;

  case 114:
#line 388 "compiler.y"
          { (yyval.s_val) = "DIV"; }
#line 2173 "y.tab.c"
    break;

  case 115:
#line 389 "compiler.y"
          { (yyval.s_val) = "REM"; }
#line 2179 "y.tab.c"
    break;

  case 116:
#line 393 "compiler.y"
             { (yyval.s_val) = "LSHIFT"; }
#line 2185 "y.tab.c"
    break;

  case 117:
#line 394 "compiler.y"
             { (yyval.s_val) = "RSHIFT"; }
#line 2191 "y.tab.c"
    break;

  case 118:
#line 398 "compiler.y"
          { (yyval.s_val) = "POS"; }
#line 2197 "y.tab.c"
    break;

  case 119:
#line 399 "compiler.y"
          { (yyval.s_val) = "NEG"; }
#line 2203 "y.tab.c"
    break;

  case 120:
#line 400 "compiler.y"
          { (yyval.s_val) = "NOT"; }
#line 2209 "y.tab.c"
    break;

  case 121:
#line 404 "compiler.y"
    { 
        (yyval.s_val) = "i32";
        if(casting){
            casting = false;
            printf("f2i\n");
        } 
    }
#line 2221 "y.tab.c"
    break;

  case 122:
#line 412 "compiler.y"
    { 
        (yyval.s_val) = "f32";
        if(casting){
            casting = false;
            printf("i2f\n");
        } 
    }
#line 2233 "y.tab.c"
    break;

  case 123:
#line 419 "compiler.y"
                            { (yyval.s_val) = "str"; }
#line 2239 "y.tab.c"
    break;

  case 124:
#line 420 "compiler.y"
                        { (yyval.s_val) = "bool"; }
#line 2245 "y.tab.c"
    break;


#line 2249 "y.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
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
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 424 "compiler.y"


/* C code section */
int main(int argc, char *argv[])
{
    if (argc == 2) {
        yyin = fopen(argv[1], "r");
    } else {
        yyin = stdin;
    }
    create_symbol();
    yylineno = 0;
    yyparse();
    dump_symbol();

	printf("Total lines: %d\n", yylineno);
    fclose(yyin);
    return 0;
}

static void create_symbol() {
    global_scope ++;
    printf("> Create symbol table (scope level %d)\n", global_scope);
    
    struct table *tmp = malloc(sizeof(struct symbol));
    tmp -> scope = global_scope;
    tmp -> prev = current_table;
    tmp -> head = NULL;
    current_table = tmp;
    
}

static void insert_symbol(char* type, char* name, char* func_sig, int mark_var, bool has_mut) {// if mark_var = 0, function; else if mark_var = 1, parameter, else if mark_var == 2, id, else(foreach), mark_var == 3
    struct symbol *tail = NULL;
    struct table *first = current_table;
    bool empty = false;
    if(mark_var == Fu){ // function
        while(first-> prev != NULL) // is not the head of table
            first = first -> prev;
        /* after find the head of table */
        if(first -> head != NULL){ // not empty -> add to tail
            tail = first -> head;
            while(tail -> next != NULL)
                tail = tail->next;
        }
        else // empty
            empty = true;
    }
    else{
        if(first -> head != NULL){
            tail = current_table -> head;
            while(tail -> next !=NULL){
                tail = tail->next;
            }
        }
        else
            empty = true;
    }
    /* to this point, first and tail is moved to the right position */
        /* function: first -> head of table, tail -> the tail of first */
        /* parameter: first -> current of table, tail -> the tail of first */
    struct symbol *new = malloc(sizeof(struct symbol));
    // next
    new -> next = NULL;
    // name
    new -> name = strdup(name);// 和strcpy不太一樣，可以直接把要複製的內容給未經過初始化或分配空間的指標，相當於strlen + 分配空間 + strcpy  
    // mut
    if(mark_var == Fu)
        new -> mut = -1;
    else if(has_mut)
        new -> mut = 1;
    else 
        new -> mut = 0;
    // type
    new -> type = strdup(type);
    // addr and lineno 
    if(mark_var == Fu){// function
        new -> lineno = yylineno + 1;
        new -> addr = -1;
    }
    else if(mark_var == P){// parameter
        new -> lineno = yylineno + 1;
        new -> addr = addr;
        addr ++;
    }
    else if(mark_var == I) { // id
        new -> lineno = yylineno + 1 ;
        new -> addr = addr;
        addr ++;
    }
    else{ // foreach
        new -> lineno = yylineno;
        new -> addr = addr;
        addr ++;
    }
    // func_sig
    new -> func_sig = strdup(func_sig);
    // index
    if(!empty){
        new -> index = (tail -> index) + 1;
        tail -> next = new;
    }
    else{
        new -> index = 0;
        first -> head = new;
    }
    // print
    if(mark_var == I || mark_var == Fo)// id and foreach
        printf("> Insert `%s` (addr: %d) to scope level %d\n", name, new -> addr, global_scope);
}

static char *lookup_symbol(char *name, int mark_var) { // if mark_var = 0, function; else if mark_var = 1, parameter, else(id) is 2
    struct table *t = current_table;
    struct symbol *s = NULL;
    while(t!=NULL){
        s = t -> head;
        while(s!= NULL){
            if(strcmp(s-> name, name) == 0){
                if(mark_var == Fu)// function
                {
                    if(has_return){
                        strcat(func_para, ")");
                        printf("call: %s%s%c\n", s -> name, func_para, toupper(return_type));
                        has_return = false;
                        if(return_type == 'b')
                            s -> func_sig = strcat(func_para, "B");
                        return s -> func_sig  ;
                    }
                    else{
                        printf("call: %s%s\n", s -> name, s -> func_sig);
                        return s -> func_sig;
                    }
                }
                    
                else if(mark_var != Fo){// not function and foreach
                    printf("IDENT (name=%s, address=%d)\n", s->name, s->addr);
                    return s-> type;
                }
                else
                    return s-> type;
            }
            else// name is not same
                s = s->next;
        }
        t = t-> prev;
    }
    /* if it's not return until this step, it is represent the symbol is an error */
    printf("error:%d: undefined: %s\n", yylineno+1, name);
    return "undefined";
}

static void dump_symbol() {
    printf("\n> Dump symbol table (scope level: %d)\n", current_table -> scope);
    printf("%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n",
        "Index", "Name", "Mut","Type", "Addr", "Lineno", "Func_sig");
    
    struct symbol *tmp = current_table-> head;
    while(tmp!= NULL){
        printf("%-10d%-10s%-10d%-10s%-10d%-10d%-10s\n",
            tmp-> index, tmp-> name, tmp-> mut, tmp-> type, tmp-> addr, tmp-> lineno, tmp-> func_sig);
        tmp = tmp->next;
    }
    current_table = current_table-> prev;
    global_scope--;
}

static void build_func_para(char *para) {
    char tmp = toupper(para[0]);
    strcat(func_para, &tmp);
}
