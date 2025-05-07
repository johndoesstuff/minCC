#ifndef ERROR_H
#define ERROR_H

#include "parser.tab.h"  // for YYLTYPE

int yyerror(YYLTYPE *loc, const char *msg);

#endif
