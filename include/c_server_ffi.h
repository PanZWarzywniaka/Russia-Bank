#ifndef SERVER_SERVER_FFI_H
#define SERVER_SERVER_FFI_H
#include "common_ffi.h" //This is the common set of definitions shared between C and Rust
#include "rust_server_binding.h" //This contains signatures of Rust functions exported to C

//This is the FFI for C++
struct server_state* init_server_state();
void drop_server_state(struct server_state*);


#endif