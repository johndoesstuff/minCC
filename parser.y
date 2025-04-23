%{
#include <stdio.h>
#include <stdlib.h>  // for atoi
%}

%union {
    int ival;
}

%token <ival> NUMBER
%type <ival> expr

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

