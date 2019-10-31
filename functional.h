#pragma once

// Convert boolean spikes to float
void *convert_array(void *x);

// Array compare
// Pointer for operator here because array of char?
bool *compare_array(void const *x, void const *y, char const *op);

// View (connection-type fold)
void *view_array(void *x, int const shape);

// Sum dimension (neuron-type fold)
void *sum_dimension(void *x, int const dim);

// Copy array (for weights)
void *copy_array(void const *x);
