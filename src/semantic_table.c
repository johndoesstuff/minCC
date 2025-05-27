#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/semantic_table.h"

SemScope* sem_current_scope = NULL;

SemEntry* sem_lookup(const char* name, SemEntryKind entryKind) {
        for (SemScope* scope = sem_current_scope; scope != NULL; scope = scope->next) {
                for (SemEntry* var = scope->variables; var != NULL; var = var->next) {
                        if (strcmp(var->name, name) == 0 && var->entryKind == entryKind) {
                                return var;
                        }
                }
        }
	return NULL;
}

SemEntry* sem_lookup_variable(const char* name) {
        return sem_lookup(name, SEM_ENTRY_VAR);
}

SemEntry* sem_lookup_function(const char* name) {
        return sem_lookup(name, SEM_ENTRY_FUNC);
}

SemEntry* sem_create(const char* name, Type* type, SemEntryKind entryKind) {
        SemEntry* entry = malloc(sizeof(SemEntry));
        entry->name = strdup(name);
        entry->type = type;
	entry->entryKind = entryKind;
        if (!sem_current_scope) {
                fprintf(stderr, "null scope, something has gone horrifically wrong!!");
		exit(1);
	}
	entry->next = sem_current_scope->variables;
	sem_current_scope->variables = entry;
        return entry;
}

SemEntry* sem_create_variable(const char* name, Type* type) {
	return sem_create(name, type, SEM_ENTRY_VAR);
}

SemEntry* sem_create_function(const char* name, Type* type, Argument* arguments, int isVariadic) {
	SemEntry* entry = sem_create(name, type, SEM_ENTRY_FUNC);
	entry->isVariadic = isVariadic;
	int arg_count = count_arguments(arguments);
	entry->argTypes = malloc(sizeof(Type*) * arg_count);
	entry->arg_count = arg_count;
	Argument* current = arguments;
	for (int i = 0; i < arg_count; i++) {
		entry->argTypes[i] = current->type;
		current = current->next;
	}
	return entry;
}

void sem_enter_scope() {
        SemScope* new_scope = malloc(sizeof(SemScope));
        new_scope->variables = NULL;
        new_scope->next = sem_current_scope;
        sem_current_scope = new_scope;
}

void sem_exit_scope() {
        if (!sem_current_scope) {
                return;
        }

        SemEntry* var = sem_current_scope->variables;
        while (var) {
                SemEntry* next = var->next;
                free(var->name);
                free(var);
                var = next;
        }

        SemScope* old_scope = sem_current_scope;
        sem_current_scope = sem_current_scope->next;
        free(old_scope);
}
