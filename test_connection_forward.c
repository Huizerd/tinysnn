#include "Connection.h"
#include "functional.h"

#include <stdio.h>

// Test connection forward functions
int main() {
  // Connection shape: (post, pre) neurons
  int const post = 2;
  int const pre = 4;

  // Build connection
  Connection c = build_connection(post, pre);
  // Init connection
  init_connection(&c);
  // Allocate arrays for spikes of pre neuron and inputs to post neuron
  float const s[4] = {1.0f, 0.0f, 0.0f, 1.0f};
  float x[2] = {0.0f};

  // Forward connection
  forward_connection(&c, x, s);

  // Print pre spikes
  printf("Pre spikes:\n");
  print_array_1d_bool(c.pre, s);
  // Print connection weights
  printf("Connection weights:\n");
  print_array_2d(post, pre, c.w);
  // Print post inputs
  printf("Post inputs:\n");
  print_array_1d(c.post, x);

  // Free connection memory again
  free_connection(&c);

  return 0;
}