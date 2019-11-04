#pragma once

#include <stdbool.h>

typedef struct {
  // Connection shape: (post, pre)
  int post, pre;
  // Connection weights
  // Use a 1D array, since structs don't support variable-sized arrays
  // TODO: is this the best way to go? Would like to be able to do w[i][j]
  float *w;
} Connection;

// Build connection
Connection build_connection(int const post, int const pre);

// Init/reset connection
// Actually, only init, but name reset to stay consistent with neurons
void reset_connection(Connection *c);

// Load parameters for connection from text
// Only w
void load_connection(Connection *c, char const path[]);

// Free allocated memory for connection
void free_connection(Connection *c);

// Forward
void forward_connection(Connection *c, float x[], bool const s[]);
