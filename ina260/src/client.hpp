#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <unistd.h>
#include <iostream>
#include <string>
#include "../lib/libsocket/headers/exception.hpp"
#include "../lib/libsocket/headers/inetclientdgram.hpp"

using std::string;

class Client {
public:
    void Error(const char *msg);                //  Error function
	void Connect();
private:

    string host = "raspberrypi-g.local";
    string port = "20001";
    string answer;
    bool stop = false;


};

#endif //CLIENT_HPP