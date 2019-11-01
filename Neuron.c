#include "Neuron.h"

#include <stdbool.h>
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

    // Allocate memory for arrays: voltage, threshold, spikes, trace
    // No need for type casting
    n.v = calloc(n.size, sizeof(*n.v));
    n.th = calloc(n.size, sizeof(*n.th));
    n.s = calloc(n.size, sizeof(*n.s));
    n.t = calloc(n.size, sizeof(*n.t));

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

// Init/reset neuron (voltage, spikes, threshold, trace)
void reset_neuron(Neuron *n) {
    // Loop over neurons
    for (int i = 0; i < n->size; i++) {
        // Voltage
        n->v[i] = n->v_rest;
        // Spikes
        n->s[i] = false;
        // Threshold
        n->th[i] = n->th_rest;
        // Trace
        n->t[i] = 0.0f;
    }
}

// Load parameters for neuron from text
void load_neuron(Neuron *n, char const *path) {
    // File containing neuron parameters
    // const here gives warning
    FILE *file = fopen(path, "r");
    // Consists of only single line:
    // a_v, a_th, a_t, d_v, d_th, d_t, v_rest, th_rest, type
    // Type cast to integer pointer for neuron type
    fscanf(file, "%f %f %f %f %f %f %f %f %d\n", &n->a_v, &n->a_th, &n->a_t, &n->d_v,
           &n->d_th, &n->d_t, &n->v_rest, &n->th_rest, (int *) &n->type);
    fclose(file);
}

// Free allocated memory for neuron
void free_neuron(Neuron *n) {
    // calloc() was used for voltage, threshold, spike and trace arrays
    free(n->v);
    free(n->th);
    free(n->s);
    free(n->t);
}
