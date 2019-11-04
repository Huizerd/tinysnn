#pragma once

#include <stdbool.h>

// Print 1D array (as floats)
void print_array_1d(int const size, float const x[size]);

// Print 1D array of bools (as integers)
// Because we can't print them as floats
void print_array_1d_bool(int const size, bool const x[size]);

// Print 2D array (as floats)
void print_array_2d(int const rows, int const cols, float const x[rows][cols]);
