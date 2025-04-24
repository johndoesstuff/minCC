%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <llvm-c/Core.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/Target.h>
#include <llvm-c/TargetMachine.h>

LLVMBuilderRef builder;

typedef struct TypeInfo {
	char* signage;
	char* type_size;
	int pointer_depth;
} TypeInfo;

typedef struct Variable {
	char* identifier;
	TypeInfo* typeinfo;
} Variable;

typedef struct Symbol {
	char* identifier;
	LLVMValueRef llvm_ref;
	TypeInfo* typeinfo;
	struct Symbol* next;
} Symbol;

typedef struct SymbolNode {
	Symbol* symbol;
	struct SymbolNode* next;
} SymbolNode;

SymbolNode* symbol_table = NULL;

Symbol* get_symbol(char* variable_name) {
	if (symbol_table == NULL) {
		return NULL;
	}
	SymbolNode* node = symbol_table;
	while (node != NULL) {
		if (strcmp(node->symbol->identifier, variable_name) == 0) {
			return node->symbol;
		}
		node = node->next;
	}
	return NULL;
}

void add_symbol(Symbol* symbol) {
	SymbolNode* node = malloc(sizeof(SymbolNode));
	node->symbol = symbol;
	node->next = NULL;
	if (symbol_table == NULL) {
		symbol_table = node;
		return;
	}
	SymbolNode* current = symbol_table;
	while (current->next != NULL) {
		current = current->next;
	}
	current->next = node;
}

%}

%union {
	int ival;
	char* sval;
	struct TypeInfo* typeinfo;
	struct Variable* variable;
	void* vval;
}

%token <ival> NUMBER
%type <ival> expr
%token <sval> IDENTIFIER
%token <sval> ASSIGNMENT_OPERATOR
%token <sval> TYPE_SIGNAGE
%token <sval> TYPE_SIZE
%token <sval> POINTER_CHAIN
%type <typeinfo> type
%type <sval> optional_signage
%type <ival> optional_pointer_chain
%type <variable> assignment_lhs
%type <ival> assignment_rhs
%type <vval> statement
%type <vval> program
%token '*'
%token ';'

%%

program:
       | program statement
;

statement:
	 assignment_expression ';' {}
;

assignment_expression:
	assignment_lhs ASSIGNMENT_OPERATOR assignment_rhs {
		TypeInfo *type = $1->typeinfo;
		
		LLVMTypeRef llvm_type;
		if (strcmp(type->type_size, "int") == 0) {
			llvm_type = LLVMInt32Type();
		} else if (strcmp(type->type_size, "char") == 0) {
			llvm_type = LLVMInt8Type();
		}

		char *variable_name = $1->identifier;
		
		LLVMValueRef rhs_value = $3;
		LLVMValueRef variable_pointer = get_symbol(variable_name)->llvm_ref;

		LLVMBuildStore(builder, rhs_value, variable_pointer);

		printf("Variable %s is of type %s %s, pointer level %d. Assigning using %s a value of %d\n", $1->identifier, $1->typeinfo->signage, $1->typeinfo->type_size, $1->typeinfo->pointer_depth, $2, $3);
	}
;

assignment_rhs:
	expr { $$ = $1; }
;

assignment_lhs:
	type IDENTIFIER {
		Variable *v = malloc(sizeof(Variable));
		v->identifier = $2;
		v->typeinfo = $1;
		$$ = v;
	}
;

type:
	optional_signage TYPE_SIZE optional_pointer_chain {
		TypeInfo *t = malloc(sizeof(TypeInfo));
		t->signage = $1;
		t->type_size = $2;
		t->pointer_depth = $3;
		$$ = t;
	}
;

optional_signage:
	TYPE_SIGNAGE { $$ = $1; }
	| { $$ = "none"; }
;

optional_pointer_chain:
	'*' optional_pointer_chain { $$ = $2 + 1; }
	| { $$ = 0; }
;

expr:
	NUMBER '+' NUMBER {
		$$ = $1 + $3;
	}
;

%%

int main() {
	LLVMModuleRef module = LLVMModuleCreateWithName("my_module");
	LLVMBuilderRef builder = LLVMCreateBuilder();
	LLVMContextRef context = LLVMGetGlobalContext();

	LLVMTypeRef func_type = LLVMFunctionType(LLVMInt32Type(), NULL, 0, 0);
	LLVMValueRef func = LLVMAddFunction(module, "main", func_type);
	LLVMBasicBlockRef entry = LLVMAppendBasicBlock(func, "entry");

	LLVMPositionBuilderAtEnd(builder, entry);
	LLVMValueRef return_val = LLVMConstInt(LLVMInt32Type(), 42, 0);
	LLVMBuildRet(builder, return_val);
	
	char *ir_string = LLVMPrintModuleToString(module);
	printf("%s\n", ir_string);

	LLVMDisposeMessage(ir_string);
	LLVMDisposeBuilder(builder);
	LLVMDisposeModule(module);

	return yyparse();
}

int yyerror(const char *s) {
	fprintf(stderr, "Error: %s\n", s);
	return 1;
}

