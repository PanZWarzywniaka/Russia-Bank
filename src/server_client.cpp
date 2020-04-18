#include "server_client.hpp"
#include <stack>

server_client::server_client() {
    m_server_state = init_server_state();
}
server_client::~server_client() {
    drop_server_state(m_server_state);
}

card* into_c::cpp_card(const Card& crd) {
    return make_card(static_cast<unsigned char>(crd.get_colour()),static_cast<unsigned char>(crd.get_value()));
}
Deck into_cpp::c_deck(const deck* dck,sf::FloatRect fr) {
    Deck ret = Deck(Deck::Type::bank); //tu zmieniłem konstruktor na losowy
    std::stack<const deck*> pointer_depth;
    const deck* curr = dck;
    while(curr->node_below) {
        pointer_depth.push(curr);
        curr = curr->node_below;
    }
    while(!pointer_depth.empty()) {
        auto* curr = pointer_depth.top();
        ret.push(c_card(curr->node_content));
        pointer_depth.pop();
    }
    return ret;
}

Card into_cpp::c_card(const card* crd) {
    return Card(static_cast<Card::Value>(crd->value),static_cast<Card::Colour>(crd->color));
}