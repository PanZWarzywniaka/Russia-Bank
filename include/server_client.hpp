#ifndef SERVER_CLIENT_HPP
#define SERVER_CLIENT_HPP
extern "C"  {
#include "c_server_ffi.h"
}

class server_client {
    server_state* m_server_state;
    public:

    server_client();
    ~server_client();
};

#endif