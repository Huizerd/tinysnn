#include "Network.h"
#include "Connection.h"
#include "Neuron.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Build network: calls build functions for children
Network build_network(int const in_size, int const hid_size,
                      int const out_size) {
  // Network struct
  Network net;

  // Set sizes
  // Input size has to be even, output size has to be 1
  if (in_size % 2 || out_size != 1) {
    printf("Network input size should be even, and output size should be 1!\n");
    exit(1);
  }
  net.in_size = in_size;
  net.hid_size = hid_size;
  net.out_size = out_size;

  // Allocate memory for input placeholders and underlying neurons and
  // connections
  net.in = calloc(in_size / 2, sizeof(*net.in));
  net.in_enc = calloc(in_size, sizeof(*net.in_enc));
  // TODO: is this the best way to do this? Or let network struct consist of
  //  actual structs instead of pointers to structs?
  net.inhid = malloc(sizeof(*net.inhid));
  net.hid = malloc(sizeof(*net.hid));
  net.hidout = malloc(sizeof(*net.hidout));
  net.out = malloc(sizeof(*net.out));

  // Call build functions for underlying neurons and connections
  // Connection inhid = build_connection(hid_size, in_size);
  // Neuron hid = build_neuron(hid_size);
  // Connection hidout = build_connection(out_size, hid_size);
  // Neuron out = build_neuron(out_size);
  // net.inhid = &inhid;
  // net.hid = &hid;
  // net.hidout = &hidout;
  // net.out = &out;
  // net.inhid = build_connection(hid_size, in_size);
  // net.hid = build_neuron(hid_size);
  // net.hidout = build_connection(out_size, hid_size);
  // net.out = build_neuron(out_size);
  *net.inhid = build_connection(hid_size, in_size);
  *net.hid = build_neuron(hid_size);
  *net.hidout = build_connection(out_size, hid_size);
  *net.out = build_neuron(out_size);

  return net;
}

// Init network: calls init functions for children
void init_network(Network *net) {
  // Loop over input placeholders
  for (int i = 0; i < net->in_size; i++) {
    if (i < net->in_size / 2) {
      net->in[i] = 0.0f;
    }
    net->in_enc[i] = 0.0f;
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

// Load parameters for network from text and call load functions for children
// Network text file specifies paths for children
// TODO: check this entire error-checking construct again with Erik
void load_network(Network *net, char const path[]) {
  // File containing network children file paths
  FILE *file;
  if ((file = fopen(path, "r")) == NULL) {
    printf("Error in loading network parameter file!\n");
    exit(1);
  }
  // Go over lines in file to load children
  // In order! connection -> neuron -> connection -> neuron
  // TODO: test whether enough lines
  // TODO: test width of text file
  // Maximum 100 characters
  char child_path[100];
  int last;
  // Connection input -> hidden
  // Check whether there's a line and its length; trim if applicable, else exit
  // TODO: does this work? I.e., does child_path get filled before strcspn()?
  if (fgets(child_path, 100, file) &&
      (last = strcspn(child_path, "\n")) < 100) {
    child_path[last] = 0;
    load_connection(net->inhid, child_path);
  } else {
    printf("Error in reading input->hidden weight file name!\n");
    exit(1);
  }
  // Hidden neuron
  if (fgets(child_path, 100, file) &&
      (last = strcspn(child_path, "\n")) < 100) {
    child_path[last] = 0;
    load_neuron(net->hid, child_path);
  } else {
    printf("Error in reading hidden parameter file name!\n");
    exit(1);
  }
  // Connection hidden -> output
  if (fgets(child_path, 100, file) &&
      (last = strcspn(child_path, "\n")) < 100) {
    child_path[last] = 0;
    load_connection(net->hidout, child_path);
  } else {
    printf("Error in reading hidden->output weight file name!\n");
    exit(1);
  }
  // Output neuron
  if (fgets(child_path, 100, file) &&
      (last = strcspn(child_path, "\n")) < 100) {
    child_path[last] = 0;
    load_neuron(net->out, child_path);
  } else {
    printf("Error in reading output parameter file name!\n");
    exit(1);
  }
  // Exit if still lines left
  if (fgets(child_path, 100, file) && !feof(file)) {
    printf("More lines than network components!\n");
    exit(1);
  }
  fclose(file);
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
  free(net->inhid);
  free(net->hid);
  free(net->hidout);
  free(net->out);
}

// Encode to current
// Called in forward_network(), so has to be put in front (because not in
// header)
static void encode_network(int const size, float x[size / 2],
                           float x_enc[size]) {
  // Repeat inputs, clamp first half to positive, second half to negative
  // and make absolute
  for (int i = 0; i < size; i++) {
    if (i < size / 2) {
      x_enc[i] = fminf(0.0f, x[i % 2]);
    } else {
      x_enc[i] = fabs(fmaxf(0.0f, x[i % 2]));
    }
  }
}

// Decode from trace
static float decode_network(int const size, float const t[size]) {
  // Scale with output range and maximum trace and apply potential offset
  float output = -0.8f + (0.5f + 0.8f) * (t[0] / 1.0f + 0.0f);

  return output;
}

// Forward network and call forward functions for children
// Encoding and decoding inside
// TODO: but we still need to check the size of the array we put in net->in
float forward_network(Network *net) {
  // Encode input from scalar value to currents
  encode_network(net->in_size, net->in, net->in_enc);
  // Call forward functions for children
  // TODO: net->in is float instead of bool, how to solve this? Or leave it?
  forward_connection(net->inhid, net->hid->x, net->in);
  forward_neuron(net->hid);
  forward_connection(net->hidout, net->out->x, net->hid->s);
  forward_neuron(net->out);
  // Decode output neuron traces to scalar value
  float output = decode_network(net->out_size, net->out->t);

  return output;
}
