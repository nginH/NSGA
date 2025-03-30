/*
 * main.c - Demonstration of Fast Non-Dominated Sorting algorithm
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "nsga.h"
#include "visualization.h"

/* Initialize population with a more interesting distribution for visualization */
Population* initialize_population_for_visualization(int size) {
    Population *population = (Population*)malloc(sizeof(Population));
    population->size = size;
    population->solutions = (Solution*)malloc(size * sizeof(Solution));
    
    // Initialize solutions with a mix of random values
    // This will create a more interesting Pareto front for visualization
    for (int i = 0; i < size; i++) {
        Solution *solution = &population->solutions[i];
        
        // Create trade-offs between objectives 1, 2, and 3
        double t = (double)i / size;  // Parameter between 0 and 1
        
        // Add some offset to make multiple fronts
        double front_offset = (i % 4) * 3.0;  // Creates 4 distinct fronts with clearer separation
        
        // First three parameters (objectives) have trade-offs
        // For minimization, smaller values are better
        solution->parameters[0] = 10.0 * t + ((double)rand() / RAND_MAX - 0.5) * 0.5 + front_offset;
        solution->parameters[1] = 10.0 * (1.0 - t) + ((double)rand() / RAND_MAX - 0.5) * 0.5 + front_offset;
        solution->parameters[2] = 5.0 * sin(t * 3.14159) + ((double)rand() / RAND_MAX - 0.5) * 0.5 + front_offset;
        
        // Remaining parameters are random
        for (int j = 3; j < NUM_PARAMETERS; j++) {
            solution->parameters[j] = ((double)rand() / RAND_MAX) * 10.0;
        }
        
        solution->domination_count = 0;
        solution->dominated_solutions = NULL;
        solution->dominated_count = 0;
        solution->rank = -1;
    }
    
    return population;
}

int main() {
    // Seed random number generator
    srand((unsigned int)time(NULL));
    
    // Define population size
    const int POP_SIZE = 100;  // Increased for better visualization
    
    // Initialize population with more interesting distribution for visualization
    printf("Initializing population with %d solutions...\n", POP_SIZE);
    Population *population = initialize_population_for_visualization(POP_SIZE);
    
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
    
    // Visualize the population
    printf("\nGenerating 3D visualization (first 3 objectives)...\n");
    visualize_population(population);
    
    // Free memory
    free_population(population);
    
    return 0;
} 