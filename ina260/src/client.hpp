#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string>
#include <cstring>
#include <iterator>
#include <map>

#define DEGREE 9
#define PORT 20001

class Client {
public:
	Client(std::vector<std::string> hostnames);

    void Error(const char *msg);                //  Error function
	std::map<std::string, std::string> Call();  //  Function to ask server pi's for data
private:

    int pies;
    bool pass = false;

    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    std::vector<std::string> hostnames;
    std::map<std::string, std::string> m;
    std::pair<std::string, std::string> p;

    std::string localhost, local = ".local", tempp = "temp\n";
    char buffer[DEGREE];
};

#endif //CLIENT_HPP