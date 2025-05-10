#include <stdlib.h>
#include <stdio.h>
#include "../inc/ast.h"
#include "../inc/types.h"
#include "../inc/semantic_table.h"
#include "../inc/error.h"

ASTNode* make_program(YYLTYPE loc) {
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_PROGRAM;
	node->loc = loc;
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

ASTNode* make_number(int value, YYLTYPE loc) {
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_NUMBER;
	node->loc = loc;
	node->valueType = make_type(TYPE_INT, 0);
	node->value = value;
	return node;
}

ASTNode* make_character(char character, YYLTYPE loc) {
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_CHARACTER;
	node->loc = loc;
	node->valueType = make_type(TYPE_CHAR, 0);
	node->character = character;
	return node;
}

ASTNode* make_string(char* string, YYLTYPE loc) {
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_STRING;
	node->loc = loc;
	node->valueType = make_type(TYPE_CHAR, 1);
	node->stringValue = string;
	return node;
}

ASTNode* make_identifier(char* identifier, YYLTYPE loc) {
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_IDENTIFIER;
	node->loc = loc;
	SemEntry* var = sem_lookup_variable(identifier);
	if (!var) {
		char *msg;
                asprintf(&msg, "Trying to access undeclared variable '%s'", identifier);
                yyerror(&loc, msg);
                free(msg);
		exit(1);
	}
	node->valueType = sem_lookup_variable(identifier)->type;
	node->identifier = identifier;
	return node;
}

ASTNode* make_assign(char* identifier, ASTNode* right, YYLTYPE loc) {
	SemEntry* var = sem_lookup_variable(identifier);
	if (!var) {
		char *msg;
                asprintf(&msg, "Assignment to undeclared variable '%s'", identifier);
                yyerror(&loc, msg);
		free(msg);
		exit(1);
	}

	/*if (type_cmp(right->valueType, var->type) != 0) {
		char *msg;
                asprintf(&msg, "Type mismatch in assignment of '%s': expected %s, got %s", identifier, type_to_str(var->type), type_to_str(right->valueType));
                yyerror(&loc, msg);
		free(msg);
		exit(1);
	}*/

	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_ASSIGN;
	node->loc = loc;
	node->valueType = right->valueType;
	node->assign.identifier = identifier;
	node->assign.right = right;
	return node;
}

ASTNode* make_declare(Type* type, char* identifier, ASTNode* right, YYLTYPE loc) {
	if (sem_lookup_variable(identifier)) {
		char *msg;
                asprintf(&msg, "Variable '%s' already declared", identifier);
                yyerror(&loc, msg);
		free(msg);
		exit(1);
	}
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_DECLARE;
	node->loc = loc;
	node->valueType = type;
	node->declare.identifier = identifier;
	node->declare.right = right;
	node->declare.type = type;

	sem_create_variable(identifier, node->valueType);

	/*if (right && type_cmp(right->valueType, type) != 0) {
		char *msg;
                asprintf(&msg, "Type mismatch in assignment of '%s': expected %s, got %s", identifier, type_to_str(type), type_to_str(right->valueType));
                yyerror(&node->loc, msg);
		free(msg);
		exit(1);
	}*/

	return node;
}

ASTNode* make_binary(char* op, ASTNode* left, ASTNode* right, YYLTYPE loc) {
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_BINARY;
	node->loc = loc;
	node->valueType = make_type(TYPE_INT, 0);
	if (is_boolean_operator(op)) {
		node->valueType = make_type(TYPE_BOOL, 0);
	}
	node->binary.op = op;
	node->binary.left = left;
	node->binary.right = right;
	return node;
}

ASTNode* make_unary(char* op, ASTNode* left, YYLTYPE loc) {
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_UNARY;
	node->loc = loc;
	node->valueType = make_type(TYPE_INT, 0);
	node->binary.op = op;
	node->binary.left = left;
	return node;
}

ASTNode* make_return(ASTNode* value, YYLTYPE loc) {
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_RETURN;
	node->loc = loc;
	node->valueType = value->valueType;
	node->return_stm.value = value;
	return node;
}

ASTNode* make_while(ASTNode* conditional, ASTNode* statements, YYLTYPE loc) {
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_WHILE;
	node->loc = loc;
	node->while_stm.conditional = conditional;
	node->while_stm.statements = statements;
	return node;
}

ASTNode* make_if(ASTNode* conditional, ASTNode* then_branch, ASTNode* else_branch, YYLTYPE loc) {
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_IF;
	node->loc = loc;
	node->if_stm.conditional = conditional;
	node->if_stm.then_branch = then_branch;
	node->if_stm.else_branch = else_branch;
	return node;
}

ASTNode* make_true(YYLTYPE loc) {
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_BOOL;
	node->loc = loc;
	node->valueType = make_type(TYPE_BOOL, 0);
	node->value = 1;
	return node;
}

ASTNode* make_false(YYLTYPE loc) {
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_BOOL;
	node->loc = loc;
	node->valueType = make_type(TYPE_BOOL, 0);
	node->value = 0;
	return node;
}
