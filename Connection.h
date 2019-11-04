#pragma once

#include <stdbool.h>

typedef struct {
  // Connection weights
  float *w;
  // Connection shape
  int *shape;
} Connection;

// Build connection
Connection *build_connection(int const *shape);

// Init/reset connection
void init_connection(Connection *c);

// Load parameters for connection from text
// Only w
void load_connection(Connection *c, char const *path);

// Forward
float *forward_connection(Connection *c, bool const *s);

// Fold (change shape/view) --> in functional
