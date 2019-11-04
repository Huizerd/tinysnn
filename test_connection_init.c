#include "Connection.h"
#include "functional.h"

#include <stdio.h>

// Test connection initialization functions
int main() {
  // File containing weights
  char const weight_path[] = "test_connection_weights.txt";
  // Connection shape: (post, pre) neurons
  int const post = 2;
  int const pre = 4;

  // Build connection
  Connection c = build_connection(post, pre);
  // Init connection
  reset_connection(&c);

  // Print connection weights before loading
  printf("Connection weights:\n");
  print_array_2d(post, pre, c.w);

  // Load connection weights
  load_connection(&c, weight_path);

  // Print connection weights after loading
  printf("Connection weights:\n");
  print_array_2d(post, pre, c.w);

  // Free connection memory again
  free_connection(&c);

  return 0;
}