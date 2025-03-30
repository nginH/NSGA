/*
 * visualization.h - Header file for NSGA visualization utilities
 */

#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include "nsga.h"

/* Indices of parameters to use as objectives for visualization (out of 30) */
#define OBJ1_INDEX 0
#define OBJ2_INDEX 1
#define OBJ3_INDEX 2

/* Function to generate data file for gnuplot */
void generate_visualization_data(Population *population, const char *filename);

/* Function to generate gnuplot script for 3D visualization */
void generate_gnuplot_script(const char *data_filename, const char *script_filename);

/* Function to generate HTML visualization with Plotly */
void generate_html_visualization(Population *population, const char *filename);

/* Function to run visualization */
void visualize_population(Population *population);

#endif /* VISUALIZATION_H */ 