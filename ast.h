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
	AST_RETURN,
	AST_BOOL,
	AST_DECLARE,
} ASTNodeType;

typedef enum {
	TYPE_INT,
	TYPE_BOOL,
} valueType;

typedef struct ASTNode {
	ASTNodeType type;
	valueType valueType;
	union {
		int value; // for AST_NUMBER
		char* identifier; // for AST_IDENTIFIER
		struct {
			char* identifier;
			struct ASTNode* right;
		} assign;
		struct {
			char* type;
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
			struct ASTNode* value;
		} retrn;
	};
} ASTNode;

ASTNode* make_number(int value);
ASTNode* make_identifier(char* identifier);
ASTNode* make_assign(char* identifier, ASTNode* right);
ASTNode* make_declare(char* type, char* identifier, ASTNode* right);
ASTNode* make_binary(char* op, ASTNode* left, ASTNode* right);
ASTNode* make_unary(char* op, ASTNode* left);
ASTNode* make_program();
void append_statement(ASTNode* program_node, ASTNode* statement);
ASTNode* make_return(ASTNode* value);
ASTNode* make_true();
ASTNode* make_false();

#endif
