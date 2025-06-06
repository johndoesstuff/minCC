#include <llvm-c/Core.h>

#include <string.h>
#include "../inc/types.h"

void declare_native_functions_sem() {
	Type* floatType = make_type(TYPE_FLOAT, 0);
	Type* doubleType = make_type(TYPE_DOUBLE, 0);

	// printf(const char*, ...) -> int
	sem_create_function("printf", make_type(TYPE_INT, 0), NULL, 1);

	// fmodf(float, float) -> float
	Argument* fmodf_sig = sem_generate_argument_signature(2, floatType, floatType);
	sem_create_function("fmodf", floatType, fmodf_sig, 0);

	// fmod(double, double) -> double
	Argument* fmod_sig = sem_generate_argument_signature(2, doubleType, doubleType);
	sem_create_function("fmod", doubleType, fmod_sig, 0);

	// floorf(float) -> float
	Argument* floorf_sig = sem_generate_argument_signature(1, floatType);
	sem_create_function("floorf", floatType, floorf_sig, 0);
}

void declare_native_functions_codegen(CodegenContext *cg) {
	// printf(const char*, ...) -> int
	LLVMTypeRef printf_arg_types[] = {
		LLVMPointerType(LLVMInt8TypeInContext(cg->context), 0)
	};
	LLVMTypeRef printf_type = LLVMFunctionType(
			LLVMInt32TypeInContext(cg->context),
			printf_arg_types,
			1,
			1
			);

	LLVMValueRef printf_func = LLVMAddFunction(cg->module, "printf", printf_type);
	LLVMSetLinkage(printf_func, LLVMExternalLinkage);

	codegen_create_function("printf", printf_func, printf_type);

	// fmodf(float, float) -> float
	LLVMTypeRef fmodf_args[] = {
		LLVMFloatTypeInContext(cg->context),
		LLVMFloatTypeInContext(cg->context)
	};
	LLVMTypeRef fmodf_type = LLVMFunctionType(
			LLVMFloatTypeInContext(cg->context),
			fmodf_args,
			2,
			0
			);
	LLVMValueRef fmodf_func = LLVMAddFunction(cg->module, "fmodf", fmodf_type);
	LLVMSetLinkage(fmodf_func, LLVMExternalLinkage);
	codegen_create_function("fmodf", fmodf_func, fmodf_type);

	// fmod(double, double) -> double
	LLVMTypeRef fmod_args[] = {
		LLVMDoubleTypeInContext(cg->context),
		LLVMDoubleTypeInContext(cg->context)
	};
	LLVMTypeRef fmod_type = LLVMFunctionType(
			LLVMDoubleTypeInContext(cg->context),
			fmod_args,
			2,
			0
			);
	LLVMValueRef fmod_func = LLVMAddFunction(cg->module, "fmod", fmod_type);
	LLVMSetLinkage(fmod_func, LLVMExternalLinkage);
	codegen_create_function("fmod", fmod_func, fmod_type);

	// floorf(float) -> float
	LLVMTypeRef floorf_args[] = {
		LLVMFloatTypeInContext(cg->context)
	};
	LLVMTypeRef floorf_type = LLVMFunctionType(
			LLVMFloatTypeInContext(cg->context),
			floorf_args,
			1,
			0
			);
	LLVMValueRef floorf_func = LLVMAddFunction(cg->module, "floorf", floorf_type);
	LLVMSetLinkage(floorf_func, LLVMExternalLinkage);
	codegen_create_function("floorf", floorf_func, floorf_type);
}

