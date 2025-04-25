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
%type <node> expr

%%

input:
	expr { root = $1; }
;

expr:
	NUMBER                { $$ = make_number($1); }
	| expr '+' expr         { $$ = make_binary('+', $1, $3); }
	| expr '-' expr         { $$ = make_binary('-', $1, $3); }
;

%%

int yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	return 1;
}
