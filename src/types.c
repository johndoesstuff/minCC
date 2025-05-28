#include <llvm-c/Core.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "../inc/types.h"
#include "../inc/ast.h"

int is_boolean_operator(char* op) {
	return strcmp(op, "==") == 0 ||
		strcmp(op, "!=") == 0 ||
		strcmp(op, "<") == 0 ||
		strcmp(op, "<=") == 0 ||
		strcmp(op, ">") == 0 ||
		strcmp(op, ">=") == 0;
}

int type_cmp(Type* a, Type* b) {
	if (!a || !b) {
		fprintf(stderr, "trying to compare non existant types");
		exit(1);
	}
	return !(a->baseType == b->baseType && a->pointerDepth == b->pointerDepth);
}

LLVMTypeRef get_llvm_type(Type* type, LLVMContextRef context) {
	LLVMTypeRef base;
	switch (type->baseType) {
		case TYPE_INT:
			base = LLVMInt32TypeInContext(context);
			break;
		case TYPE_LONG:
			base = LLVMInt64TypeInContext(context);
			break;
		case TYPE_BOOL:
			base = LLVMInt1TypeInContext(context);
			break;
		case TYPE_CHAR:
			base = LLVMInt8TypeInContext(context);
			break;
		case TYPE_FLOAT:
			base = LLVMFloatTypeInContext(context);
			break;
		case TYPE_DOUBLE:
			base = LLVMDoubleTypeInContext(context);
			break;
		default:
			base = LLVMVoidTypeInContext(context);
			break;
	}

	for (int i = 0; i < type->pointerDepth; ++i) {
		base = LLVMPointerType(base, 0);
	}

	return base;
}

Type* make_type(BaseType base, int pointerDepth) {
	Type* type = malloc(sizeof(type));
	type->baseType = base;
	type->pointerDepth = pointerDepth;
	return type;
}

BaseType get_base_type(char* type) {
	if (strcmp(type, "int") == 0) {
		return TYPE_INT;
	} else if (strcmp(type, "bool") == 0) {
		return TYPE_BOOL;
	} else if (strcmp(type, "char") == 0) {
		return TYPE_CHAR;
	} else if (strcmp(type, "float") == 0) {
		return TYPE_FLOAT;
	} else if (strcmp(type, "double") == 0) {
		return TYPE_DOUBLE;
	} else if (strcmp(type, "short") == 0) {
		return TYPE_SHORT;
	} else if (strcmp(type, "long") == 0) {
		return TYPE_LONG;
	} else if (strcmp(type, "void") == 0) {
		return TYPE_VOID;
	} else {
		fprintf(stderr, "unknown type??\n");
		exit(1);
	}
}

char* type_to_str(Type* type) {
	const char* base;
	switch (type->baseType) {
		case TYPE_INT:  base = "int"; break;
		case TYPE_BOOL: base = "bool"; break;
		case TYPE_CHAR: base = "char"; break;
		case TYPE_FLOAT: base = "float"; break;
		case TYPE_VOID: base = "void"; break;
		case TYPE_DOUBLE: base = "double"; break;
		case TYPE_SHORT: base = "short"; break;
		case TYPE_LONG: base = "long"; break;
		default:        base = "unknown"; break;
	}

	size_t len = strlen(base) + type->pointerDepth + 1;
	char* result = malloc(len);

	strcpy(result, base);
	for (int i = 0; i < type->pointerDepth; i++) {
		strcat(result, "*");
	}

	return result;
}

unsigned get_float_type_bits(LLVMTypeRef type) {
	LLVMTypeKind kind = LLVMGetTypeKind(type);
	switch (kind) {
		case LLVMHalfTypeKind:       return 16;
		case LLVMFloatTypeKind:      return 32;
		case LLVMDoubleTypeKind:     return 64;
		case LLVMFP128TypeKind:      return 128;
		case LLVMPPC_FP128TypeKind:  return 128;
		default:
					     fprintf(stderr, "Error: unknown float type kind %d\n", kind);
					     exit(1);
	}
}

