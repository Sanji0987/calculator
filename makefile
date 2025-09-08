# Makefile for GTK4 Calculator App

# Compiler
CC = gcc

# Compiler flags
CFLAGS = $(shell pkg-config --cflags gtk4) -Wall -Wextra -std=c99

# Linker flags
LIBS = $(shell pkg-config --libs gtk4)

# Target executable
TARGET = app

# Source files
SOURCES = main.c

# Object files
OBJECTS = $(SOURCES:.c=.o)

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LIBS)

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJECTS) $(TARGET)

# Install (optional - adjust paths as needed)
install: $(TARGET)
	install -m 755 $(TARGET) /usr/local/bin/

# Uninstall (optional)
uninstall:
	rm -f /usr/local/bin/$(TARGET)

# Force rebuild
rebuild: clean all

# Debug build with additional flags
debug: CFLAGS += -g -DDEBUG
debug: $(TARGET)

# Release build with optimization
release: CFLAGS += -O2 -DNDEBUG
release: $(TARGET)

# Check if GTK4 is available
check-deps:
	@pkg-config --exists gtk4 || (echo "GTK4 not found. Install libgtk-4-dev or gtk4-devel" && exit 1)
	@echo "GTK4 found: $(shell pkg-config --modversion gtk4)"

# Show help
help:
	@echo "Available targets:"
	@echo "  all      - Build the application (default)"
	@echo "  clean    - Remove build files"
	@echo "  install  - Install to /usr/local/bin"
	@echo "  uninstall- Remove from /usr/local/bin"
	@echo "  rebuild  - Clean and build"
	@echo "  debug    - Build with debug flags"
	@echo "  release  - Build with optimization"
	@echo "  check-deps - Check if GTK4 is available"
	@echo "  help     - Show this help"

# Declare phony targets
.PHONY: all clean install uninstall rebuild debug release check-deps help
