#include "c_server_ffi.h"
#include <stdlib.h>

//This is the FFI for C++
struct server_state* init_server_state() {
    foo();
    init_server();
    return malloc(sizeof(struct server_state));
}
void drop_server_state(struct server_state* dropped) {
    bye();
    free(dropped);
    drop_server();
}