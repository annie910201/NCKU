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



    /* hw3 */
    static int lookup_symbol_address(char*, int);
    static char *lookup_symbol(char*, int);
    // static void code_generation();
    FILE *fp = NULL;
    int label_number = 0;
    char id_storage[10], id_temp[10];
    int is_main = 0;
    bool is_while = false;
    int cmp_op = 0;
    int function_label = 0;
    int load_num = 0;
    char* parameter_stack[10];
    int ptr_parameter = 0;
    // char para_print[100];
    bool is_if = false;
    bool is_array = false;
    int ptr_array = 0;
    int number_arr = 0;
    bool g_has_error = false;
    bool loop = false;
    bool is_for = false;

#line 155 "y.tab.c"

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
#line 96 "compiler.y"

    int i_val;
    float f_val;
    char *s_val;

#line 297 "y.tab.c"

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
#define YYLAST   296

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  63
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  61
/* YYNRULES -- Number of rules.  */
#define YYNRULES  133
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  247

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
       0,   129,   129,   133,   134,   138,   139,   144,   151,   143,
     172,   171,   189,   207,   214,   224,   253,   254,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   269,   277,
     295,   305,   309,   309,   312,   329,   346,   357,   369,   368,
     377,   381,   393,   408,   409,   417,   418,   419,   420,   420,
     424,   427,   423,   460,   469,   468,   475,   474,   483,   482,
     490,   508,   525,   557,   562,   556,   578,   597,   577,   612,
     611,   619,   622,   628,   631,   637,   640,   690,   693,   700,
     706,   710,   717,   725,   728,   747,   748,   764,   764,   765,
     766,   766,   769,   771,   772,   772,   773,   774,   775,   785,
     784,   793,   806,   820,   821,   822,   823,   824,   828,   829,
     830,   831,   832,   833,   837,   838,   839,   840,   841,   842,
     846,   847,   851,   852,   853,   857,   858,   862,   863,   864,
     867,   876,   885,   886
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
  "DeclarationStmt", "$@5", "DeclareArrayStmt", "ArrayExpr", "$@6",
  "AssignmentStmt", "$@7", "$@8", "IFStmt", "$@9", "$@10", "IFOpen",
  "$@11", "PrintStmt", "WhileStmt", "$@12", "$@13", "ForStmt", "$@14",
  "$@15", "LoopStmt", "$@16", "ExpressionStmt", "LogicalORExpr",
  "LogicalANDExpr", "ComparisonExpr", "AdditionExpr", "MultiplicationExpr",
  "UnaryExpr", "DotExpr", "$@17", "$@18", "DOtOpen", "Operand", "$@19",
  "$@20", "Literal", "assign_op", "cmp_op", "add_op", "mul_op", "shift_op",
  "unary_op", "Type", YY_NULLPTR
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

#define YYPACT_NINF (-133)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-90)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       3,  -133,   -26,    24,     3,  -133,  -133,   -34,  -133,  -133,
    -133,   -12,  -133,     4,   -13,     6,    87,    43,  -133,     9,
      26,    37,   197,  -133,  -133,  -133,    68,  -133,     9,    33,
       2,  -133,  -133,  -133,  -133,  -133,  -133,    59,    76,    45,
    -133,  -133,    84,  -133,   133,    95,   -28,  -133,  -133,  -133,
      88,   197,   121,   134,    58,    96,  -133,   102,  -133,    52,
     104,   153,   155,     1,  -133,   156,   159,    16,    65,   110,
    -133,    14,    84,  -133,  -133,     9,   150,    32,    84,   161,
      84,   223,    84,  -133,    -8,   146,    78,   145,   191,   166,
    -133,   143,  -133,  -133,  -133,  -133,  -133,   133,   133,   164,
     193,   196,   180,  -133,   208,  -133,  -133,    25,    84,    84,
    -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,    84,    84,
      84,  -133,  -133,  -133,  -133,  -133,    84,    84,  -133,   242,
    -133,  -133,   -13,  -133,    47,     5,   133,   168,   181,  -133,
      84,   172,   174,     9,   176,   170,   175,   198,  -133,  -133,
     242,   173,  -133,   183,   186,  -133,  -133,  -133,  -133,   168,
    -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,
      65,  -133,  -133,  -133,  -133,     9,  -133,    62,  -133,     9,
      84,     5,  -133,   116,  -133,  -133,   203,   168,   224,  -133,
    -133,  -133,   206,  -133,  -133,  -133,    93,   236,   237,   168,
    -133,    84,  -133,   195,  -133,   194,   200,   207,   133,   152,
    -133,  -133,   199,   214,  -133,   209,   210,   228,   212,   219,
    -133,  -133,    84,  -133,    84,  -133,  -133,  -133,  -133,   168,
    -133,  -133,   133,  -133,   133,  -133,  -133,  -133,  -133,  -133,
     168,   197,  -133,  -133,  -133,   220,  -133
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     6,     0,     0,     2,     4,     5,     0,    12,     1,
       3,     7,    10,     0,     0,     0,     0,     0,    11,     0,
       0,     0,     0,   130,   131,   133,     0,    14,     0,     0,
       0,    27,   106,   107,    58,    66,    63,     0,     0,    96,
     102,   103,     0,    32,     0,     0,     0,   127,   128,   129,
       0,    16,     0,     0,     0,     0,    85,     0,    22,     0,
       0,     0,     0,    20,    71,    73,    75,    77,    80,    83,
      86,    93,     0,   132,     8,     0,     0,     0,     0,     0,
       0,     0,     0,    99,     0,     0,    96,     0,     0,     0,
      48,     0,   105,    15,    17,    26,    18,     0,     0,     0,
       0,     0,    53,    56,     0,    24,    25,     0,     0,     0,
     119,   117,   114,   115,   116,   118,   120,   121,     0,     0,
       0,   126,   125,   122,   123,   124,     0,     0,    94,     0,
      47,    84,     0,    13,     0,     0,     0,     0,     0,    64,
       0,     0,     0,     0,     0,     0,     0,     0,    97,    33,
       0,     0,   104,     0,     0,    30,    19,    21,    54,     0,
      23,   109,   110,   111,   112,   113,   108,    51,    72,    74,
      76,    79,    78,    81,    82,     0,    45,     0,     9,     0,
       0,     0,    38,     0,    41,    59,     0,     0,     0,    61,
      62,   100,     0,    28,    98,    46,     0,     0,     0,     0,
      57,     0,    95,    35,    40,     0,     0,     0,     0,     0,
      67,    65,     0,     0,    87,     0,    90,     0,     0,     0,
      55,    52,     0,    43,     0,    44,    69,    36,    42,     0,
      60,   101,     0,    49,     0,    92,    29,    31,    37,    39,
       0,     0,    88,    91,    70,     0,    68
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -133,  -133,  -133,   243,  -133,  -133,  -133,  -133,  -133,  -133,
     137,   -50,  -133,  -133,  -132,    41,  -133,  -133,  -133,    90,
    -111,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,
    -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,   -40,
    -133,   165,   163,   157,    48,   -62,  -133,  -133,  -133,  -133,
    -133,  -133,  -133,   -44,  -133,  -133,   211,  -133,  -133,  -133,
     -25
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     5,     6,    13,   132,    14,     7,    16,
      18,    50,    51,    52,    53,    54,    88,    55,   207,   182,
      56,   151,    57,   107,   201,    58,   199,   159,    59,    78,
      60,    61,    80,   187,    62,    79,   229,   228,   240,    63,
      64,    65,    66,    67,    68,    69,   215,   232,   234,   216,
      70,   175,   143,    71,   167,   118,   119,   126,   127,    72,
      27
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      89,    94,    87,    74,    99,   185,    76,     8,     1,    11,
     131,    23,    24,    25,    91,    23,    24,    25,   176,   -50,
     -50,   -50,   -50,   -50,     9,   144,    92,   200,   110,   111,
     112,   113,    12,     2,    17,    77,   145,    15,   137,   195,
     139,   141,   142,   161,   162,   163,   164,   165,    22,   128,
     133,   -50,    19,   153,   154,   211,   181,   102,    26,   129,
      28,    30,    26,    31,   173,   174,   130,   220,    32,    33,
      29,   114,   115,   116,   117,   166,   103,    73,   135,    75,
      83,    34,   136,    35,    36,   177,    37,    38,    84,    97,
      98,    39,   184,   179,    32,    33,    85,   180,    40,    41,
     188,    42,    81,    32,    33,    43,   177,   129,   244,    44,
     183,    45,    46,    83,   130,    47,    48,    86,   191,    82,
      49,   147,   116,   117,    40,    41,    95,    42,    90,    85,
     214,    20,    21,    40,    41,    44,    93,    45,    46,    96,
     204,    47,    48,    32,    33,   100,    49,    46,   121,   122,
     202,   101,   217,   104,   203,    30,   206,    31,   105,   227,
     106,   221,    32,    33,   225,   208,   209,   171,   172,   123,
     124,   125,   108,    40,    41,    34,   109,    35,    36,   226,
      37,    38,   238,   134,   239,    39,   146,    46,   242,   148,
     243,   245,    40,    41,   138,    42,   149,   152,   156,    43,
      30,   157,    31,    44,   158,    45,    46,    32,    33,    47,
      48,   150,   155,   160,    49,    43,   189,   186,   190,   193,
      34,   192,    35,    36,   196,    37,    38,   194,   140,   212,
      39,   144,   197,    32,    33,   198,   210,    40,    41,   213,
      42,   218,   219,   230,    43,   222,   223,    10,    44,   208,
      45,    46,    32,    33,    47,    48,    86,   224,   231,    49,
     236,   233,   -89,    40,    41,   235,    42,   237,   246,   178,
     241,   205,   169,   168,    44,   170,    45,    46,     0,   120,
      47,    48,    40,    41,     0,    49,     0,     0,     0,     0,
       0,     0,     0,    44,     0,    45,    46
};

