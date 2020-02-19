#ifndef C_SERVER_BINDING_FOR_RUST
#define C_SERVER_BINDING_FOR_RUST
#include <stdio.h>
#include <stdbool.h>
#include "common_ffi.h"
//These are the declarations of C functions to be accessed by Rust

void hello_c();

unsigned char card_get_color(const struct card*);
unsigned char card_get_value(const struct card*);

#endif