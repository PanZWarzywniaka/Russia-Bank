#ifndef SERVER_SERVER_FFI_H
#define SERVER_SERVER_FFI_H
#include "rust_server_binding.h"
struct server_state {

};

struct server_state* init_server_state();
void drop_server_state(struct server_state*);

#endif