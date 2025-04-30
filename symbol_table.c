#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"
#include "ast.h"
#include "types.h"

VarEntry* variables = NULL;

VarEntry* lookup_variable(const char* name) {
	for (VarEntry* var = variables; var != NULL; var = var->next) {
		if (strcmp(var->name, name) == 0) {
			return var;
		}
	}
	return NULL;
}

VarEntry* create_variable(const char* name, Type* type) {
	extern LLVMContextRef context;
	extern LLVMBuilderRef builder;
	LLVMValueRef alloc = LLVMBuildAlloca(builder, get_llvm_type(type, context), name);

	VarEntry* entry = malloc(sizeof(VarEntry));
	entry->name = strdup(name);
	entry->valueType = type;
	entry->value = alloc;
	entry->next = variables;
	variables = entry;
	return entry;
}

void free_symbol_table() {
	VarEntry* var = variables;
	while (var) {
		VarEntry* next = var->next;
		free(var->name);
		free(var);
		var = next;
	}
	variables = NULL;
}

