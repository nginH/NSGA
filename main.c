/*
 * main.c - Demonstration of Fast Non-Dominated Sorting algorithm
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "nsga.h"

int main() {
    // Seed random number generator
    srand((unsigned int)time(NULL));
    
    // Define population size
    const int POP_SIZE = 20;
    
    // Initialize population with random values
    printf("Initializing population with %d solutions...\n", POP_SIZE);
    Population *population = initialize_population(POP_SIZE);
    
    // Print initial population
    printf("\nInitial Population:\n");
    print_population(population);
    
    // Perform fast non-dominated sorting
    printf("\nPerforming Fast Non-Dominated Sort...\n");
    fast_nondominated_sort(population);
    
    // Print sorted population
    printf("\nSorted Population by Rank:\n");
    print_population(population);
    
    // Count solutions in each rank
    int max_rank = 0;
    for (int i = 0; i < population->size; i++) {
        if (population->solutions[i].rank > max_rank) {
            max_rank = population->solutions[i].rank;
        }
    }
    
    // Print rank statistics
    printf("\nRank Statistics:\n");
    for (int rank = 0; rank <= max_rank; rank++) {
        int count = 0;
        for (int i = 0; i < population->size; i++) {
            if (population->solutions[i].rank == rank) {
                count++;
            }
        }
        printf("Rank %d: %d solutions\n", rank, count);
    }
    
    // Free memory
    free_population(population);
    
    return 0;
} 