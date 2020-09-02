#include "ThreeLayerNetwork.h"
#include "Connection.h"
#include "Neuron.h"
#include "functional.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Build network: calls build functions for children
Network build_network(int const in_size, int const in_enc_size,
                      int const hid1_size, int const hid2_size, int const out_size) {
  // Network struct
  Network net;

  // Set encoding type
  net.enc_type = BOTH;
  // Set decoding type
  net.dec_type = WEIGHTED;

  // Set setpoint
  net.setpoint = 0.5f;

  // Set sizes
  net.in_size = in_size;
  net.in_enc_size = in_enc_size;
  net.hid1_size = hid1_size;
  net.hid2_size = hid2_size;
  net.out_size = out_size;

  // Allocate memory for input placeholders, action, place cell centers
  // and underlying neurons and connections
  net.in = calloc(in_size, sizeof(*net.in));
  net.in_enc = calloc(in_enc_size, sizeof(*net.in_enc));
  net.centers = calloc(in_enc_size, sizeof(*net.centers));
  net.actions = calloc(out_size, sizeof(*net.actions));
  // TODO: is this the best way to do this? Or let network struct consist of
  //  actual structs instead of pointers to structs?
  net.inhid1 = malloc(sizeof(*net.inhid1));
  net.hid1 = malloc(sizeof(*net.hid1));
  net.hid1hid2 = malloc(sizeof(*net.hid1hid2));
  net.hid2 = malloc(sizeof(*net.hid2));
  net.hid2out = malloc(sizeof(*net.hid2out));
  net.out = malloc(sizeof(*net.out));

  // Call build functions for underlying neurons and connections
  *net.inhid1 = build_connection(hid1_size, in_enc_size);
  *net.hid1 = build_neuron(hid1_size);
  *net.hid1hid2 = build_connection(hid2_size, hid1_size);
  *net.hid2 = build_neuron(hid2_size);
  *net.hid2out = build_connection(out_size, hid2_size);
  *net.out = build_neuron(out_size);

  return net;
}

// Init network: calls init functions for children
void init_network(Network *net) {
  // Loop over placeholders
  for (int i = 0; i < net->in_size; i++) {
    net->in[i] = 0.0f;
  }
  for (int i = 0; i < net->in_enc_size; i++) {
    net->in_enc[i] = 0.0f;
    net->centers[i] = 0.0f;
  }
  for (int i = 0; i < net->out_size; i++) {
    net->actions[i] = 0.0f;
  }
  // Call init functions for children
  init_connection(net->inhid1);
  init_neuron(net->hid1);
  init_connection(net->hid1hid2);
  init_neuron(net->hid2);
  init_connection(net->hid2out);
  init_neuron(net->out);
}

// Reset network: calls reset functions for children
void reset_network(Network *net) {
  reset_connection(net->inhid1);
  reset_neuron(net->hid1);
  reset_connection(net->hid1hid2);
  reset_neuron(net->hid2);
  reset_connection(net->hid2out);
  reset_neuron(net->out);
}

// Load parameters for network from header file and call load functions for
// children
void load_network_from_header(Network *net, NetworkConf const *conf) {
  // Check shapes
  if ((net->in_size != conf->in_size) ||
      (net->in_enc_size != conf->in_enc_size) || (net->hid1_size != conf->hid1_size) ||
      (net->hid2_size != conf->hid2_size) || (net->out_size != conf->out_size)) {
    printf(
        "Network has a different shape than specified in the NetworkConf!\n");
    exit(1);
  }
  // Encoding
  net->enc_type = conf->enc_type;
  // Decoding
  net->dec_type = conf->dec_type;
  // Setpoint
  net->setpoint = conf->setpoint;
  // Encoding place cell centers (just BS if we don't use them)
  for (int i = 0; i < net->in_enc_size; i++) {
    net->centers[i] = conf->centers[i];
  }
  // Action vector (just BS if we don't use them)
  for (int i = 0; i < net->out_size; i++) {
    net->actions[i] = conf->actions[i];
  }
  // Connection input -> hidden1
  load_connection_from_header(net->inhid1, conf->inhid1);
  // Hidden1 neuron
  load_neuron_from_header(net->hid1, conf->hid1);
  // Connection hidden1 -> hidden2
  load_connection_from_header(net->hid1hid2, conf->hid1hid2);
  // Hidden2 neuron
  load_neuron_from_header(net->hid2, conf->hid2);
  // Connection hidden2 -> output
  load_connection_from_header(net->hid2out, conf->hid2out);
  // Output neuron
  load_neuron_from_header(net->out, conf->out);
}

