#pragma once

#include "Neuron.h"
#include "Connection.h"

typedef struct
{
    // Input neurons (just a placeholder)
    float *in;
    // Connection input -> hidden
    Connection *inhid;
    // Hidden neurons
    Neuron *hid;
    // Connection hidden -> output
    Connection *hidout;
    // Output neurons
    Neuron *out;
    // Input and output shape
    int in_shape;
    int out_shape;
} Network;

// Build network
Network *build_network(int const in_shape, int const out_shape, Neuron const *hid, Neuron const *out, Connection const *inhid, Connection const *hidout);

// Init/reset state: call inits/resets for children
void init_network(Network *net);

// Load parameters for network from text and call children
// Network text file specifies paths for children
void load_network(Network *net, char const *path);

// Forward network and call forward for all children
// Encoding and decoding inside
float *forward_network(Network *net, float const *x);

// Encode to current
float *encode_network(float const *x);

// Decode from trace
float *decode_network(float const *t);
