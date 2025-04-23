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

%%

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

