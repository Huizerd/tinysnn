#include "../Neuron.h"

// Addition/decay/reset constants as const array here, use pointer in
// configuration struct
float const a_t_hid[] = {0.2f, 0.2f, 0.2f, 0.2f};
float const d_v_hid[] = {0.8f, 0.8f, 0.8f, 0.8f};
float const d_t_hid[] = {0.8f, 0.8f, 0.8f, 0.8f};
float const th_rest_hid[] = {0.9f, 0.9f, 0.9f, 0.9f};

// size, a_t, d_v, d_t, v_rest, th_rest
NeuronConf const conf_hid = {4, a_t_hid, d_v_hid, d_t_hid, 0.0f, th_rest_hid};
