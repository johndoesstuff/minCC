#include <llvm-c/Core.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/Analysis.h>
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "symbol_table.h"

extern int yyparse();
extern ASTNode* root;

LLVMBuilderRef builder;

LLVMValueRef generate(ASTNode* node) {
	switch (node->type) {
		case AST_PROGRAM: {
					for (int i = 0; i < node->program.count; i++) {
						generate(node->program.statements[i]);
					}
					return NULL;
				}
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
		case AST_ASSIGN: {
					LLVMValueRef value = generate(node->assign.right);
					LLVMValueRef var = create_variable(node->assign.identifier);
					return LLVMBuildStore(builder, value, var);
				}
		case AST_IDENTIFIER: {
					LLVMValueRef ptr = lookup_variable("x");
					return LLVMBuildLoad2(builder, LLVMInt32Type(), ptr, "loadtmp");
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
