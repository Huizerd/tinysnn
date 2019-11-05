#include "Neuron.h"
#include "functional.h"

#include <stdio.h>

// Test neuron initialization functions
int main() {
  // File containing parameters
  char const param_path[] = "test_neuron_params.txt";
  // Neuron layer size
  int const size = 4;

  // Build neuron
  Neuron n = build_neuron(size);
  // Init neuron
  reset_neuron(&n);

  // Print neuron parameters before loading
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

  // Load neuron parameters
  load_neuron(&n, param_path);
  reset_neuron(&n);

  // Print neuron parameters after loading
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

  // Free neuron memory again
  free_neuron(&n);

  return 0;
}