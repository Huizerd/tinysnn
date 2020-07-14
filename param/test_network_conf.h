#include "../TwoLayerNetwork.h"

// Include child structs
#include "test_connection_conf_hidout.h"
#include "test_connection_conf_inhid.h"
#include "test_neuron_conf_hid.h"
#include "test_neuron_conf_out.h"

// Place cell centers as const array here, use pointer in configuration struct
float const actions[] = {0.0f, 1.0f, 2.0f};

// enc_type, dec_type, setpoint, actions, centers, in_size, in_enc_size, hid_size, out_size,
// inhid, hid, hidout, out
NetworkConf const conf = {1, 0, 0.5f, actions, 1, 2, 4, 3, &conf_inhid, &conf_hid, &conf_hidout, &conf_out};
