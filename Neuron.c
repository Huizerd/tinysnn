#include "Neuron.h"
#include "functional.h"

#include <stdio.h>
#include <stdlib.h>

// Build neuron
Neuron build_neuron(int const size) {
  // Neuron struct
  Neuron n;

  // Set type
  n.type = RLIF;

  // Set size
  n.size = size;

  // Allocate memory for arrays: inputs, voltage, threshold, spikes, trace
  // No need for type casting
  n.x = calloc(size, sizeof(*n.x));
  n.v = calloc(size, sizeof(*n.v));
  n.th = calloc(size, sizeof(*n.th));
  n.s = calloc(size, sizeof(*n.s));
  n.t = calloc(size, sizeof(*n.t));

  // Allocate memory for arrays: voltage, threshold, trace and reset constants
  // Addition constants
  n.a_v = calloc(size, sizeof(*n.a_v));
  n.a_th = calloc(size, sizeof(*n.a_th));
  n.a_t = calloc(size, sizeof(*n.a_t));
  // Decay constants
  n.d_v = calloc(size, sizeof(*n.d_v));
  n.d_th = calloc(size, sizeof(*n.d_th));
  n.d_t = calloc(size, sizeof(*n.d_t));
  // Reset constants
  n.v_rest = 0.0f;
  n.th_rest = calloc(size, sizeof(*n.th_rest));

  return n;
}

// Init neuron (addition/decay/reset constants, inputs, voltage, spikes,
// threshold, trace)
void init_neuron(Neuron *n) {
  // Loop over neurons
  for (int i = 0; i < n->size; i++) {
    // Addition constants
    n->a_v[i] = 0.2f;
    n->a_th[i] = 0.2f;
    n->a_t[i] = 1.0f;
    // Decay constants
    n->d_v[i] = 0.8f;
    n->d_th[i] = 0.8f;
    n->d_t[i] = 0.8f;
    // Reset constants
    n->th_rest[i] = 0.2f;
    // Inputs
    n->x[i] = 0.0f;
    // Voltage
    n->v[i] = n->v_rest;
    // Spikes
    n->s[i] = 0.0f;
    // Threshold
    n->th[i] = n->th_rest[i];
    // Trace
    n->t[i] = 0.0f;
  }
  // Spike counter
  n->s_count = 0;
}

// Reset neuron (inputs, voltage, spikes, threshold, trace)
void reset_neuron(Neuron *n) {
  // Loop over neurons
  for (int i = 0; i < n->size; i++) {
    // Inputs
    n->x[i] = 0.0f;
    // Voltage
    n->v[i] = n->v_rest;
    // Spikes
    n->s[i] = 0.0f;
    // Threshold
    n->th[i] = n->th_rest[i];
    // Trace
    n->t[i] = 0.0f;
  }
  // Spike counter
  n->s_count = 0;
}

// Load parameters for neuron from header file (using the NeuronConf struct)
void load_neuron_from_header(Neuron *n, NeuronConf const *conf) {
  // Check shape
  if (n->size != conf->size) {
    printf("Neuron has a different shape than specified in the NeuronConf!\n");
    exit(1);
  }
  // Neuron type
  n->type = conf->type;
  // Loop over neurons
  // TODO: could also be done by just exchanging pointers to arrays?
  for (int i = 0; i < n->size; i++) {
    // Constants for addition of voltage, threshold and trace
    n->a_v[i] = conf->a_v[i];
    n->a_th[i] = conf->a_th[i];
    n->a_t[i] = conf->a_t[i];
    // Constants for decay of voltage, threshold and trace
    n->d_v[i] = conf->d_v[i];
    n->d_th[i] = conf->d_th[i];
    n->d_t[i] = conf->d_t[i];
    // Constant for resetting threshold
    n->th_rest[i] = conf->th_rest[i];
  }
  // Constant for resetting voltage
  n->v_rest = conf->v_rest;
}

