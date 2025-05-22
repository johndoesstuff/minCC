#ifndef TYPES_H
#define TYPES_H

#include <llvm-c/Core.h>
#include "../build/parser.tab.h"
#include "codegen_context.h"

typedef enum {
        TYPE_INT,
        TYPE_BOOL,
	TYPE_CHAR,
	TYPE_FLOAT,
        TYPE_VOID,
} BaseType;

typedef struct Type {
	BaseType baseType;
	int pointerDepth;
} Type;

typedef struct Argument {
	Type* type;
	char* identifier;
	YYLTYPE loc;
	struct Argument* next;
} Argument;

int is_boolean_operator(char* op);
int type_cmp(Type* a, Type* b);
LLVMTypeRef get_llvm_type(Type* type, LLVMContextRef context);
BaseType get_base_type(char* type);
Type* make_type(BaseType base, int pointerDepth);
char* type_to_str(Type* type);
LLVMValueRef cast_to(LLVMValueRef value, LLVMTypeRef target_type, int is_signed, CodegenContext* cg);
int count_arguments(Argument* arguments);

#endif
