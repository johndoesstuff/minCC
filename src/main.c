#include <llvm-c/Core.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/Analysis.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/ast.h"
#include "../inc/semantic_table.h"
#include "../inc/types.h"
#include "../inc/error.h"
#include "../inc/native.h"
#include "../inc/codegen_table.h"

extern int yyparse();
extern ASTNode* root;

LLVMValueRef generate(ASTNode* node, CodegenContext* cg) {
	if (node == NULL) {
		fprintf(stderr, "trying to generate null node??");
		return NULL;
	}
	switch (node->type) {
		case AST_PROGRAM: {
					  codegen_enter_scope();
					  for (int i = 0; i < node->program.count; i++) {
						  generate(node->program.statements[i], cg);
					  }
					  codegen_exit_scope();
					  return NULL;
				  }
		case AST_NUMBER:
				  return LLVMConstInt(LLVMInt32TypeInContext(cg->context), node->value, 0);
		case AST_FLOAT:
				  return LLVMConstReal(LLVMFloatTypeInContext(cg->context), node->floatValue);
		case AST_CHARACTER:
				  return LLVMConstInt(LLVMInt8TypeInContext(cg->context), node->character, 0);
		case AST_STRING: {
					//prepare string storage
				 	static int string_id = 0;
					char global_name[64];
					snprintf(global_name, sizeof(global_name), ".str.%d", string_id++);

					char *str = node->stringValue;
					size_t len = strlen(str) + 1;

					LLVMTypeRef str_type = LLVMArrayType(LLVMInt8TypeInContext(cg->context), len);
					LLVMValueRef global_str = LLVMAddGlobal(cg->module, str_type, global_name);
					LLVMSetLinkage(global_str, LLVMPrivateLinkage);
					LLVMSetGlobalConstant(global_str, 1);
					LLVMSetInitializer(global_str, LLVMConstStringInContext(cg->context, str, len, 1));

					LLVMValueRef zero = LLVMConstInt(LLVMInt32TypeInContext(cg->context), 0, 0);
					LLVMValueRef indices[] = { zero, zero };

					//return pointer
					LLVMValueRef gep = LLVMBuildInBoundsGEP2(cg->builder,
							str_type,     // type of the global string (array type)
							global_str,   // the pointer to GEP from
							indices,      // index list
							2,            // number of indices
							"strptr");    // name
					return gep;
				 }
		case AST_BINARY: {
					 //generate both sides
					 LLVMValueRef left = generate(node->binary.left, cg);
					 LLVMValueRef right = generate(node->binary.right, cg);

					 //prepare type coercion
					 LLVMTypeRef l_type = get_llvm_type(node->binary.left->valueType, cg->context);
					 LLVMTypeRef r_type = get_llvm_type(node->binary.right->valueType, cg->context);

					 //check float
					 int l_is_float = LLVMGetTypeKind(l_type) == LLVMFloatTypeKind || LLVMGetTypeKind(l_type) == LLVMDoubleTypeKind;
					 int r_is_float = LLVMGetTypeKind(r_type) == LLVMFloatTypeKind || LLVMGetTypeKind(r_type) == LLVMDoubleTypeKind;

					 //type coercion
					 if (l_type != r_type) {

						 //check floats
						 if (l_is_float && r_is_float) {
						 	//do nothing until i implement doubles
						 } else if (l_is_float && !r_is_float) {
						 	right = LLVMBuildSIToFP(cg->builder, right, l_type, "sitofp_tmp");
						 } else if (!l_is_float && r_is_float) {
						 	left = LLVMBuildSIToFP(cg->builder, left, r_type, "sitofp_tmp");
						 } else {
							 //match largest int
							 unsigned int l_width = LLVMGetIntTypeWidth(l_type);
							 unsigned int r_width = LLVMGetIntTypeWidth(r_type);

							 if (l_width >= r_width) {
								right = cast_to(right, l_type, 1, cg);
							 } else {
								left = cast_to(left, r_type, 1, cg);
							 }
						 }
					 }

					 if (l_is_float) {
						 if (strcmp(node->binary.op, "+") == 0) {
							 node->valueType = make_type(TYPE_FLOAT, 0);
							 return LLVMBuildFAdd(cg->builder, left, right, "faddtmp");
						 } else if (strcmp(node->binary.op, "-") == 0) {
							 node->valueType = make_type(TYPE_FLOAT, 0);
							 return LLVMBuildFSub(cg->builder, left, right, "fsubtmp");
						 } else if (strcmp(node->binary.op, "*") == 0) {
							 node->valueType = make_type(TYPE_FLOAT, 0);
							 return LLVMBuildFMul(cg->builder, left, right, "fmultmp");
						 } else if (strcmp(node->binary.op, "/") == 0) {
							 node->valueType = make_type(TYPE_FLOAT, 0);
							 return LLVMBuildFDiv(cg->builder, left, right, "fdivtmp");
						 } else if (strcmp(node->binary.op, "%") == 0) {
							 char *msg;
							 asprintf(&msg, "Invalid float operator: %s", node->binary.op);
							 yyerror(&node->loc, msg);
							 free(msg);
							 exit(1);
						 } else if (strcmp(node->binary.op, "==") == 0) {
							 node->valueType = make_type(TYPE_BOOL, 0);
							 return LLVMBuildFCmp(cg->builder, LLVMRealOEQ, left, right, "cmptmp");
						 } else if (strcmp(node->binary.op, "!=") == 0) {
							 node->valueType = make_type(TYPE_BOOL, 0);
							 return LLVMBuildFCmp(cg->builder, LLVMRealONE, left, right, "cmptmp");
						 } else if (strcmp(node->binary.op, "<") == 0) {
							 node->valueType = make_type(TYPE_BOOL, 0);
							 return LLVMBuildFCmp(cg->builder, LLVMRealOLT, left, right, "cmptmp");
						 } else if (strcmp(node->binary.op, ">") == 0) {
							 node->valueType = make_type(TYPE_BOOL, 0);
							 return LLVMBuildFCmp(cg->builder, LLVMRealOGT, left, right, "cmptmp");
						 } else if (strcmp(node->binary.op, "<=") == 0) {
							 node->valueType = make_type(TYPE_BOOL, 0);
							 return LLVMBuildFCmp(cg->builder, LLVMRealOLE, left, right, "cmptmp");
						 } else if (strcmp(node->binary.op, ">=") == 0) {
							 node->valueType = make_type(TYPE_BOOL, 0);
							 return LLVMBuildFCmp(cg->builder, LLVMRealOGE, left, right, "cmptmp");
						 }
					 } else {
						 if (strcmp(node->binary.op, "+") == 0) {
							 node->valueType = make_type(TYPE_INT, 0);
							 return LLVMBuildAdd(cg->builder, left, right, "addtmp");
						 } else if (strcmp(node->binary.op, "-") == 0) {
							 node->valueType = make_type(TYPE_INT, 0);
							 return LLVMBuildSub(cg->builder, left, right, "subtmp");
						 } else if (strcmp(node->binary.op, "*") == 0) {
							 node->valueType = make_type(TYPE_INT, 0);
							 return LLVMBuildMul(cg->builder, left, right, "multmp");
						 } else if (strcmp(node->binary.op, "/") == 0) {
							 node->valueType = make_type(TYPE_INT, 0);
							 return LLVMBuildSDiv(cg->builder, left, right, "divtmp");
						 } else if (strcmp(node->binary.op, "%") == 0) {
							 node->valueType = make_type(TYPE_INT, 0);
							 return LLVMBuildSRem(cg->builder, left, right, "modtmp");
						 } else if (strcmp(node->binary.op, "==") == 0) {
							 node->valueType = make_type(TYPE_BOOL, 0);
							 return LLVMBuildICmp(cg->builder, LLVMIntEQ, left, right, "cmptmp");
						 } else if (strcmp(node->binary.op, "!=") == 0) {
							 node->valueType = make_type(TYPE_BOOL, 0);
							 return LLVMBuildICmp(cg->builder, LLVMIntNE, left, right, "cmptmp");
						 } else if (strcmp(node->binary.op, "<") == 0) {
							 node->valueType = make_type(TYPE_BOOL, 0);
							 return LLVMBuildICmp(cg->builder, LLVMIntSLT, left, right, "cmptmp");
						 } else if (strcmp(node->binary.op, ">") == 0) {
							 node->valueType = make_type(TYPE_BOOL, 0);
							 return LLVMBuildICmp(cg->builder, LLVMIntSGT, left, right, "cmptmp");
						 } else if (strcmp(node->binary.op, "<=") == 0) {
							 node->valueType = make_type(TYPE_BOOL, 0);
							 return LLVMBuildICmp(cg->builder, LLVMIntSLE, left, right, "cmptmp");
						 } else if (strcmp(node->binary.op, ">=") == 0) {
							 node->valueType = make_type(TYPE_BOOL, 0);
							 return LLVMBuildICmp(cg->builder, LLVMIntSGE, left, right, "cmptmp");
						 }
					 }
				 }
		case AST_UNARY: {
					LLVMValueRef left = generate(node->unary.left, cg);
					if (strcmp(node->unary.op, "-") == 0) {
						node->valueType = make_type(TYPE_INT, 0);
						return LLVMBuildSub(cg->builder, LLVMConstInt(LLVMInt32TypeInContext(cg->context), 0, 0), left, "subtmp");
					}
				}
		case AST_FUNCTION: {
					LLVMTypeRef return_type = get_llvm_type(node->function.type, cg->context);
					
					int arg_count = count_arguments(node->function.arguments);
					LLVMTypeRef* param_types = malloc(sizeof(LLVMTypeRef) * arg_count);

					Argument* arg = node->function.arguments;
					for (int i = 0; i < arg_count; i++) {
						param_types[i] = get_llvm_type(arg->type, cg->context);
						arg = arg->next;
					}

					LLVMTypeRef func_type = LLVMFunctionType(return_type, param_types, arg_count, 0);

					LLVMValueRef llvm_func = LLVMAddFunction(cg->module, node->function.identifier, func_type);
					codegen_create_function(node->function.identifier, llvm_func, func_type);
					LLVMSetLinkage(llvm_func, LLVMExternalLinkage);

					LLVMBasicBlockRef entry = LLVMAppendBasicBlockInContext(cg->context, llvm_func, "entry");
					LLVMBuilderRef builder = LLVMCreateBuilderInContext(cg->context);
					LLVMPositionBuilderAtEnd(builder, entry);

					CodegenContext* new_cg = malloc(sizeof(CodegenContext));
					new_cg->builder = builder;
					new_cg->function = llvm_func;
					new_cg->module = cg->module;
					new_cg->context = cg->context;

					arg = node->function.arguments;

					codegen_enter_scope();

					for (int i = 0; i < arg_count; i++) {
						LLVMValueRef param = LLVMGetParam(llvm_func, i);
						LLVMSetValueName(param, arg->identifier);

						LLVMValueRef alloc = LLVMBuildAlloca(new_cg->builder, param_types[i], arg->identifier);
						LLVMBuildStore(new_cg->builder, param, alloc);

						codegen_create_variable(arg->identifier, alloc, param_types[i]);

						arg = arg->next;
					}
					
					generate(node->function.body, new_cg);

					if (return_type == LLVMVoidTypeInContext(cg->context)) {
						LLVMBuildRetVoid(builder);
					}

					LLVMDisposeBuilder(builder);
					free(new_cg);
					codegen_exit_scope();
					return NULL;
				}
		case AST_DECLARE: {
					  if (node->declare.right) {
						  LLVMValueRef value = generate(node->declare.right, cg);
						  LLVMTypeRef llvm_type = get_llvm_type(node->declare.type, cg->context);
						  LLVMValueRef alloc = LLVMBuildAlloca(cg->builder, llvm_type, node->declare.identifier);

						  codegen_create_variable(node->declare.identifier, alloc, llvm_type);
						  value = cast_to(value, llvm_type, 1, cg);
						  LLVMBuildStore(cg->builder, value, alloc);
					  }
					  return NULL;
				  }
		case AST_ASSIGN: {
					 CodegenEntry* var = codegen_lookup_variable(node->assign.identifier);
					 LLVMValueRef value = generate(node->assign.right, cg);
					 value = cast_to(value, var->type, 1, cg);
					 return LLVMBuildStore(cg->builder, value, var->value);
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
					     return LLVMBuildLoad2(cg->builder, var->type, var->value, "loadtmp");
				     }
		case AST_FUNCTION_CALL: {
						CodegenEntry* callee = codegen_lookup_function(node->function_call.identifier);
						if (callee == NULL) {
							char *msg;
							asprintf(&msg, "Trying to call undeclared function '%s'", node->function_call.identifier);
							yyerror(&node->loc, msg);
							free(msg);
							exit(1);
						}

						LLVMTypeRef func_sig = callee->type;
						LLVMTypeRef return_type = LLVMGetReturnType(func_sig);

						int arg_count = count_parameters(node->function_call.parameters);
						LLVMValueRef* args = malloc(sizeof(LLVMValueRef) * arg_count);

						Parameter* param = node->function_call.parameters;
						for (int i = 0; i < arg_count; i++) {
							args[i] = generate(param->value, cg);
							param = param->next;
						}

						LLVMValueRef call = LLVMBuildCall2(
								cg->builder,
								func_sig,
								callee->value,
								args,
								arg_count,
								return_type == LLVMVoidTypeInContext(cg->context) ? "" : "calltmp"
						);

						free(args);

						if (return_type == LLVMVoidTypeInContext(cg->context)) {
							return NULL;
						}

						return call;
					}
		case AST_RETURN: {
					 LLVMValueRef value = generate(node->return_stm.value, cg);
					 return LLVMBuildRet(cg->builder, value);
				 }
		case AST_BOOL: {
				       return LLVMConstInt(LLVMInt1TypeInContext(cg->context), node->value, 0);
			       }
		case AST_WHILE: {
					LLVMBasicBlockRef condBB = LLVMAppendBasicBlock(cg->function, "while.cond");
					LLVMBasicBlockRef bodyBB = LLVMAppendBasicBlock(cg->function, "while.body");
					LLVMBasicBlockRef endBB = LLVMAppendBasicBlock(cg->function, "while.end");

					LLVMBuildBr(cg->builder, condBB);

					LLVMPositionBuilderAtEnd(cg->builder, condBB);
					LLVMValueRef cond = generate(node->while_stm.conditional, cg);
					LLVMBuildCondBr(cg->builder, cond, bodyBB, endBB);

					LLVMPositionBuilderAtEnd(cg->builder, bodyBB);
					generate(node->while_stm.statements, cg);
					LLVMBuildBr(cg->builder, condBB);

					LLVMPositionBuilderAtEnd(cg->builder, endBB);
					return NULL;
				}
		case AST_IF: {
				     LLVMBasicBlockRef thenBB = LLVMAppendBasicBlock(cg->function, "if.then");
				     LLVMBasicBlockRef elseBB = node->if_stm.else_branch
					     ? LLVMAppendBasicBlock(cg->function, "if.else")
					     : NULL;
				     LLVMBasicBlockRef endBB  = LLVMAppendBasicBlock(cg->function, "if.end");

				     LLVMValueRef cond = generate(node->if_stm.conditional, cg);
				     if (elseBB) {
					     LLVMBuildCondBr(cg->builder, cond, thenBB, elseBB);
				     } else {
					     LLVMBuildCondBr(cg->builder, cond, thenBB, endBB);
				     }

				     LLVMPositionBuilderAtEnd(cg->builder, thenBB);
				     generate(node->if_stm.then_branch, cg);
				     LLVMBuildBr(cg->builder, endBB);

				     if (elseBB) {
					     LLVMPositionBuilderAtEnd(cg->builder, elseBB);
					     generate(node->if_stm.else_branch, cg);
					     if (!LLVMGetBasicBlockTerminator(elseBB)) {
						     LLVMBuildBr(cg->builder, endBB);
					     }
				     }

				     LLVMPositionBuilderAtEnd(cg->builder, endBB);
				     return NULL;
			     }
	}
	return NULL;
}

