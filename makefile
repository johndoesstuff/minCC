# Makefile

# Output binary name
TARGET = myparser

# Source files
PARSER = parser.y
LEXER = lexer.l

# Generated files
PARSER_C = parser.tab.c
PARSER_H = parser.tab.h
LEXER_C = lex.yy.c

# Compiler
CC = gcc
CFLAGS = -Wall

# Default target
all: $(TARGET)

# Build final binary
$(TARGET): $(PARSER_C) $(LEXER_C)
	$(CC) $(CFLAGS) -o $(TARGET) $(PARSER_C) $(LEXER_C) -lfl

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

