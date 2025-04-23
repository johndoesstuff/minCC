%{
#include "parser.tab.h"  // Needed for yylval and token types
#include <stdlib.h>      // For atoi
%}

%%

[0-9]+      {
                yylval.ival = atoi(yytext);  // Must come BEFORE return
                return NUMBER;
            }

[ \t\n]+    { /* skip whitespace */ }

.           { return yytext[0]; }

%%

int yywrap() { return 1; }

