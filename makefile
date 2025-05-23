# Makefile

# Output binary name
TARGET = minCC

# Source files
PARSER = src/parser.y
LEXER = src/lexer.l
AST_C = src/ast.c
CODEGEN_TABLE_C = src/codegen_table.c
SEMANTIC_TABLE_C = src/semantic_table.c
TYPES_C = src/types.c
NATIVE_C = src/native.c
MAIN_C = src/main.c

# Generated files
PARSER_C = build/parser.tab.c
PARSER_H = build/parser.tab.h
LEXER_C = build/lex.yy.c

# Compiler
CC = gcc
CFLAGS = `llvm-config --cflags` -Wno-implicit-function-declaration -Wall -g
LDFLAGS = `llvm-config --ldflags --libs core` -lfl

# Default target
all: $(TARGET)

# Build final binary
$(TARGET): $(PARSER_C) $(PARSER_H) $(LEXER_C) $(LEXER) $(AST_C) $(SEMANTIC_TABLE_C) $(CODEGEN_TABLE_C) $(TYPES_C) $(NATIVE_C) $(MAIN_C)
	$(CC) $(CFLAGS) -o $(TARGET) $(PARSER_C) $(LEXER_C) $(AST_C) $(SEMANTIC_TABLE_C) $(CODEGEN_TABLE_C) $(TYPES_C) $(NATIVE_C) $(MAIN_C) $(LDFLAGS)

# Generate parser source/header
$(PARSER_C) $(PARSER_H): $(PARSER)
	bison -d $(PARSER) -o $(PARSER_C)

# Generate lexer source
$(LEXER_C): $(LEXER)
	flex -o $(LEXER_C) $(LEXER)

# Clean generated files
clean:
	rm -f $(TARGET) $(PARSER_C) $(PARSER_H) $(LEXER_C)

.PHONY: all clean

