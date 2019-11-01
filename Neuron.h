#pragma once

#include <stdbool.h>

// Enumeration for neuron types: regular LIF and adaptive LIF
typedef enum NeuronType {
    RLIF, ALIF
} NeuronType;

// Struct that defines a layer of neurons
// "Neuron" before and after {} to define both tag and typedef alias (as is most
// common)
typedef struct Neuron {
    // Neuron type
    NeuronType type;
    // Cell voltage
    float *v;
    // Cell threshold
    float *th;
    // Cell spikes
    bool *s;
    // Post-synaptic firing trace
    float *t;
    // Constants for addition of voltage, threshold and trace
    float a_v;
    float a_th;
    float a_t;
    // Constants for decay of voltage, threshold and trace
    float d_v;
    float d_th;
    float d_t;
    // Constants for resetting voltage and threshold
    float v_rest;
    float th_rest;
    // Neuron layer size
    int size;
} Neuron;

// Build neuron
Neuron build_neuron(int const size);

// Init/reset neuron (voltage, spikes, threshold, trace)
void reset_neuron(Neuron *n);

// Load parameters for neuron from text
// a_v, a_th, a_t, d_v, d_th, d_t, v_rest, th_rest, type
void load_neuron(Neuron *n, char const *path);

// Free allocated memory for neuron
void free_neuron(Neuron *n);

// Check spikes
bool *spiking(Neuron *n);

// Do refraction
void refrac(Neuron *n, bool const *s);

// Forward
bool *forward_neuron(Neuron *n, float const *x);

// Update trace
void update_trace(Neuron *n, bool const *s);

// Update voltage
void update_voltage(Neuron *n, float const *x);

// Update threshold
void update_threshold(Neuron *n, bool const *s);

// Fold inputs (sum last dimension) --> in functional
