#include "Neuron.h"

#include <stdio.h>

// Test neuron functions
int main() {
    // File containing parameters
    char const param_path[] = "test_neuron_param.txt";
    // Neuron layer size
    int const size = 4;

    // Build neuron
    Neuron n = build_neuron(size);
    // Init neuron
    reset_neuron(&n);

    // Print neuron parameters before loading
    printf("Neuron type: %d\n", n.type);
    printf("Voltage [0]: %f\n", n.v[0]);
    printf("Threshold [0]: %f\n", n.th[0]);
    printf("Spikes [0]: %d\n", n.s[0]);
    printf("Trace [0]: %f\n", n.t[0]);
    printf("Addition constants: %f, %f, %f\n", n.a_v, n.a_th, n.a_t);
    printf("Decay constants: %f, %f, %f\n", n.d_v, n.d_th, n.d_t);
    printf("Reset constants: %f, %f\n", n.v_rest, n.th_rest);

    // Load neuron parameters
    load_neuron(&n, param_path);

    // Print neuron parameters after loading
    printf("Neuron type: %d\n", n.type);
    printf("Voltage [0]: %f\n", n.v[0]);
    printf("Threshold [0]: %f\n", n.th[0]);
    printf("Spikes [0]: %d\n", n.s[0]);
    printf("Trace [0]: %f\n", n.t[0]);
    printf("Addition constants: %f, %f, %f\n", n.a_v, n.a_th, n.a_t);
    printf("Decay constants: %f, %f, %f\n", n.d_v, n.d_th, n.d_t);
    printf("Reset constants: %f, %f\n", n.v_rest, n.th_rest);

    // Free neuron memory again
    free_neuron(&n);

    return 0;
}