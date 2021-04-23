//
// Created by kostyo on 21.04.21.
//

#include <cstring>
#include <atomic>
#include "ipk_simpleftp_client.h"


//void SignalCallbackHandler(int sig_num)
//{
//
//    exit(EXIT_SUCCESS);
//}

//std::atomic<bool> quit(false);    // signal flag
//client_core* client;

//void got_signal(int)
//{
//    std::cout << "quit";
//    quit.store(true);
//    //delete client;
//    exit(EXIT_SUCCESS);
//}

int main(int argc, char **argv){

//    struct sigaction signalAction;
//    memset(&signalAction, 0, sizeof(signalAction));
//    signalAction.sa_handler = got_signal;
//    sigfillset(&signalAction.sa_mask);
//    signalAction.sa_flags = 0;
//    sigaction(SIGINT, &signalAction, NULL);

    int c= 0;
    int port = 115;
    std::string ipAddr = "";

    while ((c = getopt(argc, argv, "h:p:")) != -1) {
        switch (c) {
            case 'h':
                ipAddr = optarg;
                break;
            case 'p':
                port = std::stoi(optarg);
                break;
            case '?':
                break;
                // TODO help
            default:
                std::cout << "Bad argument";
                return 1;
        }
    }

    if(ipAddr.empty()){
        std::cerr << "ERROR: no address specified" << std::endl;
        return (EXIT_FAILURE);
    }

    client_core* client = new client_core(ipAddr, port);
    //signal(SIGINT, SignalCallbackHandler);
    delete client;
}

