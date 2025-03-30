/*
 * visualization.c - Implementation of NSGA visualization utilities
 */

#include <stdio.h>
#include <stdlib.h>
#include "visualization.h"

/*
 * Generate data file for gnuplot
 * Format: obj1 obj2 obj3 rank
 */
void generate_visualization_data(Population *population, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        fprintf(stderr, "Error: Could not open file %s for writing\n", filename);
        return;
    }
    
    // Write header
    fprintf(fp, "# Objective1 Objective2 Objective3 Rank\n");
    
    // Write data points
    for (int i = 0; i < population->size; i++) {
        Solution *solution = &population->solutions[i];
        fprintf(fp, "%f %f %f %d\n", 
                solution->parameters[OBJ1_INDEX],
                solution->parameters[OBJ2_INDEX],
                solution->parameters[OBJ3_INDEX],
                solution->rank);
    }
    
    fclose(fp);
    printf("Data written to %s\n", filename);
    
    // Also create a CSV file for use with other visualization tools
    char csv_filename[100];
    sprintf(csv_filename, "%s.csv", filename);
    
    fp = fopen(csv_filename, "w");
    if (!fp) {
        fprintf(stderr, "Error: Could not open file %s for writing\n", csv_filename);
        return;
    }
    
    // Write CSV header
    fprintf(fp, "Objective1,Objective2,Objective3,Rank,IsParetoOptimal\n");
    
    // Write CSV data points
    for (int i = 0; i < population->size; i++) {
        Solution *solution = &population->solutions[i];
        fprintf(fp, "%f,%f,%f,%d,%d\n", 
                solution->parameters[OBJ1_INDEX],
                solution->parameters[OBJ2_INDEX],
                solution->parameters[OBJ3_INDEX],
                solution->rank,
                (solution->rank == 0) ? 1 : 0);  // Is Pareto-optimal if rank is 0
    }
    
    fclose(fp);
    printf("CSV data written to %s\n", csv_filename);
}

/*
 * Generate gnuplot script for 3D visualization
 */
void generate_gnuplot_script(const char *data_filename, const char *script_filename) {
    FILE *fp = fopen(script_filename, "w");
    if (!fp) {
        fprintf(stderr, "Error: Could not open file %s for writing\n", script_filename);
        return;
    }
    
    // Create gnuplot script
    fprintf(fp, "# Gnuplot script for visualizing NSGA results\n");
    fprintf(fp, "set title 'Fast Non-dominated Sorting - 3D Visualization'\n");
    fprintf(fp, "set xlabel 'Objective 1'\n");
    fprintf(fp, "set ylabel 'Objective 2'\n");
    fprintf(fp, "set zlabel 'Objective 3'\n");
    
    // Enable mouse rotation for 3D plots
    fprintf(fp, "set mouse\n");
    
    // Set the terminal to a graphical output
    fprintf(fp, "set term wxt size 800,600\n");
    
    // Define color palette for ranks
    fprintf(fp, "set palette defined (0 'red', 1 'green', 2 'blue', 3 'yellow', 4 'purple')\n");
    
    // Set point style
    fprintf(fp, "set style fill solid 0.5\n");
    fprintf(fp, "set pointsize 1.5\n");
    
    // Plot all solutions colored by rank
    fprintf(fp, "splot '%s' using 1:2:3:4 with points palette pt 7 ps 1.5 title 'Solutions colored by rank'", data_filename);
    
    // Plot Pareto-optimal solutions (rank 0) with a different point style and connect them with lines
    fprintf(fp, ",\\\n");
    fprintf(fp, "     '%s' using 1:2:3 with lines lt 1 lw 2 title 'Pareto Front' ", data_filename);
    
    // Add a command to pause until the user presses a key
    fprintf(fp, "\npause -1 'Press any key to continue'\n");
    
    // Create a second plot showing only Pareto-optimal solutions
    fprintf(fp, "\n# Plot showing only Pareto-optimal solutions\n");
    fprintf(fp, "set title 'Pareto-Optimal Solutions'\n");
    fprintf(fp, "splot '%s' using 1:2:3:(($4==0)?1:NaN) with points pt 7 ps 2 lc rgb 'red' title 'Pareto-Optimal Solutions'", data_filename);
    fprintf(fp, ",\\\n");
    fprintf(fp, "     '%s' using 1:2:3:(($4==0)?1:NaN) with lines lt 1 lw 2 lc rgb 'red' title 'Pareto Front'\n", data_filename);
    fprintf(fp, "pause -1 'Press any key to exit'\n");
    
    fclose(fp);
    printf("Gnuplot script written to %s\n", script_filename);
}

