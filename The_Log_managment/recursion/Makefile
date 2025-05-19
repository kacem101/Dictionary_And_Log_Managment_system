# Define the compiler
CC = gcc

# Define compiler flags
# -Wall enables all standard warnings
# -g includes debugging information
CFLAGS = -Wall -g

# Define the executable name
TARGET = recursion

# Define the object files
OBJ = recursionmain.o recursion.o

# Default target: builds the executable
all: $(TARGET)

# Rule to link the object files into the executable
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(CFLAGS)

# Rule to compile recursionmain.c into an object file
# Depends on recursionmain.c and recursion.h
recursionmain.o: recursionmain.c recursion.h
	$(CC) -c recursionmain.c $(CFLAGS)

# Rule to compile recursion.c into an object file
# Depends on recursion.c and recursion.h
recursion.o: recursion.c recursion.h
	$(CC) -c recursion.c $(CFLAGS)

# Clean target: removes generated files
clean:
	rm -f $(TARGET) $(OBJ)