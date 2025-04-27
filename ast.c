#include <stdlib.h>
#include "ast.h"

ASTNode* make_number(int value) {
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_NUMBER;
	node->value = value;
	return node;
}

ASTNode* make_binary(char op, ASTNode* left, ASTNode* right) {
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_BINARY;
	node->binary.op = op;
	node->binary.left = left;
	node->binary.right = right;
	return node;
}

ASTNode* make_unary(char op, ASTNode* left) {
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_UNARY;
	node->binary.op = op;
	node->binary.left = left;
	return node;
}
