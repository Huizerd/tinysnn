#include "Neuron.h"
#include "functional.h"

// Header file containing parameters
#include "param/test_neuron_conf.h"

#include <stdio.h>

// Test neuron initialization functions
int main() {
  // Neuron layer size
  int const size = 4;

  // Build neuron
  Neuron n = build_neuron(size);
  // Init neuron
  init_neuron(&n);

  // Print neuron parameters before loading
  print_neuron(&n);

  // Load neuron parameters from header file
  load_neuron_from_header(&n, &conf);
  reset_neuron(&n);

  // Print neuron parameters after header loading
  printf("\nHeader loading\n\n");
  print_neuron(&n);

  // Free neuron memory again
  free_neuron(&n);

  return 0;
}