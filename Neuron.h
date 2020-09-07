#pragma once

#ifdef __cplusplus
extern "C" {
#endif

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
  float *s;
  // Post-synaptic firing trace
  float *t;
  // Constants for addition of voltage, threshold and trace
  float *a_v, *a_th, *a_t;
  // Constants for decay of voltage, threshold and trace
  float *d_v, *d_th, *d_t;
  // Constants for resetting voltage and threshold
  float v_rest, *th_rest;
  // Counter for spikes
  int s_count;
} Neuron;

// Struct that holds the configuration of a layer of neurons
// To be used when loading parameters from a header file
typedef struct NeuronConf {
  // Neuron type
  NeuronType const type;
  // Neuron layer size
  int const size;
  // Constants for addition of voltage, threshold and trace
  float const *a_v, *a_th, *a_t;
  // Constants for decay of voltage, threshold and trace
  float const *d_v, *d_th, *d_t;
  // Constants for resetting voltage and threshold
  float const v_rest, *th_rest;
} NeuronConf;

// Build neuron
Neuron build_neuron(int const size);

// Init neuron (addition/decay/reset constants, inputs, voltage, spikes,
// threshold, trace)
void init_neuron(Neuron *n);

// Reset neuron (inputs, voltage, spikes, threshold, trace)
void reset_neuron(Neuron *n);

// Load parameters for neuron from header file (using the NeuronConf struct)
// a_v, a_th, a_t, d_v, d_th, d_t, v_rest, th_rest, type
void load_neuron_from_header(Neuron *n, NeuronConf const *conf);

// Free allocated memory for neuron
void free_neuron(Neuron *n);

// Print neuron parameters
void print_neuron(Neuron const *n);

// Forward
void forward_neuron(Neuron *n);

#ifdef __cplusplus
}
#endif
