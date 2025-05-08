#ifndef ERROR_H
#define ERROR_H

#include "../build/parser.tab.h"  // for YYLTYPE

int yyerror(YYLTYPE *loc, const char *msg);

#endif
