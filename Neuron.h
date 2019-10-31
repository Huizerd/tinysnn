#pragma once

#include <stdbool.h>

typedef struct
{
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
    // Neuron layer shape
    int shape;
    // Neuron type
    char type;
} Neuron;

// Check spikes
bool *spiking(Neuron *n);

// Do refraction
void refrac(Neuron *n, bool const *s);

// Init/reset neuron (voltage, spikes, threshold, refrac, trace)
void init_neuron(Neuron *neuron);
Neuron *build_neuron(int const shape);

// Load parameters for neuron from text
// a_v, a_th, a_t, d_v, d_th, d_t, v_rest, th_rest, type
void load_neuron(Neuron *n, char const *path);

// Forward
bool *forward_neuron(Neuron *n, float const *x);

// Update trace
void update_trace(Neuron *n, bool const *s);

// Update voltage
void update_voltage(Neuron *n, float const *x);

// Update threshold
void update_threshold(Neuron *n, bool const *s);

// Fold inputs (sum last dimension) --> in functional