// Free allocated memory for network and call free functions for children
void free_network(Network *net) {
  // Call free functions for children
  // Freeing in a bottom-up manner
  // TODO: or should we call this before freeing the network struct members?
  free_connection(net->inhid1);
  free_neuron(net->hid1);
  free_connection(net->hid1hid2);
  free_neuron(net->hid2);
  free_connection(net->hid2out);
  free_neuron(net->out);
  // calloc() was used for input placeholders and underlying neurons and
  // connections
  free(net->in);
  free(net->in_enc);
  free(net->centers);
  free(net->actions);
  free(net->inhid1);
  free(net->hid1);
  free(net->hid1hid2);
  free(net->hid2);
  free(net->hid2out);
  free(net->out);
}

// Print network parameters (for debugging purposes)
void print_network(Network const *net) {
  // Encoding
  printf("Encoding type: %d\n", net->enc_type);
  printf("D setpoint: %.4f\n\n", net->setpoint);
  printf("Place cell centers:\n");
  print_array_1d(net->in_enc_size, net->centers);

  // Decoding
  printf("Decoding type: %d\n", net->dec_type);
  printf("Action vector:\n");
  print_array_1d(net->out_size, net->actions);

  // Input layer
  printf("Input layer (raw):\n");
  print_array_1d(net->in_size, net->in);
  printf("Input layer (encoded):\n");
  print_array_1d(net->in_enc_size, net->in_enc);

  // Connection input -> hidden1
  printf("Connection weights input -> hidden1:\n");
  print_array_2d(net->hid1_size, net->in_enc_size, net->inhid1->w);

  // Hidden1 layer
  print_neuron(net->hid1);

  // Connection hidden1 -> hidden2
  printf("Connection weights hidden1 -> hidden2:\n");
  print_array_2d(net->hid2_size, net->hid1_size, net->hid1hid2->w);

  // Hidden2 layer
  print_neuron(net->hid2);

  // Connection hidden2 -> output
  printf("Connection weights hidden2 -> output:\n");
  print_array_2d(net->out_size, net->hid2_size, net->hid2out->w);

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

// Encode both divergence and its derivative as current,
// but subtract the divergence setpoint from the former, giving you error
// Divergence setpoint D = 0.5
// TODO: also load parameters for this?
static void encode_error(int const size, int const enc_size, float x[size],
                         float x_enc[enc_size], float setpoint) {
  // Subtract setpoint from D
  x[0] -= setpoint;

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

// Encode divergence as spikes and subtract the divergence setpoint,
// making use of "place cells" in a cubic distribution
// Divergence setpoint D = 0.5
// TODO: also load parameters for this?
static void encode_cubic_place(int const size, int const enc_size, float x[size],
                               float x_enc[enc_size], float centers[enc_size], float setpoint) {
  // Subtract setpoint from D
  x[0] -= setpoint;

  // Reset all to 0
  for (int i = 0; i < enc_size; i++) {
    x_enc[i] = 0.0f;
  }

  // Determine in which bin D falls, then spike
  for (int i = 0; i < enc_size; i++) {
    // No lower bound
    if (i == 0) {
      if (x[0] <= centers[i])
        x_enc[i] = 1.0f;
    }
    // No upper bound
    else if (i == enc_size - 1){
      if (x[0] > centers[i])
        x_enc[i] = 1.0f;
    }
    // Both lower and upper bound
    else {
      if (x[0] > centers[i - 1] && x[0] <= centers[i])
        x_enc[i] = 1.0f;
    }
  }
}

// Decode from weighted sum of traces
// Mind to take into account the trace scaling
// TODO: also load parameters for this?
static float decode_weightedtrace(int const size, float const t[size],
                                  float const a[size]) {
  // Weight actions (a) with trace (t)
  float output = 0.0f;
  float tsum = 0.0f;
  for (int i = 0; i < size; i++) {
    output += t[i] * a[i];
    tsum += t[i];
  }

  // Catch divide-by-zero
  if (tsum == 0.0f) {
    return 0.0f;
  } else {
    return output / tsum;
  }
}

// Forward network and call forward functions for children
// Encoding and decoding inside
// TODO: but we still need to check the size of the array we put in net->in
float forward_network(Network *net) {
  // Encode input from scalar value to currents
  if (net->enc_type == BOTH) {
    encode_both(net->in_size, net->in_enc_size, net->in, net->in_enc);
  } else if (net->enc_type == ERROR) {
    encode_error(net->in_size, net->in_enc_size, net->in, net->in_enc, net->setpoint);
  } else if (net->enc_type == CUBIC) {
    encode_cubic_place(net->in_size, net->in_enc_size, net->in, net->in_enc, net->centers, net->setpoint);
  }
  // Call forward functions for children
  forward_connection(net->inhid1, net->hid1->x, net->in_enc);
  forward_neuron(net->hid1);
  forward_connection(net->hid1hid2, net->hid2->x, net->hid1->s);
  forward_neuron(net->hid2);
  forward_connection(net->hid2out, net->out->x, net->hid2->s);
  forward_neuron(net->out);
  // Decode output neuron traces to scalar value
  float output;
  if (net->dec_type == WEIGHTED) {
    output = decode_weightedtrace(net->out_size, net->out->t, net->actions);
  }

  return output;
}
