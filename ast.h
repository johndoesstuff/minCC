#ifndef AST_H
#define AST_H

typedef enum {
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
	};
} ASTNode;

ASTNode* make_number(int value);
ASTNode* make_identifier(char* identifier);
ASTNode* make_assign(char* identifier, ASTNode* right);
ASTNode* make_binary(char op, ASTNode* left, ASTNode* right);
ASTNode* make_unary(char op, ASTNode* left);

#endif
