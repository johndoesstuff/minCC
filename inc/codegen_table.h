#ifndef CODEGEN_TABLE_H
#define CODEGEN_TABLE_H

#include <llvm-c/Core.h>

typedef struct CodegenEntry {
	char* name;
	LLVMValueRef value;
	LLVMTypeRef type;
	struct CodegenEntry* next;
} CodegenEntry;

typedef struct CodegenScope {
	CodegenEntry* variables;
	struct CodegenScope* next;
} CodegenScope;

extern CodegenScope* codegen_current_scope;

CodegenEntry* codegen_lookup_variable(const char* name);
CodegenEntry* codegen_create_variable(const char* name, LLVMValueRef value, LLVMTypeRef type);

void codegen_enter_scope();
void codegen_exit_scope();

#endif

