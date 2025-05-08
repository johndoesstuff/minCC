#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen_table.h"

CodegenScope* codegen_current_scope = NULL;

CodegenEntry* codegen_lookup_variable(const char* name) {
	for (CodegenScope* scope = codegen_current_scope; scope != NULL; scope = scope->next) {
		for (CodegenEntry* var = scope->variables; var != NULL; var = var->next) {
			if (strcmp(var->name, name) == 0) {
				return var;
			}
		}
	}
	return NULL;
}

CodegenEntry* codegen_create_variable(const char* name, LLVMValueRef value, LLVMTypeRef type) {
	CodegenEntry* entry = malloc(sizeof(CodegenEntry));
	entry->name = strdup(name);
	entry->value = value;
	entry->type = type;
	if (!codegen_current_scope) {
		fprintf(stderr, "null scope, something has gone horrifically wrong!!");
		exit(1);
	}
	entry->next = codegen_current_scope->variables;
	codegen_current_scope->variables = entry;
	return entry;
}

void codegen_enter_scope() {
	CodegenScope* new_scope = malloc(sizeof(CodegenScope));
	new_scope->variables = NULL;
	new_scope->next = codegen_current_scope;
	codegen_current_scope = new_scope;
}

void codegen_exit_scope() {
	if (!codegen_current_scope) {
		return;
	}

	CodegenEntry* var = codegen_current_scope->variables;
	while (var) {
		CodegenEntry* next = var->next;
		free(var->name);
		free(var);
		var = next;
	}

	CodegenScope* old_scope = codegen_current_scope;
	codegen_current_scope = codegen_current_scope->next;
	free(old_scope);
}
