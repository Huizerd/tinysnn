#pragma once

#include "Connection.h"
#include "Neuron.h"

// Enumeration for network encoding types: div+divdot and div place cells
typedef enum EncodingType { BOTH, PLACE } EncodingType;

// Struct that defines a network of one spiking layer
typedef struct Network {
  // Encoding type
  EncodingType type;
  // Decoding scale
  float decoding_scale;
  // We need place cell centers if we have place cell encoding
  float *centers;
  // Input, encoded input and output layer sizes
  int in_size, in_enc_size, out_size;
  // Two input place holders: one for scalar values
  // and one for encoded currents (size in_size)
  float *in, *in_enc;
  // Connection input -> output
  Connection *inout;
  // Output neurons
  Neuron *out;
} Network;

// Struct that holds the configuration of a one-layer network
// To be used when loading parameters from a header file
typedef struct NetworkConf {
  // Encoding type
  EncodingType const type;
  // Decoding scale
  float decoding_scale;
  // Place cell centers (just BS if we don't use them)
  float const *centers;
  // Input, encoded input and output layer sizes
  int const in_size, in_enc_size, out_size;
  // Connection input -> output
  ConnectionConf const *inout;
  // Output neurons
  NeuronConf const *out;
} NetworkConf;

// Build network: calls build functions for children
Network build_network(int const in_size, int const in_enc_size,
                      int const out_size);

// Init network: calls init functions for children
void init_network(Network *net);

// Reset network: calls reset functions for children
void reset_network(Network *net);

// Load parameters for network from header file and call load functions for
// children
void load_network_from_header(Network *net, NetworkConf const *conf);

// Free allocated memory for network and call free functions for children
void free_network(Network *net);

// Print network parameters (for debugging purposes)
void print_network(Network const *net);

// Forward network and call forward functions for children
// Encoding and decoding inside
float forward_network(Network *net);
