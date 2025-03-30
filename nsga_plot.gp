# Gnuplot script for visualizing NSGA results
set title 'Fast Non-dominated Sorting - 3D Visualization'
set xlabel 'Objective 1'
set ylabel 'Objective 2'
set zlabel 'Objective 3'
set mouse
set term wxt size 800,600
set palette defined (0 'red', 1 'green', 2 'blue', 3 'yellow', 4 'purple')
set style fill solid 0.5
set pointsize 1.5
splot 'nsga_data.txt' using 1:2:3:4 with points palette pt 7 ps 1.5 title 'Solutions colored by rank',\
     'nsga_data.txt' using 1:2:3 with lines lt 1 lw 2 title 'Pareto Front' 
pause -1 'Press any key to continue'

# Plot showing only Pareto-optimal solutions
set title 'Pareto-Optimal Solutions'
splot 'nsga_data.txt' using 1:2:3:(($4==0)?1:NaN) with points pt 7 ps 2 lc rgb 'red' title 'Pareto-Optimal Solutions',\
     'nsga_data.txt' using 1:2:3:(($4==0)?1:NaN) with lines lt 1 lw 2 lc rgb 'red' title 'Pareto Front'
pause -1 'Press any key to exit'
