%code requires{
  #include "include/ast.hpp"

  #include <cassert>

  extern const Expression *g_root; // A way of getting the AST out

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);
}

// Represents the value associated with any kind of
// AST node.
%union{
  const Expression *expr;
  double number;
  std::string *string;
}

%token T_TIMES T_DIVIDE T_PLUS T_MINUS T_LESSTHAN T_MORETHAN T_LESSEQUAL T_MOREEQUAL T_EQUAL T_NOTEQUAL T_BITWISE_AND T_BITWISE_XOR T_BITWISE_OR T_SEMICOLON T_CURLYLEFT T_CURLYRIGHT T_ASSIGN T_PLUSPLUS T_MINUSMINUS T_LOGICNOT T_MODULO T_BITWISE_LEFT T_BITWISE_RIGHT T_LOGICAND T_LOGICOR T_DIVSELF T_ADDSELF T_SUBSELF T_MULSELF T_COMMA T_FOR T_MODSELF T_LSLSELF T_LSRSELF T_ANDSELF 
%token T_LBRACKET T_RBRACKET
%token T_NUMBER T_NAME_STR TYPEDEF
%token T_IF T_ELSE T_WHILE
%token T_BOOL T_STRING
%token T_RETURN

%type <expr>  FUNCTION_DEFINITION MEGA_FUNCT_DEFINITION ARG_FUNCTION_DEFINITION EMPTY_FUNCTION_DEFINITION MEGA_STATEMENT STATEMENT_LIST STATEMENT ASSIGN_EXPR LOGIC_OR_EXPR LOGIC_AND_EXPR OR_EXPR XOR_EXPR AND_EXPR EQUALITY_EXPR COMPARISSON_EXPR SHIFT_EXPR ADD_EXPR TERM UNARY FACTOR VARIABLE DECLARATOR FOR_STATEMENT WHILE_STATEMENT IF_STATEMENT ARGUMENT_LIST VARIABLE_LIST FUNCTION_CALL
%type <number> T_NUMBER
%type <string> T_NAME_STR TYPEDEF
//T_LOG T_EXP T_SQRT FUNCTION_NAME

%start ROOT 

%%

/* The TODO notes a are just a guide, and are non-exhaustive.
   The expectation is that you do each one, then compile and test.
   Testing should be done using patterns that target the specific
   feature; the testbench is there to make sure that you haven't
   broken anything while you added it.
*/

ROOT : MEGA_FUNCT_DEFINITION { g_root = $1; } 

MEGA_FUNCT_DEFINITION : FUNCTION_DEFINITION                                             { $$ = $1; }
        |MEGA_FUNCT_DEFINITION FUNCTION_DEFINITION                                      { $$ = new StatementList($1, $2); }

FUNCTION_CALL : VARIABLE T_LBRACKET VARIABLE_LIST T_RBRACKET                                          { $$ = new Function_call($1, $3); }

FUNCTION_DEFINITION : EMPTY_FUNCTION_DEFINITION                                                         { $$ = $1; }
        |ARG_FUNCTION_DEFINITION                                                                        { $$ = $1; }
        

EMPTY_FUNCTION_DEFINITION : DECLARATOR T_LBRACKET T_RBRACKET MEGA_STATEMENT                         { $$ = new Function_declaration($1, $4); }

ARG_FUNCTION_DEFINITION : DECLARATOR T_LBRACKET ARGUMENT_LIST T_RBRACKET MEGA_STATEMENT             { $$ = new Arg_func_declaration($1, $3, $5); }
        | DECLARATOR T_LBRACKET ARGUMENT_LIST T_RBRACKET T_SEMICOLON                                    { $$ = new Empty_func_declaration($1, $3); }
        | DECLARATOR T_LBRACKET T_RBRACKET T_SEMICOLON                                                  { $$ = new Lamda_func_declaration($1); }
                                                     

MEGA_STATEMENT : T_CURLYLEFT STATEMENT_LIST T_CURLYRIGHT        { $$ = $2; }

STATEMENT_LIST : STATEMENT                                      { $$ = $1; }
        | STATEMENT_LIST STATEMENT                              { $$ = new StatementList($1, $2); }