// Free allocated memory for neuron
void free_neuron(Neuron *n) {
  // calloc() was used for voltage/decay/reset constants, inputs, voltage,
  // threshold, spike and trace arrays
  free(n->a_v);
  free(n->a_th);
  free(n->a_t);
  free(n->d_v);
  free(n->d_th);
  free(n->d_t);
  free(n->th_rest);
  free(n->x);
  free(n->v);
  free(n->th);
  free(n->s);
  free(n->t);
}

// Print neuron parameters
void print_neuron(Neuron const *n) {
  // Print all elements of neuron struct
  printf("Neuron type: %d\n", n->type);
  printf("Input:\n");
  print_array_1d(n->size, n->x);
  printf("Voltage:\n");
  print_array_1d(n->size, n->v);
  printf("Threshold:\n");
  print_array_1d(n->size, n->th);
  printf("Spikes:\n");
  print_array_1d_bool(n->size, n->s);
  printf("Trace:\n");
  print_array_1d(n->size, n->t);
  printf("Addition constants:\n");
  print_array_1d(n->size, n->a_v);
  print_array_1d(n->size, n->a_th);
  print_array_1d(n->size, n->a_t);
  printf("Decay constants:\n");
  print_array_1d(n->size, n->d_v);
  print_array_1d(n->size, n->d_th);
  print_array_1d(n->size, n->d_t);
  printf("Reset constants threshold:\n");
  print_array_1d(n->size, n->th_rest);
  printf("Reset constant voltage: %.4f\n\n", n->v_rest);
  printf("Spike count: %d\n", n->s_count);
  printf("\n");
}

// Check spikes
static void spiking(Neuron *n) {
  // Loop over neurons
  for (int i = 0; i < n->size; i++) {
    // If above/equal to threshold: set spike, else don't
    n->s[i] = n->v[i] >= n->th[i] ? 1.0f : 0.0f;
  }
}

// Do refraction
static void refrac(Neuron *n) {
  // Loop over neurons
  for (int i = 0; i < n->size; i++) {
    // If spike, then refraction
    // We don't have a refractory period, so no need to take care of that
    // TODO: how dangerous is checking for equality with floats?
    n->v[i] = n->s[i] == 1.0f ? n->v_rest : n->v[i];
    // Also increment spike counter!
    n->s_count += n->s[i] == 1.0f ? 1 : 0;
  }
}

// Update trace
// TODO: maybe all these separate loops over neurons are a bad idea, and we
//  should do one forward loop?
static void update_trace(Neuron *n) {
  // Loop over neurons
  for (int i = 0; i < n->size; i++) {
    // First decay trace, then increase for outgoing spikes
    n->t[i] *= n->d_t[i];
    n->t[i] += n->a_t[i] * n->s[i];
  }
}

// Update voltage
static void update_voltage(Neuron *n) {
  // Loop over neurons
  for (int i = 0; i < n->size; i++) {
    // Decay difference with resting potential, then increase for incoming
    // spikes
    n->v[i] = (n->v[i] - n->v_rest) * n->d_v[i];
    n->v[i] += n->a_v[i] * n->x[i];
  }
}

// Update threshold
static void update_threshold(Neuron *n) {
  // Loop over neurons
  for (int i = 0; i < n->size; i++) {
    // First decay threshold, then increase for outgoing spikes
    n->th[i] *= n->d_th[i];
    n->th[i] += n->a_th[i] * n->s[i];
  }
}

// Update/reset inputs (otherwise accumulation over time)
static void update_inputs(Neuron *n) {
  // Loop over neurons
  for (int i = 0; i < n->size; i++) {
    // Set to zero
    n->x[i] = 0.0f;
  }
}

// Forward: encompasses voltage/trace/threshold updates, spiking and refraction
// TODO: use above functions or write new loop which does all in one (and use
//  above for inspiration)
void forward_neuron(Neuron *n) {
  // Update voltage
  // Pass n because this is already a pointer
  update_voltage(n);
  // Get spikes
  spiking(n);
  // Update trace
  update_trace(n);
  // Update thresh (if adaptive)
  if (n->type == ALIF) {
    update_threshold(n);
  }
  // Refraction
  refrac(n);
  // Reset inputs (otherwise we get accumulation over time)
  update_inputs(n);
  // No return, spikes are a member of Neuron struct and can be used for next
  // layer
}