/*
 * Generate HTML visualization with Plotly
 */
void generate_html_visualization(Population *population, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        fprintf(stderr, "Error: Could not open file %s for writing\n", filename);
        return;
    }
    
    // Write HTML header
    fprintf(fp, "<!DOCTYPE html>\n");
    fprintf(fp, "<html>\n");
    fprintf(fp, "<head>\n");
    fprintf(fp, "    <title>NSGA Visualization</title>\n");
    fprintf(fp, "    <script src='https://cdn.plot.ly/plotly-latest.min.js'></script>\n");
    fprintf(fp, "    <style>\n");
    fprintf(fp, "        body { font-family: Arial, sans-serif; margin: 20px; }\n");
    fprintf(fp, "        .controls { margin: 20px 0; }\n");
    fprintf(fp, "        button { padding: 10px; margin-right: 10px; cursor: pointer; }\n");
    fprintf(fp, "    </style>\n");
    fprintf(fp, "</head>\n");
    fprintf(fp, "<body>\n");
    fprintf(fp, "    <h1>Fast Non-dominated Sorting - 3D Visualization</h1>\n");
    fprintf(fp, "    <div class='controls'>\n");
    fprintf(fp, "        <button id='btnAllSolutions'>Show All Solutions</button>\n");
    fprintf(fp, "        <button id='btnParetoOnly'>Show Pareto-Optimal Only</button>\n");
    fprintf(fp, "        <button id='btnToggleSurface'>Toggle Pareto Surface</button>\n");
    fprintf(fp, "    </div>\n");
    fprintf(fp, "    <div id='plot' style='width:900px;height:700px;'></div>\n");
    fprintf(fp, "    <script>\n");
    
    // Generate x, y, z arrays for each rank
    fprintf(fp, "        // Data arrays\n");
    
    // Count maximum rank
    int max_rank = 0;
    for (int i = 0; i < population->size; i++) {
        if (population->solutions[i].rank > max_rank) {
            max_rank = population->solutions[i].rank;
        }
    }
    
    // Create arrays for each rank
    for (int rank = 0; rank <= max_rank; rank++) {
        fprintf(fp, "        var x_rank%d = [", rank);
        int first = 1;
        for (int i = 0; i < population->size; i++) {
            Solution *solution = &population->solutions[i];
            if (solution->rank == rank) {
                if (!first) fprintf(fp, ", ");
                fprintf(fp, "%f", solution->parameters[OBJ1_INDEX]);
                first = 0;
            }
        }
        fprintf(fp, "];\n");
        
        fprintf(fp, "        var y_rank%d = [", rank);
        first = 1;
        for (int i = 0; i < population->size; i++) {
            Solution *solution = &population->solutions[i];
            if (solution->rank == rank) {
                if (!first) fprintf(fp, ", ");
                fprintf(fp, "%f", solution->parameters[OBJ2_INDEX]);
                first = 0;
            }
        }
        fprintf(fp, "];\n");
        
        fprintf(fp, "        var z_rank%d = [", rank);
        first = 1;
        for (int i = 0; i < population->size; i++) {
            Solution *solution = &population->solutions[i];
            if (solution->rank == rank) {
                if (!first) fprintf(fp, ", ");
                fprintf(fp, "%f", solution->parameters[OBJ3_INDEX]);
                first = 0;
            }
        }
        fprintf(fp, "];\n");
    }
    
    // Create traces for all ranks
    fprintf(fp, "        // Create traces for each rank\n");
    fprintf(fp, "        var allTraces = [];\n");
    const char *colors[] = {"rgb(255,0,0)", "rgb(0,255,0)", "rgb(0,0,255)", "rgb(255,255,0)", "rgb(255,0,255)", "rgb(0,255,255)", "rgb(128,0,0)", "rgb(0,128,0)", "rgb(0,0,128)", "rgb(128,128,0)"};
    
    for (int rank = 0; rank <= max_rank; rank++) {
        const char *color = colors[rank % 10];
        // Use a brighter color and larger size for Pareto-optimal solutions (rank 0)
        if (rank == 0) {
            fprintf(fp, "        var paretoTrace = {\n");
            fprintf(fp, "            x: x_rank0,\n");
            fprintf(fp, "            y: y_rank0,\n");
            fprintf(fp, "            z: z_rank0,\n");
            fprintf(fp, "            mode: 'markers',\n");
            fprintf(fp, "            type: 'scatter3d',\n");
            fprintf(fp, "            marker: {\n");
            fprintf(fp, "                size: 8,\n");
            fprintf(fp, "                color: 'rgb(255,0,0)',\n");
            fprintf(fp, "                line: { color: 'rgb(0,0,0)', width: 1 }\n");
            fprintf(fp, "            },\n");
            fprintf(fp, "            name: 'Pareto-Optimal (Rank 0)'\n");
            fprintf(fp, "        };\n");
            fprintf(fp, "        allTraces.push(paretoTrace);\n");
        } else {
            fprintf(fp, "        var trace_rank%d = {\n", rank);
            fprintf(fp, "            x: x_rank%d,\n", rank);
            fprintf(fp, "            y: y_rank%d,\n", rank);
            fprintf(fp, "            z: z_rank%d,\n", rank);
            fprintf(fp, "            mode: 'markers',\n");
            fprintf(fp, "            type: 'scatter3d',\n");
            fprintf(fp, "            marker: {\n");
            fprintf(fp, "                size: 5,\n");
            fprintf(fp, "                color: '%s',\n", color);
            fprintf(fp, "                opacity: 0.7\n");
            fprintf(fp, "            },\n");
            fprintf(fp, "            name: 'Rank %d'\n", rank);
            fprintf(fp, "        };\n");
            fprintf(fp, "        allTraces.push(trace_rank%d);\n", rank);
        }
    }
    
    // Create Pareto front surface trace using Delaunay triangulation
    fprintf(fp, "        // Create Pareto surface\n");
    fprintf(fp, "        var surfaceTrace = {\n");
    fprintf(fp, "            x: x_rank0,\n");
    fprintf(fp, "            y: y_rank0,\n");
    fprintf(fp, "            z: z_rank0,\n");
    fprintf(fp, "            type: 'mesh3d',\n");
    fprintf(fp, "            opacity: 0.7,\n");
    fprintf(fp, "            color: 'rgb(255,0,0)',\n");
    fprintf(fp, "            name: 'Pareto Surface',\n");
    fprintf(fp, "            visible: false\n");
    fprintf(fp, "        };\n");
    fprintf(fp, "        \n");
    
    // Pareto front line trace - connects points to show the front
    fprintf(fp, "        // Create Pareto front line trace\n");
    fprintf(fp, "        var lineTrace = {\n");
    fprintf(fp, "            x: x_rank0,\n");
    fprintf(fp, "            y: y_rank0,\n");
    fprintf(fp, "            z: z_rank0,\n");
    fprintf(fp, "            type: 'scatter3d',\n");
    fprintf(fp, "            mode: 'lines',\n");
    fprintf(fp, "            line: {\n");
    fprintf(fp, "                color: 'rgb(255,0,0)',\n");
    fprintf(fp, "                width: 4\n");
    fprintf(fp, "            },\n");
    fprintf(fp, "            name: 'Pareto Front'\n");
    fprintf(fp, "        };\n");
    fprintf(fp, "        allTraces.push(lineTrace);\n");
    fprintf(fp, "        allTraces.push(surfaceTrace);\n");
    
    // Layout
    fprintf(fp, "        var layout = {\n");
    fprintf(fp, "            title: '3D Visualization of Solutions with Pareto Front',\n");
    fprintf(fp, "            scene: {\n");
    fprintf(fp, "                xaxis: {title: 'Objective 1'},\n");
    fprintf(fp, "                yaxis: {title: 'Objective 2'},\n");
    fprintf(fp, "                zaxis: {title: 'Objective 3'}\n");
    fprintf(fp, "            },\n");
    fprintf(fp, "            margin: {l: 0, r: 0, b: 0, t: 30},\n");
    fprintf(fp, "            legend: {x: 0, y: 1}\n");
    fprintf(fp, "        };\n");
    
    // Create initial plot with all solutions
    fprintf(fp, "        Plotly.newPlot('plot', allTraces, layout);\n");
    
    // Add button event handlers
    fprintf(fp, "        // Button event handlers\n");
    fprintf(fp, "        document.getElementById('btnAllSolutions').addEventListener('click', function() {\n");
    fprintf(fp, "            Plotly.newPlot('plot', allTraces, layout);\n");
    fprintf(fp, "        });\n");
    
    fprintf(fp, "        document.getElementById('btnParetoOnly').addEventListener('click', function() {\n");
    fprintf(fp, "            var paretoTraces = allTraces.filter(trace => \n");
    fprintf(fp, "                trace.name === 'Pareto-Optimal (Rank 0)' || \n");
    fprintf(fp, "                trace.name === 'Pareto Front');\n");
    fprintf(fp, "            Plotly.newPlot('plot', paretoTraces, layout);\n");
    fprintf(fp, "        });\n");
    
    fprintf(fp, "        document.getElementById('btnToggleSurface').addEventListener('click', function() {\n");
    fprintf(fp, "            surfaceTrace.visible = !surfaceTrace.visible;\n");
    fprintf(fp, "            Plotly.update('plot', {visible: [surfaceTrace.visible]}, {}, [allTraces.length - 1]);\n");
    fprintf(fp, "        });\n");
    
    // End script and HTML
    fprintf(fp, "    </script>\n");
    fprintf(fp, "</body>\n");
    fprintf(fp, "</html>\n");
    
    fclose(fp);
    printf("HTML visualization written to %s\n", filename);
    printf("Open this file in a web browser to view the interactive 3D visualization.\n");
    printf("Use the buttons to show all solutions, Pareto-optimal solutions only, or toggle the Pareto surface.\n");
}

/*
 * Run visualization
 */
void visualize_population(Population *population) {
    const char *data_file = "nsga_data.txt";
    const char *script_file = "nsga_plot.gp";
    const char *html_file = "nsga_visualization.html";
    
    // Generate data file
    generate_visualization_data(population, data_file);
    
    // Generate gnuplot script
    generate_gnuplot_script(data_file, script_file);
    
    // Generate HTML visualization
    generate_html_visualization(population, html_file);
    
    // Try to execute gnuplot script if available
    printf("Checking for gnuplot availability...\n");
    FILE *fp = popen("command -v gnuplot", "r");
    if (fp != NULL) {
        char path[1024];
        if (fgets(path, sizeof(path), fp) != NULL) {
            printf("Gnuplot found. Running visualization...\n");
            char cmd[100];
            sprintf(cmd, "gnuplot %s", script_file);
            system(cmd);
        } else {
            printf("Gnuplot not found. To visualize data:\n");
            printf("1. Install gnuplot and run: gnuplot %s\n", script_file);
            printf("2. Or open %s in a web browser for interactive visualization\n", html_file);
            printf("3. Or use the CSV file %s.csv with your preferred visualization tool\n", data_file);
        }
        pclose(fp);
    }
} 