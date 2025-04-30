#include <stdlib.h>
#include <stdio.h>
#include "ast.h"
#include "types.h"
#include "symbol_table.h"

ASTNode* make_program() {
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_PROGRAM;
	node->program.statements = malloc(INITIAL_CAPACITY * sizeof(ASTNode*));
	node->program.count = 0;
	node->program.capacity = INITIAL_CAPACITY;
	return node;
}

void append_statement(ASTNode* program_node, ASTNode* statement) {
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
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_NUMBER;
	node->valueType = make_type(TYPE_INT, 0);
	node->value = value;
	return node;
}

ASTNode* make_identifier(char* identifier) {
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_IDENTIFIER;
	VarEntry* var = lookup_variable(identifier);
	if (!var) {
		fprintf(stderr, "Could not find variable %s\n", identifier);
		exit(1);
	}
	node->valueType = lookup_variable(identifier)->valueType;
	node->identifier = identifier;
	return node;
}

ASTNode* make_assign(char* identifier, ASTNode* right) {
	VarEntry* var = lookup_variable(identifier);
	if (!var) {
		fprintf(stderr, "Assignment to undeclared variable %s\n", identifier);
		exit(1);
	}

	if (type_cmp(right->valueType, var->valueType) != 0) {
		fprintf(stderr, "Type mismatch in assignment of %s: expected %s, got %s\n", identifier, type_to_str(var->valueType), type_to_str(right->valueType));
		exit(1);
	}

	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_ASSIGN;
	node->valueType = right->valueType;
	node->assign.identifier = identifier;
	node->assign.right = right;
	return node;
}

ASTNode* make_declare(Type* type, char* identifier, ASTNode* right) {
	if (lookup_variable(identifier)) {
		fprintf(stderr, "Variable %s already declared\n", identifier);
		exit(1);
	}
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_DECLARE;
	node->valueType = right->valueType;
	node->declare.identifier = identifier;
	node->declare.right = right;
	node->declare.type = type;

	create_variable(identifier, node->valueType);

	if (right && type_cmp(right->valueType, node->valueType) != 0) {
		fprintf(stderr, "Type mismatch in declaration of %s: expected %s, got %s\n", identifier, type_to_str(node->valueType), type_to_str(right->valueType));
		exit(1);
	}

	return node;
}

ASTNode* make_binary(char* op, ASTNode* left, ASTNode* right) {
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_BINARY;
	node->valueType = make_type(TYPE_INT, 0);
	if (is_boolean_operator(op)) {
		node->valueType = make_type(TYPE_BOOL, 0);
	}
	node->binary.op = op;
	node->binary.left = left;
	node->binary.right = right;
	return node;
}

ASTNode* make_unary(char* op, ASTNode* left) {
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_UNARY;
	node->valueType = make_type(TYPE_INT, 0);
	node->binary.op = op;
	node->binary.left = left;
	return node;
}

ASTNode* make_return(ASTNode* value) {
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_RETURN;
	node->valueType = value->valueType;
	node->return_stm.value = value;
	return node;
}

ASTNode* make_while(ASTNode* conditional, ASTNode* statements) {
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_WHILE;
	node->while_stm.conditional = conditional;
	node->while_stm.statements = statements;
	return node;
}

ASTNode* make_if(ASTNode* conditional, ASTNode* then_branch, ASTNode* else_branch) {
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_IF;
	node->if_stm.conditional = conditional;
	node->if_stm.then_branch = then_branch;
	node->if_stm.else_branch = else_branch;
	return node;
}

ASTNode* make_true() {
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_BOOL;
	node->valueType = make_type(TYPE_BOOL, 0);
	node->value = 1;
	return node;
}

ASTNode* make_false() {
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_BOOL;
	node->valueType = make_type(TYPE_BOOL, 0);
	node->value = 0;
	return node;
}
