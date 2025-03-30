# Fast Non-dominated Sorting Genetic Algorithm (NSGA) Implementation

An efficient C implementation of the Fast Non-dominated Sorting algorithm with interactive 3D visualization capabilities.

## Live Demo
**[View the Interactive 3D Visualization](https://nsga.busbuddy-aus.in/nsga_visualization)**

[![Live Demo](https://via.placeholder.com/600x300)](https://nsga.busbuddy-aus.in/nsga_visualization)

## Overview

This project implements the Fast Non-dominated Sorting algorithm, a key component of NSGA-II (Non-dominated Sorting Genetic Algorithm II), which is widely used in multi-objective optimization. The implementation includes:

1. Core algorithm for fast non-dominated sorting
2. Population generation with customizable parameters
3. Multiple visualization options:
   - Interactive 3D visualization using Plotly.js
   - Gnuplot scripts for static visualizations
   - CSV export for custom analysis

## Algorithm Explanation

### Fast Non-dominated Sorting

The Fast Non-dominated Sorting algorithm classifies solutions in a population into different fronts (ranks) based on dominance relationships:

1. **Dominance**: A solution dominates another if it's not worse in any objective and better in at least one objective.
2. **Pareto Front**: The set of non-dominated solutions (Rank 0).
3. **Sorting Process**:
   - For each solution, determine which solutions it dominates and which solutions dominate it
   - Solutions not dominated by any other become the first front (Rank 0)
   - For subsequent ranks, consider solutions dominated only by solutions in previous fronts

The time complexity is O(MN²), where M is the number of objectives and N is the population size, making it efficient for moderate-sized populations.

## Code Structure

- **nsga.h/.c**: Core implementation of the Fast Non-dominated Sorting algorithm
- **visualization.h/.c**: Visualization utilities for displaying results
- **main.c**: Driver program demonstrating the algorithm with sample data
- **Makefile**: Build system for compiling and running the program

### Key Components

1. **Data Structures**:
   - `Solution`: Represents an individual solution with objectives and dominance information
   - `Population`: Collection of solutions

2. **Core Functions**:
   - `dominates()`: Determines if one solution dominates another
   - `fast_nondominated_sort()`: Performs the sorting algorithm
   - `initialize_population_for_visualization()`: Creates test data with interesting Pareto fronts

3. **Visualization Functions**:
   - `generate_visualization_data()`: Exports data for visualization
   - `generate_gnuplot_script()`: Creates Gnuplot scripts for static plots
   - `generate_html_visualization()`: Creates interactive HTML/JS visualization with Plotly

## Building and Running

### Prerequisites

- C compiler (gcc recommended)
- Make
- Web browser for HTML visualization
- Gnuplot (optional for static plots)

### Build Instructions

```bash
# Clone the repository
git clone https://github.com/yourusername/nsga.git
cd nsga

# Build the program
make

# Run the program with visualization
make run
```

The `make run` command will:
1. Compile the program
2. Run the NSGA algorithm on a sample population
3. Generate visualization files
4. Open the HTML visualization in your default browser (if available)

### Manual Execution

```bash
# Build
make

# Run
./nsga
```

After running, you'll find these visualization files:
- `nsga_data.txt`: Raw data file
- `nsga_data.txt.csv`: CSV format for spreadsheet analysis
- `nsga_plot.gp`: Gnuplot script for static visualization
- `nsga_visualization.html`: Interactive 3D visualization

## Visualization Features

The interactive 3D visualization provides several features:

1. **Color-coded ranks**: Different colors for each dominance rank
   - Red: Rank 0 (Pareto-optimal solutions)
   - Green: Rank 1
   - Blue: Rank 2
   - Yellow: Rank 3
   - Purple: Rank 4 (if available)

2. **Interactive controls**:
   - "Show All Solutions": Displays all solutions across all ranks
   - "Show Pareto-Optimal Only": Filters to show only the Pareto front (Rank 0)
   - "Toggle Pareto Surface": Shows/hides a mesh surface connecting Pareto-optimal points

3. **Interactive 3D features**:
   - Rotate, zoom, and pan the visualization
   - Hover over points to see exact values
   - Click-and-drag to rotate the view
   - Toggle visibility of specific ranks using the legend

## Customizing the Implementation

### Modifying Parameters

The number of parameters and objectives can be adjusted in `nsga.h`:

```c
#define NUM_PARAMETERS 30  /* Total number of parameters per solution */
#define NUM_OBJECTIVES 3   /* Number of objectives to optimize */
```

### Creating Your Own Problems

To use this implementation for your own multi-objective problems:

1. Define your objective functions
2. Create a custom population initialization function
3. Replace `initialize_population_for_visualization()` with your function
4. Run the algorithm to obtain the sorted population

## Understanding the Results

After running the algorithm, solutions are assigned ranks:

- **Rank 0**: Pareto-optimal solutions (not dominated by any other solution)
- **Rank 1**: Solutions dominated only by solutions in Rank 0
- **Rank 2**: Solutions dominated by solutions in Ranks 0 and/or 1
- And so on...

The visualization helps identify:
- The shape of the Pareto front
- Trade-offs between objectives
- Distribution of solutions across dominance ranks

## License

This project is released under the MIT License. See the LICENSE file for details.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.