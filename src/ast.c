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

Argument* make_argument(Type* type, char* identifier, YYLTYPE loc) {
	Argument* arg = malloc(sizeof(Argument));
	arg->type = type;
	arg->identifier = identifier;
	arg->loc = loc;
	arg->next = NULL;

	sem_create_variable(identifier, type);

	return arg;
}

void append_argument(Argument* arguments, Argument* argument, YYLTYPE loc) {
	if (argument == NULL) {
		printf("null argument");
		return;
	}
	if (arguments == NULL) {
		return;
	}
	
	Argument* current = arguments;
	while (current->next) {
		current = current->next;
	}
	current->next = argument;
}

Parameter* make_parameter(ASTNode* value, YYLTYPE loc) {
	Parameter* parameter = malloc(sizeof(Parameter));
	parameter->value = value;
	parameter->loc = loc;
	parameter->next = NULL;
	return parameter;
}

void append_parameter(Parameter* parameters, Parameter* parameter, YYLTYPE loc) {
	if (parameter == NULL) {
		printf("null parameter");
		return;
	}
	if (parameters == NULL) {
		return;
	}
	
	Parameter* current = parameters;
	while (current->next) {
		current = current->next;
	}
	current->next = parameter;
}

ASTNode* make_int(int value, YYLTYPE loc) {
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_INT;
	node->loc = loc;
	node->valueType = make_type(TYPE_INT, 0);
	node->intValue = value;
	return node;
}

ASTNode* make_long(long value, YYLTYPE loc) {
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_LONG;
	node->loc = loc;
	node->valueType = make_type(TYPE_LONG, 0);
	node->longValue = value;
	return node;
}

ASTNode* make_float(float value, YYLTYPE loc) {
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_FLOAT;
	node->loc = loc;
	node->valueType = make_type(TYPE_FLOAT, 0);
	node->floatValue = value;
	return node;
}

