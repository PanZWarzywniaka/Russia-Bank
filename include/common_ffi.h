#ifndef COMMON_FFI
#define COMMON_FFI
#include <stdbool.h>
#include <stddef.h>
//These are the common definitions shared between C and Rust

struct card {
    unsigned char color;
    unsigned char value;
};

struct card* make_card(unsigned char, unsigned char);
//the getters are defined in the c_server_binding header

struct deck {
    struct deck* node_below;
    struct card* node_content;
};

struct deck* new_deck();
void drop_deck(struct deck*);
struct deck* deck_iterate(struct deck*);
struct card* deck_node_read(const struct deck*);
bool deck_node_empty(const struct deck*);
void deck_put(struct deck*,struct card*);
struct card* deck_pop(struct deck*);

struct server_state {

};



#endif