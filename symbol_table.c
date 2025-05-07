#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"
#include "ast.h"
#include "types.h"

Scope* current_scope = NULL;

VarEntry* lookup_variable(const char* name) {
	for (Scope* scope = current_scope; scope != NULL; scope = scope->next) {
		for (VarEntry* var = scope->variables; var != NULL; var = var->next) {
			if (strcmp(var->name, name) == 0) {
				return var;
			}
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
	entry->next = current_scope->variables;
	if (!current_scope) {
		fprintf(stderr, "null scope, something has gone horrifically wrong!!");
		exit(1);
	}
	current_scope->variables = entry;
	return entry;
}

void enter_scope() {
	Scope* new_scope = malloc(sizeof(Scope));
	new_scope->variables = NULL;
	new_scope->next = current_scope;
	current_scope = new_scope;
}

void exit_scope() {
	if (!current_scope) {
		return;
	}

	VarEntry* var = current_scope->variables;
	while (var) {
		VarEntry* next = var->next;
		free(var->name);
		free(var);
		var = next;
	}

	Scope* old_scope = current_scope;
	current_scope = current_scope->next;
	free(old_scope);
}
