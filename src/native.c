#include <llvm-c/Core.h>
#include <string.h>
#include "../inc/types.h"

void declare_native_functions_sem() {
	sem_create_function("printf", make_type(TYPE_INT, 0));
}

void declare_native_functions_codegen(CodegenContext *cg) {
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
}

