#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"
#include "ast.h"

VarEntry* variables = NULL;

VarEntry* lookup_variable(const char* name) {
	for (VarEntry* var = variables; var != NULL; var = var->next) {
		if (strcmp(var->name, name) == 0) {
			return var;
		}
	}
	fprintf(stderr, "Unknown variable: %s\n", name);
	exit(1);
}

VarEntry* create_variable(const char* name, valueType type) {
	extern LLVMBuilderRef builder;
	LLVMValueRef alloc = LLVMBuildAlloca(builder, LLVMInt32Type(), name);

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