STATEMENT : ASSIGN_EXPR T_SEMICOLON                     { $$ = new statement($1); }
        | T_RETURN LOGIC_OR_EXPR T_SEMICOLON            { $$ = new Return($2); }
        | IF_STATEMENT                                  { $$ = $1; } 
        | WHILE_STATEMENT                               { $$ = $1; }
        | FOR_STATEMENT                                           { $$ = $1; }    
        | DECLARATOR T_SEMICOLON                        { $$ = new statement($1); }
        //| VARIABLE T_PLUSPLUS  T_SEMICOLON                  { $$ = new PostIncrement($1); }
        //| VARIABLE T_MINUSMINUS   T_SEMICOLON                { $$ = new PostDecrement($1); }                             
       /* | T_IF T_LBRACKET LOGIC_OR_EXPR T_RBRACKET T_CURLYLEFT STATEMENT T_CURLYRIGHT                                                   { $$ = new IfStatement($3, $6, NULL);}
        | T_IF T_LBRACKET LOGIC_OR_EXPR T_RBRACKET T_CURLYLEFT STATEMENT T_CURLYRIGHT T_ELSE STATEMENT                                  { $$ = new IfStatement($3, $6, $10); }
        | T_IF T_LBRACKET LOGIC_OR_EXPR T_RBRACKET T_CURLYLEFT STATEMENT T_CURLYRIGHT T_ELSE T_CURLYLEFT STATEMENT T_CURLYRIGHT         { $$ = new IfStatement($3, $6, $10); }
        | T_WHILE T_LBRACKET LOGIC_OR_EXPR T_RBRACKET T_CURLYLEFT STATEMENT T_CURLYRIGHT                                                { $$ = new WhileLoop($3, $6); }
*/

FOR_STATEMENT : T_FOR T_LBRACKET ASSIGN_EXPR T_SEMICOLON LOGIC_OR_EXPR T_SEMICOLON ASSIGN_EXPR T_RBRACKET MEGA_STATEMENT  { $$ = new for_statement($3, $5, $7, $9); }
        | T_FOR T_LBRACKET ASSIGN_EXPR T_SEMICOLON LOGIC_OR_EXPR T_SEMICOLON ASSIGN_EXPR T_RBRACKET T_CURLYLEFT T_CURLYRIGHT  { $$ = new empty_for_statement($3, $5, $7); }

WHILE_STATEMENT : T_WHILE T_LBRACKET LOGIC_OR_EXPR T_RBRACKET MEGA_STATEMENT                    { $$ = new while_statement($3, $5); }
        | T_WHILE T_LBRACKET LOGIC_OR_EXPR T_RBRACKET T_CURLYLEFT T_CURLYRIGHT                   { $$ = new empty_while_statement($3); }

IF_STATEMENT : T_IF T_LBRACKET LOGIC_OR_EXPR T_RBRACKET MEGA_STATEMENT                          { $$ = new if_statement($3, $5); }
        | T_IF T_LBRACKET LOGIC_OR_EXPR T_RBRACKET MEGA_STATEMENT T_ELSE MEGA_STATEMENT         { $$ = new if_else_statement($3, $5, $7); }
        | T_IF T_LBRACKET LOGIC_OR_EXPR T_RBRACKET MEGA_STATEMENT T_ELSE IF_STATEMENT           { $$ = new if_else_statement($3, $5, $7); }

ASSIGN_EXPR : VARIABLE T_ASSIGN LOGIC_OR_EXPR                 { $$ = new VariableAssignment($1, $3); } 
        | DECLARATOR T_ASSIGN LOGIC_OR_EXPR                   { $$ = new DeclaratorAssignment($1, $3); }
        | VARIABLE  T_ADDSELF LOGIC_OR_EXPR                   { $$ = new SelfAddAssignment($1, $3); }
        | VARIABLE  T_SUBSELF LOGIC_OR_EXPR                   { $$ = new SelfSubAssignment($1, $3); }
        | VARIABLE  T_MULSELF LOGIC_OR_EXPR                   { $$ = new SelfMulAssignment($1, $3); }  
        | VARIABLE  T_SUBSELF LOGIC_OR_EXPR                   { $$ = new SelfDivAssignment($1, $3); } 
        | VARIABLE T_PLUSPLUS                                   { $$ = new PostIncrement($1); }
        | VARIABLE T_MINUSMINUS                                 { $$ = new PostDecrement($1); }


LOGIC_OR_EXPR : LOGIC_AND_EXPR                          { $$ = $1; }
        | LOGIC_OR_EXPR T_LOGICOR LOGIC_AND_EXPR        { $$ = new OrLogical($1, $3); }

LOGIC_AND_EXPR : OR_EXPR                                { $$ = $1; }
        | LOGIC_AND_EXPR T_LOGICAND OR_EXPR             { $$ = new AndLogical($1, $3); }

OR_EXPR : XOR_EXPR                                      { $$ = $1;}
        | OR_EXPR T_BITWISE_OR COMPARISSON_EXPR         { $$ = new BitwiseOrLogical($1, $3); }

XOR_EXPR : AND_EXPR                                     { $$ = $1; }
        | XOR_EXPR T_BITWISE_XOR AND_EXPR               { $$ = new BitwiseXorLogical($1, $3); }

