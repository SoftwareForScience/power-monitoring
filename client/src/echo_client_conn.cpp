#include <unistd.h>
#include <iostream>
#include <fstream>
#include "../headers/exception.hpp"
#include "../headers/inetclientdgram.hpp"


//g++ -std=c++11 -lsocket++ -o echoclient echo_client_conn.cpp

/*
 * Sends and receives messages via connected UDP sockets
 */

int main(void) {
    using std::string;

    string host = "raspberrypi-g.local";
    //string host2 = "raspberrypi-2.local";
    string port = "20001";
    //string port2 = "20002";
    string answer;
    //string answer2;

    answer.resize(32);

    libsocket::inet_dgram_client sock(LIBSOCKET_IPv4);

    try {
        std::cout << sock.gethost();
    } catch (const libsocket::socket_exception& exc) {
        std::cerr << exc.mesg;
    }
    try {
        sock.connect(host, port);
        std::cout << sock.gethost();
        //sock2.connect(host2, port2);
        while (1) {
            std::ifstream file("/sys/class/thermal/thermal_zone0/temp");
            int rawtemp;
            file >> rawtemp;
            file.close();

            sock << std::to_string((float) rawtemp / 1000);

            usleep(1000);
        }
        sock.deconnect();
    } catch (const libsocket::socket_exception& exc) {
        std::cerr << exc.mesg;
    }

    sock.destroy();

    return 0;
}
