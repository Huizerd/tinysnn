#include "Network.h"
#include "functional.h"

#include <stdio.h>

// Test network initialization functions
int main() {
  // File containing parameters
  char const param_path[] = "param/test_network_params.txt";
  // Network layer sizes
  int const in_size = 2;
  int const hid_size = 4;
  int const out_size = 1;

  // Build network
  Network net = build_network(in_size, hid_size, out_size);
  // Init network
  init_network(&net);

  // Print network parameters before loading
  print_network(&net);

  // Load network parameters
  load_network(&net, param_path);
  reset_network(&net);

  // Print network parameters after loading
  print_network(&net);

  // Free network memory again
  free_network(&net);

  return 0;
}