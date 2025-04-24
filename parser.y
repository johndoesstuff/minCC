%{
#include <stdio.h>
#include <stdlib.h>
%}

%union {
	int ival;
	char* sval;
}

%token <ival> NUMBER
%type <ival> expr
%token <sval> IDENTIFIER
%token <sval> ASSIGNMENT_OPERATOR
%token <sval> TYPE_SIGNAGE
%token <sval> TYPE_SIZE
%token <sval> POINTER_CHAIN
%type <ival> type
%type <sval> optional_signage

%%

type:
	optional_signage TYPE_SIZE POINTER_CHAIN {
		printf("Signage %s, Type %s, Pointer %s", $1, $2, $3);
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

