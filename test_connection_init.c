#include "Connection.h"
#include "functional.h"

// Header file containing parameters
#include "param/test_connection_conf.h"

#include <stdio.h>

// Test connection initialization functions
int main() {
  // Connection shape: (post, pre) neurons
  int const post = 2;
  int const pre = 4;

  // Build connection
  Connection c = build_connection(post, pre);
  // Init connection
  init_connection(&c);

  // Print connection weights before loading
  printf("Connection weights:\n");
  // TODO: is actually 1D array but still works, why?
  print_array_2d(post, pre, c.w);

  // Load connection weights from header
  load_connection_from_header(&c, &conf);
  reset_connection(&c); // does nothing

  // Print connection weights after header loading
  printf("\nHeader loading\n\n");
  printf("Connection weights:\n");
  print_array_2d(post, pre, c.w);

  // Free connection memory again
  free_connection(&c);

  return 0;
}