#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <llvm-c/Core.h>
#include "ast.h"

typedef struct VarEntry {
	char* name;
	LLVMValueRef value;
	Type* valueType;
	struct VarEntry* next;
} VarEntry;

typedef struct Scope {
	VarEntry* variables;
	struct Scope* next;
} Scope;

extern VarEntry* variables;
extern Scope* current_scope;

VarEntry* lookup_variable(const char* name);
VarEntry* create_variable(const char* name, Type* type);

void enter_scope();
void exit_scope();

#endif