static const yytype_int16 yycheck[] =
{
      44,    51,    42,    28,    54,   137,     4,    33,     5,    43,
      72,     6,     7,     8,    42,     6,     7,     8,   129,    18,
      19,    20,    21,    22,     0,    33,    54,   159,    12,    13,
      14,    15,    44,    30,    47,    33,    44,    33,    78,   150,
      80,    81,    82,    18,    19,    20,    21,    22,     5,    35,
      75,    50,    46,    97,    98,   187,    51,     5,    53,    45,
      34,     3,    53,     5,   126,   127,    52,   199,    10,    11,
      33,    55,    56,    57,    58,    50,    24,     9,    46,    46,
      35,    23,    50,    25,    26,   129,    28,    29,    43,    31,
      32,    33,   136,    46,    10,    11,    51,    50,    40,    41,
     140,    43,    43,    10,    11,    47,   150,    45,   240,    51,
     135,    53,    54,    35,    52,    57,    58,    33,   143,    43,
      62,    43,    57,    58,    40,    41,     5,    43,    33,    51,
      37,    44,    45,    40,    41,    51,    48,    53,    54,     5,
     180,    57,    58,    10,    11,    49,    62,    54,    38,    39,
     175,    49,   196,    49,   179,     3,   181,     5,     5,   209,
       5,   201,    10,    11,   208,    49,    50,   119,   120,    59,
      60,    61,    16,    40,    41,    23,    17,    25,    26,    27,
      28,    29,   222,    33,   224,    33,    40,    54,   232,    44,
     234,   241,    40,    41,    33,    43,     5,    54,     5,    47,
       3,     5,     5,    51,    24,    53,    54,    10,    11,    57,
      58,    45,    48,     5,    62,    47,    44,    36,    44,    49,
      23,    45,    25,    26,    51,    28,    29,    52,     5,     5,
      33,    33,    49,    10,    11,    49,    33,    40,    41,    33,
      43,     5,     5,    44,    47,    50,    52,     4,    51,    49,
      53,    54,    10,    11,    57,    58,    33,    50,    44,    62,
      48,    52,    52,    40,    41,    37,    43,    48,    48,   132,
     229,   181,   109,   108,    51,   118,    53,    54,    -1,    68,
      57,    58,    40,    41,    -1,    62,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    51,    -1,    53,    54
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     5,    30,    64,    65,    66,    67,    71,    33,     0,
      66,    43,    44,    68,    70,    33,    72,    47,    73,    46,
      44,    45,     5,     6,     7,     8,    53,   123,    34,    33,
       3,     5,    10,    11,    23,    25,    26,    28,    29,    33,
      40,    41,    43,    47,    51,    53,    54,    57,    58,    62,
      74,    75,    76,    77,    78,    80,    83,    85,    88,    91,
      93,    94,    97,   102,   103,   104,   105,   106,   107,   108,
     113,   116,   122,     9,   123,    46,     4,    33,    92,    98,
      95,    43,    43,    35,    43,    51,    33,   102,    79,   116,
      33,    42,    54,    48,    74,     5,     5,    31,    32,    74,
      49,    49,     5,    24,    49,     5,     5,    86,    16,    17,
      12,    13,    14,    15,    55,    56,    57,    58,   118,   119,
     119,    38,    39,    59,    60,    61,   120,   121,    35,    45,
      52,   108,    69,   123,    33,    46,    50,   102,    33,   102,
       5,   102,   102,   115,    33,    44,    40,    43,    44,     5,
      45,    84,    54,   116,   116,    48,     5,     5,    24,    90,
       5,    18,    19,    20,    21,    22,    50,   117,   104,   105,
     106,   107,   107,   108,   108,   114,    83,   116,    73,    46,
      50,    51,    82,   123,   116,    77,    36,    96,   102,    44,
      44,   123,    45,    49,    52,    83,    51,    49,    49,    89,
      77,    87,   123,   123,   102,    82,   123,    81,    49,    50,
      33,    77,     5,    33,    37,   109,   112,   116,     5,     5,
      77,   102,    50,    52,    50,   116,    27,    74,   100,    99,
      44,    44,   110,    52,   111,    37,    48,    48,   102,   102,
     101,    78,   116,   116,    77,    74,    48
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    63,    64,    65,    65,    66,    66,    68,    69,    67,
      70,    67,    71,    72,    72,    73,    74,    74,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    76,    77,
      77,    77,    79,    78,    80,    80,    80,    80,    81,    80,
      80,    80,    80,    82,    82,    83,    83,    83,    84,    83,
      86,    87,    85,    88,    89,    88,    90,    88,    92,    91,
      93,    93,    93,    95,    96,    94,    98,    99,    97,   101,
     100,   102,   103,   103,   104,   104,   105,   105,   106,   106,
     106,   107,   107,   107,   108,   108,   108,   110,   109,   109,
     111,   109,   112,   113,   114,   113,   113,   113,   113,   115,
     113,   113,   116,   116,   116,   116,   116,   116,   117,   117,
     117,   117,   117,   117,   118,   118,   118,   118,   118,   118,
     119,   119,   120,   120,   120,   121,   121,   122,   122,   122,
     123,   123,   123,   123
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     0,     0,     9,
       0,     5,     2,     5,     3,     4,     1,     2,     2,     3,
       1,     3,     1,     3,     2,     2,     2,     1,     4,     6,
       3,     6,     0,     3,     4,     5,     6,     7,     0,     7,
       5,     4,     6,     3,     3,     3,     4,     2,     0,     6,
       0,     0,     5,     2,     0,     5,     0,     4,     0,     4,
       6,     4,     4,     0,     0,     5,     0,     0,     9,     0,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     3,
       1,     3,     3,     1,     2,     1,     1,     0,     3,     1,
       0,     3,     2,     1,     0,     4,     1,     3,     4,     0,
       4,     6,     1,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1
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
#line 144 "compiler.y"
    {
        
        printf("> Insert `%s` (addr: -1) to scope level %d\n", (yyvsp[0].s_val), 0);
        create_symbol();
        has_return = true;
    }
#line 1672 "y.tab.c"
    break;

  case 8:
#line 151 "compiler.y"
    {
        
        
        strcat(func_para, ")");
        if(strcmp((yyvsp[0].s_val), "bool")==0){
            return_type = 'b';
        }
        insert_symbol("func", (yyvsp[-5].s_val), func_para, Fu, false);
        if(is_main == 0){
            fprintf(fp, "%s%c\n", func_para, toupper(return_type));
            fprintf(fp, ".limit stack 20\n");
            fprintf(fp, ".limit locals 20\n");
        }
    }
#line 1691 "y.tab.c"
    break;

  case 9:
#line 166 "compiler.y"
    {
        has_return = false;
        return_type = 'v';
    }
#line 1700 "y.tab.c"
    break;

  case 10:
#line 172 "compiler.y"
    {   
        insert_symbol("func", (yyvsp[-1].s_val), "()V", Fu, false);
        printf("> Insert `%s` (addr: -1) to scope level %d\n", (yyvsp[-1].s_val), 0);
        create_symbol();

        if(is_main == 0){
            fprintf(fp, "()V\n");
            fprintf(fp, ".limit stack 20\n");
            fprintf(fp, ".limit locals 20\n");
        }
        else{
            // is_main =0;
        }
    }
#line 1719 "y.tab.c"
    break;

  case 12:
#line 190 "compiler.y"
    {
        printf("func: %s\n", (yyvsp[0].s_val));
        (yyval.s_val) = (yyvsp[0].s_val);
        if(strcmp((yyvsp[0].s_val), "main") == 0){
            fprintf(fp, ".method public static main([Ljava/lang/String;)V\n");
            fprintf(fp, ".limit stack 100\n");
            fprintf(fp, ".limit locals 100\n");
            is_main = 1;
        }
        else{
            fprintf(fp, ".method public static %s", (yyvsp[0].s_val));
            is_main = 0;
        }
    }
#line 1738 "y.tab.c"
    break;

  case 13:
#line 208 "compiler.y"
    {
        insert_symbol((yyvsp[0].s_val), (yyvsp[-2].s_val), "-", P, false);
        // parameter_stack[ptr_parameter++] = $<s_val>3;
        printf("> Insert `%s` (addr: %d) to scope level %d\n", (yyvsp[-2].s_val), addr-1, global_scope);
        build_func_para((yyvsp[0].s_val));
    }
#line 1749 "y.tab.c"
    break;

  case 14:
#line 215 "compiler.y"
    {
        insert_symbol((yyvsp[0].s_val), (yyvsp[-2].s_val), "-", P, false);
        // parameter_stack[ptr_parameter++] = $<s_val>1;
        printf("> Insert `%s` (addr: %d) to scope level %d\n", (yyvsp[-2].s_val), addr-1, global_scope);
        build_func_para((yyvsp[0].s_val));
        
    }
#line 1761 "y.tab.c"
    break;

  case 15:
#line 225 "compiler.y"
    { 
        
        if(has_return){
            if (return_type == 'b'){
                fprintf(fp, "iconst_1\n");
                fprintf(fp, "L_exit:\n\n");
                fprintf(fp, "ireturn\n");
            } else {
                fprintf(fp, "L_exit:\n\n");
                fprintf(fp, "%creturn\n", return_type);
            }
            has_return = false;
        }
        else if(is_main == 0){
            fprintf(fp, "return\n");
        }
        else {
            fprintf(fp, "return\n");
            is_main = 0;
        }
            
        dump_symbol(); 
        
        fprintf(fp, ".end method\n");
        
    }
#line 1792 "y.tab.c"
    break;

  case 28:
#line 270 "compiler.y"
    { 
        // addr = 0;
        lookup_symbol((yyvsp[-3].s_val), Fu); // function

    }
#line 1802 "y.tab.c"
    break;

  case 29:
#line 278 "compiler.y"
    {
        if(strcmp((yyvsp[-3].s_val), "true") == 0 || strcmp((yyvsp[-3].s_val), "false") == 0){
            return_type = 'b';
            printf("%creturn\n" , return_type);
        }
        if(return_type == 'b'){
            if(strcmp((yyvsp[-3].s_val), "false") == 0){
                fprintf(fp, "iconst_0\n");
            } else {
                fprintf(fp, "iconst_1\n");
            }
            fprintf(fp, "goto L_exit\n");
        }
        
        dump_symbol();
        
    }
#line 1824 "y.tab.c"
    break;

  case 30:
#line 296 "compiler.y"
    { 
        dump_symbol();
        if(is_if){
            is_if = false;
        }
        if(loop){
            fprintf(fp, "goto L_loop\n");
        }
    }
#line 1838 "y.tab.c"
    break;

  case 31:
#line 305 "compiler.y"
                                               { dump_symbol();}
#line 1844 "y.tab.c"
    break;

  case 32:
#line 309 "compiler.y"
          { create_symbol(); }
#line 1850 "y.tab.c"
    break;

  case 34:
#line 312 "compiler.y"
                      { 
        insert_symbol((yyvsp[0].s_val), (yyvsp[-2].s_val), "-", I, false ); 
        if(strcmp((yyvsp[0].s_val), "i32") == 0){
            fprintf(fp, "ldc 0\n");
            fprintf(fp, "istore %d\n", lookup_symbol_address((yyvsp[-2].s_val), I));
        }
            
        else if(strcmp((yyvsp[0].s_val), "f32") == 0){
            fprintf(fp, "ldc 0.000000\n");
            fprintf(fp, "fstore %d\n", lookup_symbol_address((yyvsp[-2].s_val), I));
        }
            
        else if(strcmp((yyvsp[0].s_val), "str") == 0){
            fprintf(fp, "ldc \"\\n\"\n");
            fprintf(fp, "astore %d\n", lookup_symbol_address((yyvsp[-2].s_val), I));
        }
    }
#line 1872 "y.tab.c"
    break;

  case 35:
#line 329 "compiler.y"
                          { 
        insert_symbol((yyvsp[0].s_val), (yyvsp[-2].s_val), "-", I, true ); 
        if(strcmp((yyvsp[0].s_val), "i32") == 0){
            fprintf(fp, "ldc 0\n");
            fprintf(fp, "istore %d\n", lookup_symbol_address((yyvsp[-2].s_val), I));
        }
            
        else if(strcmp((yyvsp[0].s_val), "f32") == 0){
            fprintf(fp, "ldc 0.000000\n");
            fprintf(fp, "fstore %d\n", lookup_symbol_address((yyvsp[-2].s_val), I));
        }
            
        else if(strcmp((yyvsp[0].s_val), "str") == 0){
            fprintf(fp, "ldc \"\\n\"\n");
            fprintf(fp, "astore %d\n", lookup_symbol_address((yyvsp[-2].s_val), I));
        }
    }
#line 1894 "y.tab.c"
    break;

  case 36:
#line 346 "compiler.y"
                                        { 
        insert_symbol((yyvsp[-2].s_val), (yyvsp[-4].s_val), "-", I, false ); 
        if(strcmp((yyvsp[-2].s_val), "i32") == 0)
            fprintf(fp, "istore %d\n", lookup_symbol_address((yyvsp[-4].s_val), I));
        else if(strcmp((yyvsp[-2].s_val), "f32") == 0)
            fprintf(fp, "fstore %d\n", lookup_symbol_address((yyvsp[-4].s_val), I));
        else if(strcmp((yyvsp[-2].s_val), "str") == 0)
            fprintf(fp, "astore %d\n", lookup_symbol_address((yyvsp[-4].s_val), I));
        else if(strcmp((yyvsp[-2].s_val), "bool") == 0)
            fprintf(fp, "istore %d\n", lookup_symbol_address((yyvsp[-4].s_val), I));
    }
#line 1910 "y.tab.c"
    break;

  case 37:
#line 357 "compiler.y"
                                             { 
        insert_symbol((yyvsp[-2].s_val), (yyvsp[-4].s_val), "-", I, true ); 
        if(strcmp((yyvsp[-2].s_val), "i32") == 0)
            fprintf(fp, "istore %d\n", lookup_symbol_address((yyvsp[-4].s_val), I));
        else if(strcmp((yyvsp[-2].s_val), "f32") == 0)
            fprintf(fp, "fstore %d\n", lookup_symbol_address((yyvsp[-4].s_val), I));
        else if(strcmp((yyvsp[-2].s_val), "str") == 0)
            fprintf(fp, "astore %d\n", lookup_symbol_address((yyvsp[-4].s_val), I));
        else if(strcmp((yyvsp[-2].s_val), "bool") == 0)
            fprintf(fp, "istore %d\n", lookup_symbol_address((yyvsp[-4].s_val), I));
    }
#line 1926 "y.tab.c"
    break;

  case 38:
#line 369 "compiler.y"
    {
        is_array = true;
    }
#line 1934 "y.tab.c"
    break;

  case 39:
#line 373 "compiler.y"
    { 
        insert_symbol("array", (yyvsp[-5].s_val), "-", I, false );
        fprintf(fp, "astore_1\n");
    }
#line 1943 "y.tab.c"
    break;

  case 40:
#line 377 "compiler.y"
                                    { 
        insert_symbol("i32", (yyvsp[-2].s_val), "-", I, true ); 
        fprintf(fp, "istore %d\n", lookup_symbol_address((yyvsp[-2].s_val), I));
    }
#line 1952 "y.tab.c"
    break;

  case 41:
#line 382 "compiler.y"
    { 
        insert_symbol((yyvsp[0].s_val), (yyvsp[-2].s_val), "-", I, false); 
        if(strcmp((yyvsp[0].s_val), "i32") == 0)
            fprintf(fp, "istore %d\n", lookup_symbol_address((yyvsp[-2].s_val), I));
        else if(strcmp((yyvsp[0].s_val), "f32") == 0)
            fprintf(fp, "fstore %d\n", lookup_symbol_address((yyvsp[-2].s_val), I));
        else if(strcmp((yyvsp[0].s_val), "str") == 0)
            fprintf(fp, "astore %d\n", lookup_symbol_address((yyvsp[-2].s_val), I));
        else if(strcmp((yyvsp[0].s_val), "bool") == 0)
            fprintf(fp, "istore %d\n", lookup_symbol_address((yyvsp[-2].s_val), I));
    }
#line 1968 "y.tab.c"
    break;

  case 42:
#line 394 "compiler.y"
    {
        insert_symbol((yyvsp[-2].s_val), (yyvsp[-4].s_val), "-", I, false); 
        fprintf(fp, "L_loop_end:\n");
        if(strcmp((yyvsp[-2].s_val), "i32") == 0)
            fprintf(fp, "istore %d\n", lookup_symbol_address((yyvsp[-3].s_val), I));
        else if(strcmp((yyvsp[-2].s_val), "f32") == 0)
            fprintf(fp, "fstore %d\n", lookup_symbol_address((yyvsp[-3].s_val), I));
        else if(strcmp((yyvsp[-2].s_val), "str") == 0)
            fprintf(fp, "astore %d\n", lookup_symbol_address((yyvsp[-3].s_val), I));
        else if(strcmp((yyvsp[-2].s_val), "bool") == 0)
            fprintf(fp, "istore %d\n", lookup_symbol_address((yyvsp[-3].s_val), I));
    }
#line 1985 "y.tab.c"
    break;

  case 44:
#line 410 "compiler.y"
    {
        if(strcmp((yyvsp[-2].s_val), "i32") == 0)
            fprintf(fp, "newarray int\n");
    }
#line 1994 "y.tab.c"
    break;

  case 48:
#line 420 "compiler.y"
              { lookup_symbol((yyvsp[0].s_val), I); }
#line 2000 "y.tab.c"
    break;

  case 50:
#line 424 "compiler.y"
    {
        strcpy(id_storage, id_temp);
    }
#line 2008 "y.tab.c"
    break;

  case 51:
#line 427 "compiler.y"
             {
        
    }
#line 2016 "y.tab.c"
    break;

  case 52:
#line 431 "compiler.y"
    { 
        if(strcmp((yyvsp[-2].s_val), "ADD_ASSIGN") == 0){
            fprintf(fp, "%cadd\n", (yyvsp[-4].s_val)[0]);
        }
        else if(strcmp((yyvsp[-2].s_val), "SUB_ASSIGN") == 0){
            fprintf(fp, "%csub\n", (yyvsp[-4].s_val)[0]);
        }
        else if(strcmp((yyvsp[-2].s_val), "MUL_ASSIGN") == 0){
            fprintf(fp, "%cmul\n", (yyvsp[-4].s_val)[0]);
        }
        else if(strcmp((yyvsp[-2].s_val), "DIV_ASSIGN") == 0){
            fprintf(fp, "%cdiv\n", (yyvsp[-4].s_val)[0]);
        }
        else if(strcmp((yyvsp[-2].s_val), "REM_ASSIGN") == 0){
            fprintf(fp, "%crem\n", (yyvsp[-4].s_val)[0]);
        }

        if(strcmp((yyvsp[-4].s_val), "str")==0){
            fprintf(fp, "astore %d\n", lookup_symbol_address(id_storage, I));
        }
        else if(strcmp((yyvsp[-4].s_val), "bool")==0){
            fprintf(fp, "istore %d\n", lookup_symbol_address(id_storage, I));
        }
        else{
            fprintf(fp, "%cstore %d\n", (yyvsp[-4].s_val)[0], lookup_symbol_address(id_storage,I));
        }
    }
#line 2048 "y.tab.c"
    break;

  case 53:
#line 461 "compiler.y"
    {
        if(loop){
            fprintf(fp, "goto L_loop_end\n");
        }
        fprintf(fp, "L_if_%d: \n\n", label_number-1);
        fprintf(fp, "; ------if_end------\n");
    }
#line 2060 "y.tab.c"
    break;

  case 54:
#line 469 "compiler.y"
    {
        fprintf(fp, "L_if_%d: \n", label_number-1);
        fprintf(fp, "; ------if_end------\n");
    }
#line 2069 "y.tab.c"
    break;

  case 56:
#line 475 "compiler.y"
    {
        fprintf(fp, "L_if_%d: \n", label_number-1);
        fprintf(fp, "; ------if_end------\n");
    }
#line 2078 "y.tab.c"
    break;

  case 58:
#line 483 "compiler.y"
    {
        is_if = true;
        fprintf(fp, "; ------here is if start------\n");
    }
#line 2087 "y.tab.c"
    break;

  case 60:
#line 491 "compiler.y"
    {
        printf("PRINT %s\n", (yyvsp[-2].s_val));
        if(strcmp((yyvsp[-2].s_val), "bool") == 0){
            fprintf(fp, "; ----here is print -----\n");
            fprintf(fp, "ifne L_%d\n", label_number++);
            fprintf(fp, "ldc \"false\"\n");
            fprintf(fp, "goto L_%d\n", label_number++);
            fprintf(fp, "L_%d:\n", label_number-2);
            fprintf(fp, "ldc \"true\"\n");
            fprintf(fp, "L_%d:\n", label_number-1);
            fprintf(fp, "; -----------------------\n");
        }
        fprintf(fp, "getstatic java/lang/System/out Ljava/io/PrintStream;\n");
        fprintf(fp, "swap\n");
        fprintf(fp, "invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V\n");

    }
#line 2109 "y.tab.c"
    break;

  case 61:
#line 509 "compiler.y"
    {
        printf("PRINT %s\n", (yyvsp[-1].s_val));
        if(strcmp((yyvsp[0].s_val), "bool") == 0){
            fprintf(fp, "; ----here is print -----\n");
            fprintf(fp, "ifne L_%d\n", label_number++);
            fprintf(fp, "ldc \"false\"\n");
            fprintf(fp, "goto L_%d\n", label_number++);
            fprintf(fp, "L_%d:\n", label_number-2);
            fprintf(fp, "ldc \"true\"\n");
            fprintf(fp, "L_%d:\n", label_number-1);
            fprintf(fp, "; -----------------------\n");
        }
        fprintf(fp, "getstatic java/lang/System/out Ljava/io/PrintStream;\n");
        fprintf(fp, "swap\n");
        fprintf(fp, "invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V\n");
    }
#line 2130 "y.tab.c"
    break;

  case 62:
#line 526 "compiler.y"
    {
        printf("PRINTLN %s\n", (yyvsp[-1].s_val));
        if(strcmp((yyvsp[-1].s_val), "bool") == 0){
            fprintf(fp, "; ----here is println -----\n");
            fprintf(fp, "ifne L_%d\n", label_number++);
            fprintf(fp, "ldc \"false\"\n");
            fprintf(fp, "goto L_%d\n", label_number++);
            fprintf(fp, "L_%d:\n", label_number-2);
            fprintf(fp, "ldc \"true\"\n");
            fprintf(fp, "L_%d:\n", label_number-1);
            fprintf(fp, "; -----------------------\n");
        }
        fprintf(fp, "getstatic java/lang/System/out Ljava/io/PrintStream;\n");
        fprintf(fp, "swap\n");
        if(strcmp((yyvsp[-1].s_val), "bool") == 0 || strcmp((yyvsp[-1].s_val), "str") == 0){
            fprintf(fp, "invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V\n");
        }
        else if(is_array){
            
            fprintf(fp, "invokevirtual java/io/PrintStream/println(I)V\n");
            is_array = false;
        }
        else{
            fprintf(fp, "invokevirtual java/io/PrintStream/println(%c)V\n", toupper((yyvsp[-1].s_val)[0]));
        }
        // fprintf(fp, "invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V\n");
    }
#line 2162 "y.tab.c"
    break;

  case 63:
#line 557 "compiler.y"
    {
        is_while = true;
        fprintf(fp, "L_while_%d: \n", label_number++);
    }
#line 2171 "y.tab.c"
    break;

  case 64:
#line 562 "compiler.y"
    {
        fprintf(fp, "; ------while_start------\n");
        // if(strstr($<s_val>2, "LES"))
        fprintf(fp, "iflt L_while_%d\n", label_number++);
        fprintf(fp, "goto L_while_%d\n", label_number++);
        fprintf(fp, "L_while_%d: \n", label_number-2);//true
    }
#line 2183 "y.tab.c"
    break;

  case 65:
#line 570 "compiler.y"
    {
        fprintf(fp, "goto L_while_%d\n", label_number-3);
        fprintf(fp, "L_while_%d: \n\n", label_number-1);
        fprintf(fp, "; ------while_end------\n");
    }
#line 2193 "y.tab.c"
    break;

  case 66:
#line 578 "compiler.y"
    {
        fprintf(fp, "iconst_0\n");
        fprintf(fp, "istore_2\n");
        fprintf(fp, "aload_1\n");
        fprintf(fp, "arraylength\n");
        fprintf(fp, "istore_3\n");

        fprintf(fp, "loop:\n");
        fprintf(fp, "iload_2\n");
        fprintf(fp, "iload_3\n");
        fprintf(fp, "if_icmpge end\n");
        fprintf(fp, "aload_1\n");
        fprintf(fp, "iload_2\n");
        fprintf(fp, "iaload\n");
        fprintf(fp, "dup\n");
        fprintf(fp, "istore 4\n");
        is_for = true;
    }
#line 2216 "y.tab.c"
    break;

  case 67:
#line 597 "compiler.y"
    {
        insert_symbol("i32", (yyvsp[-1].s_val), "-", Fo, false);
        lookup_symbol((yyvsp[-1].s_val), Fo); 
    }
#line 2225 "y.tab.c"
    break;

  case 68:
#line 602 "compiler.y"
    { 
        fprintf(fp, "iinc 2 1\n");
        fprintf(fp, "goto loop\n");
        fprintf(fp, "end:\n");
        dump_symbol() ;
        is_for = false;
    }
#line 2237 "y.tab.c"
    break;

  case 69:
#line 612 "compiler.y"
    {
        fprintf(fp, "L_loop:\n");
        loop = true;
    }
#line 2246 "y.tab.c"
    break;

  case 71:
#line 619 "compiler.y"
                    {(yyval.s_val) = (yyvsp[0].s_val);}
#line 2252 "y.tab.c"
    break;

  case 72:
#line 623 "compiler.y"
    {
        (yyval.s_val) = "bool";
        printf("LOR\n");
        fprintf(fp, "ior\n");
    }
#line 2262 "y.tab.c"
    break;

  case 73:
#line 628 "compiler.y"
                     { (yyval.s_val) = (yyvsp[0].s_val); }
#line 2268 "y.tab.c"
    break;

  case 74:
#line 632 "compiler.y"
    {
        (yyval.s_val) = "bool"; 
        printf("LAND\n");
        fprintf(fp, "iand\n");
    }
#line 2278 "y.tab.c"
    break;

  case 75:
#line 637 "compiler.y"
                     { (yyval.s_val) = (yyvsp[0].s_val); }
#line 2284 "y.tab.c"
    break;

  case 76:
#line 641 "compiler.y"
    {
        if(strcmp((yyvsp[-2].s_val), (yyvsp[0].s_val)) != 0){
            printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n", yylineno+1, (yyvsp[-1].s_val), (yyvsp[-2].s_val), (yyvsp[0].s_val));
        }
        else{
            if(strcmp((yyvsp[-2].s_val), "i32") == 0){
                
                fprintf(fp, "isub\n");
            }
                
            else if(strcmp((yyvsp[-2].s_val), "f32") == 0)
                fprintf(fp, "fcmpl\n");

            if(strcmp((yyvsp[-1].s_val), "GTR") == 0){
                fprintf(fp, "; --- here is greater than ---\n");
                fprintf(fp, "ifgt L%d\n", label_number++);
                fprintf(fp, "iconst_0\n");
                fprintf(fp, "goto L%d\n", label_number++);
                fprintf(fp, "L%d:\n", label_number-2);
                fprintf(fp, "iconst_1\n");
                fprintf(fp, "L%d:\n", label_number-1);
                fprintf(fp, "; ----------greater end------------\n");
            }
               
            else if(strcmp((yyvsp[-1].s_val), "LES") == 0){
                fprintf(fp, "; --- here is less than ---\n");
                fprintf(fp, "iflt L%d\n", label_number++);
                fprintf(fp, "iconst_0\n");
                fprintf(fp, "goto L%d\n", label_number++);
                fprintf(fp, "L%d:\n", label_number-2);
                fprintf(fp, "iconst_1\n");
                fprintf(fp, "L%d:\n", label_number-1);
                fprintf(fp, "; --------less end--------\n");
            }
            else if(strcmp((yyvsp[-1].s_val), "EQL") == 0){
                fprintf(fp, "; --- here is equal to ---\n");
                fprintf(fp, "ifeq L_if_%d\n", label_number++);
                fprintf(fp, "goto L_if_%d\n", label_number++);
                fprintf(fp, "L_if_%d: \n\n", label_number-2);//true
                if(is_if == false)
                    fprintf(fp, "\nL_if_%d: \n", label_number-1);
                else 
                    is_if = false;
                fprintf(fp, "; ---------equal end---------\n");
            }
        }
        (yyval.s_val) = "bool";
        printf("%s\n", (yyvsp[-1].s_val));
    }
#line 2338 "y.tab.c"
    break;

  case 77:
#line 690 "compiler.y"
                   { (yyval.s_val) = (yyvsp[0].s_val); }
#line 2344 "y.tab.c"
    break;

  case 78:
#line 694 "compiler.y"
    {
        
        printf("%s\n", (yyvsp[-1].s_val));
        (yyval.s_val) = (yyvsp[-2].s_val); 
        fprintf(fp, "%c%s\n", tolower((yyvsp[-2].s_val)[0]), (yyvsp[-1].s_val));
    }
#line 2355 "y.tab.c"
    break;

  case 79:
#line 701 "compiler.y"
    {
        printf("%s\n", (yyvsp[-1].s_val));
        (yyval.s_val) = (yyvsp[-2].s_val); 
        fprintf(fp, "%c%s\n", tolower((yyvsp[-2].s_val)[0]), (yyvsp[-1].s_val));
    }
#line 2365 "y.tab.c"
    break;

  case 80:
#line 706 "compiler.y"
                         { (yyval.s_val) = (yyvsp[0].s_val); }
#line 2371 "y.tab.c"
    break;

  case 81:
#line 711 "compiler.y"
    {
        (yyval.s_val) = (yyvsp[-2].s_val);
        printf("%s\n", (yyvsp[-1].s_val));
        fprintf(fp, "%c%s\n", tolower((yyvsp[-2].s_val)[0]), (yyvsp[-1].s_val));

    }
#line 2382 "y.tab.c"
    break;

  case 82:
#line 718 "compiler.y"
    {
        if(strcmp((yyvsp[-2].s_val), (yyvsp[0].s_val)) != 0){
            printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n", yylineno+1, (yyvsp[-1].s_val), (yyvsp[-2].s_val), (yyvsp[0].s_val));
        }
        (yyval.s_val) = (yyvsp[-2].s_val);
        printf("%s\n", (yyvsp[-1].s_val));
    }
#line 2394 "y.tab.c"
    break;

  case 83:
#line 725 "compiler.y"
                { (yyval.s_val) = (yyvsp[0].s_val); }
#line 2400 "y.tab.c"
    break;

  case 84:
#line 729 "compiler.y"
    { 
        (yyval.s_val) = (yyvsp[0].s_val); 
        printf("%s\n", (yyvsp[-1].s_val)); 
        if(strcmp((yyvsp[-1].s_val), "not") == 0) // if !a, a is 1 => ans = 0
        {
            fprintf(fp, "; here is do not\n");
            fprintf(fp, "iconst_1\n");// let x = 1
            if(strcmp((yyvsp[0].s_val), "true") == 0)
                fprintf(fp, "iconst_1\n");
            else if(strcmp((yyvsp[0].s_val), "false") == 0)
                fprintf(fp, "iconst_0\n");
            fprintf(fp, "ixor\n");// if a is 1, x xor a = 0; if a is 0, x xor a = 1
            fprintf(fp, "; --------------\n");
            (yyval.s_val) = "bool";
        }
        else if(strcmp((yyvsp[-1].s_val), "neg") == 0)
            fprintf(fp, "%cneg\n", (yyvsp[0].s_val)[0]);
    }
#line 2423 "y.tab.c"
    break;

  case 86:
#line 749 "compiler.y"
    { 
        (yyval.s_val) = (yyvsp[0].s_val); 
        if(strcmp((yyvsp[0].s_val), "true")==0){
            fprintf(fp, "iconst_1\n");
            (yyval.s_val) = "bool";
        }
        else if(strcmp((yyvsp[0].s_val), "false")==0){
            fprintf(fp, "iconst_0\n");
            (yyval.s_val) = "bool";
        }
        
    }
#line 2440 "y.tab.c"
    break;

  case 87:
#line 764 "compiler.y"
             { printf("DOTDOT\n"); }
#line 2446 "y.tab.c"
    break;

  case 89:
#line 765 "compiler.y"
              { printf("DOTDOT\n"); }
#line 2452 "y.tab.c"
    break;

  case 90:
#line 766 "compiler.y"
               { printf("DOTDOT\n"); }
#line 2458 "y.tab.c"
    break;

  case 93:
#line 771 "compiler.y"
              { (yyval.s_val) = (yyvsp[0].s_val); }
#line 2464 "y.tab.c"
    break;

  case 94:
#line 772 "compiler.y"
                 { casting = true; }
#line 2470 "y.tab.c"
    break;

  case 95:
#line 772 "compiler.y"
                                          { (yyval.s_val) = (yyvsp[0].s_val); }
#line 2476 "y.tab.c"
    break;

  case 96:
#line 773 "compiler.y"
         { (yyval.s_val) = lookup_symbol((yyvsp[0].s_val), I) ;}
#line 2482 "y.tab.c"
    break;

  case 97:
#line 774 "compiler.y"
                             { (yyval.s_val) = (yyvsp[-1].s_val); }
#line 2488 "y.tab.c"
    break;

  case 98:
#line 776 "compiler.y"
    { 
        fprintf(fp, "aload_1\n");
        fprintf(fp, "iconst_%d\n", (yyvsp[-1].i_val));
        fprintf(fp, "iaload\n");
        (yyval.s_val) = lookup_symbol((yyvsp[-3].s_val), I); 
        printf("INT_LIT %d\n", (yyvsp[-1].i_val));
        is_array = true;
    }
#line 2501 "y.tab.c"
    break;

  case 99:
#line 785 "compiler.y"
    {
        casting = true;
        lookup_symbol((yyvsp[-1].s_val), I);
    }
#line 2510 "y.tab.c"
    break;

  case 100:
#line 790 "compiler.y"
    {
        (yyval.s_val) = (yyvsp[0].s_val);
    }
#line 2518 "y.tab.c"
    break;

  case 101:
#line 794 "compiler.y"
    {
        lookup_symbol((yyvsp[-3].s_val), P); // parameter
        lookup_symbol((yyvsp[-1].s_val), P); // parameter
        has_return = true;
        return_type = 'b';
        lookup_symbol((yyvsp[-5].s_val), Fu); // function name
        fprintf(fp, "ifeq L_if_%d\n", label_number++);
        fprintf(fp, "goto L_if_%d\n", label_number++);
        fprintf(fp, "L_if_%d: \n", label_number-2);
    }
#line 2533 "y.tab.c"
    break;

  case 102:
#line 806 "compiler.y"
              { (yyval.s_val) = "i32"; printf("INT_LIT %d\n", (yyvsp[0].i_val)); 
        if(is_while){
            is_while = false;
            fprintf(fp, "ldc %d\n", (yyvsp[0].i_val));
        }
        else if(is_array){
            fprintf(fp, "dup\n");
            fprintf(fp, "iconst_%d\n", ptr_array++);
            fprintf(fp, "bipush %d\n", (yyvsp[0].i_val));
            fprintf(fp, "iastore\n");
        }
        else
            fprintf(fp, "ldc %d\n", (yyvsp[0].i_val));
    }
#line 2552 "y.tab.c"
    break;

  case 103:
#line 820 "compiler.y"
                { (yyval.s_val) = "f32"; printf("FLOAT_LIT %f\n", (yyvsp[0].f_val));fprintf(fp, "ldc %f\n", (yyvsp[0].f_val));}
#line 2558 "y.tab.c"
    break;

  case 104:
#line 821 "compiler.y"
                         { (yyval.s_val) = "str"; printf("STRING_LIT \"%s\"\n", (yyvsp[-1].s_val));fprintf(fp, "ldc \"%s\"\n", (yyvsp[-1].s_val));}
#line 2564 "y.tab.c"
    break;

  case 105:
#line 822 "compiler.y"
             { (yyval.s_val) = "str"; printf("STRING_LIT \"\"\n");fprintf(fp, "ldc \"\"\n");}
#line 2570 "y.tab.c"
    break;

  case 106:
#line 823 "compiler.y"
           { (yyval.s_val) = "true"; printf("bool TRUE\n");}
#line 2576 "y.tab.c"
    break;

  case 107:
#line 824 "compiler.y"
            { (yyval.s_val) = "false"; printf("bool FALSE\n");}
#line 2582 "y.tab.c"
    break;

  case 108:
#line 828 "compiler.y"
          {(yyval.s_val) = "ASSIGN";}
#line 2588 "y.tab.c"
    break;

  case 109:
#line 829 "compiler.y"
                 {(yyval.s_val) = "ADD_ASSIGN";}
#line 2594 "y.tab.c"
    break;

  case 110:
#line 830 "compiler.y"
                 {(yyval.s_val) = "SUB_ASSIGN";}
#line 2600 "y.tab.c"
    break;

  case 111:
#line 831 "compiler.y"
                 {(yyval.s_val) = "MUL_ASSIGN";}
#line 2606 "y.tab.c"
    break;

  case 112:
#line 832 "compiler.y"
                 {(yyval.s_val) = "DIV_ASSIGN";}
#line 2612 "y.tab.c"
    break;

  case 113:
#line 833 "compiler.y"
                 {(yyval.s_val) = "REM_ASSIGN";}
#line 2618 "y.tab.c"
    break;

  case 114:
#line 837 "compiler.y"
          { (yyval.s_val) = "EQL"; }
#line 2624 "y.tab.c"
    break;

  case 115:
#line 838 "compiler.y"
          { (yyval.s_val) = "NEQ"; }
#line 2630 "y.tab.c"
    break;

  case 116:
#line 839 "compiler.y"
          { (yyval.s_val) = "LSS"; }
#line 2636 "y.tab.c"
    break;

  case 117:
#line 840 "compiler.y"
          { (yyval.s_val) = "LEQ"; }
#line 2642 "y.tab.c"
    break;

  case 118:
#line 841 "compiler.y"
          { (yyval.s_val) = "GTR"; }
#line 2648 "y.tab.c"
    break;

  case 119:
#line 842 "compiler.y"
          { (yyval.s_val) = "GEQ"; }
#line 2654 "y.tab.c"
    break;

  case 120:
#line 846 "compiler.y"
          { (yyval.s_val) = "add"; }
#line 2660 "y.tab.c"
    break;

  case 121:
#line 847 "compiler.y"
          { (yyval.s_val) = "sub"; }
#line 2666 "y.tab.c"
    break;

  case 122:
#line 851 "compiler.y"
          { (yyval.s_val) = "mul"; }
#line 2672 "y.tab.c"
    break;

  case 123:
#line 852 "compiler.y"
          { (yyval.s_val) = "div"; }
#line 2678 "y.tab.c"
    break;

  case 124:
#line 853 "compiler.y"
          { (yyval.s_val) = "rem"; }
#line 2684 "y.tab.c"
    break;

  case 125:
#line 857 "compiler.y"
             { (yyval.s_val) = "ishl"; }
#line 2690 "y.tab.c"
    break;

  case 126:
#line 858 "compiler.y"
             { (yyval.s_val) = "iushr"; }
#line 2696 "y.tab.c"
    break;

  case 127:
#line 862 "compiler.y"
          { (yyval.s_val) = "pos"; }
#line 2702 "y.tab.c"
    break;

  case 128:
#line 863 "compiler.y"
          { (yyval.s_val) = "neg"; }
#line 2708 "y.tab.c"
    break;

  case 129:
#line 864 "compiler.y"
          { (yyval.s_val) = "not"; }
#line 2714 "y.tab.c"
    break;

  case 130:
#line 868 "compiler.y"
    { 
        (yyval.s_val) = "i32";
        if(casting){
            casting = false;
            printf("f2i\n");
            fprintf(fp, "f2i\n");
        } 
    }
#line 2727 "y.tab.c"
    break;

  case 131:
#line 877 "compiler.y"
    { 
        (yyval.s_val) = "f32";
        if(casting){
            casting = false;
            printf("i2f\n");
            fprintf(fp, "i2f\n");
        } 
    }
#line 2740 "y.tab.c"
    break;

  case 132:
#line 885 "compiler.y"
                            { (yyval.s_val) = "str"; }
#line 2746 "y.tab.c"
    break;

  case 133:
#line 886 "compiler.y"
                        { (yyval.s_val) = "bool"; }
#line 2752 "y.tab.c"
    break;


#line 2756 "y.tab.c"

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
#line 890 "compiler.y"


/* C code section */
int main(int argc, char *argv[])
{
    if (argc == 2) 
        yyin = fopen(argv[1], "r");
    else 
        yyin = stdin;

     if (!yyin) {
        printf("file %s doesn't exists or cannot be opened\n", argv[1]);
        exit(1);
    }

    /* hw3 */
    char *bytecode_filename = "hw3.j";
    fp = fopen(bytecode_filename, "w");
    fprintf(fp,".source hw3.j\n");
    fprintf(fp,".class public Main\n");
    fprintf(fp,".super java/lang/Object\n");

    create_symbol();
    yylineno = 0;
    yyparse();
    dump_symbol();

	printf("Total lines: %d\n", yylineno);
    fclose(fp);
    fclose(yyin);
     if (g_has_error) {
        remove(bytecode_filename);
    }
    yylex_destroy();
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

static int lookup_symbol_address(char *name, int mark_var) { // if mark_var = 0, function; else if mark_var = 1, parameter, else(id) is 2
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
                    
                else if(mark_var != Fo){// parameter and idZ
                    printf("IDENT (name=%s, address=%d)\n", s->name, s->addr);
                    return s-> addr;
                }
                else // foreach
                    return s-> addr;
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

static char *lookup_symbol(char *name, int mark_var) { // if mark_var = 0, function; else if mark_var = 1, parameter, else(id) is 2
    struct table *t = current_table;
    struct symbol *s = NULL;
    while(t!=NULL){
        s = t -> head;
        while(s!= NULL){
            if(strcmp(s-> name, name) == 0){
                if(mark_var == Fu)// function
                {
                    if(return_type == 'v')
                        fprintf(fp, "invokestatic Main/%s%s\n", s -> name, s -> func_sig);
                    else if(return_type == 'b')
                        fprintf(fp, "invokestatic Main/%s%s%c\n", s -> name, s -> func_sig, toupper(return_type));
                    /* printf("call: %s\n", s -> name); */
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
                    
                else if(mark_var != Fo ){// parameter or id
                    printf("IDENT (name=%s, address=%d)\n", s->name, s->addr);
                    if((strcmp(s->type, "i32") == 0 || strcmp(s->type, "bool") == 0)&& is_for == false)
                        fprintf(fp, "iload %d\n", s-> addr);
                    else if(strcmp(s->type, "f32") == 0)
                        fprintf(fp, "fload %d\n", s-> addr);
                    else if(strcmp(s->type, "str") == 0)
                        fprintf(fp, "aload %d\n", s-> addr);
                    strcpy(id_temp, s->name);
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
    g_has_error = true;
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
