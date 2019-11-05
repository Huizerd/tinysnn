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
  reset_neuron(&n);
  // Set input to neuron
  for (int i = 0; i < size; i++) {
    n.x[i] = i * 4.0f + 0.5f;
  }

  // Print neuron parameters
  printf("Neuron type: %d\n", n.type);
  printf("Input [0]: %.2f\n", n.x[0]);
  printf("Voltage [0]: %.2f\n", n.v[0]);
  printf("Threshold [0]: %.2f\n", n.th[0]);
  printf("Spikes [0]: %d\n", n.s[0]);
  printf("Trace [0]: %.2f\n", n.t[0]);
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