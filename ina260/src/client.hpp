#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string>
#include <cstring>
#include <iterator>
#include <map>

#define DEGREE 9

using namespace std;

class Client {

public:
    void Error(const char *msg);                            //error function
    void Call(int argcc, char *argvv[]);                    //Function to ask server pi's for data
    map<std::string, std::string> Mapping(char *argvv[]);   //Function that returns map of data
    void Init();                                            //Start by asking data pi its hostname

private:

    int pies;
    bool pass = false;

    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    bool stop = false;

    FILE *hostname;

    float systemp, millideg;
    FILE *thermal;
    int x;

    char templogs[sizeof(pies)][DEGREE];

    std::map<std::string, std::string> m;
    std::pair<std::string, std::string> p;

    string localhost;
    string host;
    string local = ".local";
    string tempp = "temp\n";
    char buffer[DEGREE];
};

#endif //CLIENT_HPP