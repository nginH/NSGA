# Makefile for Fast Non-dominated Sort with Visualization
CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -lm

# Target executable name
TARGET = nsga

# Object files
OBJS = main.o nsga.o visualization.o

# Default target
all: $(TARGET)

# Link the object files to build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compile source files into object files
main.o: main.c nsga.h visualization.h
	$(CC) $(CFLAGS) -c $<

nsga.o: nsga.c nsga.h
	$(CC) $(CFLAGS) -c $<

visualization.o: visualization.c visualization.h nsga.h
	$(CC) $(CFLAGS) -c $<

# Check if gnuplot is installed
check_gnuplot:
	@command -v gnuplot >/dev/null 2>&1 || { echo "Warning: gnuplot is not installed. Alternative visualization methods will be used."; }

# Run the program
run: $(TARGET) check_gnuplot
	./$(TARGET)
	@if [ -f nsga_visualization.html ]; then \
		if command -v xdg-open >/dev/null 2>&1; then \
			xdg-open nsga_visualization.html; \
		elif command -v open >/dev/null 2>&1; then \
			open nsga_visualization.html; \
		else \
			echo "Could not find a program to open the visualization file"; \
		fi \
	fi

# Clean up object files and executable
clean:
	rm -f $(OBJS) $(TARGET) nsga_data.txt nsga_plot.gp nsga_data.txt.csv nsga_visualization.html

# Phony targets
.PHONY: all run clean check_gnuplot 