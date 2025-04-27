#ifndef AST_H
#define AST_H

#define INITIAL_CAPACITY 10

typedef enum {
	AST_PROGRAM,
	AST_NUMBER,
	AST_BINARY,
	AST_UNARY,
	AST_IDENTIFIER,
	AST_ASSIGN,
} ASTNodeType;

typedef struct ASTNode {
	ASTNodeType type;
	union {
		int value; // for AST_NUMBER
		char* identifier; // for AST_IDENTIFIER
		struct {
			char* identifier;
			struct ASTNode* right;
		} assign;
		struct {
			char op;
			struct ASTNode* left;
			struct ASTNode* right;
		} binary;
		struct {
			char op;
			struct ASTNode* left;
		} unary;
		struct {
			struct ASTNode** statements;
			int count;
			int capacity;
		} program;
	};
} ASTNode;

ASTNode* make_number(int value);
ASTNode* make_identifier(char* identifier);
ASTNode* make_assign(char* identifier, ASTNode* right);
ASTNode* make_binary(char op, ASTNode* left, ASTNode* right);
ASTNode* make_unary(char op, ASTNode* left);
ASTNode* make_program();
void append_statement(ASTNode* program_node, ASTNode* statement);

#endif
