%{
#include "parser.tab.h"
#include <stdlib.h>
#include <string.h>
%}

%%

[0-9]+ { //number
	yylval.ival = atoi(yytext);
	return NUMBER;
}

"unsigned"|"signed" { yylval.sval = strdup(yytext); return TYPE_SIGNAGE; }

"int"|"char"|"long"|"float"|"double" { yylval.sval = strdup(yytext); return TYPE_SIZE; }

"*"* { yylval.sval = strdup(yytext); return POINTER_CHAIN; }

[a-zA-Z_][a-zA-Z0-9_]* { //identifier
	yylval.sval = strdup(yytext);
	return IDENTIFIER;
}

[ \t\n]+ {} //whitespace


"=" { yylval.sval = strdup(yytext); return ASSIGNMENT_OPERATOR; } //assignment operators
"*=" { yylval.sval = strdup(yytext); return ASSIGNMENT_OPERATOR; }
"/=" { yylval.sval = strdup(yytext); return ASSIGNMENT_OPERATOR; }
"%=" { yylval.sval = strdup(yytext); return ASSIGNMENT_OPERATOR; }
"+=" { yylval.sval = strdup(yytext); return ASSIGNMENT_OPERATOR; }
"-=" { yylval.sval = strdup(yytext); return ASSIGNMENT_OPERATOR; }
"<<=" { yylval.sval = strdup(yytext); return ASSIGNMENT_OPERATOR; }
">>=" { yylval.sval = strdup(yytext); return ASSIGNMENT_OPERATOR; }
"&=" { yylval.sval = strdup(yytext); return ASSIGNMENT_OPERATOR; }
"^=" { yylval.sval = strdup(yytext); return ASSIGNMENT_OPERATOR; }
"|=" { yylval.sval = strdup(yytext); return ASSIGNMENT_OPERATOR; }

. { return yytext[0]; }

%%

int yywrap() { return 1; }

