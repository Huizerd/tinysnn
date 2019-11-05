#pragma once

#include <stdbool.h>

// Enumeration for neuron types: regular LIF and adaptive LIF
typedef enum NeuronType { RLIF, ALIF } NeuronType;

// Struct that defines a layer of neurons
// "Neuron" before and after {} to define both tag and typedef alias (as is most
// common)
typedef struct Neuron {
  // Neuron type
  NeuronType type;
  // Neuron layer size
  int size;
  // Inputs
  float *x;
  // Cell voltage
  float *v;
  // Cell threshold
  float *th;
  // Cell spikes
  bool *s;
  // Post-synaptic firing trace
  float *t;
  // Constants for addition of voltage, threshold and trace
  float a_v, a_th, a_t;
  // Constants for decay of voltage, threshold and trace
  float d_v, d_th, d_t;
  // Constants for resetting voltage and threshold
  float v_rest, th_rest;
} Neuron;

// Build neuron
Neuron build_neuron(int const size);

// Init neuron (inputs, voltage, spikes, threshold, trace)
void init_neuron(Neuron *n);

// Reset neuron (inputs, voltage, spikes, threshold, trace)
// Does the same as init, just for consistency
void reset_neuron(Neuron *n);

// Load parameters for neuron from text
// a_v, a_th, a_t, d_v, d_th, d_t, v_rest, th_rest, type
void load_neuron(Neuron *n, char const path[]);

// Free allocated memory for neuron
void free_neuron(Neuron *n);

// Forward
void forward_neuron(Neuron *n);
