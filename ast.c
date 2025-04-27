#include <stdlib.h>
#include <stdio.h>
#include "ast.h"

ASTNode* make_program() {
	printf("trying to make program node");
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_PROGRAM;
	node->program.statements = malloc(INITIAL_CAPACITY * sizeof(ASTNode*));
	node->program.count = 0;
	node->program.capacity = INITIAL_CAPACITY;
	return node;
}

void append_statement(ASTNode* program_node, ASTNode* statement) {
	printf(":3");
	if (program_node == NULL) {
		printf("null program node");
		return;
	}
	if (program_node->type != AST_PROGRAM) {
		return;
	}

	if (program_node->program.count == program_node->program.capacity) {
		program_node->program.capacity *= 2;
		program_node->program.statements = realloc(program_node->program.statements, program_node->program.capacity * sizeof(ASTNode*));
	}

	program_node->program.statements[program_node->program.count++] = statement;
}

ASTNode* make_number(int value) {
	printf("make number");
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_NUMBER;
	node->value = value;
	return node;
}

ASTNode* make_identifier(char* identifier) {
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_IDENTIFIER;
	node->identifier = identifier;
	return node;
}

ASTNode* make_assign(char* identifier, ASTNode* right) {
	printf("make assign");
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_ASSIGN;
	node->assign.identifier = identifier;
	node->assign.right = right;
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
