#include "c_server_binding.h"

//These are the definitions of C functions to be accessed by Rust

void hello_c() {
    printf("Hello from C callback, called from Rust!\n");
}

unsigned char card_get_color(const struct card* m_card) {
    return m_card->color;
}
unsigned char card_get_value(const struct card* m_card) {
    return m_card->value;
}