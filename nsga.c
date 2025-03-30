/*
 * nsga.c - Implementation of Fast Non-Dominated Sorting algorithm
 */

#include "nsga.h"

/*
 * Check if solution1 dominates solution2
 * Returns true if solution1 dominates solution2, false otherwise
 */
bool dominates(Solution *solution1, Solution *solution2) {
    bool at_least_one_better = false;
    
    for (int i = 0; i < NUM_PARAMETERS; i++) {
        // If solution1 is worse than solution2 in any parameter, it cannot dominate
        if (solution1->parameters[i] > solution2->parameters[i]) {
            return false;
        }
        
        // Check if solution1 is better in at least one parameter
        if (solution1->parameters[i] < solution2->parameters[i]) {
            at_least_one_better = true;
        }
    }
    
    // Solution1 dominates solution2 if it's not worse in any parameter
    // and better in at least one parameter
    return at_least_one_better;
}

/*
 * Perform fast non-dominated sorting on a population
 * Classifies solutions into different fronts (ranks)
 */
void fast_nondominated_sort(Population *population) {
    // Initialize dominance information
    for (int i = 0; i < population->size; i++) {
        Solution *p = &population->solutions[i];
        p->domination_count = 0;
        p->dominated_solutions = (int*)malloc(population->size * sizeof(int));
        p->dominated_count = 0;
    }
    
    // Determine domination relationships
    for (int i = 0; i < population->size; i++) {
        Solution *p = &population->solutions[i];
        
        for (int j = 0; j < population->size; j++) {
            if (i == j) continue;
            
            Solution *q = &population->solutions[j];
            
            if (dominates(p, q)) {
                // p dominates q, add q to the list of solutions dominated by p
                p->dominated_solutions[p->dominated_count++] = j;
            } else if (dominates(q, p)) {
                // q dominates p, increment domination count of p
                p->domination_count++;
            }
        }
    }
    
    // Find the first front (rank 0)
    int front_size = 0;
    int *current_front = (int*)malloc(population->size * sizeof(int));
    int *next_front = (int*)malloc(population->size * sizeof(int));
    
    for (int i = 0; i < population->size; i++) {
        if (population->solutions[i].domination_count == 0) {
            population->solutions[i].rank = 0;
            current_front[front_size++] = i;
        }
    }
    
    // Find subsequent fronts
    int rank = 0;
    while (front_size > 0) {
        int next_front_size = 0;
        rank++;
        
        for (int i = 0; i < front_size; i++) {
            Solution *p = &population->solutions[current_front[i]];
            
            for (int j = 0; j < p->dominated_count; j++) {
                int q_index = p->dominated_solutions[j];
                Solution *q = &population->solutions[q_index];
                
                q->domination_count--;
                
                if (q->domination_count == 0) {
                    q->rank = rank;
                    next_front[next_front_size++] = q_index;
                }
            }
        }
        
        // Swap fronts
        int *temp = current_front;
        current_front = next_front;
        next_front = temp;
        
        front_size = next_front_size;
    }
    
    // Free allocated memory
    free(current_front);
    free(next_front);
}

/*
 * Free memory allocated for a population
 */
void free_population(Population *population) {
    if (population == NULL) {
        return;
    }
    
    for (int i = 0; i < population->size; i++) {
        free(population->solutions[i].dominated_solutions);
    }
    
    free(population->solutions);
    free(population);
}

/*
 * Initialize a population with random values
 */
Population* initialize_population(int size) {
    Population *population = (Population*)malloc(sizeof(Population));
    population->size = size;
    population->solutions = (Solution*)malloc(size * sizeof(Solution));
    
    // Initialize solutions with random parameters
    for (int i = 0; i < size; i++) {
        Solution *solution = &population->solutions[i];
        
        for (int j = 0; j < NUM_PARAMETERS; j++) {
            solution->parameters[j] = ((double)rand() / RAND_MAX) * 10.0;
        }
        
        solution->domination_count = 0;
        solution->dominated_solutions = NULL;
        solution->dominated_count = 0;
        solution->rank = -1;
    }
    
    return population;
}

/*
 * Print the population with their parameters and ranks
 */
void print_population(Population *population) {
    printf("Population (size = %d):\n", population->size);
    
    for (int i = 0; i < population->size; i++) {
        Solution *solution = &population->solutions[i];
        
        printf("Solution %d (Rank %d):\n", i, solution->rank);
        printf("  Parameters: ");
        
        for (int j = 0; j < NUM_PARAMETERS; j++) {
            printf("%.2f ", solution->parameters[j]);
            if (j > 0 && j % 10 == 0) {
                printf("\n               ");
            }
        }
        
        printf("\n");
    }
} 