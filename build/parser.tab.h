/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_BUILD_PARSER_TAB_H_INCLUDED
# define YY_YY_BUILD_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    NUMBER = 258,                  /* NUMBER  */
    IDENTIFIER = 259,              /* IDENTIFIER  */
    CHARACTER = 260,               /* CHARACTER  */
    FLOAT = 261,                   /* FLOAT  */
    RETURN = 262,                  /* RETURN  */
    WHILE = 263,                   /* WHILE  */
    IF = 264,                      /* IF  */
    ELSE = 265,                    /* ELSE  */
    TRUE = 266,                    /* TRUE  */
    FALSE = 267,                   /* FALSE  */
    LOGIC_AND = 268,               /* LOGIC_AND  */
    LOGIC_OR = 269,                /* LOGIC_OR  */
    ASSIGNMENT_ADD_EQUALS = 270,   /* ASSIGNMENT_ADD_EQUALS  */
    ASSIGNMENT_SUB_EQUALS = 271,   /* ASSIGNMENT_SUB_EQUALS  */
    ASSIGNMENT_MUL_EQUALS = 272,   /* ASSIGNMENT_MUL_EQUALS  */
    ASSIGNMENT_DIV_EQUALS = 273,   /* ASSIGNMENT_DIV_EQUALS  */
    INCREMENT = 274,               /* INCREMENT  */
    DECREMENT = 275,               /* DECREMENT  */
    COMPARE = 276,                 /* COMPARE  */
    BASE_TYPE = 277,               /* BASE_TYPE  */
    STRING = 278                   /* STRING  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 10 "src/parser.y"

	int ival;
	char* sval;
	char cval;
	float fval;
	struct ASTNode* node;
	struct Type* type;
	struct Argument* argument;
	struct Parameter* parameter;

#line 98 "build/parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif




int yyparse (void);


#endif /* !YY_YY_BUILD_PARSER_TAB_H_INCLUDED  */
