#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <llvm-c/Core.h>

typedef struct VarEntry {
	char* name;
	LLVMValueRef value;
	struct VarEntry* next;
} VarEntry;

extern VarEntry* variables;

LLVMValueRef lookup_variable(const char* name);
LLVMValueRef create_variable(const char* name);
LLVMValueRef lookup_or_create_variable(const char* name);

void free_symbol_table();

#endif

