#ifndef AST_H
#define AST_H

#include "types.h"
#include "parser.tab.h"
#define INITIAL_CAPACITY 10

typedef enum {
	AST_PROGRAM,
	AST_NUMBER,
	AST_BINARY,
	AST_UNARY,
	AST_IDENTIFIER,
	AST_ASSIGN,
	AST_RETURN,
	AST_BOOL,
	AST_DECLARE,
	AST_WHILE,
	AST_IF,
} ASTNodeType;

typedef struct ASTNode {
	ASTNodeType type;
	Type* valueType;
	YYLTYPE loc;
	union {
		int value; // for AST_NUMBER
		char* identifier; // for AST_IDENTIFIER
		struct {
			char* identifier;
			struct ASTNode* right;
		} assign;
		struct {
			Type* type;
			char* identifier;
			struct ASTNode* right;
		} declare;
		struct {
			char* op;
			struct ASTNode* left;
			struct ASTNode* right;
		} binary;
		struct {
			char* op;
			struct ASTNode* left;
		} unary;
		struct {
			struct ASTNode** statements;
			int count;
			int capacity;
		} program;
		struct {
			struct ASTNode* conditional;
			struct ASTNode* statements;
		} while_stm;
		struct {
			struct ASTNode* conditional;
			struct ASTNode* then_branch;
			struct ASTNode* else_branch;
		} if_stm;
		struct {
			struct ASTNode* value;
		} return_stm;
	};
} ASTNode;

ASTNode* make_number(int value, YYLTYPE loc);
ASTNode* make_identifier(char* identifier, YYLTYPE loc);
ASTNode* make_assign(char* identifier, ASTNode* right, YYLTYPE loc);
ASTNode* make_declare(Type* type, char* identifier, ASTNode* right, YYLTYPE loc);
ASTNode* make_binary(char* op, ASTNode* left, ASTNode* right, YYLTYPE loc);
ASTNode* make_unary(char* op, ASTNode* left, YYLTYPE loc);
ASTNode* make_program(YYLTYPE loc);
void append_statement(ASTNode* program_node, ASTNode* statement);
ASTNode* make_return(ASTNode* value, YYLTYPE loc);
ASTNode* make_while(ASTNode* conditional, ASTNode* statements, YYLTYPE loc);
ASTNode* make_if(ASTNode* conditional, ASTNode* then_branch, ASTNode* else_branch, YYLTYPE loc);
ASTNode* make_true(YYLTYPE loc);
ASTNode* make_false(YYLTYPE loc);

#endif