LLVMValueRef cast_to(LLVMValueRef value, LLVMTypeRef target_type, int is_signed, CodegenContext* cg) {
	LLVMBuilderRef builder = cg->builder;

	LLVMTypeRef current_type = LLVMTypeOf(value);
	if (current_type == target_type) return value;

	if (LLVMGetTypeKind(current_type) == LLVMIntegerTypeKind && LLVMGetTypeKind(target_type) == LLVMIntegerTypeKind) {

		unsigned current_bits = LLVMGetIntTypeWidth(current_type);
		unsigned target_bits = LLVMGetIntTypeWidth(target_type);

		if (current_bits < target_bits) {
			return is_signed
				? LLVMBuildSExt(builder, value, target_type, "sext")
				: LLVMBuildZExt(builder, value, target_type, "zext");
		} else if (current_bits > target_bits) {
			return LLVMBuildTrunc(builder, value, target_type, "trunc");
		}
	}

	if ((LLVMGetTypeKind(current_type) == LLVMFloatTypeKind || LLVMGetTypeKind(current_type) == LLVMDoubleTypeKind) && LLVMGetTypeKind(target_type) == LLVMIntegerTypeKind) {
		return is_signed
			? LLVMBuildFPToSI(builder, value, target_type, "fptosi")
			: LLVMBuildFPToUI(builder, value, target_type, "fptoui");
	}

	if (LLVMGetTypeKind(current_type) == LLVMIntegerTypeKind && (LLVMGetTypeKind(target_type) == LLVMFloatTypeKind || LLVMGetTypeKind(target_type) == LLVMDoubleTypeKind)) {
		return is_signed
			? LLVMBuildSIToFP(builder, value, target_type, "sitofp")
			: LLVMBuildUIToFP(builder, value, target_type, "uitofp");
	}

	if (LLVMGetTypeKind(current_type) == LLVMFloatTypeKind && LLVMGetTypeKind(target_type) == LLVMFloatTypeKind) {

		unsigned current_bits = get_float_type_bits(current_type);
		unsigned target_bits = get_float_type_bits(target_type);
		if (current_bits < target_bits) {
			return LLVMBuildFPExt(builder, value, target_type, "fpext");
		} else {
			return LLVMBuildFPTrunc(builder, value, target_type, "fptrunc");
		}
	}

	if (LLVMGetTypeKind(current_type) == LLVMPointerTypeKind && LLVMGetTypeKind(target_type) == LLVMPointerTypeKind) {
		return LLVMBuildPointerCast(builder, value, target_type, "ptrcast");
	}

	printf("unable to cast\n");
	exit(1);
}

int count_arguments(Argument* args) {
	int count = 0;
	if (args == NULL) {
		return count;
	}

	Argument* current = args;
	while (current) {
		count++;
		current = current->next;
	}
	return count;
}

Argument* sem_generate_argument_signature(int count, ...) {
	va_list args;
	va_start(args, count);

	Argument* head = NULL;
	Argument* tail = NULL;

	for (int i = 0; i < count; i++) {
		Type* t = va_arg(args, Type*);

		Argument* arg = malloc(sizeof(Argument));
		if (!arg) {
			va_end(args);
			return NULL;
		}
		arg->type = t;

		char* id = malloc(32);
		if (!id) {
			free(arg);
			va_end(args);
			return NULL;
		}
		snprintf(id, 32, "nativeArg%d", i);
		arg->identifier = id;
		arg->next = NULL;

		if (!head) {
			head = arg;
			tail = arg;
		} else {
			tail->next = arg;
			tail = arg;
		}
	}

	va_end(args);
	return head;
}

int is_numeric(Type* t) {
	BaseType base = t->baseType;
	if (t->pointerDepth > 0) {
		return 0;
	}
	if (
			base == TYPE_INT ||
			base == TYPE_LONG ||
			base == TYPE_BOOL ||
			base == TYPE_CHAR ||
			base == TYPE_FLOAT ||
			base == TYPE_DOUBLE
	) {
		return 1;
	}
	return 0;
}

Type* typedup(Type* t) {
	Type* newType = malloc(sizeof(Type));
	newType->pointerDepth = t->pointerDepth;
	newType->baseType = t->baseType;
	return newType;
}
