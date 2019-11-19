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
#include <vector>

#define DEGREE 9

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

    float systemp, millideg;
    FILE *thermal;
    int x;

    char templogs[sizeof(pies)][DEGREE];

    char pi_zero[DEGREE];
    char pi_one[DEGREE];
    char pi_two[DEGREE];
    char pi_three[DEGREE];
    char pi_g[DEGREE];

    std::map<std::string, std::string> m;
    std::pair<std::string, std::string> p;


    //map<char [], char []> temps;

    string localhost;
    string host;
    string local = ".local";
    string tempp = "temp\n";
    char buffer[DEGREE];
};

#endif //CLIENT_HPP