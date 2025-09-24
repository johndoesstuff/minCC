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
extern FILE* yyin;

LLVMValueRef codegen_logical_and(CodegenContext *cg, ASTNode *node, LLVMValueRef left, LLVMValueRef right) {
	LLVMBasicBlockRef current = LLVMGetInsertBlock(cg->builder);
	LLVMValueRef func = LLVMGetBasicBlockParent(current);

	LLVMBasicBlockRef rhs_block = LLVMAppendBasicBlock(func, "and.rhs");
	LLVMBasicBlockRef end_block = LLVMAppendBasicBlock(func, "and.end");

	LLVMBuildCondBr(cg->builder, left, rhs_block, end_block);

	LLVMPositionBuilderAtEnd(cg->builder, rhs_block);
	LLVMValueRef rhs_value = right;
	LLVMBuildBr(cg->builder, end_block);
	rhs_block = LLVMGetInsertBlock(cg->builder);

	LLVMPositionBuilderAtEnd(cg->builder, end_block);
	LLVMValueRef phi = LLVMBuildPhi(cg->builder, LLVMTypeOf(left), "andtmp");
	LLVMAddIncoming(phi, &left, &current, 1);
	LLVMAddIncoming(phi, &rhs_value, &rhs_block, 1);

	node->valueType = make_type(TYPE_BOOL, 0);
	return phi;
}

