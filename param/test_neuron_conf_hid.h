#include "../Neuron.h"

// Addition/decay/reset constants as const array here, use pointer in
// configuration struct
float const a_v_hid[] = {0.2f, 0.2f, 0.2f, 0.2f};
float const a_th_hid[] = {0.2f, 0.2f, 0.2f, 0.2f};
float const a_t_hid[] = {0.2f, 0.2f, 0.2f, 0.2f};
float const d_v_hid[] = {0.8f, 0.8f, 0.8f, 0.8f};
float const d_th_hid[] = {0.8f, 0.8f, 0.8f, 0.8f};
float const d_t_hid[] = {0.8f, 0.8f, 0.8f, 0.8f};
float const th_rest_hid[] = {0.9f, 0.9f, 0.9f, 0.9f};

// type, size, a_v, a_th, a_t, d_v, d_th, d_t, v_rest, th_rest
NeuronConf const conf_hid = {1,       4,        a_v_hid, a_th_hid, a_t_hid,
                             d_v_hid, d_th_hid, d_t_hid, 0.0f,     th_rest_hid};
