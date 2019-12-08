#include "Network.h"
#include "functional.h"

// Header file containing parameters
#include "param/test_network_conf.h"

#include <stdio.h>

// Test network initialization functions
int main() {
  // Build network
  Network net = build_network(conf.in_size, conf.in_enc_size, conf.hid_size,
                              conf.out_size);
  // Init network
  init_network(&net);

  // Print network parameters before loading
  print_network(&net);

  // Load network parameters from header file
  load_network_from_header(&net, &conf);
  reset_network(&net);

  // Print network parameters after header loading
  printf("\nHeader loading\n\n");
  print_network(&net);

  // Free network memory again
  free_network(&net);

  return 0;
}