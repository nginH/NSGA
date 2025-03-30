# NSGA 3D Visualization

## Overview
This interactive visualization demonstrates the Non-dominated Sorting Genetic Algorithm (NSGA) results in 3D space. It shows different ranks of solutions with emphasis on the Pareto-optimal front (Rank 0).

## Features
- **Interactive 3D visualization** of multi-objective optimization results
- **Color-coded solution ranks** (Rank 0-4)
- **Toggle controls** to:
  - View all solutions across different ranks
  - Focus only on Pareto-optimal solutions
  - Show/hide the Pareto surface

## Preview
![NSGA Visualization Preview](https://placeholder-for-your-screenshot.png)

## Usage

### Option 1: Direct HTML Opening
Simply open the `nsga_visualization.html` file in any modern web browser. No server required.

### Option 2: Hosting
For sharing with others, you can:
1. Host on GitHub Pages
2. Use a static site hosting service like Netlify or Vercel
3. Deploy on any web server

## Implementation Details
- Built using Plotly.js for 3D visualization
- Demonstrates non-dominated sorting with 5 ranks of solutions
- Highlights the Pareto front with both points and connecting lines
- Optional mesh surface visualization of the Pareto front

## Understanding the Visualization
- **Red points (Rank 0)**: Pareto-optimal solutions
- **Green points (Rank 1)**: Solutions dominated only by Rank 0
- **Blue points (Rank 2)**: Solutions dominated by Ranks 0 and 1
- **Yellow points (Rank 3)**: Solutions dominated by Ranks 0, 1, and 2
- **Purple points (Rank 4)**: Solutions dominated by all previous ranks

The visualization helps understand the trade-offs between three conflicting objectives in the solution space.

## Customization
You can modify the data arrays in the JavaScript section to visualize your own multi-objective optimization results.

## Requirements
- Any modern web browser with JavaScript enabled
- Internet connection (to load the Plotly.js library from CDN)