/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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

#line 147 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
