# Fast Non-dominated Sorting Implementation

This is a C implementation of the Fast Non-dominated Sorting algorithm used in multi-objective optimization problems, particularly in NSGA-II (Non-dominated Sorting Genetic Algorithm II).

## Features

- Handles solutions with 30 parameters/objectives
- Efficient implementation of the Fast Non-dominated Sorting algorithm
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

## Cleaning Up

To clean up object files and the executable, use:

```
make clean
```

## Code Structure

- `nsga.h`: Header file with data structures and function prototypes
- `nsga.c`: Implementation of the Fast Non-dominated Sorting algorithm
- `main.c`: Main program demonstrating the algorithm
- `Makefile`: Build system configuration

## Algorithm

The Fast Non-dominated Sorting algorithm works as follows:

1. For each solution in the population, determine which solutions it dominates and which solutions dominate it
2. Identify solutions that are not dominated by any other solution (rank 0)
3. Iteratively identify subsequent ranks by removing solutions from consideration

A solution dominates another solution if it is not worse in any objective and better in at least one objective. 