# Makefile for Smart Public Transport Reservation System
# Author: Data Structures Project
# Description: Automated compilation script for the transport system

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g -std=c99
LDFLAGS = 

# Target executable name
TARGET = transport_system

# Source files
SOURCES = queue_operations.c \
          linkedlist_operations.c \
          graph_operations.c \
          search_operations.c \
          utility_functions.c \
          main_program.c

# Object files (replace .c with .o)
OBJECTS = $(SOURCES:.c=.o)

# Header files
HEADERS = transport_system.h

# Default target - builds the executable
all: $(TARGET)
	@echo "==================================="
	@echo "Build completed successfully!"
	@echo "Run with: ./$(TARGET)"
	@echo "==================================="

# Link object files to create executable
$(TARGET): $(OBJECTS)
	@echo "Linking object files..."
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(TARGET)
	@echo "Executable '$(TARGET)' created."

# Compile source files to object files
%.o: %.c $(HEADERS)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	@echo "Cleaning build files..."
	rm -f $(OBJECTS) $(TARGET)
	@echo "Clean completed."

# Remove only object files, keep executable
clean-obj:
	@echo "Removing object files..."
	rm -f $(OBJECTS)
	@echo "Object files removed."

# Rebuild everything from scratch
rebuild: clean all

# Run the program after building
run: $(TARGET)
	@echo "Running $(TARGET)..."
	@echo ""
	./$(TARGET)

# Display help information
help:
	@echo "Smart Transport System - Makefile Help"
	@echo "======================================="
	@echo ""
	@echo "Available targets:"
	@echo "  make          - Build the project (default)"
	@echo "  make all      - Same as 'make'"
	@echo "  make clean    - Remove all build files"
	@echo "  make clean-obj - Remove only object files"
	@echo "  make rebuild  - Clean and rebuild everything"
	@echo "  make run      - Build and run the program"
	@echo "  make help     - Display this help message"
	@echo ""
	@echo "Files compiled:"
	@echo "  $(SOURCES)"
	@echo ""

# Check coding style (if indent is available)
check-style:
	@echo "Checking code style..."
	@which indent > /dev/null && indent -kr -i4 *.c || echo "indent not installed"

# Create a distribution archive
dist: clean
	@echo "Creating distribution archive..."
	tar -czf transport_system.tar.gz *.c *.h Makefile README.md
	@echo "Archive created: transport_system.tar.gz"

# Debug build with extra symbols
debug: CFLAGS += -DDEBUG -O0
debug: clean $(TARGET)
	@echo "Debug build completed."

# Release build with optimizations
release: CFLAGS += -O2 -DNDEBUG
release: clean $(TARGET)
	@echo "Release build completed."

# Phony targets (not actual files)
.PHONY: all clean clean-obj rebuild run help check-style dist debug release