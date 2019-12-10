#ifndef SERVER_HPP
#define SERVER_HPP

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <thread>
#include "../lib/libsocket/headers/exception.hpp"
#include "../lib/libsocket/headers/inetserverdgram.hpp"

using std::string;

class Server
{
public:
    void Connect();
    void Hostname();
    void Startserv();
    void Stopserv();
    std::map<std::string, std::string> Call();
private:
    std::thread* thread;

    bool stop = false;

    string localhost;
    // TODO: Get this from param and/or config file
    string host = "raspberrypi-g.local";
    string port = "20001";

    //string answer("Hello back from the server!");
    string from;
    string fromport;
    string buf;

    std::map<std::string, std::string> m;

};


#endif //SERVER_HPP