LLVMValueRef codegen_logical_or(CodegenContext *cg, ASTNode *node, LLVMValueRef left, LLVMValueRef right) {
	LLVMBasicBlockRef current = LLVMGetInsertBlock(cg->builder);
	LLVMValueRef func = LLVMGetBasicBlockParent(current);

	LLVMBasicBlockRef rhs_block = LLVMAppendBasicBlock(func, "or.rhs");
	LLVMBasicBlockRef end_block = LLVMAppendBasicBlock(func, "or.end");

	LLVMBuildCondBr(cg->builder, left, end_block, rhs_block);

	LLVMPositionBuilderAtEnd(cg->builder, rhs_block);
	LLVMValueRef rhs_value = right;
	LLVMBuildBr(cg->builder, end_block);
	rhs_block = LLVMGetInsertBlock(cg->builder); 

	LLVMPositionBuilderAtEnd(cg->builder, end_block);
	LLVMValueRef phi = LLVMBuildPhi(cg->builder, LLVMTypeOf(left), "ortmp");
	LLVMAddIncoming(phi, &left, &current, 1);
	LLVMAddIncoming(phi, &rhs_value, &rhs_block, 1);

	node->valueType = make_type(TYPE_BOOL, 0);
	return phi;
}

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
		case AST_INT:
				  return LLVMConstInt(LLVMInt32TypeInContext(cg->context), node->intValue, 0);
		case AST_LONG:
				  return LLVMConstInt(LLVMInt64TypeInContext(cg->context), node->longValue, 0);
		case AST_FLOAT:
				  return LLVMConstReal(LLVMFloatTypeInContext(cg->context), node->floatValue);
		case AST_DOUBLE:
				  return LLVMConstReal(LLVMDoubleTypeInContext(cg->context), node->doubleValue);
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

					 //pointer math
					 int l_is_ptr = node->binary.left->valueType->pointerDepth > 0;
					 int r_is_ptr = node->binary.right->valueType->pointerDepth > 0;
					 if ((l_is_ptr && !r_is_ptr && strcmp(node->binary.op, "+") == 0) ||
							 (!l_is_ptr && r_is_ptr && strcmp(node->binary.op, "+") == 0) ||
							 (l_is_ptr && !r_is_ptr && strcmp(node->binary.op, "-") == 0)) {
						 LLVMValueRef ptr_operand = l_is_ptr ? left : right;
						 LLVMValueRef index_operand = l_is_ptr ? right : left;
						 if (LLVMTypeOf(index_operand) != LLVMInt32TypeInContext(cg->context)) {
							 index_operand = LLVMBuildIntCast(cg->builder, index_operand, LLVMInt32TypeInContext(cg->context), "idxcast");
						 }

						 Type* ptr_type = l_is_ptr ? node->binary.left->valueType : node->binary.right->valueType;
						 Type* deref_type = typedup(ptr_type);
						 deref_type->pointerDepth--;
						 LLVMTypeRef element_llvm_type = get_llvm_type(deref_type, cg->context);

						 LLVMValueRef gep_result = LLVMBuildGEP2(cg->builder, element_llvm_type, ptr_operand, &index_operand, 1, "ptradd");
						 node->valueType = typedup(ptr_type);

						 return gep_result;
					 }

					 //prepare type coercion
					 LLVMTypeRef l_type = get_llvm_type(node->binary.left->valueType, cg->context);
					 LLVMTypeRef r_type = get_llvm_type(node->binary.right->valueType, cg->context);

					 if (LLVMTypeOf(left) != LLVMTypeOf(right) && l_type == r_type) {
						 yyerror(&node->loc, "ast/codegen type discrepancy before casting. the compiler has fallen. billions must die.\n");
						 exit(1);
					 }

					 //check float
					 int l_is_float = LLVMGetTypeKind(l_type) == LLVMFloatTypeKind || LLVMGetTypeKind(l_type) == LLVMDoubleTypeKind;
					 int r_is_float = LLVMGetTypeKind(r_type) == LLVMFloatTypeKind || LLVMGetTypeKind(r_type) == LLVMDoubleTypeKind;

					 //type coercion
					 if (l_type != r_type) {

						 //check floats
						 if (l_is_float && r_is_float) {
							 if (LLVMGetTypeKind(l_type) == LLVMDoubleTypeKind) {
								 right = LLVMBuildFPExt(cg->builder, right, LLVMTypeOf(left), "fpext_tmp");
								 node->binary.right->valueType = make_type(TYPE_DOUBLE, 0);
							 } else {
								 left = LLVMBuildFPExt(cg->builder, left, LLVMTypeOf(right), "fpext_tmp");
								 node->binary.left->valueType = make_type(TYPE_DOUBLE, 0);
							 }
						 } else if (l_is_float && !r_is_float) {
						 	right = LLVMBuildSIToFP(cg->builder, right, LLVMTypeOf(left), "sitofp_tmp");
							node->binary.right->valueType = typedup(node->binary.left->valueType);
						 } else if (!l_is_float && r_is_float) {
						 	left = LLVMBuildSIToFP(cg->builder, left, LLVMTypeOf(right), "sitofp_tmp");
							node->binary.left->valueType = typedup(node->binary.right->valueType);
						 } else {
							 //match largest int
							 unsigned int l_width = LLVMGetIntTypeWidth(l_type);
							 unsigned int r_width = LLVMGetIntTypeWidth(r_type);

							 if (l_width >= r_width) {
								right = cast_to(right, l_type, 1, cg);
								node->binary.right->valueType = typedup(node->binary.left->valueType);
							 } else {
								left = cast_to(left, r_type, 1, cg);
								node->binary.left->valueType = typedup(node->binary.right->valueType);
							 }
						 }
					 }

					 if (strcmp(node->binary.op, "&&") == 0 || strcmp(node->binary.op, "||") == 0) {
						 int l_is_bool = (LLVMGetTypeKind(l_type) == LLVMIntegerTypeKind && LLVMGetIntTypeWidth(l_type) == 1);
						 int r_is_bool = (LLVMGetTypeKind(r_type) == LLVMIntegerTypeKind && LLVMGetIntTypeWidth(r_type) == 1);

						 if (!l_is_bool) {
							 if (LLVMGetTypeKind(l_type) == LLVMIntegerTypeKind) {
								 LLVMValueRef zero = LLVMConstInt(l_type, 0, 0);
								 left = LLVMBuildICmp(cg->builder, LLVMIntNE, left, zero, "int_to_bool");
							 } else if (LLVMGetTypeKind(l_type) == LLVMFloatTypeKind || LLVMGetTypeKind(l_type) == LLVMDoubleTypeKind) {
								 LLVMValueRef zero = LLVMConstReal(l_type, 0.0);
								 left = LLVMBuildFCmp(cg->builder, LLVMRealONE, left, zero, "float_to_bool");
							 } else {
								 yyerror(&node->loc, "Unsupported left operand type for boolean coercion");
								 exit(1);
							 }
						 }

						 if (!r_is_bool) {
							 if (LLVMGetTypeKind(r_type) == LLVMIntegerTypeKind) {
								 LLVMValueRef zero = LLVMConstInt(r_type, 0, 0);
								 right = LLVMBuildICmp(cg->builder, LLVMIntNE, right, zero, "int_to_bool");
							 } else if (LLVMGetTypeKind(r_type) == LLVMFloatTypeKind || LLVMGetTypeKind(r_type) == LLVMDoubleTypeKind) {
								 LLVMValueRef zero = LLVMConstReal(r_type, 0.0);
								 right = LLVMBuildFCmp(cg->builder, LLVMRealONE, right, zero, "float_to_bool");
							 } else {
								 yyerror(&node->loc, "Unsupported right operand type for boolean coercion");
								 exit(1);
							 }
						 }
					 }

					 //get types again after coercion
					 l_type = get_llvm_type(node->binary.left->valueType, cg->context);
					 r_type = get_llvm_type(node->binary.right->valueType, cg->context);

					 l_is_float = LLVMGetTypeKind(l_type) == LLVMFloatTypeKind || LLVMGetTypeKind(l_type) == LLVMDoubleTypeKind;
					 r_is_float = LLVMGetTypeKind(r_type) == LLVMFloatTypeKind || LLVMGetTypeKind(r_type) == LLVMDoubleTypeKind;

					 if (LLVMTypeOf(left) != LLVMTypeOf(right) && l_type == r_type) {
					 	printf("ast/codegen type discrepancy after casting. the compiler has fallen. billions must die.\n");
						exit(1);
					 }

					 //ts pmo
					 if (strcmp(node->binary.op, "&&") == 0) {
						 return codegen_logical_and(cg, node, left, right);
					 } else if (strcmp(node->binary.op, "||") == 0) {
						 return codegen_logical_or(cg, node, left, right);
					 }

					 if (l_is_float) { //float operations
						 if (strcmp(node->binary.op, "+") == 0) {
							 node->valueType = typedup(node->binary.right->valueType);
							 return LLVMBuildFAdd(cg->builder, left, right, "faddtmp");
						 } else if (strcmp(node->binary.op, "-") == 0) {
							 node->valueType = typedup(node->binary.right->valueType);
							 return LLVMBuildFSub(cg->builder, left, right, "fsubtmp");
						 } else if (strcmp(node->binary.op, "*") == 0) {
							 node->valueType = typedup(node->binary.right->valueType);
							 return LLVMBuildFMul(cg->builder, left, right, "fmultmp");
						 } else if (strcmp(node->binary.op, "/") == 0) {
							 node->valueType = typedup(node->binary.right->valueType);
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
					 } else { //int operations
						 if (strcmp(node->binary.op, "+") == 0) {
							 node->valueType = typedup(node->binary.right->valueType);
							 return LLVMBuildAdd(cg->builder, left, right, "addtmp");
						 } else if (strcmp(node->binary.op, "-") == 0) {
							 node->valueType = typedup(node->binary.right->valueType);
							 return LLVMBuildSub(cg->builder, left, right, "subtmp");
						 } else if (strcmp(node->binary.op, "*") == 0) {
							 node->valueType = typedup(node->binary.right->valueType);
							 return LLVMBuildMul(cg->builder, left, right, "multmp");
						 } else if (strcmp(node->binary.op, "/") == 0) {
							 node->valueType = typedup(node->binary.right->valueType);
							 return LLVMBuildSDiv(cg->builder, left, right, "divtmp");
						 } else if (strcmp(node->binary.op, "%") == 0) {
							 node->valueType = typedup(node->binary.right->valueType);
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
					 printf("reached end of control flow at ast binary\n");
					 exit(1);
				 }
		case AST_UNARY: {
					LLVMValueRef operand = generate(node->unary.operand, cg);

					LLVMTypeRef type = get_llvm_type(node->unary.operand->valueType, cg->context);

					if (strcmp(node->unary.op, "-") == 0) {
						if (LLVMGetTypeKind(type) == LLVMFloatTypeKind || LLVMGetTypeKind(type) == LLVMDoubleTypeKind) {
							node->valueType = typedup(node->unary.operand->valueType);
							LLVMValueRef zero = LLVMConstReal(type, 0.0);
							return LLVMBuildFSub(cg->builder, zero, operand, "fnegtmp");

						} else if (LLVMGetTypeKind(type) == LLVMIntegerTypeKind) {
							node->valueType = typedup(node->unary.operand->valueType);
							LLVMValueRef zero = LLVMConstInt(type, 0, 0);
							return LLVMBuildSub(cg->builder, zero, operand, "inegtmp");

						} else {
							char *msg;
							asprintf(&msg, "Invalid unary '-' operand type: %d", LLVMGetTypeKind(type));
							yyerror(&node->loc, msg);
							free(msg);
							exit(1);
						}
					} else if (strcmp(node->unary.op, "*") == 0) {
						node->valueType = typedup(node->unary.operand->valueType);
						node->valueType->pointerDepth--;
						type = get_llvm_type(node->valueType, cg->context);
						return LLVMBuildLoad2(cg->builder, type, operand, "deref");
					} else if (strcmp(node->unary.op, "&") == 0) {
						CodegenEntry* ref = codegen_lookup_variable(node->unary.operand->identifier);

						return ref->value;
					}

					printf("reached end of control flow at ast unary\n");
					exit(1);
				}
		case AST_CAST: {
				       LLVMValueRef value = generate(node->cast.value, cg);
				       LLVMTypeRef type = get_llvm_type(node->valueType, cg->context);
				       return cast_to(value, type, 1, cg);
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
						  if (type_cmp(node->declare.right->valueType, node->valueType) != 0) {
							  value = cast_to(value, llvm_type, 1, cg);
						  }
						  LLVMBuildStore(cg->builder, value, alloc);
					  }
					  return NULL;
				  }
		case AST_ASSIGN: {
					 ASTNode* left = node->assign.left;
					 LLVMValueRef ptr = NULL;
					 if (left->type == AST_IDENTIFIER) {
					 	CodegenEntry* var = codegen_lookup_variable(left->identifier);
						ptr = var->value;
					 } else if (left->type == AST_UNARY && strcmp(left->unary.op, "*") == 0) {
					 	ptr = generate(left->unary.operand, cg);
					 } else {
					 	yyerror(&left->loc, "Unsupported LHS during assignment");
					 }
					 LLVMValueRef value = generate(node->assign.right, cg);

					 LLVMBuildStore(cg->builder, value, ptr);
					 return value;
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
						int fixed_arg_count = LLVMCountParamTypes(func_sig);

						LLVMTypeRef* param_types = NULL;
						if (fixed_arg_count > 0) {
							param_types = malloc(sizeof(LLVMTypeRef) * fixed_arg_count);
							LLVMGetParamTypes(func_sig, param_types);
						}

						int is_variadic = LLVMIsFunctionVarArg(func_sig);

						for (int i = 0; i < arg_count; i++) {
							LLVMValueRef val = generate(param->value, cg);

							//needs to undergo stupid fucking variadic casting fuck my stupid fucking chungus life
							if (is_variadic && i >= fixed_arg_count) { 
								LLVMTypeRef val_type = LLVMTypeOf(val);

								//float to double
								if (LLVMGetTypeKind(val_type) == LLVMFloatTypeKind) {
									val = LLVMBuildFPExt(cg->builder, val, LLVMDoubleTypeInContext(cg->context), "promoted");
								}

								//smaller ints to i32
								if (LLVMGetTypeKind(val_type) == LLVMIntegerTypeKind && LLVMGetIntTypeWidth(val_type) < 32) {
									val = LLVMBuildZExt(cg->builder, val, LLVMInt32TypeInContext(cg->context), "promoted");
								}
							}

							args[i] = val;
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
				       return LLVMConstInt(LLVMInt1TypeInContext(cg->context), node->boolValue, 0);
			       }
		case AST_NULL: {
				       return LLVMConstNull(LLVMPointerType(LLVMInt8TypeInContext(cg->context), 0));
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

				     int needs_end = 0;

				     //build conditional
				     LLVMBuildCondBr(cg->builder, cond, thenBB, elseBB ? elseBB : endBB);
	
				     //then
				     LLVMPositionBuilderAtEnd(cg->builder, thenBB);
				     generate(node->if_stm.then_branch, cg);
				     if (!LLVMGetBasicBlockTerminator(thenBB)) {
					     LLVMPositionBuilderAtEnd(cg->builder, thenBB);
					     LLVMBuildBr(cg->builder, endBB);
					     needs_end = 1;
				     } else {
					     LLVMBuildBr(cg->builder, endBB);
					     needs_end = 1;
				     }

				     //else
				     if (elseBB) {
					     LLVMPositionBuilderAtEnd(cg->builder, elseBB);
					     generate(node->if_stm.else_branch, cg);
					     if (!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(cg->builder))) {
						     LLVMBuildBr(cg->builder, endBB);
					     }
					     needs_end = 1;
				     } 
				    
				     if (needs_end) {
					     LLVMPositionBuilderAtEnd(cg->builder, endBB);
				     }

				     return NULL;
			     }
		case AST_EMPTY: {
					return NULL;
				}
	}
	return NULL;
}

