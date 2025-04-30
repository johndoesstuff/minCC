%{
#include "parser.tab.h"
#include <string.h>
%}

%%

[0-9]+		{ yylval.ival = atoi(yytext); return NUMBER; }
"return"	{ return RETURN; }
"while"		{ return WHILE; }
"if"		{ return IF; }
"else"		{ return ELSE; }
"true"		{ return TRUE; }
"false"		{ return FALSE; }
("int"|"bool")	{ yylval.sval = strdup(yytext); return BASE_TYPE; }
("=="|"<"|">"|"<="|">="|"!=")		{ yylval.sval = strdup(yytext); return COMPARE; }
[a-zA-Z_][a-zA-Z0-9_]*	{ yylval.sval = strdup(yytext); return IDENTIFIER; }
"+"		{ return '+'; }
"-"		{ return '-'; }
"*"		{ return '*'; }
"/"		{ return '/'; }
\/\/.*		;
[ \t\n]+	; // ignore whitespace
.		{ return yytext[0]; }

%%