AND_EXPR : EQUALITY_EXPR                                { $$ = $1; }
        | AND_EXPR T_BITWISE_AND EQUALITY_EXPR          { $$ = new BitwiseAndLogical($1, $3); }

EQUALITY_EXPR : COMPARISSON_EXPR                        { $$ = $1; }
        | EQUALITY_EXPR T_EQUAL COMPARISSON_EXPR        { $$ = new EqualComparator($1, $3); }
        | EQUALITY_EXPR T_NOTEQUAL COMPARISSON_EXPR     { $$ = new NotEqualComparator($1, $3); }

COMPARISSON_EXPR : SHIFT_EXPR                               { $$ = $1; }
        | COMPARISSON_EXPR T_LESSTHAN SHIFT_EXPR            { $$ = new LessThanComparator($1, $3); }
        | COMPARISSON_EXPR T_LESSEQUAL SHIFT_EXPR           { $$ = new LessEqualComparator($1, $3); }
        | COMPARISSON_EXPR T_MOREEQUAL SHIFT_EXPR           { $$ = new MoreEqualComparator($1, $3); }
        | COMPARISSON_EXPR T_MORETHAN SHIFT_EXPR            { $$ = new MoreThanComparator($1, $3); }

SHIFT_EXPR : ADD_EXPR                               { $$ =  $1; }
        | SHIFT_EXPR T_BITWISE_LEFT ADD_EXPR        { $$ = new BitwiseLeft($1, $3); }
        | SHIFT_EXPR T_BITWISE_RIGHT ADD_EXPR       { $$ = new BitwiseRight($1, $3); }


ADD_EXPR : TERM                             { $$ = $1; }
        | ADD_EXPR T_PLUS TERM              { $$ = new AddOperator($1, $3); } 
        | ADD_EXPR T_MINUS TERM             { $$ = new SubOperator($1, $3); }

/* TODO-4 : Add support (x * 6) and (z / 11). */
TERM : UNARY                            { $$ = $1; }
        | TERM T_TIMES UNARY            { $$ = new MulOperator($1, $3); }
        | TERM T_DIVIDE UNARY           { $$ = new DivOperator($1, $3); }
        | UNARY T_MODULO FACTOR         { $$ = new Modulo($1, $3); }

/*  TODO-5 : Add support for (- 5) and (- x). You'll need to add production rules for the unary minus operator and create a NegOperator. */
UNARY : FACTOR                          { $$ = $1; }
        | T_MINUS FACTOR                { $$ = new NegOperator($2); }
        | T_PLUSPLUS VARIABLE           { $$ = new PreIncrement($2); }
        | T_MINUSMINUS VARIABLE         { $$ = new PreDecrement($2); }
        //| T_LOGICNOT LOGIC_OR_EXPR      { $$ = new LogicNot($2); }
        

/* TODO-2 : Add a rule for variable, base on the pattern of number. */
FACTOR : VARIABLE                                 { $$ = $1; }
        | T_NUMBER                                { $$ = new Number( $1 ); }
        | T_LBRACKET ADD_EXPR T_RBRACKET          { $$ = $2; }
        | FUNCTION_CALL                           { $$ = $1;}
        //| VARIABLE T_PLUSPLUS                     { $$ = new PostIncrement($1); }
        //| VARIABLE T_MINUSMINUS                   { $$ = new PostDecrement($1); }
/* TODO-6 : Add support log(x), by modifying the rule for FACTOR. */

/* TODO-7 : Extend support to other functions. Requires modifications here, and to FACTOR. */

VARIABLE_LIST : LOGIC_OR_EXPR                   { $$ = $1; }
        | LOGIC_OR_EXPR T_COMMA LOGIC_OR_EXPR       { $$ = new ParameterList($1, $3); }
        | LOGIC_OR_EXPR T_COMMA LOGIC_OR_EXPR T_COMMA LOGIC_OR_EXPR     { $$ = new ParameterList3($1, $3, $5); }
        | LOGIC_OR_EXPR T_COMMA LOGIC_OR_EXPR T_COMMA LOGIC_OR_EXPR T_COMMA LOGIC_OR_EXPR     { $$ = new ParameterList4($1, $3, $5, $7); }
ARGUMENT_LIST : DECLARATOR                     { $$ = $1; }
        | ARGUMENT_LIST T_COMMA DECLARATOR    { $$ = new ArgumentList($1, $3); }   
                   

DECLARATOR : TYPEDEF  { $$ = new IntDeclarator( *$1); }
        

VARIABLE : T_NAME_STR    { $$ = new Variable( *$1 ); }      

%%

const Expression *g_root; // Definition of variable (to match declaration earlier)

const Expression *parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
}