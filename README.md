# Fast Non-dominated Sorting Implementation

This is a C implementation of the Fast Non-dominated Sorting algorithm used in multi-objective optimization problems, particularly in NSGA-II (Non-dominated Sorting Genetic Algorithm II).

## Features

- Handles solutions with 30 parameters/objectives
- Efficient implementation of the Fast Non-dominated Sorting algorithm
- Interactive 3D visualization of Pareto-optimal solutions
- Well-structured and modular code

## Building the Project

To build the project, simply run the `make` command:

```
make
```

This will compile the source code and create an executable named `nsga`.

## Running the Program

You can run the program using the `make run` command:

```
make run
```

Alternatively, you can run the executable directly:

```
./nsga
```

## Visualization

The program provides multiple ways to visualize the Pareto-optimal solutions:

### HTML/JavaScript Visualization

An interactive 3D visualization is generated in `nsga_visualization.html`. Open this file in any web browser to:
- View all solutions with Pareto-optimal solutions highlighted in red
- Toggle between showing all solutions or only Pareto-optimal solutions
- Show/hide the Pareto front surface
- Rotate, zoom, and pan the 3D visualization

### Gnuplot Visualization

If you have Gnuplot installed, the program can generate a 3D plot with the Pareto front:

```
gnuplot nsga_plot.gp
```

### CSV Export

For custom visualization in other tools (Excel, R, Python, etc.), the program exports:
- `nsga_data.txt.csv`: Contains all solutions with columns for each objective and Pareto-optimality

## Cleaning Up

To clean up object files and the executable, use:

```
make clean
```

## Code Structure

- `nsga.h`: Header file with data structures and function prototypes
- `nsga.c`: Implementation of the Fast Non-dominated Sorting algorithm
- `main.c`: Main program demonstrating the algorithm
- `visualization.h`: Header file for visualization components
- `visualization.c`: Implementation of visualization features
- `Makefile`: Build system configuration

## Algorithm

The Fast Non-dominated Sorting algorithm works as follows:

1. For each solution in the population, determine which solutions it dominates and which solutions dominate it
2. Identify solutions that are not dominated by any other solution (rank 0) - these form the Pareto-optimal set
3. Iteratively identify subsequent ranks by removing solutions from consideration

A solution dominates another solution if it is not worse in any objective and better in at least one objective.

## Pareto-Optimal Solutions

The visualization highlights the Pareto-optimal solutions (rank 0) which represent the best trade-offs between the competing objectives. These solutions form what is known as the Pareto front - the set of solutions where no objective can be improved without degrading at least one other objective. 