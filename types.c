#include <llvm-c/Core.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "types.h"

int is_boolean_operator(char* op) {
	return strcmp(op, "==") == 0 ||
		strcmp(op, "!=") == 0 ||
		strcmp(op, "<") == 0 ||
		strcmp(op, "<=") == 0 ||
		strcmp(op, ">") == 0 ||
		strcmp(op, ">=") == 0;
}

LLVMTypeRef get_llvm_type(valueType type) {
	if (type == TYPE_INT) {
		return LLVMInt32Type();
	} else if (type == TYPE_BOOL) {
		return LLVMInt1Type();
	} else {
		fprintf(stderr, "unknown type??\n");
		return NULL;
	}
}

valueType get_value_type(char* type) {
	if (strcmp(type, "int") == 0) {
		return TYPE_INT;
	} else if (strcmp(type, "bool") == 0) {
		return TYPE_BOOL;
	} else {
		fprintf(stderr, "unknown type??\n");
		exit(1);
	}
}
