#include <string.h>
#include "types.h"

int is_boolean_operator(char* op) {
	return strcmp(op, "==") == 0 ||
		strcmp(op, "!=") == 0 ||
		strcmp(op, "<") == 0 ||
		strcmp(op, "<=") == 0 ||
		strcmp(op, ">") == 0 ||
		strcmp(op, ">=") == 0;
}