int main() {
	//build codegen context
	LLVMContextRef context = LLVMContextCreate();
	LLVMModuleRef module = LLVMModuleCreateWithNameInContext("global", context);
	LLVMBuilderRef builder = LLVMCreateBuilderInContext(context);

	LLVMTypeRef funcType = LLVMFunctionType(LLVMInt32Type(), NULL, 0, 0);
	LLVMValueRef main_function = LLVMAddFunction(module, "main", funcType);
	LLVMBasicBlockRef entry = LLVMAppendBasicBlock(main_function, "entry");
	LLVMPositionBuilderAtEnd(builder, entry);

	CodegenContext* main_cg = malloc(sizeof(CodegenContext));
	main_cg->context = context;
	main_cg->builder = builder;
	main_cg->module = module;
	main_cg->function = main_function;

	//parse and generate ast
	sem_enter_scope();

	declare_native_functions_sem();
	yyparse();

	sem_exit_scope();

	//traverse ast and generate code
	codegen_enter_scope();

	declare_native_functions_codegen(main_cg);
	generate(root, main_cg);

	codegen_exit_scope();

	//print generated code
	char* ir = LLVMPrintModuleToString(module);
	LLVMPrintModuleToFile(module, "output.ll", NULL);

	//cleanup
	LLVMDisposeMessage(ir);
	LLVMDisposeBuilder(builder);
	LLVMDisposeModule(module);

	return 0;
}
