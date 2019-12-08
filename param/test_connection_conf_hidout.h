#include "../Connection.h"

// Weights as const array here, use pointer in configuration struct
float const w_hidout[] = {0.5f, 0.4f, 0.4f, 0.5f};

// post, pre, w
ConnectionConf const conf_hidout = {1, 4, w_hidout};
