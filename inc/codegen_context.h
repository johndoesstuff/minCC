#include <llvm-c/Core.h>

typedef struct {
	LLVMContextRef context;
	LLVMModuleRef module;
	LLVMBuilderRef builder;
	LLVMValueRef function;
} CodegenContext;
