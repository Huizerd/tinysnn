#include "../Network.h"

// Include child structs
#include "test_connection_conf_hidout.h"
#include "test_connection_conf_inhid.h"
#include "test_neuron_conf_hid.h"
#include "test_neuron_conf_out.h"

// Place cell centers as const array here, use pointer in configuration struct
float const centers[] = {0.2f, 0.4f};

// type, decoding_scale, centers, in_size, in_enc_size, hid_size, out_size,
// inhid, hid, hidout, out
NetworkConf const conf = {1,        2.0f, centers,     1,         2,
                          4,        1,    &conf_inhid, &conf_hid, &conf_hidout,
                          &conf_out};
