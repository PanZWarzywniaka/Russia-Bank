#include "common_ffi.h"

struct card* make_card(unsigned char col, unsigned char val) {
    struct card* ret = malloc(sizeof(struct card));
    ret->color=col;
    ret->value=val;
    return ret;
}

struct deck* new_deck() {
    struct deck* ret = malloc(sizeof(struct deck));
    ret->node_content = NULL;
    ret->node_below = NULL;
    return ret;
}

void drop_deck(struct deck* m_deck) {
    if(m_deck->node_below) {
        drop_deck(m_deck->node_below);
    }
    if(m_deck->node_content) {
        free(m_deck->node_content);
    }
    free(m_deck);
}

struct deck* deck_iterate(struct deck* m_deck) {
    return m_deck->node_below;
}

struct card* deck_node_read(const struct deck* m_deck) {
    return m_deck->node_content;
}

bool deck_node_empty(const struct deck* m_deck) {
    return m_deck->node_content == NULL;
}

void deck_put(struct deck* m_deck,struct card* m_card) {
    struct deck* new_below = new_deck();
    new_below->node_content = m_deck->node_content;
    new_below->node_below = m_deck->node_below;
    m_deck->node_below = new_below;
    m_deck->node_content = m_card;
}

struct card* deck_pop(struct deck* m_deck) {
    struct deck* new_top = m_deck->node_below;
    struct card* ret = m_deck->node_content;
    m_deck->node_content = new_top->node_content;
    m_deck->node_below = new_top->node_below;
    new_top->node_below = NULL;
    new_top->node_content = NULL;
    drop_deck(new_top);
    return ret;
}
