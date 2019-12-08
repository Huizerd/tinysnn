#include "../Connection.h"

// Weights as const array here, use pointer in configuration struct
float const w[] = {0.1f, 0.3f, 0.3f, 0.1f, 0.4f, 1.0f, 1.0f, 0.4f};

// post, pre, w
ConnectionConf const conf = {2, 4, w};
