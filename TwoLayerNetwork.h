#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "Connection.h"
#include "Neuron.h"

// Enumeration for network encoding types:
// - div+divdot
// - div+divdot, but div setpoint subtracted
// - div place cells, cubic placement, div setpoint subtracted
typedef enum EncodingType { BOTH, ERROR, CUBIC } EncodingType;

// Enumeration for network decoding types:
// - actions weighted by trace
typedef enum DecodingType { WEIGHTED } DecodingType;

// Struct that defines a network of two spiking layers
typedef struct Network {
  // Encoding type
  EncodingType enc_type;
  // Decoding type
  DecodingType dec_type;
  // D setpoint
  float setpoint;
  // Encoding place cell centers
  float* centers;
  // Decoding action vector
  float* actions;
  // Input, encoded input, hidden and output layer sizes
  int in_size, in_enc_size, hid_size, out_size;
  // Two input place holders: one for scalar values
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

// Struct that holds the configuration of a two-layer network
// To be used when loading parameters from a header file
typedef struct NetworkConf {
  // Encoding type
  EncodingType const enc_type;
  // Decoding type
  DecodingType const dec_type;
  // D setpoint
  float setpoint;
  // Encoding place cell centers (just BS if we don't use them)
  float const *centers;
  // Decoding action vector (just BS if we don't use them)
  float const *actions;
  // Input, encoded input, hidden and output layer sizes
  int const in_size, in_enc_size, hid_size, out_size;
  // Connection input -> hidden
  ConnectionConf const *inhid;
  // Hidden neurons
  NeuronConf const *hid;
  // Connection hidden -> output
  ConnectionConf const *hidout;
  // Output neurons
  NeuronConf const *out;
} NetworkConf;

// Build network: calls build functions for children
Network build_network(int const in_size, int const in_enc_size,
                      int const hid_size, int const out_size);

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

#ifdef __cplusplus
}
#endif
