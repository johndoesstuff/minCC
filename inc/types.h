#ifndef TYPES_H
#define TYPES_H

#include <llvm-c/Core.h>

typedef enum {
        TYPE_INT,
        TYPE_BOOL,
	TYPE_CHAR,
        TYPE_VOID,
} BaseType;

typedef struct Type {
	BaseType baseType;
	int pointerDepth;
} Type;

int is_boolean_operator(char* op);
int type_cmp(Type* a, Type* b);
LLVMTypeRef get_llvm_type(Type* type, LLVMContextRef context);
BaseType get_base_type(char* type);
Type* make_type(BaseType base, int pointerDepth);
char* type_to_str(Type* type);
LLVMValueRef cast_to(LLVMValueRef value, LLVMTypeRef target_type, int is_signed);

#endif
