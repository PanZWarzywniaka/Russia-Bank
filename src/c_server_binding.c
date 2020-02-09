#include "c_server_binding.h"

//These are the definitions of C functions to be accessed by Rust

void hello_c() {
    printf("Hello from C callback, called from Rust!\n");
}