# Define the C compiler
CC = gcc

# Define compiler flags
# -Wall: Enable all common compiler warnings
# -Wextra: Enable extra compiler warnings
# -g: Include debugging information
CFLAGS = -Wall -Wextra -g

# Define the source files
SRCS = mainqueue.c queue.c

# Define the object files (generated from source files)
# The patsubst function substitutes the suffix .c with .o
OBJS = $(patsubst %.c,%.o,$(SRCS))

# Define the name of the executable
EXEC = queue_app

# Default target: build the executable
# This target depends on the object files
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

# Rule to compile C source files into object files
# This is a pattern rule that applies to any .c file
# $<: the prerequisite (the .c file)
# $@: the target (the .o file)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target: remove generated files
# .PHONY is used to declare targets that are not actual files
.PHONY: clean
clean:
	rm -f $(OBJS) $(EXEC)

