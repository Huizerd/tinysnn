#include "../Neuron.h"

// Addition/decay/reset constants as const array here, use pointer in
// configuration struct
float const a_t[] = {1.0f, 1.0f, 1.0f, 1.0f};
float const d_v[] = {0.6f, 0.6f, 0.6f, 0.6f};
float const d_t[] = {0.5f, 0.6f, 0.6f, 0.5f};
float const th_rest[] = {0.8f, 0.9f, 0.9f, 0.8f};

// size, a_t, d_v, d_t, v_rest, th_rest
NeuronConf const conf = {4, a_t, d_v, d_t, 0.0f, th_rest};