ASTNode* make_double(double value, YYLTYPE loc) {
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_DOUBLE;
	node->loc = loc;
	node->valueType = make_type(TYPE_DOUBLE, 0);
	node->doubleValue = value;
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

ASTNode* make_function_call(char* identifier, Parameter* parameters, YYLTYPE loc) {
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_FUNCTION_CALL;
	node->loc = loc;
	SemEntry* func = sem_lookup_function(identifier);
	if (!func) {
		char *msg;
                asprintf(&msg, "Trying to access undeclared function '%s'", identifier);
                yyerror(&loc, msg);
                free(msg);
		exit(1);
	}
	Parameter* currentParam = parameters;
	int arg_count = func->arg_count;
	int param_count = count_parameters(parameters);
	if (!func->isVariadic && arg_count != param_count) {
		char *msg;
                asprintf(&msg, "Argument mismatch for function '%s', expected %d arguments but recieved %d", identifier, arg_count, param_count);
                yyerror(&loc, msg);
                free(msg);
		exit(1);
	}
	for (int i = 0; i < arg_count; i++) {
		if (type_cmp(currentParam->value->valueType, func->argTypes[i]) != 0) {
			char *msg;
			asprintf(&msg, "Argument mismatch for function '%s', expected %s but recieved %s", identifier, type_to_str(func->argTypes[i]), type_to_str(currentParam->value->valueType));
			yyerror(&(currentParam->loc), msg);
			free(msg);
			exit(1);
		}
		currentParam = currentParam->next;
	}
	node->valueType = func->type;
	node->function_call.identifier = identifier;
	node->function_call.parameters = parameters;
	return node;
}

ASTNode* make_assign(ASTNode* left, ASTNode* right, YYLTYPE loc) {
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_ASSIGN;
	node->loc = loc;
	node->valueType = typedup(right->valueType);
	node->assign.left = left;
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
	node->valueType = typedup(type);
	node->declare.identifier = identifier;
	node->declare.right = right;
	node->declare.type = type;

	sem_create_variable(identifier, type);

	/*if (right && type_cmp(right->valueType, type) != 0) {
		char *msg;
                asprintf(&msg, "Type mismatch in assignment of '%s': expected %s, got %s", identifier, type_to_str(type), type_to_str(right->valueType));
                yyerror(&node->loc, msg);
		free(msg);
		exit(1);
	}*/

	return node;
}

ASTNode* make_function(Type* type, char* identifier, Argument* arguments, ASTNode* body, YYLTYPE loc) {
	if (sem_lookup_function(identifier)) {
		char *msg;
                asprintf(&msg, "Function '%s' already declared", identifier);
                yyerror(&loc, msg);
		free(msg);
		exit(1);
	}
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_FUNCTION;
	node->loc = loc;
	node->function.identifier = identifier;
	node->function.body = body;
	node->function.type = type;
	node->function.arguments = arguments;
	
	sem_create_function(identifier, type, arguments, 0); //todo: implement variadic functions at parsing

	return node;
}

ASTNode* make_binary(char* op, ASTNode* left, ASTNode* right, YYLTYPE loc) {
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_BINARY;
	node->loc = loc;

	Type* ltype = left->valueType;
	Type* rtype = right->valueType;

	if (is_boolean_operator(op)) {
		//value && value => bool
		node->valueType = make_type(TYPE_BOOL, 0);
	} else if (type_cmp(ltype, rtype) == 0) {
		//type op type => type
		node->valueType = typedup(ltype);
	} else if (is_numeric(ltype) && is_numeric(rtype)) {
		//num op num => num
		if (ltype->baseType == TYPE_FLOAT || rtype->baseType == TYPE_FLOAT) {
			//float + int => float
			node->valueType = make_type(TYPE_FLOAT, 0);
		} else {
			//bool + int => int
			node->valueType = make_type(TYPE_INT, 0);
		}
	} else if (ltype->pointerDepth > 0 && type_cmp(make_type(TYPE_INT, 0), rtype) == 0) {
		//pointer +/- int => pointer
		if (strcmp("+", op) == 0 || strcmp("-", op) == 0) {
			node->valueType = typedup(ltype);
		} else {
			char *msg;
			asprintf(&msg, "Cannot apply '%s' to types %s and %s", op, type_to_str(ltype), type_to_str(rtype));
			yyerror(&loc, msg);
			free(msg);
			exit(1);
		}
	} else if (ltype->pointerDepth > 0 && rtype->pointerDepth > 0) {
		//pointer - pointer => pointer
		if (strcmp("-", op) == 0) {
			node->valueType = make_type(TYPE_INT, 0);
		} else {
			char *msg;
			asprintf(&msg, "Cannot apply '%s' to types %s and %s", op, type_to_str(ltype), type_to_str(rtype));
			yyerror(&loc, msg);
			free(msg);
			exit(1);
		}
	} else {
		char *msg;
		asprintf(&msg, "Cannot apply '%s' to types %s and %s", op, type_to_str(ltype), type_to_str(rtype));
		yyerror(&loc, msg);
		free(msg);
		exit(1);
	}
	node->binary.op = op;
	node->binary.left = left;
	node->binary.right = right;
	return node;
}

ASTNode* make_unary(char* op, ASTNode* operand, YYLTYPE loc) {
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_UNARY;
	node->loc = loc;
	node->valueType = typedup(operand->valueType);
	node->unary.op = op;
	node->unary.operand = operand;
	if (strcmp(op, "*") == 0) {
		if (operand->valueType->pointerDepth == 0) {
			yyerror(&loc, "Cannot dereference non-pointer type");
			exit(1);
		} else {
			(node->valueType->pointerDepth)--;
		}
	} else if (strcmp(op, "&") == 0) {
		(node->valueType->pointerDepth)++;
	}
	return node;
}

ASTNode* make_cast(Type* type, ASTNode* value, YYLTYPE loc) {
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_CAST;
	node->loc = loc;
	node->valueType = typedup(type);
	node->cast.value = value;
	return node;
}

ASTNode* make_return(ASTNode* value, YYLTYPE loc) {
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_RETURN;
	node->loc = loc;
	node->valueType = typedup(value->valueType);
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
	node->boolValue = 1;
	return node;
}

ASTNode* make_false(YYLTYPE loc) {
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_BOOL;
	node->loc = loc;
	node->valueType = make_type(TYPE_BOOL, 0);
	node->boolValue = 0;
	return node;
}

ASTNode* make_null(YYLTYPE loc) {
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_NULL;
	node->loc = loc;
	node->valueType = make_type(TYPE_NULL, 0);
	return node;
}

ASTNode* make_empty(YYLTYPE loc) {
	ASTNode* node = malloc(sizeof(ASTNode));
	node->type = AST_EMPTY;
	node->loc = loc;
	return node;
}

int count_parameters(Parameter* params) {
        int count = 0;
        if (params == NULL) {
                return count;
        }

        Parameter* current = params;
        while (current) {
                count++;
                current = current->next;
        }
        return count;
}
