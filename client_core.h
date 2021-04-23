//
// Created by kostyo on 21.04.21.
//

#ifndef CLIENT_CLIENT_CORE_H
#define CLIENT_CLIENT_CORE_H

#include "client_command_processor.h"

class client_core {

public:
    client_core(std::string ipAddress, int port);
    ~client_core();

private:
    void SocketInit();
    void ClientConnect();
    void Run();

    //client
    int sockt;
    struct sockaddr_in interface;

    char buffer[256];
    bool running = true;
    uint16_t port;
    std::string ipAddress;



};


#endif //CLIENT_CLIENT_CORE_H
