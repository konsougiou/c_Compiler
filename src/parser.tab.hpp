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

#ifndef YY_YY_SRC_PARSER_TAB_HPP_INCLUDED
# define YY_YY_SRC_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "src/parser.y"

  #include "include/ast.hpp"

  #include <cassert>

  extern const Expression *g_root; // A way of getting the AST out

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);

#line 62 "src/parser.tab.hpp"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_TIMES = 258,
    T_DIVIDE = 259,
    T_PLUS = 260,
    T_MINUS = 261,
    T_LESSTHAN = 262,
    T_MORETHAN = 263,
    T_LESSEQUAL = 264,
    T_MOREEQUAL = 265,
    T_EQUAL = 266,
    T_NOTEQUAL = 267,
    T_BITWISE_AND = 268,
    T_BITWISE_XOR = 269,
    T_BITWISE_OR = 270,
    T_SEMICOLON = 271,
    T_CURLYLEFT = 272,
    T_CURLYRIGHT = 273,
    T_ASSIGN = 274,
    T_PLUSPLUS = 275,
    T_MINUSMINUS = 276,
    T_LOGICNOT = 277,
    T_MODULO = 278,
    T_BITWISE_LEFT = 279,
    T_BITWISE_RIGHT = 280,
    T_LOGICAND = 281,
    T_LOGICOR = 282,
    T_DIVSELF = 283,
    T_ADDSELF = 284,
    T_SUBSELF = 285,
    T_MULSELF = 286,
    T_COMMA = 287,
    T_FOR = 288,
    T_MODSELF = 289,
    T_LSLSELF = 290,
    T_LSRSELF = 291,
    T_ANDSELF = 292,
    T_LBRACKET = 293,
    T_RBRACKET = 294,
    T_NUMBER = 295,
    T_NAME_STR = 296,
    TYPEDEF = 297,
    T_IF = 298,
    T_ELSE = 299,
    T_WHILE = 300,
    T_BOOL = 301,
    T_STRING = 302,
    T_RETURN = 303
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 17 "src/parser.y"

  const Expression *expr;
  double number;
  std::string *string;

#line 128 "src/parser.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_PARSER_TAB_HPP_INCLUDED  */
