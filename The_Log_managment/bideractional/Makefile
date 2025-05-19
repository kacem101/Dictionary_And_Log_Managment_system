# Define the C compiler
CC = gcc

# Define compiler flags
# -Wall: Enable all standard warnings
# -g: Include debugging information
CFLAGS = -Wall -g

# Define linker flags (if any libraries are needed, add them here)
LDFLAGS =

# Define the name of the executable
TARGET = my_program

# Define the source files
SRCS = main1.c bilist.c

# Define the object files (automatically generated from source files)
OBJS = $(SRCS:.c=.o)

# Default target: build the executable
all: $(TARGET)

# Rule to link object files into the executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)

# Rule to compile .c files into .o files
# $<: the prerequisite (the .c file)
# $@: the target (the .o file)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Dependency: main1.o depends on bilist.h (if main1.c includes bilist.h)
# You might need to add other dependencies here if your files include each other
main1.o: main1.c bilist.h

# Dependency: bilist.o depends on bilist.h
bilist.o: bilist.c bilist.h

# Clean rule: remove generated files
clean:
	rm -f $(OBJS) $(TARGET)

