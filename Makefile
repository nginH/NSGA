# Makefile for Fast Non-dominated Sort
CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -lm

# Target executable name
TARGET = nsga

# Object files
OBJS = main.o nsga.o

# Default target
all: $(TARGET)

# Link the object files to build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compile source files into object files
main.o: main.c nsga.h
	$(CC) $(CFLAGS) -c $<

nsga.o: nsga.c nsga.h
	$(CC) $(CFLAGS) -c $<

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean up object files and executable
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all run clean 