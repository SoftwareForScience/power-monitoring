#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <cstring>

using namespace std;

class Server
{
public:
    void Error(const char *msg);
    void Command();
    bool Stop();
    void Connect(int argcc, char *argvv[]);
private:
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    int i;
    bool stop = false;
    string temp;
/*public:
    explicit ina_device(unsigned devID);
    ~ina_device();

private:
    std::string i2cpath = "/dev/i2c-1";
    ina_219_device *dev;
*/
};


#endif //SERVER_HPP
