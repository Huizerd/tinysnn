#include "Neuron.h"
#include "functional.h"

#include <stdio.h>

// Test neuron forward functions
int main() {
  // Neuron layer size
  int const size = 2;

  // Build neuron
  Neuron n = build_neuron(size);
  // Init neuron
  init_neuron(&n);
  // Set input to neuron
  for (int i = 0; i < size; i++) {
    n.x[i] = i * 4.0f + 0.5f;
  }

  // Print neuron parameters
  printf("Neuron type: %d\n", n.type);
  printf("Input:\n");
  print_array_1d(n.size, n.x);
  printf("Voltage:\n");
  print_array_1d(n.size, n.v);
  printf("Threshold:\n");
  print_array_1d(n.size, n.th);
  printf("Spikes:\n");
  print_array_1d_bool(n.size, n.s);
  printf("Trace:\n");
  print_array_1d(n.size, n.t);
  printf("Addition constants: %.2f, %.2f, %.2f\n", n.a_v, n.a_th, n.a_t);
  printf("Decay constants: %.2f, %.2f, %.2f\n", n.d_v, n.d_th, n.d_t);
  printf("Reset constants: %.2f, %.2f\n", n.v_rest, n.th_rest);
  printf("\n");

  // Forward neuron
  forward_neuron(&n);

  // Print inputs
  printf("Inputs:\n");
  print_array_1d(n.size, n.x);
  // Print voltage
  printf("Volts:\n");
  print_array_1d(n.size, n.v);
  // Print spikes
  printf("Spikes:\n");
  print_array_1d_bool(n.size, n.s);
  // Print trace
  printf("Trace:\n");
  print_array_1d(n.size, n.t);

  // Free neuron memory again
  free_neuron(&n);

  return 0;
}