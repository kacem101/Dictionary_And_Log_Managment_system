# Define the C compiler
CC = gcc

# Define the compiler flags
# -Wall: Enable all standard warnings
# -g: Include debugging information
CFLAGS = -Wall -g

# Define the source files
SRCS = main.c linkedlist.c

# Define the object files (generated from source files)
# $(patsubst %.c,%.o,$(SRCS)) transforms .c extensions to .o
OBJS = $(patsubst %.c,%.o,$(SRCS))

# Define the name of the executable
TARGET = linkedlist_app

# Default target: build the executable
all: $(TARGET)

# Rule to link object files into the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Rule to compile .c files into .o files
# $<: The prerequisite (the .c file)
# $@: The target (the .o file)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Dependency: main.o depends on linkedlist.h (if main.c includes it)
main.o: main.c linkedlist.h

# Dependency: linkedlist.o depends on linkedlist.h
linkedlist.o: linkedlist.c linkedlist.h

# Clean target: remove generated files
clean:
	rm -f $(OBJS) $(TARGET)

