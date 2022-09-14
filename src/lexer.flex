%option noyywrap

%{
// Avoid error "error: `fileno' was not declared in this scope"
extern "C" int fileno(FILE *stream);

#include "parser.tab.hpp"
%}


%%
[%]             { return T_MODULO; }
[*]             { return T_TIMES; }
[+]             { return T_PLUS; }
[-]             { return T_MINUS; }
[/]             { return T_DIVIDE; }

[;]             { return T_SEMICOLON; }

"="            { return T_ASSIGN; }
"||"            { return T_LOGICOR; }
"&&"            { return T_LOGICAND; }
"!"             { return T_LOGICNOT; }
"|"             { return T_BITWISE_OR; }
"&"             { return T_BITWISE_AND; }
"^"             { return T_BITWISE_XOR; }
"!="            { return T_NOTEQUAL; }
"=="            { return T_EQUAL; }
"<"             { return T_LESSTHAN; }
">"             { return T_MORETHAN; }
">="            { return T_MOREEQUAL; }
"<="            { return T_LESSEQUAL; }
"<<"            { return T_BITWISE_LEFT; }
">>"            { return T_BITWISE_RIGHT; }
"/="            { return T_DIVSELF; }
"+="            { return T_ADDSELF; }
"-="            { return T_SUBSELF; }
"*="            { return T_MULSELF; }
"%="            { return T_MODSELF; }
"<<="           { return T_LSLSELF; }
">>="           { return T_LSRSELF; }
"&="            { return T_ANDSELF; }



"++"            { return T_PLUSPLUS; }
"--"            { return T_MINUSMINUS; }

[(]             { return T_LBRACKET; }
[)]             { return T_RBRACKET; }
[}]             { return T_CURLYRIGHT; }
[{]             { return T_CURLYLEFT; }

[,]             { return T_COMMA; }

"return"        { return T_RETURN; }

"if"            { return T_IF; }
"else"          { return T_ELSE; }
"while"         { return T_WHILE; }
"for"           { return T_FOR; }


"int"(" ")*[a-z]+   { yylval.string=new std::string(yytext); return TYPEDEF; }
[0-9]+([.][0-9]*)?  { yylval.number=strtod(yytext, 0); return T_NUMBER; }
[a-z]+          { yylval.string=new std::string(yytext); return T_NAME_STR; }

[ \t\r\n]+		{;}

.               { fprintf(stderr, "Invalid token\n"); exit(1); }
%%

void yyerror (char const *s)
{
  fprintf (stderr, "Parse error : %s\n", s);
  exit(1);
}