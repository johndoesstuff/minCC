#ifndef AST_H
#define AST_H

typedef enum {
	AST_NUMBER,
	AST_BINARY
} ASTNodeType;

typedef struct ASTNode {
	ASTNodeType type;
	union {
		int value; // for AST_NUMBER
		struct {
			char op;
			struct ASTNode* left;
			struct ASTNode* right;
		} binary;
	};
} ASTNode;

ASTNode* make_number(int value);
ASTNode* make_binary(char op, ASTNode* left, ASTNode* right);

#endif
