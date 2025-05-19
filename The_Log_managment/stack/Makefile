# Define the C compiler
CC = gcc

# Define compiler flags
# -Wall: Enable all standard warnings
# -g: Include debugging information
CFLAGS = -Wall -g

# Define the target executable name
TARGET = stack

# Define the source files
SRCS = stacks.c stackmain.c

# Automatically generate object file names from source file names
OBJS = $(SRCS:.c=.o)

# Default target: build the executable
all: $(TARGET)

# Rule to link the object files into the executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(CFLAGS)

# Rule to compile .c files into .o files
# $<: the prerequisite (the .c file)
# $@: the target (the .o file)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target: remove generated files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets (targets that do not correspond to actual files)
.PHONY: all clean