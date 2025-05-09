%{
#include <stdio.h>
#include <stdlib.h>
#include "../inc/ast.h"
#include "../inc/types.h"

ASTNode* root;
%}

%union {
	int ival;
	char* sval;
	char cval;
	struct ASTNode* node;
	struct Type* type;
}

%token <ival> NUMBER
%token <sval> IDENTIFIER
%token <cval> CHARACTER
%token RETURN
%token WHILE
%token IF
%token ELSE
%token TRUE
%token FALSE
%token <sval> COMPARE
%token <sval> BASE_TYPE
%type <ival> none_or_more_pointers
%type <type> type
%type <node> else_clause declare rvalue mag term factor expr statement input

%left '+' '-'
%left '*' '/'
%nonassoc RETURN
%define parse.error verbose
%define api.pure full
%locations

%%

program:
	input	{ root = $1; }
;

input:
			{ $$ = make_program(@$); }
	| input statement	{ append_statement($1, $2); $$ = $1; }
;

statement:
	declare ';'	{ $$ = $1; }
	| expr ';'	{ $$ = $1; }
	| RETURN expr ';'	{ $$ = make_return($2, @$); }
	| WHILE '(' expr ')' '{' input '}'	{ $$ = make_while($3, $6, @$); }
	| IF '(' expr ')' '{' input '}' else_clause	{ $$ = make_if($3, $6, $8, @$); }
;

else_clause:
			{ $$ = NULL; }
	| ELSE '{' input '}'	{ $$ = $3; }
	| ELSE IF '(' expr ')' '{' input '}' else_clause	{ $$ = make_if($4, $7, $9, @$); }
;

declare:
	type IDENTIFIER '=' expr	{ $$ = make_declare($1, $2, $4, @$); }
	| type IDENTIFIER		{ $$ = make_declare($1, $2, NULL, @$); }
;

type:
	BASE_TYPE none_or_more_pointers	{ $$ = make_type(get_base_type($1), $2); }
;

none_or_more_pointers:
	{ $$ = 0; }
	| none_or_more_pointers '*'	{ $$ = $1 + 1; }
;

expr:
	IDENTIFIER '=' expr	{ $$ = make_assign($1, $3, @$); }
	| rvalue		{ $$ = $1; }
;

rvalue:
	rvalue COMPARE mag	{ $$ = make_binary($2, $1, $3, @$); }
	| mag			{ $$ = $1; }
;

mag:
	mag '+' term	{ $$ = make_binary("+", $1, $3, @$); }
	| mag '-' term	{ $$ = make_binary("-", $1, $3, @$); }
	| TRUE			{ $$ = make_true(@$); }
	| FALSE			{ $$ = make_false(@$); }
	| term		{ $$ = $1; }
;

term:
	term '*' factor	{ $$ = make_binary("*", $1, $3, @$); }
	| term '/' factor	{ $$ = make_binary("/", $1, $3, @$); }
	| term '%' factor	{ $$ = make_binary("%", $1, $3, @$); }
	| factor	{ $$ = $1; }
;

factor:
	'(' rvalue ')'	{ $$ = $2; }
	| '-' factor	{ $$ = make_unary("-", $2, @$); }
	| IDENTIFIER	{ $$ = make_identifier($1, @$); }
	| NUMBER	{ $$ = make_number($1, @$); }
	| CHARACTER	{ $$ = make_character($1, @$); }
;

%%


int yyerror(YYLTYPE* yylloc, const char *msg) {
	fprintf(stderr, "Parse error at line %d, column %d: %s\n",
		yylloc->first_line, yylloc->first_column, msg);
	exit(1);
	return 1;
}
