#include "TwoLayerNetwork.h"
#include "Connection.h"
#include "Neuron.h"
#include "functional.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Build network: calls build functions for children
Network build_network(int const in_size, int const in_enc_size,
                      int const hid_size, int const out_size) {
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
  net.hid_size = hid_size;
  net.out_size = out_size;

  // Allocate memory for input placeholders, action, place cell centers
  // and underlying neurons and connections
  net.in = calloc(in_size, sizeof(*net.in));
  net.in_enc = calloc(in_enc_size, sizeof(*net.in_enc));
  net.centers = calloc(in_enc_size, sizeof(*net.centers));
  net.actions = calloc(out_size, sizeof(*net.actions));
  // TODO: is this the best way to do this? Or let network struct consist of
  //  actual structs instead of pointers to structs?
  net.inhid = malloc(sizeof(*net.inhid));
  net.hid = malloc(sizeof(*net.hid));
  net.hidout = malloc(sizeof(*net.hidout));
  net.out = malloc(sizeof(*net.out));

  // Call build functions for underlying neurons and connections
  *net.inhid = build_connection(hid_size, in_enc_size);
  *net.hid = build_neuron(hid_size);
  *net.hidout = build_connection(out_size, hid_size);
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
  init_connection(net->inhid);
  init_neuron(net->hid);
  init_connection(net->hidout);
  init_neuron(net->out);
}

// Reset network: calls reset functions for children
void reset_network(Network *net) {
  reset_connection(net->inhid);
  reset_neuron(net->hid);
  reset_connection(net->hidout);
  reset_neuron(net->out);
}

// Load parameters for network from header file and call load functions for
// children
void load_network_from_header(Network *net, NetworkConf const *conf) {
  // Check shapes
  if ((net->in_size != conf->in_size) ||
      (net->in_enc_size != conf->in_enc_size) ||
      (net->hid_size != conf->hid_size) || (net->out_size != conf->out_size)) {
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
  // Connection input -> hidden
  load_connection_from_header(net->inhid, conf->inhid);
  // Hidden neuron
  load_neuron_from_header(net->hid, conf->hid);
  // Connection hidden -> output
  load_connection_from_header(net->hidout, conf->hidout);
  // Output neuron
  load_neuron_from_header(net->out, conf->out);
}

// Free allocated memory for network and call free functions for children
void free_network(Network *net) {
  // Call free functions for children
  // Freeing in a bottom-up manner
  // TODO: or should we call this before freeing the network struct members?
  free_connection(net->inhid);
  free_neuron(net->hid);
  free_connection(net->hidout);
  free_neuron(net->out);
  // calloc() was used for input placeholders and underlying neurons and
  // connections
  free(net->in);
  free(net->in_enc);
  free(net->centers);
  free(net->actions);
  free(net->inhid);
  free(net->hid);
  free(net->hidout);
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

  // Connection input -> hidden
  printf("Connection weights input -> hidden:\n");
  print_array_2d(net->hid_size, net->in_enc_size, net->inhid->w);

  // Hidden layer
  print_neuron(net->hid);

  // Connection hidden -> output
  printf("Connection weights hidden -> output:\n");
  print_array_2d(net->out_size, net->hid_size, net->hidout->w);

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
      if (x[0] <= centers[i]) {
        x_enc[i] = 1.0f;
        break;
      }
    }
    // No upper bound
    else if (i == enc_size - 1) {
      if (x[0] > centers[i]) {
        x_enc[i] = 1.0f;
        break;
      }
    }
    // Both lower and upper bound
    else {
      if (x[0] > centers[i - 1] && x[0] <= centers[i]) {
        x_enc[i] = 1.0f;
        break;
      }
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
  forward_connection(net->inhid, net->hid->x, net->in_enc);
  forward_neuron(net->hid);
  forward_connection(net->hidout, net->out->x, net->hid->s);
  forward_neuron(net->out);
  // Decode output neuron traces to scalar value
  float output;
  if (net->dec_type == WEIGHTED) {
    output = decode_weightedtrace(net->out_size, net->out->t, net->actions);
  }

  return output;
}
