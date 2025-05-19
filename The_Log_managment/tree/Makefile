# Makefile for the tree program

# Define the compiler to use
CC = gcc

# Define the compiler flags
# -Wall: Enable all standard warnings
# -Wextra: Enable extra warnings
# -g: Include debugging information
CFLAGS = -Wall -Wextra -g

# Define the executable name
TARGET = tree

# Define the source files
SRCS = treemain.c tree.c

# Define the object files by replacing the .c extension with .o
OBJS = $(SRCS:.c=.o)

# Default target: build the executable
all: $(TARGET)

# Rule to link the object files into the executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Rule to compile each .c file into a .o object file
# $<: the prerequisite (the .c file)
# $@: the target (the .o file)
%.o: %.c tree.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target: remove generated files
clean:
	rm -f $(OBJS) $(TARGET)

