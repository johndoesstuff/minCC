%{
#include <stdio.h>
#include "ast.h"

ASTNode* root;
%}

%union {
	int ival;
	char* sval;
	struct ASTNode* node;
}

%token <ival> NUMBER
%token <sval> IDENTIFIER
%type <node> mag term factor expr

%%

input:
	expr		{ root = $1; }
;

expr:
	IDENTIFIER '=' expr	{ $$ = make_assign($1, $3); }
	| mag		{ $$ = $1; }
;

mag:
	mag '+' term	{ $$ = make_binary('+', $1, $3); }
	| mag '-' term	{ $$ = make_binary('-', $1, $3); }
	| term		{ $$ = $1; }
;

term:
	term '*' factor	{ $$ = make_binary('*', $1, $3); }
	| term '/' factor	{ $$ = make_binary('/', $1, $3); }
	| factor	{ $$ = $1; }
;

factor:
	'(' mag ')'	{ $$ = $2; }
	| '-' factor	{ $$ = make_unary('-', $2); }
	| NUMBER	{ $$ = make_number($1); }
;

%%

int yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	return 1;
}
