%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char *signage;
	char *type_size;
	int pointer_depth;
} TypeInfo;

%}

%union {
	int ival;
	char* sval;
	TypeInfo* typeinfo;
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

%%

type:
	optional_signage TYPE_SIZE POINTER_CHAIN {
		TypeInfo *t = malloc(sizeof(TypeInfo));
		t->signage = $1;
		t->type_size = $2;
		t->pointer_depth = strlen($3);
	}
;

optional_signage:
	TYPE_SIGNAGE { $$ = $1; }
	| { $$ = "none"; }
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

