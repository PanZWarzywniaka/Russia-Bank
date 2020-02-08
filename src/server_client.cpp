#include "server_client.hpp"

server_client::server_client() {
    m_server_state = init_server_state();
}
server_client::~server_client() {
    drop_server_state(m_server_state);
}