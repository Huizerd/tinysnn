#pragma once

#include "Connection.h"
#include "Neuron.h"

typedef struct Network {
  // Input, hidden and output layer sizes
  int in_size, hid_size, out_size;
  // Two input place holders: one for scalar values (size in_size / 2)
  // and one for encoded currents (size in_size)
  float *in, *in_enc;
  // Connection input -> hidden
  Connection *inhid;
  // Hidden neurons
  Neuron *hid;
  // Connection hidden -> output
  Connection *hidout;
  // Output neurons
  Neuron *out;
} Network;

// Build network: calls build functions for children
Network build_network(int const in_size, int const hid_size,
                      int const out_size);

// Init network: calls init functions for children
void init_network(Network *net);

// Reset network: calls reset functions for children
void reset_network(Network *net);

// Load parameters for network from text and call load functions for children
// Network text file specifies paths for children
void load_network(Network *net, char const path[]);

// Free allocated memory for network and call free functions for children
void free_network(Network *net);

// Print network parameters (for debugging purposes)
void print_network(Network *net);

// Forward network and call forward functions for children
// Encoding and decoding inside
float forward_network(Network *net);
