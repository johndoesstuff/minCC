%{
#include "parser.tab.h"
%}

%%

[0-9]+      { yylval.ival = atoi(yytext); return NUMBER; }
"+"         { return '+'; }
"-"         { return '-'; }
"*"         { return '*'; }
"/"         { return '/'; }
[ \t\n]+    ; // ignore whitespace
.           { return yytext[0]; }

%%
