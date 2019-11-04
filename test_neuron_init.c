#include "Neuron.h"

#include <stdio.h>

// Test neuron initialization functions
int main() {
  // File containing parameters
  char const param_path[] = "test_neuron_param.txt";
  // Neuron layer size
  int const size = 4;

  // Build neuron
  Neuron n = build_neuron(size);
  // Init neuron
  reset_neuron(&n);

  // Print neuron parameters before loading
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

  // Load neuron parameters
  load_neuron(&n, param_path);

  // Print neuron parameters after loading
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

  // Free neuron memory again
  free_neuron(&n);

  return 0;
}