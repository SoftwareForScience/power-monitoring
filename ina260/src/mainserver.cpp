#include "server.hpp"

int main(int argc, char *argv[]) {
    Server serv;
    serv.Connect(argc, argv);

    while(!serv.Stop()){
        serv.Command();
        serv.Stop();
    }
    return 0;
}