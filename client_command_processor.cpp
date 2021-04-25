//
// Created by kostyo on 22.04.21.
//

#include <cstring>
#include <algorithm>
#include "client_command_processor.h"
#include <stdio.h>

client_command_processor::client_command_processor(int socket, bool *running) {
    this->sockt = socket;
    this->run = running;

}

client_command_processor::~client_command_processor() {};

void client_command_processor::Process() {

    std::cout << "Enter command: ";
    this->userInput.clear();
    std::getline(std::cin, this->userInput);
    this->command = this->userInput.substr(0, 4);
    //this->userInput.erase(0, 5);
    //std::cout << "Command: " << this->userInput.size() << std::endl;

    switch (this->ParseCommand(this->command)) {
        case USER:
            this->UserCommand();
            break;
        case ACCT:
            this->AcctCommand();
            break;
        case PASS:
            this->PassCommand();
            break;
        case TYPE:
            break;
        case LIST:
            this->ListCommand();
            break;
        case CDIR:
            this->CdirCommand();
            break;
        case KILL:
            this->KillCommand();
            break;
        case NAME:
            break;
        case DONE:
            this->DoneCommand();
            break;
        case RETR:
            break;
        case STOR:
            break;
        case INVALID:
        default:
            this->InvalidCommand();
            break;

    }

}

void client_command_processor::UserCommand() {

    std::string comm = this->userInput;
    comm.erase(0, 5);
    //std::cout << this->userInput << std::endl << comm;

    std::vector<std::string> vec;
    this->SplitString(vec, comm);

    if (vec.size() != 1) {
        this->InvalidCommand();
        return;
    }

    vec[0].insert(0, "USER ");
    //vec[0].push_back('\r');
    vec[0].push_back('\n');
    //std::cout << vec[0] << std::endl;
    if ((send(this->sockt, vec[0].data(), vec[0].size(), 0)) < 0) {
        std::cerr << "ERROR: UserCommand" << std::endl;
        close(this->sockt);
        exit(EXIT_FAILURE);
    }

    this->data.clear();
    memset(this->buffer, 0, 1);
    int received;

    while ((received = recv(this->sockt, &this->buffer, 1, 0)) > 0) {
        if (received < 0) {
            std::cerr << "ERROR: receive" << std::endl;
            close(this->sockt);
            exit(EXIT_FAILURE);
        }
        if (*this->buffer == '\n') {
            break;
        }
        data.append(this->buffer);
    }
    if (this->data.size() == 0) {
        this->ShutDown();
    }
    this->data.append("\n");
    std::cout << this->data;
}


void client_command_processor::AcctCommand() {

    std::string comm = this->userInput;
    comm.erase(0, 5);
    //std::cout << this->userInput << std::endl << comm;

    std::vector<std::string> vec;
    this->SplitString(vec, comm);

    if (vec.size() != 1) {
        this->InvalidCommand();
        return;
    }

    vec[0].insert(0, "ACCT ");
    //vec[0].push_back('\r');
    vec[0].push_back('\n');
    //std::cout << vec[0] << std::endl;
    if ((send(this->sockt, vec[0].data(), vec[0].size(), 0)) < 0) {
        std::cerr << "ERROR: AcctCommand" << std::endl;
        close(this->sockt);
        exit(EXIT_FAILURE);
    }

    this->data.clear();
    memset(this->buffer, 0, 1);
    int received;

    while ((received = recv(this->sockt, &this->buffer, 1, 0)) > 0) {
        if (received < 0) {
            std::cerr << "ERROR: receive" << std::endl;
            close(this->sockt);
            exit(EXIT_FAILURE);
        }
        if (*this->buffer == '\n') {
            break;
        }
        data.append(this->buffer);
    }
    if (this->data.size() == 0) {
        this->ShutDown();
    }
    this->data.append("\n");
    std::cout << this->data;

}

void client_command_processor::PassCommand() {
    std::string comm = this->userInput;
    comm.erase(0, 5);
    //std::cout << this->userInput << std::endl << comm;

    std::vector<std::string> vec;
    this->SplitString(vec, comm);

    if (vec.size() != 1) {
        this->InvalidCommand();
        return;
    }

    vec[0].insert(0, "PASS ");
    //vec[0].push_back('\r');
    vec[0].push_back('\n');
    //std::cout << vec[0] << std::endl;
    if ((send(this->sockt, vec[0].data(), vec[0].size(), 0)) < 0) {
        std::cerr << "ERROR: PassCommand" << std::endl;
        close(this->sockt);
        exit(EXIT_FAILURE);
    }

    this->data.clear();
    memset(this->buffer, 0, 1);
    int received;

    while ((received = recv(this->sockt, &this->buffer, 1, 0)) > 0) {
        if (received < 0) {
            std::cerr << "ERROR: receive" << std::endl;
            close(this->sockt);
            exit(EXIT_FAILURE);
        }
        if (*this->buffer == '\n') {
            break;
        }
        data.append(this->buffer);
    }

    if (this->data.size() == 0) {
        this->ShutDown();
    }
    this->data.append("\n");
    std::cout << this->data;

}

