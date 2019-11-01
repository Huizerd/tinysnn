#pragma once

#include <stdbool.h>
#include <stdlib.h>

// Convert boolean spikes to float
void *convert_array(void *x);

// 1D array compare
void compare_array_1d(void const *x, void const *y, bool *result, size_t const size,
                      char const *op);

// View (connection-type fold)
void *view_array(void *x, int const *shape);

// Sum dimension (neuron-type fold)
void *sum_dimension(void *x, int const dim);

// Copy array (for weights)
void *copy_array(void const *x);

// Print 1D array
void print_array_1d(void const *x, size_t const size);
