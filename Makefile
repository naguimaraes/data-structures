# Makefile for Data Structures Comparison Project
# Authors: Ian Kersz Amaral & Nathan Alonso Guimarães
# UFRGS 2022/1

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
LDFLAGS = -lm

# Target executable
TARGET = data-structures.exe

# Source files
SOURCES = main.c \
          include/files.c \
          include/trees.c \
          include/types.c \
          structures/ABP.c \
          structures/AVL.c \
          structures/LSE.c \
          structures/Splay.c \
          structures/RN.c

# Include directories
INCLUDES = -I include -I structures -I output

# Default target
all: $(TARGET)

# Create target executable
$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(INCLUDES) $(SOURCES) -o $@ $(LDFLAGS)

# Clean build files
clean:
	rm -f $(TARGET)

# Run the program with default parameters
run: $(TARGET) run-shuffled run-sorted

# Run with shuffled data
run-shuffled: $(TARGET)
	@echo "\nRunning with shuffled data..."
	./$(TARGET) data/1000Shuffled.csv data/day1.csv output/output_shuffled.txt

# Run with sorted data  
run-sorted: $(TARGET)
	@echo "\nRunning with sorted data..."
	./$(TARGET) data/1000Sorted.csv data/day1.csv output/output_sorted.txt

# Help target
help:
	@echo "Available targets:"
	@echo "  make         - Build the project (default)"
	@echo "  make run     - Run with default parameters"
	@echo "    make run-shuffled - Run with shuffled data"
	@echo "    make run-sorted   - Run with sorted data"
	@echo "  make clean   - Remove all built files"
	@echo "  make help    - Show available targets"

# Declare phony targets
.PHONY: all clean run run-shuffled run-sorted help
