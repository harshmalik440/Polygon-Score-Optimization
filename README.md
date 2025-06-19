# Polygon-Score-Optimization README

## Overview
This program processes input files containing crystal and mine data, evaluates different strategies for maximizing resource collection while minimizing losses from mines, and generates output based on the best strategy.

## Modify Input & Output File Names
- Put the input files in the input folder.
- Change the start and end variable in the main function corresponding to start and end test case.

## Code Structure
- `struct node`: Defines a crystal or mine with `x, y, val` attributes.
- `_input()`: Reads input data and initializes structures.
- `generate_stripperX()` / `generate_stripperY()`: Generates output for X/Y-based selection.
- `generateBest165()`: Computes the best 165 points selection.
- `generateWorst165()`: Computes the worst 165 points selection.

## Output Format
- The first line corresponds to the total score achieved.
- The second line is the percentage gained score with respect to total achievable score.
- The third line is the total number of edges used.
- The following lines are the set of edges formed.

## Check_Function
- This is used to check if the set of edges formed forms a correct polygon or not.

## OUTPUT_VISUALISATION
- This is used to plot the edges forming the polygon, crystals and mines.

## Dependencies
- Requires C++11 or later.
- Uses standard libraries (no external dependencies).

## Notes
- The program is optimized for large inputs with up to 10,000 x 10,000 grid space.
- The generated output includes structured boundary definitions that can be used for visualization.
- Edge cases such as overlapping points and high density of mines are handled efficiently.
