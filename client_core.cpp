//
// Created by kostyo on 21.04.21.
//

#include "client_core.h"
#include "client_command_processor.h"


client_core::client_core(std::string ipAddress, int port) {
    this->ipAddress = ipAddress;
    this->port = port;
    this->SocketInit();
    this->ClientConnect();
    this->Run();

}

client_core::~client_core() {
    std::cout << "Shutting down...\n";
    close(this->sockt);
}

void client_core::Run() {

    client_command_processor * commandProcessor = new client_command_processor(this->sockt, &this->running);

    while (this->running) {
    commandProcessor->Process();
    }

    delete commandProcessor;
};

void client_core::ClientConnect() {

    std::cout << "Establishing connection to: " << inet_ntoa(((struct sockaddr_in) interface).sin_addr) << std::endl;

    if (connect(this->sockt, reinterpret_cast<struct sockaddr *>(&interface), sizeof(interface)) < 0) {
        std::cerr << "ERROR: connect" << std::endl;
        close(this->sockt);
        exit(EXIT_FAILURE);
    }

    if ((recv(this->sockt, &this->buffer, 25, 0)) < 0) {
        std::cerr << "ERROR: receive" << std::endl;
        close(this->sockt);
        exit(EXIT_FAILURE);
    }
    std::cout << this->buffer << std::endl;


}

void client_core::SocketInit() {

    if ((this->sockt = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "ERROR: socketCreate" << std::endl;
        close(this->sockt);
        exit(EXIT_FAILURE);
    }

    this->interface.sin_port = htons(this->port);
    this->interface.sin_family = AF_INET;
    inet_pton(AF_INET, ipAddress.data(), &(interface.sin_addr));
    //std::cout << inet_ntoa(((struct sockaddr_in) interface).sin_addr);
    //std::cout << htons(this->interface.sin_port);

}


