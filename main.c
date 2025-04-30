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
LLVMContextRef context;

LLVMValueRef generate(ASTNode* node, LLVMValueRef function) {
	if (node == NULL) {
		fprintf(stderr, "trying to generate null node??");
		return NULL;
	}
	switch (node->type) {
		case AST_PROGRAM: {
					  for (int i = 0; i < node->program.count; i++) {
						  generate(node->program.statements[i], function);
					  }
					  return NULL;
				  }
		case AST_NUMBER:
				  return LLVMConstInt(LLVMInt32TypeInContext(context), node->value, 0);
		case AST_BINARY: {
					 LLVMValueRef left = generate(node->binary.left, function);
					 LLVMValueRef right = generate(node->binary.right, function);
					 if (type_cmp(node->binary.left->valueType, node->binary.right->valueType) != 0) {
						 fprintf(stderr, "type mismatch!!\n");
						 exit(1);
					 }
					 if (strcmp(node->binary.op, "+") == 0) {
						 node->valueType = make_type(TYPE_INT, 0);
						 return LLVMBuildAdd(builder, left, right, "addtmp");
					 } else if (strcmp(node->binary.op, "-") == 0) {
						 node->valueType = make_type(TYPE_INT, 0);
						 return LLVMBuildSub(builder, left, right, "subtmp");
					 } else if (strcmp(node->binary.op, "*") == 0) {
						 node->valueType = make_type(TYPE_INT, 0);
						 return LLVMBuildMul(builder, left, right, "multmp");
					 } else if (strcmp(node->binary.op, "/") == 0) {
						 node->valueType = make_type(TYPE_INT, 0);
						 return LLVMBuildSDiv(builder, left, right, "divtmp");
					 } else if (strcmp(node->binary.op, "==") == 0) {
						 node->valueType = make_type(TYPE_BOOL, 0);
						 return LLVMBuildICmp(builder, LLVMIntEQ, left, right, "cmptmp");
					 } else if (strcmp(node->binary.op, "!=") == 0) {
						 node->valueType = make_type(TYPE_BOOL, 0);
						 return LLVMBuildICmp(builder, LLVMIntNE, left, right, "cmptmp");
					 } else if (strcmp(node->binary.op, "<") == 0) {
						 node->valueType = make_type(TYPE_BOOL, 0);
						 return LLVMBuildICmp(builder, LLVMIntSLT, left, right, "cmptmp");
					 } else if (strcmp(node->binary.op, ">") == 0) {
						 node->valueType = make_type(TYPE_BOOL, 0);
						 return LLVMBuildICmp(builder, LLVMIntSGT, left, right, "cmptmp");
					 } else if (strcmp(node->binary.op, "<=") == 0) {
						 node->valueType = make_type(TYPE_BOOL, 0);
						 return LLVMBuildICmp(builder, LLVMIntSLE, left, right, "cmptmp");
					 } else if (strcmp(node->binary.op, ">=") == 0) {
						 node->valueType = make_type(TYPE_BOOL, 0);
						 return LLVMBuildICmp(builder, LLVMIntSGE, left, right, "cmptmp");
					 }
				 }
		case AST_UNARY: {
					LLVMValueRef left = generate(node->unary.left, function);
					if (strcmp(node->unary.op, "-") == 0) {
						node->valueType = make_type(TYPE_INT, 0);
						return LLVMBuildSub(builder, LLVMConstInt(LLVMInt32TypeInContext(context), 0, 0), left, "subtmp");
					}
				}
		case AST_DECLARE: {
					  if (node->declare.right) {
						  LLVMValueRef value = generate(node->declare.right, function);
						  VarEntry* var = lookup_variable(node->declare.identifier);
						  LLVMBuildStore(builder, value, var->value);
					  }
					  return NULL;
				  }
		case AST_ASSIGN: {
					 VarEntry* var = lookup_variable(node->assign.identifier);
					 LLVMValueRef value = generate(node->assign.right, function);
					 return LLVMBuildStore(builder, value, var->value);
				 }
		case AST_IDENTIFIER: {
					     VarEntry* var = lookup_variable(node->identifier);
					     if (!var) {
						     fprintf(stderr, "Trying to access undeclared variable %s\n", node->identifier);
						     exit(1);
					     }
					     return LLVMBuildLoad2(builder, get_llvm_type(var->valueType, context), var->value, "loadtmp");
				     }
		case AST_RETURN: {
					 LLVMValueRef value = generate(node->return_stm.value, function);
					 return LLVMBuildRet(builder, value);
				 }
		case AST_BOOL: {
				       return LLVMConstInt(LLVMInt1TypeInContext(context), node->value, 0);
			       }
		case AST_WHILE: {
					LLVMBasicBlockRef condBB = LLVMAppendBasicBlock(function, "while.cond");
					LLVMBasicBlockRef bodyBB = LLVMAppendBasicBlock(function, "while.body");
					LLVMBasicBlockRef endBB = LLVMAppendBasicBlock(function, "while.end");

					LLVMBuildBr(builder, condBB);

					LLVMPositionBuilderAtEnd(builder, condBB);
					LLVMValueRef cond = generate(node->while_stm.conditional, function);
					LLVMBuildCondBr(builder, cond, bodyBB, endBB);

					LLVMPositionBuilderAtEnd(builder, bodyBB);
					generate(node->while_stm.statements, function);
					LLVMBuildBr(builder, condBB);

					LLVMPositionBuilderAtEnd(builder, endBB);
					return NULL;
				}
		case AST_IF: {
				     LLVMBasicBlockRef thenBB = LLVMAppendBasicBlock(function, "if.then");
				     LLVMBasicBlockRef elseBB = node->if_stm.else_branch
					     ? LLVMAppendBasicBlock(function, "if.else")
					     : NULL;
				     LLVMBasicBlockRef endBB  = LLVMAppendBasicBlock(function, "if.end");

				     LLVMValueRef cond = generate(node->if_stm.conditional, function);
				     if (elseBB) {
					     LLVMBuildCondBr(builder, cond, thenBB, elseBB);
				     } else {
					     LLVMBuildCondBr(builder, cond, thenBB, endBB);
				     }

				     LLVMPositionBuilderAtEnd(builder, thenBB);
				     generate(node->if_stm.then_branch, function);
				     LLVMBuildBr(builder, endBB);

				     if (elseBB) {
					     LLVMPositionBuilderAtEnd(builder, elseBB);
					     generate(node->if_stm.else_branch, function);
					     if (!LLVMGetBasicBlockTerminator(elseBB)) {
						     LLVMBuildBr(builder, endBB);
					     }
				     }

				     LLVMPositionBuilderAtEnd(builder, endBB);
				     return NULL;
			     }
	}
	return NULL;
}

int main() {
	context = LLVMContextCreate();
	LLVMModuleRef module = LLVMModuleCreateWithNameInContext("tiny", context);
	builder = LLVMCreateBuilderInContext(context);

	LLVMTypeRef funcType = LLVMFunctionType(LLVMInt32Type(), NULL, 0, 0);
	LLVMValueRef main_function = LLVMAddFunction(module, "main", funcType);
	LLVMBasicBlockRef entry = LLVMAppendBasicBlock(main_function, "entry");
	LLVMPositionBuilderAtEnd(builder, entry);

	yyparse();

	LLVMValueRef result = generate(root, main_function);
	//LLVMBuildRet(builder, result);

	char* ir = LLVMPrintModuleToString(module);
	//printf("%s", ir);
	LLVMPrintModuleToFile(module, "output.ll", NULL);
	LLVMDisposeMessage(ir);
	LLVMDisposeBuilder(builder);
	LLVMDisposeModule(module);

	return 0;
}
