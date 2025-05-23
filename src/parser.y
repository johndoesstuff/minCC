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
	float fval;
	struct ASTNode* node;
	struct Type* type;
	struct Argument* argument;
	struct Parameter* parameter;
}

%token <ival> NUMBER
%token <sval> IDENTIFIER
%token <cval> CHARACTER
%token <fval> FLOAT
%token RETURN
%token WHILE
%token IF
%token ELSE
%token TRUE
%token FALSE
%token LOGIC_AND
%token LOGIC_OR
%token <sval> COMPARE
%token <sval> BASE_TYPE
%token <sval> STRING
%type <ival> none_or_more_pointers
%type <type> type
%type <node> else_clause declare rvalue mag term factor expr statement input logic_and logic_or
%type <argument> argument_list
%type <parameter> parameter_list

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
	| WHILE '(' expr ')' '{' { sem_enter_scope(); } input '}'	{ $$ = make_while($3, $7, @$); sem_exit_scope(); }
	| IF '(' expr ')' '{' { sem_enter_scope(); } input '}' else_clause	{ $$ = make_if($3, $7, $9, @$); sem_exit_scope(); }
	| type IDENTIFIER { sem_enter_scope(); } '(' argument_list ')' '{' input '}'	{ sem_exit_scope(); $$ = make_function($1, $2, $5, $8, @$); }
;

else_clause:
			{ $$ = NULL; }
	| ELSE '{' { sem_enter_scope(); } input '}'	{ $$ = $4; sem_exit_scope(); }
	| ELSE IF '(' expr ')' '{' { sem_enter_scope(); } input '}' else_clause	{ $$ = make_if($4, $8, $10, @$); sem_exit_scope(); }
;

declare:
	type IDENTIFIER '=' expr	{ $$ = make_declare($1, $2, $4, @$); }
	| type IDENTIFIER		{ $$ = make_declare($1, $2, NULL, @$); }
;

argument_list:
	{ $$ = NULL; }
	| type IDENTIFIER		{ $$ = make_argument($1, $2, @$); }
	| argument_list ',' type IDENTIFIER	{ append_argument($1, make_argument($3, $4, @$), @$); $$ = $1; }
;

parameter_list:
	{ $$ = NULL; }
	| expr				{ $$ = make_parameter($1, @$); }
	| parameter_list ',' expr	{ append_parameter($1, make_parameter($3, @$), @$); $$ = $1; }

type:
	BASE_TYPE none_or_more_pointers	{ $$ = make_type(get_base_type($1), $2); }
;

none_or_more_pointers:
	{ $$ = 0; }
	| none_or_more_pointers '*'	{ $$ = $1 + 1; }
;

expr:
	IDENTIFIER '=' expr	{ $$ = make_assign($1, $3, @$); }
        | logic_or              { $$ = $1; }
;

logic_or:
        logic_or LOGIC_OR logic_and   { $$ = make_binary("||", $1, $3, @$); }
        | logic_and              { $$ = $1; }
;

logic_and:
        logic_and LOGIC_AND rvalue    { $$ = make_binary("&&", $1, $3, @$); }
        | rvalue                 { $$ = $1; }
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
	| IDENTIFIER '(' parameter_list ')'	{ $$ = make_function_call($1, $3, @$); }
	| IDENTIFIER	{ $$ = make_identifier($1, @$); }
	| NUMBER	{ $$ = make_number($1, @$); }
	| CHARACTER	{ $$ = make_character($1, @$); }
	| STRING	{ $$ = make_string($1, @$); }
	| FLOAT		{ $$ = make_float($1, @$); }
;

%%


int yyerror(YYLTYPE* yylloc, const char *msg) {
	fprintf(stderr, "Parse error at line %d, column %d: %s\n",
		yylloc->first_line, yylloc->first_column, msg);
	exit(1);
	return 1;
}
