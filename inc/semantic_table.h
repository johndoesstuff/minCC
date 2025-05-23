#ifndef SEMANTIC_TABLE_H
#define SEMANTIC_TABLE_H

#include <llvm-c/Core.h>
#include "ast.h"
#include "types.h"

typedef enum SemEntryKind {
	SEM_ENTRY_VAR,
	SEM_ENTRY_FUNC,
} SemEntryKind;

typedef struct SemEntry {
	char* name;
	Type* type;
	SemEntryKind entryKind;
	struct SemEntry* next;
} SemEntry;

typedef struct SemScope {
	SemEntry* variables;
	struct SemScope* next;
} SemScope;

extern SemScope* current_sem_scope;

void sem_enter_scope();
void sem_exit_scope();

SemEntry* sem_lookup_variable(const char* name);
SemEntry* sem_create_variable(const char* name, Type* type);

SemEntry* sem_lookup_function(const char* name);
SemEntry* sem_create_function(const char* name, Type* type);

#endif
