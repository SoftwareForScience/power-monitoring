/* The port number is passed as an argument */

#include "server.hpp"


void Server::Connect() {
    this->buf.resize(32);

    try {
        libsocket::inet_dgram_server srv(this->host, this->port, LIBSOCKET_BOTH);
        std::cout << this->host << this->port << std::endl;

        while (!stop) {
//            std::cout << "We komen in connect" << std::endl;
            srv.rcvfrom(this->buf, this->from, this->fromport);

            std::cout << "Datagram from " << this->from << ":" << this->fromport << " "
                      << this->buf << std::endl;
            this->m[this->from] = std::string(this->buf);

            //srv.sndto(answer, from, fromport);
        }

        // libsocket::inet_dgram_server also has a destructor doing this for us, so we are doing explicitly and can reuse the socket.
        srv.destroy();
    } catch (const libsocket::socket_exception& exc) {
        std::cerr << exc.mesg;
    }

}

void Server::Startserv()
{
    Hostname();
    this->stop = false;
    this->thread = new std::thread(&Server::Connect, this);
    this->thread->detach();
}

void Server::Stopserv()
{
    this->stop = true;
    if (this->thread->joinable())
    {
        this->thread->join();
    }

}

void Server::Hostname() {
        std::ifstream lhost("/etc/hostname");
        lhost >> this->localhost;
        lhost.close();
}

std::map<std::string, std::string> Server::Call() {
    std::ifstream file("/sys/class/thermal/thermal_zone0/temp");
    int rawtemp;
    file >> rawtemp;
    file.close();

    this->m[this->localhost] = std::to_string((float) rawtemp / 1000);

    return this->m;
}