#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

class Client {

public:
    void Error(const char *msg);
    void Command(int argcc, char *argvv[]);
private:

    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];

};

#endif //CLIENT_HPP