#include <llvm-c/Core.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/Analysis.h>
#include <stdio.h>
#include "ast.h"

extern int yyparse();
extern ASTNode* root;

LLVMBuilderRef builder;

LLVMValueRef generate(ASTNode* node) {
	switch (node->type) {
		case AST_NUMBER:
			return LLVMConstInt(LLVMInt32Type(), node->value, 0);
		case AST_BINARY: {
					 LLVMValueRef left = generate(node->binary.left);
					 LLVMValueRef right = generate(node->binary.right);
					 if (node->binary.op == '+') {
						 return LLVMBuildAdd(builder, left, right, "addtmp");
					 } else if (node->binary.op == '-') {
						 return LLVMBuildSub(builder, left, right, "subtmp");
					 } else if (node->binary.op == '*') {
						 return LLVMBuildMul(builder, left, right, "multmp");
					 } else if (node->binary.op == '/') {
						 return LLVMBuildSDiv(builder, left, right, "divtmp");
					 }
				 }
		case AST_UNARY: {
					LLVMValueRef left = generate(node->unary.left);
					if (node->unary.op == '-') {
						return LLVMBuildSub(builder, LLVMConstInt(LLVMInt32Type(), 0, 0), left, "subtmp");
					}
				}
	}
	return NULL;
}

int main() {
	LLVMModuleRef module = LLVMModuleCreateWithName("tiny");
	builder = LLVMCreateBuilder();

	LLVMTypeRef funcType = LLVMFunctionType(LLVMInt32Type(), NULL, 0, 0);
	LLVMValueRef function = LLVMAddFunction(module, "main", funcType);
	LLVMBasicBlockRef entry = LLVMAppendBasicBlock(function, "entry");
	LLVMPositionBuilderAtEnd(builder, entry);

	yyparse();

	LLVMValueRef result = generate(root);
	LLVMBuildRet(builder, result);

	char* ir = LLVMPrintModuleToString(module);
	printf("%s", ir);
	LLVMDisposeMessage(ir);
	LLVMDisposeBuilder(builder);
	LLVMDisposeModule(module);

	return 0;
}
