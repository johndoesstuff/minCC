#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"

VarEntry* variables = NULL;

LLVMValueRef lookup_variable(const char* name) {
	for (VarEntry* var = variables; var != NULL; var = var->next) {
		if (strcmp(var->name, name) == 0)
			return var->value;
	}
	fprintf(stderr, "Unknown variable: %s\n", name);
	exit(1);
}

LLVMValueRef create_variable(const char* name) {
	extern LLVMBuilderRef builder;
	LLVMValueRef alloc = LLVMBuildAlloca(builder, LLVMInt32Type(), name);

	VarEntry* entry = malloc(sizeof(VarEntry));
	entry->name = strdup(name);
	entry->value = alloc;
	entry->next = variables;
	variables = entry;
	return alloc;
}

LLVMValueRef lookup_or_create_variable(const char* name) {
	VarEntry* var;
	for (var = variables; var != NULL; var = var->next) {
		if (strcmp(var->name, name) == 0)
			return var->value;
	}
	return create_variable(name);
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

