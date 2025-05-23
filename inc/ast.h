#ifndef AST_H
#define AST_H

#include "types.h"
#include "../build/parser.tab.h"
#define INITIAL_CAPACITY 10

typedef enum {
	AST_PROGRAM,
	AST_NUMBER,
	AST_FLOAT,
	AST_CHARACTER,
	AST_STRING,
	AST_BINARY,
	AST_UNARY,
	AST_IDENTIFIER,
	AST_ASSIGN,
	AST_RETURN,
	AST_BOOL,
	AST_DECLARE,
	AST_WHILE,
	AST_IF,
	AST_FUNCTION,
	AST_FUNCTION_CALL,
} ASTNodeType;

typedef struct ASTNode {
	ASTNodeType type;
	Type* valueType;
	YYLTYPE loc;
	union {
		int value; // for AST_NUMBER
		float floatValue; // for AST_FLOAT
		char* identifier; // for AST_IDENTIFIER
		char character; // for AST_CHARACTER
		char* stringValue; // for AST_STRING
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
		struct {
			Type* type;
			char* identifier;
			Argument* arguments;
			struct ASTNode* body;
		} function;
		struct {
			char* identifier;
			struct Parameter* parameters;
		} function_call;
	};
} ASTNode;

typedef struct Parameter {
        ASTNode* value;
        YYLTYPE loc;
        struct Parameter* next;
} Parameter;

int count_parameters(Parameter* params);

//primitives
ASTNode* make_number(int value, YYLTYPE loc);
ASTNode* make_float(float value, YYLTYPE loc);
ASTNode* make_character(char character, YYLTYPE loc);
ASTNode* make_string(char* string, YYLTYPE loc);
ASTNode* make_true(YYLTYPE loc);
ASTNode* make_false(YYLTYPE loc);

//arguments / identifiers
ASTNode* make_identifier(char* identifier, YYLTYPE loc);
Argument* make_argument(Type* type, char* identifier, YYLTYPE loc);
void append_argument(Argument* arguments, Argument* argument, YYLTYPE loc);

Parameter* make_parameter(ASTNode* value, YYLTYPE loc);
void append_parameter(Parameter* parameters, Parameter* parameter, YYLTYPE loc);

//operators
ASTNode* make_binary(char* op, ASTNode* left, ASTNode* right, YYLTYPE loc);
ASTNode* make_unary(char* op, ASTNode* left, YYLTYPE loc);

//variables
ASTNode* make_assign(char* identifier, ASTNode* right, YYLTYPE loc);
ASTNode* make_declare(Type* type, char* identifier, ASTNode* right, YYLTYPE loc);
ASTNode* make_function(Type* type, char* identifier, Argument* arguments, ASTNode* body, YYLTYPE loc);
ASTNode* make_function_call(char* identifier, Parameter* parameters, YYLTYPE loc);

//control flow
ASTNode* make_return(ASTNode* value, YYLTYPE loc);
ASTNode* make_while(ASTNode* conditional, ASTNode* statements, YYLTYPE loc);
ASTNode* make_if(ASTNode* conditional, ASTNode* then_branch, ASTNode* else_branch, YYLTYPE loc);

//program
ASTNode* make_program(YYLTYPE loc);
void append_statement(ASTNode* program_node, ASTNode* statement);

#endif
