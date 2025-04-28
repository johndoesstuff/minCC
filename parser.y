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
%token RETURN
%token <sval> COMPARE
%type <node> rvalue mag term factor expr statement

%left '+' '-'
%left '*' '/'
%nonassoc RETURN

%%

input:
			{ root = make_program(); }
	| input statement	{ append_statement(root, $2); }
;

statement:
	expr ';'	{ $$ = $1; }
	| RETURN expr ';'	{ $$ = make_return($2); }
;

expr:
	IDENTIFIER '=' expr	{ $$ = make_assign($1, $3); }
	| rvalue		{ $$ = $1; }
;

rvalue:
	rvalue COMPARE mag	{ $$ = make_binary($2, $1, $3); }
	| mag			{ $$ = $1; }
;

mag:
	mag '+' term	{ $$ = make_binary("+", $1, $3); }
	| mag '-' term	{ $$ = make_binary("-", $1, $3); }
	| term		{ $$ = $1; }
;

term:
	term '*' factor	{ $$ = make_binary("*", $1, $3); }
	| term '/' factor	{ $$ = make_binary("/", $1, $3); }
	| factor	{ $$ = $1; }
;

factor:
	'(' rvalue ')'	{ $$ = $2; }
	| '-' factor	{ $$ = make_unary("-", $2); }
	| IDENTIFIER	{ $$ = make_identifier($1); }
	| NUMBER	{ $$ = make_number($1); }
;

%%

int yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	return 1;
}
