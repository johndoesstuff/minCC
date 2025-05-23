%{
#include "parser.tab.h"
#include <string.h>


int yycolumn = 1;

#define YY_DECL int yylex(YYSTYPE *yylval, YYLTYPE *yylloc)

#define YY_USER_ACTION                                  \
	yylloc->first_line = yylloc->last_line = yylineno;  \
	yylloc->first_column = yycolumn;                    \
	yycolumn += yyleng;                                 \
	yylloc->last_column = yycolumn;                     \

YY_DECL;

char *unescape_string(const char *src) {
	size_t len = strlen(src);
	char *dst = malloc(len + 1);
	char *out = dst;

	for (const char *p = src; *p; p++) {
		if (*p == '\\') {
			p++;
			if (!*p) break;
			switch (*p) {
				case 'n': *out++ = '\n'; break;
				case 't': *out++ = '\t'; break;
				case '\\': *out++ = '\\'; break;
				case '"': *out++ = '"'; break;
				default: *out++ = *p; break;
			}
		} else {
			*out++ = *p;
		}
	}

	*out = '\0';
	return dst;
}

char parse_char_literal(const char *text) {
	if (text[1] != '\\') {
		return text[1];
	}

	switch (text[2]) {
		case 'n': return '\n';
		case 't': return '\t';
		case '0': return '\0';
		case '\'': return '\'';
		case '\\': return '\\';
		default: return text[2];
	}
}


%}

%option yylineno

%%

([0-9]*\.[0-9]+([eE][-+]?[0-9]+)?|[0-9]+[eE][-+]?[0-9]+)	{ yylval->fval = atof(yytext); return FLOAT; }
[0-9]+		{ yylval->ival = atoi(yytext); return NUMBER; }
'([^\\']|\\.)' { yylval->cval = parse_char_literal(yytext); return CHARACTER; }
\"([^\\\"]|\\.)*\"		{ yytext[yyleng - 1] = '\0'; yylval->sval = unescape_string(yytext + 1); return STRING; }
"return"	{ return RETURN; }
"while"		{ return WHILE; }
"if"		{ return IF; }
"else"		{ return ELSE; }
"true"		{ return TRUE; }
"false"		{ return FALSE; }
"="		{ return '='; }
";"		{ return ';'; }
"("		{ return '('; }
")"		{ return ')'; }
"{"		{ return '{'; }
"}"		{ return '}'; }
("int"|"bool"|"char"|"float")	{ yylval->sval = strdup(yytext); return BASE_TYPE; }
("=="|"<"|">"|"<="|">="|"!=")		{ yylval->sval = strdup(yytext); return COMPARE; }
[a-zA-Z_][a-zA-Z0-9_]*	{ yylval->sval = strdup(yytext); return IDENTIFIER; }
"+"		{ return '+'; }
"-"		{ return '-'; }
"*"		{ return '*'; }
"/"		{ return '/'; }
"%"		{ return '%'; }
","		{ return ','; }
\/\/.*		;
\n      { yycolumn = 1; yylineno++; }
[ \t]+	; // ignore whitespace
.		{ fprintf(stderr, "Invalid character: %s at %d:%d\n", yytext, yylineno, yycolumn); }

%%
