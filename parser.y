%{
#include <stdio.h>
#include "ast.h"

ASTNode* root;
%}

%union {
	int ival;
	struct ASTNode* node;
}

%token <ival> NUMBER
%type <node> mag term

%%

input:
	mag		{ root = $1; }
;

mag:
	mag '+' term	{ $$ = make_binary('+', $1, $3); }
	| mag '-' term	{ $$ = make_binary('-', $1, $3); }
	| term		{ $$ = $1; }
;

term:
	term '*' term	{ $$ = make_binary('*', $1, $3); }
	| term '/' term	{ $$ = make_binary('/', $1, $3); }
	| NUMBER	{ $$ = make_number($1); }
;

%%

int yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	return 1;
}
