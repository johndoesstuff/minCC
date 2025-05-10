#include <llvm-c/Core.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/Analysis.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/ast.h"
#include "../inc/codegen_table.h"
#include "../inc/semantic_table.h"
#include "../inc/types.h"
#include "../inc/error.h"

extern int yyparse();
extern ASTNode* root;

LLVMBuilderRef builder;
LLVMContextRef context;
LLVMModuleRef module;

LLVMValueRef generate(ASTNode* node, LLVMValueRef function) {
	if (node == NULL) {
		fprintf(stderr, "trying to generate null node??");
		return NULL;
	}
	switch (node->type) {
		case AST_PROGRAM: {
					  codegen_enter_scope();
					  for (int i = 0; i < node->program.count; i++) {
						  generate(node->program.statements[i], function);
					  }
					  codegen_exit_scope();
					  return NULL;
				  }
		case AST_NUMBER:
				  return LLVMConstInt(LLVMInt32TypeInContext(context), node->value, 0);
		case AST_FLOAT:
				  return LLVMConstReal(LLVMFloatTypeInContext(context), node->floatValue);
		case AST_CHARACTER:
				  return LLVMConstInt(LLVMInt8TypeInContext(context), node->character, 0);
		case AST_STRING: {
					//prepare string storage
				 	static int string_id = 0;
					char global_name[64];
					snprintf(global_name, sizeof(global_name), ".str.%d", string_id++);

					char *str = node->stringValue;
					size_t len = strlen(str) + 1;

					LLVMTypeRef str_type = LLVMArrayType(LLVMInt8TypeInContext(context), len);
					LLVMValueRef global_str = LLVMAddGlobal(module, str_type, global_name);
					LLVMSetLinkage(global_str, LLVMPrivateLinkage);
					LLVMSetGlobalConstant(global_str, 1);
					LLVMSetInitializer(global_str, LLVMConstStringInContext(context, str, len, 1));

					LLVMValueRef zero = LLVMConstInt(LLVMInt32TypeInContext(context), 0, 0);
					LLVMValueRef indices[] = { zero, zero };

					//return pointer
					LLVMValueRef gep = LLVMBuildInBoundsGEP2(builder,
							str_type,     // type of the global string (array type)
							global_str,   // the pointer to GEP from
							indices,      // index list
							2,            // number of indices
							"strptr");    // name
					return gep;
				 }
		case AST_BINARY: {
					 //generate both sides
					 LLVMValueRef left = generate(node->binary.left, function);
					 LLVMValueRef right = generate(node->binary.right, function);

					 //prepare type coercion
					 LLVMTypeRef l_type = get_llvm_type(node->binary.left->valueType, context);
					 LLVMTypeRef r_type = get_llvm_type(node->binary.right->valueType, context);

					 //check float
					 int l_is_float = LLVMGetTypeKind(l_type) == LLVMFloatTypeKind || LLVMGetTypeKind(l_type) == LLVMDoubleTypeKind;
					 int r_is_float = LLVMGetTypeKind(r_type) == LLVMFloatTypeKind || LLVMGetTypeKind(r_type) == LLVMDoubleTypeKind;

					 //type coercion
					 if (l_type != r_type) {

						 //check floats
						 if (l_is_float && r_is_float) {
						 	//do nothing until i implement doubles
						 } else if (l_is_float && !r_is_float) {
						 	right = LLVMBuildSIToFP(builder, right, l_type, "sitofp_tmp");
						 } else if (!l_is_float && r_is_float) {
						 	left = LLVMBuildSIToFP(builder, left, r_type, "sitofp_tmp");
						 } else {
							 //match largest int
							 unsigned int l_width = LLVMGetIntTypeWidth(l_type);
							 unsigned int r_width = LLVMGetIntTypeWidth(r_type);

							 if (l_width >= r_width) {
								right = cast_to(right, l_type, 1);
							 } else {
								left = cast_to(left, r_type, 1);
							 }
						 }
					 }

					 if (l_is_float) {
						 if (strcmp(node->binary.op, "+") == 0) {
							 node->valueType = make_type(TYPE_FLOAT, 0);
							 return LLVMBuildFAdd(builder, left, right, "faddtmp");
						 } else if (strcmp(node->binary.op, "-") == 0) {
							 node->valueType = make_type(TYPE_FLOAT, 0);
							 return LLVMBuildFSub(builder, left, right, "fsubtmp");
						 } else if (strcmp(node->binary.op, "*") == 0) {
							 node->valueType = make_type(TYPE_FLOAT, 0);
							 return LLVMBuildFMul(builder, left, right, "fmultmp");
						 } else if (strcmp(node->binary.op, "/") == 0) {
							 node->valueType = make_type(TYPE_FLOAT, 0);
							 return LLVMBuildFDiv(builder, left, right, "fdivtmp");
						 } else if (strcmp(node->binary.op, "%") == 0) {
							 char *msg;
							 asprintf(&msg, "Invalid float operator: %s", node->binary.op);
							 yyerror(&node->loc, msg);
							 free(msg);
							 exit(1);
						 } else if (strcmp(node->binary.op, "==") == 0) {
							 node->valueType = make_type(TYPE_BOOL, 0);
							 return LLVMBuildFCmp(builder, LLVMRealOEQ, left, right, "cmptmp");
						 } else if (strcmp(node->binary.op, "!=") == 0) {
							 node->valueType = make_type(TYPE_BOOL, 0);
							 return LLVMBuildFCmp(builder, LLVMRealONE, left, right, "cmptmp");
						 } else if (strcmp(node->binary.op, "<") == 0) {
							 node->valueType = make_type(TYPE_BOOL, 0);
							 return LLVMBuildFCmp(builder, LLVMRealOLT, left, right, "cmptmp");
						 } else if (strcmp(node->binary.op, ">") == 0) {
							 node->valueType = make_type(TYPE_BOOL, 0);
							 return LLVMBuildFCmp(builder, LLVMRealOGT, left, right, "cmptmp");
						 } else if (strcmp(node->binary.op, "<=") == 0) {
							 node->valueType = make_type(TYPE_BOOL, 0);
							 return LLVMBuildFCmp(builder, LLVMRealOLE, left, right, "cmptmp");
						 } else if (strcmp(node->binary.op, ">=") == 0) {
							 node->valueType = make_type(TYPE_BOOL, 0);
							 return LLVMBuildFCmp(builder, LLVMRealOGE, left, right, "cmptmp");
						 }
					 } else {
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
						 } else if (strcmp(node->binary.op, "%") == 0) {
							 node->valueType = make_type(TYPE_INT, 0);
							 return LLVMBuildSRem(builder, left, right, "modtmp");
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
						  LLVMTypeRef llvm_type = get_llvm_type(node->declare.type, context);
						  LLVMValueRef alloc = LLVMBuildAlloca(builder, llvm_type, node->declare.identifier);

						  codegen_create_variable(node->declare.identifier, alloc, llvm_type);
						  value = cast_to(value, llvm_type, 1);
						  LLVMBuildStore(builder, value, alloc);
					  }
					  return NULL;
				  }
		case AST_ASSIGN: {
					 CodegenEntry* var = codegen_lookup_variable(node->assign.identifier);
					 LLVMValueRef value = generate(node->assign.right, function);
					 value = cast_to(value, var->type, 1);
					 return LLVMBuildStore(builder, value, var->value);
				 }
		case AST_IDENTIFIER: {
					     CodegenEntry* var = codegen_lookup_variable(node->identifier);
					     if (!var) {
						     char *msg;
						     asprintf(&msg, "Trying to access undeclared variable '%s'", node->identifier);
						     yyerror(&node->loc, msg);
						     free(msg);
						     exit(1);
					     }
					     return LLVMBuildLoad2(builder, var->type, var->value, "loadtmp");
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
	module = LLVMModuleCreateWithNameInContext("global", context);
	builder = LLVMCreateBuilderInContext(context);

	LLVMTypeRef funcType = LLVMFunctionType(LLVMInt32Type(), NULL, 0, 0);
	LLVMValueRef main_function = LLVMAddFunction(module, "main", funcType);
	LLVMBasicBlockRef entry = LLVMAppendBasicBlock(main_function, "entry");
	LLVMPositionBuilderAtEnd(builder, entry);

	sem_enter_scope();
	yyparse();
	sem_exit_scope();

	codegen_enter_scope();
	generate(root, main_function);
	codegen_exit_scope();

	char* ir = LLVMPrintModuleToString(module);
	//printf("%s", ir);
	LLVMPrintModuleToFile(module, "output.ll", NULL);
	LLVMDisposeMessage(ir);
	LLVMDisposeBuilder(builder);
	LLVMDisposeModule(module);

	return 0;
}
