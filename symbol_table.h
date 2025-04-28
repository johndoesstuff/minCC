#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <llvm-c/Core.h>
#include "ast.h"

typedef struct VarEntry {
	char* name;
	LLVMValueRef value;
	valueType valueType;
	struct VarEntry* next;
} VarEntry;

extern VarEntry* variables;

VarEntry* lookup_variable(const char* name);
VarEntry* create_variable(const char* name, valueType type);

void free_symbol_table();

#endif

