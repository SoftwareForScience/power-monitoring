/* The port number is passed as an argument */
#include <fstream>
#include "client.hpp"



void Client::Connect() {
    libsocket::inet_dgram_client sock(LIBSOCKET_IPv4);

    this->answer.resize(32);

    try {
        std::cout << sock.gethost();
    } catch (const libsocket::socket_exception& exc) {
        std::cerr << exc.mesg;
    }
    try {
        sock.connect(this->host, this->port);
        //sock2.connect(host2, port2);
        while (!this->stop) {
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
}
