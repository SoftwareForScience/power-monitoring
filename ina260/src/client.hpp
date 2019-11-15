#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string>
#include <cstring>
#include <iterator>
#include <map>

#define DEGREE 15

using namespace std;

class Client {

public:
    void Error(const char *msg);
    //std::map<char *, char *>  Connect(char *argvv[]);
    void Connect();
    void Command(int argcc, char *argvv[]);
    bool Stop();
    void Init();
    char *pi_temp_zero;
    char *pi_temp_one;
    char *pi_temp_two;
    char *pi_temp_three;
    char *pi_temp_g;
    //map<char *, char *> temperatures;

private:

    int pies;

    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    bool stop = false;

    FILE *hostname;

    char templogs[sizeof(pies)][DEGREE];

    string localhost;
    string host;
    string local = ".local";
    string tempp = "temp\n";
    char buffer[];
};

#endif //CLIENT_HPP