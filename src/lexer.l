%{
#include "parser.tab.h"
#include <string.h>


int yycolumn = 1;

#define YY_DECL int yylex(YYSTYPE *yylval, YYLTYPE *yylloc)

#define YY_USER_ACTION                                  \
	yylloc->first_line = yylloc->last_line = yylineno;  \
	yylloc->first_column = yycolumn;                    \
	yycolumn += yyleng;                                 \
	yylloc->last_column = yycolumn;                     \

YY_DECL;
%}

%option yylineno

%%

[0-9]+		{ yylval->ival = atoi(yytext); return NUMBER; }
'[^']'		{ yylval->cval = yytext[1]; return CHARACTER; }
\"[^"]*\"		{ yytext[yyleng - 1] = '\0'; yylval->sval = strdup(yytext + 1); return STRING; }
"return"	{ return RETURN; }
"while"		{ return WHILE; }
"if"		{ return IF; }
"else"		{ return ELSE; }
"true"		{ return TRUE; }
"false"		{ return FALSE; }
"="		{ return '='; }
";"		{ return ';'; }
"("		{ return '('; }
")"		{ return ')'; }
"{"		{ return '{'; }
"}"		{ return '}'; }
("int"|"bool"|"char")	{ yylval->sval = strdup(yytext); return BASE_TYPE; }
("=="|"<"|">"|"<="|">="|"!=")		{ yylval->sval = strdup(yytext); return COMPARE; }
[a-zA-Z_][a-zA-Z0-9_]*	{ yylval->sval = strdup(yytext); return IDENTIFIER; }
"+"		{ return '+'; }
"-"		{ return '-'; }
"*"		{ return '*'; }
"/"		{ return '/'; }
"%"		{ return '%'; }
\/\/.*		;
\n      { yycolumn = 1; yylineno++; }
[ \t]+	; // ignore whitespace
.		{ fprintf(stderr, "Invalid character: %s at %d:%d\n", yytext, yylineno, yycolumn); }

%%
