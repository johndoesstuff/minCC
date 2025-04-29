#include <llvm-c/Core.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/Analysis.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "symbol_table.h"
#include "types.h"

extern int yyparse();
extern ASTNode* root;

LLVMBuilderRef builder;

LLVMValueRef generate(ASTNode* node) {
	if (node == NULL) {
		fprintf(stderr, "trying to generate null node??");
		return NULL;
	}
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
					 if (node->binary.left->valueType != node->binary.right->valueType) {
					 	fprintf(stderr, "type mismatch!!\n");
						exit(1);
					 }
					 if (strcmp(node->binary.op, "+") == 0) {
						 return LLVMBuildAdd(builder, left, right, "addtmp");
					 } else if (strcmp(node->binary.op, "-") == 0) {
						 return LLVMBuildSub(builder, left, right, "subtmp");
					 } else if (strcmp(node->binary.op, "*") == 0) {
						 return LLVMBuildMul(builder, left, right, "multmp");
					 } else if (strcmp(node->binary.op, "/") == 0) {
						 return LLVMBuildSDiv(builder, left, right, "divtmp");
					 } else if (strcmp(node->binary.op, "==") == 0) {
						 return LLVMBuildICmp(builder, LLVMIntEQ, left, right, "cmptmp");
					 } else if (strcmp(node->binary.op, "!=") == 0) {
						 return LLVMBuildICmp(builder, LLVMIntNE, left, right, "cmptmp");
					 } else if (strcmp(node->binary.op, "<") == 0) {
						 return LLVMBuildICmp(builder, LLVMIntSLT, left, right, "cmptmp");
					 } else if (strcmp(node->binary.op, ">") == 0) {
						 return LLVMBuildICmp(builder, LLVMIntSGT, left, right, "cmptmp");
					 } else if (strcmp(node->binary.op, "<=") == 0) {
						 return LLVMBuildICmp(builder, LLVMIntSLE, left, right, "cmptmp");
					 } else if (strcmp(node->binary.op, ">=") == 0) {
						 return LLVMBuildICmp(builder, LLVMIntSGE, left, right, "cmptmp");
					 }
				 }
		case AST_UNARY: {
					LLVMValueRef left = generate(node->unary.left);
					if (strcmp(node->unary.op, "-") == 0) {
						return LLVMBuildSub(builder, LLVMConstInt(LLVMInt32Type(), 0, 0), left, "subtmp");
					}
				}
		case AST_DECLARE: {
					if (node->declare.right) {
						LLVMValueRef value = generate(node->declare.right);
						VarEntry* var = lookup_variable(node->declare.identifier);
						LLVMBuildStore(builder, value, var->value);
					}
					return NULL;
				}
		case AST_ASSIGN: {
					VarEntry* var = lookup_variable(node->assign.identifier);
					LLVMValueRef value = generate(node->assign.right);
					return LLVMBuildStore(builder, value, var->value);
				}
		case AST_IDENTIFIER: {
					VarEntry* var = lookup_variable(node->identifier);
					if (!var) {
						fprintf(stderr, "Trying to access undeclared variable %s\n", node->identifier);
						exit(1);
					}
					return LLVMBuildLoad2(builder, get_llvm_type(var->valueType), var->value, "loadtmp");
				}
		case AST_RETURN: {
					LLVMValueRef value = generate(node->retrn.value);
					return LLVMBuildRet(builder, value);
				}
		case AST_BOOL: {
					return LLVMConstInt(LLVMInt1Type(), node->value, 0);
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
	//LLVMBuildRet(builder, result);

	char* ir = LLVMPrintModuleToString(module);
	printf("%s", ir);
	LLVMPrintModuleToFile(module, "output.ll", NULL);
	LLVMDisposeMessage(ir);
	LLVMDisposeBuilder(builder);
	LLVMDisposeModule(module);

	return 0;
}
