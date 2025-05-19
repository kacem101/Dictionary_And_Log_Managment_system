# Makefile for the Dictionary project

# Define the compiler to use
CC = gcc

# Define the compiler flags
# -Wall: Enable all standard warnings
# -Wextra: Enable extra warnings
# -g: Include debugging information for debugging
# -Wno-unused-variable: Disable warnings about unused variables
CFLAGS = -Wall -Wextra -g -Wno-unused-variable

# Define the executable name
TARGET = dictionary

# Define the source files
SRCS = dictionarymain.c dictionary.c

# Define the object files by replacing the .c extension with .o
OBJS = $(SRCS:.c=.o)

# Default target: build the executable
all: $(TARGET)

# Rule to link the object files into the executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Rule to compile each .c file into a .o object file
# This rule specifies that each .o file depends on the corresponding .c file and the header file.
# $<: the first prerequisite (the .c file)
# $@: the target (the .o file)
%.o: %.c dictionary.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target: remove generated files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets: .PHONY tells make that 'all' and 'clean' are not actual files.
.PHONY: all clean
