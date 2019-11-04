#include "Neuron.h"
#include "functional.h"

#include <stdio.h>

// Test neuron forward functions
int main() {
    // Incoming inputs from connection
    // Connection shape (post neurons, pre neurons)
    // TODO: variable-sized arrays don't allow initialization, so use integers 2 and 4
    int const post = 2;
    int const pre = 4;
    float const x[2][4] = {{1.0f, 1.0f, 1.0f, 1.0f},
                           {2.0f, 2.0f, 2.0f, 2.0f}};

    // Build neuron
    Neuron n = build_neuron(post);
    // Init neuron
    reset_neuron(&n);

    // Print neuron parameters
    printf("Neuron type: %d\n", n.type);
    printf("Input [0]: %.2f\n", n.x[0]);
    printf("Voltage [0]: %.2f\n", n.v[0]);
    printf("Threshold [0]: %.2f\n", n.th[0]);
    printf("Spikes [0]: %d\n", n.s[0]);
    printf("Trace [0]: %.2f\n", n.t[0]);
    printf("Addition constants: %.2f, %.2f, %.2f\n", n.a_v, n.a_th, n.a_t);
    printf("Decay constants: %.2f, %.2f, %.2f\n", n.d_v, n.d_th, n.d_t);
    printf("Reset constants: %.2f, %.2f\n", n.v_rest, n.th_rest);
    printf("\n");

    // Print array of inputs coming from connection
    printf("Inputs:\n");
    print_array_2d(post, pre, x);

    // Forward neuron
    forward_neuron(&n, post, pre, x);

    // Print summed inputs
    printf("Summed inputs:\n");
    print_array_1d(n.size, n.x);
    // Print voltage
    printf("Volts:\n");
    print_array_1d(n.size, n.v);
    // Print spikes
    printf("Spikes:\n");
    print_array_1d_bool(n.size, n.s);
    // Print trace
    printf("Trace:\n");
    print_array_1d(n.size, n.t);

    // Free neuron memory again
    free_neuron(&n);

    return 0;
}