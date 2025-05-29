%{
#include <stdio.h>
#include <stdlib.h>
#include "../inc/ast.h"
#include "../inc/types.h"

ASTNode* root;
%}

%union {
	int ival;
	long lval;
	char* sval;
	char cval;
	float fval;
	double dval;
	struct ASTNode* node;
	struct Type* type;
	struct Argument* argument;
	struct Parameter* parameter;
}

%token <ival> INT
%token <sval> IDENTIFIER
%token <cval> CHARACTER
%token <fval> FLOAT
%token <dval> DOUBLE
%token <lval> LONG
%token RETURN
%token WHILE
%token FOR
%token IF
%token ELSE
%token TRUE
%token FALSE
%token LOGIC_AND
%token LOGIC_OR
%token ASSIGNMENT_ADD_EQUALS
%token ASSIGNMENT_SUB_EQUALS
%token ASSIGNMENT_MUL_EQUALS
%token ASSIGNMENT_DIV_EQUALS
%token INCREMENT
%token DECREMENT
%token NULLTOK
%token <sval> COMPARE
%token <sval> BASE_TYPE
%token <sval> STRING
%type <ival> none_or_more_pointers
%type <type> type
%type <node> else_clause declare rvalue mag term factor expr statement input logic_and logic_or block expr_opt declare_or_expr_opt postfix primary
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
	| WHILE '(' expr ')' block	{ $$ = make_while($3, $5, @$); }
	| FOR '(' { sem_enter_scope(); } declare_or_expr_opt ';' expr_opt ';' expr_opt ')' block	{
		$$ = make_program(@$);
		append_statement($$, $4);
		ASTNode* while_body = $10;
		append_statement(while_body, $8);
		append_statement($$, make_while($6, while_body, @$));
		sem_exit_scope(); }
	| IF '(' expr ')' block else_clause	{ $$ = make_if($3, $5, $6, @$); }
	| type IDENTIFIER { sem_enter_scope(); } '(' argument_list ')' block	{ sem_exit_scope(); $$ = make_function($1, $2, $5, $7, @$); }
	| ';'		{ $$ = make_empty(@$); }
;

else_clause:
			{ $$ = NULL; }
	| ELSE block	{ $$ = $2; }
	| ELSE IF '(' expr ')' block else_clause	{ $$ = make_if($4, $6, $7, @$); }
;

block:
	'{' { sem_enter_scope(); } input '}' { sem_exit_scope(); $$ = $3; }
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

declare_or_expr_opt:
	declare		{ $$ = $1; }
	| expr		{ $$ = $1; }
	|	{ $$ = make_empty(@$); }
;

expr_opt:
	expr	{ $$ = $1; }
	|	{ $$ = make_empty(@$); }
;

expr:
	factor '=' expr		{ $$ = make_assign($1, $3, @$); }
	| factor ASSIGNMENT_ADD_EQUALS expr	{ $$ = make_assign($1, make_binary("+", $1, $3, @$), @$); }
	| factor ASSIGNMENT_SUB_EQUALS expr	{ $$ = make_assign($1, make_binary("-", $1, $3, @$), @$); }
	| factor ASSIGNMENT_MUL_EQUALS expr	{ $$ = make_assign($1, make_binary("*", $1, $3, @$), @$); }
	| factor ASSIGNMENT_DIV_EQUALS expr	{ $$ = make_assign($1, make_binary("/", $1, $3, @$), @$); }
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
	| term		{ $$ = $1; }
;

term:
	term '*' factor	{ $$ = make_binary("*", $1, $3, @$); }
	| term '/' factor	{ $$ = make_binary("/", $1, $3, @$); }
	| term '%' factor	{ $$ = make_binary("%", $1, $3, @$); }
	| factor	{ $$ = $1; }
;

factor:
	'(' type ')' factor	{ $$ = make_cast($2, $4, @$); }
	| '-' factor	{ $$ = make_unary("-", $2, @$); }
	| '*' factor	{ $$ = make_unary("*", $2, @$); }
	| '&' IDENTIFIER	{ $$ = make_unary("&", make_identifier($2, @$), @$); }
	| INCREMENT factor { $$ = make_assign($2, make_binary("+", $2, make_int(1, @$), @$), @$); }
	| DECREMENT factor { $$ = make_assign($2, make_binary("-", $2, make_int(1, @$), @$), @$); }
	| postfix	{ $$ = $1; }
;

postfix:
	primary		{ $$ = $1; }
	| postfix '[' factor ']'	{ $$ = make_unary("*", make_binary("+", $1, $3, @$), @$); }
	| IDENTIFIER '(' parameter_list ')'	{ $$ = make_function_call($1, $3, @$); }
	| postfix INCREMENT	{ $$ = make_binary("-", make_assign($1, make_binary("+", $1, make_int(1, @$), @$), @$), make_int(1, @$), @$); }
	| postfix DECREMENT	{ $$ = make_binary("+", make_assign($1, make_binary("-", $1, make_int(1, @$), @$), @$), make_int(1, @$), @$); }
;

primary:
	IDENTIFIER	{ $$ = make_identifier($1, @$); }
	| INT		{ $$ = make_int($1, @$); }
	| LONG		{ $$ = make_long($1, @$); }
	| CHARACTER	{ $$ = make_character($1, @$); }
	| STRING	{ $$ = make_string($1, @$); }
	| FLOAT		{ $$ = make_float($1, @$); }
	| DOUBLE	{ $$ = make_double($1, @$); }
	| TRUE			{ $$ = make_true(@$); }
	| FALSE			{ $$ = make_false(@$); }
	| NULLTOK		{ $$ = make_null(@$); }
	| '(' expr ')'	{ $$ = $2; }
;

%%


int yyerror(YYLTYPE* yylloc, const char *msg) {
	fprintf(stderr, "Parse error at line %d, column %d: %s\n",
		yylloc->first_line, yylloc->first_column, msg);
	exit(1);
	return 1;
}
