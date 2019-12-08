#include "../Neuron.h"

// Addition/decay/reset constants as const array here, use pointer in
// configuration struct
float const a_v[] = {0.3f, 0.3f, 0.3f, 0.3f};
float const a_th[] = {1.0f, 1.0f, 1.0f, 1.0f};
float const a_t[] = {1.0f, 1.0f, 1.0f, 1.0f};
float const d_v[] = {0.6f, 0.6f, 0.6f, 0.6f};
float const d_th[] = {0.5f, 0.4f, 0.4f, 0.5f};
float const d_t[] = {0.5f, 0.6f, 0.6f, 0.5f};
float const th_rest[] = {0.8f, 0.9f, 0.9f, 0.8f};

// type, size, a_v, a_th, a_t, d_v, d_th, d_t, v_rest, th_rest
NeuronConf const conf = {1, 4, a_v, a_th, a_t, d_v, d_th, d_t, 0.0f, th_rest};
