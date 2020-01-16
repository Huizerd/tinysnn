#include "Network2.h"
#include "Connection.h"
#include "Neuron.h"
#include "functional.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Build network: calls build functions for children
Network build_network(int const in_size, int const in_enc_size,
                      int const out_size) {
  // Network struct
  Network net;

  // Set encoding type
  net.type = BOTH;

  // Set decoding scale
  net.decoding_scale = 1.0f;

  // Set sizes
  // Output size has to be 1
  if (out_size != 1) {
    printf("Network output size should be 1!\n");
    exit(1);
  }
  net.in_size = in_size;
  net.in_enc_size = in_enc_size;
  net.out_size = out_size;

  // Allocate memory for input placeholders, place cell centers and underlying
  // neurons and connections
  net.in = calloc(in_size, sizeof(*net.in));
  net.in_enc = calloc(in_enc_size, sizeof(*net.in_enc));
  net.centers = calloc(in_enc_size, sizeof(*net.centers));
  // TODO: is this the best way to do this? Or let network struct consist of
  //  actual structs instead of pointers to structs?
  net.inout = malloc(sizeof(*net.inout));
  net.out = malloc(sizeof(*net.out));

  // Call build functions for underlying neurons and connections
  *net.inout = build_connection(out_size, in_enc_size);
  *net.out = build_neuron(out_size);

  return net;
}

// Init network: calls init functions for children
void init_network(Network *net) {
  // Loop over input placeholders
  for (int i = 0; i < net->in_size; i++) {
    net->in[i] = 0.0f;
  }
  for (int i = 0; i < net->in_enc_size; i++) {
    net->in_enc[i] = 0.0f;
    net->centers[i] = 0.0f;
  }
  // Call init functions for children
  init_connection(net->inout);
  init_neuron(net->out);
}

// Reset network: calls reset functions for children
void reset_network(Network *net) {
  reset_connection(net->inout);
  reset_neuron(net->out);
}

// Load parameters for network from header file and call load functions for
// children
void load_network_from_header(Network *net, NetworkConf const *conf) {
  // Check shapes
  if ((net->in_size != conf->in_size) ||
      (net->in_enc_size != conf->in_enc_size) ||
      (net->out_size != conf->out_size)) {
    printf(
        "Network has a different shape than specified in the NetworkConf!\n");
    exit(1);
  }
  // Encoding
  net->type = conf->type;
  // Decoding
  net->decoding_scale = conf->decoding_scale;
  // Place cell centers (just BS if we don't use them)
  for (int i = 0; i < net->in_enc_size; i++) {
    net->centers[i] = conf->centers[i];
  }
  // Connection input -> output
  load_connection_from_header(net->inout, conf->inout);
  // Output neuron
  load_neuron_from_header(net->out, conf->out);
}

// Free allocated memory for network and call free functions for children
void free_network(Network *net) {
  // Call free functions for children
  // Freeing in a bottom-up manner
  // TODO: or should we call this before freeing the network struct members?
  free_connection(net->inout);
  free_neuron(net->out);
  // calloc() was used for input placeholders and underlying neurons and
  // connections
  free(net->in);
  free(net->in_enc);
  free(net->centers);
  free(net->inout);
  free(net->out);
}

// Print network parameters (for debugging purposes)
void print_network(Network const *net) {
  // Encoding type
  printf("Encoding type: %d\n", net->type);
  printf("Place cell centers:\n");
  print_array_1d(net->in_enc_size, net->centers);

  // Decoding scale
  printf("Decoding scale: %.4f\n\n", net->decoding_scale);

  // Input layer
  printf("Input layer (raw):\n");
  print_array_1d(net->in_size, net->in);
  printf("Input layer (encoded):\n");
  print_array_1d(net->in_enc_size, net->in_enc);

  // Connection input -> output
  printf("Connection weights input -> output:\n");
  print_array_2d(net->out_size, net->in_enc_size, net->inout->w);

  // Output layer
  print_neuron(net->out);
}

// Encode both divergence and its derivative as current
// Called in forward_network(), so has to be put in front (because not in
// header)
// TODO: also load parameters for this?
static void encode_both(int const size, int const enc_size, float x[size],
                        float x_enc[enc_size]) {
  // Repeat inputs, clamp first half to positive, second half to negative
  // and make absolute
  for (int i = 0; i < enc_size; i++) {
    if (i < size) {
      x_enc[i] = fmaxf(0.0f, x[i % (size)]);
    } else {
      x_enc[i] = fabs(fminf(0.0f, x[i % (size)]));
    }
  }
}

// Encode divergence through nonlinearly distributed place cells
// TODO: also load parameters for this?
static void encode_place(int const size, int const enc_size, float x[size],
                         float x_enc[enc_size], float centers[enc_size]) {
  // Place cell activity/current depends on distance between
  // current state and center
  // First clamp to [-10, 10]
  // TODO: maybe make this more flexible?
  for (int i = 0; i < size; i++) {
    x[i] = fmaxf(-10.0f, fminf(10.0f, x[i]));
  }
  // Overlap of activity: total range of inputs divided by # of centers - 1
  float sigma = 20.0f / (enc_size - 1);

  // Do actual encoding
  // 1.0: input scaling
  for (int i = 0; i < enc_size; i++) {
    x_enc[i] =
        1.0f * exp(-(x[0] - centers[i]) * (x[0] - centers[i]) / (2.0f * sigma));
  }
}

// Decode from trace
// Mind to take into account the trace scaling
// TODO: also load parameters for this?
static float decode_network(int const size, float const t[size],
                            float const scale) {
  // Scale with output range and maximum trace and apply potential offset
  float output = -0.8f + (0.5f + 0.8f) * (t[0] / scale + 0.0f);

  return output;
}

// Forward network and call forward functions for children
// Encoding and decoding inside
// TODO: but we still need to check the size of the array we put in net->in
float forward_network(Network *net) {
  // Encode input from scalar value to currents
  if (net->type == BOTH) {
    encode_both(net->in_size, net->in_enc_size, net->in, net->in_enc);
  } else if (net->type == PLACE) {
    encode_place(net->in_size, net->in_enc_size, net->in, net->in_enc,
                 net->centers);
  }
  // Call forward functions for children
  forward_connection(net->inout, net->out->x, net->in_enc);
  forward_neuron(net->out);
  // Decode output neuron traces to scalar value
  float output =
      decode_network(net->out_size, net->out->t, net->decoding_scale);

  return output;
}