void client_command_processor::CdirCommand() {
    std::string comm = this->userInput;
    comm.erase(0, 5);
    //std::cout << this->userInput << std::endl << comm;

    std::vector<std::string> vec;
    this->SplitString(vec, comm);

    if (vec.size() != 1) {
        this->InvalidCommand();
        return;
    }

    vec[0].insert(0, "CDIR ");
    //vec[0].push_back('\r');
    vec[0].push_back('\n');
    //std::cout << vec[0] << std::endl;
    if ((send(this->sockt, vec[0].data(), vec[0].size(), 0)) < 0) {
        std::cerr << "ERROR: AcctCommand" << std::endl;
        close(this->sockt);
        exit(EXIT_FAILURE);
    }

    this->data.clear();
    memset(this->buffer, 0, 1);
    int received;

    while ((received = recv(this->sockt, &this->buffer, 1, 0)) > 0) {
        if (received < 0) {
            std::cerr << "ERROR: receive" << std::endl;
            close(this->sockt);
            exit(EXIT_FAILURE);
        }
        if (*this->buffer == '\n') {
            break;
        }
        data.append(this->buffer);
    }
    if (this->data.size() == 0) {
        this->ShutDown();
    }
    this->data.append("\n");
    std::cout << this->data;
}

void client_command_processor::ListCommand() {
    std::string comm = this->userInput;
    comm.erase(0, 5);

    std::vector<std::string> vec;
    this->SplitString(vec, comm);

    if (vec.size() != 1 and vec.size() != 2) {
        this->InvalidCommand();
        return;
    }

    if (vec[0].compare("F") != 0 and vec[0].compare("V") != 0) {
        this->InvalidCommand();
        return;
    }

    comm.insert(0, "LIST ");
    comm.push_back('\n');

    if ((send(this->sockt, comm.data(), comm.size(), 0)) < 0) {
        std::cerr << "ERROR: ListCommand" << std::endl;
        close(this->sockt);
        exit(EXIT_FAILURE);
    }

    this->data.clear();
    memset(this->buffer, 0, 1);
    int received;

    while ((received = recv(this->sockt, &this->buffer, 1, 0)) > 0) {
        if (received < 0) {
            std::cerr << "ERROR: receive" << std::endl;
            close(this->sockt);
            exit(EXIT_FAILURE);
        }
        if (*this->buffer == '\n') {
            break;
        }
        data.append(this->buffer);
    }
    if (this->data.size() == 0) {
        this->ShutDown();
    }
    std::replace(data.begin(), data.end(), '&', '\n');
    this->data.append("\n");


    std::cout << this->data;

}

void client_command_processor::KillCommand() {
    std::string comm = this->userInput;
    comm.erase(0, 5);

    std::vector<std::string> vec;
    this->SplitString(vec, comm);

    if (vec.size() != 1) {
        this->InvalidCommand();
        return;
    }

    comm.insert(0, "LIST ");
    comm.push_back('\n');

    if ((send(this->sockt, comm.data(), comm.size(), 0)) < 0) {
        std::cerr << "ERROR: ListCommand" << std::endl;
        close(this->sockt);
        exit(EXIT_FAILURE);
    }

    this->data.clear();
    memset(this->buffer, 0, 1);
    int received;

    while ((received = recv(this->sockt, &this->buffer, 1, 0)) > 0) {
        if (received < 0) {
            std::cerr << "ERROR: receive" << std::endl;
            close(this->sockt);
            exit(EXIT_FAILURE);
        }
        if (*this->buffer == '\n') {
            break;
        }
        data.append(this->buffer);
    }
    if (this->data.size() == 0){
        this->ShutDown();
    }

    this->data.append("\n");
    std::cout << this->data;
}

void client_command_processor::DoneCommand() {

    std::string comm = this->userInput;
    comm.erase(0, 5);


    //this->SplitString(vec, comm);

    if (comm.size() != 0) {
        this->InvalidCommand();
        return;
    }

    comm.insert(0, "DONE\n");

    if ((send(this->sockt, comm.data(), comm.size(), 0)) < 0) {
        std::cerr << "ERROR: PassCommand" << std::endl;
        close(this->sockt);
        exit(EXIT_FAILURE);
    }


    this->data.clear();
    this->userInput.clear();
    *this->run = false;

}


void client_command_processor::ShutDown() {
    std::cout << "SERVER is shutdown" << std::endl;
    this->data.clear();
    this->userInput.clear();
    *this->run = false;
}

void client_command_processor::InvalidCommand() {

    std::cout << "You entered an unknown command" << std::endl;
    return;

}


void client_command_processor::SplitString(std::vector<std::string> &vector, std::string inputString) {

    std::string temp;
    for (int i = 0; i < inputString.length(); i++) {

        if (inputString[i] == ' ') {
            vector.push_back(temp);
            temp = "";
        } else {
            temp.push_back(inputString[i]);
        }
    }
    // push last word
    vector.push_back(temp);
}

int client_command_processor::ParseCommand(std::string command) {
    if (command.compare("USER") == 0) return USER;
    else if (command.compare("ACCT") == 0)return ACCT;
    else if (command.compare("PASS") == 0) return PASS;
    else if (command.compare("TYPE") == 0) return TYPE;
    else if (command.compare("LIST") == 0)return LIST;
    else if (command.compare("CDIR") == 0) return CDIR;
    else if (command.compare("KILL") == 0)return KILL;
    else if (command.compare("NAME") == 0) return NAME;
    else if (command.compare("DONE") == 0)return DONE;
    else if (command.compare("RETR") == 0)return RETR;
    else if (command.compare("STOR") == 0) return STOR;
    else return INVALID;


}