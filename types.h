#ifndef TYPES_H
#define TYPES_H

#include <llvm-c/Core.h>
#include "ast.h"

int is_boolean_operator(char* op);
LLVMTypeRef get_llvm_type(valueType type);
valueType get_value_type(char* type);

#endif
