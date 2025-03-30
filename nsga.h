/*
 * nsga.h - Header file for Fast Non-Dominated Sorting implementation
 */

#ifndef NSGA_H
#define NSGA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_PARAMETERS 30  /* Number of parameters/objectives for each solution */
#define MAX_POPULATION 100 /* Maximum population size */

/* Structure to represent a solution with its parameters and dominance information */
typedef struct {
    double parameters[NUM_PARAMETERS];  /* The objective values */
    int domination_count;               /* Number of solutions that dominate this solution */
    int *dominated_solutions;           /* Array of indices of solutions dominated by this solution */
    int dominated_count;                /* Number of solutions dominated by this solution */
    int rank;                           /* Non-domination rank */
} Solution;

/* Structure to represent a population of solutions */
typedef struct {
    Solution *solutions;                /* Array of solutions */
    int size;                           /* Number of solutions in the population */
} Population;

/* Function prototypes */
bool dominates(Solution *solution1, Solution *solution2);
void fast_nondominated_sort(Population *population);
void free_population(Population *population);

/* Utility functions */
Population* initialize_population(int size);
void print_population(Population *population);

#endif /* NSGA_H */ 