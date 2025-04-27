# Makefile

# Output binary name
TARGET = minCC

# Source files
PARSER = parser.y
LEXER = lexer.l
AST_C = ast.c
SYMBOL_TABLE_C = symbol_table.c
MAIN_C = main.c

# Generated files
PARSER_C = parser.tab.c
PARSER_H = parser.tab.h
LEXER_C = lex.yy.c

# Compiler
CC = gcc
CFLAGS = `llvm-config --cflags` -Wno-implicit-function-declaration -Wall -g
LDFLAGS = `llvm-config --ldflags --libs core` -lfl

# Default target
all: $(TARGET)

# Build final binary
$(TARGET): $(PARSER_C) $(LEXER_C) $(AST_C) $(MAIN_C)
	$(CC) $(CFLAGS) -o $(TARGET) $(PARSER_C) $(LEXER_C) $(AST_C) $(SYMBOL_TABLE_C) $(MAIN_C) $(LDFLAGS)

# Generate parser source/header
$(PARSER_C) $(PARSER_H): $(PARSER)
	bison -d $(PARSER)

# Generate lexer source
$(LEXER_C): $(LEXER)
	flex $(LEXER)

# Clean generated files
clean:
	rm -f $(TARGET) $(PARSER_C) $(PARSER_H) $(LEXER_C)

.PHONY: all clean

