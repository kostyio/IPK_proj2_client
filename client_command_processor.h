//
// Created by kostyo on 22.04.21.
//

#ifndef CLIENT_CLIENT_COMMAND_PROCESSOR_H
#define CLIENT_CLIENT_COMMAND_PROCESSOR_H

#include <string>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <ifaddrs.h>
#include <sys/types.h>   // Types used in sys/socket.h and netinet/in.h
#include <netinet/in.h>  // Internet domain address structures and functions
#include <sys/socket.h>  // Structures and functions used for socket API
#include <arpa/inet.h>
#include <vector>

class client_command_processor {

public:
    client_command_processor(int socket, bool *running);

    ~client_command_processor();

    void Process();

private:
    int sockt;
    bool *run;
    std::string command;
    char buffer[1];
    std::string userInput;
    std::string data;



    int ParseCommand(std::string command);

    // commands
    void InvalidCommand();
    void UserCommand();
    void AcctCommand();
    void PassCommand();

    void SplitString(std::vector<std::string> &vector, std::string inputString);


};

enum Commands {
    USER,
    ACCT,
    PASS,
    TYPE,
    LIST,
    CDIR,
    KILL,
    NAME,
    DONE,
    RETR,
    STOR,
    INVALID
};

#endif //CLIENT_CLIENT_COMMAND_PROCESSOR_H