int main(int argc, char** argv) {
	char* infile = NULL;
	char* outfile = "output.ll";

	//parse cli args
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-o") == 0) {
			if (i + 1 < argc) {
				outfile = argv[++i];
			} else {
				fprintf(stderr, "Error: -o requires an argument\n");
				return 1;
			}
		} else if (!infile) {
			infile = argv[i];
		} else {
			fprintf(stderr, "Error: multiple input files not supported\n");
			return 1;
		}
	}

	if (!infile) {
		fprintf(stderr, "usage: %s [-o output.ll] <input file>\n", argv[0]);
		return 1;
	}

	FILE* f = fopen(infile, "r");
	if (!f) {
		fprintf(stderr, "Error: Could not open file %s", infile);
		exit(1);
	}

	yyin = f;

	//build codegen context
	LLVMContextRef context = LLVMContextCreate();
	LLVMModuleRef module = LLVMModuleCreateWithNameInContext("global", context);
	LLVMBuilderRef builder = LLVMCreateBuilderInContext(context);

	CodegenContext* main_cg = malloc(sizeof(CodegenContext));
	main_cg->context = context;
	main_cg->builder = builder;
	main_cg->module = module;
	main_cg->function = NULL;

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
	if (LLVMPrintModuleToFile(module, outfile, NULL) != 0) {
		fprintf(stderr, "Error: Could not write to file %s\n", outfile);
		exit(1);
	}

	//cleanup
	LLVMDisposeMessage(ir);
	LLVMDisposeBuilder(builder);
	LLVMDisposeModule(module);

	return 0;
}
