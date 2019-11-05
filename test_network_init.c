#include "Network.h"
#include "functional.h"

#include <stdio.h>

// Test network initialization functions
int main() {
  // File containing parameters
  char const param_path[] = "test_network_params.txt";
  // Network layer sizes
  int const in_size = 2;
  int const hid_size = 4;
  int const out_size = 1;

  // Build network
  Network net = build_network(in_size, hid_size, out_size);
  // Init network
  init_network(&net);

  // Print network parameters before loading
  // Input layer
  printf("Input layer (raw):\n");
  print_array_1d(net.in_size / 2, net.in);
  printf("Input layer (encoded):\n");
  print_array_1d(net.in_size, net.in_enc);

  // Connection input -> hidden
  printf("Connection weights input -> hidden:\n");
  print_array_2d(net.hid_size, net.in_size, net.inhid->w);

  // Hidden layer
  printf("Hidden neuron:\n");
  printf("Neuron type: %d\n", net.hid->type);
  printf("Input:\n");
  print_array_1d(net.hid_size, net.hid->x);
  printf("Voltage:\n");
  print_array_1d(net.hid_size, net.hid->v);
  printf("Threshold:\n");
  print_array_1d(net.hid_size, net.hid->th);
  printf("Spikes:\n");
  print_array_1d_bool(net.hid_size, net.hid->s);
  printf("Trace:\n");
  print_array_1d(net.hid_size, net.hid->t);
  printf("Addition constants: %.2f, %.2f, %.2f\n", net.hid->a_v, net.hid->a_th,
         net.hid->a_t);
  printf("Decay constants: %.2f, %.2f, %.2f\n", net.hid->d_v, net.hid->d_th,
         net.hid->d_t);
  printf("Reset constants: %.2f, %.2f\n", net.hid->v_rest, net.hid->th_rest);
  printf("\n");

  // Connection hidden -> output
  printf("Connection weights hidden -> output:\n");
  print_array_2d(net.out_size, net.hid_size, net.hidout->w);

  // Output layer
  printf("Output neuron:\n");
  printf("Neuron type: %d\n", net.out->type);
  printf("Input:\n");
  print_array_1d(net.out_size, net.out->x);
  printf("Voltage:\n");
  print_array_1d(net.out_size, net.out->v);
  printf("Threshold:\n");
  print_array_1d(net.out_size, net.out->th);
  printf("Spikes:\n");
  print_array_1d_bool(net.out_size, net.out->s);
  printf("Trace:\n");
  print_array_1d(net.out_size, net.out->t);
  printf("Addition constants: %.2f, %.2f, %.2f\n", net.out->a_v, net.out->a_th,
         net.out->a_t);
  printf("Decay constants: %.2f, %.2f, %.2f\n", net.out->d_v, net.out->d_th,
         net.out->d_t);
  printf("Reset constants: %.2f, %.2f\n", net.out->v_rest, net.out->th_rest);
  printf("\n");

  // Load network parameters
  load_network(&net, param_path);
  reset_network(&net);

  // Print network parameters after loading
  // Input layer
  printf("Input layer (raw):\n");
  print_array_1d(net.in_size / 2, net.in);
  printf("Input layer (encoded):\n");
  print_array_1d(net.in_size, net.in_enc);

  // Connection input -> hidden
  printf("Connection weights input -> hidden:\n");
  print_array_2d(net.hid_size, net.in_size, net.inhid->w);

  // Hidden layer
  printf("Neuron type: %d\n", net.hid->type);
  printf("Input:\n");
  print_array_1d(net.hid_size, net.hid->x);
  printf("Voltage:\n");
  print_array_1d(net.hid_size, net.hid->v);
  printf("Threshold:\n");
  print_array_1d(net.hid_size, net.hid->th);
  printf("Spikes:\n");
  print_array_1d_bool(net.hid_size, net.hid->s);
  printf("Trace:\n");
  print_array_1d(net.hid_size, net.hid->t);
  printf("Addition constants: %.2f, %.2f, %.2f\n", net.hid->a_v, net.hid->a_th,
         net.hid->a_t);
  printf("Decay constants: %.2f, %.2f, %.2f\n", net.hid->d_v, net.hid->d_th,
         net.hid->d_t);
  printf("Reset constants: %.2f, %.2f\n", net.hid->v_rest, net.hid->th_rest);
  printf("\n");

  // Connection hidden -> output
  printf("Connection weights hidden -> output:\n");
  print_array_2d(net.out_size, net.hid_size, net.hidout->w);

  // Output layer
  printf("Neuron type: %d\n", net.out->type);
  printf("Input:\n");
  print_array_1d(net.out_size, net.out->x);
  printf("Voltage:\n");
  print_array_1d(net.out_size, net.out->v);
  printf("Threshold:\n");
  print_array_1d(net.out_size, net.out->th);
  printf("Spikes:\n");
  print_array_1d_bool(net.out_size, net.out->s);
  printf("Trace:\n");
  print_array_1d(net.out_size, net.out->t);
  printf("Addition constants: %.2f, %.2f, %.2f\n", net.out->a_v, net.out->a_th,
         net.out->a_t);
  printf("Decay constants: %.2f, %.2f, %.2f\n", net.out->d_v, net.out->d_th,
         net.out->d_t);
  printf("Reset constants: %.2f, %.2f\n", net.out->v_rest, net.out->th_rest);
  printf("\n");

  // Free network memory again
  free_network(&net);

  return 0;
}