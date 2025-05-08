#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantic_table.h"

SemScope* sem_current_scope = NULL;

SemEntry* sem_lookup_variable(const char* name) {
        for (SemScope* scope = sem_current_scope; scope != NULL; scope = scope->next) {
                for (SemEntry* var = scope->variables; var != NULL; var = var->next) {
                        if (strcmp(var->name, name) == 0) {
                                return var;
                        }
                }
        }
        return NULL;
}

SemEntry* sem_create_variable(const char* name, Type* type) {
        SemEntry* entry = malloc(sizeof(SemEntry));
        entry->name = strdup(name);
        entry->type = type;
        if (!sem_current_scope) {
                fprintf(stderr, "null scope, something has gone horrifically wrong!!");
		exit(1);
	}
	entry->next = sem_current_scope->variables;
	sem_current_scope->variables = entry;
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
