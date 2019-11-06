#include "Neuron.h"

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

  // Voltage constants
  n.a_v = 1.0f;
  n.d_v = 0.8f;
  // Threshold constants
  n.a_th = 1.0f;
  n.d_th = 0.8f;
  // Trace constants
  n.a_t = 1.0f;
  n.d_t = 0.8f;
  // Reset constants
  n.v_rest = 0.0f;
  n.th_rest = 1.0f;

  return n;
}

// Init neuron (inputs, voltage, spikes, threshold, trace)
void init_neuron(Neuron *n) {
  // Loop over neurons
  for (int i = 0; i < n->size; i++) {
    // Inputs
    n->x[i] = 0.0f;
    // Voltage
    n->v[i] = n->v_rest;
    // Spikes
    n->s[i] = 0.0f;
    // Threshold
    n->th[i] = n->th_rest;
    // Trace
    n->t[i] = 0.0f;
  }
}

// Reset neuron (inputs, voltage, spikes, threshold, trace)
// Does the same as init, just for consistency
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
    n->th[i] = n->th_rest;
    // Trace
    n->t[i] = 0.0f;
  }
}

// Load parameters for neuron from text
// TODO: check with Erik whether we're checking input file nicely here
void load_neuron(Neuron *n, char const path[]) {
  // File containing neuron parameters
  // const here gives warning
  FILE *file;
  int count;
  if ((file = fopen(path, "r")) == NULL) {
    printf("Error in loading neuron parameter file!\n");
    exit(1);
  }
  // Consists of only single line:
  // a_v, a_th, a_t, d_v, d_th, d_t, v_rest, th_rest, type
  // Type cast to integer pointer for neuron type
  count = fscanf(file, "%f %f %f %f %f %f %f %f %d\n", &n->a_v, &n->a_th,
                 &n->a_t, &n->d_v, &n->d_th, &n->d_t, &n->v_rest, &n->th_rest, (int *)&n->type);
  // Exit if not all parameters assigned or EOF/error
  if (count == EOF || count != 9) {
    printf("Error in loading neuron parameters!\n");
    exit(1);
  }
  fclose(file);
}

// Free allocated memory for neuron
void free_neuron(Neuron *n) {
  // calloc() was used for inputs, voltage, threshold, spike and trace arrays
  free(n->x);
  free(n->v);
  free(n->th);
  free(n->s);
  free(n->t);
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
  }
}

// Update trace
// TODO: maybe all these separate loops over neurons are a bad idea, and we
//  should do one forward loop?
static void update_trace(Neuron *n) {
  // Loop over neurons
  for (int i = 0; i < n->size; i++) {
    // First decay trace, then increase for outgoing spikes
    n->t[i] *= n->d_t;
    n->t[i] += n->a_t * n->s[i];
  }
}

// Update voltage
static void update_voltage(Neuron *n) {
  // Loop over neurons
  for (int i = 0; i < n->size; i++) {
    // Decay difference with resting potential, then increase for incoming
    // spikes
    n->v[i] = (n->v[i] - n->v_rest) * n->d_v;
    n->v[i] += n->a_v * n->x[i];
  }
}

// Update threshold
static void update_threshold(Neuron *n) {
  // Loop over neurons
  for (int i = 0; i < n->size; i++) {
    // First decay threshold, then increase for outgoing spikes
    n->th[i] *= n->d_th;
    n->th[i] += n->a_th * n->s[i];
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
  // No return, spikes are a member of Neuron struct and can be used for next
  // layer
}
