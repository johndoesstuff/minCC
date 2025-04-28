%{
#include "parser.tab.h"
#include <string.h>
%}

%%

[0-9]+		{ yylval.ival = atoi(yytext); return NUMBER; }
"return"	{ return RETURN; }
"true"		{ return TRUE; }
"false"		{ return FALSE; }
("=="|"<"|">"|"<="|">="|"!=")		{ yylval.sval = strdup(yytext); return COMPARE; }
[a-zA-Z_][a-zA-Z0-9_]*	{ yylval.sval = strdup(yytext); return IDENTIFIER; }
"+"		{ return '+'; }
"-"		{ return '-'; }
"*"		{ return '*'; }
"/"		{ return '/'; }
[ \t\n]+	; // ignore whitespace
.		{ return yytext[0]; }

%%
