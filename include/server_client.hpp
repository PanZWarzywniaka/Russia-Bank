#ifndef SERVER_CLIENT_HPP
#define SERVER_CLIENT_HPP
extern "C"  {
#include "c_server_ffi.h"
}
#include "deck.hpp"



class server_client {
    server_state* m_server_state;
    public:

    server_client();
    ~server_client();
};


namespace into_c {
    card* cpp_card(const Card&);
}

namespace into_cpp {
    Deck c_deck(const deck*, sf::FloatRect);
    Card c_card(const card*);
}

#endif