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
%token WHILE
%token IF
%token ELSE
%token TRUE
%token FALSE
%token <sval> COMPARE
%token <sval> TYPE
%type <node> else_clause declare rvalue mag term factor expr statement input

%left '+' '-'
%left '*' '/'
%nonassoc RETURN

%%

program:
	input	{ root = $1; }
;

input:
			{ $$ = make_program(); }
	| input statement	{ append_statement($1, $2); $$ = $1; }
;

statement:
	declare ';'	{ $$ = $1; }
	| expr ';'	{ $$ = $1; }
	| RETURN expr ';'	{ $$ = make_return($2); }
	| WHILE '(' expr ')' '{' input '}'	{ $$ = make_while($3, $6); }
	| IF '(' expr ')' '{' input '}' else_clause	{ $$ = make_if($3, $6, $8); }
;

else_clause:
			{ $$ = NULL; }
	| ELSE '{' input '}'	{ $$ = $3; }
	| ELSE IF '(' expr ')' '{' input '}' else_clause	{ $$ = make_if($4, $7, $9); }
;

declare:
	TYPE IDENTIFIER '=' expr	{ $$ = make_declare($1, $2, $4); }
	| TYPE IDENTIFIER		{ $$ = make_declare($1, $2, NULL); }
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
	| TRUE			{ $$ = make_true(); }
	| FALSE			{ $$ = make_false(); }
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
