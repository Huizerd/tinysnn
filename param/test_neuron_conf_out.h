#include "../Neuron.h"

// Addition/decay/reset constants as const array here, use pointer in
// configuration struct
float const a_v_out[] = {1.5f};
float const a_th_out[] = {1.5f};
float const a_t_out[] = {1.5f};
float const d_v_out[] = {0.7f};
float const d_th_out[] = {0.7f};
float const d_t_out[] = {0.7f};
float const th_rest_out[] = {1.2f};

// type, size, a_v, a_th, a_t, d_v, d_th, d_t, v_rest, th_rest
NeuronConf const conf_out = {0,       1,        a_v_out, a_th_out, a_t_out,
                             d_v_out, d_th_out, d_t_out, 0.0f,     th_rest_out};
