%{
#include "parser.tab.h"
%}

%%

[0-9]+      { yylval.ival = atoi(yytext); return NUMBER; }
[+]         { return '+'; }
[ \t\n]+    ; // ignore whitespace
.           { return yytext[0]; }

%%
