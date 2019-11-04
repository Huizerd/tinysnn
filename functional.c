#include "functional.h"

#include <stdio.h>
#include <stdbool.h>

// View (connection-type fold)
//void *view_array(void *x, int const *shape);

// Sum second dimension (neuron-type fold)
// TODO: pointer, so shape cannot be calculated but has to be passed!
// TODO: define sum array in calling function!
// TODO: no need to return anything in this case
void
sum_2d(int const rows, int const cols, float const x[rows][cols], float sum[rows]) {
    // Loop over rows
    for (int i = 0; i < rows; i++) {
        // Loop over columns
        for (int j = 0; j < cols; j++) {
            sum[i] += x[i][j];
        }
    }
}

// Copy array (for weights)
//void *copy_array(void const *x);

// Print 1D array (as floats)
void print_array_1d(int const size, float const x[size]) {
    for (int i = 0; i < size; i++) {
        printf("%.2f ", x[i]);
    }
    printf("\n\n");
}

// Print 1D array of bools (as integers)
// Because we can't print them as floats
void print_array_1d_bool(int const size, bool const x[size]) {
    for (int i = 0; i < size; i++) {
        printf("%d ", x[i]);
    }
    printf("\n\n");
}

// Print 2D array (as floats)
void print_array_2d(int const rows, int const cols, float const x[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%.2f ", x[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
