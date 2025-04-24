%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TypeInfo {
	char* signage;
	char* type_size;
	int pointer_depth;
} TypeInfo;

typedef struct Variable {
	char* identifier;
	TypeInfo* typeinfo;
} Variable;

%}

%union {
	int ival;
	char* sval;
	struct TypeInfo* typeinfo;
	struct Variable* variable;
	void* vval;
}

%token <ival> NUMBER
%type <ival> expr
%token <sval> IDENTIFIER
%token <sval> ASSIGNMENT_OPERATOR
%token <sval> TYPE_SIGNAGE
%token <sval> TYPE_SIZE
%token <sval> POINTER_CHAIN
%type <typeinfo> type
%type <sval> optional_signage
%type <ival> optional_pointer_chain
%type <variable> assignment_lhs
%type <ival> assignment_rhs
%type <vval> statement
%type <vval> program
%token '*'
%token ';'

%%

program:
       | program statement
;

statement:
	 assignment_expression ';' {}
;

assignment_expression:
	assignment_lhs ASSIGNMENT_OPERATOR assignment_rhs {
		printf("Variable %s is of type %s %s, pointer level %d. Assigning using %s a value of %d", $1->identifier, $1->typeinfo->signage, $1->typeinfo->type_size, $1->typeinfo->pointer_depth, $2, $3);
	}
;

assignment_rhs:
	expr { $$ = $1; }
;

assignment_lhs:
	type IDENTIFIER {
		Variable *v = malloc(sizeof(Variable));
		v->identifier = $2;
		v->typeinfo = $1;
		$$ = v;
	}
;

type:
	optional_signage TYPE_SIZE optional_pointer_chain {
		TypeInfo *t = malloc(sizeof(TypeInfo));
		t->signage = $1;
		t->type_size = $2;
		t->pointer_depth = $3;
		$$ = t;
	}
;

optional_signage:
	TYPE_SIGNAGE { $$ = $1; }
	| { $$ = "none"; }
;

optional_pointer_chain:
	'*' optional_pointer_chain { $$ = $2 + 1; }
	| { $$ = 0; }
;

expr:
	NUMBER '+' NUMBER {
		$$ = $1 + $3;
		printf("Sum = %d\n", $$);
	}
;

%%

int main() {
	return yyparse();
}

int yyerror(const char *s) {
	fprintf(stderr, "Error: %s\n", s);
	return 1;
}

